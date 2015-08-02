/* code.c - Handles Code 11, 39, 39+ and 93 */

/*
    libzint - the open source barcode library
    Copyright (C) 2008 Robin Stuart <robin@zint.org.uk>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the project nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/

/* In version 0.5 this file was 1,553 lines long! */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define SODIUM	"0123456789-"
#define SILVER	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-. $/+%abcd"

static const char *C11Table[11] = {"111121", "211121", "121121", "221111", "112121", "212111", "122111",
	"111221", "211211", "211111", "112111"};


/* Code 39 tables checked against ISO/IEC 16388:2007 */
	
/* Incorporates Table A1 */

static const char *C39Table[43] = { "1112212111", "2112111121", "1122111121", "2122111111", "1112211121",
	"2112211111", "1122211111", "1112112121", "2112112111", "1122112111", "2111121121",
	"1121121121", "2121121111", "1111221121", "2111221111", "1121221111", "1111122121",
	"2111122111", "1121122111", "1111222111", "2111111221", "1121111221", "2121111211",
	"1111211221", "2111211211", "1121211211", "1111112221", "2111112211", "1121112211",
	"1111212211", "2211111121", "1221111121", "2221111111", "1211211121", "2211211111",
	"1221211111", "1211112121", "2211112111", "1221112111", "1212121111", "1212111211",
	"1211121211", "1112121211"};
/* Code 39 character assignments (Table 1) */

static const char *EC39Ctrl[128] = {"%U", "$A", "$B", "$C", "$D", "$E", "$F", "$G", "$H", "$I", "$J", "$K",
	"$L", "$M", "$N", "$O", "$P", "$Q", "$R", "$S", "$T", "$U", "$V", "$W", "$X", "$Y", "$Z",
	"%A", "%B", "%C", "%D", "%E", " ", "/A", "/B", "/C", "/D", "/E", "/F", "/G", "/H", "/I", "/J",
	"/K", "/L", "-", ".", "/O", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "/Z", "%F",
	"%G", "%H", "%I", "%J", "%V", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "%K", "%L", "%M", "%N", "%O",
	"%W", "+A", "+B", "+C", "+D", "+E", "+F", "+G", "+H", "+I", "+J", "+K", "+L", "+M", "+N", "+O",
	"+P", "+Q", "+R", "+S", "+T", "+U", "+V", "+W", "+X", "+Y", "+Z", "%P", "%Q", "%R", "%S", "%T"};
/* Encoding the full ASCII character set in Code 39 (Table A2) */

static const char *C93Ctrl[128] = {"bU", "aA", "aB", "aC", "aD", "aE", "aF", "aG", "aH", "aI", "aJ", "aK",
	"aL", "aM", "aN", "aO", "aP", "aQ", "aR", "aS", "aT", "aU", "aV", "aW", "aX", "aY", "aZ",
	"bA", "bB", "bC", "bD", "bE", " ", "cA", "cB", "cC", "cD", "cE", "cF", "cG", "cH", "cI", "cJ",
	"cK", "cL", "cM", "cN", "cO", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "cZ", "bF",
	"bG", "bH", "bI", "bJ", "bV", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "bK", "bL", "bM", "bN", "bO",
	"bW", "dA", "dB", "dC", "dD", "dE", "dF", "dG", "dH", "dI", "dJ", "dK", "dL", "dM", "dN", "dO",
	"dP", "dQ", "dR", "dS", "dT", "dU", "dV", "dW", "dX", "dY", "dZ", "bP", "bQ", "bR", "bS", "bT"};

static const char *C93Table[47] = {"131112", "111213", "111312", "111411", "121113", "121212", "121311",
	"111114", "131211", "141111", "211113", "211212", "211311", "221112", "221211", "231111",
	"112113", "112212", "112311", "122112", "132111", "111123", "111222", "111321", "121122",
	"131121", "212112", "212211", "211122", "211221", "221121", "222111", "112122", "112221",
	"122121", "123111", "121131", "311112", "311211", "321111", "112131", "113121", "211131",
	"121221", "312111", "311121", "122211"};

/* Global Variables for Channel Code */
int S[11], B[11];
long value;
long target_value;
char pattern[30];
	
int c39(struct zint_symbol *symbol, unsigned char source[], int length)
{ /* Code 39 */
	unsigned int i;
	unsigned int counter;
	char check_digit;
	int error_number;
	char dest[775];
	char localstr[2] = { 0 };
	
	error_number = 0;
	counter = 0;

	if((symbol->option_2 < 0) || (symbol->option_2 > 1)) {
		symbol->option_2 = 0;
	}
	
	if((symbol->symbology == BARCODE_LOGMARS) && (length > 59)) {
			strcpy(symbol->errtxt, "Input too long");
			return ERROR_TOO_LONG;
	} else if(length > 74) {
			strcpy(symbol->errtxt, "Input too long");
			return ERROR_TOO_LONG;
	}
	to_upper(source);
	error_number = is_sane(SILVER , source, length);
	if(error_number == ERROR_INVALID_DATA) {
		strcpy(symbol->errtxt, "Invalid characters in data");
		return error_number;
	}

	/* Start character */
	strcpy(dest, "1211212111");

	for(i = 0; i < length; i++) {
		lookup(SILVER, C39Table, source[i], dest);
		counter += posn(SILVER, source[i]);
	}
	
	if((symbol->symbology == BARCODE_LOGMARS) || (symbol->option_2 == 1)) {
		
		counter = counter % 43;
		if(counter < 10) {
			check_digit = itoc(counter);
		} else {
			if(counter < 36) {
				check_digit = (counter - 10) + 'A';
			} else {
				switch(counter) {
					case 36: check_digit = '-'; break;
					case 37: check_digit = '.'; break;
					case 38: check_digit = ' '; break;
					case 39: check_digit = '$'; break;
					case 40: check_digit = '/'; break;
					case 41: check_digit = '+'; break;
					case 42: check_digit = 37; break;
					default: check_digit = ' '; break; /* Keep compiler happy */
				}
			}
		}
		lookup(SILVER, C39Table, check_digit, dest);
	
		/* Display a space check digit as _, otherwise it looks like an error */
		if(check_digit == ' ') {
			check_digit = '_';
		}
		
		localstr[0] = check_digit;
		localstr[1] = '\0';
	}
	
	/* Stop character */
	concat (dest, "121121211");
	
	if((symbol->symbology == BARCODE_LOGMARS) || (symbol->symbology == BARCODE_HIBC_39)) {
		/* LOGMARS uses wider 'wide' bars than normal Code 39 */
		counter = strlen(dest);
		for(i = 0; i < counter; i++) {
			if(dest[i] == '2') {
				dest[i] = '3';
			}
		}
	}
	
	expand(symbol, dest);
	
	if(symbol->symbology == BARCODE_CODE39) {
		ustrcpy(symbol->text, (unsigned char*)"*");
		uconcat(symbol->text, source);
		uconcat(symbol->text, (unsigned char*)localstr);
		uconcat(symbol->text, (unsigned char*)"*");
	} else {
		ustrcpy(symbol->text, source);
		uconcat(symbol->text, (unsigned char*)localstr);
	}
	return error_number;
}
