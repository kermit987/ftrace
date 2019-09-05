/*
** ftrace.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace/test_lio/include
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Wed Apr 20 18:21:13 2016 Karmes Lionel
** Last update Sun May  1 23:05:22 2016 Steven Loo Fat
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <errno.h>
#include <string.h>
#include <linux/limits.h>
#include "ftrace.h"

void	print_exit(struct user_regs_struct* regs)
{
  regs->orig_rax = regs->rax;
  print_syscall(regs);
}

void				call_function(pid_t child,
					      const struct user_regs_struct*
					      regs,
					      const t_symbol *symbols,
					      t_symbol **symbols_entries)
{
  long				instruct;

  if ((instruct = ptrace(PTRACE_PEEKTEXT, child, regs->rip, NULL)) == -1)
    return ((void)fprintf(stderr, "err: ptrace(PTRACE_PEEKTEXT, ...): %s\n",
			  strerror(errno)));
  if (is_syscall(regs->orig_rax))
    print_syscall(regs);
  else
    is_call_or_ret(instruct, regs, symbols, symbols_entries);
}

void				proc_father(pid_t child,
					    const t_symbol *symbols)
{
  int				status;
  t_symbol			*symbols_entries;
  struct user_regs_struct	regs;

  symbols_entries = NULL;
  if (waitpid(child, &status, 0) == -1)
    return ((void)fprintf(stderr, "err: waipid()\n"));
  while (1)
    {
      if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
	return ((void)fprintf(stderr, "err: ptrace(PTRACE_GETREGS, ...): %s\n",
			      strerror(errno)));
      call_function(child, &regs, symbols, &symbols_entries);
      ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
      if (waitpid(child, &status, 0) == -1)
	return ((void)fprintf(stderr, "err: waipid()\n"));
      if (WIFEXITED(status))
	{
	  print_exit(&regs);
	  break ;
	}
      else if (WIFSTOPPED(status) && WSTOPSIG(status) != SIGTRAP)
	fprintf(stdout, "signal : %d\n", WSTOPSIG(status));
    }
}

void		ftrace(char **av, char *const *env)
{
  pid_t		child;
  char		path[PATH_MAX];
  t_symbol	*symbols;

  if (!find_bin(av[0], env, &path[0]))
    return ;
  if (!(symbols = load_call(&path[0])))
    return ;
  if ((child = fork()) == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, 0);
      if (execvp(av[0], av) == -1)
	return ((void)fprintf(stderr, "err: execvp(%s): %s\n",
			      av[0], strerror(errno)));
    }
  else
    proc_father(child, symbols);
  free_symbols(&symbols, -1);
}

int	main(int ac, char **av, char *const *env)
{
  if (ac < 2)
    {
      fprintf(stderr, "./ftrace <commande>\n");
      return (1);
    }
  ftrace(&av[1], env);
  return (0);
}
