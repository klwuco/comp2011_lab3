#include "string.h"
#include "string"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "conio.h"
#include "regex"
#include "map"
#include "algorithm"
#include "vector"
using namespace std;

// Global Scope definitions
enum sides {LEFT, RIGHT};
enum status {WIN, LOSE, CONTINUE};
enum minion_identity {EXPERT, NEWBIE};
const string MINIONS = "KJCDSB";
const map<char, minion_identity> IDENTITY_LOOKUP = {
    {'K', EXPERT},
    {'J', EXPERT},
    {'C', EXPERT},
    {'D', NEWBIE},
    {'S', NEWBIE},
    {'B', NEWBIE}
};
constexpr int NUM = 6; // Number of minions
const unsigned int LEN_BRIDGE = 40;

// Function Prototypes
void printgame(string left ,string right, sides side);
string ask_move(string);
void move_minions(string &from, string &to, sides side, string to_move);
status judge(string left, string right);
bool lose_condition(string current_side);

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
    string left = MINIONS;
    string right = "";
    int attempts = 0;
    string user_move;
	sides side = RIGHT;
    status game;
    cout << hellomessage;
	
	cout << "Press any key to enter the game\n";
    _getch();
    system("cls");
    //count_down();
    do {
        side = (side == LEFT) ? RIGHT : LEFT; // switch sides
        printgame(left, right, side);
        user_move = ask_move((side == LEFT) ? left : right);
        move_minions(left, right, side, user_move);
        game = judge(left, right);
        attempts++;
    } while (game == CONTINUE);
    if (game == LOSE) {
        cout << "LOSE\n";
    }
    else {
        cout << "WIN\n";
    }
    system("PAUSE");
	return 0;

}

void printgame(string left, string right, sides side) {
	system("CLS");
    string left_identity(left.length(), ' ');
    string right_identity(right.length(), ' ');
    transform(left.begin(), left.end(), left_identity.begin(),
        [](char c) -> char {return (IDENTITY_LOOKUP.at(c) == NEWBIE) ? 'N' : 'E'; });
    transform(right.begin(), right.end(), right_identity.begin(),
        [](char c) -> char {return (IDENTITY_LOOKUP.at(c) == NEWBIE) ? 'N' : 'E'; });
    cout << "EXPERT: Kevin Jerry Carl (KJC) \nNEWBIES: Dave Stuart Bob (DSB)\n";
    cout << ((side == LEFT)? "Left": "Right") << " side to move now\n\n\n";
    // Print padding and the identity of minions on their head
    cout << string(NUM - left.length(), ' ') << left_identity;
    cout << string(LEN_BRIDGE + 2, ' ') << right_identity << endl;
    cout << string(NUM - left.length(), ' ') << left << ((side == LEFT) ? '*' : ' ');
    cout << string(LEN_BRIDGE, ' ');
    cout << ((side == RIGHT) ? '*' : ' ') << right << endl;
    cout << string(8, '-') << string(LEN_BRIDGE - 2, '=') << string(8, '-') << endl;
    for (int i = 0; i < 4; i++) cout << string(7, ' ') <<
        "|" << string(LEN_BRIDGE - 2, ' ') << "|\n";
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
            // to disrupt our nice prints
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

void move_minions(string &left, string &right, sides side, string to_move){
    for (char minion : to_move) {
        if (side == LEFT) {
            // the minion must be found somewhere in the string,
            // because it was checked by regex before calling.
            left.erase(left.find(minion), 1);
            right += minion;
        }
        else {
            right.erase(right.find(minion), 1);
            left += minion;
        }
    }
}

status judge(string left, string right){
    if (left.length() == 0 && right.length() == NUM)
        return WIN;
    else if (lose_condition(left) || lose_condition(right))
        return LOSE;
    return CONTINUE;
}

bool lose_condition(string current_side) {
    int num_newbie;
    int num_minion_on_side = current_side.length();
    num_newbie = count_if(current_side.begin(), current_side.end(),
        [](char c) -> bool {return IDENTITY_LOOKUP.at(c) == NEWBIE; });
    return ((float)num_newbie) / num_minion_on_side > 0.5 &&
        num_minion_on_side > num_newbie;

}

// Helper Functions

void count_down() {
    cout << "Game start in 3 seconds";
    for (int i = 2; i >= 0; i--) {
        Sleep(250);
        cout << ".";
        Sleep(250);
        cout << ".";
        Sleep(250);
        cout << ".";
        Sleep(250);
        if (i == 0) return;
        // We erase the 3 dots, then also the "<i> seconds", and push the cursor 1 more backwards
        else cout << "\b \b\b \b\b \b\b\b\b\b\b\b\b\b\b" <<
            i << " second" << ((i == 1)? " \b": "s");
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
            if (user_str.length() > 0) { 
                user_str.pop_back();
                cout << " \b";
            }
            else {
                cout << '\n'; // Prevents going back 1 line
            }
            break;
        case '\r':
            break;
        default:
            user_str += user_input;
        }
    }
    cout << endl; // newline is not automatically inserted like cin
    return user_str;
}
