#!/bin/bash

FILE="address_book.txt"

search_key(){
   echo -n "Enter the Name or Id you want to search:"
   read key
   grep -i "$key" "$FILE"||echo "NO matching found in the address book"
}

Add_entry(){
  echo -n "Enter the ID:"
  read Id
  echo -n "Enter the name:"
  read name
  echo -n "Enter the phone number:"
  read phone

  echo "$Id;$name;$phone" >> "$FILE"
  echo "Entry Added Successfully"
}

Remove_entry(){
   echo -n "Enter the Id or Name that you want to delete:"
   read dele

   grep -iv "$dele" "$FILE" > temp.txt
   mv temp.txt "$FILE"

   echo "Entry Removed Successfully(If exits)"

}

while true;
do
echo "==========Address Book=========="
echo "You have the following options:"
echo "1.Search Entry"
echo "2.Add Entry"
echo "3.Remove Entry"
echo "4.Exit"

echo "Enter your choice:"
read choice
case $choice in
     1)search_key;;
     2)Add_entry;;
     3)Remove_entry;;
     4)echo "GoodBye!"; exit;;
     *)echo "Choose correct option.";;
esac
done