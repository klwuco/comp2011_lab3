#include "string.h"
#include "string"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "conio.h"
#include "regex"
using namespace std;

const string MINIONS = "KJCDSB";
enum sides {LEFT, RIGHT};
enum status {WIN, LOSE, CONTINUE};

void printgame(char left[] ,char right[], sides side);
string ask_move(string);
void move_minions(char from[], char to[], string moved);
status judge(char left[], char right[]);

// Helper Functions
void count_down(void);
void cursor_up(int n);
void clear_line(void);
void cursor_up_clear(int n);
string get_without_cr(void);

const string hellomessage = R"(Bomba! You are Minion Kevin! You must direct your team of 6 Minion Bomb Transporters
across a high narrow bridge.You, Jerry, and Carl are seasoned experts, but Dave, Stuart, and
Bob are over - excited newbies.Initially, all 6 of you are on one side of the bridge.Your task is to
get everybody across the bridge.But, the bridge can only take the weight of 1 or 2 Transporters
at a time, and it¡¯s dark!You only have a single lantern that must be carried with each crossing
to light your way across!Even worse, when newbies and experts are both together on one side
and newbies outnumber expects, they start squabbling and hitting one another, their bombs go
off, and everybody dies!
)";

int main() {
	char left[7] = "KJCDSB";
    char right[7] = "      ";
    int attempts = 0;
    string user_move;
	sides side = LEFT;
    status game;
    cout << hellomessage;
	
	cout << "Press any key to enter the game\n";
    _getch();
    system("cls");
    count_down();
    do {
        printgame(left, right, side);
        if (attempts & 1 == 0) {
            user_move = ask_move(left);
            move_minions(left, right, user_move);
        }
        else {
            user_move = ask_move(right);
            move_minions(right, left, user_move);
        }
        game = judge(left, right);
        attempts++;
    } while (game == CONTINUE);
    system("PAUSE");
	return 0;

}

void count_down() {
    cout << "Game start in 3 seconds";
    for (int i = 2; i >= 0; i--) {
        // Sleep(250);
        cout << ".";
        // Sleep(250);
        cout << ".";
        // Sleep(250);
        cout << ".";
        // Sleep(250);
        Sleep(1000);
        if (i == 0) return;
        // We erase the 3 dots, then also the "<i> seconds", and push the cursor 1 more backwards
        else cout << "\b \b\b \b\b \b\b\b\b\b\b\b\b\b\b" <<
            i << " second" << ((i == 1)? " \b": "s");
    }
}

void printgame(char left[], char right[], sides side) {
	system("CLS");
	cout << "EXPERT: Kevin Jerry Carl (KJC) \nNEWBIES: Dave Stuart Bob (DSB)\n\n\n\n";
    cout << left << ((side == LEFT) ? '*' : ' ');
    cout << string(38, ' ');
    cout << ((side == RIGHT) ? '*' : ' ') << right << endl;
    cout << string(8, '-') << string(36, '=') << string(8, '-') << endl;
    for (int i = 0; i < 4; i++) cout << string(7, ' ') <<
        "|" << string(36, ' ') << "|\n";
}

string ask_move(string current_side) {
    string user_input;
    string str_pattern = "^[" + current_side + "]{1,2}$";
    regex pattern (str_pattern);
    while (true) {
        user_input = get_without_cr();
        while (!(regex_match(user_input, pattern) && user_input[0] != user_input[1] )) {
            cout << "Invalid Input!";
            // Move back to input line, clear and return
            cursor_up(1);
            clear_line();
            cout << '\r';
            // We don't use cin because we don't want carriage return
            // to disrupt our command line
            user_input = get_without_cr();
        }
        cout << "You have inputted " << user_input << ". Is that correct?\n" <<
            "Press N or n to type in again, press any other key to get the minons moving.\n";
        if (toupper(_getch()) == 'N') {
            cursor_up_clear(3); // two for the cout, one for the input line
            clear_line(); // clear the input line
        }
        else
            return user_input;
    }
}

void cursor_up(int n) {
    for (int i = 0; i < n; i++) cout << "\033[A";
}

void clear_line(void) {
    cout << "\33[2K";
}

void cursor_up_clear(int n) {
    for (int i = 0; i < n; i++) {
        clear_line();
        cursor_up(1);
    };
}

string get_without_cr() {
    char user_input = 0;
    string user_str = "";
    while (user_input != '\r') {
        user_input = _getche();
        switch (user_input) {
        case '\b':
            if (user_str.length() > 0)
                user_str.resize(user_str.length() - 1);
            break;
        case '\r':
            break;
        default:
            user_str += user_input;
        }
    }
    // Transform to upper case
    for (char &c : user_str) {
        c = toupper(c);
    }
    cout << endl; // newline is not automatically inserted like cin
    return user_str;
}
void move_minions(char from[], char to[], string moved){
}

status judge(char left[], char right[]){
    return CONTINUE;
}
