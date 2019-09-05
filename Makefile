##
## Makefile for  in /home/karmes_l/Projets/tek2/Systeme_Unix-Instrumentation/PSU_2015_strace
## 
## Made by Karmes Lionel
## Login   <karmes_l@epitech.net>
## 
## Started on  Mon Apr  4 20:10:20 2016 Karmes Lionel
## Last update Sun May  1 22:11:00 2016 Karmes Lionel
##

CC	= gcc -g

RM	= rm -f

SRCS	= ftrace.c \
	syscall.c \
	find_bin.c \
	call.c \
	symbol.c \
	my_elf.c


OBJS	= $(SRCS:.c=.o)

NAME	= ftrace

CFLAGS	+= -Wall -Wextra -Werror
CFLAGS	+= -I./include

LDFLAGS	= -lelf


all:	$(NAME)

$(NAME): $(OBJS)
	 @printf "\033[032m --- COMPILING ---\033[0m\n"
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@printf "\033[032m --- CLEAN ---\033[0m\n"
	$(RM) $(OBJS)

fclean: clean
	@printf "\033[032m --- FCLEAN ---\033[0m\n"
	$(RM) $(NAME)

re: fclean all
	@printf "\033[032m --- RE DONE---\033[0m\n"

.PHONY: all clean fclean re
