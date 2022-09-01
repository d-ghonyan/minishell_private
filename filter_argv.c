/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/01 19:08:37 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filter_error(char **argv, t_cmd *cmd, int cond)
{
	if (cond)
	{
		free_ptr_arr(argv);
		perror_exit(cmd, "malloc at filter_argv", 1);
	}
}

char	**filter_argv(char **argv, t_cmd *cmd, int k)
{
	int		i;
	int		j;
	char	**new_argv;

	new_argv = malloc(sizeof (*new_argv) * (ptr_arr_len(argv)));
	perror_exit(cmd, "malloc at filter_argv", !new_argv);
	j = 0;
	i = -1;
	while (argv[++i])
	{
		if (i != k)
		{
			new_argv[j] = ft_strdup(argv[i]);
			filter_error(new_argv, cmd, !new_argv[j]);
			j++;
		}
	}
	new_argv[j] = NULL;
	free_ptr_arr(argv);
	return (new_argv);
}
