SRC	=	$(wildcard lexer/*.c) \

OBJ = $(SRC:.c=.o)

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I./includes

NAME = minishell
all	:	$(NAME)
$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o  $(NAME) -lreadline

clean:
	$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re