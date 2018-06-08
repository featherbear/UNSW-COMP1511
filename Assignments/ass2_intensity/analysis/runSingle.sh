#!/bin/bash

fileName=intensity.log
COUNT=1

while :
do
        echo ${COUNT}
        #1511 intensity_referee intensity.c --no_valgrind >> intensityGiant.log
        #1511 intensity_referee intensity.c --no_valgrind | grep "0x4F7295 with" >> intensity.log
        #1511 intensity_referee intensity.c --no_valgrind | tail -n 30 >> intensity.log.larger
        1511 intensity_referee ../intensity.c --no_valgrind | tail -n 30 | tee -a ${fileName}.verbose | tee >(grep "intensity.c:" >> ${fileName}.error) | grep "0x4F7295 with" >> ${fileName}
        let COUNT=COUNT+1
done
