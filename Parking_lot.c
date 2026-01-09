#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* RETRO COLOR PALETTE (ANSI ESCAPE CODES) */
#define RGB     "\x1b[1;33m"
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

#define MAX 5   // Size of Parking Lot

/* STACK STRUCTURE */
typedef struct {
    int arr[MAX];
    int top;
} Stack;

/* VISUAL FUNCTIONS */
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

/* DISPLAY FUNCTION */
void display(Stack s) {
    clearScreen();

    printf("%s+==================================+%s\n", RGB, RESET);
    printf("%s|   STACK BASED PARKING LOT SYS    |%s\n", RGB, RESET);
    printf("%s+==================================+%s\n", RGB, RESET);

    printf("\nStatus : %sONLINE%s | Capacity : %d/%d\n\n", GREEN, RESET, s.top+1, MAX);

    for(int i=MAX-1;i>=0;i--){
        if(i > s.top){
            printf("%s+-------------------------------+%s\n", CYAN, RESET);
            printf("%s|           [ EMPTY ]           |%s\n", CYAN, RESET);
            printf("%s+-------------------------------+%s\n", CYAN, RESET);
        } else {
            printf("%s+-------------------------------+%s\n", MAGENTA, RESET);
            printf("%s| CAR : %-5d | Position : %-2d |%s\n", MAGENTA, s.arr[i], i+1, RESET);
            printf("%s+-------------------------------+%s\n", MAGENTA, RESET);
        }
    }
}

/* STACK OPERATIONS */
int isFull(Stack *s){
    return s->top == MAX-1;
}

int isEmpty(Stack *s){
    return s->top == -1;
}

void push(Stack *s, int car){
    if(isFull(s)){
        printf("%sERROR: Parking Lane Full!%s\n", RED, RESET);
        sleep(1);
        return;
    }
    s->arr[++s->top] = car;
    printf("%sCar %d Parked Successfully.%s\n", GREEN, car, RESET);
    usleep(500000);
}

int pop(Stack *s){
    if(isEmpty(s)) return -1;
    return s->arr[s->top--];
}

/* REMOVE MIDDLE CAR LOGIC */
void removeCar(Stack *parking, int car){
    Stack temp;
    temp.top = -1;
    int found = 0;

    printf("%sInitiating retrieval for Car %d%s\n", YELLOW, car, RESET);

    while(!isEmpty(parking)){
        int c = pop(parking);
        if(c == car){
            found = 1;
            break;
        }
        push(&temp, c);
    }

    while(!isEmpty(&temp)){
        push(parking, pop(&temp));
    }

    if(found)
        printf("%sCar %d Retrieved Successfully.%s\n", GREEN, car, RESET);
    else
        printf("%sCar %d Not Found!%s\n", RED, car, RESET);

    printf("Press Enter to continue...");
    getchar(); getchar();
}

/* MAIN */
int main(){
    Stack parking;
    parking.top = -1;
    int choice, car;

    while(1){
        display(parking);
        printf("\n1. Park Car\n2. Retrieve Car\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("Enter Car ID: ");
                scanf("%d",&car);
                loadingBar("Parking");
                push(&parking, car);
                break;

            case 2:
                printf("Enter Car ID to Retrieve: ");
                scanf("%d",&car);
                removeCar(&parking, car);
                break;

            case 3:
                printf("%sSystem Exit. Goodbye!%s\n", RED, RESET);
                exit(0);

            default:
                printf("Invalid choice!\n");
                sleep(1);
        }
    }
    return 0;
}
