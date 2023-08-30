#include "minishell.h"

void printf_cmd(t_env *env)
{
	while (env->cmd)
	{
		int i = 0;
		while (env->cmd->cmd_line[i])
		{
			printf("cmd   |%s| **\n", env->cmd->cmd_line[i]);
			i++;
		}
		printf("--- redir--\n");
		while (env->cmd->redir)
		{
			printf("====>%d || %s\n", env->cmd->redir->type, env->cmd->redir->file_name);
			env->cmd->redir = env->cmd->redir->next;
		}
		printf("---end redir--\n");
				printf("--------------------\n");
		env->cmd = env->cmd->next;
	}

}