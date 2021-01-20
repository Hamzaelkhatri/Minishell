/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:44:38 by zdnaya            #+#    #+#             */
/*   Updated: 2021/01/19 18:28:52 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



char **check_each_node(char *line, t_shell *sh) {

  char **tmp;
  char **tmp1;
  char **tmp2;

  line = befor_direction(line, sh);
  tmp = ft_space_split(line);

  return (tmp);
}

