#!/bin/bash
INTERVAL=3

function loopRank {
    echo -e "Here we go!\n"
    sleep 3
    while :
        do
            ./rankOnce.sh
            sleep $INTERVAL
            clear
        done
}

function finish {
    tput cnorm
    kill $loopPID
}


tput civis
loopRank &

loopPID=$!

trap finish EXIT

./runMany.sh
