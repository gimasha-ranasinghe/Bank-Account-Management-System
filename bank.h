#ifndef BANK_H
#define BANK_H

typedef struct {
    char name[50];
    int accountNumber;
    float balance;
} Account;

void createAccount();
void viewAccount();
void depositMoney();
void withdrawMoney();
void displayMenu();

#endif

