<?php
/**
 * author:LSGOZJ
 * time:2016/10/17 20:27
 * description:<添加简要说明>
 */


namespace Core\lib;
use Core\lib\config;

class cache
{
    /**
     * 1、确定缓存的存储方式
     * 2、写缓存
     * 3、读缓存
     * 4、删缓存
     */

    private static $class;

    //初始化，确定存储方式
    public static function init(){
        //确定存储方式
        $drive = config::get('DRIVE','cache');
        $class = '\Core\lib\drive\cache\\'.$drive;
        self::$class = $class::getInstance();
    }
    /**
     *增删查缓存数据
     *@param $key,缓存文件名 $value,缓存内容 $time,0表示永久的
     *@return
     */
    public static function cache($key,$value = '',$time = 0){
        return self::$class->cache($key,$value,$time);
    }



}