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

void udea_pwd();
void udea_cd(char ** it);
void udea_echo(char ** it, int n);
void udea_clr();
void udea_time();
void udea_exit();

int main ()
{
	char *mypath[] = {"./", "/usr/bin/", "/bin/", NULL};

	char ** items;
	int num, background, status;
	char expresion[TAM];

	while(1) {
		printf (GREEN "udea-shell$ " RESET);
		fgets (expresion, TAM, stdin);

		num = separaItems (expresion, &items, &background);

		// ORDENES INTERNAS //

		if(strcmp(items[0], "udea-pwd") == 0)
		{
			udea_pwd();
		}

		else if (strcmp(items[0], "udea-cd") == 0)
        {
            udea_cd(&items[0]);
        }

        else if (strcmp(items[0], "udea-echo") == 0)
        {
        	udea_echo(&items[0], num);
        }

        else if (strcmp(items[0], "udea-clr") == 0)
        {
  			udea_clr();

        }

        else if (strcmp(items[0], "udea-time") == 0)
        {
  			udea_time();
        }

        else if (strcmp(items[0], "udea-exit") == 0)
        {
        	udea_exit();
        }

        // FIN ORDENES INTERNAS //

        // ORDENES EXTERNAS //

        else if(fork() == 0)
        {
        	printf("Entre acá \n");
        	execvp(items[0], mypath);
        }else
        {
        	if(background == 1)
        	{
        		wait(&status);
        	}
        }

        // FIN ORDENES EXTERNAS //

        liberaItems(items);
	}

	return 0;
}

void udea_pwd(){

	char directorio[TAM];

	getcwd(directorio, TAM);

	printf("%s\n", directorio);
}

void udea_cd(char ** it){
	chdir(it[1]);
}

void udea_echo(char ** it, int n){
	for(int i = 1; i < n; i++)
    {	
     	printf("%s ", it[i]);
    }
    printf("\n");
}

void udea_clr(){
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  	write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void udea_time(){
	time_t rawtime;
  	struct tm * timeinfo;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
  	printf ( "%s", asctime (timeinfo) );
}

void udea_exit(){
	exit(0);
}

