#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 100
#define MAX_SEATS 10

typedef struct {
    int bus_number;
    int seats[MAX_SEATS];
} Bus;

typedef struct {
    int bus_number;
    int seat_number;
} Ticket;

Bus buses[MAX_BUSES];
int num_buses = 0;
Ticket tickets[MAX_BUSES * MAX_SEATS];
int num_tickets = 0;

void displayMenu();
void bookTicket();
void checkSeatAvailability();
void cancelTicket();
void modifyTicket();
void ticketHistory();
void displayWelcome();

int main() {
  char choice;

  buses[0].bus_number = 101;
  for (int i = 0; i < MAX_SEATS; i++) {
    buses[0].seats[i] = 0;
  }
  buses[1].bus_number = 102;
  for (int i = 0; i < MAX_SEATS; i++) {
    buses[1].seats[i] = 0;
  }
  num_buses = 2;

  displayWelcome();

  do {
    displayMenu();
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    switch (choice) {
    case 'a':
      bookTicket();
      break;
    case 'b':
      checkSeatAvailability();
      break;
    case 'c':
      cancelTicket();
      break;
    case 'd':
      modifyTicket();
      break;
    case 'e':
      ticketHistory();
      break;
    case 'q':
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 'q');

  return 0;
}

void displayMenu() {
  printf("\n==============================\n");
  printf("What do you want to do?\n");
  printf("a. Ticket Booking\n");
  printf("b. Seat availability\n");
  printf("c. Ticket cancellation\n");
  printf("d. Ticket modification\n");
  printf("e. Ticket History\n");
  printf("q. Quit\n");
  printf("----------------------------\n");
}

void displayWelcome() {
  printf("==============================\n");
  printf("Welcome to the bus reservation system\n");
  printf("==============================\n");

  printf("Available Bus Numbers: ");
  for (int i = 0; i < num_buses; i++) {
    printf("%d ", buses[i].bus_number);
  }
  printf("\n");

  printf("Number of Seats Available:\n");
  for (int i = 0; i < num_buses; i++) {
    printf("Bus %d: %d\n", buses[i].bus_number, MAX_SEATS);
  }
}

void bookTicket() {
  int bus_number, seat_number;
  printf("Enter bus number: ");
  scanf("%d", &bus_number);

  if (bus_number < 101 || bus_number > 102) {
    printf("Invalid bus number.\n");
    return;
  }

  printf("Enter seat number: ");
  scanf("%d", &seat_number);

  if (seat_number < 1 || seat_number > MAX_SEATS) {
    printf("Invalid seat number.\n");
    return;
  }

  if (buses[bus_number - 101].seats[seat_number - 1] == 1) {
    printf("Seat %d is already booked.\n", seat_number);
    return;
  }

  buses[bus_number - 101].seats[seat_number - 1] = 1;
  tickets[num_tickets].bus_number = bus_number;
  tickets[num_tickets].seat_number = seat_number;
  num_tickets++;

  printf("Ticket booked successfully.\n");
}

void checkSeatAvailability() {
  int bus_number;
  printf("Enter bus number: ");
  scanf("%d", &bus_number);

  if (bus_number < 101 || bus_number > 102) {
    printf("Invalid bus number.\n");
    return;
  }

  printf("Bus Number: %d\n", bus_number);
  printf("Seat Availability:\n");
  for (int i = 0; i < MAX_SEATS; i++) {
    printf("Seat %d: %s\n", i + 1,
           buses[bus_number - 101].seats[i] == 0 ? "✔" : "✘");
  }
}

void cancelTicket() {
  int bus_number, seat_number;
  printf("Enter bus number: ");
  scanf("%d", &bus_number);

  if (bus_number < 101 || bus_number > 102) {
    printf("Invalid bus number.\n");
    return;
  }

  printf("Enter seat number: ");
  scanf("%d", &seat_number);

  if (seat_number < 1 || seat_number > MAX_SEATS) {
    printf("Invalid seat number.\n");
    return;
  }

  if (buses[bus_number - 101].seats[seat_number - 1] == 0) {
    printf("Seat %d is not booked.\n", seat_number);
    return;
  }

  buses[bus_number - 101].seats[seat_number - 1] = 0;

  for (int i = 0; i < num_tickets; i++) {
    if (tickets[i].bus_number == bus_number &&
        tickets[i].seat_number == seat_number) {
      for (int j = i; j < num_tickets - 1; j++) {
        tickets[j] = tickets[j + 1];
      }
      num_tickets--;
      break;
    }
  }

  printf("Ticket canceled successfully.\n");
}

void modifyTicket() {
  int bus_number, seat_number, new_seat_number;
  printf("Enter current bus number: ");
  scanf("%d", &bus_number);

  if (bus_number < 101 || bus_number > 102) {
    printf("Invalid bus number.\n");
    return;
  }

  printf("Enter current seat number: ");
  scanf("%d", &seat_number);

  if (seat_number < 1 || seat_number > MAX_SEATS) {
    printf("Invalid seat number.\n");
    return;
  }

  printf("Enter new seat number: ");
  scanf("%d", &new_seat_number);

  if (new_seat_number < 1 || new_seat_number > MAX_SEATS) {
    printf("Invalid new seat number.\n");
    return;
  }

  if (buses[bus_number - 101].seats[seat_number - 1] == 0) {
    printf("Seat %d is not booked.\n", seat_number);
    return;
  }

  if (buses[bus_number - 101].seats[new_seat_number - 1] == 1) {
    printf("Seat %d is already booked.\n", new_seat_number);
    return;
  }

  buses[bus_number - 101].seats[seat_number - 1] = 0;
  buses[bus_number - 101].seats[new_seat_number - 1] = 1;

  for (int i = 0; i < num_tickets; i++) {
    if (tickets[i].bus_number == bus_number &&
        tickets[i].seat_number == seat_number) {
      tickets[i].seat_number = new_seat_number;
      break;
    }
  }

  printf("Ticket modified successfully.\n");
}

void ticketHistory() {
  printf("Ticket History:\n");
  for (int i = 0; i < num_tickets; i++) {
    printf("Ticket %d - Bus: %d, Seat: %d\n", i + 1, tickets[i].bus_number,
           tickets[i].seat_number);
  }
}
