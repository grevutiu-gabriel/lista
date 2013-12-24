#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int comp(const void *s1, const void *s2);

int main (int argc, char *argv[])
{
    DIR * d;
    char * dir_name = ".";
    int i=0;
    int count=0;
    char **data=NULL;
    char *first_letter = argv[1];
   
    /* Deschide directorul curent. */

    d = opendir (dir_name);

    if (! d) {
        fprintf (stderr, "Nu poate fi deschis directorul '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        
        entry = readdir (d);
        if (! entry) {
            break;
        }
	data = realloc(data, (i + 1) * sizeof(char *));

	if (data == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);}

	data[i] = malloc(strlen(entry->d_name));
	if (data[i] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

	if (argc == 2){
	
		if (entry->d_name[0]==*first_letter) {
			strcpy(data[i], entry->d_name);
			i++;
			}
		}
	
	else {
		strcpy(data[i], entry->d_name);
	     	i++;
	     }
	     
}


/* Sortare cuvinte (de fapt, sortare de pointeri). */

    	qsort(data, i, sizeof(data[0]), comp);
	//printf ("%s\n", entry->d_name);

/* Afiseaza cuvintele sortate. */

	for (count = 0; count < i; count++) printf("%s\n", data[count]);
	
    /* Inchide folderul. */
    if (closedir (d)) {
        fprintf (stderr, "Nu poate fi inchis '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }

    return 0;
}

int comp(const void *s1, const void *s2){return (strcmp(*(char **)s1, *(char **)s2));}
