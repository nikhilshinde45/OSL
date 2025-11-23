#!/bin/bash

factorial () {
    ANS=1
    num=$1
    while [ $num -ne 0 ]
    do
        ANS=(( $ANS \* $num ))
        num=(( $num - 1 ))
    done
    echo "Factorial = $ANS"
}

factorial 5