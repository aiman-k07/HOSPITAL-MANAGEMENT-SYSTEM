#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Color Codes */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
};

void addPatient() {
    FILE *fp;
    struct Patient p;

    fp = fopen("patients.dat", "ab");
    if (fp == NULL) {
        printf(RED "Error opening file!\n" RESET);
        return;
    }

    printf(CYAN "\nEnter Patient ID: " RESET);
    scanf("%d", &p.id);

    printf(CYAN "Enter Name: " RESET);
    scanf(" %[^\n]", p.name);

    printf(CYAN "Enter Age: " RESET);
    scanf("%d", &p.age);

    printf(CYAN "Enter Disease: " RESET);
    scanf(" %[^\n]", p.disease);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf(GREEN "\n✔ Patient record added successfully!\n" RESET);
}

void viewPatients() {
    FILE *fp;
    struct Patient p;

    fp = fopen("patients.dat", "rb");
    if (fp == NULL) {
        printf(RED "\nNo records found!\n" RESET);
        return;
    }

    printf(BOLD BLUE "\n========== Patient Records ==========\n" RESET);

    while (fread(&p, sizeof(p), 1, fp)) {
        printf(YELLOW "\nID: %d\n" RESET, p.id);
        printf("Name: %s\n", p.name);
        printf("Age: %d\n", p.age);
        printf("Disease: %s\n", p.disease);
        printf(BLUE "-------------------------------------\n" RESET);
    }

    fclose(fp);
}

void searchPatient() {
    FILE *fp;
    struct Patient p;
    int id, found = 0;

    fp = fopen("patients.dat", "rb");
    if (fp == NULL) {
        printf(RED "\nNo records found!\n" RESET);
        return;
    }

    printf(CYAN "Enter Patient ID to search: " RESET);
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf(GREEN "\n✔ Patient Found!\n" RESET);
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.name);
            printf("Age: %d\n", p.age);
            printf("Disease: %s\n", p.disease);
            found = 1;
            break;
        }
    }

    if (!found)
        printf(RED "\n✘ Patient not found!\n" RESET);

    fclose(fp);
}

void deletePatient() {
    FILE *fp, *temp;
    struct Patient p;
    int id, found = 0;

    fp = fopen("patients.dat", "rb");
    if (fp == NULL) {
        printf(RED "\nNo records found!\n" RESET);
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf(CYAN "Enter Patient ID to delete: " RESET);
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;
        } else {
            fwrite(&p, sizeof(p), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    if (found)
        printf(GREEN "\n✔ Patient record deleted successfully!\n" RESET);
    else
        printf(RED "\n✘ Patient not found!\n" RESET);
}

int main() {
    int choice;

    while (1) {
        printf(BOLD BLUE "\n\n===== HOSPITAL MANAGEMENT SYSTEM =====\n" RESET);
        printf(YELLOW "1. Add Patient\n" RESET);
        printf(YELLOW "2. View Patients\n" RESET);
        printf(YELLOW "3. Search Patient\n" RESET);
        printf(YELLOW "4. Delete Patient\n" RESET);
        printf(YELLOW "5. Exit\n" RESET);
        printf(CYAN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5:
                printf(GREEN "\nThank you! Exiting...\n" RESET);
                exit(0);
            default:
                printf(RED "\nInvalid choice! Try again.\n" RESET);
        }
    }

    return 0;
}