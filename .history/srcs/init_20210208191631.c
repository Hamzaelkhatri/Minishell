#include "minishell.h"

void init(t_path *path, t_key *key, t_cmd *cmd)
{
    ft_bzero(key, sizeof(t_key));
    ft_bzero(cmd, sizeof(t_cmd));
    // path->key = malloc(sizeof(t_key));
	ft_bzero(path->env,sizeof(t_env));
    // path->env = malloc(sizeof(t_env));
    path->dollar = 0;
}

void	init_simple_cmd(t_simple_command **parent, int i)
{
	(*parent)->l_element->cmd = NULL;
	(*parent)->l_element->argument = NULL;
	(*parent)->l_element->redirection.file = NULL;
	(*parent)->l_element->redirection.i_o = NULL;
	(*parent)->l_element->indice = i;
	(*parent)->right = NULL;
	(*parent)->parent = NULL;
}

void	init_lcommand(t_list_cmd **parent)
{
	(*parent)->line = NULL;
	(*parent)->command->s_left->l_element = NULL;
	(*parent)->command->s_left->right = NULL;
	(*parent)->command->right = NULL;
	(*parent)->next = NULL;
	(*parent)->previous = NULL;
	ft_bzero(&(*parent)->command->tool, sizeof(t_tool));
}
