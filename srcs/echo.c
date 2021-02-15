/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:02:30 by zjamali           #+#    #+#             */
/*   Updated: 2021/02/15 14:19:59 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *line)
{
	line = ft_strtrim(line, "\n");
	ft_putstr_fd(line, 1);
	frees(&line);
}

void	execute_echo(char *cmd, t_path *path, t_command *l_cmd)
{
	int					i;
	t_simple_command	*cmds;
	t_simple_command	*tmp;
	t_simple_command	*tmp1;

	cmds = l_cmd->s_left;
	i = 0;
	if (l_cmd->s_left->right &&
			!ft_strcmp(l_cmd->s_left->right->l_element->argument, "-n"))
	{
		tmp1 = l_cmd->s_left->right->right;
		l_cmd->s_left->right = l_cmd->s_left->right->right;
		i = 1;
	}
	while (l_cmd->s_left)
	{
		if (l_cmd->s_left->right)
			echo(l_cmd->s_left->right->l_element->argument);
		if (l_cmd->s_left->right && l_cmd->s_left->right->right)
			ft_putstr_fd(" ", 1);
		l_cmd->s_left = l_cmd->s_left->right;
	}
	l_cmd->s_left = cmds;
	if (ft_strcmp(cmd, "echo -n") && i != 1)
		ft_putendl_fd("", 1);
	path->dollar = 0;
}
