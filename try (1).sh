#!/bin/bash

ADDRESS_BOOK="$HOME/Desktop/33265/address.txt"

create_address_book() {
    if [ ! -f "$ADDRESS_BOOK" ]; then
        touch "$ADDRESS_BOOK"
        echo "Address book created."
    else 
        echo "Address book already present."
    fi
}

view_address_book() {
    if [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not present."
    else
        echo "The data in address book is:"
        nl -w2 -s'. ' "$ADDRESS_BOOK" | column -t -s '|'
    fi
}

insert_record() {
    echo "Enter Name:"
    read name

    echo "Enter Email:"
    read email

    echo "Enter Phone Number:"
    read phone

    echo "Enter Location:"
    read location

    if [ -z "$name" ] || [ -z "$email" ] || [ -z "$phone" ] || [ -z "$location" ]; then
        echo "Invalid input. All fields are required."
    else 
        echo "${name}|${email}|${phone}|${location}" >> "$ADDRESS_BOOK"
        echo "Record inserted successfully."
    fi
}

delete_record() {
    if [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not present."
        return
    fi

    view_address_book
    echo -n "Enter the record number to delete: "
    read num

    total=$(wc -l < "$ADDRESS_BOOK")
    if ! [[ "$num" =~ ^[0-9]+$ ]] || [ "$num" -lt 1 ] || [ "$num" -gt "$total" ]; then
        echo "Invalid record number."
        return
    fi

    sed -i "${num}d" "$ADDRESS_BOOK"
    echo "Record deleted successfully."
}

modify_record() {
    if [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty or not present."
        return
    fi

    view_address_book
    echo -n "Enter the record number to modify: "
    read num

    total=$(wc -l < "$ADDRESS_BOOK")
    if ! [[ "$num" =~ ^[0-9]+$ ]] || [ "$num" -lt 1 ] || [ "$num" -gt "$total" ]; then
        echo "Invalid record number."
        return
    fi

    old_record=$(sed -n "${num}p" "$ADDRESS_BOOK")
    IFS='|' read -r old_name old_email old_phone old_location <<< "$old_record"

    echo "Leave field empty to keep existing value."

    echo -n "Enter new Name (old: $old_name): "
    read name
    name=${name:-$old_name}

    echo -n "Enter new Email (old: $old_email): "
    read email
    email=${email:-$old_email}

    echo -n "Enter new Phone Number (old: $old_phone): "
    read phone
    phone=${phone:-$old_phone}

    echo -n "Enter new Location (old: $old_location): "
    read location
    location=${location:-$old_location}

    sed -i "${num}s/.*/${name}|${email}|${phone}|${location}/" "$ADDRESS_BOOK"
    echo "Record modified successfully."
}

# Main menu loop
while true; do
    echo
    echo "===== Address Book Menu ====="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo -n "Enter your choice: "
    read ch

    case $ch in
        1) create_address_book ;;
        2) view_address_book ;;
        3) insert_record ;;
        4) delete_record ;;
        5) modify_record ;;
        6) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice. Try again." ;;
    esac
done

