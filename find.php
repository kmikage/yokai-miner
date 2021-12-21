<?php

// 妖怪道中記 password miner
// 2021.12.21 kei.

// ---
// Configration

// パスワードの文字数
$config['length']       = 14;
// デバッグ表示
$config['debug']        = false;
// チェックの処理をバックグラウンドで実行
$config['background']   = true;

// build ytoa array
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
    if($config['debug']) echo ('Testing -> '. $PASSWORD .'('. strlen($PASSWORD) .')'. "\n");

    // Kick checker
    if($config['background']) {
        exec ('./chk.sh '.$PASSWORD. '&' ); // for background
    } else {
        exec ('./chk.sh '.$PASSWORD );} // for foreground
}

function build_password($PASSWORD, $len){
    global $ytoa;
    global $config;
    if (strlen($PASSWORD) == 14) {
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


function build_ytoa() {
    $ytoa[]="A";
    $ytoa[]="B";
    $ytoa[]="C";
    $ytoa[]="D";
    $ytoa[]="E";
    $ytoa[]="F";
    $ytoa[]="G";
    $ytoa[]="H";
    $ytoa[]="I";
    $ytoa[]="J";
    $ytoa[]="K";
    $ytoa[]="L";
    $ytoa[]="M";
    $ytoa[]="N";
    $ytoa[]="O";
    $ytoa[]="P";
    $ytoa[]="Q";
    $ytoa[]="R";
    $ytoa[]="S";
    $ytoa[]="T";
    $ytoa[]="U";
    $ytoa[]="V";
    $ytoa[]="W";
    $ytoa[]="X";
    $ytoa[]="Y";
    $ytoa[]="Z";
    $ytoa[]="-";
    $ytoa[]=".";
    $ytoa[]="1";
    $ytoa[]="2";
    $ytoa[]="3";
    $ytoa[]="4";
    $ytoa[]="5";
    $ytoa[]="6";
    $ytoa[]="7";
    $ytoa[]="8";
    $ytoa[]="9";
    $ytoa[]="0";
    $ytoa[]="!";
    $ytoa[]="n";
    $ytoa[]="m";
    $ytoa[]="c";

    return($ytoa);
}
