<?php
/**
 * author:LSGOZJ
 * time:2016/10/10 22:48
 * description:<添加简要说明>
 */


namespace Core\lib;

//配置类
class config
{
    private static $configs = array();

    //获取单个配置
    public static function get($name, $file)
    {
        /**
         * 流程：
         * 1、判断配置文件是否存在
         * 2、判断对应的配置是否存在
         * 3、缓存配置
         */
        if (!isset(self::$configs[$file])) {
            $truefile = CORE . '/configs/' . $file . '.config.php';
            if (file_exists($truefile)) {
                $config = include $truefile;
                if (isset($config[$name])) {
                    self::$configs[$file] = $config;
                } else {
                    throw new \Exception("找不到配置项" . $name);
                }
            } else {
                throw new \Exception("找不到配置文件" . $file);
            }
        }
        return self::$configs[$file][$name];
    }
    //加载整个配置文件，获取所有有关的配置
    public static function all($file){
        if (!isset(self::$configs[$file])) {
            $truefile = CORE . '/configs/' . $file . '.config.php';
            if (file_exists($truefile)) {
                $config = include $truefile;
                self::$configs[$file] = $config;
            } else {
                throw new \Exception("找不到配置文件" . $file);
            }
        }
        return self::$configs[$file];
    }
}