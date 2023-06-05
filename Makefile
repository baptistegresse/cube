NAME		=	cub3D
BMP			=	./screenshot.bmp
MLX			=	libmlx.a

SRCS			=	sources/main.c \
					sources/utils/*.c \
					sources/parse/*.c \
					sources/display/*.c \
					sources/garbage/*.c \

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

RMRF		=	rm -rf

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
$(NAME):
			@echo "\033[33m[Cub3D MACOS compilation...]"
			@ $(MAKE) -C mlx all
			@ cp ./mlx/$(MLX) .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(SRCS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "\033[32m[ ./cub3D created ]"
endif

ifeq ($(UNAME), Linux)
$(NAME):
			@echo "\033[31;1mCompiling for Linux...\033[0m"
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(SRCS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "\033[32m[ ./cub3D created ]"
endif

all:		$(NAME)

ifeq ($(UNAME), Darwin)
clean:
			@ echo "\033[31m[Remove last version...]"
			@ $(MAKE) -C mlx clean
			@ $(RM) $(BMP)
endif

ifeq ($(UNAME), Linux)
clean:
			@ echo "\033[31m[Remove last version...]"
			@ $(MAKE) -C mlx_linux clean
			@ $(RM) $(BMP)
endif

fclean:		clean
			@ $(RM) $(MLX)
			$(RM) cub3D


re:			fclean all

.PHONY:		$(NAME) all test clean fclean re

