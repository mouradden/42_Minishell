/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:33:02 by yoamzil           #+#    #+#             */
/*   Updated: 2023/09/17 19:47:42 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_output_add(t_redir *redis)
{
	int		fd;

	fd = open(redis->file_name, O_CREAT
			| O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (!fd)
		ft_putstr_fd("error openning file\n", 2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_putstr_fd("error duplication ADD\n", 2);
}

void	dup_output_append(t_redir *redis)
{
	int		fd;

	fd = open(redis->file_name, O_CREAT
			| O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	if (!fd)
		ft_putstr_fd("error openning file\n", 2);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_putstr_fd("error duplication APPEND \n", 2);
}

void	dup_input(t_redir *redis)
{
	int		fd;

	if (access(redis->file_name, F_OK) == 0)
	{
		fd = open(redis->file_name, O_RDONLY | S_IRUSR);
		if (!fd)
			ft_putstr_fd("error openning file\n", 2);
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_putstr_fd("error duplication INPUT\n", 2);
	}
	else
	{
		perror(redis->file_name);
		exit (1);
	}
}

void	dup_herdoc(int *fdd)
{
	if (*fdd != -1 && dup2(*fdd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_putstr_fd("error dpulication INPUT HERDOC\n", 2);
		exit(1);
	}
}
