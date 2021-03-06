// Requires a terminal capable of showing ANSI escape sequences (every modern terminal?)
#include "algorithm" // count_if, sort, for_each
#include "iostream"
#include "map"
#include "numeric" // accumulate
#include "regex" // regex_match
#include "string"
#include "conio.h"
#include "windows.h"
using namespace std;
// Note: heavy function programming style here

// enum definitions
enum sides {LEFT, RIGHT};
enum status {WIN, LOSE, CONTINUE};
enum minion_identity {EXPERT, NEWBIE};

// Helper Functions
// Counts down 3 seconds
void count_down(void);
// These functions make use of ANSI escape sequences to manipulate the console
void cursor_up(int n);
void clear_line(void);
void cursor_up_clear(int n);
// Asks for user input that prevents cursor movement by CR and sometimes backspaces
string get_without_cr(void);
// This is a wrapper of std::sort which returns the sorted container directly.
// Requires iterable to have a begin() and end() member function that returns ForwardIterator
// and comp as a functor
template< class T, class CompareFunc>
T functional_sort(T iterable,CompareFunc comp);


// Constants
const map<char, minion_identity> IDENTITY_LOOKUP = {
    {'K', EXPERT},
    {'J', EXPERT},
    {'C', EXPERT},
    {'D', NEWBIE},
    {'S', NEWBIE},
    {'B', NEWBIE}
};
const unsigned int LEN_BRIDGE = 40;
const string hellomessage = R"(Bomba! You are Minion Kevin! You must direct your team of 6 Minion Bomb Transporters
across a high narrow bridge.You, Jerry, and Carl are seasoned experts, but Dave, Stuart, and
Bob are over - excited newbies.Initially, all 6 of you are on one side of the bridge.Your task is to
get everybody across the bridge.But, the bridge can only take the weight of 1 or 2 Transporters
at a time, and it's dark!You only have a single lantern that must be carried with each crossing
to light your way across!Even worse, when newbies and experts are both together on one side
and newbies outnumber expects, they start squabbling and hitting one another, their bombs go
off, and everybody dies!
)";
// Derived definitions
// Extract the string representation of minions from the lookup map
const string MINIONS_UNSORTED = accumulate(IDENTITY_LOOKUP.begin(), IDENTITY_LOOKUP.end(), string(),
    [](string str, pair<char, minion_identity> p) -> string {return str + get<0>(p); }); // string concat
// sort according to identity
const string MINIONS = functional_sort(MINIONS_UNSORTED,
    [](char a, char b) {return (IDENTITY_LOOKUP.at(a) < IDENTITY_LOOKUP.at(b)); });
const unsigned int NUM_MINIONS = MINIONS.length();

// Function Prototypes
void printgame(string left ,string right, sides side, int num_moves);
void print_minion_identity(string minions);
string ask_move(string);
void move_minions(string &from, string &to, sides side, string to_move);
status judge(string left, string right);
bool lose_condition(string current_side);
void switch_side(sides &side);



int main() {
    // Variable declaration
    string user_move;
    status game;
    // Initial conditions
    int num_moves = 1;
    string left = MINIONS;
    string right = string();
    sides side = RIGHT; // will switch at start of game
    // Lambda expressions
    // Needs reference to update
    auto current = [&left, &right, &side]() -> string {return (side == LEFT) ? left : right; };
    
    
    // main program
    cout << hellomessage;
    cout << "Press any key to enter the game\n\n";
    _getch();
    count_down();
    do {
        switch_side(side);
        printgame(left, right, side, num_moves);
        user_move = ask_move(current());
        move_minions(left, right, side, user_move);
        game = judge(left, right);
        num_moves++;
    } while (game == CONTINUE);
    switch_side(side);
    printgame(left, right, side, num_moves);
    if (game == LOSE) {
        cout << "OH NO! The newbies tried to impress the expert, but ended up failing\n" <<
            "and the bomb explodes! Everybody dies... :(\n" <<
            "The gory details are not shown here...\n";
    }
    else {
        cout << "Kevin! You have done it! You have managed to finish the job in "<< num_moves << " moves!\n" <<
            "As a bonus for you, you get a banana!";
    }
    system("PAUSE");
    return 0;

}

void printgame(string left, string right, sides side, int num_moves) {
    int padding = NUM_MINIONS - left.length();
    system("CLS");
    cout << "Expert: Kevin(You!) Jerry Carl\t\tNewbies: Dave Stuart Bob\n";
    cout << ((side == LEFT)? "Left": "Right") << " side to move now\t\t\tMove " << num_moves << "\n\n\n";

    // Print padding and the identity of minions on their head
    cout << string(padding, ' ');
    print_minion_identity(left);
    cout << string(LEN_BRIDGE + 4, ' ');
    print_minion_identity(right);

    // print padding, name of minions, lantern and the floor
    cout << '\n' << string(padding, ' ') << left << ((side == LEFT) ? '*' : ' ') <<
        string(LEN_BRIDGE + 2, ' ') << ((side == RIGHT) ? '*' : ' ') << right << endl <<
        string(NUM_MINIONS + 2, '-') << string(LEN_BRIDGE, '=') << string(NUM_MINIONS + 2, '-') << endl;

    // print the bottom
    for (int i = 0; i < 4; i++) cout << string(NUM_MINIONS + 1, ' ') <<
        "|" << string(LEN_BRIDGE, ' ') << "|\n";
}

void print_minion_identity(string minions) {
    for_each(minions.begin(), minions.end(),
        [](char c) -> void {cout << ((IDENTITY_LOOKUP.at(c) == NEWBIE) ? 'N' : 'E'); });
}

string ask_move(string current_side) {
    string user_input;
    string str_pattern = "^[" + current_side + "]{1,2}$";
    regex pattern (str_pattern);
    cout << "Who will cross the bridge? (" << current_side << ")\n";
    while (true) {
        user_input = get_without_cr();
        while (!(regex_match(user_input, pattern) && user_input[0] != user_input[1] )) {
            clear_line();
            if (user_input == "")
                cout << "The latern can not just fly back to the other side! Someome must carry it!";
            else
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
    if (left.length() == 0 && right.length() == NUM_MINIONS)
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

void switch_side(sides &side){
    side = static_cast<sides>((side + 1) % 2);
}

// Helper Functions

void count_down() {
    cout << "Game starting in 3 seconds";
    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j < 3; j++) {
            Sleep(250);
            cout << ".";
        }
        Sleep(250);
        if (i == 0) return;
        cout << "\rGame starting in "<< i <<" second" <<
            ((i<=1)? "    \b\b\b\b": "s   \b\b\b"); // The last spaces and \b is for the dots
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
            else
                cout << '\n'; // Prevents going back 1 line
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

template< class T, class CompareFunc>
T functional_sort(T iterable,CompareFunc comp) {
    sort(iterable.begin(), iterable.end(), comp);
    return iterable;
}
