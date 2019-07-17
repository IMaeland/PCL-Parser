//
//	Ljmain.h
//
//	Manifest constants used in LasterJet work
//	Version 1.4
//
#ifndef JLMAIN
	#define LJMAIN	1

#ifndef MSDOS
	#if (__MSDOS__)
		#define MSDOS	1
	#endif
#endif

#if MSDOS
	#include <dos.h>
#undef UNIX

#else
	#define UNIX	1
#endif

//#pragma pack(1)

#define ESC		0x1B
#define FormFeed	0x0C
#define ON		1
#define OFF	0

#define YES	1
#define NO	0

#define POINTS	1
#define DECIPOINTS 2
#define COLUMNS	4
#define ROWS	8

//	Edges
#define TOP	'T'
#define BOTTOM	'B'
#define LEFT 'L'
#define RIGHT 'R'

//	Directories
#define HORIZ 'H'
#define VERT 'V'

#endif

