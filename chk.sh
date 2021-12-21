#!/bin/bash

# パスワードをチェックするスクリプト
TARGET="65 94 0E AC E9 07 33 25"

### for Debug.
# HEITAISUGOI
# TARGET="8B 71 0B 15 42 18 AE 15"

PASSWORD=${1}
if [ "${PASSWORD}" = "" ]; then
echo "oops... XD"
echo "% chk.sh <PASSWORD>"
exit 1
fi

# 同じ文字の連続を回避
FLG1=`echo ${PASSWORD} | grep -E "([0-9A-Z])\1{2,}" | wc -l`
if [ "${FLG1}" = "1" ]; then
 exit
fi

# HONBAN
FLG2=`./yokai02 ${PASSWORD} | grep "${TARGET}" | wc -l`

if [ "${FLG2}" = "1" ]; then
 echo "${PASSWORD} ${TARGET}" >> ./output

 ### for WebHook Notify :)
 #
 # DATA=`echo "{\"username\": \"yokai02\", \"content\": \"${PASSWORD} ${CODE}\"}"`
 # curl \
 # -H "Content-Type: application/json" \
 # -X POST -d "${DATA}" \
 # https://discord.com/api/webhooks/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

fi

exit
