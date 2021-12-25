<?php

// 妖怪道中記 password miner
// 2021.12.21 kei.

// ---
// Configration

// パスワードの文字数
$config['len']  = 14;
// デバッグ表示
$config['view'] = false;
// チェックの処理をバックグラウンドで実行
$config['bg']   = true;

// コンフィグのロード
require_once('./config.php');

// 辞書の構築
require_once($config['dicfile']);
$ytoa=build_ytoa();

// ---
// First PASSWORD form option.
$PASSWORD='';
if ( $argc == 2 ) $PASSWORD=$argv[1];

while (true) {
 # kick build password
 build_password($PASSWORD, strlen($PASSWORD));
}

exit;

// ---
// Functions

function exec_chk($PASSWORD) {
    global $config;

    // for Debug.
    if($config['view']) echo ('Testing -> '. $PASSWORD .'('. strlen($PASSWORD) .')'. "\n");

    // Kick checker
    if($config['bg']) {
        exec ('./chk.sh '.$PASSWORD. '&' ); // for background
    } else {
        exec ('./chk.sh '.$PASSWORD );} // for foreground
}

function build_password($PASSWORD, $len){
    global $ytoa;
    global $config;
    if (strlen($PASSWORD) == $config['len']) {
        exec_chk($PASSWORD);
    } else {
        $w=$ytoa[rand(0, count($ytoa) - 1)];
        $PASSWORDn=$PASSWORD.$w;
        build_password($PASSWORDn, $len + 1);

    /*** 総当たり用
    foreach ($ytoa as $w) {
        $PASSWORDn=$PASSWORD.$w;
        build_password($PASSWORDn, $len + 1);
    }
    ***/
    }
}
