
#include "minishell.h"

void    unset_cmd(char *name, t_path *path)
{
    int i = 0;
	int j = 0;
    char **spl;
    int check = 0;
	if(ft_strchr(name,'\n'))
		name = ft_strtrim(name,"\n");
    while (path->env->fullenv[i])
    {
		if(!ft_strcmp(get_befor_equal(path->env->fullenv[i]),get_befor_equal(name)))
		{
			j = i;
			while (path->env->fullenv[j])
			{
				path->env->fullenv[j]=path->env->fullenv[j+1];
				j++;
			}
            break;
		}
        i++;
    }
    if (j)
        path->env->fullenv[j] = NULL;
}

void	execute_unset(t_path *path, t_command *l_cmd)
{
	unset_cmd(l_cmd->s_left->right->l_element->argument, path);
	path->dollar = 0;
}
