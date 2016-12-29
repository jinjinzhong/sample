<?php
/**
 * author:LSGOZJ
 * time:2016/10/11 19:30
 * description:日志存到文件系统中
 */
namespace Core\lib\drive\log;
use \Core\lib\config;

class file extends log
{
    public function log($message, $file = 'log')
    {
        /**
         * 1、确定文件的存储位置是否存在
         *  新建目录
         * 2、写入目录
         */

        //为了避免log文件过大，每个小时建一个目录存放log文件
        if (!is_dir($this->conf['PATH'].'/'.date('Ymd'))) {
            mkdir($this->conf['PATH'].'/'.date('Ymd'), 0777, true);
        }
        $line = '################################################## '.date('Y-m-d H:i:s', time()).' ##################################################';
        return file_put_contents($this->conf['PATH'].'/'.date('Ymd') . '/' . $file .$this->conf['EXT'] , $line.PHP_EOL.json_encode($message).PHP_EOL.PHP_EOL,FILE_APPEND);
    }
}