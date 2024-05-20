CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -fsanitize=address -g

MLX = ./MLX42/build/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/Users/${USER}/goinfre/.brew/Cellar/glfw/3.4/include/GLFW
LIB = -L/Users/$(USER)/goinfre/.brew/opt/glfw/lib/

SRCF = ./exec/main.c ./exec/key_handle.c ./exec/move_player.c ./exec/cast_rays.c ./exec/free.c ./exec/render_wall.c ./parsing/utils.c ./parsing/list.c ./parsing/parsing_map.c ./parsing/start_parsing.c \
			 ./parsing/parsing_map_name.c ./parsing/parsing_map_color.c ./parsing/parsing_map_values.c
LIBFT =	./libft/ft_strtrim.c ./libft/ft_strlen.c ./libft/ft_substr.c ./libft/ft_split.c\
		 ./libft/ft_strcmp.c ./libft/ft_memset.c ./libft/ft_atoi.c ./libft/ft_strdup.c
GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c
GNL_SRCF = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
LIBFT_OBJF = $(LIBFT:.c=.o)
OBJF = $(SRCF:.c=.o)
GNL_OBJF = $(GNL:.c=.o)

NAME = cub3D

all : $(NAME)

$(NAME): $(OBJF) $(LIBFT_OBJF) $(GNL_OBJF)
	@$(CC) $(CFLAGS) $^ $(MLX) $(FLAG_MLX) -o $@
	@echo "🚀 Mission complete!"

%.o : %.c ./include/header.h  ./gnl/get_next_line.h
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJF) $(GNL_OBJF) $(LIBFT_OBJF)
	@echo "BYE BYE 🤫🧏"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE CUB3D🤫🧏"

re: fclean all
