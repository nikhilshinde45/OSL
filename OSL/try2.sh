#!/bin/bash

palindrome () {
    len=${#STR}
    for (( i=0; i<(len/2); i++ ))
    do
        if [[ "${STR:i:1}" != "${STR:len-i-1:1}" ]]
        then
            echo -e "Not palindrome"
            return
        fi
    done
    echo -e "Palindrome"
}

read -p "Enter string : " STR
palindrome $STR