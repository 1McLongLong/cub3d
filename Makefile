CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -fsanitize=address -g

MLX = ./MLX42/build/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/Users/${USER}/goinfre/.brew/Cellar/glfw/3.4/include/GLFW
LIB = -L/Users/$(USER)/goinfre/.brew/opt/glfw/lib/

SRCF = ./src/main.c ./src/key_handle.c ./src/move_player.c ./src/cast_rays.c

GNL_SRCF = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
OBJF = $(SRCF:.c=.o)
GNL_OBJF = $(GNL_SRCF:.c=.o)

NAME = cub3D

all : $(NAME)

$(NAME): $(OBJF) $(GNL_OBJF)
	@$(CC) $(CFLAGS) $^ $(MLX) $(FLAG_MLX) -o $@
	@echo "🚀 Mission complete!"

%.o : %.c ./include/header.h ./gnl/get_next_line.h
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJF) $(GNL_OBJF)
	@echo "BYE BYE 🤫🧏"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE CUB3D🤫🧏"

re: fclean all

.PHONY : all clean fclean re
