/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdenguir <mdenguir@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:35:47 by mdenguir          #+#    #+#             */
/*   Updated: 2023/09/16 12:19:40 by mdenguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	parse_equal(t_elem **elem, char *input, int *i, int a, int len)
{
	int		j;
	int		s_q;
	int		d_q;

	j = a - 1;
	s_q = 0;
	d_q = 0;
	if (input[j] == '=' && input[j + 1]
		&& (input[j + 1] == '\'' || input[j + 1] == '"'))
	{
		if (input[j + 1] == '\'')
			s_q++;
		if (input[j + 1] == '"')
			d_q++;
		j += 2;
		while (input[j] && input[j + 1])
		{
			if (input[j] == '\'')
				s_q++;
			if (input[j] == '"')
				d_q++;
			if ((input[j] == '"' && input[j + 1] == ' ')
				|| (input[j] == '\'' && input[j + 1] == ' ')
				|| (input[j] == ' ' && ((s_q % 2 == 0 && s_q)
						|| (d_q % 2 == 0 && d_q))))
				break ;
			len++;
			j++;
		}
		add_back(elem, new_elem(input, i, len + 2, WORD));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	(void)ac;
	(void)av;
	env.envp = copy_env(envp);
	env.in = dup(STDIN_FILENO);
	env.out = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	minishell(env, envp);
	clear_history();
	free_envp(&env);
	return (0);
}
