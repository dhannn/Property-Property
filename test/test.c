#include <stdio.h>

typedef enum{
    GO_JAIL
} State;

typedef struct {
    State state;
    void (*displayState)();
} CurrentState;


void goToJail(){
    printf("Oh no. You're in jail");
}

CurrentState goJail = {GO_JAIL, goToJail};
CurrentState goJail = {GO_JAIL, goToJail};

void handleState(CurrentState state){
    state.displayState();
}

int main(){
    handleState(goJail);
}
