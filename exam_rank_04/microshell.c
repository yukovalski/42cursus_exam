#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define T_END	0
#define T_PIPE	1
#define T_BREAK	2

#define E_FATAL		0
#define	E_CD_ARG	1
#define E_CD_PATH	2
#define E_EXEC		3

typedef struct s_micro t_micro;

typedef struct	s_micro
{
	char		**args;
	int			fd[2];
	int			type;

	t_micro		*prev;
	t_micro		*next;
}				t_micro;

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return(i);
}

void	ft_lstadd(t_micro **shell, t_micro *new)
{
	if (!(*shell))
	{
		*shell = new;
		return;
	}
	t_micro *tmp = *shell;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;

}

void	error_exit(int error, char *str)
{
	if (error == E_FATAL)
		write(2, "error: fatal\n", 13);
	else if (error == E_CD_ARG)
		write(2, "error: cd: bad arguments\n", 25);
	else if (error == E_CD_PATH)
	{
		write(2, "error: cd: cannot change directory to ", 38);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	else
	{
		write(2, "error: cannot execute", 21);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	exit(1);
}

int		count_arg(char **str)
{
	int count = 0;
	while (str[count])
	{
		if (strcmp(str[count], ";") == 0  || strcmp(str[count], "|") == 0)
			break;
		count++;
	}
	return(count);
}

int		pars_arg(t_micro **shell, char **args)
{
	int count = count_arg(args);
	t_micro *new;
	if (!(new = malloc(sizeof(t_micro))) ||
		!(new->args = malloc(sizeof(char *) * (count + 1))))
		error_exit(E_FATAL, NULL);
	new->next = NULL;
	new->prev = NULL;
	new->args[count] = NULL;
	for (int i = 0; i < count; i++)
		new->args[i] = args[i];
	
	if (!args[count])
		new->type = T_END;
	else if (strcmp(args[count], "|") == 0)
		new->type = T_PIPE;
	else
		new->type = T_BREAK;
	ft_lstadd(shell, new);
	return(count);

}

void	exec_other_cmd(t_micro *shell, char **env)
{
	int		pipe_use = 0;
	int		st;

	if (shell->type == T_PIPE || shell->prev && shell->prev->type == T_PIPE)
	{
		pipe_use = 1;
		if (pipe(shell->fd))
			error_exit(E_FATAL, NULL);
	}

	pid_t	pid;
	if ((pid = fork()) < 0)
		error_exit(E_FATAL, NULL);
	else if (pid == 0)
	{
		if (shell->type == T_PIPE)
			if (dup2(shell->fd[1], 1) < 0)
				error_exit(E_FATAL, NULL);
		if (shell->prev && shell->prev->type == T_PIPE)
			if (dup2(shell->prev->fd[0], 0) < 0)
				error_exit(E_FATAL, NULL);
		if ((execve(shell->args[0],shell->args, env)) < 0)
			error_exit(E_EXEC, shell->args[0]);
		exit(0);
	}
	else
	{
		waitpid(pid, &st, 0);
		if (pipe_use == 1)
		{
			close(shell->fd[1]);
			if (!shell->prev || shell->type == T_BREAK)
				close(shell->fd[0]);
		}
		if (shell->prev && shell->prev->type == T_PIPE)
			close(shell->prev->fd[0]);
	}

}

void	exec_cmd(t_micro *shell, char **env)
{
	while (shell)
	{
		if (strcmp("cd", shell->args[0]) == 0)
		{
			if (shell->args[2])
				error_exit(E_CD_ARG, NULL);
			if (chdir(shell->args[1]))
				error_exit(E_CD_PATH, shell->args[1]);
		}
		else
			exec_other_cmd(shell, env);
		shell = shell->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_micro *shell = NULL;
	for (int i = 1; i <= ac; i++)
	{
		if (strcmp(av[i], ";") == 0)
			continue;
		i += pars_arg(&shell, &av[i]);
		if (!av[i])
			break;
	}
	if (shell)
		exec_cmd(shell, env);
	return (0);
}