#!/bin/bash

test_file(){
  echo -n "Enter the filename that you want to check: "
  read filename

  if [[ -e "$filename" ]]; then
       echo "File '$filename' exists"
  else
       echo "File '$filename' does not exists"
  fi

}

read_file(){
   echo -n "Enter the filename that you want to read: "

   read filename

   if [[ -e "$filename" ]]; then
      echo -e "\n------------"
      cat "$filename"
       echo -e "\n------------"
  else
    echo "file with filename '$filename'  not found"
   fi
     


}

delete_file(){
   echo -n "Enter the filename you want to delete: "
   read filename

   if [[ -e "$filename" ]]; then
      rm "$filename"
      echo "File deleted successfully"
   else
     echo -n "File with name '$filename' not found"

     fi
}

displaylist(){
  echo -e "\nThe file in directory: "
  ls -l
}

while true;
do
 echo -e "\n===========File Manupulation=========="
 echo "1.Test file"
 echo "2.Read file"
 echo "3.Delete file"
 echo "4.Display files"
 echo "5.Exit"

 echo -n "Enter your choice: "
 read choice

 case $choice in
   1)test_file;;
   2)read_file;;
   3)delete_file;;
   4)displaylist;;
   5)echo "Existing program...";exit;;
   *)echo "Choose correct options..."
   esac
done