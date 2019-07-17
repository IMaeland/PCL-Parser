//
//	Parser for PCL version 5 and earlier.
//	Once a command is known, it is acted upon by
//	routines in <pclprint.h> which write out a
//	description of the PCL commands.  Replace
//	pclprint.h with your own routines as needed.
//
//	Usage: PCLPARSE infile outfile
//
//	Errors are printed to stderr, and the data
//	is passed to outfile untouched.
//
#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#if !defined (_DOS)
	#include <windows.h>
#else
	#define LPSTR	char *
#endif

#if defined (WIN32)
	#define DllExport	__declspec( dllexport )
#endif

#undef islower	//  Make sure they're functions,
#undef isupper  //  NOT macros with side-effects
#undef isdigit
#undef isgraph

void doResolution (void);
void eolPitchFamily (void);
void eolWrapFamily (void);
void fontManagement (void);
int getCommandString (void);
void graphicsPclFamily (void);
void macroFamily (void);
int ourAtoi (void);
void pageControlFamily (void);
void parseCommandString (int len);
void pclErr (int);
void posMarginFamily (void);
void printImaging (void);
void rasterCompression (void);
void rasterGraphics (void);
void resetBuffer (int);
void underlineFamily (void);
void pclJobControl (void);
void parsePrintingOptions (char *szCommand);
int openFiles (char *szFlags, char *szInput, char *szOutput);
long MyGetFileLength (LPSTR lpszFileName);
int PercentParsed ();

FILE *fin, *fout;
long finLength, foutLength;
int combinedCommand;     // = YES if several commands in one string
int savedChar;
int bPrintPlus;
int bPrintMinus;
int nCharsRead = 0;

#define PclBufSize	128
#define Unsupported	200
#define Illegal		201
#define TooLong		202

#define Temporary	1
#define AllFonts	2
#define Primary		3
#define Secondary	4
#define Permanent   5

#define true	1
#define false	0

#define PPOK			0
#define PPInputFile		1
#define PPOutputFile    2
#define PPBadPcl		3


char buffer [PclBufSize + 1];
char szBuffer [PclBufSize + 1];
char *bufPtr = buffer;    /* Where are we in buffer?  */

int downloadingChar;

#include "ljmain.h"
#include "pclprint.h"   //	Header with actions for each command
                        //	should change with every application

BOOL WINAPI DllMain (HANDLE, DWORD, LPVOID);
BOOL WINAPI DllMain (HANDLE hModule, DWORD fdwReason, LPVOID lpReserved) {
                                                                  
	switch (fdwReason) {
	//
	//	Code from LibMain inserted here.  Return TRUE to keep the
	//	DLL loaded or return FALSE to fail loading the DLL.
	//
	//	You may have to modify the code in your original LibMain to
	//	account for the fact that it may be called more than once.
	//	You will get one DLL_PROCESS_ATTACH for each process that
	//	loads the DLL. This is different from LibMain which gets
	//	called only once when the DLL is loaded. The only time this
	//	is critical is when you are using shared data sections.
	//	If you are using shared data sections for statically
	//	allocated data, you will need to be careful to initialize it
	//	only once. Check your code carefully.
	//	
	//	Certain one-time initializations may now need to be done for
	//	each process that attaches. You may also not need code from
	//	your original LibMain because the operating system may now
	//	be doing it for you.
	//
	case DLL_PROCESS_ATTACH:	break;

	//
	//	Called each time a thread is created in a process that has
	//	already loaded (attached to) this DLL. Does not get called
	//	for each thread that exists in the process before it loaded
	//	the DLL.
	//	
	//	Do thread-specific initialization here.
	//
	case DLL_THREAD_ATTACH:		break;
 
	//
	//	Same as above, but called when a thread in the process exits.
	//	Do thread-specific cleanup here.
	//
	case DLL_THREAD_DETACH:		break;

	//
	//	Code from _WEP inserted here.  This code may (like the
	//	LibMain) not be necessary.  Check to make certain that the
    //	operating system is not doing it for you.
	//
	case DLL_PROCESS_DETACH:	break;
	}
 
	//	The return value is only used for DLL_PROCESS_ATTACH; all other
	//	conditions are ignored.  
	return TRUE;   // successful DLL_PROCESS_ATTACH
}

//
// 32 bit dll
//
LONG WINAPI PclParse (LPSTR, LPSTR, LPSTR);
LONG WINAPI PclParse (LPSTR lpszFlags, LPSTR lpszInput, LPSTR lpszOutput) {

	int c, i;
	int state = 0;
	int count = 0;
	int nResult = 0;
	int tmp = 0;

#ifdef _Debug 
	MessageBox (0, lpszFlags, "", 0);
	MessageBox (0, lpszInput, "", 0);
	MessageBox (0, lpszOutput, "", 0);
#endif

	if (nResult = openFiles (lpszFlags, lpszInput, lpszOutput) != 0) return (nResult);
    downloadingChar = 0;
	while ((c = fgetc (fin)) != EOF) {
		   
		tmp++;

		if (tmp == 100) {
			tmp = 0;
		}

		if ((downloadingChar == 1) && (c != ESC)) {
			// Keep reading until we reach an escape char.
			while ((c = fgetc (fin)) != ESC) {
				count++;
			}
			fprintf (fout, "[Extra downloaded characters %d]", count);
			downloadingChar = 0;
			count = 0;
		}
		
		if (c != ESC) {
			pclRegChar (c);
			state = 0;
		}
		else {
			//
			// Finished parsing regular characters.
			// Print a eoln
			//
			if ((state == 0) && shouldPrint (regChar)) fprintf (fout, "\r\n");
			state = 1;
			if (((i = getCommandString ()) == Illegal)|| i == Unsupported || i == TooLong ) {
				pclErr (i);
				continue;
			}
			else {
				parseCommandString (i);
			}
		}
		fflush (fout);
   }

   fclose (fin);
   fclose (fout);
   return (PPOK);
}	//	end of main()

//
//	Get the PCl comand string after ESC detected
//	Returns length of command (excluding Esc) or error code
//
int getCommandString (void) {

    int c, i = 0;
    
    memset (buffer, '\0', PclBufSize + 1);	//  Set buffer to 0's
    buffer [i++] = c = fgetc (fin);

	//	2nd char cannot be EOF
    if (c == EOF)			
        return Illegal;

	//	A 2-character command
    if (c >= 0x30 && c <= 0x7E)	
        return (2);	//  Length of command

	//	Paramaterized Command
    if (c >= 0x21 && c <= 0x2F)	
    {
        buffer [i++] = c = fgetc (fin);
        if (( c >= 0x60 && c <= 0x7E ) || isdigit (c))
        {            
			//	Valid char, so get rest of command string
			while (i < PclBufSize && c !=EOF )
			{
				buffer [i++] = c = fgetc (fin);

				//  End of command
				if (c >= 0x40 && c <= 0x5E)
                    break;
			}	
			//	128 cars was not enough!
			if ((i == PclBufSize) && (c < 0x40 || c > 0x5E))
				return (TooLong); 
		}
		else
			return (Illegal);
	}
	else
		return (Illegal);
	
	//	Valid command
	return (strlen (buffer));   
}

//
//	Parses command strings and calls action routine.
//	While a string may be valid by HP standards it might
//	not be supported by the current PCL (now at Level 5).
//	In these cases, the command is passed on as print datal
//	Note the main loop has a foto destination at top.  This
//	is for use in combined commands, to process the next command.
//
void parseCommandString (int len) {

	//	It's not PCL, so just pass it on
    if (len < 2) {
		fprintf (fout, "/n%c%s", ESC, buffer);
		return;
    }
	//	Handle 2-char commands here 
    if (len == 2) {

		switch (buffer [0]) {
		
		case '9':	pclResetMargins ();   
					break;
		case 'E':	pclReset ();
					break;
		case 'Y':	pclDisplayCodes (ON); 
					break;
		case 'z':	pclDisplayCodes (OFF); 
					break;
		case '=':	pclHalfLineFeed ();     
					break;
		default:	pclErr (Unsupported);
		}
	}
	//	Parameterized command form her on in
	else {
		//	Destination of subsequent goto's 
		parseLoop:             
		combinedCommand = NO;
            bufPtr = buffer;

            switch (*bufPtr) {
			
			case '%':	graphicsPclFamily (); 
						break;
            case '&':	{
				switch (*(++bufPtr)) {
				
				case EOF:	pclFinish();
							break;
				case 'a':	posMarginFamily();
							break;
				case 'd':	underlineFamily();     
							break;
				case 'f':	macroFamily();         
							break;
				case 'k':	eolPitchFamily();     
							break;
				case 'l':	pageControlFamily();  
							break;
				case 'p':	pclTransparentData();
							break;
				case 's':	eolWrapFamily();
							break;
				case 'u':	pclJobControl();
							break;
				default:	pclErr (Unsupported);  break;
				}
				if (combinedCommand == YES)
					goto parseLoop;
				else
					return;
            }
			case '*':	{
				switch (*(++bufPtr)) {
				
				case 'b':	rasterCompression ();  
							break;
				// Fonts and shading areas
				case 'c':	fontManagement ();     
							break;
				case 'p':	pclDotPosition ();
							break;
				case 'r':	rasterGraphics ();     
							break;
				case 't':	doResolution ();       
							break;
				case 'v':	printImaging ();       
							break;
				default:	pclErr (Unsupported); 
							break;
				}
				if (combinedCommand == YES)
					goto parseLoop;
				else
					return;
				}
				case')':
				case'(':	{
					
					int i, ch, e;
					
					//	Save the ) or (
					ch = *bufPtr;     
					if ((e = *(++bufPtr)) == 's') {
						i = ourAtoi ();
						//	Get lats char in string  
						e = *bufPtr;     
						switch (e) {
						
						case 'w':
						case 'W':	if (ch == ')')
										pclDownloadFontHeader (i);
                                    else
										pclDownloadFontChar (i);
									combinedCommand;// + NO;
                                    break;
						case 'p':
						case 'P':	pclSpacingType (i);
                                    break;
						case 'h': 
						case 'H':	pclPrimaryPitch (i);
									break;
						case 't': 
						case 'T':	pclTypeface (i);
                                    break;
						case 'v': 
						case 'V':	pclPrimaryHeight (i);
                                    break;
						case 'b': 
						case 'B':	pclStrokeWeight (i + 7);
                                    break;
						}
						//	Combined command
						if (islower (e)) {
							combinedCommand = YES;
							resetBuffer (2);
						}
						break;
					}
					else {
						//  See below at special case
						char *saveBufPtr = bufPtr; 
						i = ourAtoi ();
						e = *bufPtr;

						switch (e) {
						
						case '@':	pclDefaultFont (Secondary);
									break;
						case 'x': 
						case 'X':	pclSelectFont (Secondary, i);
									break;
						case 'd': 
						case 'D':
						case 'e': 
						case 'E':
						case 'f': 
						case 'F':
						case 'g': 
						case 'G':
                        case 'i': 
						case 'I':
                        case 'k': 
						case 'K':
                        case 'n': 
						case 'N':
                        case 's': 
						case 'S':
                        case 'u': 
						case 'U': {
							//	Special case:
							//	prefix on these combined commands is only char, 
							//	so ourAtoi() and resetBuffer() must be done 
							//	specially, since those functions depend on the
                            //	more common 2-char prefix.

							bufPtr = saveBufPtr - 1;
							i = ourAtoi();

							pclSymbolSet (i, e);

							if (islower (e)) {
								resetBuffer (1);
								goto parseLoop;
							}
						}
						break;
					}
					//	Combined command
					if (islower (e)) {
						combinedCommand = YES;
						resetBuffer (2);
					}
					break;
				}
			}
			default:	pclErr (Unsupported); 
						break;
		}
		if (combinedCommand == YES)
			goto parseLoop;
	}
}

//
//	Command Prefix: Esc %
//	Switching between graphics and PCL modes
//
void graphicsPclFamily (void) {

	int parameter, type;

	//  Get the data parameter
	parameter = *(++bufPtr);  

	//	Get the type of command
	type = *(++bufPtr);  

	if (type == 'A')
		pclEnterPclMode (parameter);
	else
		if (type == 'B')
			pclEnterHpglMode (parameter);
		else
			pclErr (Unsupported);
}

//
//	Command Prefix: Esc & d
//	Underlining handled here.
//
void underlineFamily (void)
{
	switch (*(bufPtr)) {

	case '@':	pclDisableUnderline ();
				return;
	case '0':	pclEnableFixedUnderline ();
				break;
	case '3':	pclEnableFloatUnderline ();
				break;
	default:	pclErr (Unsupported);
				return;
	}
	if (*bufPtr == 'd') {
		combinedCommand = YES; 
		resetBuffer (2);
	}
}

//
//	Command prefix: Esc & a
//	Set cursor position, right and left margins, and print rotaion.
//
void posMarginFamily (void)
{
    int i;

    i = ourAtoi ();

    switch ( *bufPtr ) {

	case 'v':     
	case 'V':	pclVertPosition (i, DECIPOINTS);    
				break;
	case 'r':     
	case 'R':	pclVertPosition (i, ROWS);
				break;
	case 'c':     
	case 'C':	pclHorzPosition (i, COLUMNS);       
				break;
	case 'h':     
	case 'H':	pclHorzPosition (i, DECIPOINTS);    
				break;
	case 'l':     
	case 'L':	pclSetLeftMargin (i);      
				break;
	case 'm':     
	case 'M':	pclSetRightMargin (i);
				break;
	//	Note absence of 'p'
	case 'p':	pclRotatePrint (i);
				break;
	default:	pclErr (Unsupported);         
				return;
    }

    if (islower (*bufPtr)) {
		combinedCommand = YES; 
		resetBuffer (2);
    }
}

//
//	Comand Prefix: Esc & k
//	Set line-stermination sequence, pitch,
//	and HMI ( i.e., line height)
//
void eolPitchFamily (void) {

	int i = ourAtoi();

	switch (*bufPtr) {
        
	//	Esc & k # G
	case 'G': 
	case 'g':	{
				//	Possible EOL actions
				enum {Cr = 1, Lf = 2, Ff = 4};

				//	Array of possible switches for CR LF FF respectively
                char CR_LF_FF [3];
  
				CR_LF_FF [0] = Cr;
                CR_LF_FF [1] = Lf;
                CR_LF_FF [2] = Ff;

				switch (i) {
				case 0:	break;
				case 1: CR_LF_FF [0] |= Lf;
						break;
				case 3: CR_LF_FF [0] |= Cr;
				case 2:	CR_LF_FF [1] |= Cr;
						CR_LF_FF [2] |= Ff;
				}
				pclLineTermination (CR_LF_FF);
				break;
                }
				//	Esc & k # h 
	case 'H':
	case 'h':	pclHorzMove (i);
				break;

	case 'S':
	case 's':	switch (i) {
                        
				case 0:	pclSet10Pitch ();
						break;
				case 4: pclSet12Pitch (); 
						break;
				case 2:	pclSetCompressedMode (); 
						break;
				}
				break;
	default:	pclErr (Unsupported);        
				return;
	}
	if (islower (*bufPtr))	{
		combinedCommand = YES; 
		resetBuffer (2);
	}
}

//
//	Command Prefix: Esc & s
//	Set whether long lines shoud wrap ar EOL
//
void eolWrapFamily () {

	if (*(++bufPtr) == '0')
		pclEolWrap (ON);
	else
		pclEolWrap (OFF);

	if (islower (*(++bufPtr))) {
		combinedCommand = YES; 
		resetBuffer (2);
    }
}

//
//	Command Prefix: Esc & 1
//	Set mos page-related parameters, including:
//	page size, top margin, perforation skip,
//	orientation, number of copies, etc.
//
void pageControlFamily() {

    int i = ourAtoi ();

	switch (*bufPtr) {

	case 'A':  
	case 'a':	pclPageSize (i);
				break;
	case 'C':  
	case 'c':	pclVertMove (i);
				break;
	case 'D':  
	case 'd':	pclLineSpacing (i);
				break;
	case 'E':  
	case 'e':	pclTopMargin (i); 
				break;
	case 'F':  
	case 'f':	pclTextLength (i);
				break;
	case 'H':  
	case 'h':	pclPaperSource (i);
				break;
	case 'L':  
	case 'l':	pclPerforationSkip (i);
				break;
	case 'o':
	case 'O':	pclPageOrientation (i);
				break;
	case 'P':  
	case 'p':	pclPageLength (i);
				break;
	case 'U':  
	case 'u':	pclRegistration (i, LEFT);      
				break;
	case 'X':  
	case 'x':	pclMakeCopies (i);
				break;
	case 'Z': 
	case 'z':	pclRegistration (i, TOP);
				break;
	default:	pclUnknownPageControlCommand ();
	}
	if (islower (*bufPtr)) {
		combinedCommand = YES; 
		resetBuffer (2);
	}
}

//
//	Command Prefix: Esc & f
//	All macro handling done here.
//
void macroFamily () {

	int i;

	i = ourAtoi ();

	switch (*(++bufPtr)) {
		case 'S': 
		case 's':	pclPushPopPosition (i);	
					break;

		case 'X': 
		case 'x': 	switch (i) {
					case 0: pclStartMacroDef (); 
							break;
					case 1: pclStopMacroDef (); 
							break;
					case 2: pclExecuteMacro (); 
							break;
					case 3: pclCallMacro (); 
							break;
					case 4: pclEnableOverlay (); 
							break;
					case 5: pclDisableOverlay (); 
							break;
					case 6: pclDeleteMacros (); 
							break;
					case 7: pclDeleteTempMacros (); 
							break;
					case 8: pclDeleteMacroId (); 
							break;
					case 9: pclMakeMacroTemp (); 
							break;
					case 10: pclMakeMacroPerm (); 
							break;
					}
		case 'Y': 
		case 'y':	pclIdentifyMacro (i);
	}
	if (islower (*bufPtr)) {
		combinedCommand = YES; 
		resetBuffer (2);
	}
}

//
//	Command Prefix: Esc * t
//	Set graphics print resolution
//
void doResolution (void) {

	pclResolution (ourAtoi ());
	if (islower (*bufPtr)) {
		combinedCommand = YES;
		resetBuffer (2);
	}
}

// 
//	Command Prefix: Esc * c
//	Handle some font and many shading functions
//
void fontManagement (void) {
	
	static int fill_type;
	enum {Shade = 1, CrossHatch};

	int i = ourAtoi ();

	switch (*bufPtr) {
	case 'A': 
	case 'a':	pclRectangle (i, POINTS, HORIZ);	
				break;
	case 'B': 
	case 'b':	pclRectangle (i, POINTS, VERT);	
				break;
	case 'c':
	case 'C':	//???
				pclSetPictureFrameAnchorPoint ();
				break;
	case 'D': 
	case 'd':	pclAssignFontId (i);
				break;
	case 'E': 
	case 'e':	pclAnnounceNextChar (i);
				break;
	case 'F': 
	case 'f':	switch (i) {
				case 0:	pclDeleteFonts (AllFonts);	
						break;
				case 1:	pclDeleteFonts (Temporary);	
						break;
				case 2:	pclDeleteLastFont ();	
						break;
				case 3:	pclDeleteLastChar ();	
						break;
				case 4:	pclFontStatus (Temporary); 
						break;
				case 5: pclFontStatus (Permanent);	
						break;
				case 6:	pclAssignFontTemp ();	
						break;
				}		  
				break;			  
	case 'G': 
	case 'g': 	if (fill_type == CrossHatch)
					pclSelectPattern (i);
				//
				//	It hasn't been defined, so we do our best.
				//	Shade < 6 is so unlikely that we assume it's a pattern.
				//
				else if (fill_type == Shade)
					pclSelectShading (i);
				else if (i <= 6)			//  Changed from !=
					pclSelectPattern (i);
				else
					pclSelectShading (i);
				break;
	case 'H': 
	case 'h':	pclRectangle (i, DECIPOINTS, HORIZ);	
				break;
	case 'P': 
	case 'p':	pclFillRectangle (i);
				if (i == 3)
					fill_type = CrossHatch;
				else if (i == 2)
					fill_type = Shade;	
				break;
	case 't':
	case 'T':	pclSetPictureFrameAnchorPoint ();
				break;
	case 'V': 
	case 'v':	pclRectangle (i, DECIPOINTS, VERT);	
				break;
	case 'w':
	case 'W':	pclUserDefinedPattern (i);
				break;
	case 'X':
	case 'x':	pclPictureFrameHorizontalSize (i);
				break;
	case 'Y':
	case 'y':	pclPictureFrameVerticalSize (i);
				break;

	default:	pclErr (Unsupported);
				return;
	}
	if (islower (*bufPtr)) {
		combinedCommand = YES; 
		resetBuffer (2);
	}
}

//
//	Command Prefix: Esc * r
//	Set various raster graphics parameters
//
void rasterGraphics (void) {

	int i = ourAtoi();

	switch (*bufPtr) {
	case 'A':
	case 'a':	pclStartRasterGraphics (i);	
				break;
	case 'B': 
	case 'b':	pclEndRasterGraphics ();	
				break;
	case 'F': 
	case 'f':	pclGraphicPresentation (i);	
				break;
	case 'S': 
	case 's':	pclRasterWidth (i);	
				break;
	case 'T': 
	case 't':	pclRasterHeight (i);
	}

	if (islower (*bufPtr)) {
		combinedCommand = YES;	
		resetBuffer (2);
	}
}                            

//
//	Command Prefix: Esc * v
//	Set miscellaneous raster functions:
//		compression mode, offset, actual rasters
//
void rasterCompression (void) {

	int i = ourAtoi();

	switch (*bufPtr) {
	
	case 'M': 
	case 'm':	pclRasterCompress (i);	
				break;
	case 'W':	pclSendRasterData (i);	
				break;
	case 'Y': 
	case 'y':	pclRasterYOffset (i); 
				break;
	}

	if (islower (*bufPtr)) {
		combinedCommand = YES;
		resetBuffer (2);
	}
}

//
//	Command Prefix: Esc * v         
//	Set transparency mode and imaging pattern
//
void printImaging (void) {
	
	int i = ourAtoi ();

	switch (*bufPtr) {
	case 'T':	pclImagingPattern (i);	
				break;
	case 'N':	pclSourceTransparency (i);	
				break;
	case 'O':	pclPatternTransparency (i);	
				break;
	}
}

//
//	Esc &u *d
//
void pclJobControl (void) {

	int i = ourAtoi ();

	switch (*bufPtr) {
	case 'D':	pclUnitOfMeasure (i);	
				break;
	}
}

//
//	Utility Functions
//

//
//	Returns atoi () on characters at bufPtr + 1.
//	at end, bufPtr points to the first char after digits.
//
int ourAtoi (void) {
	
	char numberString [6];		//	Max size of int string is 5 + '\0'
	int c, i;
	int sign = 0;

	bufPtr += 1;
	for (i = 0; i < 5; ) {		//	Get the digits as a string
		c = *(bufPtr++);
		if (isdigit (c) || c == '-' || c == '+') {
			if (c == '-' || c == '+') {

				//	Sign already seen, so new sign is not part
				//	of this string of digits.
				if (sign != 0) {
					bufPtr -= 1;
					break;
				}
				else
					sign = 1;
			}
			numberString [i++] = c;		
		}
		else {
			//	bufPtr currently points past non-digit char
			bufPtr -= 1;
			break;
		}
	}
	numberString [i] = '\0';
	i = atoi (numberString);
	return (i);
}

//
//	Prints an error message and the incorrect command,
//	then writes the data to the output file.
//
void pclErr (int type) {

	int c;

	if (type == TooLong) {
		fprintf (fout, "[Command Too Long : [Esc%s]", buffer);
		
		while ((c = fgetc (fin)) != EOF && !isupper (c)) {
//			fputc (c, stderr);
			fputc (c, fout);
		}
	}
	else {
//		fprintf (stderr, "\n%s Command : [Esc%s",
//			( type == Unsupported ? "Unsupported" : "Illegal"),
//			buffer);
		fprintf (fout, "[Unsupported %s]", buffer);
	}
}

//
//	Resets parsing buffer so that the next parsing operation
//	will look at the next command in a combined command.
//	Combined commands have prefix_length chars after the Esc
//	as a common prefix, so the rest of the string is moved
//	forward in the buffer to follow right behind the prefix
//
void resetBuffer (int prefixLength) {
	
	bufPtr += 1;	//	Point to the next command
	memmove (buffer + prefixLength, bufPtr, strlen (bufPtr) + 1);
}


void parsePrintingOptions (char *szCommand) {
	
	int i;

	if (szCommand == "") return;

	if (szCommand [0] == '-') {
		bPrintPlus = false;
		bPrintMinus = true;
	} 
	else if (szCommand [0] == '+') {
			bPrintPlus = true;
			bPrintMinus = false;
	} 
	else return;

	for (i = 1; szCommand[i] != (char) 0; i++) {
		printFunctions [szCommand[i] - '#'].shouldPrint = true; 
	}
}

int openFiles (char *szFlags, char *szInput, char *szOutput) {
	
	parsePrintingOptions (szFlags);

	//
	//  A plus sign indicates print only items specified
	//  while a minus sign means print everything minus
	//  the items specified.
	//
	finLength = MyGetFileLength (szInput);
	fin = fopen (szInput, "rb");
	if (fin == NULL) return (PPInputFile);
	    
	fout = fopen (szOutput, "wb");
	if (fout == NULL) return (PPOutputFile);

	return (PPOK);
}

long MyGetFileLength (LPSTR lpszFileName)
{
   int fh, result;
   unsigned int nbytes = BUFSIZ;

   /* Open a file */
   result = 0;
   if((fh = _open(lpszFileName, _O_RDWR, _S_IREAD)) != -1)
   {
      result = _filelength (fh);
      _close( fh );
   }
   return (result);
}

int PercentParsed () {

//	int nResult = 0;
//	nResult = ftell (fin);
//	return ((int (nResult / finLength)) * 100);
	return (0);
}