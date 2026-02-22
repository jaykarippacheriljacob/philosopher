# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkarippa <jkarippa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 15:25:06 by jkarippa          #+#    #+#              #
#    Updated: 2026/02/22 13:21:25 by jkarippa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME	=	philo
BNAME	=	
# Compiler and flags
CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
# Source files
SRC	=	philo.c	error_handling.c	parsing.c	\
		utils_write.c	utils_synchro_monitor.c	simulation.c	\
		utils_wrapper_fn.c utils_gen.c	utils_synchro_monitor1.c	\
		simulation1.c
BSRC	= 
# Object files
OBJ	=	$(SRC:.c=.o)
BOBJ	=	$(BSRC:.c=.o)
# Default rule
all: $(NAME)
# Linking the object files into the final executable
$(NAME):	$(OBJ)
	$(CC)	$(CFLAGS)	-o	$(NAME)	$(OBJ)
# Bonus rule
bonus:	all	$(BNAME)
# Linking the object files into the final executable
$(BNAME):	$(BOBJ)
	$(CC)	$(CFLAGS)	-o	$(BNAME)	$(BOBJ)
helgrind:
	valgrind --tool=helgrind --fair-sched=yes ./philo 5 800 200 200 7
# Clean object files
clean:
	rm	-f	$(OBJ)
	rm	-f	$(BOBJ)
# Clean everything (objects + executable)
fclean: clean
	rm	-f	$(NAME)
	rm	-f	$(BNAME)
# Rebuild everything
re:	fclean all
# Specify what happens when the Makefile is executed
help:
	@echo "Makefile for $(NAME)"
	@echo ""
	@echo "Usage:"
	@echo "  make           Build the project"
	@echo "  make bonus     -"
	@echo "  make clean     Remove all object files"
	@echo "  make fclean    Remove object files and executable"
	@echo "  make re        Rebuild the project"
	@echo "  make help      Display this help message"
	@echo "  make helgrind  Run Helgrind test (5 800 200 200 7)"