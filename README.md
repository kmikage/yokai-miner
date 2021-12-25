# yokai-miner
妖怪道中記 隠しパスワード解析ツール for Linux.

## About
PCE版 妖怪道中記のパスワード探索をするツール  
https://twitter.com/4STUDIO4/status/1472415489595174912

地獄の沙汰もなんとやら :)

## How to Build

### 1. Install
Install g++, php7-cli.

### 2. Compile yokai02
`% g++ -o yokai02 yokai02.cpp `

### 3. chmod
```
% chmod +x ./chk.sh
% chmod +x ./yokai02
% chmod +x ./watch.sh
``` 

## 使い方

### 設定ファイルの修正
`config.php`を編集し、探索に必要な設定をおこないます。
- パスワードの文字数
- 探索中のパスワード表示
- マルチコアについての設定
- 辞書ファイルの指定
- チェック用スクリプトの指定
- デバッグモード（動作のトレース）

### 探索の実行
`% php ./find.php`

### Prefix, Suffixの指定
`% php ./find.php <Prefix> <Suffix>`  
Suffixのみ指定する場合、Prefixを`""`で埋めます    
`% php ./find.php "" <Suffix>`

### Run Hashing Tool
`% ./yokai02 <PASSWORD>`  
```
$ ./yokai02 HEITAISUGOI
8F 22 0B EE C1 20 6D 13
```

# Thanks.
`yokai02` Original code.  
http://i486.mods.jp/ichild/yokaipw