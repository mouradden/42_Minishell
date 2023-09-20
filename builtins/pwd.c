/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:16:27 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/20 22:21:19 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	printf("%s\n", buffer);
	g_exit_status = 0;
}
