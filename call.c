/*
** call.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace/test_lio
**
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
**
** Started on  Wed Apr 20 15:10:47 2016 Karmes Lionel
** Last update Sun May  1 23:04:25 2016 Steven Loo Fat
*/

#include <stdio.h>
#include "call.h"

long	call_e8(long instruct, long long unsigned int rip)
{
  int	addr_rel;
  long	addr_abs;

  instruct = instruct >> 8;
  addr_rel = instruct;
  addr_abs = addr_rel + rip + 5;
  return (addr_abs);
}

void	init_regs_opcode(char *regs_opcode)
{
  regs_opcode[0] = 0xD0;
  regs_opcode[1] = 0xD1;
  regs_opcode[2] = 0xD2;
  regs_opcode[3] = 0xD3;
  regs_opcode[4] = 0xD4;
  regs_opcode[5] = 0xD5;
  regs_opcode[6] = 0xD6;
  regs_opcode[7] = 0xD7;
  regs_opcode[8] = 0xD8;
  regs_opcode[9] = 0xD9;
  regs_opcode[10] = 0xDA;
  regs_opcode[11] = 0xDB;
  regs_opcode[12] = 0xDC;
  regs_opcode[13] = 0xDD;
  regs_opcode[14] = 0xDE;
  regs_opcode[15] = 0xDF;
}

void	init_regs_addr(long *regs_addr, const struct user_regs_struct *regs)
{
  regs_addr[0] = regs->rax;
  regs_addr[1] = regs->rcx;
  regs_addr[2] = regs->rdx;
  regs_addr[3] = regs->rbx;
  regs_addr[4] = regs->rsp;
  regs_addr[5] = regs->rbp;
  regs_addr[6] = regs->rsi;
  regs_addr[7] = regs->rdi;
  regs_addr[8] = regs->r8;
  regs_addr[9] = regs->r9;
  regs_addr[10] = regs->r10;
  regs_addr[11] = regs->r11;
  regs_addr[12] = regs->r12;
  regs_addr[13] = regs->r13;
  regs_addr[14] = regs->r14;
  regs_addr[15] = regs->r15;
}

long	call_ff(long instruct, const struct user_regs_struct *regs)
{
  char	reg_addr;
  char	regs_opcode[16];
  long	regs_addr[16];
  int	i;
  long	addr_abs;

  init_regs_opcode(&regs_opcode[0]);
  init_regs_addr(&regs_addr[0], regs);
  i = 0;
  reg_addr = instruct >> 8;
  while (i < 16 && regs_opcode[i] != reg_addr)
    ++i;
  if (i == 16)
    return (0);
  addr_abs = regs_addr[i];
  return (addr_abs);
}

void			is_call_or_ret(long instruct,
			       const struct user_regs_struct *regs,
			       const t_symbol *symbols,
			       t_symbol **symbols_entries)
{
  char			opcode;
  long			addr_abs;
  const t_symbol	*elem;

  opcode = instruct;
  addr_abs = 0;
  if (opcode == (char)0xe8)
    addr_abs = call_e8(instruct, regs->rip);
  else if (opcode == (char)0xff)
    addr_abs = call_ff(instruct, regs);
  else if ((opcode == (char)0xc3 || opcode == (char)0xcb
	    || opcode == (char)0xc2 || opcode == (char)0xca)
	   && *symbols_entries)
    {
      printf("Leaving function %s\n", (*symbols_entries)->name);
      free_symbols(symbols_entries, 1);
    }
  if (addr_abs && (elem = find_symbol(symbols, addr_abs)))
    {
      add_cpy_symbol(symbols_entries, elem);
      printf("Entering function %s at 0x%lx\n",
	     (*symbols_entries)->name, (*symbols_entries)->addr);
    }
}
