NAME = pipex
CC = cc
FLAGS = -c -Wall -Wextra -Werror
IFLAGS = -I./libft
LFLAGS = -L./libft -lft
FILES = pipex.c \
		utils.c \
		parse.c
FILES_BONUS = pipex_bonus.c \
			utils_bonus.c \
			parse_bonus.c \
			get_next_line_bonus.c \
			get_next_line_utils_bonus.c
OBJS = $(FILES:.c=.o)
OBJS_BONUS = $(FILES_BONUS:.c=.o)
TO_BUILD =	$(if $(filter bonus, $(MAKECMDGOALS)), $(OBJS_BONUS), $(OBJS))

%.o: %.c
	$(CC) $(FLAGS) $(IFLAGS) $< -o $@

all: lib $(NAME)

$(NAME): $(TO_BUILD)
	$(CC) -g -fsanitize=address $(TO_BUILD) $(LFLAGS) -o $(NAME)

lib:
	cd libft && make

bonus : lib $(NAME)

clean:
	rm -f ./*.o libft/*.o

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re lib bonus