# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 20:08:28 by dukim             #+#    #+#              #
#    Updated: 2025/03/26 20:08:29 by dukim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror #-g -fsanitize=address
NAME		=	cub3D
LIBFT		=	libft
LIBFT_LIB	=	libft.a
MLX			=	mlx
MLX_LIB		=	libmlx.a

SRCS		= 	main.c player.c hooks.c init.c \
				map/config.c map/parse_file.c map/parse_utils.c map/str_utils.c \
				render/render_util1.c render/render_util2.c render/render.c

OBJS 		:=	$(SRCS:%.c=%.o)

.PHONY:			all clean fclean re

all			:	$(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) 	

$(LIBFT_LIB):
				@make bonus -C $(LIBFT)

$(MLX_LIB)	:
				@make -C $(MLX)

%.o: %.c
				$(CC) $(CFLAGS) -I$(LIBFT) -I$(MLX) -I./inc -c $< -o $@

clean		:
				@make clean -C $(LIBFT)
				@make clean -C $(MLX)
				@rm -f $(OBJS)

fclean		:	clean
				@rm -f $(LIBFT)/$(LIBFT_LIB)
				@rm -f $(MLX)/$(MLX_LIB)
				@rm -f $(NAME)

re			:	fclean all