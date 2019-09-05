/*
** symbol.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Wed Apr 27 15:31:30 2016 Karmes Lionel
** Last update Sun May  1 23:06:36 2016 Steven Loo Fat
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

void		free_symbols(t_symbol **symbols, int n)
{
  t_symbol	*tmp;

  tmp = *symbols;
  while (tmp && (n == -1 || n > 0))
    {
      *symbols = tmp->next;
      free(tmp->name);
      free(tmp);
      tmp = *symbols;
      n = (n == -1) ? -1 : n - 1;
    }
}

void		add_cpy_symbol(t_symbol **list, const t_symbol *elem)
{
  t_symbol	*front;

  if (!(front = malloc(sizeof(t_symbol))))
    return ;
  front->name = strdup(elem->name);
  front->addr = elem->addr;
  front->next = *list;
  *list = front;
}

const t_symbol*		find_symbol(const t_symbol *symbols,
				    long unsigned addr)
{
  const t_symbol*	tmp;

  tmp = symbols;
  while (tmp && tmp->addr != addr)
    tmp = tmp->next;
  return (tmp);
}
