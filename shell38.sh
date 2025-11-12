#!/bin/bash

echo "Welcome to Address Book 📒"
echo -n "Enter file name to store records: "
read fname
touch "$fname"
echo -e "Phone\tName\tAddress" > "$fname"

choice=0
while [ $choice -ne 6 ]
do
    echo -e "\nChoose one of the following"
    echo "1. Create a New Address Book"
    echo "2. Insert new Record"
    echo "3. Modify a Record"
    echo "4. Delete a Record"
    echo "5. View Records"
    echo "6. Exit"
    echo -n "Enter Choice : "
    read choice

    case $choice in
        1)
            echo -n "Enter Phone Number of person: "
            read phone
            echo -n "Enter Name of person: "
            read name
            echo -n "Enter Address of person: "
            read address
            echo -e "$phone\t$name\t$address" >> "$fname"
            echo "Record added."
            ;;

        2)
            echo -n "Enter Phone Number: "
            read phone
            echo -n "Enter Name: "
            read name
            echo -n "Enter Address: "
            read address
            echo -e "$phone\t$name\t$address" >> "$fname"
            echo "Record inserted."
            ;;

        3)
            echo -n "Enter Phone Number to modify: "
            read phone
            if grep -wq "$phone" "$fname"
            then
                head -n 1 "$fname" > temp
                grep -vw "$phone" "$fname" | tail -n +2 >> temp
                mv temp "$fname"
                echo -n "Enter new Phone Number: "
                read new_phone
                echo -n "Enter new Name: "
                read name
                echo -n "Enter new Address: "
                read address
                echo -e "$new_phone\t$name\t$address" >> "$fname"
                echo "Record modified."
            else
                echo "Record not found."
            fi
            ;;

        4)
            echo -n "Enter Phone Number to delete: "
            read phone
            if grep -wq "$phone" "$fname"
            then
                head -n 1 "$fname" > temp
                grep -vw "$phone" "$fname" | tail -n +2 >> temp
                mv temp "$fname"
                echo "Record deleted."
            else
                echo "Record not found."
            fi
            ;;

        5)
            echo -e "\n--- Address Book Records ---"
            column -t "$fname"
            ;;

        6)
            echo "Exiting Address Book. Goodbye!"
            ;;

        *)
            echo "Invalid choice! Try again."
            ;;
    esac
done



// run command :chmod +x filename.sh     //
   //      ./filename.sh            //
