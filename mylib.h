// mylib 4.19.34

#include "color.h"
#include "conio.h"
#include <sstream>

short xwin, ywin;

/*______________________________________________________________________________
VENTANA
______________________________________________________________________________*/


//______________________________________________________________________________
void pause (long x = 0)
{
	if (!x) getch ();
	else Sleep (x);
}

//______________________________________________________________________________
// Mostrar u ocultar cursor en la consola
void cursor (string str)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	if (str == "show")  cci.bVisible = true;
	else if (str == "hide") cci.bVisible = false;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cci);
}

//______________________________________________________________________________
int finish (void)
{
	cursor ("hide");
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 17*colf);
	ShowWindow (GetForegroundWindow (), SW_HIDE);
	return 0;
}

//______________________________________________________________________________
// Dibujar una marco en la consola
void frame (void)
{
	short winheight = vActual.screenheight;
	short winwidth = vActual.screenwidth;

	for (short i = 1; i <= winheight; i++)
	{
		gotoxy (1, i); cout << (char)179;
		gotoxy (winwidth, i); cout << (char)179;
	}
	for (short i = 1; i <= winwidth; i++)
	{
		gotoxy (i, winheight); cout << (char)196;
		gotoxy (i, 1); cout << (char)196;
	}

	gotoxy (1, 1); cout << (char)218;
	gotoxy (winwidth, 1); cout << (char)191;
	gotoxy (1, winheight); cout << (char)192;
	gotoxy (winwidth, winheight); cout << (char)217;
}

//______________________________________________________________________________
// Crear una ventana dentro de la consola
void defineWindow (short left, short top, short right, short bottom, short colf1, short colt1, short colt2 = CYAN)
{
	window (left, top, right, bottom);
	textbackground (colf1);
	textcolor (colt1);
	clrscr ();
	frame ();
	setcolors (colf1, colt1, colt2);
}

/*______________________________________________________________________________
NUMEROS
______________________________________________________________________________*/


//______________________________________________________________________________
// Convertir una string en entero
int stoI (string str) { return atoi (str.c_str ()); }

// Convertir una string en entero largo
long stoL (string str) { return atol (str.c_str ()); }

// Convertir una string en real
double stoF (string str) { return atof (str.c_str ()); }

// Valor absoluto de un entero
int abs (int num) { return num < 0? -num : num; }

//______________________________________________________________________________
double power (double base, double exp)
{
	double pot = 1;
	for (int i = 0; i < exp; i++) pot *= base;
	return pot;
}

//______________________________________________________________________________
// Aproximar un numero por exceso
double aproxexc (double num, short dec)
{
	double x = power (10, dec), aux = (int)(num*x+1);
	
	return (double)(num > aux && num < aux+1? (num*x+1) : num*x)/x;
}

//______________________________________________________________________________
// Aproximar un numero segun los decimales solicitados
double aprox (double num, short dec)
{
	double x = power (10, dec), aux = (int)(num*x+1);
		
	return (double)(num > aux && num < aux+0.5? (int)(num*x) : (int)(num*x+1))/x;
}

//______________________________________________________________________________
// Calcular factorial de un numero
unsigned long long fact (int n)
{
	unsigned long long f = 1;
	for (int i = 1; i <= n ; i++) f = i*f;
	return f;
}

//______________________________________________________________________________
// Ordenar un arreglo con el metodo BubbleSort
void bubbleSort (int*arr, int ele)
{
  int i, j, tmp;
  for (i = 0; i < ele; i++)
    for (j = i+1; j < ele; j++)
      if (arr[i] > arr[j])
      {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
}

//______________________________________________________________________________
// Ordenar un arreglo con el metodo de insercion
void insertionsort (int*arr, int ele)
{
	int i, pos, aux;
	for (i = 0; i < ele; i++)
	{
		pos = i;
		aux = arr[i];
		while (pos > 0 && arr[pos-1] > aux)
		{
			arr[pos] = arr[pos-1];
			pos--;
		}
		arr[pos] = aux;
	}
}

//______________________________________________________________________________
// Ordenar un arreglo con el metodo de seleccion
void selectionsort (int*arr, int ele)
{
	int i, j, aux, min;
	for (int i = 0; i < ele; i++)
	{
		min = i;
		for (int j = i+1; j < ele; j++)
		  if (arr[j] < arr[min])
				min = j;
		aux = arr[i];
		arr[i] = arr[min];
		arr[min] = aux;
	}
}

//______________________________________________________________________________
// Ordenar un arreglo con el metodo QuickSort
void quickSort (int*arr, int izq, int der)
{
  int itr = izq, jtr = der, tmp;
  int piv = arr[(izq+der)/2];

  while (itr <= jtr)
  {
    while (arr[itr] < piv) itr++;
    while (arr[jtr] > piv) jtr--;

    if (itr <= jtr)
    {
      tmp = arr[itr];
      arr[itr] = arr[jtr];
      arr[jtr] = tmp;
      itr++;
      jtr--;
    }
  }

  if (izq < jtr) quickSort (arr, izq, jtr);
  if (itr < der) quickSort (arr, itr, der);
}

//______________________________________________________________________________
// Generar un numero aleatorio
int random (int lim_i, int lim_s) { return (lim_i + rand()% (lim_s + 1 - lim_i)); }

/*______________________________________________________________________________
TEXTO
______________________________________________________________________________*/


//______________________________________________________________________________
// Centar texto tomando en cuenta el tamano de la ventana y la cadena
int centerText (short y, string txt, short tx = scolt, short exc = 0)
{
	int tam_c = txt.size () - exc;
	int pos_x = (tam_c < vActual.screenwidth? (vActual.screenwidth - tam_c)/2 : 0)+1;

	gotoxy (pos_x, y); cprintf (txt, tx);
	return pos_x;
}

//______________________________________________________________________________
// Mostrar mensaje de error
bool warning (short y, string err, short exc = 0)
{
	err = "\\ERROR: *\\" + err + "\\*";
	
	short i, pos = centerText (y, err, 12, exc+3);
	
	getch ();

	gotoxy (pos, y);
	for (i = 0; i < err.size (); i++)
		cout << ' ';

	return false;
}

//______________________________________________________________________________
// Convertir una variable de cualquier tipo en string
template <typename mytype> string s (mytype var)
{
	stringstream ss;
	ss << var;
	return ss.str();
}

//______________________________________________________________________________
// Determinar el tamano de la consola
void sizeWindow (short x, short y)
{
	system (("mode con: cols=" + s (x+1) + " lines=" + s (y)).c_str ());
}

//______________________________________________________________________________
// Retornar una cadena cortada respecto a otra
string substr (string source, int from, int to)
{
	string aux = "";
	for (int i = from; i <= to; i++) aux += source[i];
	return aux;
}

//______________________________________________________________________________
// Retornar una cadena quitandole espacios innecesarios
string removeSpaces (string str)
{
	for (short i = 0; i < str.size (); i++)
		while (str[0] == 32 || str[str.size ()-1] == 32 || str[i] == 32 && str[i+1] == 32)
			if (str[0] == 32)
				str = substr (str, 1, str.size ()-1);
			else if (str[str.size ()-1] == 32)
				str = substr (str, 0, str.size ()-2);
			else if (str[i] == 32 && str[i+1] == 32)
				str = substr (str, 0, i) + substr (str, i+2, str.size ()-1);
	return str;
}

//______________________________________________________________________________
// Borrar el ultimo caracter de un string
string pop_back (string str) { return str.substr (0, str.size()-1); }

//______________________________________________________________________________
unsigned char toUpper (unsigned char);
unsigned char toLower (unsigned char);

// String a mayusculas
string uppercase (string str) 
{
	for (short i = 0; i < str.size(); i++)
		if (str[i] >= 'a' && str[i]<='z')
			str[i] = toUpper (str[i]);
	return str;
}

//______________________________________________________________________________
// String a minusculas
string lowercase (string str) 
{
	for (short i = 0; i < str.size(); i++)
		if (str[i] >= 'A' && str[i]<='Z')
			str[i] = toLower (str[i]);
	return str;
}

//______________________________________________________________________________
bool istext (string str)
{
	for (short i = 0; i < str.size (); i++)
	    if (!isalpha (str[i]))
			return false;
	return true;
}

//______________________________________________________________________________
bool isnumber (string str)
{
	for (short i = 0; i < str.size (); i++)
	    if (!isdigit (str[i]))
			return false;
	return true;
}

/*______________________________________________________________________________
CARACTERES
______________________________________________________________________________*/

//______________________________________________________________________________
bool isaccent (unsigned char kar)
{
	return
	kar == 160 || kar == 130 || kar == 161 || kar == 162 || kar == 163 || // tildes minusculas agudas
	kar == 181 || kar == 144 || kar == 214 || kar == 224 || kar == 233 || // tildes mayusculas agudas
	kar == 133 || kar == 138 || kar == 141 || kar == 149 || kar == 151 || // tildes minusculas graves
	kar == 183 || kar == 212 || kar == 222 || kar == 227 || kar == 235 || // tildes mayusculas graves
	kar == 164 || kar == 165; // n, N
}

//______________________________________________________________________________
unsigned char removeaccent (unsigned char kar)// Vocal tildada a vocal sin tilde
{
	switch (kar)
	{
		case 160: kar = 97; break;  //  -> a
		case 130: kar = 101; break; //  -> e
		case 161: kar = 105; break; //  -> i
		case 162: kar = 111; break; //  -> o
		case 163: kar = 117; break; //  -> u

		case 181: kar = 65; break; //  -> A
		case 144: kar = 69; break; //  -> E
		case 214: kar = 73; break; //  -> I
		case 224: kar = 79; break; //  -> O
		case 233: kar = 85; break; //  -> U
	}
	return kar;
}

//______________________________________________________________________________
unsigned char toUpper (unsigned char kar)
{
	if (isaccent (kar))
		switch (kar)
		{
			case 160: kar = 181; break; // a -> A
			case 130: kar = 144; break; // e -> E
			case 161: kar = 214; break; // i -> I
			case 162: kar = 224; break; // o -> O
			case 163: kar = 233; break; // u -> U
			case 164: kar = 165; break; // n -> N
		}
	else kar = toupper (kar);
	return kar;
}

//______________________________________________________________________________
unsigned char toLower (unsigned char kar)
{
	if (isaccent (kar))
		switch (kar)
		{
			case 181: kar = 160; break; // A -> a
			case 144: kar = 130; break; // E -> e
			case 214: kar = 161; break; // I -> i
			case 224: kar = 162; break; // O -> o
			case 233: kar = 163; break; // U -> u
			case 165: kar = 164; break; // N -> n
		}
	else kar = tolower (kar);
	return kar;
}

//______________________________________________________________________________
// Vocal tildada grave a vocal tildada aguda
unsigned char gtoa (unsigned char kar) 
{
	switch (kar)
	{
		// tildes minusculas graves -> tildes minusculas agudas
		case 133: kar = 160; break;
		case 138: kar = 130; break;
		case 141: kar = 161; break;
		case 149: kar = 162; break;
		case 151: kar = 163; break;
		// tildes mayusculas graves -> tildes mayusculas agudas
		case 183: kar = 181; break;
		case 212: kar = 144; break;
		case 222: kar = 214; break;
		case 227: kar = 224; break;
		case 235: kar = 233; break;
	}
	return kar;
}

/*______________________________________________________________________________
______________________________________________________________________________*/

class type
{
	private:
		short lim; // limite de caracteres
		string add; // cadena de caracteres que almacenara caracteres adicionales
	public:
		short i; // indicador de posicion
		unsigned char key;
		string str; // cadena de caracteres a retornar

		type (int x, string y) { lim = x; add = y; }

		virtual bool showif (void) {}
		virtual void toshow (void) { cvar (key); }

		// incluir caracteres adicionales
		others (void)
		{
			for (int i = 0; i < add.size (); i++)
				if (key == add[i])
					return true;
			return false;
		}

		virtual string capture (void);
};

//______________________________________________________________________________
class integer : private type
{
	private:
		bool negative;
	public:
		integer (int x, bool y = true, string z = "") : type (x, z) { negative = y; };

		bool showif (void)
		{
			return negative?
				isdigit (key) || (key == 45 && str.find ("-") == string::npos && !isdigit (str[0]))
			:
				isdigit (key);
		}
		string capture (void) { return type::capture (); }
};

//______________________________________________________________________________
class floating : private type
{
	private:
		bool negative;
	public:
		floating (int x, bool y = true, string z = "") : type (x, z) { negative = y; }

		bool showif (void)
		{
			return negative?
				isdigit (key) || (key == 45 && str.find ("-") == string::npos && !isdigit (str[0])) ||
				(key == 46 && str.find (".") == string::npos && (isdigit (str[0]) || (str[0] == 45 && isdigit (str[1]))))
			:
				isdigit (key) || key == 46 && str.find (".") == string::npos && isdigit (str[0]);
		}
		string capture (void) { return type::capture (); }
};

//______________________________________________________________________________
class text : private type
{
	private:
		bool uppercase;
	public:
		text (int x, bool y = true, string z = "") : type (x, z) { uppercase = y; };

		bool showif (void) { return isalpha (key) || key == 32 || isaccent (key); }
		void toshow (void)
		{
			key = gtoa (key);

			key = uppercase && (i == 0 || str[i-1] == ' ')? toUpper (key) : toLower (key);
			cout << key;
		}
		string capture (void) { return type::capture (); }
};

string type::capture (void)
{
	i = 0;
	str.clear ();
	do
	{
		key = getch ();
		if (key == 8)
		{
			if (i > 0)
			{
				cout << "\b \b";
				str = pop_back (str);
				i--;
			}
		}
		else if ((showif () || others ()) && i < lim) // condicion que depende del tipo, caracteres adicionales y limite
		{
			toshow ();
			str.push_back (key);
			i++;
		}
	}
	while (key != 13 || str.empty ()); // hasta que presione enter y la cadena tenga contenido
	return str;
}
