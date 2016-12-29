<?php
/**
 * author:LSGOZJ
 * time:2016/10/17 22:39
 * description:<添加简要说明>
 */


namespace Core\lib;
use \Core\lib\config;

class responce
{
    private static $class;
    private static $config;
    public static function init(){
        $config = config::all('responce');
        self::$config = $config;
        $drive = $config["{$config['DRIVE']}"];
        $class = '\Core\lib\drive\responce\\'.$drive;
        self::$class = new $class;
    }
    public static function Encode($code, $msg = '', $data = array()){
//        header("Access-Control-Allow-Origin: *");//定义输出的类型
        echo self::$class->Encode($code,$msg,$data);
        exit;
    }
}