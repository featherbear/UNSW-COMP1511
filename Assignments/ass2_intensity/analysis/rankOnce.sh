#!/bin/bash

fileName=intensity.log
SCOPE=60

firstPlace=`cat $fileName | grep -P "1\t" -c`
secondPlace=`cat $fileName | grep -P "2\t" -c`
thirdPlace=`cat $fileName | grep -P "3\t" -c`
fourthPlace=`cat $fileName | grep -P "4\t" -c`

# errorCount=`cat $fileName.verbose | grep "intensity.c:" -c`
errorCount=`cat $fileName.error | wc -l`

sum=$(($firstPlace + $secondPlace + $thirdPlace + $fourthPlace))

echo -e "Intensity Game Statistics"
echo -e "======================================"
echo -e "For $sum games..."
echo -e "Pos\tScore\tPercentage"
echo -e "1st\t$firstPlace\t$(($firstPlace*100/$sum))%"
echo -e "2nd\t$secondPlace\t$(($secondPlace*100/$sum))%"
echo -e "3rd\t$thirdPlace\t$(($thirdPlace*100/$sum))%"
echo -e "4th\t$fourthPlace\t$(($fourthPlace*100/$sum))%"
echo -e "There were $errorCount errors"
echo -e "======================================"
echo -e "In the last $SCOPE games..."

firstPlace=`cat $fileName | tail -n $SCOPE | grep -P "1\t" -c`
secondPlace=`cat $fileName | tail -n $SCOPE | grep -P "2\t" -c`
thirdPlace=`cat $fileName | tail -n $SCOPE | grep -P "3\t" -c`
fourthPlace=`cat $fileName | tail -n $SCOPE | grep -P "4\t" -c`
sum=$(($firstPlace + $secondPlace + $thirdPlace + $fourthPlace))

echo -e "Pos\tScore\tPercentage"
echo -e "1st\t$firstPlace\t$(($firstPlace*100/$sum))%"
echo -e "2nd\t$secondPlace\t$(($secondPlace*100/$sum))%"
echo -e "3rd\t$thirdPlace\t$(($thirdPlace*100/$sum))%"
echo -e "4th\t$fourthPlace\t$(($fourthPlace*100/$sum))%"
echo -e "======================================"
