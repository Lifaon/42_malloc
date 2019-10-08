# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:20:55 by mlantonn          #+#    #+#              #
#    Updated: 2019/10/08 17:40:28 by mlantonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft_malloc_$(HOSTTYPE).so
LNK_NAME		= libft_malloc.so
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
INC_FILES		=	malloc.h

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_FILES		=	malloc.c	\
					realloc.c	\
					free.c

OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES		=	$(SRC_FILES:.c=.o)

#-------------------------------- COMPILATION ---------------------------------#

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror
IFLAGS			=	-I$(INC_DIR)
LFLAGS			=

FLAGS			=	$(CFLAGS) $(IFLAGS) $(LFLAGS)

#----------------------------------- RULES ------------------------------------#

.PHONY: all clean fclean re

# compilation rules

all: $(NAME) $(LNK_NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(CC) $(FLAGS) $(OBJS) -o $(MAG)$(NAME)$(EOC)"
	@$(CC) $(FLAGS) -shared $(OBJS) -o $(NAME)

$(LNK_NAME):
	@echo "ln -s $(NAME) $(MAG)$(LNK_NAME)$(EOC)"
	@ln -s $(NAME) $(LNK_NAME)

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
	@echo "$(RED)rm -rf$(EOC) $(LNK_NAME) from $(DIR_NAME)"
	@rm -f $(LNK_NAME)

re: fclean all

# debug rules

debug: change_cflag all

re_debug: fclean debug

change_cflag:
	@$(eval CFLAGS = -fsanitize=address)
