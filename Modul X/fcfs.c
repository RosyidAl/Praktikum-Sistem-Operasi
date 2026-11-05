#include <stdio.h>
#include <string.h>

int main(void) {
    int n, at[100], bt[100], wt[100];
    int tat[100], ct[100], start[100];
    int i, j, temp, time = 0;
    int totalWT = 0, totalTAT = 0;
    char name[100][20], tempName[20];

    printf("=== Simulasi Penjadwalan CPU FCFS ===\n");
    printf("Jumlah proses (1-100): ");

    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        printf("Jumlah proses tidak valid.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nProses ke-%d\n", i + 1);

        printf("Nama proses: ");
        scanf("%19s", name[i]);

        printf("Arrival time: ");
        if (scanf("%d", &at[i]) != 1 || at[i] < 0) {
            printf("Arrival time tidak valid.\n");
            return 1;
        }

        printf("Burst time: ");
        if (scanf("%d", &bt[i]) != 1 || bt[i] <= 0) {
            printf("Burst time tidak valid.\n");
            return 1;
        }
    }

    /* Urutkan proses berdasarkan arrival time. */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                strcpy(tempName, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], tempName);
            }
        }
    }

    printf("\nTabel Hasil FCFS\n");
    printf("Proses\tAT\tBT\tWT\tCT\tTAT\n");

    for (i = 0; i < n; i++) {
        if (time < at[i])
            time = at[i];

        start[i] = time;
        wt[i] = start[i] - at[i];
        ct[i] = start[i] + bt[i];
        tat[i] = ct[i] - at[i];

        time = ct[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
               name[i], at[i], bt[i],
               wt[i], ct[i], tat[i]);
    }

    printf("\nGantt Chart\n");
    printf("0");

    if (start[0] > 0)
        printf(" -- Idle -- %d", start[0]);

    for (i = 0; i < n; i++) {
        if (i > 0 && start[i] > ct[i - 1])
            printf(" -- Idle -- %d", start[i]);

        printf(" -- %s -- %d", name[i], ct[i]);
    }

    printf("\n\nRata-rata Waiting Time = %.2f\n",
           (double) totalWT / n);

    printf("Rata-rata Turnaround Time = %.2f\n",
           (double) totalTAT / n);

    return 0;
}
