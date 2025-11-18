#include <stdio.h>

#define MAX 30
#define SPEED_LIMIT 80

void inputData(int vehicleID[], int speed[], int lane[], int *n);
int countSpeedViolations(int speed[], int n);
int countLaneViolations(int vehicleID[], int lane[], int n);
int busiestLane(int laneCount[]);
int leastBusyLane(int laneCount[]);
void displayReport(int vehicleID[], int speed[], int lane[], int n);

int main() {
    int vehicleID[MAX], speed[MAX], lane[MAX];
    int n;

    inputData(vehicleID, speed, lane, &n);

    displayReport(vehicleID, speed, lane, n);

    return 0;
}

void inputData(int vehicleID[], int speed[], int lane[], int *n) {
    int i;

    printf("Enter number of vehicles (max 30): ");
    scanf("%d", n);

    if (*n > MAX) {
        *n = MAX; 
    }

    for (i = 0; i < *n; i++) {
        printf("Vehicle %d ID: ", i + 1);
        scanf("%d", &vehicleID[i]);

        printf("Speed: ");
        scanf("%d", &speed[i]);
        if (speed[i] < 0) speed[i] = 0;  // ensure positive

        printf("Lane (1-4): ");
        scanf("%d", &lane[i]);
        if (lane[i] < 1 || lane[i] > 4) lane[i] = 1;  // default safe
    }
}

int countSpeedViolations(int speed[], int n) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (speed[i] > SPEED_LIMIT) {
            count++;
        }
    }
    return count;
}

int countLaneViolations(int vehicleID[], int lane[], int n) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (vehicleID[i] % 4 != lane[i]) {
            count++;
        }
    }
    return count;
}

int busiestLane(int laneCount[]) {
    int maxLane = 1, i;
    for (i = 1; i < 4; i++) {
        if (laneCount[i] > laneCount[maxLane]) {
            maxLane = i;
        }
    }
    return maxLane + 1;
}

int leastBusyLane(int laneCount[]) {
    int minLane = 0, i;
    for (i = 1; i < 4; i++) {
        if (laneCount[i] < laneCount[minLane]) {
            minLane = i;
        }
    }
    return minLane + 1;
}

void displayReport(int vehicleID[], int speed[], int lane[], int n) {
    int i;
    int laneCount[4] = {0, 0, 0, 0};

    int speedViol = countSpeedViolations(speed, n);
    int laneViol = countLaneViolations(vehicleID, lane, n);

    // Count traffic per lane
    for (i = 0; i < n; i++) {
        laneCount[lane[i] - 1]++;
    }

    int busy = busiestLane(laneCount);
    int less = leastBusyLane(laneCount);

    printf("\n---------------- Traffic Report ----------------\n");
    printf("VehID\tSpeed\tLane\tSpeedViolation\tLaneViolation\n");

    for (i = 0; i < n; i++) {
        int sv = (speed[i] > SPEED_LIMIT) ? 1 : 0;
        int lv = (vehicleID[i] % 4 != lane[i]) ? 1 : 0;

        printf("%d\t%d\t%d\t%d\t\t%d\n",
               vehicleID[i], speed[i], lane[i], sv, lv);
    }

    printf("\nTotal Speed Violations: %d", speedViol);
    printf("\nTotal Lane Violations: %d", laneViol);

    printf("\nBusiest Lane: %d", busy);
    printf("\nLeast Busy Lane: %d", less);
    printf("\nTotal Traffic Volume: %d\n", n);

    printf("\n");
}
