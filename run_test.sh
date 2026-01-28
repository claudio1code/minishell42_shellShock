#!/bin/bash

# Compila o tester com os ficheiros do executor e a libft
cc -g3 \
    srcs/exec/tester.c \
    srcs/exec/exec.c \
    srcs/exec/redirect.c \
    srcs/exec/path_utils.c \
    srcs/exec/exec_pipeline.c \
    srcs/builtins/builtins.c \
	srcs/builtins/env_utils.c \
    srcs/builtins/echo.c \
	srcs/builtins/cd.c \
	srcs/builtins/pwd.c \
	srcs/builtins/export.c \
	srcs/builtins/unset.c \
	srcs/builtins/exit.c \
	srcs/builtins/exit_utils.c \
	srcs/builtins/env.c \
	srcs/builtins/hashtable.c \
    -I includes \
    -I libft/includes \
    -Llibft -lft \
    -lreadline \
    -o executor_tester

# Executa se compilou bem
if [ $? -eq 0 ]; then
    ./executor_tester
else
    echo "Erro de compilação ❌"
fi