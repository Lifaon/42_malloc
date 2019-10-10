# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:20:55 by mlantonn          #+#    #+#              #
#    Updated: 2019/10/10 16:56:11 by mlantonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft_malloc_$(HOSTTYPE).so
NAME_LNK		= libft_malloc.so
DIR_NAME		= malloc

ifeq ($(HOSTTYPE),)
	HOSTTYPE	= $(shell uname -m)_$(shell uname -s)
endif

#----------------------------------- COLOR ------------------------------------#

RED				=	\033[31m
GRE				=	\033[32m
YEL				=	\033[33m
BLU				=	\033[34m
MAG				=	\033[35m
CYA				=	\033[36m
EOC				=	\033[0m

#-------------------------------- DIRECTORIES ---------------------------------#

SRC_DIR			=	src/
OBJ_DIR			=	obj/
INC_DIR			=	inc/

OBJ_SUBDIRS		=	$(addprefix $(OBJ_DIR), $(SUBDIRS))
SUBDIRS			=	

#----------------------------------- FILES ------------------------------------#

INCS			=	$(addprefix $(INC_DIR), $(INC_FILES))
INC_FILES		=	malloc.h	\
					zone.h

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_FILES		=	malloc.c	\
					realloc.c	\
					free.c		\
					g_data.c	\

OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES		=	$(SRC_FILES:.c=.o)

#-------------------------------- COMPILATION ---------------------------------#

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror
IFLAGS			=	-I$(INC_DIR)
LFLAGS			=

#----------------------------------- RULES ------------------------------------#

.PHONY: all clean fclean re

# compilation rules

all: $(NAME) $(NAME_LNK)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -shared $(OBJS) -o $(MAG)$(NAME)$(EOC)"
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -shared $(OBJS) -o $(NAME)

$(NAME_LNK):
	@echo "ln -s $(NAME) $(MAG)$(NAME_LNK)$(EOC)"
	@ln -s $(NAME) $(NAME_LNK)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@echo "$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $(CYA)$@$(EOC)"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# mkdir rules

$(OBJ_DIR): $(OBJ_SUBDIRS)
	@mkdir -p $(OBJ_DIR)

$(OBJ_SUBDIRS):
	@mkdir -p $(OBJ_SUBDIRS)

# cleaning rules

clean:
	@echo "$(RED)rm -rf$(EOC) $(OBJ_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)rm -rf$(EOC) $(NAME) from $(DIR_NAME)"
	@rm -f $(NAME)
	@echo "$(RED)rm -rf$(EOC) $(NAME_LNK) from $(DIR_NAME)"
	@rm -f $(NAME_LNK)

re: fclean all

# debug rules

debug: change_cflag all

re_debug: fclean debug

change_cflag:
	@$(eval CFLAGS = -fsanitize=address)

# testing rules

test:
	@gcc main.c -L. -lft_malloc && ./a.out

test_debug:
	@gcc main.c -L. -lft_malloc -fsanitize=address && ./a.out

cl_test:
	@rm a.out
