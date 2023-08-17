#include "minishell.h"

void	read_command(t_elem **elem, char *input)
{
	int				i;
	int				j;
	int				len;

	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] && is_space(input[i]))
			add_back(elem, new_elem(input, &i, 1, WHITE_SPACE));
		else if (input[i] && !is_special(input[i]))
		{
			j = i;
			len = 0;
			while (input[j] && !is_special(input[j]))
			{
				len++;
				j++;
			}
			add_back(elem, new_elem(input, &i, len, WORD));
		}
		else if (input[i] && input[i] == '|')
			add_back(elem, new_elem(input, &i, 1, PIPE));
		else if (input[i] && input[i] == '\'')
			add_back(elem, new_elem(input, &i, 1, S_QUOTE));
		else if (input[i] && input[i] == '"')
			add_back(elem, new_elem(input, &i, 1, D_QUOTE));
		else if (input[i] && input[i] == '$')
		{
			len = 0;
			j = i;
			while (input[j])
			{	
				j++;
				len++;
				if (input[j] && is_special(input[j]))
					break ;
			}
			add_back(elem, new_elem(input, &i, len, VAR));
		}
		else if (input[i] && input[i] == '>' && input[i + 1] == '>')
			add_back(elem, new_elem(input, &i, 2, REDIR_APPEND));
		else if (input[i] && input[i] == '>')
			add_back(elem, new_elem(input, &i, 1, REDIR_ADD));
		else if (input[i] && input[i] == '<' && input[i + 1] == '<')
			add_back(elem, new_elem(input, &i, 2, HER_DOC));
		else if (input[i] && input[i] == '<')
			add_back(elem, new_elem(input, &i, 1, REDIR_IN));
	}
	isolate_quotes(elem);
}

void	isolate_quotes(t_elem **elem)
{
	t_elem		*cursor;

	cursor = *elem;
	while (cursor)
	{
		if (cursor && cursor->type == S_QUOTE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type != S_QUOTE)
			{
				cursor->state = IN_QUOTE;
				cursor = cursor->next;
			}
		}
		if (cursor && cursor->type == D_QUOTE)
		{
			cursor = cursor->next;
			while (cursor && cursor->type != D_QUOTE)
			{
				cursor->state = IN_DQUOTE;
				cursor = cursor->next;
			}
		}
		if (cursor)
			cursor = cursor->next;
	}
}

char *ft_strcat(char *dest, char *src)
{
	int 	i;
	int 	j;
	char	*res;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
		j++;
	res = malloc(sizeof(i + j + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (dest[i] != '\0')
	{
		res[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
	{
		res[i] = src[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

int main(int ac, char **av, char **envp)
{
	// int status;
	char	*input;
	t_env	*env;
	t_elem	*node;
	(void)ac;
	(void)av;
	(void)envp;
	while(1)
	{
		env = malloc(sizeof(t_env));
		env->elem = malloc(sizeof(t_elem));
		// env = 0;
		env->elem = 0;
		env->exit_status = 0;
		input = readline("\033[1;37;44m\033[34mMINISHELL $ \033[0m\033[0m");
		add_history(input);
		read_command(&env->elem, input);
		if(check_syntax_errors(env))
		{
			expand(&env->elem);
			get_rid_of_spaces(&env->elem);
			get_rid_of_quotes(&env->elem);
				env->cmd = split_line(env->elem);
				if (env->cmd)

				{
					if (!ft_strcmp(env->cmd->cmd_line[0], "pwd"))
					pwd();
					if (!ft_strcmp(env->cmd->cmd_line[0], "echo"))
						echo(env->cmd->cmd_line);
				// else
				// {//execve("/bin/ls", )
				// 	pid_t pid = fork();
				// 	if (pid == 0)
				// 		execve(ft_strcat("/bin/", env->cmd->cmd_line[0]), env->cmd->cmd_line, envp);
				// 	else if (pid > 0)
				// 		waitpid(pid, &status, 0);
				// }
			}

				// while (env->cmd)
				// {
				// 	int i = 0;
				// 	while (env->cmd->cmd_line[i])
				// 	{
				// 		printf("cmd   |%s| **\n", env->cmd->cmd_line[i]);
				// 		i++;
				// 	}
				// 	printf("--- redir--\n");
				// 	while (env->cmd->redir)
				// 	{
				// 		printf("====>%d || %s\n", env->cmd->redir->type, env->cmd->redir->file_name);
				// 		env->cmd->redir = env->cmd->redir->next;
				// 	}
				// 	printf("---end redir--\n");
				// 			printf("--------------------\n");
				// 	env->cmd = env->cmd->next;
				// }
			// }
			while (env->elem)
			{
				node = env->elem->next;
				free(env->elem->content);
				free(env->elem);
				env->elem = node;
			}
		}
	}
	clear_history();
	return (0);
}