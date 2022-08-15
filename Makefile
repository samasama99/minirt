# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 17:52:43 by orahmoun          #+#    #+#              #
#    Updated: 2022/08/15 12:58:46 by zsarir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- VARIABLE DECLARATION --- #

NAME				=	minirt

CC					=	cc

FLAGS				=	-Wall -Wextra -Werror -I libft

MLX_FLAGS		=	-lmlx -framework OpenGL -framework AppKit

HEADER			=	src/main.h src/parsing.h src/linear_algebra.h src/main.h src/get_next_line.h src/parsing.h

LIBFT 			=	libft/libft.a

MAKE_LIBFT 	=	libft/

SRC 				=	src/camera.c \
						src/cone.c \
						src/cylinder.c \
						src/discriminant.c \
						src/get_next_line.c \
						src/intersection.c \
						src/light.c \
						src/matrix.c \
						src/matrix2.c \
						src/matrix3.c \
						src/matrix4.c \
						src/mlx.c \
						src/mlx2.c \
						src/mlx3.c \
						src/mlx4.c \
						src/parsing.c \
						src/parsing2.c \
						src/parsing3.c \
						src/parsing_2.c \
						src/parsing_3.c \
						src/parsing_rt.c \
						src/parsing_rt2.c \
						src/parsing_utils.c \
						src/plane.c \
						src/prof.c \
						src/ray.c \
						src/ray2.c \
						src/render.c \
						src/rgb.c \
						src/rgb2.c \
						src/shading.c \
						src/sphere.c \
						src/transform.c \
						src/transform2.c \
						src/utils.c \
						src/vector.c \
						src/vector2.c \
						src/vector3.c \
						src/vector4.c \
						src/world.c \
						main.c

OBJDIR 			=	obj

OBJ 				=	$(addprefix ${OBJDIR}/, ${SRC:%.c=%.o})

# ---------------------------- #
	
# RULES

all	: ${NAME} 

${LIBFT} :
	@echo "${YEL}MAKING LIBFT ...${NC}"
	@make -C ${MAKE_LIBFT}

${NAME} : ${OBJ} ${LIBFT}
	@echo "${YEL}LINKING PROCESS ...${NC}"
	@echo "${GRN}COMPILATION COMPLETE${NC}"
	${CC} ${MLX_FLAGS} $^  -o ${NAME}

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
