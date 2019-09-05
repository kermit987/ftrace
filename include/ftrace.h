/*
** ftrace.h for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace/test_lio/include
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Wed Apr 20 18:12:40 2016 Karmes Lionel
** Last update Sun May  1 22:09:49 2016 Karmes Lionel
*/

#ifndef FTRACE_H_
# define FTRACE_H_

# include <unistd.h>
# include "find_bin.h"
# include "syscall.h"
# include "call.h"
# include "symbol.h"
# include "my_elf.h"

void	print_exit(struct user_regs_struct *);
void	call_function(pid_t child, const struct user_regs_struct *, const t_symbol *, t_symbol **);
void	proc_father(pid_t child, const t_symbol *);
void	ftrace(char **av, char *const *env);

/* void	catch_signal(); */

#endif /* !FTRACE_H_ */
