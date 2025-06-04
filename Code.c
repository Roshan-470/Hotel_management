#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 100

struct Room {
    int roomNo;
    char type[20];
    int isAvailable; // 1 means available, 0 means booked
    char guestName[50];
    char checkInDate[20];
    char checkOutDate[20];
    int daysStayed;
    int serviceCharges;
    int cleaningCharges;
    int foodCharges;   // New field for food charges
};

struct Room rooms[MAX_ROOMS];
int roomCount = 0;

// Initialize some rooms (for demo)
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
        strcpy(rooms[i].checkInDate, "");
        strcpy(rooms[i].checkOutDate, "");
        rooms[i].daysStayed = 0;
    }
}

// Book a room
void bookRoom() {
    int roomNo;
    char guest[50], checkIn[20], checkOut[20];
    int days;

    printf("Enter room number to book: ");
    scanf("%d", &roomNo);

    // Find room
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (!rooms[i].isAvailable) {
                printf("Room %d is already booked.\n", roomNo);
                return;
            }
            printf("Enter guest name: ");
            getchar(); // to clear newline
            fgets(guest, sizeof(guest), stdin);
            guest[strcspn(guest, "\n")] = 0;  // Remove newline

            printf("Enter check-in date (dd/mm/yyyy): ");
            fgets(checkIn, sizeof(checkIn), stdin);
            checkIn[strcspn(checkIn, "\n")] = 0;

            printf("Enter check-out date (dd/mm/yyyy): ");
            fgets(checkOut, sizeof(checkOut), stdin);
            checkOut[strcspn(checkOut, "\n")] = 0;

            printf("Enter number of days: ");
            scanf("%d", &days);

            rooms[i].isAvailable = 0;
            strcpy(rooms[i].guestName, guest);
            strcpy(rooms[i].checkInDate, checkIn);
            strcpy(rooms[i].checkOutDate, checkOut);
            rooms[i].daysStayed = days;
            rooms[i].serviceCharges = 0;
            rooms[i].cleaningCharges = 0;
            rooms[i].foodCharges = 0;

            printf("Room %d successfully booked for %s.\n", roomNo, guest);
            return;
        }
    }
    printf("Room number %d not found.\n", roomNo);
}

// Check out and free room
void checkOut() {
    int roomNo;
    printf("Enter room number to check out: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("Room %d is already available.\n", roomNo);
                return;
            }
            rooms[i].isAvailable = 1;
            strcpy(rooms[i].guestName, "");
            strcpy(rooms[i].checkInDate, "");
            strcpy(rooms[i].checkOutDate, "");
            rooms[i].daysStayed = 0;
            rooms[i].serviceCharges = 0;
            rooms[i].cleaningCharges = 0;
            rooms[i].foodCharges = 0;
            printf("Room %d is now available.\n", roomNo);
            return;
        }
    }
    printf("Room number %d not found.\n", roomNo);
}

// Kitchen department - add food charges
void kitchenMenu() {
    int choice, roomNo;
    do {
        printf("\n--- Kitchen Department ---\n");
        printf("1. View Food Menu\n2. Order Food\n3. Food Payment Info\n4. Back to Main Menu\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Menu: Pizza - Rs.250, Burger - Rs.150, Thali - Rs.200\n");
                break;
            case 2: {
                printf("Enter room number for food order: ");
                scanf("%d", &roomNo);

                int found = 0;
                for (int i = 0; i < roomCount; i++) {
                    if (rooms[i].roomNo == roomNo && !rooms[i].isAvailable) {
                        found = 1;
                        int foodChoice, quantity;
                        printf("Select Food:\n1. Pizza (Rs.250)\n2. Burger (Rs.150)\n3. Thali (Rs.200)\nEnter choice: ");
                        scanf("%d", &foodChoice);
                        printf("Enter quantity: ");
                        scanf("%d", &quantity);

                        int cost = 0;
                        switch (foodChoice) {
                            case 1: cost = 250 * quantity; break;
                            case 2: cost = 150 * quantity; break;
                            case 3: cost = 200 * quantity; break;
                            default:
                                printf("Invalid food choice.\n");
                                continue;
                        }

                        rooms[i].foodCharges += cost;
                        printf("Food order placed. Rs.%d added to room %d bill.\n", cost, roomNo);
                        break;
                    }
                }
                if (!found) {
                    printf("Invalid or unbooked room number.\n");
                }
                break;
            }
            case 3:
                printf("Food payment is included in the total billing at Receptionist Department.\n");
                break;
            case 4:
                return;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

// Service department charges
void serviceMenu() {
    int roomNo, charge;
    printf("Enter room number to add service charges: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("Room %d is not booked currently. Cannot add service charges.\n", roomNo);
                return;
            }
            printf("Enter service charge amount: ");
            scanf("%d", &charge);
            rooms[i].serviceCharges += charge;
            printf("Service charges of Rs.%d added to room %d.\n", charge, roomNo);
            return;
        }
    }
    printf("Invalid room number.\n");
}

// Cleaning department charges
void cleanerMenu() {
    int roomNo, charge;
    printf("Enter room number to add cleaning charges: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("Room %d is not booked currently. Cannot add cleaning charges.\n", roomNo);
                return;
            }
            printf("Enter cleaning charge amount: ");
            scanf("%d", &charge);
            rooms[i].cleaningCharges += charge;
            printf("Cleaning charges of Rs.%d added to room %d.\n", charge, roomNo);
            return;
        }
    }
    printf("Invalid room number.\n");
}

// Receptionist department - billing including all charges
void addBilling() {
    int roomNo;
    printf("Enter room number for billing: ");
    scanf("%d", &roomNo);

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) {
            if (rooms[i].isAvailable) {
                printf("Room %d is currently not booked.\n", roomNo);
                return;
            }

            int roomRate = 0;
            if (strcmp(rooms[i].type, "Single") == 0) roomRate = 1000;
            else if (strcmp(rooms[i].type, "Double") == 0) roomRate = 1500;
            else roomRate = 2500;

            int stayCost = roomRate * rooms[i].daysStayed;
            int total = stayCost + rooms[i].serviceCharges + rooms[i].cleaningCharges + rooms[i].foodCharges;

            printf("\n--- Billing Details for Room %d ---\n", roomNo);
            printf("Guest Name: %s\n", rooms[i].guestName);
            printf("Stay Charges (%d days @ Rs.%d per day): Rs.%d\n", rooms[i].daysStayed, roomRate, stayCost);
            printf("Service Charges: Rs.%d\n", rooms[i].serviceCharges);
            printf("Cleaning Charges: Rs.%d\n", rooms[i].cleaningCharges);
            printf("Food Charges: Rs.%d\n", rooms[i].foodCharges);
            printf("Total Bill Amount: Rs.%d\n\n", total);

            return;
        }
    }
    printf("Invalid room number.\n");
}

// Display room details
void displayRooms() {
    printf("\nRoom No\tType\tAvailability\tGuest Name\n");
    for (int i = 0; i < roomCount; i++) {
        printf("%d\t%s\t%s\t%s\n", rooms[i].roomNo, rooms[i].type,
               rooms[i].isAvailable ? "Available" : "Booked",
               rooms[i].isAvailable ? "-" : rooms[i].guestName);
    }
}

int main() {
    int choice;
    initRooms();

    do {
        printf("\n--- Hotel Management System ---\n");
        printf("1. Book Room\n");
        printf("2. Check Out\n");
        printf("3. Kitchen Department\n");
        printf("4. Service Department\n");
        printf("5. Cleaning Department\n");
        printf("6. Receptionist Department (Billing)\n");
        printf("7. Display Rooms\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                checkOut();
                break;
            case 3:
                kitchenMenu();
                break;
            case 4:
                serviceMenu();
                break;
            case 5:
                cleanerMenu();
                break;
            case 6:
                addBilling();
                break;
            case 7:
                displayRooms();
                break;
            case 8:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
