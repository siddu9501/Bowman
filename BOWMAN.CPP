#include <fstream.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int play = 0, comp = 1, vit = 2, index = 1, wall = 0, wind = 1, windVal = 0;
int titleC=15, selectedC=15, textC=15, arrowC=15, fold = 15, BG = 9, back = 1;
int helpTitle = 1, helpText = 6, helpFoot = 7, helpAbstract = 5, helpFold = 7;

void main ();

void backGround ( int c = fold )	{
	setfillstyle ( 1, c );
	arc ( 100, 100, 90, 180, 100 );
	floodfill ( 10, 10, getcolor () );
	arc ( getmaxx() - 100, getmaxy() - 100, 270, 360, 100 );
	floodfill ( getmaxx() - 10, getmaxy() - 10, getcolor () );
}

void theme ( int c )	{
	if ( back == 1 )	{
		titleC = 4; 	selectedC = 14;	textC = 1;
		arrowC = 8;	fold = 15;	BG = 9;

		helpTitle = 1;	helpText = 6;	helpFoot = 7;
		helpAbstract = 5;		helpFold = 7;

		setbkcolor ( BG );
	}
}

void windBar ( )	{
	int w = 10, h = 10, m = 6, x = 80, y = 50;
	setcolor ( WHITE );
	settextjustify ( CENTER_TEXT, CENTER_TEXT );
	settextstyle ( DEFAULT_FONT, VERT_DIR, 1 );
	outtextxy ( 5, y, "Wind" );
	setcolor ( RED );
	rectangle ( x-w*m-4, y-h-4, x+w*m+2, y+h+4 );
	setfillstyle ( 1, BLACK );
	floodfill ( x, y, RED );
	setfillstyle ( 1, YELLOW );
	for ( int i = -m; i < m; i++ )	{
		setcolor ( YELLOW );
		rectangle ( x+w*i, y-h, x+w*(i+1)-2, y+h );
		if ( ( windVal < 0 && windVal <= i && i < 0 ) ||
		     ( windVal > 0 && windVal >= i+1 && i >= 0 ) )
			floodfill ( x+w*i+w/2, y, YELLOW );
	}
//      setlinestyle ( 0, 0, 3 );
	setcolor ( RED );
	line ( x-1, y-h-4, x-1, y+h+4 );
	setlinestyle ( 0, 0, 1 );
}

class arrow 	{
public :
	float x, y, vx, vy;
}arr;

class player	{
public:
	int x, hp, number;
	int hit ();
	void draw ();
}p[2];
void player :: draw ()	{
	float l = 13, y = 352;
	settextjustify ( CENTER_TEXT, CENTER_TEXT );
	settextstyle ( DEFAULT_FONT, HORIZ_DIR, 1 );
	int w = 15, h = 4;
	setcolor ( RED );
	rectangle ( x-w*(vit)/2-4, 300-h-4, x+w*(vit)/2+1, 300+h+4 );
	for ( int i = 0; i < vit; i++ )	{
		setcolor ( YELLOW );
		rectangle ( x-w*(vit-i*2)/2, 300-h, x-w*(vit-2*i-2)/2-3, 300+h );
		if ( i < hp )	{
			setfillstyle ( 1, YELLOW );
			floodfill ( x-w*(vit-i*2)/2+w/4, 300, YELLOW );
		}
	}
	setcolor ( WHITE );
	if ( number == 1 )	{
		outtextxy ( x, y - ( 0.75 * l ), "1" );
		line ( x - 300, 0, x - 300, 400 );
	}
	else if ( number == 2 )	{
		outtextxy ( x, y - ( 0.75 * l ), "2" );
		line ( x + 300, 0, x + 300, 400 );
	}
	circle ( x, y - ( 0.75 * l ), 0.75 * l );
	line ( x, y, x, y + ( 3 * l ) );
	line ( x, y, x + ( 0.75 * l ), y + ( 0.75 * l ) );
	line ( x, y, x - ( 0.75 * l ), y + ( 0.75 * l ) );
	line ( x, y + ( 3 * l ), x + ( 0.75 * l ), y + ( 3 * l ) + ( 0.75 * l ) );
	line ( x, y + ( 3 * l ), x - ( 0.75 * l ), y + ( 3 * l ) + ( 0.75 * l ) );
	setcolor ( WHITE );
	line ( p[0].x-300, 400, p[1].x+300, 400 );
}

int player :: hit () 	{
	if ( comp == -1 )
		return 0;
	if ( x >= getmaxx() / 2 - 15 && x <= getmaxx() / 2 + 15
	     && arr.y > 334 && arr.y < 400 ) 	{
		hp--;
		setcolor ( 4 );
		settextjustify ( CENTER_TEXT, CENTER_TEXT );
		settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 4 );
		char tempC[] = "Player X got hit !";
		tempC[7] = '0' + number;
		outtextxy ( getmaxx()/2, getmaxy()/2, tempC );
		return ( 1 );
	}
	return ( 0 );
}

void arow ( float j, float k )	{
	float l = 50;
	float sint, cost, temp = 0.1;
	while ( temp*temp <= j*j + k*k )
		temp += 1;
	sint=k/temp;
	cost=j/temp;
	asm mov ax,2;
	asm int 0x33;
	line ( getmaxx()/2-(l*cost/2), arr.y-(l*sint/2),
	       getmaxx()/2+(l*cost/2), arr.y+(l*sint/2) );
	line ( getmaxx()/2+(l*0.1*(sint-cost)/1.414),
	       arr.y+(l*0.1*(cost+sint)/1.414),
	       getmaxx()/2-(l*cost/2), arr.y-(l*sint/2) );
	line ( getmaxx()/2+(l*0.1*(cost-sint)/1.414),
	       arr.y+(l*0.1*(sint-cost)/1.414),
	       getmaxx()/2-(l*cost/2), arr.y-(l*sint/2) );
}

void screenmove () 	{
	for ( float i = 0; i < 10000; i += 0.5 ) 	{
		cleardevice ();
		arr.y -= arr.vy * 0.1 - 0.05;
		arr.vy -= 1;
		if ( wind == 1 )
			arr.vx -= wind * ( arr.vx*arr.vx + arr.vy*arr.vy ) * 0.0001;
		arow ( arr.vx, arr.vy );
		p[play % 2].x += arr.vx * 0.1;
		p[( play + 1 ) % 2].x += arr.vx * 0.1;
		p[play % 2].draw ();
		p[( play + 1 ) % 2].draw ();
		if ( i > 5 ) 	{
			if ( arr.y >= 400 || p[0].hit() || p[1].hit() ||
				getmaxx()/2 < p[0].x-300 ||
				getmaxx()/2 > p[1].x+300 )	{
				delay ( 1500 );
				play = ( ++play ) % 2;
				if ( p[0].hp == 0 || p[1].hp == 0 )	{
					settextjustify ( CENTER_TEXT, CENTER_TEXT );
					settextstyle ( GOTHIC_FONT, HORIZ_DIR, 5 );
					setcolor ( 4 );
					cleardevice ();
					outtextxy ( getmaxx()/2, getmaxy()/2, "G A M E   O V E R" );
					delay ( 1000 );
					asm mov ax,2;		asm int 0x33;
					main ();
				}
				break;
			}
		}
		delay ( 50 );
	}
	arr.y = 356;
}

void AI ()	{
	randomize (); randomize ();
	arr.vx = ( 50 + random ( 32 ) );
	float f = 0;
	while ( f*f <= 10000 - arr.vx*arr.vx )
		f += 0.1;
	arr.vy = f;
	screenmove ();
}

void start ()	{
	setbkcolor ( 0 );
	setcolor ( 15 );
	int mx, my, clk, chk = 0;
	play = 0;
	windVal = 0;
	p[0].hp = vit;
	p[1].hp = vit;
	p[1].number = 2;
	p[0].number = 1;
	int maxX=getmaxx() , maxY=getmaxy();
	int fx, fy, lx, ly, temp = 0;
	arr.y = 356;
	randomize();
	int tem = random(400) + 900;
	p[play % 2].x = getmaxx () / 2;
	if ( play == 1 )
		p[( play+1 ) % 2].x = getmaxx() / 2 - tem;
	else
		p[(play + 1 ) % 2].x = tem;
	if ( index == 1 )	{
		gotoxy ( 1, 1 );
		cout<<" Magnitude : 000\t Angle : 000";
	}
	cleardevice();
	p[0].draw ();
	p[1].draw ();
	if  ( wind == 1 )
		windBar ( );
	asm	{
		mov ax,1;
		int 0x33;

		mov ax,7;
		mov cx,0;
		mov dx,maxX;
		int 0x33;

		mov ax,8;
		mov cx,0;
		mov dx,maxY;
		int 0x33;
	}
loop:
	asm mov ax,1;	asm int 0x33;
	asm mov ax,3;	asm int 0x33;
	mx=_CX;
	my=_DX;
	clk=_BX;
	if ( wind == 1 && ++temp == 10 )	{
		randomize ();
		windVal += random(3) - 1;
		if ( windVal == -7 )
			windVal++;
		else if ( windVal == 7 )
			windVal--;
		temp = 0;
		windBar ();
	}

	if ( clk == 1 )	{
		if ( chk == 0 )    {
			fx = mx;
			fy = my;
			chk = 1;
		}
		asm mov ax,2; 		asm int 0x33;
		arr.vx = (mx-fx)/5.0;
		arr.vy = (my-fy)/5.0;
		int sq = 0;
		while ( sq*sq < (arr.vx*arr.vx)+(arr.vy*arr.vy) )
			sq += 1;
		float ang;
		if ( arr.vx == 0 )
			ang = 90;
		else
			ang = 180 - atan2 ( arr.vy, arr.vx ) * 180 / 3.14;
		cleardevice();
		windBar ();
		p[0].draw ();
		p[1].draw ();
		line ( fx, fy, mx, my );
		if ( index == 1 )	{
			gotoxy ( 1, 1 );
			cout<<"Magnitude : "<<sq<<"\tAngle : "<<int ( ang );
		}
		arow ( arr.vx, arr.vy );
		asm mov ax,1;		asm int 0x33;
	}
	else if ( clk == 2 )	{
		theme ( back );
		asm mov ax,2;		asm int 0x33;
		return;
	}
	else    {
		if ( chk == 1 )	{
			chk = 0;
			screenmove ();
			p[play % 2].x = getmaxx () / 2;
			if ( play == 1 )
				p[0].x = getmaxx() - tem;
			else
				p[1].x = tem;

			if ( comp != 0 )	{
				if ( comp == 1 )
					AI ();
				else
					play = ++play % 2;
				p[play % 2].x = getmaxx () / 2;
				if ( play == 1 )
					p[0].x = getmaxx() - tem;
				else if ( play == 0 )
					p[1].x = tem;
			}
			gotoxy ( 1, 1 );
			cout<<" Magnitude : 000\t Angle : 000";
			cleardevice();
			p[0].draw ();
			p[1].draw ();
		}
	}
	delay ( 100 );
	goto loop;
}

/// MENU

void arrowHeader ( char a[], int y, int c = 8, int x = getmaxx()/2 )	{
	setcolor ( c );
	setlinestyle ( 0, 0, 3 );
	line ( x-textwidth(a)/2-10, y, // BODY
	       x+textwidth(a)/2+10, y );
	setlinestyle ( 0, 0, 1 );
	int temp[] = { x+textwidth(a)/2+30, y,
			x+textwidth(a)/2, y+7,
			x+textwidth(a)/2+5, y,
			x+textwidth(a)/2, y-7 };
	setfillstyle ( 1, c );
	fillpoly ( 4, temp );

	int temp2[] = { x-textwidth(a)/2-10, y,
			x-textwidth(a)/2-25, y+10,
			x-textwidth(a)/2-75, y+10,
			x-textwidth(a)/2-60, y,
			x-textwidth(a)/2-75, y-10,
			x-textwidth(a)/2-25, y-10 };
	fillpoly ( 6, temp2 );
}

class page	{
	char names[12][50];
	int titleC, textC, selectedC, max, current, arrowC, graphic;
	int ( * function ) ( int );
	void graphicArr ( int x, int y, int c );
public:
	void set ( char lst[12][50], int tiC, int tC, int sC,
		int aC, int g, int m, int ( * f ) ( int )  );
	void draw ();
	void actions ();
	void setC ( int tiC, int tC, int sC, int aC )	{
		titleC = tiC;	        textC = tC;
		selectedC = sC;	        arrowC = aC;
	}
	void nameSet ( int a, char c[] );
}menu, opt;

void page :: set ( char lst[12][50], int tiC, int tC, int sC, int aC,
		   int g, int m, int ( * f ) ( int ) )	{
	function = f;
	for ( int i = 0; i < m; i++ )
		strcpy ( names[i], lst[i] );
	max = m;	current = 1;	graphic = g;
	setC ( tiC, tC, sC, aC );
}

void page :: nameSet ( int a, char c[] )	{
	strcpy ( names[a], c );
}

void page :: graphicArr ( int x, int y, int c )	{
	setcolor ( c );
	line ( x-20, y, x+20, y );
	line ( x-20, y+1, x+20, y+1 );
	int temp[] = { x+20, y, x+10, y+3, x+12, y, x+12, y+1, x+10, y-2, x+20, y+1 };
	setfillstyle ( 1, c );
	fillpoly ( 6, temp );
	int temp2[] = { x-20, y+1, x-25, y+3, x-35, y+3, x-30, y+1,
			x-30, y, x-35, y-3, x-25, y-3, x-20, y };
	fillpoly ( 8, temp2 );
}

void page :: draw ( )	{
	settextjustify ( CENTER_TEXT, CENTER_TEXT );
	settextstyle ( GOTHIC_FONT, HORIZ_DIR, 5 );
	cleardevice ();
	setcolor ( titleC );
	outtextxy ( getmaxx()/2 , .5 * getmaxy () / ( max + 1 ), names[0]);

	arrowHeader ( names[0], getmaxy()/(max+1), arrowC );
	settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 2 );
	setcolor ( textC );
	for ( int i = 1; i <= max; i++ )
		if ( current == i )	{
			settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 4 );
			setcolor ( selectedC );
			settextjustify ( CENTER_TEXT, CENTER_TEXT );
			outtextxy ( getmaxx()/2 , ( i + .5 )* getmaxy () / ( max + 1 ), names[i]);
		}
		else	{
			setcolor ( textC );
			settextjustify ( CENTER_TEXT, CENTER_TEXT );
			settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 2 );
			outtextxy ( getmaxx()/2 , ( i + .5 )* getmaxy () / ( max + 1 ), names[i]);
		}
	backGround ();
	if ( graphic == 1 )	{
		settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 4 );
		setcolor ( arrowC );
		int maxX = getmaxx()/2-textwidth(names[current])/2-20,
		    y = (current+.5)*getmaxy()/(max+1)+4, x = 0;
		// DRAW ARROW AND MOVE IT
		for ( int i = 5; x < maxX; i++  )	{
			graphicArr ( x, y, getbkcolor () );
			x += i*2;
			if ( x + (i+1)*2 > maxX )
				x = maxX;
			graphicArr ( x, y, arrowC );
			if ( kbhit () )
				break;
			delay ( 50 );
		}
	}
	settextstyle ( DEFAULT_FONT, HORIZ_DIR, 1 );
}

void page :: actions ()	{
	int key;
loop:
	key = getch ();
	if ( key ==  80 ) 	{ // down arrow
		++current == max ? current = 1 : 0;
		draw ();
	}
	else if ( key == 72 ) 	{ // up arrow
		--current == 0 ? current = max-1 : 0;
		draw ();
	}
	else if ( key == 13 ) // enter key
		if ( function )
			if ( function ( current ) != 0 )
				return;
	goto loop;
}

/// MAIN

int optFunc ( int a )	{
	if ( a == 1 )	{
		index = index++ % 2;
		if ( index == 1 )
			opt.nameSet ( a, "Show Index : Y" );
		else
			opt.nameSet ( a, "Show Index : N" );
	}
	else if ( a == 2 )	{
		if ( ++vit == 6 )
			vit = 1;
		char temp[] = "Vitality :  ";
		temp[11] = '0' + vit;
		opt.nameSet ( a, temp );
	}
	else if ( a == 3 )	{
		wall = wall++ % 2;
		if ( wall == 1 )
			opt.nameSet ( a, "Wall : Y" );
		else
			opt.nameSet ( a, "Wall : N" );
	}
	else if ( a == 4 )	{
		wind = wind++ % 2;
		if ( wind == 1 )
			opt.nameSet ( a, "Wind : Y" );
		else
			opt.nameSet ( a, "Wind : N" );
	}
	else if ( a == 5 )	{
		back = ++back % 1;
		theme ( back );
	}
	else if ( a == 6 )
		return 1;
	opt.draw ();
	return 0;
}

int menuFunc ( int a )	{
	if ( a == 1 ) 	{ // Instructions
		cleardevice ();
		backGround ( helpFold );
		settextjustify ( CENTER_TEXT, CENTER_TEXT );
		settextstyle ( GOTHIC_FONT, HORIZ_DIR, 5 );
		setcolor ( helpTitle );
		outtextxy ( getmaxx()/2, 50, "I n s t r u c t i o n s" );
		arrowHeader ( "I n s t r u c t i o n s", 80 );
		settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 1 );
		setcolor ( helpAbstract );
		outtextxy ( getmaxx()/2+10, 120, "Master the art of shooting with a bow and arrow using a mouse !" );
		settextstyle ( DEFAULT_FONT, HORIZ_DIR, 2 );
		setcolor ( helpText );
		outtextxy ( getmaxx()/2, 170, "SHOOTING" );
		settextstyle ( SANS_SERIF_FONT, HORIZ_DIR, 1 );
		outtextxy ( getmaxx()/2+11, 210, "To shoot an arrow, click anywhere on screen (make sure you have" );
		outtextxy ( getmaxx()/2+11, 230, "enough room to adjust strength and angle) and move your mouse" );
		outtextxy ( getmaxx()/2+11, 250, "back and down and finally release the left mouse button." );
		settextstyle ( DEFAULT_FONT, HORIZ_DIR, 2 );
		outtextxy ( getmaxx()/2, 300, "SETTINGS" );
		settextstyle ( SANS_SERIF_FONT, HORIZ_DIR, 1 );
		outtextxy ( getmaxx()/2+11, 340, "Click on \'settings\' in menu to alter game parameters." );
		outtextxy ( getmaxx()/2+11, 360, "Show index : Information about arrow while pulling" );
		outtextxy ( getmaxx()/2+11, 380, "Vitality : Number of hits a player can sustain" );
		settextstyle ( TRIPLEX_FONT, HORIZ_DIR, 1 );
		setcolor ( helpFoot );
		outtextxy ( getmaxx()/2+11, 450, "Press any key to continue..." );
		getch ();
	}
	else if ( a == 2 )	{ // VS Human
		comp = 0;
		start ();
	}
	else if ( a == 3 )	{ // VS Comp
		comp = 1;
		start ();
	}
	else if ( a == 4 )	{ // VS No one
		comp = -1;
		start ();
	}
	else if ( a == 5 )	{
		char tempC[10][50] = { "S e t t i n g s", "Show Index :  ",
			"Vitality :  ", "Wall :  ", "Wind :  ", "Change Theme", "Main Menu" };
		if ( index == 1 )
			tempC[1][13] = 'Y';
		else
			tempC[1][13] = 'N';
		tempC[2][11] = '0' + vit;
		if  ( wall == 1 )
			tempC[3][7] = 'Y';
		else
			tempC[3][7] = 'N';
		if  ( wind == 1 )
			tempC[4][7] = 'Y';
		else
			tempC[4][7] = 'N';
		opt.set ( tempC, titleC, textC, selectedC, arrowC, 0, 7, optFunc );
		opt.draw ();
		opt.actions ();
	}
	else if ( a == 6 )
		exit ( 0 );
	menu.draw ();
	return 0;
}

void main()	{
	int g = DETECT;
	initgraph ( &g, 0, "C:\\TC\\BGI" );
	cleardevice ();
	theme ( back );
	char tempC[10][50] = { "B O W M A N", "Instructions",
	"VS Human", "VS Computer", "Practice", "Settings", "Exit Application" };
	menu.set ( tempC, titleC, textC, selectedC, arrowC, 1, 7, menuFunc );
	menu.draw ();
	menu.actions ();
}
