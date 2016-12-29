<?php

/**
 * author:LSGOZJ
 * time:2016/10/11 22:35
 * description:<添加简要说明>
 */
namespace App\Model;

use Core\lib\Model;

class UserModel extends Model
{
    public $table;

    /**
     * 初始化表名称，如果是比较复杂的超过两个表的Model，可以不实现该方法
     */
    public function __construct()
    {
        parent::__construct();
        $path_arr = explode('\\', __CLASS__);
        $this->table = strtolower(substr($path_arr[count($path_arr) - 1], 0, strlen($path_arr[count($path_arr) - 1]) - 5));
    }

    //下面的对表的增删改查都是使用medoo的语法

    /**
     * 从数据库中获取数据（可能不止一条）
     * @param null
     * @return array   从数据库中返回的数据
     */
    public function lists()
    {
        $data = $this->select(
            $this->table,
            ['name','mobile','regtime'],
            ["id[<]"=>10]
        );
        return $data;
    }

    //获取一条数据
    public function getOne($id)
    {

    }

    public function setOne($id, $data)
    {

    }

    public function delOne($id)
    {

    }
}