#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 100

struct Room {
    int roomNo;
    char type[20];
    int isAvailable;
    char guestName[50];
    int daysStayed;
    int serviceCharges;
    int cleaningCharges;
    int foodCharges;
};

struct Room rooms[MAX_ROOMS];
int roomCount = 0;

// Initialize rooms
void initRooms() {
    roomCount = 5;
    for (int i = 0; i < roomCount; i++) {
        rooms[i].roomNo = 101 + i;
        if (i % 3 == 0) strcpy(rooms[i].type, "Single");
        else if (i % 3 == 1) strcpy(rooms[i].type, "Double");
        else strcpy(rooms[i].type, "Suite");

        rooms[i].isAvailable = 1;
        rooms[i].serviceCharges = 0;
        rooms[i].cleaningCharges = 0;
        rooms[i].foodCharges = 0;
        strcpy(rooms[i].guestName, "");
        rooms[i].daysStayed = 0;
    }
}

// Book a room
void bookRoom() {
    int roomNo;
    char guest[50];
    int days;

    printf("\n========== Available Rooms ==========\n");
    printf("Room\tType\tPrice per Day\n");
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].isAvailable) {
            int price = 0;
            if (strcmp(rooms[i].type, "Single") == 0) price = 1000;
            else if (strcmp(rooms[i].type, "Double") == 0) price = 1500;
            else price = 2500;
            printf("%d\t%s\tRs.%d\n", rooms[i].roomNo, rooms[i].type, price);
        }
    }

    printf("\nEnter room number to book: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (!rooms[i].isAvailable) {
                printf("⚠️  Room %d is already booked.\n", roomNo);
                return;
            }

            getchar();
            printf("Enter guest name: ");
            fgets(guest, sizeof(guest), stdin);
            guest[strcspn(guest, "\n")] = 0;

            printf("Enter number of days: ");
            scanf("%d", &days);

            rooms[i].isAvailable = 0;
            strcpy(rooms[i].guestName, guest);
            rooms[i].daysStayed = days;
            rooms[i].serviceCharges = 0;
            rooms[i].cleaningCharges = 0;
            rooms[i].foodCharges = 0;

            printf("\n✅ Room %d successfully booked for %s.\n", roomNo, guest);
            return;
        }
    }
    printf("❌ Error: Room number %d not found.\n", roomNo);
}

// Check-out guest
void checkOut() {
    int roomNo;
    printf("\n========== Check Out Guest ==========\n");
    printf("Enter room number to check out: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("⚠️  Room %d is already available.\n", roomNo);
                return;
            }

            rooms[i].isAvailable = 1;
            strcpy(rooms[i].guestName, "");
            rooms[i].daysStayed = 0;
            rooms[i].serviceCharges = 0;
            rooms[i].cleaningCharges = 0;
            rooms[i].foodCharges = 0;
            printf("✅ Guest has checked out. Room %d is now available.\n", roomNo);
            return;
        }
    }
    printf("❌ Error: Room number %d not found.\n", roomNo);
}

// Kitchen department
void kitchenMenu() {
    int choice, roomNo;
    do {
        printf("\n========== Kitchen Department ==========\n");
        printf("1. View Food Menu\n2. Order Food\n3. Food Info\n4. Back\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n🍽️  Menu:\n1. Pizza - Rs.250\n2. Burger - Rs.150\n3. Thali - Rs.200\n");
                break;
            case 2: {
                printf("Enter room number: ");
                scanf("%d", &roomNo);
                int found = 0;

                for (int i = 0; i < roomCount; i++) {
                    if (rooms[i].roomNo == roomNo && !rooms[i].isAvailable) {
                        found = 1;
                        int foodChoice, quantity, cost = 0;
                        printf("Select item (1.Pizza 2.Burger 3.Thali): ");
                        scanf("%d", &foodChoice);
                        printf("Enter quantity: ");
                        scanf("%d", &quantity);

                        if (foodChoice == 1) cost = 250 * quantity;
                        else if (foodChoice == 2) cost = 150 * quantity;
                        else if (foodChoice == 3) cost = 200 * quantity;
                        else {
                            printf("❌ Invalid food choice.\n");
                            break;
                        }

                        rooms[i].foodCharges += cost;
                        printf("✅ Order placed. Rs.%d added to room %d.\n", cost, roomNo);
                        break;
                    }
                }
                if (!found)
                    printf("❌ Invalid or unbooked room number.\n");
                break;
            }
            case 3:
                printf("ℹ️  Food charges are included in the final billing.\n");
                break;
            case 4:
                return;
            default:
                printf("❌ Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}

// Add service charge
void serviceMenu() {
    int roomNo, charge;
    printf("\n========== Service Department ==========\n");
    printf("Enter room number: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("⚠️  Room not booked. Cannot add charges.\n");
                return;
            }
            printf("Enter service charge: ");
            scanf("%d", &charge);
            rooms[i].serviceCharges += charge;
            printf("✅ Rs.%d added to room %d.\n", charge, roomNo);
            return;
        }
    }
    printf("❌ Invalid room number.\n");
}

// Add cleaning charge
void cleanerMenu() {
    int roomNo, charge;
    printf("\n========== Cleaning Department ==========\n");
    printf("Enter room number: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("⚠️  Room not booked. Cannot add charges.\n");
                return;
            }
            printf("Enter cleaning charge: ");
            scanf("%d", &charge);
            rooms[i].cleaningCharges += charge;
            printf("✅ Rs.%d cleaning charge added to room %d.\n", charge, roomNo);
            return;
        }
    }
    printf("❌ Invalid room number.\n");
}

// Final billing
void addBilling() {
    int roomNo;
    printf("\n========== Receptionist Billing ==========\n");
    printf("Enter room number: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("⚠️  Room not booked.\n");
                return;
            }

            int rate = 0;
            if (strcmp(rooms[i].type, "Single") == 0) rate = 1000;
            else if (strcmp(rooms[i].type, "Double") == 0) rate = 1500;
            else rate = 2500;

            int stayCost = rate * rooms[i].daysStayed;
            int total = stayCost + rooms[i].serviceCharges + rooms[i].cleaningCharges + rooms[i].foodCharges;

            printf("\n--- Bill for Room %d ---\n", roomNo);
            printf("Guest: %s\n", rooms[i].guestName);
            printf("Stay (%d days x Rs.%d): Rs.%d\n", rooms[i].daysStayed, rate, stayCost);
            printf("Service Charges: Rs.%d\n", rooms[i].serviceCharges);
            printf("Cleaning Charges: Rs.%d\n", rooms[i].cleaningCharges);
            printf("Food Charges: Rs.%d\n", rooms[i].foodCharges);
            printf("👉 Total Amount: Rs.%d\n", total);
            return;
        }
    }
    printf("❌ Invalid room number.\n");
}

// Display all rooms
void displayRooms() {
    printf("\n========== Room Status ==========\n");
    printf("Room\tType\tStatus\t\tGuest\n");
    for (int i = 0; i < roomCount; i++) {
        printf("%d\t%s\t%s\t%s\n", rooms[i].roomNo, rooms[i].type,
               rooms[i].isAvailable ? "Available" : "Booked",
               rooms[i].isAvailable ? "-" : rooms[i].guestName);
    }
}

// Main menu
int main() {
    int choice;
    initRooms();

    do {
        printf("\n========== Welcome to Roshan's Hotel ==========\n");
        printf("1. Book Room\n2. Check Out\n3. Kitchen Dept\n4. Service Dept\n5. Cleaning Dept\n6. Billing\n7. Show Rooms\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookRoom(); break;
            case 2: checkOut(); break;
            case 3: kitchenMenu(); break;
            case 4: serviceMenu(); break;
            case 5: cleanerMenu(); break;
            case 6: addBilling(); break;
            case 7: displayRooms(); break;
            case 8: printf("\n🙏 Thank you for using Roshan's Hotel Management System. Goodbye!\n"); break;
            default: printf("❌ Invalid choice. Try again.\n");
        }
    } while (choice != 8);

    return 0;
}
