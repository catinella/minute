/*------------------------------------------------------------------------------------------------------------------------------
//
//                                            __  __ _             _   _     _____    
//                                           |  \/  (_)_ __       | | | |   |_   _|__ 
//                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
//                                           | |  | | | | | |_____| |_| |_____| |  __/
//                                           |_|  |_|_|_| |_|      \___/      |_|\___|
//                                                    Minimal Unit Test support
//
// File:      minute.cpp
//
// Author:    Silvano Catinella
//
// Description
//	
//
// Editor parameters: 128 cols, ts=6
------------------------------------------------------------------------------------------------------------------------------*/
#include <minute.h>
#include <string>
#include <vector>

#define MINUTE_MAXARGSIZE 64
#define MINUTE_MAXNUMARGS 16

using namespace std;

typedef struct {
	string name;
	string value;
} arg_t;

typedef uint8_t dbIdx_t;

static vector<arg_t> internalDB = {};

static dbIdx_t _findArg (const string &name_a) {
	dbIdx_t t     = 0;
	bool    found = false;

	for (arg_t item : internalDB) {
		if (item.name == name_a) {
			found = true;
			break;
		}
	}
	if (found == false) t = MINUTE_MAXNUMARGS + 1;
	return(t);
}

//------------------------------------------------------------------------------------------------------------------------------
//                                          P U B L I C   F U N C T I O N S
//------------------------------------------------------------------------------------------------------------------------------

bool fileArgumentsDb_set (const string arg_a, const string value) {
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

	// Check for the function's argumennts
	pos = _findArg(arg_a);
	if (pos < MINUTE_MAXNUMARGS) {
		// Argument's avalue update
		internalDB[pos].value = value;
		out = true;

	} else {
		arg_t tmp = {arg_a, value};
		internalDB.push_back(tmp);
		out = true;
	}

	return(out);
}

bool fileArgumentsDb_get (const string &arg_a, string &value) {
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
		value = internalDB[pos].value;
		out = true;
	}
	return(out);
}

