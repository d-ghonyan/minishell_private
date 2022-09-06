/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:07:17 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/06 14:40:10 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

__int128_t	int_128_atoi(char *s)
{
	int			i;
	__int128_t	minus;
	__int128_t	res;

	res = 0;
	minus = 1;
	res = 0;
	i = ft_isspace_index(s);
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			minus = -1;
		i += 1;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res * minus);
}

int	check_args(t_cmd *cmd, int j)
{
	int		i;
	char	*err;
	char	*s;

	err = ": numeric argument required";
	if (ptr_arr_len(cmd[j].exec.argv) > 1)
	{
		s = cmd[j].exec.argv[1];
		i = ft_isspace_index(s);
		if (!s[i])
			return (stderror_putstr("minishell: exit: ", s, err, 1));
		i += (s[i] == '+' || s[i] == '-');
		if (!s[i])
			return (stderror_putstr("minishell: exit: ", s, err, 1));
		while (s[i])
		{
			if (!ft_isdigit(s[i]))
				return (stderror_putstr("minishell: exit: ", s, err, 1));
			i++;
		}
	}
	return (0);
}

int	check_llong(t_cmd *cmd, int i)
{
	if (ptr_arr_len(cmd[i].exec.argv) > 1)
	{
		if (int_128_atoi(cmd[i].exec.argv[1]) > LLONG_MAX
			|| int_128_atoi(cmd[i].exec.argv[1]) < LLONG_MIN)
		{		
			stderror_putstr("minishell: exit: ", cmd[i].exec.argv[1],
				": numeric argument required", 1);
			return (1);
		}
	}
	return (0);
}

int	ft_exit(t_cmd *cmd, int i, int single)
{
	int	status;

	if (single)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (ptr_arr_len(cmd[i].exec.argv) > 2)
	{
		*(cmd->status) = 1;
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	status = *(cmd->status);
	if (check_args(cmd, i) || check_llong(cmd, i))
	{
		*(cmd->status) = 1;
		return (1);
	}
	if (ptr_arr_len(cmd[i].exec.argv) > 1)
		status = (unsigned char)int_128_atoi(cmd[i].exec.argv[1]);
	free_ptr_arr(cmd->new_env);
	free(cmd->pwd);
	free(cmd->oldpwd);
	free_cmd(cmd);
	exit(status);
}
