#include "header.h"

int main()
{
	UniTest();
	return EXIT_SUCCESS;
}

void UniTest(void)
{
	/*Strlen test:	
	printf("%lu\n",Strlen("x"));
	printf("%lu\n",Strlen(" "));
	printf("%lu\n",Strlen("123456"));
	printf("%lu\n",Strlen("123 456"));
	printf("%lu\n",Strlen("\0"));*/ 
	
	/*Strcmp test: 
	char s1[] = "lala";
	char s2[] = "lola";
	printf("%d\n", Strcmp(s1, s2));
	printf("%d\n", Strcmp("l", "dola"));
	printf("%d\n", Strcmp("zzzz", "zzz"));
	printf("%d\n", Strcmp("zzz", "zzz")); */
	
	/*Strcpy test: 
	char src[]="whwheiurhwiehoeijfpoidhgpoqhger";
	char *dest=calloc(sizeof(src),sizeof(src[0]));
	dest = Strcpy(dest, src);
	printf("%s\n", dest);
	free(dest); */

	/*Strncpy test: 
	char src[]="this is my string";
	char *dest=calloc(sizeof(src),sizeof(src[0]));
	dest = Strncpy(dest, src, 6);
	printf("%s\n", dest);
	free(dest); */
	
	/*strcasecmp test
	printf("%d\n", Strcasecmp("sSs","Sss"));*/

	
	/*strchr test
	char c='s';
	char s[]="iamsotired";
	char *result=Strchr(s, c);
	printf("%p\n",result);*/


	/*strdup test
	char *s= "free me";
	char *willy=Strdup(s);	
	printf("%s\n",willy); 
	free(willy);*/
	
	/*Strcat test:
	char *s2=" is";	
	char s1[70]="this";
	printf("%s\n", Strcat(s1,s2));*/
	
	 /*Strncat test:
	char *s2="whatchuwant";	
	char s1[70]="tell me ";
	printf("%s\n", Strncat(s1,s2,6));*/

	/*Strstr test: 
	char *needle = "r";
	char *haystack = "abbcccdddd";	
	
	char *needle2 = "ccd";
	char *haystack2 = "abbcccdddd";
	
	char *needle3 = "r";
	char *haystack3 = "r";
	
	char *needle4 = "r";
	char *haystack4 = "a";

	char *needle5 = "a";
	char *haystack5 = "r";
	
	char *needle6 = "r";
	char *haystack6 = "";
	
	char *needle7 = "";
	char *haystack7 = "r";
	
	char *needle8 = "";
	char *haystack8 = "";
	
	char *needle9 = "aaa";
	char *haystack9 = "aaaa";
	
	printf("1: %s\n", Strstr(haystack,needle));	
	printf("2: %s\n", Strstr(haystack2,needle2));
	printf("3: %s\n", Strstr(haystack3,needle3));
	printf("4: %s\n", Strstr(haystack4,needle4));
	printf("5: %s\n", Strstr(haystack5,needle5));
	printf("6: %s\n", Strstr(haystack6,needle6));
	printf("7: %s\n", Strstr(haystack7,needle7));
	printf("8: %s\n", Strstr(haystack8,needle8));
	printf("9: %s\n", Strstr(haystack9,needle9));*/


	char *s="trings";
	char *accept = "s";
	size_t size = Strspn(s,accept);
	
	char *s1="ffftrings";
	char *accept1 = "f";
	size_t size1 = Strspn(s1,accept1);
	printf("%lu\n",size);
	printf("%lu\n",size1);

	
	
   

}

