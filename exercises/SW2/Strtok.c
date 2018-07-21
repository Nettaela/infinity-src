#include <stdio.h>
#include <string.h>

int isDelimiter(char currentCheckedChar, char *delimiters); 

      
char *Strtok(char *str, const char *delim)
{
	static char *remain =NULL; 
	char *run_str = str;
	char *next_token_start = str;
	static int nextTimeStop = 0;
	
	if (str == NULL)
	{
		while (isDelimiter(*remain, (char*)delim))
		{
			++remain;
		}
		run_str = remain;
		next_token_start=remain;
	}
	else 
	{
		nextTimeStop = 0;
	}
	
	if(nextTimeStop)
	{
		return NULL;
	}
		
	
	while (*run_str != '\0')
	{
		if (isDelimiter(*run_str, (char*)delim))
		{
			*run_str='\0';
			break;
		}
		++run_str;
	}
	if (*(run_str+1) == '\0')
	{
		nextTimeStop=1;;
	}
	else
	{
		remain=run_str+1;
		return  next_token_start;
	}
	

} 


int isDelimiter(char currentCheckedChar, char *delimiters)
{
	int result = 0;
	while (*delimiters != '\0')
	{
		if (*delimiters == currentCheckedChar)
		{
			result = 1;
		}
		++delimiters;
		
	}
	return result;
}





int main ()
{

   char str[80] = "This is ---- what is --/----- u'p ' with u --- 'there -- man";
   const char s[] = "-,/'";
   char *token;
   
   
   
  
   
   
   token = Strtok(str, s);
   printf("\"%s\"\n", token);
   
    /*with while*/
   
   while( token != NULL ) 
   {
      printf( " %s\n", token );
    
      token = Strtok(NULL, s);
   }
  
   return 0;
   

}

