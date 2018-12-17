#!/bin/bash

LOGFILE=".log"

if [ ! -d "awtk-demo" ]
then
    echo "Please check the working directory" 2>&1
    exit 1
fi

if [ -f "$LOGFILE" ]
then    
    truncate -c -s 0 $LOGFILE
else
    touch "$LOGFILE"
fi

find ./awtk-demo/assets -regex '.*\(ui\|styles\)/.*\(bin\|data\)' -exec rm -rf '{}' \+ 2>>$LOGFILE

python ./scripts/update_res.py app 2>>$LOGFILE

EXIT_STATUS=$?

if [ $EXIT_STATUS == 0 ]
then
    ./bin/demo_ui.exe &
else 
    exit $EXIT_STATUS
fi