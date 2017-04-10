/*
** shell2.c for  in /home/christian.betta/Minishell/PSU_2016_minishell1
**
** Made by Christian Betta
** Login   <christian.betta@epitech.net>
**
** Started on  Thu Mar 23 19:12:02 2017 Christian Betta
** Last update Mon Apr 10 17:56:06 2017 Christian Betta
*/

#include "include/my.h"

void    my_pid(t_mini c)
{
  int	a;

  if (c.pid == 0)
    {
      a = 0;
      while (c.array[a])
        {
          c.str_cat = mystrcat(c.array[a], c.argument[0]);
          exec_all(c);
          ++a;
        }
      if (c.array[a] == NULL || my_strncmp("cd", c.buffer) == -1)
	{
	  my_putstr(c.buffer);
	  my_putstr(": Command not found.\n");
	  exit (84);
	}
    }
  else
    wait(&c.status);
}

void             cd(t_mini cd)
{
  char **tabl;

  tabl = malloc(sizeof(char *) * 10);
  tabl = my_str_to_wordtab(cd.buffer,' ');
  if ((my_strncmp("cd", tabl[0])) == 0)
    {
      if (tabl[1] == NULL)
	chdir("/home/");
      else
	chdir(tabl[1]);
    }
  free(tabl);
}

char    *find_pwd(char **tabl)
{
  int   i;
  int   b;

  i = 0;
  while (tabl[i])
    {
      if (tabl[i][0] == 'P' && tabl[i][1] == 'W'
	  && tabl[i][2] == 'D' && tabl[i][3] == '=')
	b = i;
      i++;
    }
  return (tabl[b]);
}

char    **copy_env(char **envp)
{
  int           i;
  char          **tabl;

  i = 0;
  while (envp[i])
    {
      if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
	  envp[i][2] == 'T' && envp[i][3] == 'H')
	tabl = my_str_to_wordtab(envp[i], ':');
      i++;
    }
  return (tabl);
}
