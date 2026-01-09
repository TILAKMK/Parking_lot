#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* RETRO COLOR PALETTE (ANSI ESCAPE CODES) */
#define RGB "\x1b[1;33m"
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

#define MAX 5   // Parking Lot Capacity

/* STACK STRUCTURE */
typedef struct {
    int arr[MAX];
    int top;
} Stack;

/* Utility Functions */
void clearScreen() {
    printf("\033[H\033[J");
}

void loadingBar(char *message) {
    printf("%s%s", CYAN, message);
    for(int i=0;i<3;i++){
        fflush(stdout);
        usleep(300000);
        printf(".");
    }
    printf("%s\n", RESET);
}

/* Display Parking Lot */
void display(Stack s) {
    clearScreen();

    printf("%s + + + + + + +\n", RGB);
    printf(" +== + +== + +== + | ++ |+== +==+\n");
    printf(" ++ | ++ ++ | | \n");
    printf(" +===+ +== | +== + += + | | \n");
    printf(" | | | | | | + | | \n");
    printf(" +=+ +=+ +=++=+ +=++=+ +=++=+ +=+ \n");
    printf("--------------------------------------------%s\n", RESET);

    printf("%s :: STACK BASED PARKING LOT MANAGEMENT ::%s\n", MAGENTA, RESET);
    printf("\nStatus: %sONLINE%s | Capacity: %d/%d\n\n", GREEN, RESET, s.top + 1, MAX);

    printf(" %sENTRY / EXIT (TOP)%s\n", YELLOW, RESET);
    printf(" %s|| ||%s\n", CYAN, RESET);
    printf(" %s\\/ \\/%s\n", CYAN, RESET);

    for (int i = MAX - 1; i >= 0; i--) {
        if (i > s.top) {
            printf(" %s+-----------------+%s\n", CYAN, RESET);
            printf(" %s|     EMPTY       |%s\n", CYAN, RESET);
            printf(" %s+-----------------+%s\n", CYAN, RESET);
        } else {
            printf(" %s+-----------------+%s\n", MAGENTA, RESET);
            printf(" %s| CAR : %-5d     |%s <--Pos %d\n", MAGENTA, s.arr[i], RESET, i+1);
            printf(" %s+-----------------+%s\n", MAGENTA, RESET);
        }
    }
    printf(" %s===================%s\n", WHITE, RESET);
    printf(" %sBLOCKED WALL%s\n\n", RED, RESET);
}

/* Stack Operations */
int isFull(Stack *s) { return s->top == MAX - 1; }
int isEmpty(Stack *s) { return s->top == -1; }

void push(Stack *s, int car) {
    if (isFull(s)) {
        printf("\n%s[!] PARKING FULL. Cannot admit Car %d%s\n", RED, car, RESET);
        sleep(1);
        return;
    }
    s->arr[++(s->top)] = car;
    printf("\n%s[+] Car %d Parked Successfully%s\n", GREEN, car, RESET);
    usleep(800000);
}

int pop(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->arr[(s->top)--];
}

/* Remove Specific Car */
void removeCar(Stack *parking, int car) {
    Stack temp;
    temp.top = -1;
    int found = 0;

    printf("\n%s>> Retrieving Car %d...%s\n", YELLOW, car, RESET);

    while (!isEmpty(parking)) {
        int cur = pop(parking);
        if (cur == car) {
            found = 1;
            break;
        } else {
            push(&temp, cur);
        }
    }

    while (!isEmpty(&temp))
        push(parking, pop(&temp));

    if (found)
        printf("%s[✓] Car %d Retrieved Successfully%s\n", GREEN, car, RESET);
    else
        printf("%s[X] Car %d Not Found%s\n", RED, car, RESET);

    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

/* MAIN */
int main() {
    Stack parking;
    parking.top = -1;
    int choice, car;

    while (1) {
        display(parking);
        printf("%s[1]%s Park Car   %s[2]%s Retrieve Car   %s[3]%s Exit\n",
               GREEN, RESET, YELLOW, RESET, RED, RESET);
        printf("\n%sCOMMAND > %s", WHITE, RESET);
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Car ID: ");
            scanf("%d", &car);
            loadingBar("Parking");
            push(&parking, car);
            break;

        case 2:
            printf("Enter Car ID to Retrieve: ");
            scanf("%d", &car);
            removeCar(&parking, car);
            break;

        case 3:
            printf("%sSystem Shutdown...%s\n", RED, RESET);
            exit(0);

        default:
            printf("Invalid Option\n");
            sleep(1);
        }
    }
    return 0;
}
