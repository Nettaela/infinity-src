#include <stdio.h>		/*for printing*/
#include <stdlib.h>		/*for allocating memory*/


void UniTest(void);
int LoneSurvivor(int NumOfPeople);

int main()
{
	UniTest();
	
	return EXIT_SUCCESS;

}

int LoneSurvivor(int NumOfPeople)
{

	int *circleArray = malloc(NumOfPeople * sizeof(int));
	int i = 0, loneSurvivor = 0, victim = 0;
	
	if (NumOfPeople < 0)
	{
		printf("can't have a negative number of people\n");
	}
	
	if (circleArray == NULL)
	{
		printf("memory allocation failed\n");
		return EXIT_FAILURE;
	}
	
	
		
	for(i = 0 ; i < (NumOfPeople - 1) ; i++)
	{													/*put some numbers in the array*/
		circleArray[i]=(i+1);	
	}
	circleArray[NumOfPeople - 1] = 0;					/*the last number must be zero*/

	
	/*slaughter begins:*/
	i=0;
	while (i != circleArray[i])
	{
		victim = circleArray[i];
		circleArray[i] = circleArray[victim];
		i = circleArray[i];
		
	}
	
	loneSurvivor = i + 1;
	
	
	free(circleArray);
	circleArray = NULL;
	
	
	return loneSurvivor;


}

void UniTest(void)
{
	int NumOfPeople = 0;

	printf("how many miserable lives are in your circle?\n");


	scanf("%d", &NumOfPeople);
	
	printf("the lone survivor will be in position %d,\nmay the odds be ever in your favor\n",LoneSurvivor(NumOfPeople));
	

}
