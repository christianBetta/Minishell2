/*
** main.c for  in /home/christian.betta/minishel/Minishell1-master
**
** Made by Christian Betta
** Login   <christian.betta@epitech.net>
**
** Started on  Thu Mar 23 17:27:05 2017 Christian Betta
** Last update Wed Apr 12 16:41:42 2017 Christian Betta
*/

//#include "include/my.h"
#include"my.h"

void    commande_unique(t_mini c, char **envp)
{
  c.argument = my_str_to_wordtab(c.buffer, ' ');
  if (my_strncmp("cd", c.argument[0]) == 0)
    cd(c, envp);
  else if ((c.buffer[0] == '.' && c.buffer[1] == '/') || chemin(c.buffer) == 1)
    my_exec_prog(c, envp);
  else if (my_strncmp("PATH", c.buffer) == 0)
    {
      my_put_str_tab_path(c.array);
      my_putchar('\n');
    }
  else if ((c.pid = fork()) == -1)
    exit (0);
  else
    my_pid(c, envp);
  my_putstr("> ");
}

void    commande_multiple(t_mini c, char **envp)
{
  c.i = 0;
  c.nbr = nbr_comm(c.buffer);
  c.buffer = my_epure_2(c.buffer);
  c.cmd = my_str_to_wordtab(c.buffer, ';');
  while (c.i <= c.nbr)
    {
      c.argument = my_str_to_wordtab(c.cmd[c.i], ' ');
      if (my_strncmp("cd ..", c.cmd[c.i]) == 0 ||
          my_strncmp("cd", c.cmd[c.i]) == 0)
        cd(c, envp);
      else if ((chemin(c.cmd[c.i]) == 1) ||
	       (c.cmd[c.i][0] == '.' && c.cmd[c.i][1] == '/'))
	my_exec_prog(c, envp);
      else if (my_strncmp("PATH", c.cmd[c.i]) == 0)
	{
          my_put_str_tab_path(c.array);
          my_putchar('\n');
        }
      else if ((c.pid = fork()) == -1)
	exit (0);
      else
	my_pid(c, envp);
      my_putstr("> ");
      c.i++;
    }
}

void            shell(t_mini c, char **envp)
{
  if (nbr_comm(c.buffer) == 0)
    commande_unique(c, envp);
  else
    commande_multiple(c,envp);
}

void    test_exit(t_mini c, char **envp)
{
  while (42)
    {
      c.buffer = get_next_line(0);
      if (c.buffer == NULL)
        {
	  if (isatty(0))
            my_putstr("exit\n");
          exit(0);
        }
      c.buffer = my_epure(c.buffer);
      if (c.buffer[0] == 's' && c.buffer[1] == 'e' && c.buffer[2] == 't')
	set_env(c, envp);
      else if (c.buffer[0] == 'u' && c.buffer[1] == 'n'
	       && c.buffer[2] == 's' && c.buffer[3] == 'e' && c.buffer[4] == 't')
	un_env(c, envp);
      else if (my_strncmp("exit", c.buffer) != 0)
	shell(c, envp);
      else
        my_exit(c.buffer);
    }
}

int	main(int ac, char **av, char **envp)
{
  t_mini	c;

  c.my_env = malloc(sizeof(char *) * (1000000));
  c.buffer = malloc(sizeof(char) * (1000));
  c.my_env = envp;
  my_putstr("> ");
  signal(SIGINT, control_c);
  c.array = copy_env(envp);
  test_exit(c, envp);
  free(c.my_env);
  free(c.buffer);
  return (1);
}