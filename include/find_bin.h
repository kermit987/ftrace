/*
** find_bin.h for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_strace/include
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Wed Apr  6 18:11:53 2016 Karmes Lionel
** Last update Wed Apr 20 18:41:08 2016 Karmes Lionel
*/

#ifndef FIND_BIN_H_
# define FIND_BIN_H_

struct env_path
{
  int	len;
  char	*paths;
};

void	load_env_path(char* const *, struct env_path *);
int	find_bin(char *, char *const *, char *);
int	search_bin(char *, char *, char *);

#endif /* !FIND_BIN_H_ */
