#include <stdlib.h>

#ifdef __AKAVEL_FALSE
extern	char **environ;
#endif

char *
getenv(const char *name)
{
	runtime·panicstring("C function \'getenv\' not yet implemented");
	USED(&name);
	return 0;
#ifdef __AKAVEL_FALSE
	char **p = environ;
	char *v, *s1, *s2;

	while (*p != NULL){
		for(s1 = (char *)name, s2 = *p++; *s1 == *s2; s1++, s2++)
			continue;
		if(*s1 == '\0' && *s2 == '=')
			return s2+1;
	}
	return NULL ;
#endif
}
