#include "string.h"
#include "string"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "conio.h"
#include "regex"
using namespace std;
#define LEFT 0 
#define RIGHT 1
const string MINIONS = "KJCDSB";

void printgame(char left[] ,char right[], int side);
string ask_move(string);

// Helper Functions
void cursor_up(int n);
void clear_line(void);
void cursor_up_clear(int n);

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
	int side = LEFT;
    int attempts = 0;
    cout << hellomessage;
	
	cout << "Press any key to enter the game\n";
    _getch();
    system("cls");
	cout << "Game start in 3 second";
    for (int i = 2; i >= 0; i--) {
        // Sleep(250);
        cout << ".";
        // Sleep(250);
        cout << ".";
        // Sleep(250);
        cout << ".";
        // Sleep(250);
        if (i != 0) cout << "\b \b\b \b\b \b\b\b\b\b\b\b\b\b" << i << " second";
    }

	printgame(left, right, side);
    ask_move(left);
    system("PAUSE");
	return 0;

}


void printgame(char left[], char right[], int side) {
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
    cout << str_pattern << endl;
    regex pattern(str_pattern.begin(), str_pattern.end());
    while (true) {
        cin >> user_input;
        while (!regex_match(user_input, pattern)) {
            cout << "Invalid Input!";
            cout << "\033[A\33[2K\r";
            cin >> user_input;
        }
        clear_line();
        cout << "You have inputted " << user_input << ". Is that correct?\n" <<
            "Press N or n to type in again, press any other key to get the minons moving.\n";
        if (toupper(_getch()) == 'N')
            cursor_up_clear(4);
        else
            return user_input;
    }
}

void cursor_up(int n) {
    for (int i = 0; i < n; i++) cout << "\033[A";
}

void cursor_up_clear(int n) {
    for (int i = 0; i < n; i++) {
        clear_line();
        cursor_up(1);
    };
}
void clear_line(void) {
    cout << "\33[2K";
}