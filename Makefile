SRCS	= main.c \
			philo_utils.c \
			routine.c \
			philo_fork_creation.c 

OBJS 	= ${SRCS:.c=.o}

NAME 	= philo

CC		= gcc

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror

.c.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:		${NAME}


clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re