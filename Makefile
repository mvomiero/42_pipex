
#BSRCS	= pipex_bonus.c utils_bonus.c
SRCS	= srcs/pipex.c srcs/utils.c
NAME	= pipex
CC	= cc
FLAGS	= -Wall -Werror -Wextra -fsanitize=address
RM	= rm -f
INCS	= libft/includes
LIBFT	= -Llibft -lft

all: ${NAME}

${NAME}: runlibft 
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

ignore: runlibft
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

#bonus: runlibft 
#	${CC} ${FLAGS} -o ${NAME} ${BSRCS} -I ${INCS} ${LIBFT}

clean:
	make -C libft fclean

fclean: clean
	${RM} ${NAME}

re: fclean all

runlibft:
	make bonus -C libft

.PHONY: all re clean fclean