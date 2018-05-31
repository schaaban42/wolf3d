# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/19 09:41:23 by schaaban          #+#    #+#              #
#    Updated: 2018/05/20 15:39:36 by schaaban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		wolf3d

CC			=		gcc
FLAGS		=		-Wall -Werror -Wextra

INC_DIR		=		./includes
SRCS_DIR	=		./srcs
OBJS_DIR	=		./objs

LFT_DIR		=		./libft
LFT_I_DIR	=		$(LFT_DIR)/includes
LFT_NAME	=		ft

SDL_DIR		=		./sdl2_srcs
SDL_I_DIR	=		$(SDL_DIR)/include

CC_INC		=		-I$(INC_DIR) -I$(LFT_I_DIR) -I$(SDL_I_DIR)
CC_LINK		=		-L$(LFT_DIR) -l$(LFT_NAME) -L$(SDL_DIR)/build/.libs \
					-lSDL2main -lSDL2 -lpthread -lm -ldl

SRCS		=		$(addprefix $(SRCS_DIR)/, 	\
					main.c						\
					inputs.c					\
					exit.c						\
					graphics.c					\
					draw.c						\
					update.c					\
					ray.c						\
					parser.c					\
					init.c						\
					ray_cast.c					\
					minimap.c					\
					graphics_line_mm.c			\
					color.c						\
					graphics_mm.c				\
					tex.c						\
					parser_ppm.c)
OBJS		=		$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

COLOR_RED	=	\033[1;31m
COLOR_BLUE	=	\033[1;34m
COLOR_GREEN	=	\033[1;32m
COLOR_WHITE	=	\033[0m

all: $(NAME)

$(NAME): dir_creation $(OBJS)
	@echo "$(COLOR_BLUE)WOLF3D - $(COLOR_GREEN)Compiling exe...$(COLOR_WHITE)"
	@$(MAKE) -C $(LFT_DIR)
	@$(MAKE) -C $(SDL_DIR)
	@$(CC) $(FLAGS) $(OBJS) $(CC_INC) $(CC_LINK) -o $(NAME)
	@echo "$(COLOR_BLUE)WOLF3D - $(COLOR_GREEN)Done !$(COLOR_WHITE)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INC_DIR)/$(NAME).h
	@$(CC) $(FLAGS) $(CC_INC) -o $@ -c $<

dir_creation:
	@echo "$(COLOR_BLUE)WOLF3D - $(COLOR_GREEN)Objs creation...$(COLOR_WHITE)"
	@mkdir -p $(OBJS_DIR)

clean:
	@echo "$(COLOR_BLUE)WOLF3D - $(COLOR_RED)Cleaning objs...$(COLOR_WHITE)"
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LFT_DIR) clean
	@$(MAKE) -C $(SDL_DIR) clean

fclean: clean
	@echo "$(COLOR_BLUE)WOLF3D - $(COLOR_RED)Cleaning libft...$(COLOR_WHITE)"
	@rm -rf $(NAME)
	@$(MAKE) -C $(LFT_DIR) fclean
	@$(MAKE) -C $(SDL_DIR) clean

re: fclean all

.PHONY: all re clean fclean dir_creation
