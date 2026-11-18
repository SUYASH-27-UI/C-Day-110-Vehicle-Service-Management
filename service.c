
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Service {
    int id;
    char customer[50];
    char vehicle[50];
    char problem[100];
    char status[20];
};

struct Service services[MAX];
int count = 0;

void loadServices() {
    FILE *fp = fopen("services.txt", "r");

    if (fp == NULL)
        return;

    while (count < MAX &&
           fscanf(fp, "%d %49s %49s %99s %19s",
                  &services[count].id,
                  services[count].customer,
                  services[count].vehicle,
                  services[count].problem,
                  services[count].status) == 5) {
        count++;
    }

    fclose(fp);
}

void saveServices() {
    FILE *fp = fopen("services.txt", "w");

    if (fp == NULL) {
        printf("Unable to save records!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %s %s\n",
                services[i].id,
                services[i].customer,
                services[i].vehicle,
                services[i].problem,
                services[i].status);
    }

    fclose(fp);
}

void addService() {
    if (count >= MAX) {
        printf("Service record limit reached!\n");
        return;
    }

    struct Service s;
    int maxID = 0;

    for (int i = 0; i < count; i++) {
        if (services[i].id > maxID)
            maxID = services[i].id;
    }

    s.id = maxID + 1;

    printf("Enter customer name (one word): ");
    scanf("%49s", s.customer);

    printf("Enter vehicle name (one word): ");
    scanf("%49s", s.vehicle);

    printf("Enter problem (one word): ");
    scanf("%99s", s.problem);

    strcpy(s.status, "Pending");

    services[count] = s;
    count++;

    saveServices();

    printf("Service registered! ID: %d\n", s.id);
}

void viewServices() {
    if (count == 0) {
        printf("No service records found.\n");
        return;
    }

    printf("\n===== SERVICE RECORDS =====\n");

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", services[i].id);
        printf("Customer: %s\n", services[i].customer);
        printf("Vehicle: %s\n", services[i].vehicle);
        printf("Problem: %s\n", services[i].problem);
        printf("Status: %s\n", services[i].status);
    }
}

void searchService() {
    int id, found = 0;

    printf("Enter service ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (services[i].id == id) {
            printf("\nCustomer: %s\n", services[i].customer);
            printf("Vehicle: %s\n", services[i].vehicle);
            printf("Problem: %s\n", services[i].problem);
            printf("Status: %s\n", services[i].status);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Service record not found.\n");
}

void updateStatus() {
    int id, choice, found = 0;

    printf("Enter service ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (services[i].id == id) {
            printf("1. Pending\n");
            printf("2. In Progress\n");
            printf("3. Completed\n");
            printf("Choose status: ");

            if (scanf("%d", &choice) != 1) {
                printf("Invalid choice!\n");
                return;
            }

            switch (choice) {
                case 1:
                    strcpy(services[i].status, "Pending");
                    break;
                case 2:
                    strcpy(services[i].status, "Progress");
                    break;
                case 3:
                    strcpy(services[i].status, "Completed");
                    break;
                default:
                    printf("Invalid choice!\n");
                    return;
            }

            saveServices();
            printf("Service status updated!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Service record not found.\n");
}

int main() {
    int choice;

    loadServices();

    do {
        printf("\n===== VEHICLE SERVICE CENTER =====\n");
        printf("1. Add Service\n");
        printf("2. View All Services\n");
        printf("3. Search Service\n");
        printf("4. Update Service Status\n");
        printf("5. Total Services\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addService();
                break;
            case 2:
                viewServices();
                break;
            case 3:
                searchService();
                break;
            case 4:
                updateStatus();
                break;
            case 5:
                printf("Total Services: %d\n", count);
                break;
            case 6:
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}
