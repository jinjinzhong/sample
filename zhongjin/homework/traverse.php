<?php

/**
 * Created by PhpStorm.
 * User: zhongjin
 * Date: 2016/10/26
 * Time: 22:32
 * 二叉树的遍历
 */
class traverse
{
    private $tree;

    public function __construct($tree)
    {
        $this->tree = $tree;
    }

    /**
     * 前序遍历(递归方法)
     */
    private function pre_order1($root)
    {
        if (!is_null($root)) {
            $function = __FUNCTION__;
            echo $root->key . " ";
            $this->$function($root->left);
            $this->$function($root->right);
        }
    }

    /**
     * 前序遍历(非递归方法)
     */
//    private function pre_order2($root){
//        if(is_null($root)){
//            return;
//        }
//        $current = $root;
//        $stack = array();
//        array_push($stack,$current);
//        while($node = array_pop($stack)){
//            echo $node->key.' ';
//            if(!is_null($node->right)){
//                array_push($stack,$node->right);
//            }
//            if(!is_null($node->left)){
//                array_push($stack,$node->left);
//            }
//        }
//    }

    private function pre_order2($root)
    {
        if (is_null($root)) {
            return;
        }
        $stack = new splstack();
        $node = $root;
        while (!is_null($node) || !$stack->isEmpty()) {
            while (!is_null($node)) {
                //只要结点不为空就应该入栈保存，与其左右结点无关
                $stack->push($node);
                echo $node->key . ' ';
                $node = $node->left;
            }
            $node = $stack->pop();
            $node = $node->right;
        }

//        $stack = new splstack();
//        $stack->push($root);
//        while(!$stack->isEmpty()){
//            $node = $stack->pop();
//            echo $node->key.' ';
//            if(!is_null($node->right)){
//                $stack->push($node->right);
//            }
//            if(!is_null($node->left)){
//                $stack->push($node->left);
//            }
//        }
    }

    //前序遍历
    public function PreOrder()
    {
        $this->pre_order2($this->tree->root);
    }

    /**
     * 中序遍历(递归方法)
     */
    private function mid_order1($root)
    {
        if (!is_null($root)) {
            $function = __FUNCTION__;
            $this->$function($root->left);
            echo $root->key . " ";
            $this->$function($root->right);
        }
    }

    /**
     * 中序遍历(非递归方法)
     */
    private function mid_order2($root)
    {
        if (is_null($root)) {
            return;
        }

        $stack = new splstack();
        $node = $root;
        while (!is_null($node) || !$stack->isEmpty()) {
            while (!is_null($node)) {
                $stack->push($node);
                $node = $node->left;
            }
            $node = $stack->pop();
            echo $node->key . ' ';
            $node = $node->right;
        }
    }

    //中序遍历
    public function MidOrder()
    {
        //        $this->mid_order1($this->tree->root);
        $this->mid_order2($this->tree->root);
    }

    /**
     * 后序遍历(递归方法)
     */
    private function post_order1($root)
    {
        if (!is_null($root)) {
            $function = __FUNCTION__;
            $this->$function($root->left);
            $this->$function($root->right);
            echo $root->key . " ";
        }
    }

    /**
     * 后序遍历(非递归方法)
     */
    private function post_order2($root)
    {
        if (is_null($root)) {
            return;
        }

        $node = $root;
        $stack = new splstack();
        $lastVisited = NULL;
        $stack->push($node);
        while(!$stack->isEmpty()){
            $node = $stack->top();
            if(($node->left == NULL && $node->right == NULL) || ($node->right == NULL && $lastVisited == $node->left) || ($lastVisited == $node->right)){
                echo $node->key.' ';
                $lastVisited = $node;
                $stack->pop();
            }else{
                if($node->right){
                    $stack->push($node->right);
                }
                if($node->left){
                    $stack->push($node->left);
                }
            }
        }
    }

    //后序遍历
    public function PostOrder()
    {
        //        $this->post_order1($this->tree->root);
        $this->post_order2($this->tree->root);
    }

    /**
     * 获取树的层数
     */
    private function getdepth($root)
    {
        if ($root == NULL) {
            return 0;
        }

        $dl = $this->getdepth($root->left);
        $dr = $this->getdepth($root->right);

        return ($dl > $dr ? $dl : $dr) + 1;
    }

    /**
     * 层次遍历(递归方法)
     */
    private function level_order1($root,$level){
        if($root == NULL || $level < 1){
            return;
        }
        if($level == 1){
            echo $root->key.' ';
            return;
        }
        if(!is_null($root->left)){
            $this->level_order1($root->left,$level - 1);
        }
        if(!is_null($root->right)){
            $this->level_order1($root->right,$level - 1);
        }
    }

    /**
     * 层次遍历(非递归方法)
     */
    private function level_order2($root){
        if(is_null($root)){
            return;
        }

        $node = $root;
        //利用队列实现
//        $queue = array();
//        array_push($queue,$node);
//
//        while(!is_null($node = array_shift($queue))){
//            echo $node->key.' ';
//            if(!is_null($node->left)){
//                array_push($queue,$node->left);
//            }
//            if(!is_null($node->right)){
//                array_push($queue,$node->right);
//            }
//        }

        $queue = new splqueue();
        $queue->enqueue($node);
        while(!$queue->isEmpty()){
            $node = $queue->dequeue();
            echo $node->key.' ';
            if (!is_null($node->left)) {
                $queue->enqueue($node->left);
            }
            if (!is_null($node->right)) {
                $queue->enqueue($node->right);
            }
        }
    }

    //层次遍历
    public function LevelOrder(){
//        $level = $this->getdepth($this->tree->root);
//        for($i = 1;$i <= $level;$i ++){
//            $this->level_order1($this->tree->root,$i);
//        }

        $this->level_order2($this->tree->root);
    }
}

class Client
{
    public static function Main()
    {
        try {
            //实现文件的自动加载
            function autoload($class)
            {
                include strtolower($class) . '.php';
            }

            spl_autoload_register('autoload');

            $arr = array(10, 8, 12, 7, 9, 11, 13);
            $tree = new Bst();
//            $tree = new Avl();
//            $tree = new Rbt();

            $tree->init($arr);

            $traverse = new traverse($tree);
            $traverse->LevelOrder();
//            $image = new image($tree);
//            $image->show();
        } catch (Exception $e) {
            echo $e->getMessage();
        }
    }
}

CLient::Main();