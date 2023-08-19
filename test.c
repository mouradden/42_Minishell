#include "minishell.h"


int main(int ac, char **av, char **envp)
{
	// void(ac);
    // void(av);
    t_envp	*cmd;
    cmd = copy_env(envp);
    while (cmd)
	{
		printf("title : %s || content : %s\n", cmd->title, cmd->content);
		cmd=cmd->next;
	}
}