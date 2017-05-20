#Set permisions
sudo chmod o+rwx /dev/ttyUSB0


#!/bin/bash

# Port setting
stty -F /dev/ttySC1 cs8 cstopb -ixon raw speed 9600

# Loop
while [ 1 ]; 
do
    #echo 'LOADING...'
    FRAME_READ=`dd if=/dev/ttySC1 bs=10 count=1 status=none | hexdump -d`
    printf "\033c"
    PM2DOT5=$(echo $FRAME_READ | awk '{print ($3/10)}')
    PM10=$(echo $FRAME_READ | awk '{print ($4/10)}')
    echo PM2.5 = $PM2DOT5 µg/m3
    echo PM10 = $PM10 µg/m3
    echo
    echo '[PRESS Ctrl + C TO EXIT]'
	sleep 1
done


