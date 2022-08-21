# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 15:27:34 by orahmoun          #+#    #+#              #
#    Updated: 2022/03/21 09:44:40 by orahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET    = libft.a

SRCS    =  ft_isdigit.c ft_memset.c ft_isprint.c ft_strlcat.c\
           ft_strlcpy.c ft_tolower.c ft_bzero.c ft_strlen.c\
           ft_toupper.c ft_isalnum.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
           ft_strnstr.c ft_isascii.c ft_memmove.c ft_strrchr.c\
           ft_memcpy.c ft_calloc.c ft_strdup.c ft_memchr.c\
           ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c\
           ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
           ft_strmapi.c ft_atoi.c ft_split.c ft_striteri.c ft_memcmp.c \
					 ft_malloc.c ft_split_space.c

SRCSB	=	ft_lstnew.c ft_lstiter.c ft_lstadd_back.c ft_lstlast.c ft_lstdelone.c\
			ft_lstclear.c ft_lstadd_front.c ft_lstsize.c ft_lstmap.c 

HEAD	=	libft.h

OBJSB	=	$(SRCSB:.c=.o)

OBJS	=	$(SRCS:.c=.o)


FLAGS	=	-Wall -Werror -Wextra -Ofast -ffast-math -march=native

CC	=	cc

all	:	$(TARGET) bonus

$(TARGET)	:	$(OBJS) $(HEAD)
	@ar rcs	$@	$^

bonus:	$(OBJS) $(OBJSB) $(HEAD)
	@ar rcs $(TARGET) $(OBJS) $(OBJSB)

%.o	:	%.c
	@$(CC) $(FLAGS) -c $<

clean:
	@rm -rf $(OBJS) $(OBJSB)

fclean:	clean
	@rm	-rf	$(TARGET)

re: fclean all
