/*
** my_elf.c for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_ftrace
** 
** Made by Karmes Lionel
** Login   <karmes_l@epitech.net>
** 
** Started on  Fri Apr 29 10:23:11 2016 Karmes Lionel
** Last update Sun May  1 21:26:05 2016 Karmes Lionel
*/

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_elf.h"

void		load_symbols(Elf *e, const GElf_Shdr *shdr, Elf_Scn *scn,
		     t_symbol **symbols)
{
  Elf_Data	*data;
  int		c;
  GElf_Sym	sym;
  t_symbol	*front;

  data = elf_getdata(scn, NULL);
  c = shdr->sh_size / shdr->sh_entsize;
  while (c > 0)
    {
      if (!(front = malloc(sizeof(t_symbol))))
	return ;
      gelf_getsym(data, c - 1, &sym);
      front->name = strdup(elf_strptr(e, shdr->sh_link, sym.st_name));
      front->addr = sym.st_value;
      front->next = *symbols;
      *symbols = front;
      --c;
    }
}

void*		close_elf(int fd, Elf *e)
{
  close(fd);
  if (e)
    elf_end(e);
  return (NULL);
}

t_symbol*	load_call(const char *path)
{
  int		fd;
  Elf*		e;
  Elf_Scn	*scn;
  GElf_Shdr	shdr;
  t_symbol	*symbols;

  if (elf_version(EV_CURRENT) == EV_NONE)
    return (fprintf(stderr, "Err: Elf%s\n", elf_errmsg(elf_errno())), NULL);
  if ((fd = open(path, O_RDONLY, 0)) < 0)
    return (fprintf(stderr, "Err: open() %s\n", strerror(errno)), NULL);
  if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
    return (fprintf(stderr, "Err: elf_begin() %s\n", elf_errmsg(elf_errno())),
	    close_elf(fd, NULL));
  if (elf_kind(e) != ELF_K_ELF)
    return (fprintf(stderr, "Err: is not an ELF object\n"), close_elf(fd, e));
  scn = NULL;
  symbols = NULL;
  while ((scn = elf_nextscn(e, scn)) != NULL)
    {
      gelf_getshdr(scn, &shdr);
      if (shdr.sh_type == SHT_DYNSYM || shdr.sh_type == SHT_SYMTAB)
	load_symbols(e, &shdr, scn, &symbols);
    }
  close_elf(fd, e);
  return (symbols);
}
