#!/bin/bash

ADDRESS_BOOK="/home/vrishabh-patni/Desktop/address.txt"

# Function to add an entry
add_entry() {
    echo -n "Enter ID: "
    read id
    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone: "
    read phone

    if [ -z "$id" ] || [ -z "$name" ] || [ -z "$phone" ]; then
        echo "All fields are required!"
    else
        echo "${id};${name};${phone}" >> "$ADDRESS_BOOK"
        echo "Record added successfully."
    fi
}

# Function to search for a record (by ID, Name, or Phone)
search_entry() {
    echo -n "Enter keyword to search (ID/Name/Phone): "
    read keyword

    if grep -i "$keyword" "$ADDRESS_BOOK" > /dev/null; then
        echo "Matching record(s):"
        grep -i "$keyword" "$ADDRESS_BOOK"
    else
        echo "No matching record found."
    fi
}

# Function to remove a record (by ID, Name, or Phone)
remove_entry() {
    echo -n "Enter keyword to remove (ID/Name/Phone): "
    read keyword

    if grep -i "$keyword" "$ADDRESS_BOOK" > /dev/null; then
        grep -iv "$keyword" "$ADDRESS_BOOK" > temp.txt
        mv temp.txt "$ADDRESS_BOOK"
        echo "Record(s) matching '$keyword' removed successfully."
    else
        echo "No record found for '$keyword'."
    fi
}

# Main menu
while true; do
    echo
    echo "===== ADDRESS BOOK MENU ====="
    echo "1. Search Address Book"
    echo "2. Add an Address Book Entry"
    echo "3. Remove an Address Book Entry"
    echo "4. Quit"
    echo "=============================="
    echo -n "Enter your choice: "
    read choice

    case $choice in
        1) search_entry ;;
        2) add_entry ;;
        3) remove_entry ;;
        4) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done

