# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:20:55 by mlantonn          #+#    #+#              #
#    Updated: 2019/10/17 12:08:05 by mlantonn         ###   ########.fr        #
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

SRC_DIR				=	src/
OBJ_DIR				=	obj/
INC_DIR				=	inc/
LIB_DIR				=	lib/

OBJ_DIRS			=	$(OBJ_DIR) $(OBJ_SUBDIRS)
OBJ_SUBDIRS			=	$(addprefix $(OBJ_DIR), $(SUBDIRS))
SUBDIRS				=	

FT_PRINTF_DIR		=	$(LIB_DIR)ft_printf/
FT_PRINTF_INC_DIR	=	$(FT_PRINTF_DIR)inc/

#----------------------------------- FILES ------------------------------------#

INCS			=	$(addprefix $(INC_DIR), $(INC_FILES))
INC_FILES		=	mymalloc.h			\

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_FILES		=	malloc.c			\
					realloc.c			\
					calloc.c			\
					free.c				\
					g_data.c			\
					g_mtx.c				\
					show_alloc_mem.c	\

OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES		=	$(SRC_FILES:.c=.o)

FT_PRINTF		=	$(FT_PRINTF_DIR)/libftprintf.a

#-------------------------------- COMPILATION ---------------------------------#

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror
IFLAGS			=	-I$(INC_DIR) -I$(FT_PRINTF_INC_DIR)
LFLAGS			=	-L$(FT_PRINTF_DIR) -lftprintf

#----------------------------------- RULES ------------------------------------#

.PHONY: all clean fclean re

# compilation rules

all: $(FT_PRINTF) $(NAME) $(NAME_LNK)

$(NAME): $(OBJ_DIRS) $(OBJS)
	@echo "$(CC) -shared $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(MAG)$(NAME)$(EOC)"
	@$(CC) -shared $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(NAME_LNK):
	@echo "ln -s $(NAME) $(MAG)$(NAME_LNK)$(EOC)"
	@ln -s $(NAME) $(NAME_LNK)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@echo "$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $(CYA)$@$(EOC)"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

# mkdir rules

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)

# cleaning rules

clean:
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@echo "$(RED)rm -rf$(EOC) $(OBJ_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJ_DIR)

fclean:
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@echo "$(RED)rm -rf$(EOC) $(OBJ_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJ_DIR)
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
	@gcc main.c -L. -lft_malloc -Llib/ft_printf -lftprintf && ./a.out

test_debug:
	@gcc main.c -L. -lft_malloc -Llib/ft_printf -lftprintf -fsanitize=address && ./a.out

cl_test:
	@rm a.out
