NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRC = ./srcs/
INCS_DIR = ./incs

FILES =		$(SRC)main.c \
			$(SRC)alloc.c \
			$(SRC)free.c \
			$(SRC)utils.c \
			$(SRC)mutex.c \
			$(SRC)threads.c \
			$(SRC)time.c \
			$(SRC)philo_loop.c \
			$(SRC)supervisor.c \

OBJ_FILES = $(FILES:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCS_DIR)

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ -I$(INCS_DIR)

clean : 
	rm -rf $(OBJ_FILES)

fclean : clean
	rm -rf $(NAME)

re : fclean
	make all


.PHONY : all clean fclean re
