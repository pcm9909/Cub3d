all:
	@make bonus -C libft/
	cc *.c map/*.c libft/libft.a -Lmlx -lmlx -lXext -lX11