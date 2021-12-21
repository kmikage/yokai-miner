#!/bin/bash

# 監視用スクリプト
watch -n 1 "uptime; echo ---; cat output; echo ---; ps aux | grep find.php"

