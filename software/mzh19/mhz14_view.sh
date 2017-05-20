#Set permisions
sudo chmod o+rwx /dev/ttySC0


#!/bin/bash

# Port setting
stty -F /dev/ttySC0 cs8 -echo -cstopb -ixon -istrip raw speed 9600


# Loop
while [ 1 ]; 
do
    #echo 'LOADING...'
    printf "\377\001\206\000\000\000\000\000\171" > /dev/ttySC0 &  
    #FRAME_READ=`dd if=/dev/ttySC0 count=1 bs=20 status=none | hexdump -v -C`
    sleep 3

    #printf "\033c"
    #echo $FRAME_READ
    #PPM=$(echo $FRAME_READ | awk '{print ($2)}')
    #echo CO2 = $PPM PPM
    #echo
    #echo '[PRESS Ctrl + C TO EXIT]'
done


