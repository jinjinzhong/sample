<?php

/**
 * author:LSGOZJ
 * time:2016/10/17 14:13
 * description:使用redis缓存
 */
namespace Core\lib\drive\cache;

use \Core\lib\config;

class redis extends cache
{
    private $redis;
    protected function __construct()
    {
        parent::__construct();
        $this->redis = new redis;
        $this->redis->connect($this->conf['REDIS_HOST'], $this->conf['REDIS_PORT']);
    }

    /**
     * 增删查缓存数据
     * @param $key ,缓存文件名 $value,缓存内容 $time,0表示永久的
     * @return
     */
    public function cache($key, $value = '', $time = 0)
    {
        //删除缓存
        if (is_null($value)) {
            return $this->delete($key);
        }

        //生成缓存
        if ($value !== '') {//将value值写入缓存文件
            return $this->set($key, $value, $time);
        }

        //读取缓存
        return $this->get($key);
    }

    private function set($key, $value, $cacheTime)
    {
        $value = serialize($value);
        if ($cacheTime <= 0) {
            return $this->redis->set($key, $value);
        } else {
            return $this->redis->setex($key, $cacheTime, $value);
        }
    }

    private function get($key)
    {
        $return = $this->redis->get($key);
        if (!$return) {
            return false;
        }
        return unserialize($return);
    }

    private function delete($key)
    {
        return $this->redis->delete($key);
    }
}