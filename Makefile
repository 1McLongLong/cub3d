CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRCF = ./src/main.c ./src/key_handle.c

#LIBFT_SRCF = $(addprefix libft/, ft_atoi.c ft_isalpha.c ft_isprint.c ft_memmove.c ft_putchar_fd.c ft_putnbr_fd.c ft_split.c ft_strcmp.c ft_strdup.c ft_strlcpy.c ft_strncmp.c ft_strstr.c \
			ft_isalnum.c ft_isdigit.c ft_itoa.c ft_memset.c ft_memcpy.c ft_putendl_fd.c ft_putstr_fd.c ft_strchr.c ft_strcpy.c ft_strjoin.c ft_strlen.c ft_strrchr.c ft_substr.c)

GNL_SRCF = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
OBJF = $(SRCF:.c=.o)
GNL_OBJF = $(GNL_SRCF:.c=.o)
#LIBFT_OBJF = $(LIBFT_SRCF:.c=.o)

NAME = cub3D

all : $(NAME)

$(NAME): $(OBJF) $(GNL_OBJF)
	@$(CC) $(CFLAGS) $^ -lmlx -framework OpenGL -framework AppKit -o $@
	@echo "🚀 Mission complete!"

%.o : %.c ./include/header.h ./gnl/get_next_line.h
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@rm -f $(OBJF) $(GNL_OBJF)
	@echo "BYE BYE 🤫🧏"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE CUB3D🤫🧏"

re: fclean all

.PHONY : all clean fclean re
