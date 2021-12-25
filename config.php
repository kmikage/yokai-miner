<?php
// yokai-miner 設定ファイル

// パスワードの文字数
$config['len']  = 14;

// デバッグ表示
// 探索中のパスワードを表示します
$config['view'] = false;

// チェックの処理をバックグラウンドで実行
// パスワードのチェック処理を、バックグラウンドで実行します

// true - CPUコア数が多い場合(推奨)
// false - 1スレッドでの動作
$config['bg']   = true;

// 辞書ファイル名
$config['dicfile'] = './dic.php';

// デバッグモード
$config['debug'] = true;
