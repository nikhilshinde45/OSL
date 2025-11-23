#!/bin/bash

# --- Test if File Exists ---
test_file() {
    echo -n "Enter the file name to test: "
    read filename
    if [[ -e "$filename" ]]; then
        echo " File '$filename' exists."
    else
        echo " File '$filename' does NOT exist."
    fi
}

# --- Read File ---
read_file() {
    echo -n "Enter the file name to read: "
    read filename
    if [[ -e "$filename" ]]; then
        echo -e "\n--- Contents of $filename ---"
        cat "$filename"
        echo -e "\n------------------------------"
    else
        echo " File '$filename' not found!"
    fi
}

# --- Delete File ---
delete_file(){
    echo -n "Enter the file name to delete: "
    read filename
    if [[ -e "$filename" ]]; then
        rm "$filename"
        echo " File '$filename' deleted successfully."
    else
        echo " File '$filename' does not exist."
    fi
}

# --- Display List of Files ---
list_files() {
    echo -e "\n Files in Current Directory:"
    ls -1
}

# --- Main Menu Loop ---
while true; do
    echo -e "\n--- FILE MANAGEMENT MENU ---"
    echo "1. Test if file exists"
    echo "2. Read a file"
    echo "3. Delete a file"
    echo "4. Display list of files"
    echo "5. Quit"
    echo -n "Enter your choice: "
    read choice

    case $choice in
        1) test_file ;;
        2) read_file ;;
        3) delete_file ;;
        4) list_files ;;
        5) echo "Exiting program..."; exit 0 ;;
        *) echo "Invalid choice! Please try again." ;;
    esac
done