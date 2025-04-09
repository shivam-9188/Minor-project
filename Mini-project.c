#include <stdio.h>
#define MAX 10

int getMaxCredit(int amount[], int n) {
    int maxIndex = 0;
    for (int i = 1; i < n; i++)
        if (amount[i] > amount[maxIndex])
            maxIndex = i;
    return maxIndex;
}


int getMaxDebit(int amount[], int n) {
    int minIndex = 0;
    for (int i = 1; i < n; i++)
        if (amount[i] < amount[minIndex])
            minIndex = i;
    return minIndex;
}


void settleDebts(int amount[], int n) {
    int maxCreditor = getMaxCredit(amount, n);
    int maxDebtor = getMaxDebit(amount, n);

    if (amount[maxCreditor] == 0 && amount[maxDebtor] == 0)
        return;

    int minAmount = (amount[maxCreditor] < -amount[maxDebtor]) ? amount[maxCreditor] : -amount[maxDebtor];
    amount[maxCreditor] -= minAmount;
    amount[maxDebtor] += minAmount;

    printf("=> Person %d pays Rs. %d to Person %d\n", maxDebtor + 1, minAmount, maxCreditor + 1);

    settleDebts(amount, n);
}

int main() {
    int n, i, j;
    int graph[MAX][MAX];
    int amount[MAX] = {0};

    printf("Welcome to the Cash Flow Minimizer!\n");
    printf("How many people are involved in transactions? ");
    scanf("%d", &n);

    if (n > MAX || n <= 1) {
        printf("Please enter between 2 and %d people.\n", MAX);
        return 0;
    }

    printf("\nEnter who owes whom (Person i to Person j):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                printf("Amount Person %d owes to Person %d: ", i + 1, j + 1);
                scanf("%d", &graph[i][j]);
            } else {
                graph[i][j] = 0;
            }
        }
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            amount[i] += graph[j][i] - graph[i][j];

    printf("\nCalculating simplified payments...\n\n");
    settleDebts(amount, n);

    printf("\nAll debts settled with minimum number of transactions.\n");

    return 0;
}