/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:42:17 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/30 12:27:29 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd, t_envp *envp)
{
	t_envp		*cursor;
	char		**paths;
	int			i;

	cursor = envp;
	while (cursor && cursor->title && ft_strcmp(cursor->title, "PATH"))
		cursor = cursor->next;
	// printf("+++++|%s|\n", cursor->content);
	if (cursor && cursor->title && !ft_strcmp(cursor->title, "PATH"))
		paths = ft_split(cursor->content, ':');
	else
		return (NULL);
	
	i = 0;
	while (paths[i])
	{
		char *path = ft_strjoin(paths[i], "/");
		char *str = ft_strjoin(path, cmd);
		free(path);
		if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
		{
			
			return (str);
		}
		i++;
	}
	return (NULL);
}

// void	threat_redir(t_cmd *cmd)
// {
// 	int		fd;

// 	if (cmd->redir->type == ADD)
// 	{
// 		fd = open(cmd->redir->file_name, O_CREAT | O_WRONLY);
// 		if (!fd)
// 			ft_putstr_fd(2, "error openning file\n");
		
// 	}
// }