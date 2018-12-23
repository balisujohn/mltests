// Michael Ivanitskiy

#ifndef ERROR_UTILITIES
#define ERROR_UTILITIES

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

// STANDARD: Errors will print the message (and perform other actions) if the input statement is true
// they will also return the value of the input statement

// real error checking
void WARNING( string const& msg );
void ERROR( string const& msg );
void ERROR_FATAL( string const& msg );
bool CHK_WARNING( bool cond, string const& msg );
bool CHK_ERROR( bool cond, string const& msg );
bool CHK_ERROR_FATAL( bool cond, string const& msg );
void TEST( string const& msg );
void CHK_TEST( bool cond, string const& msg );
void TEST();
void __DEBUG( string const& msg );
void __DEBUG();

int num_tests = 0;
const bool PRINT_DEBUG = true;
const bool PRINT_TEST = true;

// const bool PRINT_DEBUG = true;
// const bool PRINT_TEST = true;

// print error

void WARNING( string const& msg )
{
	cerr << "WARNING:\t" << msg << "\n";
}

void ERROR( string const& msg )
{
	cerr << "ERROR:\t" << msg << "\n";
}

void ERROR_FATAL( string const& msg )
{
	cerr << "===============================\n";
	cerr << "FATAL ERROR:\t" << msg << "\n";
	exit(1);
}

// print upon condition

bool CHK_WARNING( bool cond, string const& msg )
{
	if (cond) WARNING(msg);
	return cond;
}

bool CHK_ERROR( bool cond, string const& msg )
{
	if (cond) ERROR(msg);
	return cond;
}

bool CHK_ERROR_FATAL( bool cond, string const& msg )
{
	if (cond) ERROR_FATAL(msg);
	return cond;
}

// testing/debug prints

void TEST( string const& msg )
{
	cerr << "\tTEST:\t" << msg << "\n";
}

void CHK_TEST( bool cond, string const& msg )
{
	if (cond) TEST(msg);
}

void TEST()
{
	if (PRINT_TEST)
	{
		cerr << "\tTEST__" << num_tests << "\n";
		num_tests++;
	}
}

void TEST(int input)
{
	if (PRINT_TEST)
	{
		cerr << "\tTEST__" << input << "\n";
		num_tests = input + 1;
	}
}


void __DEBUG( string const& msg )
{
	if (PRINT_DEBUG) cerr << "\tDEBUG:\t" << msg << "\n";
}

void __DEBUG()
{
	if (PRINT_DEBUG) 
	{
		cerr << "\tDEBUG__" << num_tests << "\n";
		num_tests++;
	}
}

void DEBUG_VEC_CONTENTS(vector < size_t > & vec)
{
	for ( size_t x : vec )
	{
		cerr << x << " ";
	}
	cerr << endl;
}

#endif
