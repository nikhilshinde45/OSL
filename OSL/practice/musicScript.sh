#!/bin/bash

#declaring variable for file name
FILE="musicDB.txt"

insert_rec () {
    read -p "Enter music id (5 digits) : " ID
    if ! [[ $ID =~ ^[1-9][0-9]{4}$ ]] then
        echo -e "\nInvalid music id. Please enter 5 digit number."
        return
    fi
    if grep -qE "^$ID:.*$" $FILE
    then
        echo -e "\nMusic ID already exists"
        return
    fi
    read -p "Enter artist name : " AN
    read -p "Enter soundtrack name : " SN
    read -p "Enter release year : " RY
    if ! [[ $RY =~ ^[0-9]{4}$ ]] then
        echo -e "\nInvalid release year. Please enter 4 digit number."
        return
    fi
    echo "$ID:$SN:$AN:$RY" >> $FILE
    echo -e "\nRecord inserted"
}

display_rec () {
    if [ -e $FILE ] 
    then
        echo -e "\n+------------+--------------------------------+--------------------------------+--------------+"
        echo "|  Music Id  |           Soundtrack           |             Artist             | Release Year |"
        echo "+------------+--------------------------------+--------------------------------+--------------+"
        awk -F ":" '{ printf "| %-10s | %-30s | %-30s | %-12s |\n", $1, $2, $3, $4 }' $FILE | sort
        echo "+------------+--------------------------------+--------------------------------+--------------+"
    else
        echo -e "\nNo Records Inserted"
    fi
}

update_rec () {
    if [ -e $FILE ]
    then
        read -p "Enter music Id to update : " ID
        if grep -qE "^$ID:" $FILE
        then
            read -p "Enter soundtrack name : " SN
            read -p "Enter artist name : " AN
            read -p "Enter release year : " RY
            if ! [[ $RY =~ ^[0-9]{4}$ ]]
            then
                echo -e "\nEnter valid release year"
                return
            fi
            sed -i "s/^$ID:.*$/$ID:$SN:$AN:$RY/" $FILE
            echo -e "\nRecord Updated"
        else
            echo -e "\nMusic ID does not exist"
            return
        fi
    else
        echo -e "\nNo Records inserted"
    fi
}

delete_rec () {
    if [ -e $FILE ]
    then
        read -p "Enter music Id to update : " ID
        if grep -qE "^$ID:" $FILE
        then
            sed -i "/^$ID:.*$/d" $FILE
            echo -e "\nRecord deleted"
        else
            echo -e "\nMusic ID does not exist"
            return
        fi
    else
        echo -e "\nNo Records inserted"
    fi
}

search_rec () {
    if [ -e $FILE ]
    then
        read -p "Enter soundtrack or artist name : " NAME
        if grep -qiF "$NAME" $FILE
        then
            echo -e "\nSearch Results :"
            echo -e "\n+------------+--------------------------------+--------------------------------+--------------+"
            echo "|  Music Id  |           Soundtrack           |             Artist             | Release Year |"
            echo "+------------+--------------------------------+--------------------------------+--------------+"
            grep -iF "$NAME" $FILE | awk -F ":" '{ printf "| %-10s | %-30s | %-30s | %-12s |\n", $1, $2, $3, $4 }' | sort
            echo "+------------+--------------------------------+--------------------------------+--------------+"
        else
            echo -e "\nNo Results Found for Soundtrack"
        fi
    else
        echo -e "\nNo Records inserted"
    fi
}

#main program
main () {
    GO=1
    while [ $GO -eq 1 ]; 
    do
        echo -e "\nEnter choice\n1. Insert Record\n2. Display Records\n3. Update Record\n4. Delete Record\n5. Search Record\n6. Exit\n"
        read CHOICE
        case $CHOICE in
            1)
                insert_rec
                ;;
            2)
                display_rec
                ;;
            3)
                update_rec
                ;;
            4)
                delete_rec
                ;;
            5)
                search_rec
                ;;
            6)
                GO=0
                ;;
            *)
                echo -e "\nInvalid choice"
                ;;
        esac
    done
}

#calling the main function
main