/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:51:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/14 11:41:26 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_affect_extended(t_list_cmd **l_cmd,\
		char *command, int indice, t_save *save)
{
	(*l_cmd)->command->tool.redirection = 1;
	(*l_cmd)->command = add_simple_cmd((*l_cmd)->command, 3, (*l_cmd));
	if ((*l_cmd)->command->s_left->right != NULL)
		(*l_cmd)->command->s_left = (*l_cmd)->command->s_left->right;
	(*l_cmd)->command->s_left->l_element->redirection.file = ft_strdup(command);
	(*l_cmd)->command->s_left->l_element->redirection.i_o =\
			ft_strdup(save->red);
}

void	alloc_affect(t_list_cmd *l_cmd, char *command, int indice, t_save *save)
{
	if (indice == 1)
	{
		l_cmd->command->tool.cmd = 1;
		l_cmd->command = add_simple_cmd(l_cmd->command, 1, l_cmd);
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		l_cmd->command->s_left->l_element->cmd = ft_strdup(command);
	}
	else if (indice == 2)
	{
		l_cmd->command->tool.argument = 1;
		l_cmd->command = add_simple_cmd(l_cmd->command, 2, l_cmd);
		if (l_cmd->command->s_left->right != NULL)
			l_cmd->command->s_left = l_cmd->command->s_left->right;
		l_cmd->command->s_left->l_element->argument = ft_strdup(command);
	}
	else if (indice == 3)
		alloc_affect_extended(&l_cmd, command, indice, save);
}

int		ft_2strlen(char **str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup_beg(const char *s1, int j)
{
	int		i;
	char	*ptr;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	if (!(ptr = malloc(sizeof(char) * (j) + 1)))
		return (NULL);
	while (i < j)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_concatenation(char *line, int *i, int index, char *ptr)
{
	char	*str1;
	char	*str_beg;
	char	*str_end;
	int		len;
	char	*tmp;

	str1 = (ptr != NULL) ? ft_strdup(ptr) : ft_strdup("");
	tmp = str1;
	len = ft_strlen(str1);
	// printf("hii\n");
	if(index == -1)
		index = 0;
	if (*i > 0)
	{
		str_beg = ft_strdup_beg(line, *i);
		// printf("str_beg ==> %s\n",str_beg);
		concat_ext(&str1, &str_beg, &tmp, 1);
		tmp = str1;
	}
	if (line[*i + 1 + index])
	{
		str_end = ft_strdup(&line[*i + index + 1]);
		// printf("|index ==> %d|\t|%s|\n",*i + 1 + index,&line[*i + 1 + index]);
		// getchar();
		// printf("|index ==> %d|\t|%s|\n",*i + 1 + index,str_end);
		// getchar();
		concat_ext(&str1, &str_end, &tmp, 2);
	// printf("str1 ==> %s\n",str1);
		
	}
	// printf("str1 ==> %s\n",str1);
	*i = len + *i;
	if (*i < 0)
		*i = 0;
	// printf("i==> %d\n",*i);
		// printf("str1 ==> %s\n",&str1[*i]);
	return (str1);
}
