#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void unitestbubble(void);
void unitestinsertion(void);
void unitestselection(void);
void unitestcounting(void);
int IsSorted(const void *data1, const void *data2);
int GetVal(const void *val, void *param);
static int IsSortSuccess(int *array, size_t arr_size);

int main()
{
	unitestbubble();
	unitestinsertion();
	unitestselection();
	unitestcounting();
    return EXIT_SUCCESS;
}

void unitestbubble(void)
{
   int array[] = {4,38, 2,7,-100 };

    BubbleSort(
            array,
            sizeof(int),
            5,
            IsSorted);

    assert(IsSortSuccess(array, 5));
	
    puts("selection sort success");
}

void unitestinsertion(void)
{
    int array[] =  {4,38, 2,7,-100};

    InsertionSort(
            array,
            5,
            IsSorted);

    assert(IsSortSuccess(array, 5));
	
    puts("insertion sort success");
}

void unitestselection(void)
{
    int array[] = {2,435,435,-342,54,0,-239};
  
    SelectionSort(
            array,
            7,
            IsSorted);

 	assert(IsSortSuccess(array, 7));
	
    puts("selection sort success");
}
void unitestcounting(void)
{
    int array[] = {1,7,3,5,4,6,2};
	void *sorted_array = malloc(7*sizeof(int));
	 
    CountingSort(
            array,
            sizeof(int),
            7,
            sorted_array,
            1,
            7,
            GetVal,
            NULL);


	assert(IsSortSuccess(sorted_array, 7));
	
    puts("counting sort success");

}

int IsSorted(const void *data1, const void *data2)
{
    return (*(int*)data1 <= *(int*)data2);
}

int GetVal(const void *val, void *param)
{
	(void)param;
	return *(int*)val;
}

int IsSortSuccess(int *array, size_t arr_size)
{
	size_t i = 0;
	for(i = 0 ; i < arr_size - 1 ; ++i)
	{
		if(array[i] > array[i + 1])
		{
			return 0;
		}
	}
	return 1;
}


