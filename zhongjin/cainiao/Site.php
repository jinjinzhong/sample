<?php
/**
 * author:zhongjin
 * time:2016/10/30 19:46
 * description: RESTFUL 服务类 Site.php
 */
class Site
{
    private $sites = array(
        1=>'TaoBao',
        2=>'Google',
        3=>'Runood',
        4=>'Baidu',
        5=>'Weibo',
        6=>'Sina'
    );

    public function getAllSite(){
        return $this->sites;
    }

    public function getSite($id){
        $site = array($id=>((isset($this->sites[$id]))?$this->sites[$id]:$this->sites[1]));
        return $site;
    }

}