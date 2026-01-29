NAME= P_P.out

cc= cc -g3

lib_path= ../libft

lib = $(lib_path)/libft.a

flags=  -Wall\
		-Werror\
		-Wextra

header= parse.h

c_files= parse_init.c

o_files= $(c_files:.c=.o)


all: $(NAME)

$(NAME):$(o_files) $(header) $(lib)
	$(cc) $(o_files) $(flags) -L$(lib_path) -lft -o $@ -lreadline

$(lib):
	@$(MAKE) -sC $(lib_path)

%.o:%.c
	$(cc) $(flags) -I -I$(lib_path) -c $< -o $@

clean:
	rm -f $(o_files)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -sC $(lib_path) fclean

re: fclean all