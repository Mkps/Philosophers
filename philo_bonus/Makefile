# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aloubier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 12:58:01 by aloubier          #+#    #+#              #
#    Updated: 2023/08/21 16:35:19 by aloubier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
SRCDIR = src/
INCDIR = includes/
OBJDIR = build/

SRC =	main.c output.c time.c status_check.c \
		philo_init.c philo_process.c philo_actions.c \
		init.c exit.c utils.c
SRCS = $(addprefix $(SRCDIR), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR), $(OBJ))

CC = cc

CFLAGS = -Wall -Wextra -Werror -pedantic -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)
	
$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p '$(OBJDIR)'
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
