# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aloubier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 12:58:01 by aloubier          #+#    #+#              #
#    Updated: 2023/08/12 23:45:32 by aloubier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCDIR = src
INCDIR = includes
OBJ_DIR = build

SRC = $(SRCDIR)/main.c $(SRCDIR)/output.c $(SRCDIR)/time.c $(SRCDIR)/status_check.c \
			$(SRCDIR)/threads.c
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)
	
$(OBJ_DIR)/%.o:	$(SRCDIR)/%.c
	mkdir -p '$(@D)'
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re
