#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

// Function Prototypes
void menu(void);
void password(void);
void namefun(void);
void searchfun(void);
void listfun(void);
void modifyfun(void);
void deletefun(void);
void exitfun(void);

int main() {
    system("color C");//color test
    password();
    getch();
    return 0;
}

void namefun() {
    system("cls");
    printf("NEW SECTION\n");

    FILE *fptr;
    char name[100];
    char address[100];
    char gmail[100];
    double phone;
    char gender[8];

    fptr = fopen("shakil.txt", "ab+");//open file
    if (fptr == NULL) {
        printf("Failed to create the required file.");
        return;
    }

    printf("Name:\t");
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Address:\t");
    fgets(address, 100, stdin);
    address[strcspn(address, "\n")] = '\0';

    printf("Gender:\t");
    fgets(gender, 8, stdin);
    gender[strcspn(gender, "\n")] = '\0';

    printf("Gmail:\t");
    fgets(gmail, 100, stdin);
    gmail[strcspn(gmail, "\n")] = '\0';

    printf("Phone Number:\t");
    scanf("%lf", &phone);
    getchar(); // to consume the newline character after scanf

    fprintf(fptr, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
    fclose(fptr);

    char ch;
    printf("Do you want to add more data? Press y for yes: ");
    Sleep(1000);
    fflush(stdin);
    while ((ch = getch()) == 'y') {
        namefun();
    }
    menu();
}

void searchfun() {
    FILE *fptr;
    int flag = 0;
    char name[100];
    char address[100];
    char gmail[100];
    double phone;
    char gender[8];
    char name1[100];

    system("cls");
    fflush(stdin);
    printf("Enter the name of the person you want to see the detail: ");
    fgets(name1, 100, stdin);
    name1[strcspn(name1, "\n")] = '\0';

    fptr = fopen("shakil.txt", "r");
    if (fptr == NULL) {
        printf("Failed to open file.");
        return;
    }

    while (fscanf(fptr, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        if (strcmp(name, name1) == 0) {
            printf("Record Found\n");
            printf("----------------------------------------\n");
            printf("Name: %s\n", name);
            printf("Address: %s\n", address);
            printf("Gender: %s\n", gender);
            printf("Gmail: %s\n", gmail);
            printf("Phone Number: %.0lf\n", phone);
            printf("----------------------------------------\n");
            flag = 1;
            Sleep(1000);
            printf("Enter y for menu option: ");
            if (getch() == 'y') {
                menu();
            }
            break;
        }
    }

    if (flag == 0) {
        system("cls");
        printf("No record found.\n");
        printf("Enter 'a' to search again or 'y' to open the menu section: ");
        if (getch() == 'a') {
            searchfun();
        } else {
            menu();
        }
    }
    fclose(fptr);
}

void listfun() {
    FILE *fptr;
    char name[100], address[100], gmail[100], gender[8];
    double phone;

    fptr = fopen("ebraj.txt", "r");
    if (fptr == NULL) {
        printf("Failed to open file.");
        return;
    }

    system("cls");
    printf("LIST SECTION OPENED\n");
    printf("\n");
    while (fscanf(fptr, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        printf("------------------------------------------\n");
        printf("Name: %s\n", name);
        printf("Address: %s\n", address);
        printf("Gender: %s\n", gender);
        printf("Gmail: %s\n", gmail);
        printf("Phone: %.0lf\n", phone);
        printf("------------------------------------------\n\n");
    }
    Sleep(1000);
    printf("Enter 'y' for the menu section: ");
    if (getch() == 'y') {
        menu();
    }
    fclose(fptr);
}

void modifyfun() {
    FILE *fptr, *fptr1;
    char name[100], address[100], gmail[100], gmail1[100], address1[100], name1[100], gender[8], gender1[8];
    int res, f = 0;
    double phone, phone1;

    fptr = fopen("shakil.txt", "r");
    fptr1 = fopen("temp.txt", "a");
    if (fptr == NULL || fptr1 == NULL) {
        printf("Failed to open file.");
        return;
    }

    system("cls");
    printf("Enter the name: ");
    fgets(name1, 100, stdin);
    name1[strcspn(name1, "\n")] = '\0';

    system("cls");
    while (fscanf(fptr, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        res = strcmp(name, name1);
        if (res == 0) {
            f = 1;
            printf("MODIFY SECTION OPENED\n");
            printf("Enter the new address: ");
            fgets(address1, 100, stdin);
            address1[strcspn(address1, "\n")] = '\0';
            printf("Enter the new gender: ");
            fgets(gender1, 8, stdin);
            gender1[strcspn(gender1, "\n")] = '\0';
            printf("Enter the new gmail: ");
            fgets(gmail1, 100, stdin);
            gmail1[strcspn(gmail1, "\n")] = '\0';
            printf("Enter the new phone number: ");
            scanf("%lf", &phone1);
            getchar(); // to consume the newline character after scanf
            fprintf(fptr1, "%s %s %s %s %.0lf\n", name, address1, gender1, gmail1, phone1);
        } else {
            fprintf(fptr1, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
        }
    }

    if (f == 0) {
        printf("Record not found.\n");
    }
    fclose(fptr);
    fclose(fptr1);

    // Copy data from temp file back to original file
    fptr = fopen("shakil.txt", "w");
    fptr1 = fopen("temp.txt", "r");
    while (fscanf(fptr1, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        fprintf(fptr, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
    }
    fclose(fptr);
    fclose(fptr1);

    // Clear temp file
    fptr1 = fopen("temp.txt", "w");
    fclose(fptr1);

    printf("\n\nPress 'y' for menu option: ");
    if (getch() == 'y') {
        menu();
    }
}

void deletefun() {
    FILE *fptr, *fptr1;
    char name[100], address[100], gmail[100], name1[100], gender[8];
    int res, f = 0;
    double phone;

    fptr = fopen("shakil.txt", "r");
    fptr1 = fopen("temp.txt", "a");
    if (fptr == NULL || fptr1 == NULL) {
        printf("Failed to open file.");
        return;
    }

    system("cls");
    printf("Enter the CONTACT name that you want to delete: ");
    fgets(name1, 100, stdin);
    name1[strcspn(name1, "\n")] = '\0';

    while (fscanf(fptr, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        res = strcmp(name, name1);
        if (res == 0) {
            f = 1;
            printf("Record deleted successfully.\n");
        } else {
            fprintf(fptr1, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
        }
    }

    if (f == 0) {
        printf("Record not found.\n");
    }
    fclose(fptr);
    fclose(fptr1);

    // Copy data from temp file back to original file
    fptr = fopen("shakil.txt", "w");
    fptr1 = fopen("temp.txt", "r");
    while (fscanf(fptr1, "%s %s %s %s %lf", name, address, gender, gmail, &phone) != EOF) {
        fprintf(fptr, "%s %s %s %s %.0lf\n", name, address, gender, gmail, phone);
    }
    fclose(fptr);
    fclose(fptr1);

    // Clear temp file
    fptr1 = fopen("temp.txt", "w");
    fclose(fptr1);

    printf("\n\nPress 'y' for menu option: ");
    if (getch() == 'y') {
        menu();
    }
}

void menu() {
    system("cls");
    printf("\n\n\t\t\t\t=====================\n");
    printf("\t\t\t\tPHONEBOOK DIRECTORY\n");
    printf("\t\t\t\t=====================\n");
    printf("\t\t\t\t1. Add New Contact\n");
    printf("\t\t\t\t2. Search Contact\n");
    printf("\t\t\t\t3. List All Contacts\n");
    printf("\t\t\t\t4. Modify Contact\n");
    printf("\t\t\t\t5. Delete Contact\n");
    printf("\t\t\t\t6. Exit\n");
    printf("\t\t\t\tEnter your choice: ");

    switch (getch()) {
        case '1':
            namefun();
            break;
        case '2':
            searchfun();
            break;
        case '3':
            listfun();
            break;
        case '4':
            modifyfun();
            break;
        case '5':
            deletefun();
            break;
        case '6':
            exitfun();
            break;
        default:
            printf("\nInvalid choice, please try again.\n");
            menu();
            break;
    }
}

void password() {
    char pass[15] = "1234";
    char input[15];
    int attempts = 0;

    system("cls");
    printf("Enter Password to Access Phonebook Directory: ");

    while (attempts < 3) {
        fgets(input, 15, stdin);
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(pass, input) == 0) {
            printf("\nPassword Accepted!\n");
            menu();
            return;
        } else {
            attempts++;
            printf("Incorrect password. You have %d attempt(s) left.\n", 3 - attempts);
        }
    }
    printf("Access denied.\n");
    exit(0);
}

void exitfun() {
    printf("Exiting the program...\n");
    exit(0);
}
