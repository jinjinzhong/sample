<?php
/**
 * author:zhongjin
 * time:2016/10/24 12:38
 * description: 显示代码
 */
//获取树的层数，返回该层最多的节点数

class Image
{
    //树相关设置
    //每层之间的间隔高度
    private $level_high = 100;
    //叶子结点之间的宽度
    private $leaf_width = 50;
    //结点圆的半径
    private $rad = 20;
    //根节点离边框顶端距离
    private $leave = 20;
    //树
    private $tree;
    //树的层数
    private $level;
    //树的叶子结点数量的最大值
    private $maxCount;

    //图像相关设置
    //画布宽度
    private $width;
    //画布高度
    private $height;
    //画布背景颜色（RGB）
    private $bg = array(
        220, 220, 220
    );
    //图像句柄
    private $image;

    public function __construct($tree)
    {
        $this->tree = $tree;
        $this->level = $this->getLevel();
        $this->maxCount = $this->GetMaxCount($this->level);
        $this->width = ($this->rad * 2 * $this->maxCount) + $this->maxCount * $this->leaf_width;
        $this->height = $this->level * ($this->rad * 2) + $this->level_high * ($this->level - 1) + $this->leave;
        //1.创建画布
        $this->image = imagecreatetruecolor($this->width, $this->height); //新建一个真彩色图像，默认背景是黑色
        //填充背景色
        $bg = imagecolorallocate($this->image, $this->bg[0], $this->bg[1], $this->bg[2]);
        imagefill($this->image, 0, 0, $bg);
    }

    //返回叶子结点数量的最大值
    function GetMaxCount($level)
    {
        return pow(2, $level - 1);
    }

    //获取树的层数
    function getLevel()
    {
        return $this->tree->Depth();
    }

    //画图
    public function show()
    {
        $this->draw($this->tree->root, 1, 0, 0);
        header("Content-type:image/png");
        imagepng($this->image);
        imagedestroy($this->image);
    }

    //画出树状结构
    private function draw($root, $i, $p_x, $p_y)
    {
        if ($i <= $this->level) {
            $root_y = $i * $this->rad + ($i - 1) * $this->level_high;
            if (!is_null($parent = $root->parent)) {
                if ($root == $parent->left) {
                    $root_x = $p_x - $this->width / (pow(2, $i));
                } else {
                    $root_x = $p_x + $this->width / (pow(2, $i));
                }
            } else {
                //根节点
                $root_x = (1 / 2) * $this->width;
                $root_y += $this->leave;
            }

            //画结点
            $method = 'draw'.get_class($this->tree).'Node';
            $this->$method($root_x,$root_y,$root);

            $black = imagecolorallocate($this->image, 0, 0, 0);
            if (!is_null($parent = $root->parent)) {
                imageline($this->image, $p_x, $p_y, $root_x, $root_y, $black);
            }

            //画左边
            if (!is_null($root->left)) {
                $this->draw($root->left, $i + 1, $root_x, $root_y);
            }
            //画右边
            if (!is_null($root->right)) {
                $this->draw($root->right, $i + 1, $root_x, $root_y);
            }
        }
    }

    //画搜索二叉树结点
    private function drawBstNode($x,$y,$node)
    {
        $black = imagecolorallocate($this->image, 0, 0, 0);
        $pink = imagecolorallocate($this->image, 255, 192, 203);
        imageellipse($this->image, $x, $y, $this->rad * 2, $this->rad * 2, $black);
        imagefill($this->image, $x, $y, $pink);
        imagestring($this->image, 4, $x, $y, $node->key, $black);
    }

    //画平衡二叉树结点
    private function drawAvlNode($x,$y,$node)
    {
        $black = imagecolorallocate($this->image, 0, 0, 0);
        $pink = imagecolorallocate($this->image, 255, 192, 203);
        imageellipse($this->image, $x, $y, $this->rad * 2, $this->rad * 2, $black);
        imagefill($this->image, $x, $y, $pink);
        imagestring($this->image, 4, $x, $y, $node->key.'('.$node->bf.')', $black);
    }

    //画红黑树结点
    private function drawRbtNode($x,$y,$node)
    {
        $black = imagecolorallocate($this->image, 0, 0, 0);
        $gray = imagecolorallocate($this->image, 180, 180, 180);
        $pink = imagecolorallocate($this->image, 255, 192, 203);
        imageellipse($this->image, $x, $y, $this->rad * 2, $this->rad * 2, $black);
        if($node->IsRed == TRUE){
            imagefill($this->image, $x, $y, $pink);
        }else{
            imagefill($this->image, $x, $y, $gray);
        }
        imagestring($this->image, 4, $x, $y, $node->key, $black);
    }
}

//class Client
//{
//    public static function Main()
//    {
//        try {
//            //实现文件的自动加载
//            function autoload($class){
//                include strtolower($class).'.php';
//            }
//            spl_autoload_register('autoload');
//
//            $arr = array(62, 88, 58, 47, 35, 73, 51, 99, 37, 93);
////                $arr = array(1,2,3,4,5,6,7,10);
//            $tree = new Bst();
////            $tree = new Avl();
////            $tree = new Rbt();
//
//            $tree->init($arr);
//            $tree->Delete(62);
////            $tree->Insert(9);
////            $tree->MidOrder();
//            $image = new Image($tree);
//            $image->show();
//        } catch (Exception $e) {
//            echo $e->getMessage();
//        }
//    }
//}
//
//Client::Main();