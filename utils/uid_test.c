#include "uid.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void Unitest(void);

int main()
{
	Unitest();
	return EXIT_SUCCESS;
}

void Unitest(void)
{
	/*create some ids*/
	
	guid_t my_uid1 = UIDCreate();
	guid_t my_uid2 = UIDCreate();
	guid_t my_uid3 = UIDCreate();
	guid_t my_uid4 = UIDCreate();	
	
	assert(!UIDIsSame(my_uid1, my_uid2));
	assert(!UIDIsSame(my_uid1, my_uid3));
	assert(!UIDIsSame(my_uid4, my_uid2));	
	assert(!UIDIsSame(my_uid3, my_uid2));	
	
	my_uid1 = g_bad_uid;
	
	assert(UIDIsBad(my_uid1));
	
	puts("u passed");

}

