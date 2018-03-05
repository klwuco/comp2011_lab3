#include "string.h"
#include "string"
#include "iostream"
#include "stdio.h"
#include "windows.h"
#include "conio.h"
#include <cstdlib> 
using namespace std;
#define LEFT 0 
#define LEFT 1
void printgame(char[ ],char [], char[], char[], int side);
bool continuegame(char[], char[], char[], char[]);
bool checkInvalidinput(char, char, char[], char[]);
void movepeople(char input1, char input2, char[], char[],char[],char[],int);
void concat(char a[], char b);
void deletelocation(char, char[]);
const string hellomessage = R"(Bomba! You are Minion Kevin! You must direct your team of 6 Minion Bomb Transporters
	across a high narrow bridge.You, Jerry, and Carl are seasoned experts, but Dave, Stuart, and
	Bob are over - excited newbies.Initially, all 6 of you are on one side of the bridge.Your task is to
	get everybody across the bridge.But, the bridge can only take the weight of 1 or 2 Transporters
	at a time, and it¡¯s dark!You only have a single lantern that must be carried with each crossing
	to light your way across!Even worse, when newbies and experts are both together on one side
	and newbies outnumber expects, they start squabbling and hitting one another, their bombs go
	off, and everybody dies!)";



int main1() {
	
	char leftexpert [4] = "KJC"; 
	char rightexpert[4] = {'\0','\0' ,'\0' ,'\0' };//the fourth space store the null terminator
	char leftbaby   [4] = "DSB"; 
	char rightbaby  [4] = {'\0','\0' ,'\0' ,'\0' };//the fourth space store the null terminator

	
	cout << hellomessage;                              //welcoming message
	cout << "\n\n\nPress spacebar to enter the game";  //welcoming message
	char gamestart;									   //welcoming message
	do                                                 //welcoming message
	{                                                  //welcoming message
		gamestart = _getch();                          //welcoming message
	} while (gamestart != 32);                         //welcoming message
	cout<<"\n\nPressed\n\n";                           //welcoming message
	for (int i = 3; i >= 1; i--) {                     //welcoming message
		cout << "Game start in " << i << " second";    //welcoming message
	    Sleep(1000);                                   //welcoming message
		cout << "\r";                                  //welcoming message
	}                                                  //welcoming message



	
	
	char userinput1 = ' ';//store the first  people to be moved
	char userinput2 = ' ';//store the second people to be moved
	
	int side = 1;// side=1  mean lantern on the left,     side=2 mean lantern on the right
	do {

		system("cls");
		printgame(leftexpert, leftbaby, rightexpert, rightbaby, side);//Print the whole game interface
		


		cout << "How many people do you want to move, enter 1 or 2\n\n";
		char NumberOfPeopleMove;
		while (true) {//ask whether player move one or move two people
			NumberOfPeopleMove = _getch();
			if ((NumberOfPeopleMove  == '1' || NumberOfPeopleMove == '2')) {break; }//exit if valid
			cout << "Enter 1 or 2 only . Thank you\n";
		} 



		switch (side) {//determine where is the lantern,  1 is left side, 2 is right side
		case 1:	switch (NumberOfPeopleMove) { 
		        case '1':cout << "Plese enter one char in " << leftexpert << leftbaby << "\n\n"; break;
		        case '2':cout << "Plese enter two char in " << leftexpert << leftbaby << "\n\n"; break;
		        }break;
		
		case 2: switch (NumberOfPeopleMove) {
		        case '1':cout << "Plese enter one char in  " << rightexpert << rightbaby << "\n\n"; break;
				case '2':cout << "Plese enter two char in  " << rightexpert << rightbaby << "\n\n"; break;
				}
		}
        


		do {//this do while will check whether input is valid or not
			cin >> userinput1;      userinput1 = toupper(userinput1);
			if (NumberOfPeopleMove == '2')
			{
				cin >> userinput2;	userinput2 = toupper(userinput2);
			}
			else { userinput2 = ' '; }//record two letter if player want to move two
			
		} while (
			(side==1)?//check lantern side
			checkInvalidinput(userinput1, userinput2, leftexpert, leftbaby)://for lantern on left side,     check whether the input is only consist of people on left-side, function will detect whether userinput2 contain something
			checkInvalidinput(userinput1, userinput2, rightexpert, rightbaby)//for lantern on right side,check whether the input is only consist of people on right-side, function will detect whether userinput2 contain something
			);

		
		movepeople(userinput1, userinput2 ,leftexpert, leftbaby, rightexpert, rightbaby, side);//move the player

	
		side=(side == 1) ? 2 : 1;//switch the lantern side
	
		
	} while (continuegame(leftexpert, leftbaby, rightexpert, rightbaby));//check whether bomb goes off

	system("cls");
	printgame(leftexpert, leftbaby, rightexpert, rightbaby, side);
	if (strlen(rightexpert) + strlen(rightbaby) == 6)
	{ cout << "\n\nCongratuation!\n\n"; }
	else
	cout << "\n\nYou lose. Haha\n\n\n\n";
	system("PAUSE");
	exit(0);
	
	return 0;//end of main function

}


void printgame(char leftexpert[],char leftbaby[],char rightexpert[],char rightbaby[], int side) {
	cout << "Welcome\n";
	cout << "EXPERT: Kevin Jerry Carl \t\t\tNEWBIES: Dave Stuart Bob\n\n";
	cout << "Lantern is now on  " << ((side == 1) ? "LEFT" : "RIGHT")<< "  side\n\n"; 
	cout << leftexpert << "\t\t\t\t" << rightexpert<<endl;
	cout << leftbaby << "\t\t\t\t" << rightbaby<<"\n\n\n\n\n";
}

bool continuegame(char a[], char b[],char  c[],char d[]){
 
	if ((strlen(a) < strlen(b))&&(strlen(a)>0)) return false;
	if ((strlen(c) < strlen(d))&&(strlen(c)>0)) return false;
	if (strlen(c)+ strlen(d)==6) return false;
	return true;


}

bool checkInvalidinput(char input1, char input2, char expertOnAnySide[], char babyOnAnySide[]) //return true if invalid

{  
	
	if (input1 == input2) { cout << "Please don't duplicate input please ^_^ \n\n"; return true; }
	
	char combineTwoGroup[7] = {};//size three for expert    size three for baby   size one for null terminator
	strcpy(combineTwoGroup, expertOnAnySide);
	strcat(combineTwoGroup, babyOnAnySide);
	
	
	
	//checking input 1
	bool inputfound=false;
	for (int i = 0; i < strlen(combineTwoGroup); i++) {
		if (input1 == combineTwoGroup[i]) { inputfound = true; }
	}
	if (inputfound == false) { cout << "The first char is not valid!   Please try again\n\n"; return true; }
	//checking input 1 end
	


	inputfound = false; //reset the indicator
	

	if (input2 == ' ') { return false; }//if player only want to move one player , no need to check the second input

	//checking input 2 
    for (int i = 0; i < strlen(combineTwoGroup); i++) {
		//cout << "beforeDebug " <<i << inputfound<<endl;
		if (input2 == combineTwoGroup[i]) { inputfound = true; }
		//cout << "afterDebug " <<i << inputfound << endl;
	}
	if (inputfound == false) { cout << "The second char is not valid!   Please try again\n\n"; return true; }
	//checking input 2 end
	
	
	return false;   // input is valid  
}



void movepeople(char input1, char input2, char leftexpert[], char leftbaby[], char rightexpert[], char rightbaby[],int side) {

	switch (side) {
	case 1:
		   if (input1 == 'K' || input1 == 'J' || input1 == 'C') { concat(rightexpert, input1); }
		   else{ concat(rightbaby, input1); }
	
		 
		  
		  
		   deletelocation(input1, leftexpert);
		    
		   deletelocation(input1, leftbaby);

		   if (input2 != ' ') {
			  if (input2 == 'K' || input2 == 'J' || input2 == 'C') { concat(rightexpert, input2); }
			   else { concat(rightbaby, input2); }
			   deletelocation(input2, leftexpert);

			   deletelocation(input2, leftbaby);

		   }


		   break;
	
	
	case 2:if (input1 == 'K' || input1 == 'J' || input1 == 'C') 
	                   {concat(leftexpert, input1);}
		   else { concat(leftbaby, input1); }

		   deletelocation(input1, rightexpert);

		   deletelocation(input1, rightbaby);
		   if (input2 != ' ') {
			   if (input2 == 'K' || input2 == 'J' || input2 == 'C') { concat(leftexpert, input2); }
			   else { concat(leftbaby, input2); }
			   deletelocation(input2, rightexpert);

			   deletelocation(input2, rightbaby);

		   }

	
	
	
	}

	

}



void concat(char a[], char b) {
	a[strlen(a)] = b;
	a[strlen(a) + 1] = '\0';
}


void deletelocation(char input, char array[]) {
	int temp = strlen(array);
	for (int i = 0; i < temp; i++) {
		
		if (input== array[i]) {
			array[i] = '\0';

			for (int j = i; j < temp - 1; j++) {
				char temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}

	}

}