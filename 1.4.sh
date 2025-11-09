#!/bin/bash

# --- Function to test if a file exists ---
test_file() {
    echo -n "Enter the file name to test: "
    read fname

    if [ -f "$fname" ]; then
        echo "✅ File '$fname' exists."
    else
        echo "❌ File '$fname' does not exist."
    fi
}

# --- Function to read (display) a file ---
read_file() {
    echo -n "Enter the file name to read: "
    read fname

    if [ -f "$fname" ]; then
        echo "====== Contents of '$fname' ======"
        cat "$fname"
        echo "=================================="
    else
        echo "❌ File '$fname' not found."
    fi
}

# --- Function to delete a file ---
delete_file() {
    echo -n "Enter the file name to delete: "
    read fname

    if [ -f "$fname" ]; then
        rm "$fname"
        echo "🗑️  File '$fname' deleted successfully."
    else
        echo "❌ File '$fname' does not exist."
    fi
}

# --- Function to display all files in current directory ---
list_files() {
    echo "📂 Files in current directory:"
    ls -1
}

# --- Main menu ---
while true; do
    echo
    echo "========= FILE MANAGEMENT MENU ========="
    echo "1. Test if file exists"
    echo "2. Read a file"
    echo "3. Delete a file"
    echo "4. Display list of files"
    echo "5. Exit"
    echo "========================================"
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

