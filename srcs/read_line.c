#include "minishell.h"
int var_glob = 0; /* hadi zadtha ha9ash fach kanktab shi haja o kandir ctrl + d o n annuli dakshi li ktabt b ctrl + c 
                    makat3awdsh tkhdam ctrl + d*/

int read_line(t_key *key, char **line)
{
    int ret;
    ret = 0;

    // line = malloc(sizeof(char));
    *line = malloc(sizeof(char) * BUFFER_SIZE);
    ft_bzero(*line, BUFFER_SIZE);
    if (!line)
    {
        write(1, "bash$> allocation error\n", 30);
        exit(1);
    }
    if ((ret = read(0, *line, BUFFER_SIZE)) == -1)
    {
        if (line[BUFFER_SIZE] == 0)
            exit(0);
        else
            exit(1);
    }
    return (ret);
}

void sigint_handler(int sig)
{
    int a;

    // signal(SIGINT, sigint_handler);
    write(1, "\nbash$ ", 7);
    var_glob = 1;
    a = fork();
    if (!a) //a != 0
    {
        char *cmd[] = {"/bin/stty", 0};
        char *cmd_args[] = {"stty", "-echoctl", 0};
        char *env[] = {" ", "env", 0};
        execve(cmd[0], cmd_args, env);
    }
}

// void split_line(char *line)
// {
//     char **tab;
//     tab = ft_space_split(line);
//     int i;

//     i = 1;
//     if (ft_str_in_str("echo", tab[0]))
//     {
//         if (ft_2strlen(tab) == 1)
//             write(1, "\n", 1);
//         else
//         {
//             if (ft_2strlen(tab) == 2)
//                 ft_putstr_fd(tab[1], 1);
//             else
//             {
//                 while (i < ft_2strlen(tab))
//                 {
//                     ft_putstr_fd(tab[i++], 1);
//                     if (i < ft_2strlen(tab))
//                         write(1, " ", 1);
//                 }
//             }
//         }
//     }
// }

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
    {
        cmd->echo = 0;
    }
}

void promp_bash(t_cmd *cmd, t_key *key, int ret, char **line)
{
    if (var_glob == 1)
        key->cntrd = 0;
    if (ret == 0 && key->cntrd != 1)
    {
        ft_putstr_fd("exit", 1);
        exit(1);
    }
    if (ft_strrchr(*line, '\n') && search_cmd(cmd))
    {
        write(1, "bash$ ", 6);
        key->cntrd = 0;
    }
    else if (ft_strrchr(*line, '\n'))
    {
        if (cmd->echo != 1)
            write(1, "\n", 1);
        ft_putstr_fd("bash$ ", 1);
        key->cntrd = 0;
    }
    if (ret > 0 && !ft_strrchr(*line, '\n'))
    {
        key->cntrd = 1;
    }
    // else if (ret == 0 && !ft_strrchr(*line, '\n'))
    //     key->cntrd = 0;
    // printf("|ret ==> %d|\t|cntr ==> %d|\n", ret, key->cntrd);
    // printf("|cmd->echo ==> %d|\t|key->cntrd ==> %d|\n", cmd->echo, key->cntrd);
}

void check_cmd(t_cmd *cmd, char **line, t_key *key, int ret)
{
    int i;
    char **tab;

    i = 1;
    if (ft_strnstr(*line, "echo", 4))
    {
        tab = ft_space_split(*line);
        cmd->echo = 1;
        if (ft_str_in_str(tab[0], "echo\n"))
            write(1, "\n", 1);
        else
        {
            if (ft_2strlen(tab) == 2)
                ft_putstr_fd(tab[1], 1);
            else
            {
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
        cmd->echo = 0;
    promp_bash(cmd, key, ret, line);
}

void loop_shell(t_key *key, t_cmd *cmd)
{
    char *line;
    int ret;
    int status;
    int cntrd;
    int salam;

    signal(SIGINT, sigint_handler);
    status = 1;
    cntrd = 0;
    ft_putstr_fd("bash$ ", 1); //\e[32;40m
    while (status)
    {
        ret = 0;
        ret = read_line(key, &line);
        // ft_putnbr_fd(ret,1);
        check_cmd(cmd, &line, key, ret);
        var_glob = 0;
        free(line);
    }
}
