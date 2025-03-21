all:
	cc *.c map/*.c libft/libft.a -Lmlx -lmlx -lXext -lX11 -lm -g -fsanitize=address

mac:
	cc -L ./minilibx_opengl_20191021 -lmlx -framework OpenGL ./libft/libft.a ./map/*.c -framework AppKit *.c