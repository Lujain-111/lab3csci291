#include <stdio.h>

#define MAX_TRANSACTIONS 100

int validate_input(int *input) {
    if (scanf("%d", input) != 1) {
        while (getchar() != '\n'); 
        printf("Invalid input! Please enter a valid integer.\n");
        return -1; // Return -1 if input is invalid
    }
    return 1; // Return 1 if input is valid
}

// Function to process the transactions and manage balance
void process_transactions(int transactions[], int length) {
    int balance = 1000; // Starting balance
    int tobeprocessed[MAX_TRANSACTIONS]; // Array to store unprocessed transactions
    int unprocessed_count = 0; // Counter for unprocessed transactions

    for (int i = 0; i < length; i++) {
        int transaction = transactions[i];

        // If it's a withdrawal, check if the balance will be exceeded
        if (transaction < 0) {
            if (balance + transaction < 0) {
                printf("Invalid transaction: Withdrawal of %d exceeds current balance of %d.\n", -transaction, balance);
                tobeprocessed[unprocessed_count++] = transaction; // Store unprocessed withdrawal
                continue; // Skip this transaction and go to the next one
            }
        }

        balance += transaction; // Apply the transaction to the balance

        // If balance reaches zero, stop processing further transactions
        if (balance == 0) {
            printf("Balance has reached 0. No further transactions will be processed.\n");
            for (int j = i + 1; j < length; j++) {
                tobeprocessed[unprocessed_count++] = transactions[j]; // Store remaining unprocessed transactions
            }
            break; // Exit the loop when balance is 0
        }
    }

    // Print the final balance
    printf("Final balance: %d AED\n", balance);

    // Display unprocessed transactions, if any
    if (unprocessed_count > 0) {
        printf("Unprocessed transactions:\n");
        for (int i = 0; i < unprocessed_count; i++) {
            printf("%d ", tobeprocessed[i]);
        }
        printf("\n");
    } else {
        printf("No unprocessed transactions.\n");
    }
}

int main() {
    int transactions[MAX_TRANSACTIONS];
    int length = 0;
    int input;

    printf("Enter transactions (positive for deposits, negative for withdrawals, 0 to end):\n");

    // Loop to take transactions as input from the user
    while (1) {
        printf("Transaction %d: ", length + 1);

        if (validate_input(&input) == -1) {
            continue; // Skip invalid input and prompt again
        }

        if (input == 0) {
            break; // Exit the loop if input is 0
        }

        transactions[length++] = input; // Store valid transaction

        if (length >= MAX_TRANSACTIONS) {
            printf("Maximum number of transactions reached.\n");
            break; // Exit if maximum transactions are reached
        }
    }

    // Process the transactions and display results
    process_transactions(transactions, length);

    return 0;
}
