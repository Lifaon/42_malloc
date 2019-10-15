# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 22:00:00 by mlantonn          #+#    #+#              #
#    Updated: 2019/10/15 17:39:55 by mlantonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
MAG = \033[35m
CYA = \033[36m
EOC = \033[39m

NAME = libftprintf.a
DIR_NAME = ft_printf

CFLAGS = -Wall -Wextra -Werror

INC = -I $(INC_DIR)
INC_DIR = includes

OBJS = $(SRCS:.c=.o)
OBJS_DIR = ./objs
OBJS_SUB_DIRS = conv parse
OBJS_PRE = $(addprefix $(OBJS_DIR)/, $(OBJS))

SRCS_DIR = srcs
SRCS =	ft_printf.c \
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

.PHONY = all $(OBJS_DIR) $(NAME) clean fclean re

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "gcc $(CFLAGS) $(INC) -c $^ -o $(CYA)$@$(EOC)"
	@gcc $(CFLAGS) $(INC) -c $^ -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(addprefix $(OBJS_DIR)/, $(OBJS_SUB_DIRS))

$(NAME): $(OBJS_DIR) $(OBJS_PRE)
	@echo "ar rc $(YEL)$(NAME)$(EOC) $(OBJS_PRE)"
	@ar rc $(NAME) $(OBJS_PRE)
	@echo "ranlib $(YEL)$(NAME)$(EOC)"
	@ranlib $(NAME)

clean:
	@echo "$(RED)rm -rf$(EOC) $(OBJS_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(RED)rm -rf$(EOC) $(NAME)"
	@rm -rf $(NAME)

re: fclean all
