/*------------------------------------------------------------------------------------------------------------------------------
//
//                                            __  __ _             _   _     _____    
//                                           |  \/  (_)_ __       | | | |   |_   _|__ 
//                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
//                                           | |  | | | | | |_____| |_| |_____| |  __/
//                                           |_|  |_|_|_| |_|      \___/      |_|\___|
//                                                    Minimal Unit Test support
//
// File:      minute.c
//
// Author:    Silvano Catinella
//
// Description
//
//
// Editor parameters: 128 cols, ts=6
------------------------------------------------------------------------------------------------------------------------------*/
#include <minute.h>
#include <string.h>
#include <ctype.h>

#define MINUTE_MAXARGSIZE 64
#define MINUTE_MAXNUMARGS 16

typedef struct {
	char name[MINUTE_MAXARGSIZE];
	char value[MINUTE_MAXARGSIZE];
} arg_t;

typedef uint8_t dbIdx_t;

static arg_t   internalDB[MINUTE_MAXNUMARGS];
static dbIdx_t internalDB_idx = 0;
static bool    initFlag = false;

static dbIdx_t _findArg (const char* name_a) {
	dbIdx_t t     = 0;
	bool    found = false;

	if (name_a != NULL && *name_a != '\0') {
		while (*(internalDB[t].name) != '\0' && t < MINUTE_MAXNUMARGS) {
			if (strcmp(name_a, internalDB[t].name) == 0) {
				found = true;
				break;
			} else
				t++;
		}
	}
	if (found == false) t = MINUTE_MAXNUMARGS + 1;
	return(t);
}

static void _initDB () {
	for (dbIdx_t t=0; t<MINUTE_MAXNUMARGS; t++) {
		memset(internalDB[t].name,  '\0', MINUTE_MAXARGSIZE * sizeof(char));
		memset(internalDB[t].value, '\0', MINUTE_MAXARGSIZE * sizeof(char));
	}
	return;
}

//------------------------------------------------------------------------------------------------------------------------------
//                                          P U B L I C   F U N C T I O N S
//------------------------------------------------------------------------------------------------------------------------------

char* _strdup (const char* src) {
	unsigned int size = (strlen(src)+1)*sizeof(char);
	char *out = (char*)malloc(size);
	memcpy(out, src, size);
	return(out);
}

bool fileArgumentsDb_set (const char *arg_a, const char *value) {
	//
	// Description:
	//	This function allows you to set/update an argument's avue in the insternal static DB
	//
	// Returned value:
	//	true   the defined argument has been updated or created
	//	false  operation failed for invalid fata, overflow....
	//
	dbIdx_t pos = 0;
	bool    out = false;
	if (initFlag == false) {
		_initDB();
		initFlag = true;
	}

	// Check for the function's argumennts
	if (arg_a != NULL && *arg_a != '\0') {
		pos = _findArg(arg_a);
		if (pos < MINUTE_MAXNUMARGS) {
			// Argument's avalue update
			strcpy(internalDB[pos].value, value);
			out = true;

		} else if (internalDB_idx < MINUTE_MAXNUMARGS) {
			strcpy(internalDB[internalDB_idx].name, arg_a);
			strcpy(internalDB[internalDB_idx].value, value);
			internalDB_idx++;
			out = true;
		}
	}
	return(out);
}

bool fileArgumentsDb_get (const char *arg_a, char *value) {
	//
	// Description:
	//	This function retrive a previousely stored argument's value and copy its value in the second argument
	//
	// Returned value:
	//	false  operation failed: argument defined item has not be found
	//	true   ok
	//
	bool    out = false;
	dbIdx_t pos = 0;
	
	pos = _findArg(arg_a);
	if (pos < MINUTE_MAXNUMARGS) {
		if (value != NULL)
			strcpy(value, internalDB[pos].value);
		out = true;
	}
	return(out);
}

