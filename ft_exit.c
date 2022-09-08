/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:07:17 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/08 14:06:58 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_exit_(t_cmd *cmd, int status, int err, char *msg)
{
	if (err)
	{
		stderror_putstr("minishell: exit: ", msg,
			": numeric argument required", 1);
	}
	free_ptr_arr(cmd->new_env);
	free(cmd->pwd);
	free(cmd->oldpwd);
	free_cmd(cmd);
	rl_clear_history();
	exit(status);
}

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

void	check_args(t_cmd *cmd, int j)
{
	int		i;
	char	*s;

	if (ptr_arr_len(cmd[j].exec.argv) > 1)
	{
		s = cmd[j].exec.argv[1];
		i = ft_isspace_index(s);
		if (!s[i])
			_exit_(cmd, 255, 1, s);
		i += (s[i] == '+' || s[i] == '-');
		if (!s[i])
			_exit_(cmd, 255, 1, s);
		while (s[i])
		{
			if (!ft_isdigit(s[i]))
				_exit_(cmd, 255, 1, s);
			i++;
		}
	}
}

void	check_llong(t_cmd *cmd, int i)
{
	if (ptr_arr_len(cmd[i].exec.argv) > 1)
	{
		if (ft_strlen(cmd[i].exec.argv[1]) > 21
			|| int_128_atoi(cmd[i].exec.argv[1]) > LLONG_MAX
			|| int_128_atoi(cmd[i].exec.argv[1]) < LLONG_MIN)
		{
			_exit_(cmd, 255, 1, cmd[i].exec.argv[1]);
		}
	}
}

int	ft_exit(t_cmd *cmd, int i, int single)
{
	int	status;

	if (single)
		ft_putendl_fd("exit", STDOUT_FILENO);
	check_args(cmd, i);
	check_llong(cmd, i);
	if (ptr_arr_len(cmd[i].exec.argv) > 2)
	{
		*(cmd->status) = 1;
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	status = *(cmd->status);
	if (ptr_arr_len(cmd[i].exec.argv) > 1)
		status = (unsigned char)int_128_atoi(cmd[i].exec.argv[1]);
	_exit_(cmd, status, 0, NULL);
	return (0);
}
