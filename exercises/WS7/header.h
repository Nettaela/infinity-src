#include <stdio.h>		/*for printf function*/
#include <stdlib.h>		/*for exit success*/
#include <ctype.h>		/*remove this*/
#include <assert.h> 	/*for asserting*/
#include <string.h>		/*remove this*/
#include <strings.h>	/*remove this*/
#define IS_UPPERCASE(c) ('A' <= (c) && (c) <= 'Z') /*macro for strcasecmp*/


size_t Strlen(const char *str);
int Strcmp(const char *str1, const char *str2);
char * Strcpy (char *dest, const char *src);
char * Strncpy (char *dest, const char *src, size_t n);
int Strcasecmp(const char *str1, const char *str2);
char *Strchr(const char *str, int c);
char *Strdup(const char *s);
char *Strcat(char *dest, const char *src);
char *Strncat(char *dest, const char *src, size_t n);
char *Strstr(const char *haystack, const char *needle);
size_t Strspn(const char *s, const char *accept);

void UniTest(void);
