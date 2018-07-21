#include <stdio.h>	/*for printing and file functions */
#include <stdlib.h> /*for exit*/
#define ARRSIZE(x) (sizeof(x)/ sizeof(x[0]))
#define CONT_NUM 11

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

static int WriteArrayToFile(cont_t array[], size_t array_size, char *path);
static int ReadArrayfromFile(cont_t array[], size_t array_size, char *path);

int main()
{
	char *path = "contacts.txt";
	unsigned int i = 0;
	static cont_t array_of_contacts_read[CONT_NUM]; 

	static cont_t array_of_contacts[CONT_NUM] = {

	{"gavriel", "suna",      {22,02,1991}, 316879642},
	{"doron",   "feldman",   {05,12,1988}, 200662575},
	{"uri",     "abraham",   {20,11,1981}, 229805385},
	{"ziv",     "shoshany",  {11,10,1988}, 200554947},
	{"michael", "maizenberg",{22,10,1980}, 040407272},
	{"daniel",  "gomon",     {23,02,1986}, 309285039},
	{"meytal",  "goren",     {23,12,1988}, 301879276},
	{"evgeny",  "oyffe",     {21,8,1988},  309392876},
	{"tamar",	"admoni",	 {17,8,1986},  221995733},
	{"nicole",  "dolginov",  {07,11,1996}, 316062843},
	{"netta",   "elazari", 	 {30,3,1988},  200286763} };
	
		
	WriteArrayToFile(array_of_contacts, CONT_NUM, path);
	ReadArrayfromFile(array_of_contacts_read, CONT_NUM, path);

    for (i = 0 ; i < ARRSIZE(array_of_contacts_read) ; ++i)
    {
    	/*print out the contacts that were read from file*/
    	printf("%10s %10s - %lu - %lu\n",array_of_contacts_read[i].f_name,
    									 array_of_contacts_read[i].l_name,
    									 array_of_contacts_read[i].DateOfBirth.year, 
    									 array_of_contacts_read[i].ID);
    }
    
	return EXIT_SUCCESS;

}


static int WriteArrayToFile(cont_t array[], size_t array_size, char *path)
{
	size_t result = 0;
	FILE * contacts_file = NULL;
	contacts_file = fopen(path , "w");
	
	if (contacts_file == NULL) 
	{
		perror("open file to write");
		return EXIT_FAILURE;
	}
	result = fwrite(array, sizeof(cont_t), array_size, contacts_file);
	
	if (result != array_size)
	{
		printf("%lu elements written\n", result); /*prints only if the number is different than the expected size*/
	}

	if(fclose(contacts_file) != 0)
    {
    	perror("close file for writing"); /*perror adds fail of success at the end*/ 
    	return EXIT_FAILURE;
    }
    
	return EXIT_SUCCESS;

}

static int ReadArrayfromFile(cont_t array[], size_t array_size, char *path)
{
 	size_t result = 0;
	FILE * contacts_file = NULL;
 	contacts_file = fopen(path, "r");
    if (contacts_file == NULL) 
	{
		perror("open file to read");
		return EXIT_FAILURE;
	}
	
	result = fread(array, sizeof(cont_t), array_size, contacts_file);
	if (result != array_size)
	{
		printf("%lu elements read\n", result);
	}
	
    if(fclose(contacts_file) != 0)
    {
    	perror("close file for writings");
    	return EXIT_FAILURE;
    }
    
	return EXIT_SUCCESS;

}
	
