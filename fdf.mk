# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fdf.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 15:52:32 by rponsonn          #+#    #+#              #
#    Updated: 2022/03/03 17:12:25 by rponsonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

CC = gcc

CFLAGS	=	-Wall -Wextra -Werror -g

SRC_PATH =	srcs

SRC_NAME =	

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(SRC_PATH)/,$(OBJ_NAME))

LDLIBS = -lft -lmlx -lm

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBX_FD = ./minilibx_macos
	LDLIBS += -framework OpenGL -framework AppKit
else
	LIBX_FD = ./minilibx-linux
	LDLIBS += -lXext -lX11
endif

LDFLAGS = -Llibft -L$(LIBX_FD)

CPPFLAGS = -I./includes -I$(LIBX_FD) -I./libft

LIBS = libft/libft.a $(LIBX_FD)/libmlx.a

all : $(NAME)

libft/libft.a :
	make -C libft/ all

$(LIBX_FD)/libmlx.a :
	make all -C $(LIBX_FD)


$(NAME) : $(LIBS) $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(SRC_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
	make clean -C $(LIBX_FD)
	make fclean -C libft
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean re fclean
