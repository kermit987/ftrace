/*
** elf.h for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace/include
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Fri Apr 29 10:20:18 2016 Karmes Lionel
** Last update Sun May  1 10:48:06 2016 Karmes Lionel
*/

#ifndef MY_ELF_H_
# define MY_ELF_H_

# include <gelf.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "symbol.h"

t_symbol*	load_call(const char *);

#endif /* MY_ELF_H_ */
