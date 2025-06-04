# HOTEL MANAGEMENT SYSTEM - C LANGUAGE PROJECT
===========================================

# 📌 DESCRIPTION:
This is a simple console-based Hotel Management System developed in C. It simulates room booking, billing, and departmental services like food, room service, and cleaning.

# 🛠️ FEATURES INCLUDED:
---------------------
## 1. Book a Room
## 2. Check Out from a Room
## 3. Kitchen Department (Food Menu, Orders, Food Charges)
## 4. Service Department (Add Service Charges)
## 5. Cleaning Department (Add Cleaning Charges)
## 6. Receptionist Department (Generate Total Bill)
## 7. Display Room Status (Booked / Available)
## 8. Exit System

# 🏨 ROOM TYPES & RATES:
-----------------------
- Single Room: Rs.1000/day
- Double Room: Rs.1500/day
- Suite Room: Rs.2500/day

# 🧾 BILLING COMPONENTS:
----------------------
- Stay Charges (Based on Room Type & Days)
- Service Charges (Manually added)
- Cleaning Charges (Manually added)
- Food Charges (From Kitchen Menu)

# 📦 FILE STRUCTURE:
------------------
- hotel.c (Main source code file)
- README.txt (This help file)

# 🔧 COMPILATION INSTRUCTIONS:
----------------------------
1. Open terminal / command prompt.
2. Compile the code using:
   `gcc hotel.c -o hotel`
3. Run the compiled executable:
   `./hotel` (Linux/Mac) or `hotel.exe` (Windows)

# ✅ SAMPLE OUTPUT OPTIONS:
-------------------------
## Main Menu:
1. Book Room
2. Check Out
3. Kitchen Department
4. Service Department
5. Cleaning Department
6. Receptionist Department (Billing)
7. Display Rooms
8. Exit

## Food Menu:
1. Pizza - Rs.250
2. Burger - Rs.150
3. Thali - Rs.200

# 💡 NOTES:
---------
- You can book only initialized rooms (Default: 5 rooms from 101 to 105).
- Charges can only be applied to booked rooms.
- Billing is cumulative based on department activities.

# 🧑‍💻 AUTHOR:
-----------
Developed by: [Roshan Hiwase]
Language: C
License: Open-source / Educational Use

Happy coding! 🎉
