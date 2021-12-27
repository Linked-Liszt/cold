//  Routines for reading in and looking at Roper (formerly Princeton Instruments) 
//  '*.spe' files from a CCD.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#include "WinViewHeader.h"


#ifndef _WIN_VIEW_READ_
#define _WIN_VIEW_READ_

/*TODO: REMOVE THIS HACK */
#define __LITTLE_ENDIAN__ 1

#define HEADER_LENGTH		4100


#if (!defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__))
	#if defined(BYTE_ORDER) && defined(BIG_ENDIAN)
		#if (BYTE_ORDER==BIG_ENDIAN)	/* the mac is BIG_ENDIAN, Intel is LITTLE_ENDIAN */
		#define __BIG_ENDIAN__ 1
		#endif
	#elif defined(LITTLE_ENDIAN)		/* don't define anything for little endian machines */
	#elif defined(__BIG_ENDIAN__)
		#define __BIG_ENDIAN__ 1
	#elif defined(__POWERPC__) || defined(__ppc__) 
		#define __BIG_ENDIAN__ 1
	#endif
#endif
#if ((!defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)))
	#error ONE these must be defined;
	exit(1);
#endif

#if ((defined(__LITTLE_ENDIAN__) && defined(__BIG_ENDIAN__)))
	#error ONLY ONE these must be defined;
	exit(1);
#endif

#ifndef MAX
#define MAX(X,Y) ( ((X)<(Y)) ? (Y) : (X) )
#endif
#ifndef MIN
#define MIN(X,Y) ( ((X)>(Y)) ? (Y) : (X) )
#endif


int WinViewReadHeader(FILE *fid, WinViewHeader *head);
int WinViewParseHeader(char *buf, WinViewHeader *head);
int WinViewReadROI(FILE *fid, void  **vbuf, size_t xlo, size_t xhi, size_t ylo, size_t yhi, WinViewHeader *head);
int WinViewWriteROI(FILE *fid, char *vbuf, int itype, size_t xdim, size_t xlo, size_t xhi, size_t ylo, size_t yhi);
char *onlyNamePartOfFile(char *full, char *name);
char *WinViewControllers(int itype, char *stype);
char *WinViewFileTypeString(int itype,char *stype);
int	WinView_itype2len(int itype);
int	checkTypeSizes(void);
void printBufferHex(void *buffer, size_t bufSizeOf, size_t n, size_t offset);
double NumberByKey(char *key, char *list, char keySepStr, char listSepStr);
long IntByKey(char *key, char *list, char keySepChar, char listSepChar);
char* StringByKey(char *key, char *list, char keySepChar, char listSepChar, int maxLen);


/* for .spe itype==
  0	"float (4 byte)"
  1	"long integer (4 byte)"
  2	"integer (2 byte)"
  3	"unsigned integer (2 byte)"
  4	"string/char (1 byte)"
  5	"double (8 byte)"
  6	"signed int8 (1 byte)"
  7	"unsigned int8 (1 byte)"
*/


#endif	/* _WIN_VIEW_READ_ */
