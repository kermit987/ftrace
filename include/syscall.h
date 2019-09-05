/*
** syscall.h for  in /home/obrero_k/depot/TEK2/Semestre4/SystemUnixInstrumentation/PSU_2015_strace
** 
** Made by Kevin OBRERO
** Login   <obrero_k@epitech.net>
** 
** Started on  Thu Apr  7 13:36:57 2016 Kevin OBRERO
** Last update Sun May  1 22:06:07 2016 Karmes Lionel
*/

#ifndef SYSCALL_H_
# define SYSCALL_H_

# include <sys/user.h>

typedef enum	enum_type
  {
    INT,
    CHAR,
    STR,
    TABSTR,
    VOID,
    ADDR,
    NUL,
  }		e_type;

typedef struct	s_syscall
{
  int args;
  char* name;
  e_type argsType[6];
  e_type returnType;
}		t_syscall;

extern t_syscall g_syscall[];

int	is_syscall(long long unsigned int);
void	print_syscall(const struct user_regs_struct *);

#endif /* !SYSCALL_H_ */
