# Name of the executable
NAME	=	philo
BNAME	=	
# Compiler and flags
CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
# Source files
SRC	=	philo.c	error_handling.c	initialize.c
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
	@echo "Usage:"
	@echo "  make          					Build the project"
	@echo "  make bonus    					-"
	@echo "  make clean    					Removes all object files"
	@echo "  make fclean   					Removes all object files, executables and the library"
	@echo "  make re       					Rebuild the project"
	@echo "  make help     					Display this help message"