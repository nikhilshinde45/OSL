#!/bin/bash

#This script checks the presence of text files as albums. So keep it in saperate folders where no other text files are present.

#function to create an album (file)
create_album () {
	#-p option allows to print string before reading value into a variable
	read -p "Enter album name (without spaces and extension) : " ALBUM
	FILE="$ALBUM.txt"
	#-e options to check if file exists
	if [ -e $FILE ]
	then
		#-e option in echo is used to recognise escape sequences
		echo -e "\nInserting records in Album : $ALBUM"
	else	
		touch $FILE
		echo -e "\nCreated New Album : $ALBUM"
	fi		
}

#function to display all albums
display_album () {
	print_line 3
	#check if any txt file (album) exists
	if [ -e *.txt ]
	then
		echo " Your Albums "
		print_line 4
		#-F option to give the formatting character to split line about
		find *.txt | awk -F. '{ printf " %-30s ", $1 }'
	else
		echo " No albums found"
	fi	
	print_line 3
}

#function to delete an album (file)
delete_album () {
	read -p "Enter album name to delete : " A_
	F_="$A_.txt"
	if [ -e $F_ ]
	then
		rm $F_
		echo -e "\nAlbum deleted"
	else
		echo -e "\nAlbum doesn't exist"
	fi
}

#function to print a specific type of line based on parameter
print_line () {
	if [ $1 -eq 1 ]
	then
		echo "-------------+----------------------------------+----------------------------------+---------------"		
	elif [ $1 -eq 2 ]
	then
		echo -e "\n===================================================================================================\n"
	elif [ $1 -eq 3 ]
	then
		echo -e "\n================================\n"	
	elif [ $1 -eq 4 ]
	then
		echo "--------------------------------"	
	fi	
}

#function to insert a single record
insert_rec () {	
	create_album
	read -p "Enter music id : " MUSIC_ID
	if ! [[ $MUSIC_ID =~ ^[1-9][0-9]{4}$ ]]
	then
		echo -e "\nInvalid Music Id ! Enter 5 digit Music Id"
		return
	fi
	#check for repetition of music id
	#-q option searches in quiet mode and returns status only
	#-E option allows the grep to interpret the search string as regex
	if grep -qE "^$MUSIC_ID:" $FILE
	then
		echo -e "\nMusic Id already exists"
		return
	fi
	read -p 'Enter music name : ' MUSIC_NAME
 	read -p 'Enter artist name : ' ARTIST_NAME
	read -p 'Enter release year : ' RL_YEAR
	#validations of release year (first digit 1,2 and last 3 digit 0-9)
	if ! [[ $RL_YEAR =~ ^[1-2][0-9]{3}$ ]]
	then
		echo -e "\nInvalid Release Year !"
		return
	fi
	echo -e "$MUSIC_ID:$MUSIC_NAME:$ARTIST_NAME:$RL_YEAR" >> $FILE
	echo -e '\nRecord inserted'
}

#function to search a record
search_rec () {
	read -p "Enter album name to search records : " A_
	FILE="$A_.txt"
	if [ -e $FILE ]
	then
		read -p 'Enter music name : ' MUSIC_NAME
		print_line 2
		#search the music name in quiet mode and return the status
		#-i option is used to search in case insensitive mode
		#-F option is used to not to split the search string about spaces
		grep -qiF ":$MUSIC_NAME" $FILE
		#status returned is 0 if the name is found
		if [ $? -eq 0 ]
		then
			echo " Music Id    |  Music name                      |  Artist                          |  Release year "
			print_line 1
			#pipe the output of grep to awk to display in proper format
			#-F option in grep to intrepret the search string literally
			grep -iF ":$MUSIC_NAME" $FILE | awk -F: '{ printf " %-10s  |  %-30s  |  %-30s  |  %-15s \n", $1, $2, $3, $4 }'
		#status returned is 1 if the name is not found
		else
			echo -e "No records found"
		fi
	else
		print_line 2
		echo -e "Album doesn't exist"
	fi
	print_line 2
}

#function to display all records
display_all () {
	read -p "Enter album name to display records : " A_
	FILE="$A_.txt"
	print_line 2
	if [ -e $FILE ]
	then
		echo -e " Album Name : $A_"
		print_line 2
		echo -e " Music Id    |  Music name                      |  Artist                          |  Release year "
		print_line 1
		#-F option of awk splits the line about the preceding character
		awk -F: '{ printf " %-10s  |  %-30s  |  %-30s  |  %-15s \n", $1, $2, $3, $4 }' $FILE | sort
	else
		echo -e "Album doesn't exist"
	fi
	print_line 2
}

#function to update a record
update_rec () {
	read -p "Enter album name to search records : " A_
	FILE="$A_.txt"
	#check if the file exists
	if [ -e $FILE ]
	then
		read -p "Enter music id to update rec : " MUSIC_ID
		if ! [[ $MUSIC_ID =~ ^[1-9][0-9]{4}$ ]]
		then
			echo -e "\nEnter valid music Id"
			return
		fi
		#-E option to search the music id in a regex pattern
		if grep -qE "^$MUSIC_ID:" $FILE
		then
			#read new values from user
			read -p "Enter music name : " MUSIC_NAME
			read -p "Enter artist name : " ARTIST_NAME
			read -p "Enter release year : " RL_YEAR
			if ! [[ $RL_YEAR =~ ^[12][0-9]{3}$ ]]
			then
				echo -e "\nInvalid Release Year !"
				return
			fi
			#-i option of sed to reflect changes in file
			#.* in regular expression matches any string that comes after music id until \n is encountered
			sed -i "s/^$MUSIC_ID:.*$/$MUSIC_ID:$MUSIC_NAME:$ARTIST_NAME:$RL_YEAR/" $FILE
			echo -e "\nRecord updated"
		else
			echo -e "\nNo record found"
		fi	

	else
		echo -e "Album doesn't exist"
	fi
}

#fucntion to delete a record
delete_rec () {
	read -p "Enter album name to search records : " A_
	FILE="$A_.txt"
	if [ -e $FILE ]
	then
		read -p "Enter music id to delete rec : " MUSIC_ID
		if ! [[ $MUSIC_ID =~ ^[1-9][0-9]{4}$ ]]
		then
			echo -e "\nEnter valid music Id"
			return
		fi
		if grep -qE "^$MUSIC_ID:" $FILE
		then
			sed -i "/^$MUSIC_ID:/d" $FILE
			echo -e "\nRecord deleted"
		else
			echo -e "\nNo record found"
		fi	
	else
		echo -e "Album doesn't exist"
	fi	
}

#main program
GO=1
while [ $GO -eq 1 ]
do
	echo -e "\nChoose operation\n1. Display all albums\n2. Insert a record\n3. Search records\n4. Display all records\n5. Update a record\n6. Delete a record\n7. Delete an album\n8. Exit\nEnter choice : \c"
	read CH
	case $CH in
	1)
		display_album
		;;
	2)
		insert_rec
		;;
	3)
		search_rec
		;;
	4)
		display_all
		;;
	5)
		update_rec
		;;
	6)
		delete_rec
		;;
	7)
		delete_album
		;;	
	8)
		GO=0
		;;
	*)
		echo -e "\nInvalid input !"
		;;
	esac
done
