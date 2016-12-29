<?php
/**
 * author:LSGOZJ
 * time:2016/10/11 19:28
 * description:日志处理类文件
 */


namespace Core\lib;
use Core\lib\config;

class log
{
    private static $class;
    /**
 * 1、确定日志的存储方式
 * 2、写日志
 */

    //初始化，确定存储方法
    public static function init(){
        //确定存储方式
        $drive = config::get('DRIVE','log');
        $class = '\Core\lib\drive\log\\'.$drive;
        self::$class = $class::getInstance();
    }
    public static function log($name,$file = 'log'){
        self::$class->log($name,$file);
    }
}