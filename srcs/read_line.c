#include "minishell.h"
int var_glob = 0; /* hadi zadtha ha9ash fach kanktab shi haja o kandir ctrl + d o n annuli dakshi li ktabt b ctrl + c 
		     makat3awdsh tkhdam ctrl + d*/

int read_line(t_path *key, char **line)
{
	int ret;
	ret = 0;

	*line = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!line)
	{
		ft_putendl_fd("\e[0;31m bash$ : allocation error\e[0;37m",1);
		exit(1);
	}
	if ((ret = read(0, *line, BUFFER_SIZE)) == -1)
	{
		if (line[BUFFER_SIZE] == 0)
		{
			exit(0);
		}
		else
			exit(1);
	}
	return (ret);
}

void sigint_handler(int sig)
{
	int a;

	if (sig == SIGINT)
	{
		write(1, "\nbash$ ", 7);
		var_glob = 1;
		a = fork();
		if (!a)
		{
			char *cmd[] = {"/bin/stty", 0};
			char *cmd_args[] = {"stty", "-echoctl", 0};
			char *env[] = {" ", "env", 0};
			execve(cmd[0], cmd_args, env);
		}
	}
	if (sig == SIGQUIT)
	{
		pid_t iPid = getpid(); /* Process gets its id.*/
		kill(iPid, SIGINT);
		// write(1, "HERE", 4);
	}
}

int search_cmd(t_cmd *cmd)
{
	if (cmd->echo != 0 || cmd->cd != 0 || cmd->env != 0 ||
		cmd->exit != 0 || cmd->export != 0 || cmd->pwd != 0)
	{
		return (0);
	}
	return (1);
}

void execute_cmd(t_cmd *cmd)
{
	if (cmd->echo != 0)
		cmd->echo = 0;
}

void promp_bash(t_cmd *cmd, t_path *path, int ret, char **line)
{
	if (var_glob == 1)
		path->key->cntrd = 0;
	if (ret == 0 && path->key->cntrd != 1)
	{
		ft_putstr_fd("exit", 1);
		exit(1);
	}
	if (ft_strrchr(*line, '\n') && search_cmd(cmd))
	{
		bash_promp();
		path->key->cntrd = 0;
	}
	else if (ft_strrchr(*line, '\n'))
	{
		bash_promp();
		path->key->cntrd = 0;
	}
	if (ret > 0 && !ft_strrchr(*line, '\n'))
		path->key->cntrd = 1;
}

void check_pwd(t_cmd *cmd, char **line, t_path *path, int ret)
{
	if (ft_strnstr(*line, "pwd", 3))
		print_working_directory(path);
}

char **delete_quote(char **line)
{
	int i;
	int j;
	int index;
	char wich;

	i = 0;
	while (line[i])
	{
		j = 0;
		index = 0;
		while (line[i][j])
		{
			while (line[i][j] != 34 && line[i][j] != 39 && line[i][j])
				line[i][index++] = line[i][j++];
			if ((line[i][j] == 34 || line[i][j] == 39) && line[i][j])
			{
				wich = (line[i][j] == 34) ? 34 : 39;
				j++;
				while (line[i][j] != wich && line[i][j])
					line[i][index++] = line[i][j++];
				if (line[i][j] == '\0')
					line[i][index] = '\0';
				else
					j++;
			}
			if (line[i][j] == '\0')
				line[i][index] = '\0';
		}
		i++;
	}
	return (line);
}

bool check_quote(char *line)
{
	int i;
	int check;
	char wich;

	check = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			wich = (line[i] == 34) ? 34 : 39;
			i++;
			check = 0;
			while (line[i])
			{
				if (line[i] == wich)
				{
					check = 1;
					break;
				}
				i++;
			}
			if (check != 1)
				return (false);
		}
		if (line[i])
			i++;
	}
	return (true);
}

void ft_nhaydo_nl(char **tab)
{
	int count;
	int len;

	count = ft_2strlen(tab);
	len = ft_strlen(tab[count - 1]);
	tab[count - 1][len - 1] = '\0';
}

void check_cmd(t_cmd *cmd, char **line, t_path *path, int ret)
{
	int i;
	char **tab;

	i = 1;
	if (ft_strnstr(*line, "echo", 4))
	{
		if (check_quote(*line))
		{
			tab = ft_space_split(*line);
			tab = delete_quote(tab);
			cmd->echo = 1;
			if (ft_str_in_str(tab[0], "echo\n"))
				write(1, "\n", 1);
			else
			{
				if (tab[1] == 0)
					path->key->cntrd = 1;
				else
				{
					if (ft_strnstr(tab[1], "-n", 2) || ft_strnstr(tab[1], "-n\n", 3))
					{
						ft_nhaydo_nl(tab);
						i++;
					}
					while (i < ft_2strlen(tab))
					{
						ft_putstr_fd(tab[i++], 1);
						if (i < ft_2strlen(tab))
							write(1, " ", 1);
					}
				}
			}
		}
		else
		{
			ft_putstr_fd("check quotes", 1);
			exit(0);
		}
	}
	promp_bash(cmd, path, ret, line);
}

void bash_promp()
{

	ft_putstr_fd("\e[1;32mbash$ \e[0;37m", 1);
}

void loop_shell(t_path *path)
{
	char *line;
	int ret;
	int status;
	int salam;
	t_list_cmd *cmd = NULL;
	int i;

	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n can't catch cnrtl-C", 1);
	if (signal(SIGQUIT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("\n can't catch cntrl-\\", 1);
	status = 1;
	while (status)
	{
		bash_promp();
		ret = 0;
		ret = read_line(path, &line);
		if (line[0] == '\0')
		{
			exit(0);
					break;
		}
		ft_check_line(line);
    	cmd = add_list_cmd(cmd);
		cmd->line = ft_strdup(line);
    	parse_list_command(cmd, cmd->line);
		ft_strdel(&line);
    	sort(cmd);
    	quotes(cmd);
		commande_effect(cmd,path);
		var_glob = 0;
		free_lcommand(&cmd);
	}
}
