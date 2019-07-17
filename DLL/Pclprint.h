	

typedef enum {
	announceNextChar, assignFontId, assignFontTemp,
	callMacro, defaultFont, deleteFonts, deleteLastChar,
	deleteLastFont, deleteMacroId, deleteMacros, deleteTempMacros,
	disableOverlay, disableUnderline, displayCodes, dotPosition,
	downloadFontChar, downloadFontHeader, enableFixedUnderline, enableFloatUnderline,
	endRasterGraphics, enableOverlay, enterHpglMode, enterPclMode, 
	eolWrap, executeMacro, fillRectangle, finish, 
	fontStatus, graphicPresentation, halfLineFeed, horzMove,
	horzPosition, identifyMacro, imagingPattern, init, 
	lineSpacing, lineTermination, makeMacroPerm, makeMacroTemp,
	makeCopies, orientation, pageLength, pageOrientation, 
	pageSize, paperSource, patternTransparency, 
	perforationSkip, pictureFrameHorizontalSize, pictureFrameVerticalSize, 
	primaryHeight, primaryPitch, pushPopPosition,
	rasterCompress, rasterHeight, rasterWidth,
	rasterYOffset, rectangle, regChar, registration, reset, 
	resetMargins, resolution, rotatePrint, selectFont,
	selectPattern, selectShading, sendRasterData, set10Pitch, 
	set12Pitch, setCompressedMode, setLeftMargin, setRightMargin, 
	setPictureFrameAnchorPoint, stopMacroDev, strokeWeight, unitOfMeasure,
	userDefinedPattern, sourceTransparency,
	spacingType, startMacroDef, startRasterGraphics, stopMacroDef,
	symbolSet, textLength, topMargin, transparentData, 
	typeface, vertMove, vertPosition, unknownCommand, 
	unknownPageControlCommand
} printFunctionId;

typedef struct printingProp
{
    printFunctionId functionId;
    int				shouldPrint;
} printProp;

printProp printFunctions [] = {
	announceNextChar,		false,	// 35 #
	assignFontId,			false,
	assignFontTemp,			false,
	callMacro,				false,
	defaultFont,			false,
	deleteFonts,			false,	// 40 (
	deleteLastChar,			false,
	deleteLastFont,			false,
	deleteMacroId,			false,
	deleteMacros,			false,
	deleteTempMacros,		false,	// 45 - 
	disableOverlay,			false,
	disableUnderline,		false,
	displayCodes,			false,
	dotPosition,			false,
	downloadFontChar,		false,	// 50 1
	downloadFontHeader,		false,	
	enableFixedUnderline,	false,	
	enableFloatUnderline,	false,	
	endRasterGraphics,		false,	
	enableOverlay,			false,	// 55 7
	enterHpglMode,			false,
	enterPclMode,			false,	
	eolWrap,				false,		
	executeMacro,			false,	
	fillRectangle,			false,	// 60
	finish,					false,
	fontStatus,				false,	
	graphicPresentation,	false,	
	halfLineFeed,			false,	
	horzMove,				false,	// 65 A	
	horzPosition,			false,
	identifyMacro,			false,	
	imagingPattern,			false,	
	init,					false,	
	lineSpacing,			false,	// 70
	lineTermination,		false,
	makeMacroPerm,			false,	
	makeMacroTemp,			false,
	makeCopies,				false,
	orientation,			false,
	pageLength,				false,
	pageOrientation,		false,
	pageSize,				false,
	paperSource,			false,
	patternTransparency,	false,	// 80
	perforationSkip,		false,	
	pictureFrameHorizontalSize, false,
	pictureFrameVerticalSize, false,
	primaryHeight,			false,
	primaryPitch,			false,
	pushPopPosition,		false,
	rasterCompress,			false,
	rasterHeight,			false,
	rasterWidth,			false,
	rasterYOffset,			false,
	rectangle,				false,
	regChar,				false,
	registration,			false,	// 90
	reset,					false,	
	resetMargins,			false,
	resolution,				false,
	rotatePrint,			false,
	selectFont,				false,
	selectPattern,			false,
	selectShading,			false,	// 97 a
	sendRasterData,			false, 	
	set10Pitch,				false,
	set12Pitch,				false,	// 100
	setCompressedMode,		false,
	setLeftMargin,			false,
	setRightMargin,			false,
	sourceTransparency,		false,
	spacingType,			false,
	startMacroDef,			false,
	startRasterGraphics,	false,
	stopMacroDef,			false,
	symbolSet,				false,
	textLength,				false, 
	topMargin,				false,	// 110
	transparentData,		false,
	typeface,				false,
	vertMove,				false,
	vertPosition,			false,
	unknownCommand,			false,
	unknownPageControlCommand, false
};

//
//	Functions to print the meanings of PCL code sequences in English
//
//	Function names are in alphabetical order
//
//	This module requires access to ourAtoi() and reset_buffer() in pclParse.c
//

void pclAnnounceNextChar (int);
void pclAssignFontId (int);
void pclAssignFontTemp (void);
void pclCallMacro (void);
void pclDefaultFont (int);
void pclDeleteFonts (int);
void pclDeleteLastChar (void);
void pclDeleteLastFont (void);
void pclDeleteMacroId (void);
void pclDeleteMacros (void);
void pclDeleteTempMacros (void);
void pclDisableOverlay (void);
void pclDisableUnderline (void);
void pclDisplayCodes (int);
void pclDotPosition (void);
void pclDownloadFontChar (int);
void pclDownloadFontHeader (int);
void pclEnableFixedUnderline (void);
void pclEnableFloatUnderline (void);
void pclEndRasterGraphics (void);
void pclEnableOverlay (void);
void pclEnterHpglMode (int);
void pclEnterPclMode (int);
void pclEolWrap (int);
void pclExecuteMacro (void);
void pclFillRectangle (int);
void pclFinish (void);
void pclFontStatus (int);
void pclGraphicPresentation (int);
void pclHalfLineFeed (void);
void pclHorzMove (int);
void pclHorzPosition (int, long int);
void pclIdentifyMacro (int);
void pclImagingPattern (int);
void pclLineSpacing (int);
void pclLineTermination (char []);
void pclMakeMacroPerm (void);
void pclMakeMacroTemp (void);
void pclMakeCopies (int);
void pclOrientation (int);
void pclPageLength (int);
void pclPageOrientation (int type);
void pclPageSize (int);
void pclPaperSource (int);
void pclPatternTransparency (int);
void pclPerforationSkip (int);
void pclPrimaryHeight (int points);
void pclPrimaryPitch (int pitch);
void pclPushPopPosition (int);
void pclRasterCompress (int);
void pclRasterHeight (int);
void pclRasterWidth (int);
void pclRasterYOffset (int);
void pclRectangle (int qty, int units, int direction);
void pclRegChar (int);
void pclRegistration (int, int);
void pclReset (void);
void pclResetMargins (void);
void pclResolution (int);
void pclRotatePrint (int);
void pclSelectFont (int, int);
void pclSelectPattern (int);
void pclSelectShading (int);
void pclSendRasterData (int);
void pclSet10Pitch (void);
void pclSet12Pitch (void);
void pclSetCompressedMode (void);
void pclSetLeftMargin (int);
void pclSourceTransparency (int);
void pclSpacingType (int);
void pclStartMacroDef (void);
void pclStartRasterGraphics (int);
void pclStopMacroDef (void);
void pclSymbolSet (int, int);
void pclTextLength (int);
void pclTopMargin (int);
void pclTransparentData (void);
void pclTypeface (int);
void pclVertMove (int);
void pclVertPosition (int, long int);
void pclUserDefinedPattern (int);
void pclUnknownCommand ();
void pclUnknownPageControlCommand ();

void myPrintString (char *szString, int nValue);
void myPrintChar (char cChar, int nValue);
static void getUnitName (long int, char *);
void pclEnterPclMode (int);
int shouldPrint (int nValue);


void pclAnnounceNextChar (int nextChar) {
	sprintf (szBuffer, "[%X]", nextChar);
	myPrintString (szBuffer, announceNextChar);
}

void pclAssignFontId (int id) {
	sprintf (szBuffer, "[Font Assigned #%d]", id);
	myPrintString (szBuffer, assignFontId);
}

void pclAssignFontTemp (void) {
	myPrintString ("[Last Font Assigned as Temporary]", assignFontTemp);
}

void pclCallMacro (void) {
	myPrintString ("[Call Macro]", callMacro);
}
void pclDefaultFont (int whichOne) {
	sprintf (szBuffer, "[Default to %s Font]", 
		whichOne == Primary ? "Primary" : "Secondary");
	myPrintString (szBuffer, defaultFont);
}

void pclDeleteFonts (int type) {
	sprintf (szBuffer, "[Delete %s Fonts]", type == Temporary ? "Temporary" : "All");
	myPrintString (szBuffer, deleteFonts);
}
void pclDeleteLastChar (void) {
	myPrintString ("[Delete Last Character]", deleteLastChar);
}
void pclDeleteLastFont (void) {
	myPrintString ("[Delete Last Font]", deleteLastFont);
}
void pclDeleteMacroId (void) {
	myPrintString ("[Delete Macro ID]", deleteMacroId);
}
void pclDeleteMacros (void) {
	myPrintString ("[Delete Macros]", deleteMacros);
}
void pclDeleteTempMacros (void) {
	myPrintString ("[Delete Temp Macros]", deleteTempMacros);
}
void pclDisableOverlay (void) {
	myPrintString ("[Disable Macro Overlay]", disableOverlay);
}
void pclDisableUnderline (void) {
	myPrintString ("[Turn Off Underline]", disableUnderline);
}
void pclDisplayCodes (int state) {
	sprintf (szBuffer, "[Turn %s Function Display]",
		(state == ON ? "ON" : "OFF"));
	myPrintString (szBuffer, displayCodes);
}
void pclDotPosition (void) {
	int i, c, d, x;

	x = *(++bufPtr);

	//	Digit = absolute move
	if (isdigit (x) || x == '-' || x == '+')
		--bufPtr;

	i = ourAtoi ();
	c = *bufPtr;
	d = toupper (c);

	if (isdigit (x))
		sprintf (szBuffer, "[Position to %c %d Dots]", d, i);
	else
		sprintf (szBuffer, "[Position to %c %d Dots]", d, x, i);

	if (islower (c)) {
		combinedCommand = YES;
		resetBuffer (2);
	}
	myPrintString (szBuffer, dotPosition);
}
//	Just eat 'em
void pclDownloadFontChar (int bytes) {
	sprintf (szBuffer, "[Download Font Char for %d bytes]", bytes);
	for ( ; bytes > 0; bytes --)
		fgetc (fin);
	myPrintString (szBuffer, downloadFontChar);
}
void pclDownloadFontHeader (int bytes) {
	char name [16];	//	Store the font name
	int i;

	++bufPtr;		//	Get rid of trailing bytes in PCL command.

	//  Eat the first 48 characters
	for (i = 0; i < 48; i++)
		fgetc (fin);
	
	//	Next 15 chars are font name
	for (i = 0; i < 15; i++)
			name[i] = fgetc (fin);

	//	Null-terminate name after last character
	for (i = 14; i > 0; i--)
		if (isgraph (name [i])) {
			i += 1; 
			break;
		}
	name [i] = '\0';

	sprintf (szBuffer, "[Download Font: %s]", name);
	myPrintString (szBuffer, downloadFontHeader);

	//	Eat the rest of the header
	for (i = 0; i < (bytes - 63); i++)
		fgetc (fin);
}

void pclEnableFixedUnderline (void) {
	myPrintString ("[Fixed Underline Enabled]", enableFixedUnderline);
}

void pclEnableFloatUnderline (void) {
	myPrintString ("[Float Underline Enabled]", enableFloatUnderline);
}
void pclEndRasterGraphics (void) {
	myPrintString ("[End of Raster Graphics]", endRasterGraphics);
}
void pclEnableOverlay (void) {
	myPrintString ("[Enable Macro Overlay]", enableOverlay);
}
void pclEnterHpglMode (int position) {
	int c;
	char i;
	char num [7];

	sprintf (szBuffer, "[Enter HPGL Mode Using %s Position]", 
		position == '0' ? "Previous HPGL" : "Current PCL");
	myPrintString (szBuffer, enterHpglMode);

	//
	//	Continue reading bytes looking for one of five legitimate
	//	Esc commands available in HP-GL/2.  If it's not one of them,
	//	discard the data.  Keep going until EOF or the beginning of 
	//	"enter PCL mode" command is found.  At that point, call pcl_
	//	enter_pcl_mode (function below) and return to the parser.
	//
	while ((i = fgetc (fin)) != EOF) {
		if (i != ESC) continue;
		i = fgetc (fin);
		if (i != '*' && i != '%') continue;
		
		//	Start of "return to PCL" command
		if (i == '%') {
			//	s/b 0 or 1
			i = fgetc (fin);
			//	s/b A
			c = fgetc (fin);
			if (c == 'A') {
				pclEnterPclMode (i);
				break;
			}
		//	Otherwise, keep looping for chars
		}
		else {
			//	Start of HP-GL/2 command
			if ((i = fgetc (fin)) != 'c') 
				continue;
			//	Load digits into num
			for (i = 0; i < 6; i++) {
				num [i] = c = getc (fin);
				if (c == EOF)
					return;
				if (!isdigit (c))
					num[i] = '\0';
			}
			i = atoi (num);

			switch (c) {
			case 'K':
				sprintf (szBuffer, "[HP-GL/2 Horizontal size: %d inches]", i);
				break;
			case 'L':
				sprintf (szBuffer, "[HP-GL/2 Vertical size: %d inches]", i);
				break;
			case 'T':
				sprintf (szBuffer, "[HP-GL/2 Set anchor point to CAP");
				break;
			case 'X':
				sprintf (szBuffer, "[HP-GL/2 Picture Fame Horiz. Size %d Decipoints]", i);
				break;
			case 'Y':
				sprintf (szBuffer, "[HP-GL/2 Picture Fame Vert. Size %d Decipoints]", i);
				break;
			}
			myPrintString (szBuffer, enterHpglMode);
		}
	}
}
void pclEnterPclMode (int position) {
	sprintf (szBuffer, "[Enter PCL Mode Using %s Position]", 
		position == '0' ? "Previous PCL " : "Current HPGL ");
	myPrintString (szBuffer, enterPclMode);
}
void pclEolWrap (int toggle) {
	sprintf (szBuffer, "[EOL Wrap Set %s]", 
		toggle == ON ? "On" : "Off");
	myPrintString (szBuffer, eolWrap);
}

void pclExecuteMacro (void) {
	myPrintString ("[Execute Macro]", executeMacro);
}

void pclFillRectangle (int style) {
	static char *fills [] = {
		"Solid Black", "Solid White", "Shaded Fill",
		"Cross-Hatched", "User-Defined", "Current Pattern"
	};
	sprintf (szBuffer, "[Fill Area with %s]", fills [style]);
	myPrintString (szBuffer, fillRectangle);
}

void pclFinish (void) {
	fflush (fout);
	fcloseall();

//	exit (1);
}

void pclFontStatus (int type) {
	sprintf (szBuffer, "[Make Font %s]", 
		type == Temporary ? "Temporary" : "Permanent");
	myPrintString (szBuffer, fontStatus);
}

void pclGraphicPresentation (int mode) {
	sprintf (szBuffer, "[Print Raster Image %s]",
		mode == 0 ? "Along Orientation of Logical Page"
		: "Along Page Width");
	myPrintString (szBuffer, graphicPresentation);
}

void pclHalfLineFeed (void) {
	myPrintString ("[Half-Line Feed]", halfLineFeed);
}

void pclHorzMove (int units) {
	sprintf (szBuffer, "Horiz. Move %d / 120\"]", units);
	myPrintString (szBuffer, horzMove);
}

void pclHorzPosition (int num, long int units) {
	char unitName [11];
	getUnitName (units, unitName);
	sprintf (szBuffer, "[Horizontal Position to %d %s]",
		num, unitName);
	myPrintString (szBuffer, horzPosition);
}

void pclIdentifyMacro (int id) {
	sprintf (szBuffer, "[Macro ID # %d]", id);
	myPrintString (szBuffer, identifyMacro);
}

void pclImagingPattern (int pattern) {
	static char *style [] = {
		"Solid Black", "Solid White",
		"HP Defined Shading", "HP Defined Cross-Hatch"
	};
	sprintf (szBuffer, "[Imaging Pattern: %s]", style [pattern]);
	myPrintString (szBuffer, imagingPattern);
}

void pclLineSpacing (int spacing) {
	sprintf (szBuffer, "[Spacing at %d lines/inch]", spacing);
	myPrintString (szBuffer, lineSpacing);
}

void pclLineTermination (char switches [3]) {
	int i;
	static const char *terminator [] = {"CR", "LF", "FF"};

	myPrintChar ('[', lineTermination);
	for (i = 0; i < 3; i++) {
		int j;
		j = 0;

		sprintf (szBuffer, "%s=", terminator[i]);

		if (switches [i] & 0x04) {
			myPrintString ("FF", lineTermination);
			j += 1;
		}
		if (switches [i] & 0x02) {
			if (j) myPrintChar ('+', lineTermination);
			myPrintString ("LF", lineTermination);
			j += 1;
		}
		if (switches [i] & 0x01) {
			if (j) myPrintChar ('+', lineTermination);
			myPrintString ("CR", lineTermination);
		}
		if (i < 2)
			myPrintChar (',', lineTermination);
	}
	myPrintChar (']', lineTermination);
}

void pclMakeMacroPerm (void) {
	myPrintString ("[Make Macro Permanent]", makeMacroPerm);
}

void pclMakeMacroTemp (void) {
	myPrintString ("[Make Macro Temporary]", makeMacroTemp);
}

void pclMakeCopies (int copies) {
	sprintf (szBuffer, "[Make %d %s]", copies, copies == 1 ? "Copy" : "Copies");
	myPrintString (szBuffer, makeCopies);
}

void pclOrientation (int j) {
	sprintf (szBuffer, "[%s ", j > 1 ? "Reverse" : "Normal");
	sprintf (szBuffer, "%s Orientation]", 
		j & 0x01 ? "Landscape" : "Portrait");
	myPrintString (szBuffer, orientation);
}

void pclPageLength (int lines) {
	sprintf (szBuffer, "[Page Length: %d Lines]", lines);
	myPrintString (szBuffer, pageLength);
}

void pclPageOrientation (int type) {

	static char *orientation [] = {
		"Portrait", "Landscape", "Reverse Portrait", "Reverse Landscape"
	};
	sprintf (szBuffer, "[Page Orientation is %s]", orientation [type]);
	myPrintString (szBuffer, pageOrientation);
}

void pclPageSize (int size) {
	
	int i, j;
	enum {Paper, Envelope};

	static char *name [] = {
		"Executive", "Letter", "Legal", "A4",
		"Monarch", "Com 10", "DL", "C5"
	};

	switch (size) {
	case  1: i = 0; j = Paper;	break;
	case  2: i = 1; j = Paper;	break;
	case  3: i = 2; j = Paper;	break;
	case 26: i = 3; j = Paper;	break;
	case 80: i = 4; j = Envelope;	break;
	case 81: i = 5; j = Envelope;	break;
	case 90: i = 6; j = Envelope;	break;
	case 91: i = 7; j = Envelope;	break;

	}
	sprintf (szBuffer, "[%s Size: %s]", j == Paper ? "Paper" : "Envelope", name [i]);
	myPrintString (szBuffer, pageSize);
}

void pclPaperSource (int source) {
	static char *paperSources[] = {
		//  There are new paper sources.
		//	"Eject Page", "Paper Tray Auto Feed", "Manual Feed", "Manual Envelope Feed"
		"Eject Page", "Upper Paper Tray", "Manual Feed", "Manual Envelope Feed", "Lower Paper Tray", "Envelope Feeder"
	};

	sprintf (szBuffer, "[Paper Source: %s]", paperSources [source]);
	myPrintString (szBuffer, paperSource);
}

void pclPatternTransparency (int opacity) {
	sprintf (szBuffer, "[Pattern is %s]", 
		opacity == 0 ? "Transparent" : "Opaque");
	myPrintString (szBuffer, patternTransparency);
}
void pclPerforationSkip (int toggle) {
	sprintf (szBuffer, "[Perforation Skip %s]",
		(toggle == 0 ? "Off" : "On"));
	myPrintString (szBuffer, perforationSkip);
}

void pclPictureFrameHorizontalSize (int points) {
	sprintf (szBuffer, "[Picture Frame Horizontal Size = %d]", points);
	myPrintString (szBuffer, pictureFrameHorizontalSize);
}

void pclPictureFrameVerticalSize (int points) {
	sprintf (szBuffer, "[Picture Frame Vertical Size = %d]", points);
	myPrintString (szBuffer, pictureFrameVerticalSize);
}

void pclPrimaryHeight (int points) {
 	sprintf (szBuffer, "[Primary Height: %d Points]", points);
	myPrintString (szBuffer, primaryHeight);
}   

void pclPrimaryPitch (int pitch) {
	sprintf (szBuffer, "[Primary Pitch %d]", pitch);
	myPrintString (szBuffer, primaryPitch);
}

void pclPushPopPosition (int toggle) {
	sprintf (szBuffer, "[%s Position]", toggle == 0 ? "Push" : "Pop");
	myPrintString (szBuffer, pushPopPosition);
}

void pclRasterCompress (int method) {
	static char *compression [] = {
		"Uncoded", "RLE", "TIFF", "Delta Row"
	};

	sprintf (szBuffer, "[Raster Compression: %s]", compression [method]);
	bufPtr++;
	myPrintString (szBuffer, rasterCompress);
}

void pclRasterHeight (int rows) {
	sprintf (szBuffer, "[Primary Height %d Rows]", rows);
	myPrintString (szBuffer, rasterHeight);
}

void pclRasterWidth (int pixels) {
	sprintf (szBuffer, "[Raster Width %d Pixels]", pixels);
	myPrintString (szBuffer, rasterWidth);
}

void pclRasterYOffset (int lines) {
	sprintf (szBuffer, "[Vertical Movement: %s Raster Lines]", lines);
	myPrintString (szBuffer, rasterYOffset);
}

void pclRectangle (int qty, int units, int direction) {
	char name [11];

	getUnitName (units, name);
	sprintf (szBuffer, "[Rectangle %s of %d %s]", 
		direction == VERT ? "Height" : "Width",
		qty, name);
	myPrintString (szBuffer, rectangle);
}

//	Char that is not PCL
void pclRegChar (int c) {
	if (c == FormFeed)
		myPrintString ("[FormFeed]", regChar);
	//
	// There is some defect where the characters are getting
	// an ascii value of 3 greater than what is actually 
	// getting printed.  Adjust the value here.
	// 
	else
		myPrintChar ((char) c - 3, regChar);
	
}

void pclRegistration (int distance, int margin) {
	sprintf (szBuffer, "[%s Registration: %d Decipoints]",
		margin == TOP ? "Top" : "Left", distance);
	myPrintString (szBuffer, registration);
}

void pclReset (void) {
	myPrintString ("[Reset Printer]", reset);
}

void pclResetMargins (void) {
	myPrintString ("[Reset Margins]", resetMargins);
}

void pclResolution (int nResolution) {
	sprintf (szBuffer, "[Resolution: %d DPI]", nResolution);
	myPrintString (szBuffer, resolution);
}

void pclRotatePrint (int rotation) {
	sprintf (szBuffer, "[Print Rotated %d Degrees]", rotation);
	myPrintString (szBuffer, rotatePrint);
}

void pclSelectFont (int type, int number) {
	sprintf (szBuffer, "[Select %s Font # %d]",
		type == Primary ? "Primary" : "Secondary", number);
	myPrintString (szBuffer, selectFont);
}

void pclSelectPattern (int pattern) {
	static char *builtIn [] = {
		"Horizontal Lines", "Vertical Lines",
		"Right Diagonal", "Left Diagonal",
		"Square Grid", "Diagonal Grid"
	};
		
	sprintf (szBuffer, "[Fill with %s]", builtIn [pattern - 1]);
	myPrintString (szBuffer, selectPattern);
}

void pclSelectShading (int shade) {
	sprintf (szBuffer, "[Shading of %d%%]", shade);
	myPrintString (szBuffer, selectShading);
}

void pclSendRasterData (int bytes) {
	int i;

	sprintf (szBuffer, "[Receive %d Bytes Raster Data]", bytes);
	myPrintString (szBuffer, sendRasterData);

	//	Eat up the data bytes
	for (i = 0; i < bytes; i++)
		fgetc (fin);
}

void pclSet10Pitch (void) {
	myPrintString ("[Set to 10 Pitch]", set10Pitch);
}

void pclSet12Pitch (void) {
	myPrintString ("[Set to 12 Pitch]", set12Pitch);
}

void pclSetCompressedMode (void) {
	myPrintString ("[Compressed Mode On]", setCompressedMode);
}

void pclSetLeftMargin (int column) {
	sprintf (szBuffer, "[Set Left Margin to %d]", column);
	myPrintString (szBuffer, setLeftMargin);
}

void pclSetRightMargin (int column) {
	sprintf (szBuffer, "[Set Right Margin to %d]", column);
	myPrintString (szBuffer, setRightMargin);
}

void pclSetPictureFrameAnchorPoint () {
	myPrintString ("[Set Picture Frame Anchor Point]", setPictureFrameAnchorPoint);
}

void pclSourceTransparency (int opacity) {
	sprintf (szBuffer, "[Source is %s]",
		opacity == 0 ? "Transparent" : "Opaque");
	myPrintString (szBuffer, sourceTransparency);
}

void pclSpacingType (int type) {
	sprintf (szBuffer, "[%s Spacing]",
		type == 1 ? "Proportional" : "Fixed");
	myPrintString (szBuffer, spacingType);
}

void pclStartMacroDef (void) {
	myPrintString ("[Start of Macro Definition]", startMacroDef);
}

void pclStartRasterGraphics (int position) {
	sprintf (szBuffer, "[Start Raster Graphics at %s]",
		position == 1 ? "Current Cursor" : "Left Graphic Margin");
	myPrintString (szBuffer, startRasterGraphics);
}

void pclStopMacroDef (void) {
	myPrintString ("[End of Macro Definition]", stopMacroDev);
}    

void pclStrokeWeight (int weight) {
	static char * weightName [] = {
		"Ultra Thin", "Extra Thnin", "Thin", 
		"Extra Light", "Demi Leight", "Semi Light",
		"Medium",
		"Semi Bold", "Demi Bold", "Bold", "Extra Bold",
		"Black", "Extra Black", "Ultra Black"
	};
	
	sprintf (szBuffer, "[%s Stroke Weight]", weightName [weight]);
	myPrintString (szBuffer, strokeWeight);
}

void pclSymbolSet (int idNum, int idLtr) {
	if (idLtr == 'U' || idLtr == 'u') {
		if (idNum == 8)
			myPrintString ("[Roman-8 Symbol Set]", symbolSet);
		if (idNum == 10)
			myPrintString ("[IBM-PC Symbol Set]", symbolSet);
		return;
	}
	sprintf (szBuffer, "[Symbol Set %2d%c]", idNum, toupper (idLtr));
	myPrintString (szBuffer, symbolSet);
}

void pclTextLength (int length) {
	sprintf (szBuffer, "[Text Length: %d Lines]", length);
	myPrintString (szBuffer, textLength);
}

void pclTopMargin (int margin) {
	sprintf (szBuffer, "[Top Margin: %d Lines]", margin);
	myPrintString (szBuffer, topMargin);
}

void pclTransparentData (void) {
	//	Prints characters that normally are
	//	commands to the LaserJet.  Ex: Esc, FF

	//	char numStr [6];
	int c, i, j;

	j = ourAtoi ();
	sprintf (szBuffer, "[Transparent Print of Next %d Bytes]", j);
	myPrintString (szBuffer, transparentData);
	//	Output the transparent data
	for (i = 0; i < j; i++) {
		c = fgetc (fin);
		myPrintChar ((char) c, transparentData);
	}
	combinedCommand = NO;
}
void pclTypeface (int face) {
	sprintf (szBuffer, "[Typeface %d]", face);
	myPrintString (szBuffer, typeface);
}

void pclUnitOfMeasure (int units) {
	sprintf (szBuffer, "[Number of units per inch = %d]", units);
	myPrintString (szBuffer, unitOfMeasure);
}

void pclUserDefinedPattern (int nBytes) {
	int i;

	sprintf (szBuffer, "[User defined pattern with %d bytes]", nBytes);
	myPrintString (szBuffer, userDefinedPattern);

	//	Eat up the data bytes
	for (i = 0; i < nBytes; i++)
		fgetc (fin);

}

void pclVertMove (int units) {
	sprintf (szBuffer, "[Vert. Move of %d / 48\"]", units);
	myPrintString (szBuffer, vertMove);
}

void pclVertPosition (int num, long int units) {
	char unitName [11];

	getUnitName (units, unitName);
	sprintf (szBuffer, "[Vertical Position to %d %s]", num, unitName);
	myPrintString (szBuffer, vertPosition);
}

//
//	Pcl Support Functions
//
static void getUnitName (long int unit, char *unitName) {
	switch (unit) {
	
	case POINTS:		strcpy (unitName, "Points");	
						break;
	case DECIPOINTS:	strcpy (unitName, "DeciPoints");	
						break;
	case ROWS:			strcpy (unitName, "Rows");	
						break;
	case COLUMNS:		strcpy (unitName, "Columns");	
						break;
	default:			strcpy (unitName, "? Units");	
						break;
	}
}


void pclUnknownCommand () {
	sprintf (szBuffer, "[Unknown Command %s]", buffer);
	myPrintString (szBuffer, unknownCommand);
}

void pclUnknownPageControlCommand () {
	sprintf (szBuffer, "[Unknown Page Control Command %s]", buffer);
	myPrintString (szBuffer, unknownPageControlCommand);
}

void myPrintString (char *szString, int nValue) {
	if (shouldPrint (nValue)) {
		fprintf (fout, "%s", szString);
		if (nValue != regChar) fprintf (fout, "\r\n");	
	}	
}

void myPrintChar (char cChar, int nValue) {
	if (shouldPrint (nValue)) {
		fputc (cChar, fout);
		if (nValue != regChar) fprintf (fout, "\r\n");
	}
}


int shouldPrint (int nValue) {

	if (nValue > (sizeof (printFunctions) / sizeof (printProp))) return (false);

	if (bPrintPlus) 
		return (printFunctions [nValue].shouldPrint);
	else if (bPrintMinus)
		return (!printFunctions [nValue].shouldPrint);
	else 
		return true;

}