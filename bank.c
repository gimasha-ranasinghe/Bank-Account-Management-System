
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"

// Function to display the menu
void displayMenu() {
    printf("\n*** Bank Account Management System ***\n");
    printf("1. Create Account\n");
    printf("2. View Account\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Exit\n");
}

// Function to create a new account
void createAccount() {
    FILE *file = fopen("accounts.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Account newAccount;
    printf("Enter account holder's name: ");
    scanf(" %[^\n]", newAccount.name);
    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNumber);
    printf("Enter initial deposit: ");
    scanf("%f", &newAccount.balance);

    fwrite(&newAccount, sizeof(Account), 1, file);
    fclose(file);

    printf("Account created successfully!\n");
}

// Function to view an account
void viewAccount() {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No accounts found!\n");
        return;
    }

    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            printf("\nAccount Details:\n");
            printf("Name: %s\n", account.name);
            printf("Account Number: %d\n", account.accountNumber);
            printf("Balance: $%.2f\n", account.balance);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to deposit money
void depositMoney() {
    FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("No accounts found!\n");
        return;
    }

    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account account;
    int found = 0;
    long position;

    while ((position = ftell(file)) != -1 && fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            printf("Enter deposit amount: ");
            float deposit;
            scanf("%f", &deposit);

            account.balance += deposit;

            fseek(file, position, SEEK_SET);
            fwrite(&account, sizeof(Account), 1, file);

            printf("Deposit successful! New balance: $%.2f\n", account.balance);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to withdraw money
void withdrawMoney() {
    FILE *file = fopen("accounts.txt", "r+");
    if (file == NULL) {
        printf("No accounts found!\n");
        return;
    }

    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    Account account;
    int found = 0;
    long position;

    while ((position = ftell(file)) != -1 && fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            printf("Enter withdrawal amount: ");
            float withdrawal;
            scanf("%f", &withdrawal);

            if (withdrawal > account.balance) {
                printf("Insufficient balance!\n");
            } else {
                account.balance -= withdrawal;

                fseek(file, position, SEEK_SET);
                fwrite(&account, sizeof(Account), 1, file);

                printf("Withdrawal successful! New balance: $%.2f\n", account.balance);
            }
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found!\n");
    }
}
