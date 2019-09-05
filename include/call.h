/*
** call.h for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace/test_lio/include
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Wed Apr 20 18:18:26 2016 Karmes Lionel
** Last update Sun May  1 21:23:24 2016 Karmes Lionel
*/

#ifndef CALL_H_
# define CALL_H_

# include <elf.h>
# include <sys/user.h>
# include "symbol.h"

void	is_call_or_ret(long, const struct user_regs_struct *, const t_symbol *, t_symbol **);

#endif /* CALL_H_ */
