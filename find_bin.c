/*
** find_bin.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_strace
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Wed Apr  6 18:04:22 2016 Karmes Lionel
** Last update Sun May  1 22:05:24 2016 Karmes Lionel
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include "find_bin.h"

void	load_env_path(char* const *env, struct env_path *paths)
{
  int	i;

  i = 0;
  paths->len = 0;
  paths->paths = NULL;
  while (env[i] && !paths->paths)
    {
      if (!strncmp(env[i], "PATH=", 5))
	  paths->paths = &env[i][5];
      ++i;
    }
  if (!paths->paths || !paths->paths[0])
    return ;
  i = 0;
  while (paths->paths[i])
    {
      if (paths->paths[i] == ':')
	{
	  paths->paths[i] = '\0';
	  paths->len++;
	}
      ++i;
    }
  paths->len++;
}

int			find_bin(char *filename, char* const *env, char *path)
{
  struct env_path	paths;
  int			i;
  int			c;

  i = 0;
  c = 0;
  load_env_path(env, &paths);
  if (!strncmp(filename, "./", 2))
    {
      if (search_bin(filename, getcwd(path, PATH_MAX), path))
	return (1);
    }
  else
    while (c < paths.len)
      {
	if (search_bin(filename, &paths.paths[i], path))
	  return (1);
	i += strlen(&paths.paths[i]) + 1;
	++c;
      }
  fprintf(stderr, "ftrace: Can't stat '%s': %s\n", filename, strerror(errno));
  return (0);
}

int		search_bin(char *filename, char *abs_path, char *path)
{
  struct stat	buf;

  memmove(path, abs_path, strlen(abs_path) + 1);
  strcat(path, "/");
  strcat(path, filename);
  if (stat(path, &buf) == -1)
    return (0);
  return (1);
}
