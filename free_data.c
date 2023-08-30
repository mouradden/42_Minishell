/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:40:44 by mdenguir          #+#    #+#             */
/*   Updated: 2023/08/29 18:46:05 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elem(t_env **env)
{
	t_elem      *node;

	while ((*env)->elem)
	{
		node = (*env)->elem->next;
		free((*env)->elem->content);
		free((*env)->elem);
		(*env)->elem = node;
	}
}