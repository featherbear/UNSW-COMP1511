#!/bin/bash

INSTANCES=10

fileName=intensity.log
dcc ../intensity.c -o ~/intensity
playerName=`echo 0 | ~/intensity`
rm ~/intensity

function spawnGameLoop {
    while :
        do
            1511 intensity_referee ../intensity.c --no_valgrind --print_summary --quiet | tail -n 30 | tee -a ${fileName}.verbose | tee >(grep "intensity.c:" >> ${fileName}.error ) | grep "$playerName" >> ${fileName}
            #python3 intensity_referee.py ../intensity.c --no_valgrind --print_summary --quiet | tail -n 30 | tee -a ${fileName}.verbose | tee >(grep "intensity.c:" >> ${fileName}.error ) | grep "$playerName" >> ${fileName}
        done
}

function finish {
echo -e "\nQuitting..."
kill $PIDS
echo "Killed PIDs $PIDS"
}

PIDS=
i=0
while ((i++ < $INSTANCES))
    do
        spawnGameLoop &
        PID=$!
        PIDS="${PIDS}${PID} "
        echo Spawning loop with PID $PID
    done

trap finish EXIT
wait