/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:00:45 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/23 13:01:15 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax_errors(t_env *env)
{
	if (!check_quotes(env))
	{
		printf("syntax error : unclosed quotes\n");
		g_exit_status = 258;
		return (0);
	}
	if (!check_syntax_pipes(env))
	{
		printf("syntax error : pipes \n");
		g_exit_status = 258;
		return (0);
	}
	if (!check_redir_syntax(env))
	{
		printf("syntax error : redirections \n");
		g_exit_status = 258;
		return (0);
	}
	return (1);
}

int	check_syntax_pipes(t_env *env)
{
	if (count_cmd(&env->elem))
	{
		if (!check_before_pipe(env->elem))
			return (0);
		if (!check_consecutive_pipes(env->elem))
			return (0);
		if (!check_after_pipe(env->elem))
			return (0);
	}
	return (1);
}

int	check_redir_syntax(t_env *env)
{
	if (count_redir(env->elem))
	{
		if (!check_empty_redir(env->elem))
			return (0);
		if (!check_invalid_redir(env->elem))
			return (0);
		if (!invalid_consecutives_redir(env->elem))
			return (0);
	}
	return (1);
}
