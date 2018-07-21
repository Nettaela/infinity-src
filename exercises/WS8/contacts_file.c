#include <stdio.h>
#include <stdlib.h>

typedef struct DateOfBirth
{
	size_t day;
	size_t month;
	size_t year;
}dob_t;

typedef struct Contact
{
	char f_name[50];
	char l_name[50];
	dob_t DateOfBirth;
	size_t ID;
}cont_t;

int main()
{
	static cont_t array_of_contacts[10] = {
	
	{"gavriel", "suna",      {22,02,1991}, 316879642},
	{"doron",   "feldman",   {05,12,1988}, 200662575},
	{"uri",     "abraham",   {20,11,1981}, 049805385},
	{"ziv",     "shoshany",  {11,10,1988}, 200554947},
	{"michael", "maizenberg",{22,10,1980}, 040407272},
	{"daniel",  "gomon",     {23,02,1986}, 309285039},
	{"meytal",  "goren",     {23,12,1988}, 301879276},
	{"evgeny",  "oyffe",     {21,08,1988}, 309392876},
	{"tamar",	"admoni",	 {17,08,1986}, 021995733},
	{"nicole",  "dolginov",  {07,11,1996}, 316062843} };
	
	
	array_of_contacts[0].f_name = "gavriel";
	array_of_contacts[0].l_name = "suna";
	array_of_contacts[0].DateOfBirth.day = 
	array_of_contacts[0].DateOfBirth.month = 
	array_of_contacts[0].DateOfBirth.year = 


}
	
