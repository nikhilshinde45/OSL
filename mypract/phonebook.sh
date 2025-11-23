#!/bin/bash

FILE="phonebook.txt"
add_entry(){
  echo -n "Enter the first name: "
  read fname
  echo -n "Enter the last name: "
  read lname
  echo -n "Enter the phone: "
  read phone

  echo -e "${fname}\t${lname}\t${phone}" >> "$FILE"
  echo "Entry Added Successfully" 

}

search_entry(){
  echo -n "Enter the name that you want to search: "
  read key
  grep -i "$key" "$FILE"||echo "No matching record found"

}

sort_record(){
  echo -n "Sorted by last name: "
 # sort -k2 "$FILE"
  sort -k2 "$FILE" -o "$FILE"
  # to write sorted result back in file
}

delete_entry(){
   echo -n "Enter the name or phone no that you want to delete: "
   read key
   grep -iv "$key" "$FILE" > temp.txt
   mv temp.txt "$FILE"

   echo "Entry removed successfully"
}

display_all(){
  echo "----------Phonebook Records----------"
  cat "$FILE"
}

while true;
do
echo "==========Phone Book=========="
echo "1.Add new entry"
echo "2.Search the entry"
echo "3.Delete the entry"
echo "4:Sort record"
echo "5.Display record"
echo "6.Exit"

echo "Enter the choice:"
read choice

  case $choice in
     1)add_entry;;
     2)search_entry;;
     3)delete_entry;;
     4)sort_record;;
     5)display_all;;
     6)echo "Goodbye!";exit;;
     *)echo "Choose correct option..."

  esac
done


#e echo "Enter name to edit:"
#     read name

#     # Check if name exists
#     if ! grep -q "$name" addressbook.txt; then
#         echo "No such record found!"
#         return
#     fi

#     echo "Enter new details (format: Name:Phone:Email:Address):"
#     read new_entry

#     # Replace old entry with new one
#     grep -v "$name" addressbook.txt > temp.txt
#     echo "$new_entry" >> temp.txt
#     mv temp.txt addressbook.txt

#     echo "Recorddit_entry() {
#     updated!"
# }
