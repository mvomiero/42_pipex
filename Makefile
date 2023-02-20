# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:19:44 by mvomiero          #+#    #+#              #
#    Updated: 2023/02/20 12:09:37 by mvomiero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= srcs/pipex.c srcs/utils.c
OBJS	= ${SRCS:.c=.o}
NAME	= pipex
CC	= cc
FLAGS	= -Wall -Werror -Wextra 
#-fsanitize=address -g3
RM	= rm -f
INCS	= libft/includes
LIBFT	= -Llibft -lft

all: ${NAME}

${NAME}: $(SRCS)
	make -C libft
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

clean:
	make -C ./libft fclean
	rm -f ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

# *** TESTING

INFILE	= infile.txt
OUTFILE	= outfile.txt
IN_CMD	= "ls -l"
OUT_CMD	= "cat"
IN_CMD_B	= $(IN_CMD:"%=%)
IN_CMD_BA	= $(IN_CMD_B:%"=%)
OUT_CMD_BA	= $(OUT_CMD_B:%"=%)
OUT_CMD_B	= $(OUT_CMD:"%=%)
VALGRIND = valgrind --leak-check=full --track-fds=yes
#--track-fds=yes 

test: test_pipex test_bash

test_pipex:
	@touch infile.txt
	@echo "**** TEST PIPEX ****"
# - is to ignore if  there is an error
#	- ${VALGRIND}
	-./pipex $(INFILE) $(IN_CMD) $(OUT_CMD) $(OUTFILE)
	@cat outfile.txt

test_bash:
	@echo "*** TEST BASH ****"
# - is to ignore if there is an error
	-< $(INFILE) $(IN_CMD_BA) | $(OUT_CMD_BA) > $(OUTFILE)
	@cat outfile.txt

test_clean:
	@rm -f infile.txt outfile.txt

.PHONY: all re clean fclean test
