#include <stdio.h> 	/*for printing*/
#include <string.h>	/*for strcpy*/
#include <stdlib.h>	/*for exit and mem allocation*/

typedef struct structFunc structFunc_t;

typedef void (*print_func_t)(void* data);
typedef void (*add_func_t)(structFunc_t *struct_ptr, int num);
typedef void (*free_func_t)(void* data);

void PrintInt(void* data);
void PrintFloat(void* data);
void PrintStr(void* data);

void AddInt(structFunc_t *struct_ptr, int num);
void AddFloat(structFunc_t *struct_ptr, int num);
void AddStr(structFunc_t *struct_ptr, int num);

void FreeInt(void* data);
void FreeFloat(void* data);
void FreeStr(void* data);

struct structFunc
{
	void *data;
	print_func_t print_f;
	add_func_t add_f;
	free_func_t free_f;
};

int main()
{

	char *stra = "ma string";
	char *stringi = malloc( (strlen(stra) + 1) * sizeof(char)); /*set a pointer for string*/
	float floati = 3.2;
	int inti = 100;
	unsigned int i = 0;
	
	
	/*initialize array of structs*/
	static structFunc_t array_of_structs[3] =

	{
	{  0, PrintInt,   AddInt,   FreeInt  },
	{  0, PrintFloat, AddFloat, FreeFloat},
	{  0, PrintStr,	  AddStr,   FreeStr  }};
	
	
	if(stringi == NULL)
	{
		perror("memory allocation");
		return EXIT_FAILURE;
	}
	
	/*initialize data ptr as a string*/
	strcpy(stringi, stra);
	
	/*initialize only data void pointers - runtime*/
	*(int*)&array_of_structs[0].data = inti;
	*(float*)&array_of_structs[1].data = floati;
	array_of_structs[2].data = stringi;	
	
	/*check that everything is in place*/
	printf("int is: %d\nfloat is: %.2f\nstring is: %s \n", 
										*(int*)&array_of_structs[0].data,  
										*(float*)&array_of_structs[1].data, 										(char*)array_of_structs[2].data);
				
	/*loop all the print functions*/	
	for(i = 0; i < sizeof(array_of_structs)/sizeof(array_of_structs[0]) ; ++i)
	{	
		array_of_structs[i].print_f(array_of_structs[i].data);
	}

	/*loop all the add functions followed by a print func to check*/
	for(i = 0; i < sizeof(array_of_structs)/sizeof(array_of_structs[0]) ; ++i)
	{
		array_of_structs[i].add_f(&array_of_structs[i], inti);
		array_of_structs[i].print_f(array_of_structs[i].data);
	}
	
	/*check again for null terminator and that it can work more than once*/
	for(i = 0; i < sizeof(array_of_structs)/sizeof(array_of_structs[0]) ; ++i)
	{
		array_of_structs[i].add_f(&array_of_structs[i], inti);
		array_of_structs[i].print_f(array_of_structs[i].data);
	}

	/*loop all the free functions*/
	for(i = 0; i < sizeof(array_of_structs)/sizeof(array_of_structs[0]) ; ++i)
	{	
		array_of_structs[i].free_f(array_of_structs[i].data);
	}
	
	return EXIT_SUCCESS;
	
}

void PrintInt(void* data)
{
	printf("%d\n", *(int*)&data);
}

void PrintFloat(void* data)
{
	printf("%.2f\n",*(float*)&data);
}

void PrintStr(void* data)
{
	printf("%s \n", (char*)data);
}

void AddInt(structFunc_t *struct_ptr, int num)
{
	*(int*)&struct_ptr->data += num;
}

void AddFloat(structFunc_t *struct_ptr, int num)
{
	*(float*)&struct_ptr->data += (float)num;
}

void AddStr(structFunc_t *struct_ptr, int num)
{
	char *str_ptr = NULL;
	char str_num[20] = {0};
	int data_str_len = strlen(struct_ptr->data);
	sprintf(str_num, "%d", num);
	
	struct_ptr->data = realloc(struct_ptr->data, (data_str_len + 1 + strlen(str_num)) * sizeof(char));
	
	if(struct_ptr->data == NULL)
	{
		perror("allocation in AddStr");
		return;
	}
	
	str_ptr = struct_ptr->data;

	strcat(str_ptr + data_str_len, str_num);

}

void FreeInt(void* data)
{
	(void)data;
}

void FreeFloat(void* data)
{
	(void)data;
}

void FreeStr(void* data)
{
	free(data);
	data=NULL;
}


















