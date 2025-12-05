GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
DEF_COLOR = \033[0;39m

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCLUDES = -I includes

SRCS_LIST = 

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

all: $(NAME)

$(NAME):$(OBJS)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c

clean:

fclean:

re: fclean all

.PHONY: all fclean clean re
