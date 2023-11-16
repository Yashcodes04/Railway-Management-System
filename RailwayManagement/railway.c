#include <stdio.h>
#include <string.h>

#define MAX_SEATS 50
#define MAX_QUEUE 50
int seat_number=1;
int front = 0;
int rear = -1;

struct Reservation {
    char passenger_name[50];
    int seat_number;
    int is_reserved;
};

struct Reservation train[MAX_SEATS];
struct Reservation queue[MAX_QUEUE];

void initializeTrain() {
    for (int i = 0; i < MAX_SEATS; i++) {
        train[i].is_reserved = 0;
    }
}

void enqueue(struct Reservation passenger) {
    if(rear == MAX_QUEUE - 1) {
        printf("Waiting queue is full.\n");
    } else {
        queue[++rear] = passenger;
    }
}

struct Reservation dequeue() {
    if(front > rear) {
        printf("Waiting queue is empty.\n");
        struct Reservation empty;
        strcpy(empty.passenger_name, "");
        empty.seat_number = -1;
        empty.is_reserved = 0;
        return empty;
    } else {
        return queue[front++];
    }
}

int checkSeatAvailability(int seat_number) {
    if (seat_number >= 0 && seat_number <= MAX_SEATS) {
        if (train[seat_number].is_reserved == 0) {
            return 1; // Seat is available
        } else {
            return 0; // Seat is already reserved
        }
    } else {
        return -1; // Invalid seat number
    }
}

void reserveSeat() {
    char name[50];
    printf("Enter passenger name: ");
    scanf("%s", name);

    int availability = checkSeatAvailability(seat_number-1);

    if (availability == 1) {
        strcpy(train[seat_number - 1].passenger_name, name);
        train[seat_number - 1].seat_number = seat_number;
        train[seat_number - 1 ].is_reserved = 1;
        printf("Seat %d reserved for %s successfully.\n", seat_number, name);
        seat_number++;
    } else if (availability == 0) {
        printf("Seat %d is already reserved.\n", seat_number);
        struct Reservation passenger;
        strcpy(passenger.passenger_name, name);
        passenger.seat_number = seat_number;
        passenger.is_reserved = 0;
        enqueue(passenger);
    } else {
        printf("Invalid seat number. Please choose a seat between 1 and %d.\n", MAX_SEATS);
    }
}

void displayTrainStatus() {
    printf("Train Seat Reservation Status:\n");
    printf("--------------------------------\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (train[i].is_reserved) {
            printf("Seat %d: %s\n", train[i].seat_number, train[i].passenger_name);
        }
        else {
            printf("Seat %d: Not reserved\n", i + 1);
        }
    }
    printf("--------------------------------\n");
}

void CancelReserv()
{   int num;
    printf("Enter your reserved seat number: ");
    scanf("%d",&num);
    if(train[num-1].is_reserved == 0)
        printf("The seat is not a reserved seat \n Please Enter a valid SEAT");
    else
    {
        printf("Reservation Cancelled");
        train[num-1].is_reserved = 0;
        if(front <= rear) {
            struct Reservation passenger = dequeue();
            strcpy(train[num-1].passenger_name, passenger.passenger_name);
            train[num-1].seat_number = num;
            train[num-1].is_reserved = 1;
            printf("Seat %d reserved for %s from waiting queue.\n", num, passenger.passenger_name);
        }
    }
}
int main() {
    int choice;

    initializeTrain();

    do {
        printf("\nRailway Reservation System\n");
        printf("1. Reserve a seat\n");
        printf("2. Display train status\n");
        printf("3. Exit\n");
        printf("4. Reservation Cancelation\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                reserveSeat();
                break;
            case 2:
                displayTrainStatus();
                break;
            case 3:
                printf("Exiting program. Have a nice day!\n");
                break;
            case 4: 
                CancelReserv();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}