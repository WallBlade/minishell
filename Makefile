SRC	=	$(wildcard lexer/*.c) \
		$(wildcard utils/*.c) \
		$(wildcard parser/*.c) \
		$(wildcard builtins/*.c) \

OBJ = $(SRC:.c=.o)

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g -I./includes

NAME = minishell
all	:	$(NAME)
$(NAME):	$(OBJ)
			make -C libft
			ar -rcs libft/libft.a
			cp libft/libft.a libft.a
			$(CC) $(CFLAGS) $(OBJ) libft.a -o  $(NAME) -lreadline

clean:
	$(RM) $(OBJ)
	@make clean -sC libft

fclean:	clean
		$(RM) $(NAME)
		$(RM) libft.a
		@make fclean -sC libft

re:			fclean $(NAME)

.PHONY:		all clean fclean re