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

## How to use

### Configure
edit `find.php`

### Run Miner
`% php ./find.php`

(option)  
add Prefix.  
`% php ./find.php <Password Prefix>`

### Run Hashing Tool
`% ./yokai02 <PASSWORD>`  
```
$ ./yokai02 HEITAISUGOI
8F 22 0B EE C1 20 6D 13
```

