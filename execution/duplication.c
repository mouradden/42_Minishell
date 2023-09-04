/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:03:54 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/04 10:12:12 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	duplicate_fd(int **fd, int count_pipes, int i)
{
	if (i == 0)
		dup2(fd[i][1], STDOUT_FILENO);
	else if (i == count_pipes - 1)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		// if(close(fd[i - 1][0]) != 0 )
		// 	dprintf(2, "1/  %d not closed\n", i - 1);
	}
	else
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
	// 	if (close(fd[i - 1][0]) != 0)
	// 	dprintf(2, "2/  %d 0 not closed\n", i - 1);
	}
	i = 0;
	while (i < count_pipes - 1)
	{
		if (close(fd[i][0]) != 0)
		{
			dprintf(2, "3/  %d 0 not closed\n", i);
			perror("Error closing file");
		}
		if (close(fd[i][1]) != 0)
			dprintf(2, "4/  %d  1 not closed\n", i);;
		i++;
	}
}

int	duplicate_redir(t_env *env)
{
	int		fd;
	pid_t pid;
	t_cmd	*cmd;
	t_redir *red;

	gl_sig = 0;
	cmd = env->cmd;
	while (cmd)
	{
		red = cmd->redir;
		while (red)
		{
			if (red->type == HERDOC)
			{
				pid = fork();
				if (pid == 0)
				{
					fd = open("herdoc_file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
					if (!fd)
						ft_putstr_fd("error openning file\n", 2);
					
					char *input = "";
					t_env *env;
						env = malloc(sizeof(t_env));
						env = 0;
						
					while (1)
					{	
						signal(SIGINT, sig_check_herdoc);
						input = readline("> ");
						if (!input)
							break;
						if (input && red->file_name && !ft_strcmp(input, red->file_name))
								break;
						// ft_putstr_fd("here\n", 2);
			// 			env->elem = malloc(sizeof(t_elem));
			// 			env->elem = 0;
			// 			read_command(&env->elem, input);
			// while (env->elem)
			// {
			// 	dprintf(2, "content : |%s|  type :|%d|\n", env->elem->content, env->elem->type);
			// 	env->elem = env->elem->next;
			// }
			// 			// ft_putstr_fd(env->elem->content, 2);
			// 			// ft_putchar_fd('\n', 2);
			// 			// expand(env);
			// 			ft_putstr_fd(env->elem->content, fd);
			// 			ft_putchar_fd('\n', fd);
			// 			free_elem(&env);
						if (check_dollar(input) > -1)
							expand_input_herdoc(input);
						ft_putstr_fd(input, fd);
						ft_putchar_fd('\n', fd);
					}
					close(fd);
					fd = open("herdoc_file", O_RDONLY);
					if (dup2(fd, STDIN_FILENO) == -1)
					{
						perror("dup2");
						ft_putstr_fd("error dpulication INPUT HERDOC\n", 2);
					}
				}
				waitpid(pid, NULL, 0);
			}
			red = red->next;
			if (red)
				dup2(env->in, STDIN_FILENO);
		}
		cmd = cmd->next;
	}
	return (fd);
}

// char	*expand_input_herdoc(char *input)
// {
// 	int		index;
// 	char	*res;

// 	if (check_dollar(input) != 0)
// 	{
// 		res = ft_strjoin("", extract_word(input, 0, ))
// 	}
// }