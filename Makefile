
#BSRCS	= pipex_bonus.c utils_bonus.c
SRCS	= srcs/pipex.c srcs/utils.c
OBJS	= ${SRCS:.c=.o}
NAME	= pipex
CC	= cc
FLAGS	= -Wall -Werror -Wextra 
#-fsanitize=address
RM	= rm -f
INCS	= libft/includes
LIBFT	= -Llibft -lft

all: ${NAME}

${NAME}: runlibft 
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

ignore: runlibft
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

clean:
	make -C ./libft fclean
	rm -f ${OBJS}


fclean: clean
	${RM} ${NAME}

re: fclean all

runlibft:
	make bonus -C libft

# *** TESTING

INFILE	= infile.txt
OUTFILE	= outfile.txt
IN_CMD	= "ciao"
OUT_CMD	= "wc -l"
IN_CMD_B	= $(IN_CMD:"%=%)
IN_CMD_BA	= $(IN_CMD_B:%"=%)
OUT_CMD_B	= $(OUT_CMD:"%=%)
OUT_CMD_BA	= $(OUT_CMD_B:%"=%)

test: test_pipex test_bash

test_pipex:
	@echo "**** TEST PIPEX ****"
# - is to ignore if there is an error
	-./pipex $(INFILE) $(IN_CMD) $(OUT_CMD) $(OUTFILE)
	@cat outfile.txt

test_bash:
	@echo "*** TEST BASH ****"
# - is to ignore if there is an error
	-< $(INFILE) $(IN_CMD_BA) | $(OUT_CMD_BA) > $(OUTFILE)
	@cat outfile.txt

.PHONY: all re clean fclean
