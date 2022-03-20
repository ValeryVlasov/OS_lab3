#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static int G_kill = 0;

void OnCtrlC(int sig)
{
	(void)sig;
	G_kill = 1;
	signal(SIGINT, SIG_DFL);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Wrong number of arguments.\n"));
	pid_t pid = atoi(argv[1]);
	signal(SIGINT, OnCtrlC);
	printf("Waiting for signal to kill process with %d id...\n", pid);
	while (1)
	{
		if (G_kill)
		{
			if (kill(pid, SIGKILL) != 0)
			{
				write(2, "killing process failed\n", strlen("killing process failed\n"));
				exit(EXIT_FAILURE);
			}
			printf("\b\bProcess %d has been killed successfully\n", pid);
			break;
		}
	}
	return 0;
}