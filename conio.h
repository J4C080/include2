// conio 2.2.4

#include <windows.h>

typedef enum
{
   BLACK, BLUE, GREEN, CYAN,
   RED, MAGENTA, BROWN, LIGHTGRAY,
   DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
   LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
}
COLORS;

// enum text_modes { LASTMODE = -1, BW40 = 0,  C40, BW80, C80, MONO = 7,  C4350 = 64 };

short xwin = 25, ywin = 80;

struct text_info
{
	unsigned char winleft;        /* left window coordinate */
    unsigned char wintop;         /* top window coordinate */
    unsigned char winright;       /* right window coordinate */
    unsigned char winbottom;      /* bottom window coordinate */
    unsigned char attribute;      /* text attribute */
    // unsigned char normattr;       /* normal attribute */
    // unsigned char currmode;       /* BW40, BW80, C40, C80, or C4350 */
    unsigned char screenheight;   /* text screen's height */
    unsigned char screenwidth;    /* text screen's width */
    unsigned char curx;           /* x-coordinate in current window */
    unsigned char cury;           /* y-coordinate in current window */
}
vActual = {0, 0, 79, 24, WHITE,/* WHITE, C80,*/ xwin, ywin, 1, 1};

//______________________________________________________________________________
// Posicionar cursor en las coordenadas dentro de una ventana definida anteriormente
void gotoxy (int x, int y)
{
    COORD dwPos;
    if (x < 1 || x > vActual.screenwidth ||
        y < 1 || y > vActual.screenheight) return;
    vActual.curx = x;
    vActual.cury = y;
    dwPos.X = vActual.winleft + x - 1;
    dwPos.Y = vActual.wintop + y - 1;

    SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), dwPos);
}

//______________________________________________________________________________
void clrscr ()
{
   DWORD escrito;
   for (int i = 0; i < vActual.screenheight; i++)
   {
      FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
         vActual.attribute, vActual.screenwidth,
         (COORD) {vActual.winleft, vActual.wintop+i}, &escrito);
      FillConsoleOutputCharacter (GetStdHandle (STD_OUTPUT_HANDLE), ' ',
         vActual.screenwidth,
         (COORD) {vActual.winleft, vActual.wintop+i}, &escrito);
   }
   gotoxy (vActual.curx, vActual.cury);
}

//______________________________________________________________________________
void window (int left, int top, int right, int bottom)
{
   vActual.winleft   = left-1;
   vActual.wintop    = top-1;
   vActual.winright  = right-1;
   vActual.winbottom = bottom-1;
   vActual.screenheight = 1+bottom-top;
   vActual.screenwidth  = 1+right-left;
   vActual.curx = 1;
   vActual.cury = 1;
   clrscr ();
}

//______________________________________________________________________________
void textcolor (int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}
//______________________________________________________________________________
void textbackground (int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

//______________________________________________________________________________
int getch(void)
{
   int car;
   DWORD leidos, modo;
   GetConsoleMode (GetStdHandle (STD_INPUT_HANDLE), &modo);
   SetConsoleMode (GetStdHandle (STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT & !ENABLE_PROCESSED_INPUT);
   ReadConsole (GetStdHandle (STD_INPUT_HANDLE), &car, 1, &leidos, NULL);
   SetConsoleMode (GetStdHandle (STD_INPUT_HANDLE), modo);
   return car;
}

//______________________________________________________________________________
// int kbhit(void)
// {
//    DWORD nEventos;
//    INPUT_RECORD *eventos;
//    DWORD leidos;
//    int retval = 0, i;
//    GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &nEventos);
//    eventos = (INPUT_RECORD *)malloc(nEventos*sizeof(INPUT_RECORD)); // eventos = new INPUT_RECORD[nEventos];
//    PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), eventos, nEventos, &leidos);
//    for(i = 0;  i < nEventos; i++)
//       if(eventos[i].EventType == KEY_EVENT && eventos[i].Event.KeyEvent.bKeyDown) retval = 1;
//    free( eventos ); // delete[] eventos;
//    return retval;
// }
