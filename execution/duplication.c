/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplication.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:03:54 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/30 16:11:10 by mdenguir         ###   ########.fr       */
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
	int		fd = -1;
	t_cmd	*cmd;
	t_redir *red;

	cmd = env->cmd;
	while (cmd)
	{
			red = cmd->redir;
			while (red)
			{
				
				// if (cmd->redir->type == ADD)
				// {
				// 	fd = open(cmd->redir->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
				// 	if (!fd)
				// 		ft_putstr_fd("error openning file\n", 2);
				// 	if (dup2(fd, STDOUT_FILENO) == -1)
				// 		ft_putstr_fd("error duplication ADD\n", 2);
				// }
				// else if (cmd->redir->type == APPEND)
				// {
				// 	fd = open(cmd->redir->file_name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
				// 	if (!fd)
				// 		ft_putstr_fd("error openning file\n", 2);
				// 	if (dup2(fd, STDOUT_FILENO) == -1)
				// 		ft_putstr_fd("error duplication APPEND \n", 2);
				// }
				// else if (cmd->redir->type == INPUT)
				// {
				// 	fd = open(cmd->redir->file_name, O_RDONLY);
				// 	if (!fd)
				// 		ft_putstr_fd("error openning file\n", 2);
				// 	if (dup2(fd, STDIN_FILENO) == -1)
				// 		ft_putstr_fd("error duplication INPUT\n", 2);
				// }
				// else
				if (fd != -1)
					close(fd);
				if (red->type == HERDOC)
				{
					fd = open("herdoc_file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
					if (!fd)
						ft_putstr_fd("error openning file\n", 2);
					
					char *input = "";
					while (1)
					{
						input = readline("> ");
						if (!input)
							break;
						if (!ft_strcmp(input, red->file_name))
								break;
						// t_ malloc(sizeof(t_;	
						// elem = malloc(sizeof(t_elem));
						// elem = 0;
						// read_command(&elem, input);
						// ft_putstr_fd(elem->content, 2);
						// ft_putchar_fd('\n', 2);
						// expand(
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
				red = red->next;
				// if (cmd->redir)
				// 	dup2(env->in, STDIN_FILENO);
			}
		cmd = cmd->next;
	}
	return (fd);
}
