////GAME HAS THE FOLOWING SPECIAL FEATURES:
//	IT HAS 4 MONSTERS MOVING RANDOMLY. 
//	IT HAS A ESCAPE DOOR.
//	THE GAME IS COLORED.
//	GAME HAS START AND KILL SOUNDS


#include<iostream>
#include <stdlib.h>		// TO USE CLEAR SCREEN FUNCTION
#include<conio.h>		//TO USE _getch() FUNCTION
#include<time.h>		//TO USE SYSTEM'S TIME AS A SEED FOR SRAND
#include<Windows.h>		// FOR COLOR FUNCTION
#include <mmsystem.h>   // FOR SOUND FUNCTION

using namespace std;

int Background = 0;
void Color(string color)
//DEFINING COLORS USING HEADER Windows.h
{
	int colorNum;
	if (color == "White") colorNum = 15;
	else if (color == "Red") colorNum = 12;
	else if (color == "Cyan") colorNum = 11;
	else if (color == "Yellow") colorNum = 7;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (colorNum + (Background * 16)));
}
void movesDefine(char Table[26][50], char input, int& positionRowOfPacMan, int& positionColoumnOfPacMan, int& score)
//MOVES THE PACMAN
{
	if ((input == 'a' || input == 'A') && ((Table[positionRowOfPacMan][positionColoumnOfPacMan - 1] != '_') && (Table[positionRowOfPacMan][positionColoumnOfPacMan - 1] != '#') && (Table[positionRowOfPacMan][positionColoumnOfPacMan - 1] != '|')))
	{
		Table[positionRowOfPacMan][positionColoumnOfPacMan] = ' ';
		positionColoumnOfPacMan = positionColoumnOfPacMan - 1;
		if (Table[positionRowOfPacMan][positionColoumnOfPacMan] == '.')
		{
			score++;
		}
	}
	else if ((input == 'd' || input == 'D') && ((Table[positionRowOfPacMan][positionColoumnOfPacMan + 1] != '_') && (Table[positionRowOfPacMan][positionColoumnOfPacMan + 1] != '#') && (Table[positionRowOfPacMan][positionColoumnOfPacMan + 1] != '|')))
	{
		Table[positionRowOfPacMan][positionColoumnOfPacMan] = ' ';
		positionColoumnOfPacMan = positionColoumnOfPacMan + 1;
		if (Table[positionRowOfPacMan][positionColoumnOfPacMan] == '.')
		{
			score++;
		}
	}
	else if ((input == 'w' || input == 'W') && ((Table[positionRowOfPacMan - 1][positionColoumnOfPacMan] != '_') && (Table[positionRowOfPacMan - 1][positionColoumnOfPacMan] != '#') && (Table[positionRowOfPacMan - 1][positionColoumnOfPacMan] != '|')))
	{
		Table[positionRowOfPacMan][positionColoumnOfPacMan] = ' ';
		positionRowOfPacMan = positionRowOfPacMan - 1;
		if (Table[positionRowOfPacMan][positionColoumnOfPacMan] == '.')
		{
			score++;
		}
	}
	else if ((input == 's' || input == 'S') && ((Table[positionRowOfPacMan + 1][positionColoumnOfPacMan] != '_') && (Table[positionRowOfPacMan + 1][positionColoumnOfPacMan] != '#') && (Table[positionRowOfPacMan + 1][positionColoumnOfPacMan] != '|')))
	{
		Table[positionRowOfPacMan][positionColoumnOfPacMan] = ' ';
		positionRowOfPacMan = positionRowOfPacMan + 1;
		if (Table[positionRowOfPacMan][positionColoumnOfPacMan] == '.')
		{
			score++;
		}
	}
	else
	{
		cout << "wrong key";
	}


	Table[positionRowOfPacMan][positionColoumnOfPacMan] = 'C';
}
int monsterRandomControl(int& positionRowOfMonster, int& positionColoumnOfMonster, int& positionRowOfPacMan, int& positionColoumnOfPacMan, int coloumnClone, int rowClone, int randomControlInteger)
{
	if (randomControlInteger == 1 || randomControlInteger == 4)
	{
		if (positionColoumnOfPacMan >= positionColoumnOfMonster)
		{
			if ((positionColoumnOfPacMan - positionColoumnOfMonster) > (positionColoumnOfPacMan - coloumnClone))
			{
				return 1;
			}
		}
		else if (positionColoumnOfMonster >= positionColoumnOfPacMan)
		{
			if ((positionColoumnOfMonster - positionColoumnOfPacMan) > (coloumnClone - positionColoumnOfPacMan))
			{
				return 1;
			}
		}
	}
	else if (randomControlInteger == 2 || randomControlInteger == 3)
	{
		if (positionRowOfPacMan >= positionRowOfMonster)
		{
			if ((positionRowOfPacMan - positionRowOfMonster) > (positionRowOfPacMan - rowClone))
			{
				return 1;
			}
		}
		else if (positionRowOfPacMan <= positionRowOfMonster)
		{
			if ((positionRowOfMonster - positionRowOfPacMan) > (rowClone - positionRowOfPacMan))
			{
				return 1;
			}
		}
	}
	else return 0;
}
int monsterMoveCheck(char Table[26][50], int& positionRowOfMonster, int& positionColoumnOfMonster, char& value, char& temp,int& positionRowOfPacMan, int& positionColoumnOfPacMan)
//CHECKS THAT THE NEW POSITION OF MONSTER HAS FOOD ON IT OR NOT. BY USING THIS FUNCTION THE MONSTER DOESNOT CREATE NEW FOOD POINTS
{
	
	int rowClone = positionRowOfMonster;
	int coloumnClone = positionColoumnOfMonster;
	char input;
	const char Monst[4] = { 'w','a','s','d' };
	int check = 0;
	int RandIndex;
	int RandomControlInteger;
	while (check != 1)
	{
		RandIndex = rand() % 4;
		input = Monst[RandIndex];

		if (input == 'a') { coloumnClone = coloumnClone - 1; RandomControlInteger = 1; }
		else if (input == 'w') { rowClone = rowClone - 1; RandomControlInteger = 2; }
		else if (input == 's') { rowClone = rowClone + 1; RandomControlInteger = 3; }
		else if (input == 'd') { coloumnClone = coloumnClone + 1;  RandomControlInteger = 4; }
		check = monsterRandomControl(positionRowOfMonster, positionColoumnOfMonster, positionRowOfPacMan, positionColoumnOfPacMan, coloumnClone, rowClone, RandomControlInteger);
		if (check == 0 && input == 'a') { coloumnClone = coloumnClone + 1; }
		else if (check == 0 && input == 'w') { rowClone = rowClone + 1; }
		else if (check == 0 && input == 's') { rowClone = rowClone - 1; }
		else if (check == 0 && input == 'd') { coloumnClone = coloumnClone - 1; }

	}
	if (Table[rowClone][coloumnClone] == '.')
	{
		temp= '.';
	}
	else if (Table[rowClone][coloumnClone] == 'C')
	{
		temp = 'C';
	}
	else if (Table[rowClone][coloumnClone] == ' ')
	{
		temp = ' ';
	}
	return RandIndex;
}
void monsterMove(char Table[26][50], int& positionRowOfMonster, int& positionColoumnOfMonster, char& value,int monsterSelection[4][2], int i, int positionRowOfPacMan, int positionColoumnOfPacMan, int& check)
//MOVES THE MONSTER USING RANDOM FUNCTION. ABOVE FUNCTION IS ALSO CALLED IN IT TO CHECK THE NEW POSITION OF MONSTER
{
	char temp;
	char input;
	const char Monst[4] = { 'w','a','s','d' };
	int RandIndex = monsterMoveCheck(Table, positionRowOfMonster, positionColoumnOfMonster, value, temp, positionRowOfPacMan, positionColoumnOfPacMan);
	input = Monst[RandIndex];
	if ((input == 'a') && ((Table[positionRowOfMonster][positionColoumnOfMonster - 1] != '_') && (Table[positionRowOfMonster][positionColoumnOfMonster - 1] != '#') && (Table[positionRowOfMonster][positionColoumnOfMonster - 1] != '|')))
	{

		Table[positionRowOfMonster][positionColoumnOfMonster] = value;
		positionColoumnOfMonster = positionColoumnOfMonster - 1;
		value = temp;
	}
	else if ((input == 'd') && ((Table[positionRowOfMonster][positionColoumnOfMonster + 1] != '_') && (Table[positionRowOfMonster][positionColoumnOfMonster + 1] != '#') && (Table[positionRowOfMonster][positionColoumnOfMonster + 1] != '|')))
	{

			Table[positionRowOfMonster][positionColoumnOfMonster] = value;
			positionColoumnOfMonster = positionColoumnOfMonster + 1;
			value = temp;
	}
	else if ((input == 'w') && ((Table[positionRowOfMonster - 1][positionColoumnOfMonster] != '_') && (Table[positionRowOfMonster - 1][positionColoumnOfMonster] != '#') && (Table[positionRowOfMonster - 1][positionColoumnOfMonster] != '|')))
	{

		Table[positionRowOfMonster][positionColoumnOfMonster] = value;
		positionRowOfMonster = positionRowOfMonster - 1;
		value = temp;
	}
	else if ((input == 's') && ((Table[positionRowOfMonster + 1][positionColoumnOfMonster] != '_') && (Table[positionRowOfMonster + 1][positionColoumnOfMonster] != '#') && (Table[positionRowOfMonster + 1][positionColoumnOfMonster] != '|')))
	{

		Table[positionRowOfMonster][positionColoumnOfMonster] = value;
		positionRowOfMonster = positionRowOfMonster + 1;
		value = temp;
	}
	if ((positionRowOfMonster == positionRowOfPacMan) && (positionColoumnOfMonster == positionColoumnOfPacMan))
	{
		check = 0;
		return;
	}
	Table[positionRowOfMonster][positionColoumnOfMonster] = '@';
	int j = 0;
	monsterSelection[i][j] = positionRowOfMonster;
	j++;
	monsterSelection[i][j] = positionColoumnOfMonster;
}
int checkKill(int& positionRowOfMonster, int& positionColoumnOfMonster, int& positionRowOfPacMan, int& positionColoumnOfPacMan)
// THIS FUNCTION CHECKS IF MONSTER AND PACMAN ARE ON SAME POSITION
{
	if ((positionRowOfMonster == positionRowOfPacMan) && (positionColoumnOfMonster == positionColoumnOfPacMan))
	{
		return 0;
	}
	return 1;
}
int checkFood(char Table[26][50])
{
	int counter = 0;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (Table[i][j] == '.')
				return 1;
		}
	}
	return 0;
}
int main()
{
	char playAgain;
	int playyAgain = 1;

	srand(time(NULL));
	while (playyAgain == 1)
	{
		char Table[26][50] =
		{
			{'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},
			{'|','C','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.','.','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','@','.','.','.','.','.','#','.','.','.','.','.','.','|','.','.','J',' ','A',' ','F',' ','F',' ','E',' ','R',' ','Y','.','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','@','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.','.','|','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.','.','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.',' ','.','.','.','.','.','.','.','.','|','|','|','.','.','.','.','.','.','.','.',' ','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','|','.','#','#','#','#','#','.',' ','.','.','.','.','.','.','.','.','|','|','|','.','.','.','.','.','.','.','.',' ','.','#','#','#','#','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','.','.','.','.','|','.','.','#','#','#','#','#','.','|','|','|','.','#','#','#','#','#','.','.','|','.','.','.','.','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','.','.','|','.','|','.','.','.','.','.','.','.','.','|','|','|','.','.','.','.','.','.','.','.','|','.','|','.','.','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','|','.','|','.','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','.','|','.','|','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','|','.','|','.','|','.','.','.','|',' ','#','#','#','#','#','#','#','#','#',' ','|','.','.','.','|','.','|','.','|','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.',' ','.','|','.','|','.','|','.','.','.','|',' ','.',' ',' ',' ','.',' ',' ',' ','.',' ','|','.','.','.','|','.','|','.','|','.',' ','.','|','.','.','.','.','.','.','.',' '},
			{' ','.','.','.','.',' ','.','.','.','.','.','.','.','.','.','.','.',' ',' ',' ','P','A','C','-','M','A','N',' ',' ',' ','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.',' ','.','|','.','|','.','|','.','.','.','|',' ','.',' ',' ',' ','.',' ',' ',' ','.',' ','|','.','.','.','|','.','|','.','|','.',' ','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','|','.','|','.','|','.','.','.','|','.','#','#','#','#','#','#','#','#','#','.','|','.','.','.','|','.','|','.','|','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','|','.','|','.','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','.','|','.','|','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','.','.','|','.','|','.','.','.','.','.','.','.','.','|','|','|','.','.','.','.','.','.','.','.','|','.','|','.','.','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.',' ','.','|','.','#','.','.','.','.','.','|','.','.','#','#','#','#','#','.','|','|','|','.','#','#','#','#','#','.','.','|','.','.','.','.','.','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','|','.','#','#','#','#','#','.',' ','.','.','.','.','.','.','.','.','|','|','|','.','.','.','.','.','.','.','.',' ','.','#','#','#','#','#','.','|','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.',' ','.','.','.','.','.','.','.','.','|','|','|','.','.','.','.','.','.','.','.',' ','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.','.','|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','@','.','.','.','.','.','#','.','.','.','.','.','.','|','.','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','@','|'},
			{'|','.','.','.','.','.','.','#','.','.','.','.','.','.','|','.','.','L','-','1',' ','9',' ','0',' ','9',' ','1',' ','0','.','.','|','.','.','.','.','.','.','#','.','.','.','.','.','.','.','.','.','|'},
			{'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|'},
			{'|','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','|'}

		};
		cout << "loading.....3...2...1" << endl;
		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (Table[i][j] == '.')
				{
					Color("Cyan"); cout << Table[i][j];
				}
				else if (Table[i][j] == '@')
				{
					Color("Red"); cout << Table[i][j];
				}
				else
				{
					Color("White"); cout << Table[i][j];
				}
			}
			cout << endl;
		}
		PlaySound(TEXT("pac-man-intro-music.wav"), NULL, SND_SYNC);
		cout << "Go!";
		int monsterSelection[4][2] =
		{
			{3, 1},
			{3, 48},
			{22,1},
			{22,48}
		};
		
		char input;
		int positionRowOfPacMan = 1;
		int positionColoumnOfPacMan = 1;
		int positionRowOfMonster;
		int positionColoumnOfMonster;
		int check = 1;
		int check2 = 1;
		int score = 0;
		int j = 0;
		while (check != 0 && check2 != 0)
		{
			
			
			input = _getch();
			movesDefine(Table, input, positionRowOfPacMan, positionColoumnOfPacMan, score);
			

			for (int i = 0; i < 4; i++)
			{
				char value = '.';
				j = 0;
				positionRowOfMonster = monsterSelection[i][j];
				j = j + 1;
				positionColoumnOfMonster = monsterSelection[i][j];
				j = 0;
				check = checkKill(positionRowOfMonster, positionColoumnOfMonster, positionRowOfPacMan, positionColoumnOfPacMan);
				if (check == 0)
				{
					Table[positionRowOfPacMan][positionColoumnOfPacMan] = 'X';
					break;
				}
				monsterMove(Table, positionRowOfMonster, positionColoumnOfMonster, value, monsterSelection, i, positionRowOfPacMan, positionColoumnOfPacMan, check);
				Table[positionRowOfPacMan][positionColoumnOfPacMan] = 'C';
				check = checkKill(positionRowOfMonster, positionColoumnOfMonster, positionRowOfPacMan, positionColoumnOfPacMan);
				if (check == 0)
				{
					Table[positionRowOfPacMan][positionColoumnOfPacMan] = 'X';
					break;
				}
			}
			check2 = checkFood(Table);
			system("CLS");
			cout << "Score: " << score << endl;

			for (int i = 0; i < 26; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					if (Table[i][j] == '.')
					{
						Color("Cyan"); cout << Table[i][j];
					}
					else if (Table[i][j] == '@')
					{
						Color("Red"); cout << Table[i][j];
					}
					else
					{
						Color("White"); cout << Table[i][j];
					}
				}
				cout << endl;
			}
		}

		if (score == 646)
		{
			cout << "You Win!";
		}
		else
		{
			cout << "Game Over! ";
		}
		cout << endl << "Your Score Is: " << score;
		PlaySound(TEXT("pacman-death-sound-effect.wav"), NULL, SND_SYNC);
		
		cout << endl << "Press 'Y' to Play Again or 'Q' to Quit ";
		playAgain = _getch();
		if (playAgain == 'y' || playAgain == 'Y')
		{
			playyAgain = 1;
			system("CLS");
		}
		else if (playAgain == 'q' || playAgain == 'Q')
		{
			playyAgain = 0;
		}
		
	}
	cout << endl << "THANKYOU!" << endl << endl;

}
