<?php
/**
 * Created by PhpStorm.
 * User: zhongjin
 * Date: 2016/11/9
 * Time: 21:43
 */

//定义传递给Insert方法的合法标志
define('DB_INSERT', 1);     //添加一条新纪录
define('DB_REPLACE', 2);    //替换一条已有的记录
define('DB_STORE', 3);      //添加一条新纪录或替换一条已有的记录

//Hash表的桶大小
define('DB_BUCKET_SIZE', 262144);    //桶中有262144个元素指针，每个指针是一个int类型的整数，存储Hash链表的第一个元素的文件偏移量

//指定键的长度为128字节
define('DB_KEY_SIZE', 128);

//指定一条索引记录的长度
define('DB_INDEX_SIZE', DB_KEY_SIZE + 12);

//定义3个返回信息常量
define('DB_KEY_EXISTS', 1);     //调用Insert方法，键重复时返回
define('DB_FAILURE', -1);       //方法调用失败时返回
define('DB_SUCCESS', 0);        //方法调用成功时返回

class DB
{
    private $idx_fp;    //保存索引文件句柄
    private $dat_fp;    //保存数据文件句柄
    private $closed;    //记录数据库是否已经关闭

    //打开数据库
    //@param $pathname 数据库名字
    public function open($pathname)
    {
        $idx_path = "./Index/".$pathname . '.idx';
        $dat_path = "./Data/".$pathname . '.dat';
        if (!file_exists($idx_path)) {
            $init = TRUE;   //决定是否需要初始化索引文件
            $mode = "w + b";    //读写方式，不存在则创建
        } else {
            $init = FALSE;
            $mode = "r + b";    //读写方式，文件必须存在
        }
        $this->idx_fp = fopen($idx_path, $mode);
        if (!$this->idx_fp) {
            return DB_FAILURE;  //方法调用失败
        }

        //如果需要初始化索引文件
        //因为索引文件在刚创建的时候还没有索引块，程序首先要判断是否需要初始化索引文件，如果需要初始化，就把索引块写入到索引文件中
        if ($init) {
            $elem = pack("L", 0x00000000);   //将元素初始化（打包成二进制字符串）为0（长整形），表示该位置hash链表为空链表
            for ($i = 0; $i < DB_BUCKET_SIZE; $i++) {
                fwrite($this->idx_fp, $elem, 4);  //每个整数占4个字节
            }
        }
        //索引文件与数据文件状态是相同的，因此使用同样的打开模式
        $this->dat_fp = fopen($dat_path, $mode);
        if (!$this->dat_fp) {
            return DB_FAILURE;
        }
        $this->closed = FALSE;
        return DB_SUCCESS;  //数据库打开成功
    }

    //Hash函数(使用Times33算法)
    //根据给定的字符串计算Hash值
    //使用Times33算法优点是分布比较均匀，而且速度很快
    private function _hash($string)
    {
        $string = substr(md5($string), 0, 8);
        $hash = 0;
        for ($i = 0; $i < 8; $i++) {
            $hash += $hash * 33 + ord($string{$i}); //获取字符的ASCII码
        }
        return $hash & 0x7FFFFFFF;
    }

    //根据给定的键从数据库中查询到指定的一条记录
    public function fetch($key)
    {
        $offset = ($this->_hash($key) % DB_BUCKET_SIZE) * 4;    //在索引文件中的偏移量

        fseek($this->idx_fp, $offset, SEEK_SET);    //设定文件指针处于索引文件的offset字节处
        $pos = unpack("L", fread($this->idx_fp, 4));
        $pos = $pos[1];     //Hash链表中的第一条索引记录偏移量

        $found = FALSE; //标志是否找到指定的记录

        //遍历记录所在Hash链表（结束条件：1、Hash链表遍历完毕，2、找到指定记录）
        while ($pos) {
            fseek($this->idx_fp, $pos, SEEK_SET);
            //索引块
            $block = fread($this->idx_fp, DB_INDEX_SIZE);
            //获取存储的键值(128个字节)
            //索引记录：0-3链表指针 4-132键值 133-136数据偏移量 137-140数据记录长度
            $cpkey = substr($block, 4, DB_KEY_SIZE);

            //比较字符相等返回 0(为什么这里用strncmp而不是strcmp，那是因为在插入的时候key在索引项的值有可能是被填充过的)
            if (!strncmp($key, $cpkey, strlen($key))) {
                //数据偏移量
                $dataoff = unpack("L", substr($block, DB_KEY_SIZE + 4, 4));
                $dataoff = $dataoff[1];

                //数据长度
                $datalen = unpack("L", substr($block, DB_KEY_SIZE + 8, 4));
                $datalen = $datalen[1];
                $found = TRUE;
                break;
            }
            $pos = unpack("L", substr($block, 0, 4));
            $pos = $pos[1];     //Hash链表中的下一条索引记录的偏移量
        }
        if (!$found) {
            return NULL;
        }
        //在数据文件中地位指针
        fseek($this->dat_fp, $dataoff, SEEK_SET);
        //从数据文件指定指针位置获取长度为$datalen的数据
        $data = fread($this->dat_fp, $datalen);
        return $data;
    }

    //数据插入
    public function insert($key, $data)
    {
        $offset = ($this->_hash($key) % DB_BUCKET_SIZE) * 4;    //获取该$key在hash表(索引文件)中的位置

        //fstat()返回打开文件的信息
        $idxoff = fstat($this->idx_fp);
        $idxoff = intval($idxoff['size']);  //索引文件大小字节数（为了在索引文件末尾插入新的索引记录）

        $datoff = fstat($this->dat_fp);
        $datoff = intval($datoff['size']);

        $keylen = strlen($key);
        //限制key的大小，避免索引记录大小超过DB_INDEX_SIZE
        if ($keylen > DB_KEY_SIZE) {
            return DB_FAILURE;
        }

        //构造索引记录块(下一个链表的指针|键值|数据在数据文件的偏移量|数据存储在数据文件中的长度)
        $block = pack("L", 0x00000000);  //链表指针
        $block .= $key;     //键值
        //将键值填充至128个字符
        $space = DB_KEY_SIZE - strlen($key);
        for ($i = 0; $i < $space; $i++) {
            $block .= pack("C", 0x00);
        }
        $block .= pack("L", $datoff);
        $block .= pack("L", strlen($data));

        //将索引块插入索引文件
        fseek($this->idx_fp, $offset, SEEK_SET);
        $pos = unpack("L", fread($this->idx_fp, 4));
        $pos = $pos[1];

        //hash表中对应位置的链表为空
        if ($pos == 0) {
            //写入链表指针到hash表对应位置
            fseek($this->idx_fp, $offset, SEEK_SET);
            fwrite($this->idx_fp, pack("L", $idxoff), 4);

            //在索引文件末尾添加索引项
            fseek($this->idx_fp, 0, SEEK_END);    //将文件指针指向索引文件末尾
            fwrite($this->idx_fp, $block, DB_INDEX_SIZE);

            //在数据文件末尾添加数据项
            fseek($this->dat_fp, 0, SEEK_END);
            fwrite($this->dat_fp, $data, strlen($data));

            return DB_SUCCESS;
        }
        //假如hash表中对应位置上的链表不为空,则在对应链表后面添加索引项
        $found = FALSE;
        while($pos){
            fseek($this->idx_fp,$pos,SEEK_SET); //移动到hash表对应链表中的各项的文件位置
            $temp_block = fread($this->idx_fp,DB_INDEX_SIZE);
            $cpkey = substr($temp_block,4,DB_KEY_SIZE);
            //如果在索引文件中已经存在key对应的索引项，则不用再插入了
            if(!strncmp($key,$cpkey,strlen($key))){
                $dataoff = unpack("L",substr($temp_block,4+DB_KEY_SIZE,4));
                $dataoff = $dataoff[1];

                $datalen = unpack("L",substr($temp_block,8+DB_KEY_SIZE,4));
                $datalen = $datalen[1];

                $found = TRUE;
                break;
            }
            $prev = $pos;
            $pos = unpack("L",substr($temp_block,0,4));
            $pos = $pos[1];
        }
        //已经存在项
        if($found){
            return DB_KEY_EXISTS;
        }

        //将新索引项和数据追加到文件中
        fseek($this->idx_fp,$prev,SEEK_SET);    //找到对应链表的末尾结点
        fwrite($this->idx_fp,pack("L",$idxoff),4);  //将末尾结点指向新节点
        fseek($this->idx_fp,0,SEEK_END);
        fwrite($this->idx_fp,$block,DB_INDEX_SIZE);
        fseek($this->dat_fp,0,SEEK_END);
        fwrite($this->dat_fp,$data,strlen($data));
    }

    //删除记录(数据文件中的数据并没删除)
    public function delete($key){
        $offset = ($this->_hash($key) % DB_BUCKET_SIZE) * 4;
        fseek($this->idx_fp,$offset,SEEK_SET);

        //Hash表对应位置的链表头
        $head = unpack("L",fread($this->idx_fp,4));
        $head = $head[1];
        $cur = $head;
        $prev = 0;

        $found = FALSE;

        while($cur){
            fseek($this->idx_fp,$cur,SEEK_SET);
            //cur索引块
            $block = fread($this->idx_fp,DB_INDEX_SIZE);

            $next = unpack("L",substr($block,0,4));
            $next = $next[1];

            $cpkey = substr($block,4,DB_KEY_SIZE);
            if(!strncmp($key,$cpkey,strlen($key))){
                //找到待删除的点
                $found = true;
                break;
            }
            //找不到，则继续循环链表
            $prev = $cur;
            $cur = $next;
        }

        if(!$found){
            return DB_FAILURE;
        }

        //如果链表中只有一个结点
        if($prev == 0){
            fseek($this->idx_fp,$offset,SEEK_SET);
            fwrite($this->idx_fp,pack("L",$next),4);
        }else{
            fseek($this->idx_fp,$prev,SEEK_SET);
            fwrite($this->idx_fp,pack("L",$next),4);
        }

        return DB_SUCCESS;
    }

    //将$this->closed设置为true,避免程序多次关闭文件导致错误发生
    public function close(){
        if(!$this->closed){
            fclose($this->idx_fp);
            fclose($this->dat_fp);
            $this->closed = TRUE;
        }
    }
}