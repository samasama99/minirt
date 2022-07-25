# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/21 15:23:06 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- VARIABLE DECLARATION --- #

NAME				=	mlx

CC					=	cc

# FLAGS				=	-Wall -Wextra -I libft -Ofast -ffast-math -march=native
FLAGS				=	-Wall -Wextra -I libft

MLX_FLAGS		=	-lmlx -framework OpenGL -framework AppKit

DEBUG				=	-g -D DEBUG

HEADER			=	src/main.h

LIBFT 			=	libft/libft.a

MAKE_LIBFT 	=	libft/

SRC 				=	src/main.c \
							src/mlx.c \
							src/vector.c \
							src/matrix.c \
							src/utils.c \
							src/handling_events.c \
						# src/draw.c \

OBJDIR 			=	obj

OBJ 				=	$(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})

# ---------------------------- #
	
# RULES

all	: ${NAME}

debug : ${SRC} ${LIBFT}
	@echo "${MGN}[DEBUG MODE]${NC}"
	@${CC} ${FLAGS} ${MLX_FLAGS} ${DEBUG} $^ -o ${NAME}

${LIBFT} :
	@echo "${YEL}MAKING LIBFT ...${NC}"
	@make -C ${MAKE_LIBFT}

${NAME} : ${OBJ} ${LIBFT}
	@echo "${YEL}LINKING PROCESS ...${NC}"
	@echo "${GRN}COMPILATION COMPLETE${NC}"
	@${CC} ${FLAGS} ${MLX_FLAGS} $^ -o ${NAME}

$(OBJDIR)/%.o : %.c ${HEADER}
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@
	@echo "${BLU}MAKING ::	$@${NC}"

clean : 
	@rm -rf ${OBJDIR}
	@make clean -C ${MAKE_LIBFT}

fclean : clean
	@rm -f ${NAME}
	@make fclean -C ${MAKE_LIBFT}

re : fclean all

.PHONY : bonus clean fclean all

# ---------------------------- #

# --- Terminal Color Codes --- #

NC		:= \033[31;0m
RED 	:= \033[0;31;1m
YEL 	:= \033[0;33;1m
GRA		:= \033[0;37;1m
CYN 	:= \033[0;36;1m
GRN 	:= \033[0;32;1m
MGN		:= \033[0;35;1m
BLU 	:= \033[0;34;1m

# ---------------------------- #
