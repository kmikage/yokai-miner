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

// ---
// コンフィグのロード
require_once('./config.php');

// ---
// 辞書の構築
require_once($config['dicfile']);
$ytoa=build_ytoa();


// ---
// get Prefix and Suffix

// Prefix
if (isset($argv[1])) {
    $input['prefix'] = $argv[1];
} else {
    $input['prefix'] = '';
}

// Suffix
if (isset($argv[2])) {
    $input['suffix'] = $argv[2];
} else {
    $input['suffix'] = '';
}

// ---
// 探索（無限ループ）
while (true) {
 # kick build password
 build_password($input['prefix']);
}

// ---
// Functions

function exec_chk($password) {
    global $config;

    // for Debug.
    if($config['view']) echo ('Testing -> '. $password .'('. strlen($password) .')'. "\n");

    if($config['bg']) {
        // background
        exec ('./chk.sh '.$password. '&' );
    } else {
        // foreground
        exec ('./chk.sh '.$password );}
}

function build_password($password) {
    global $ytoa;
    global $config;
    global $input;

    $password_len = strlen($password);

    // for Debug
    if($config['debug']) echo ('Testing -> '. $password .'('. strlen($password) .')'. "\n");


    if ($password_len == $config['len']) {
        // 文字数を満たした場合、チェックスクリプトに渡す
        exec_chk($password);
    } else {
        // 辞書からランダムな1つを追加
        while(true) {
            if ( ($password_len + strlen($input['suffix'])) == $config['len'] ) {
                $w=$input['suffix'];
            } else {
                $w=$ytoa[rand(0, count($ytoa) - 1)];
            }
            // 複数文字の対応
            if (($password_len + strlen($w)) <= $config['len']) break;
        }

        $password_new=$password.$w;
        build_password($password_new);
    }

}
