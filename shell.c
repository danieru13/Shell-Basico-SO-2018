#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "parser.h"

#define GREEN "\033[1;32m"
#define RESET "\033[0m"

#define TAM 100

int main ()
{
	const char *mypath[] = {"./", "/usr/bin/", "/bin/", NULL};

	char ** items;
	int i, num, background;
	char expresion[TAM];

	while(1) {
		printf (GREEN "udea-shell$ " RESET);
		fgets (expresion, TAM, stdin);

		num = separaItems (expresion, &items, &background);

		printf ("Numero de parametros: %d\n", num);

		// ORDENES INTERNAS //

		if(strcmp(items[0], "udea-pwd") == 0)
		{
			char directorio[TAM];

			getcwd(directorio, TAM);

			printf("%s\n", directorio);
		}

		else if (strcmp(items[0], "udea-cd") == 0)
        {
            chdir(items[1]);
        }

        else if (strcmp(items[0], "udea-echo") == 0)
        {
        	for(i = 1; i < num; i++)
        	{	
        		printf("%s ", items[i]);
        	}
        	printf("\n");
        }

        else if (strcmp(items[0], "udea-clr") == 0)
        {
        	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  			write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        }

        else if (strcmp(items[0], "udea-time") == 0)
        {
        	time_t rawtime;
  			struct tm * timeinfo;

  			time ( &rawtime );
  			timeinfo = localtime ( &rawtime );
  			printf ( "%s", asctime (timeinfo) );
        }

        else if (strcmp(items[0], "udea-exit") == 0)
        {
        	exit(0);
        }

        // FIN ORDENES INTERNAS //

		/*
		if (num>0)
		{
			for (i=0; i<num; i++)
		    printf ("%d \"%s\"\n", i+1, items[i]);

		    printf ("Background: %d\n", background);

		    liberaItems (items);
		}**/
	}

	return 0;
}