#include <ncurses.h>

int main() {
    initscr();             //Starts ncurses mode
    printw("Press 'a' for a message, 'q' to quit.");
    refresh();             //Refreshes the screen to show message

    int ch;
    while ((ch = getch()) != 'q') {  //Loop until 'q' is pressed
        clear();                     //Clears the screen
        
        if (ch == 'a') {
            printw("You pressed 'a'! Great choice.");
        } else {
            printw("Press 'a' for a message or 'q' to quit.");
        }

        refresh();                   
    }

    endwin(); //Ends ncurses mode
    return 0;
}