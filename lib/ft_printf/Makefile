# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 22:00:00 by mlantonn          #+#    #+#              #
#    Updated: 2019/10/15 18:11:19 by mlantonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libftprintf.a
DIR_NAME		= ft_printf

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
LIB_DIR			=

OBJ_DIRS		=	$(OBJ_DIR) $(OBJ_SUBDIRS)
OBJ_SUBDIRS		=	$(addprefix $(OBJ_DIR), $(SUBDIRS))
SUBDIRS			=	conv/	\
					parse/

#----------------------------------- FILES ------------------------------------#

INCS			=	$(addprefix $(INC_DIR), $(INC_FILES))
INC_FILES		=	conv.h \
					defines.h \
					parse.h \
					structs.h \
					utils.h

SRCS			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_FILES		=	ft_printf.c \
					ft_vprintf.c \
					buffer.c \
					init_param.c \
					parse_fmt.c \
					\
					conv/ft_atoi.c \
					conv/ft_dtoa.c \
					conv/ft_itoa.c \
					conv/ft_utoa_base.c \
					\
					parse/print_type.c \
					parse/b.c \
					parse/c.c \
					parse/f.c \
					parse/i.c \
					parse/o.c \
					parse/p.c \
					parse/s.c \
					parse/u.c \
					parse/x.c

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

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
	@echo "ar rc $(YEL)$(NAME)$(EOC) $(OBJS)"
	@ar rc $(NAME) $(OBJS)
	@echo "ranlib $(YEL)$(NAME)$(EOC)"
	@ranlib $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@echo "$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $(CYA)$@$(EOC)"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# mkdir rules

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)

# cleaning rules

clean:
	@echo "$(RED)rm -rf$(EOC) $(OBJ_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJ_DIR)

fclean:
	@echo "$(RED)rm -rf$(EOC) $(OBJ_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)rm -rf$(EOC) $(NAME) from $(DIR_NAME)"
	@rm -f $(NAME)

re: fclean all

# debug rules

debug: change_cflag all

re_debug: fclean debug

change_cflag:
	@$(eval CFLAGS = -fsanitize=address)
