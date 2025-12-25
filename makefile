GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;96m
DEF_COLOR = \033[0;39m

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCS_DIR = srcs/
OBJS_DIR = objs/
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a


SRCS_LIST = exec/path_utils.c \
			exec/redirect.c \
			exec/exec.c \
			exec/tester.c


SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

INCLUDES = -I includes -I $(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME):$(OBJS) $(LIBFT)
	@printf "$(YELLOW)Linking $(NAME)... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) '
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)Compiling $<... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@'
	@printf "\b$(GREEN)OK!$(DEF_COLOR)\n"

$(LIBFT):
	@make -sC $(LIBFT_DIR)

clean: 
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make -sC $(LIBFT_DIR) fclean
re: fclean all

.PHONY: all fclean clean re
