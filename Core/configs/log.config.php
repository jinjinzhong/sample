<?php
/**
 * author:LSGOZJ
 * time:2016/10/11 19:32
 * description:日志配置文件
 */
namespace Core\configs;
$config = array(
    //配置日志的存储方法
    'DRIVE' =>  'file',
    'OPTION'=>array(
        'PATH'=>BASEDIR.'/Log',
        'EXT' =>'.log',
    ),
);

return $config;