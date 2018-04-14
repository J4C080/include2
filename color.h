// color 4.0.4

#include <windows.h>
#include <iostream>
using namespace std;

short colf = 0, pcolt = 15, scolt = 15;

bool isaccent (unsigned char);

void setcolors (short bg, short tx1, short tx2)
{
	while (bg > 15) bg -= 16;
	while (tx1 > 15) tx1 -= 16;
	while (tx2 > 15) tx2 -= 16;
	colf = bg;
	pcolt = tx1;
	scolt = tx2;
}

//______________________________________________________________________________
// Color de fondo y de texto para mostrar una variable
template <typename mytype> void cvar (mytype var, short tx = scolt)
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 16*colf + tx);
	cout << var;
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 16*colf + pcolt);
}

//______________________________________________________________________________

void cprintf (string str, short tx = scolt)
{
	bool color = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		while (i < str.size() && (str[i] != '\\' && str[i] != '\"'))
		{
			if (color)
				if (str[i] == '*')
					cvar (str[i], 12);
				else
					cvar (str[i], tx);
			else
				if (!isalnum (str[i]) && !isaccent (str[i]) && !isspace (str[i]))
					cvar (str[i], scolt);
				else
					cout << str[i];
			i++;
		}
		color = !color;
	}
}

/*
viod mycprintf (string str, short tx = scolt)
{
	bool color = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		while (i < str.size() && (str[i] != '\\' && str[i] != '\"'))
		{
			if (color) cvar (str[i], tx);
			else cout << str[i];
			i++;
		}
		color = !color;
	}
}
*/
