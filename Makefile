# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 10:16:14 by leaugust          #+#    #+#              #
#    Updated: 2025/01/16 22:48:23 by leaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c \
				utils.c \
				init.c \
				philosophers.c \
				philo_utils.c

OBJ			=	$(SRC:.c=.o)

ROSE		=	\033[1;38;5;206m
LILA		=	\033[1;38;5;177m
NC			=	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(LILA)COMPILATION DE PHILOSOPHERS$(NC)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lpthread
	@echo "$(ROSE)PHILOSOPHERS CRÉÉ$(NC)"

clean:
	@echo "$(LILA)SUPPRESSION DES OBJECTS DANS PHILOSOPHERS$(NC)"
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "$(ROSE)DONE$(NC)"

fclean: clean
	@echo "$(LILA)SUPPRESSION DE L'EXÉCUTABLE DE PHILOSOPHERS$(NC)"
	@rm -f $(NAME)
	@echo "$(ROSE)DONE$(NC)"

re: fclean all

.PHONY: all clean fclean re
