# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:20:55 by mlantonn          #+#    #+#              #
#    Updated: 2019/10/08 16:07:49 by mlantonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= a.out
DIR_NAME		= malloc

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

SUBDIRS			=	
OBJ_SUBDIRS		=	$(addprefix $(OBJ_DIR), $(SUBDIRS))

#----------------------------------- FILES ------------------------------------#

INC_FILES		=	malloc.h
INCS			=	$(addprefix $(INC_DIR), $(INC_FILES))

SRC_FILES		=	main.c
SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES		=	$(SRC_FILES:.c=.o)
OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

#-------------------------------- COMPILATION ---------------------------------#

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror
IFLAGS			=	-I$(INC_DIR)
LFLAGS			=

FLAGS			=	$(CFLAGS) $(IFLAGS) $(LFLAGS)

#----------------------------------- RULES ------------------------------------#

.PHONY: all clean fclean re

# compilation rules

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(CC) $(FLAGS) $(OBJS) -o $(MAG)$(NAME)$(EOC)"
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS) $(INCS)
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

re: fclean all

# debug rules

debug: change_cflag all

re_debug: fclean debug

change_cflag:
	@$(eval CFLAGS = -fsanitize=address)
