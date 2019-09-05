/*
** symbol.h for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace/test_lio/include
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Wed Apr 20 18:18:26 2016 Karmes Lionel
** Last update Sun May  1 21:34:16 2016 Karmes Lionel
*/

#ifndef SYMBOL_H_
# define SYMBOL_H_

# include <elf.h>
# include <sys/user.h>

typedef struct		s_symbol
{
  char			*name;
  Elf64_Addr		addr;
  struct s_symbol	*next;
}			t_symbol;

void		free_symbols(t_symbol **, int);
void		add_cpy_symbol(t_symbol **, const t_symbol *);
const t_symbol*	find_symbol(const t_symbol *, long unsigned);

#endif /* SYMBOL_H_ */
