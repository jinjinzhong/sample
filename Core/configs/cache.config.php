<?php
/**
 * author:LSGOZJ
 * time:2016/10/17 20:04
 * description:缓存设置
 */

namespace Core\configs;

$config = array(
    //配置缓存的文件存储方法
    'DRIVE' => 'file',
    'OPTION'=>array(
        'PATH'=> BASEDIR.'/Cache',
        'EXT' => '',
    ),
    //配置缓存的redis存储方法
//    'DRIVE' =>  'redis',
//    'OPTION'=>  array(
//        'REDIS_HOST'	 =>		'127.0.0.1',	//Redis主机
//        'REDIS_PORT'	 =>		'6379',
//    ),
);

return $config;