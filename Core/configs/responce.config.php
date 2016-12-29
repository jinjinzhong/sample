<?php
/**
 * author:LSGOZJ
 * time:2016/10/17 22:41
 * description:格式化返回配置文件
 */

namespace Core\configs;

$config = array(
    //默认的传输格式
    'DRIVE'  => 'JSON',
    
    'JSON'      => 'jsonEncode',
    'XML'       => 'xmlEncode',
);

return $config;