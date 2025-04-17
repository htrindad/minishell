# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 17:08:01 by htrindad          #+#    #+#              #
#    Updated: 2024/05/04 12:46:18 by htrindad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = neo_libft.a

SRC = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
ft_memcpy.c  ft_memmove.c  ft_memset.c  ft_strlcat.c  ft_strlcpy.c  ft_strlen.c\
ft_toupper.c ft_tolower.c ft_strchr.c ft_strdup.c ft_atoi.c ft_strrchr.c\
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c ft_substr.c\
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstclear.c\
ft_lstiter.c ft_lstmap.c ft_lstadd_back.c ft_lstdelone.c

OBJS = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -O3

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJ)

clean:
	rm -f $(OBJS)

clean_bonus:
	rm -f $(BONUS_OBJ) $(OBJS)

fclean: clean clean_bonus
	rm -f $(NAME)

re: fclean all
