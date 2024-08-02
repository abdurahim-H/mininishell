#include "minishell.h"

void printTokens(Token *head)
{
	Token *current = head;
	int i;

	i = 0;
	printf("------------------------------------------------\n");
	while (current != NULL)
	{
		printf("Token : %d\n", ++i);
		printf("Type  : %s\n", findType(current->type));
		printf("Text  : %s\n", current->text);
		printf("------------------------------------------------\n");
		current = current->next;
	}
}

void printCmds(t_commands *head)
{
	t_commands *current = head;
	int i;

	i = 0;
	printf("------------------------------------------------\n");
	while (current != NULL)
	{
		printf("CMD   : %d\n", ++i);
		int n = -1;
		if (current->cmds)
		{
			while (current->cmds[++n])
				printf("Arg_%d : %s\n", n, current->cmds[n]);
		}
		printf("Fd_in   : %d\n", current->fd_in);
		printf("Fd_out  : %d\n", current->fd_out);
		printf("------------------------------------------------\n");
		current = current->next;
	}
}