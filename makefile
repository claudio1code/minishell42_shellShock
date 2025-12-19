GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;96m
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
	@echo -n $(YELLOW)"Linking $(NAME)... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null/; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)'
	@echo "\b$(GREEN)OK!$(DEF_COLOR)"

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@echo -n $(BLUE)"Compiling $<... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null/; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05 \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@'
	@echo "\b$(GREEN)OK!$(DEF_COLOR)"

clean: 
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all fclean clean re
