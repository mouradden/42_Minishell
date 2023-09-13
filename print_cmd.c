#include "minishell.h"

void	printf_cmd(t_env *env)
{
	int	i;
	t_cmd *cmd = env->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->cmd_line[i])
		{
			printf("cmd   |%s| **\n", cmd->cmd_line[i]);
			i++;
		}
		printf("--- redir--\n");
		while (cmd->redir)
		{
			printf("====>%d || %s\n", cmd->redir->type, cmd->redir->file_name);
			cmd->redir = cmd->redir->next;
		}
		printf("---end redir--\n");
		printf("--------------------\n");
		cmd = cmd->next;
	}
}

void	print_elem(t_env *env)
{
	t_elem *elem = env->elem;
	while (elem)
	{
		printf("content : |%s|  type :|%d| state : |%d|\n", elem->content, elem->type, elem->state);
		elem = elem->next;
	}
}