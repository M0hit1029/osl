#!/bin/bash

ADDRESS_BOOK="addressbook.txt"

# --- Function to Add an Entry ---
add_entry() {
    echo -n "Enter ID: "
    read id
    echo -n "Enter Name: "
    read name
    echo -n "Enter Phone: "
    read phone
    echo -n "Enter Email: "
    read email

    if [ -z "$id" ] || [ -z "$name" ] || [ -z "$phone" ] || [ -z "$email" ]; then
        echo "All fields are required!"
    else
        echo "${id}:${name}:${phone}:${email}" >> "$ADDRESS_BOOK"
        echo "Record added successfully!"
    fi
}

# --- Function to Display All Records ---
display_records() {
    if [ ! -f "$ADDRESS_BOOK" ] || [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not created yet."
        return
    fi

    echo "========== ADDRESS BOOK =========="
    echo "ID : NAME : PHONE : EMAIL"
    echo "----------------------------------"
    cat "$ADDRESS_BOOK"
    echo "----------------------------------"
}

# --- Function to Search for a Record ---
search_entry() {
    if [ ! -f "$ADDRESS_BOOK" ] || [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not created yet."
        return
    fi

    echo -n "Enter keyword to search (ID/Name/Phone/Email): "
    read keyword

    if grep -i "$keyword" "$ADDRESS_BOOK" > /dev/null; then
        echo "Matching record(s):"
        grep -i "$keyword" "$ADDRESS_BOOK"
    else
        echo "No record found matching '$keyword'."
    fi
}

# --- Function to Remove a Record ---
remove_entry() {
    if [ ! -f "$ADDRESS_BOOK" ] || [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not created yet."
        return
    fi

    echo -n "Enter keyword (ID/Name/Phone/Email) to remove: "
    read keyword

    if grep -i "$keyword" "$ADDRESS_BOOK" > /dev/null; then
        grep -iv "$keyword" "$ADDRESS_BOOK" > temp.txt
        mv temp.txt "$ADDRESS_BOOK"
        echo "Record(s) removed successfully!"
    else
        echo "No matching record found."
    fi
}

# --- Function to Edit a Record ---
edit_entry() {
    if [ ! -f "$ADDRESS_BOOK" ] || [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not created yet."
        return
    fi

    echo -n "Enter keyword (ID/Name/Phone/Email) to edit: "
    read keyword

    match=$(grep -i "$keyword" "$ADDRESS_BOOK")

    if [ -z "$match" ]; then
        echo "No record found to edit."
        return
    fi

    echo "Record found:"
    echo "$match"
    echo "----------------------------------"
    echo -n "Enter new ID: "
    read new_id
    echo -n "Enter new Name: "
    read new_name
    echo -n "Enter new Phone: "
    read new_phone
    echo -n "Enter new Email: "
    read new_email

    new_record="${new_id}:${new_name}:${new_phone}:${new_email}"

    # Replace old record with new one
    grep -iv "$keyword" "$ADDRESS_BOOK" > temp.txt
    echo "$new_record" >> temp.txt
    mv temp.txt "$ADDRESS_BOOK"

    echo "Record updated successfully!"
}

# --- Main Menu Loop ---
while true; do
    echo
    echo "========= ADDRESS BOOK MENU ========="
    echo "1. Display all records"
    echo "2. Search address book"
    echo "3. Add new entry"
    echo "4. Remove an entry"
    echo "5. Edit an entry"
    echo "6. Quit"
    echo "====================================="
    echo -n "Enter your choice: "
    read choice

    case $choice in
        1) display_records ;;
        2) search_entry ;;
        3) add_entry ;;
        4) remove_entry ;;
        5) edit_entry ;;
        6) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice! Please try again." ;;
    esac
done

