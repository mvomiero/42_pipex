# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 18:00:23 by mvomiero          #+#    #+#              #
#    Updated: 2023/02/13 18:21:37 by mvomiero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PIPEX	= pipex

SRCS	= srcs/pipex.c srcs/utils.c
OBJS	= ${SRCS:.c=.o}
MAIN	= srcs/pipex.c

INCS	= -I ./includes/

CFLAGS	= -Wall -Wextra -Werror

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${INCS} -c $< -o $(<:.c=.o)

all: 		${PIPEX}

${PIPEX}:	${OBJS}
					@make re -C ./libft
					@cc ${OBJS} -Llibft -lft -o ${PIPEX}

clean:
					@make clean -C ./libft
					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(PIPEX)
					@rm -f ${PROG}

re:			fclean all
