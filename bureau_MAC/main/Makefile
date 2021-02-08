NAME = Cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra
# LDFLAGS =  -lmlx -framework OpenGL -framework AppKit
SRC = 	ft_atoi.c\
		ft_color.c\
		ft_error.c\
		ft_parcing_map_2.c\
		ft_parcing_map.c\
		ft_resolution.c\
		ft_split.c\
		ft_strtrim.c\
		ft_textures.c\
		get_next_line_utils.c\
		get_next_line.c\
		main.c\
		parse.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all




