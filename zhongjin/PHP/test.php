<?php
$str = "zhong";
for($i = 0;$i < 10;$i ++){
    $str .= pack("C",0x00);
}

$str .= "jin";

$fp = fopen("data.dat","w+b");
fwrite($fp,$str,100);
fclose($fp);