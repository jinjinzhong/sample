<?php
/**
 * author:LSGOZJ
 * time:2016/10/17 21:32
 * description:<添加简要说明>
 */


namespace Core\lib\drive\cache;
use \Core\lib\config;

abstract class cache
{
    protected $conf;  //相关设置
    protected static $_instance;
    protected function __construct()
    {
        $this->conf = config::get('OPTION', 'cache');
    }

    protected function __clone()
    {
        
    }
    public static function getInstance()
    {
        if (!(self::$_instance instanceof self)) {
            //这里由于父类是抽象方法，因此用延迟静态绑定（运行时多态）
            self::$_instance = new static;
        }
        return self::$_instance;
    }
    public abstract function cache($key, $value = '', $time = 0);
}