#include <stdio.h>	/*for printing*/
#include <stdlib.h> /*for allocating memory*/

void UniTest(void);
int LoneSurvivor(int num_of_people);

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

int LoneSurvivor(int num_of_people)
{
															/*save some space for an array*/
	int *circle_array = malloc(num_of_people * sizeof(int));
	int i = 0, lone_survivor = 0, kill = 0, body_count = 0;	/*kill is a switch*/
	
	if (num_of_people <= 0)
	{
		puts("can't kill what's not there...\n");
		/*if 0 - will return 0 at the end, if negative, allocation will be unsucessful and will return 0*/
	}
	else if (num_of_people == 1)
	{
		return 1;		/*return position 1*/
		
	}
	
	if (circle_array == NULL)
	{
		puts("memory allocation failed\n");
		return 0;		/*return position 0*/
	}
	
	for(i = 0 ; i < num_of_people ; i++)
	{														/*put some ones in the array*/
		circle_array[i] = 1;	
	}
		
	/*slaughter begins:*/
	
	i = 0;
	
	while (body_count != num_of_people)
	{
		if ((circle_array[i] == 1) )
		{
			if(kill == 1)
			{
				circle_array[i] = 0;
				kill = 0;
				body_count += 1;
			}
			else 
			{
				kill = 1;
			}
		}
		i = ((i + 1) % num_of_people);
		
	}
	
		
	lone_survivor = i;
	
	if (lone_survivor == 0)
	{
		return num_of_people;
	}
	
	free(circle_array);
	
	circle_array = NULL;
	
	
	return lone_survivor;


}

void UniTest(void)
{
	int num_of_people = 0;

	printf("how many miserable lives are in your circle?\n");

	scanf("%d",&num_of_people);
	
	printf("the lone survivor will be in position %d,\nmay the odds be ever in your favor\n",LoneSurvivor(num_of_people));
	

}
