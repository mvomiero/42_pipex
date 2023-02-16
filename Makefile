# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:19:44 by mvomiero          #+#    #+#              #
#    Updated: 2023/02/16 12:14:49 by mvomiero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= srcs/pipex.c srcs/utils.c
BSRCS	= srcs/pipex_bonus.c srcs/utils.c srcs/utils_bonus.c
OBJS	= ${SRCS:.c=.o}
BOBJS	= ${BSRCS:.c=.o}
NAME	= pipex
CC	= cc
FLAGS	= -Wall -Werror -Wextra 
#-fsanitize=address -g3
RM	= rm -f
INCS	= libft/includes
LIBFT	= -Llibft -lft

all: ${NAME}

${NAME}: runlibft
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

bonus: runlibft
	${CC} ${FLAGS} -o ${NAME} ${BSRCS} -I ${INCS} ${LIBFT}

clean:
	make -C ./libft fclean
	rm -f ${OBJS} ${BOBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

runlibft:
	make bonus -C libft

# *** TESTING

INFILE	= infile.txt
OUTFILE	= outfile.txt
IN_CMD	= "ls -l"
OUT_CMD	= "wc"
IN_CMD_B	= $(IN_CMD:"%=%)
IN_CMD_BA	= $(IN_CMD_B:%"=%)
OUT_CMD_B	= $(OUT_CMD:"%=%)
OUT_CMD_BA	= $(OUT_CMD_B:%"=%)

test: test_pipex test_bash

test_pipex:
	@touch infile.txt
	@echo "**** TEST PIPEX ****"
# - is to ignore if there is an error
	-./pipex $(INFILE) $(IN_CMD) $(OUT_CMD) $(OUTFILE)
	@cat outfile.txt

test_bash:
	@echo "*** TEST BASH ****"
# - is to ignore if there is an error
	-< $(INFILE) $(IN_CMD_BA) | $(OUT_CMD_BA) > $(OUTFILE)
	@cat outfile.txt

test_bonus: test_pipex_a test_bash_a test_pipex_b test_bash_b 

test_pipex_a:
	@touch infile.txt
	@echo "**** TEST PIPEX ****"
	-./pipex $(INFILE) $(IN_CMD) "wc -l" $(OUT_CMD) $(OUTFILE)
	@cat outfile.txt

test_bash_a:
	@echo "*** TEST BASH ****"
	-< $(INFILE) $(IN_CMD_BA) | wc -l | $(OUT_CMD_BA) > $(OUTFILE)
	@cat outfile.txt

test_pipex_b:
	@touch infile.txt
	@echo "**** TEST PIPEX ****"
	-./pipex here_doc LIMITER cat wc $(OUTFILE)
	@cat outfile.txt

test_bash_b:
	@echo "*** TEST BASH ****"
	-cat << LIMITER | wc >> $(OUTFILE)
	@cat outfile.txt

.PHONY: all re clean fclean test
