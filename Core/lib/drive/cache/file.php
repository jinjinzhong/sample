<?php

/**
 * author:LSGOZJ
 * time:2016/10/17 14:12
 * description:使用文件静态缓存
 */
namespace Core\lib\drive\cache;

use \Core\lib\config;

class file extends cache
{
    /**
     *增删查缓存数据
     * @param $key ,缓存文件名 $value,缓存内容 $time,0表示永久的
     * @return
     */
    public function cache($key, $value = '', $time = 0)
    {
        $filename = $this->conf['PATH'] . '/' . md5($key) . $this->conf['EXT'];

        //删除缓存
        if (is_null($value)) {
            return @unlink($filename);
        }

        //生成缓存
        if ($value !== '') {//将value值写入缓存文件
            $dir = dirname($filename);
            if (!is_dir($dir)) {
                mkdir($dir, 0777, TRUE);
            }
            $cacheTime = sprintf('%011d', $time);
            return file_put_contents($filename, $cacheTime . json_encode($value));//保证写入的value是字符串,这里或者用序列化的方式serialize()
        }

        //读取缓存
        if (!is_file($filename)) {
            return false;
        }
        $content = file_get_contents($filename);
        $cacheTime = (int)substr($content, 0, 11);

        //缓存失效
        if ($cacheTime != 0 && $cacheTime + filemtime($filename) < time()) {
            unlink($filename);
            return NULL;
        }

        $value = substr($content, 11);
        return json_decode($value, true);//如果是序列化的方式则用unserialize()
    }
}