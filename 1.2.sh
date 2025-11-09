#!/bin/bash

Phone_Book="/home/vrishabh-patni/Desktop/phonebook.txt"

add_entry() {
	echo -n "Enter First name: "
	read fName
	echo -n "Enter Last Name: "
	read lName
	echo -n "Enter phone number: "
	read pnumber
	
	if [ -z "$fName" ] || [ -z "$lName" ] || [ -z "$pnumber" ]; then
		echo "All details required."
	else
		echo "${fName}  	${lName}  	${pnumber}" >> "$Phone_Book"
		echo "Record added successfully"
	fi
}

search_record() {
	if [ ! -f "$Phone_Book" ] || [ ! -s "$Phone_Book" ]; then
		echo "No phone book created or it is empty"
		return
	fi
	echo -n "Enter name or phone number to be searched: "
	read rec
	if grep -i "$rec" "$Phone_Book" > /dev/null; then
		echo "All record(s) are:"
		grep -i "$rec" "$Phone_Book"
	else
		echo "No records found."
	fi
}

sort_record() {
	if [ ! -f "$Phone_Book" ] || [ ! -s "$Phone_Book" ]; then
		echo "No phone book created or it has no records"
		return
	fi
	sort -t '	' -k2 "$Phone_Book" -o "$Phone_Book"
	echo "Successfully sorted by last name"
}

remove_record() {
	if [ ! -f "$Phone_Book" ] || [ ! -s "$Phone_Book" ]; then
		echo "No phone book created or it has no records"
		return
	fi
	echo -n "Enter name or phone number to be deleted: "
	read rec
	if grep -i "$rec" "$Phone_Book" > /dev/null; then
		grep -iv "$rec" "$Phone_Book" > temp.txt
		mv temp.txt "$Phone_Book"
		echo "Removed successfully"
	else
		echo "No match found"
	fi
}

while true; do
	echo
	echo "=====Phone_Book====="
	echo "1.Add Record"
	echo "2.Search record"
	echo "3.Sort by last name"
	echo "4.Remove record"
	echo "5.Exit"
	echo "==================="
	echo "Enter your choice:"
	read choice
	
	case $choice in
		1) add_entry ;;
		2) search_record ;;
		3) sort_record ;;
		4) remove_record ;;
		5) exit 0 ;;
		*) echo "Enter valid choice" ;;
	esac
done
