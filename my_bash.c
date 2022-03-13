#include "my_bash.h"

void	putstr_fd(char *msg, int fd) {
	write(fd, msg, strlen(msg));
}

void delete_mem(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	execute_cmd(char *arg, char *path)
{
	int status = 0;
	char *arg_dup = strdup(arg);
	pid_t pid = fork();
	if (pid < 0)
		exit(errno);
	if (pid == 0)
	{
		if (execlp(path, arg_dup, NULL) == -1)
		{
			putstr_fd("error: fatal: exec failed\n", 2);
			perror(strerror(errno));
		}
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		delete_mem(arg_dup);
	}
}

int check_command(char *arg)
{
	if (strcmp(arg, "ls") != 0 && strcmp(arg, "cat") != 0)
		return 1;
	return 0;
}

int	main(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc != 2) {
		putstr_fd("Error. Wrong number of arguments\n", 2);
		putstr_fd("usage: ./minibash <name_of_command>\n", 2);
		putstr_fd("List of available commands: \"ls\", \"cat\"\n", 2);// /bin/ls, /bin/cat
		return 1;
	}
	if (check_command(argv[1]) != 0)
	{
		putstr_fd("Error. Unknown argument\n", 2);
		putstr_fd("List of available commands: \"ls\", \"cat\"\n", 2);
		return 1;
	}
	char *prefix = strdup("/bin/");
	char *binary_folder = strcat(prefix, argv[1]);
	delete_mem(prefix);
	execute_cmd(argv[1], binary_folder);
	return 0;
}