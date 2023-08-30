/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:48:28 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/30 16:52:24 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_one_command(t_env *env ,char **envp, int fdd)
{
	// pid_t	pid0;
	// int		status;


	char	*path;
	// int		fd;
	if (env->cmd->cmd_line[0] && !ft_strcmp(env->cmd->cmd_line[0], "pwd"))
		pwd();
	else if (env->cmd->cmd_line[0] && !ft_strcmp(env->cmd->cmd_line[0], "echo"))
		echo(env->cmd->cmd_line);
	else if (env->cmd->cmd_line[0] && !ft_strcmp(env->cmd->cmd_line[0], "cd"))
		cd(env->cmd->cmd_line[1]);
	else if (env->cmd->cmd_line[0] && !ft_strcmp(env->cmd->cmd_line[0], "env"))
		ft_env(env->envp);
	else if (env->cmd->cmd_line[0] && !ft_strcmp(env->cmd->cmd_line[0], "export"))
		export(&env->envp, env->cmd->cmd_line);
	else if (env->cmd->cmd_line[0] && !ft_strcmp(env->cmd->cmd_line[0], "unset"))
		unset(&env->envp, env->cmd->cmd_line[1]);
	else
	{
		t_redir *redis;
		path = get_cmd_path(env->cmd->cmd_line[0], env->envp);
		if (!path)
		{
			dprintf(2, "%s : command not found\n" , env->cmd->cmd_line[0]);
		}
		redis = env->cmd->redir;
			// while (redis)
			// {
				
			// // 	// if (env->cmd->redir->type == ADD)
			// // 	// {
			// // 	// 	fd = open(env->cmd->redir->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
			// // 	// 	if (!fd)
			// // 	// 		ft_putstr_fd("error openning file\n", 2);
			// // 	// 	if (dup2(fd, STDOUT_FILENO) == -1)
			// // 	// 		ft_putstr_fd("error duplication ADD\n", 2);
			// // 	// }
			// // 	// else if (env->cmd->redir->type == APPEND)
			// // 	// {
			// // 	// 	fd = open(env->cmd->redir->file_name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
			// // 	// 	if (!fd)
			// // 	// 		ft_putstr_fd("error openning file\n", 2);
			// // 	// 	if (dup2(fd, STDOUT_FILENO) == -1)
			// // 	// 		ft_putstr_fd("error duplication APPEND \n", 2);
			// // 	// }
			// // 	// else if (env->cmd->redir->type == INPUT)
			// // 	// {
			// // 	// 	fd = open(env->cmd->redir->file_name, O_RDONLY);
			// // 	// 	if (!fd)
			// // 	// 		ft_putstr_fd("error openning file\n", 2);
			// // 	// 	if (dup2(fd, STDIN_FILENO) == -1)
			// // 	// 		ft_putstr_fd("error duplication INPUT\n", 2);
			// // 	// }
			// 	if (redis->type == HERDOC)
			// 	{
			// 		break ;
			// 	}
			// 	redis = redis->next;
			// // 	// if (env->cmd->redir)
			// // 	// 	dup2(env->in, STDIN_FILENO);

			// }
			(void)fdd;
			if (redis && redis->type == HERDOC)
			{
				if (fdd != -1 && dup2(fdd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					ft_putstr_fd("error dpulication INPUT HERDOC\n", 2);
					exit (1);
				}
			}
			// close(fd);
			execve(path, env->cmd->cmd_line, envp);
		// }
		// waitpid(pid0, &status, 0);
	}
	// dup2(env->in, STDIN_FILENO);
	// dup2(env->out, STDOUT_FILENO);
}

void	exec_one_command_herdoc(t_env *env ,char **envp)
{
	pid_t	pid0;
	int		status;
	char	*path;
	int		fd;

	
	path = get_cmd_path(env->cmd->cmd_line[0], env->envp);
	if (!path)
	{
		dprintf(2, "%s : command not found\n" , env->cmd->cmd_line[0]);
	}
	pid0 = fork();
	if (pid0 == 0)
	{
		// printf("hi from child\n");
		// int fd;
		// int i = 0;
		while (env->cmd->redir)
		{
			
			if (env->cmd->redir->type == ADD)
			{
				fd = open(env->cmd->redir->file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
				if (!fd)
					ft_putstr_fd("error openning file\n", 2);
				if (dup2(fd, STDOUT_FILENO) == -1)
					ft_putstr_fd("error duplication ADD\n", 2);
			}
			else if (env->cmd->redir->type == APPEND)
			{
				fd = open(env->cmd->redir->file_name, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
				if (!fd)
					ft_putstr_fd("error openning file\n", 2);
				if (dup2(fd, STDOUT_FILENO) == -1)
					ft_putstr_fd("error duplication APPEND \n", 2);
			}
			else if (env->cmd->redir->type == INPUT)
			{
				fd = open(env->cmd->redir->file_name, O_RDONLY);
				if (!fd)
					ft_putstr_fd("error openning file\n", 2);
				if (dup2(fd, STDIN_FILENO) == -1)
					ft_putstr_fd("error duplication INPUT\n", 2);
			}
			else 
			if (env->cmd->redir->type == HERDOC)
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
					if (!ft_strcmp(input, env->cmd->redir->file_name))
							break;
					// t_env *env = malloc(sizeof(t_env));	
					// env->elem = malloc(sizeof(t_elem));
					// env->elem = 0;
					// read_command(&env->elem, input);
					// ft_putstr_fd(env->elem->content, 2);
					// ft_putchar_fd('\n', 2);
					// expand(env);
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
			// i++;
			env->cmd->redir = env->cmd->redir->next;
			if (env->cmd->redir)
				dup2(env->in, STDIN_FILENO);
		}
		
		execve(path, env->cmd->cmd_line, envp);
	close(fd);
	}
	waitpid(pid0, &status, 0);
	// dup2(env->in, STDIN_FILENO);
	// dup2(env->out, STDOUT_FILENO);
}