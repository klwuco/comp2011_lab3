#include "string.h"
#include "string"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "conio.h"
using namespace std;
#define LEFT 0 
#define LEFT 1
void printgame(char left[] ,char right[], int side);


const string hellomessage = R"(Bomba! You are Minion Kevin! You must direct your team of 6 Minion Bomb Transporters
	across a high narrow bridge.You, Jerry, and Carl are seasoned experts, but Dave, Stuart, and
	Bob are over - excited newbies.Initially, all 6 of you are on one side of the bridge.Your task is to
	get everybody across the bridge.But, the bridge can only take the weight of 1 or 2 Transporters
	at a time, and it¡¯s dark!You only have a single lantern that must be carried with each crossing
	to light your way across!Even worse, when newbies and experts are both together on one side
	and newbies outnumber expects, they start squabbling and hitting one another, their bombs go
	off, and everybody dies!)";

int main() {
	char left[] = "KJCDSB"; char right[6];
	int side;
	cout << hellomessage;
	
	cout << "Press spacebar to enter the game";
	char ans;
	do
	{
	} while (_getch() != 32 || _getch() != ' ');
	
	cout << "Game start in 3 second" << endl;
	Sleep(3000);
	
	printgame(left, right, side);



	return 0;

}


void printgame(char left[], char right[], int side) {
	system("CLS");
	cout << "EXPERT: KEVIN JERRY CARL \nNEWBIES: DAVE STUART BOB\n\n\n\n";
	cout << "Test";
	Sleep(1000);
	cout << "";


}