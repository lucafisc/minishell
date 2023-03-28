#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
// To use the readline library specify -lreadline to your compiler.
// still has still reachable leaks...
int main(void)
{
	char *input;
	int i = 0;
	char cwd[1024];

	while (++i < 5)
	{
		getcwd(cwd, sizeof(cwd));
		input = readline(cwd);
		add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	return 0;
}