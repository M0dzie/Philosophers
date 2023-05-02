# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 13:23:23 by thmeyer           #+#    #+#              #
#    Updated: 2023/05/02 15:24:16 by thmeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ##################################### #
#               VARIABLES               #
# ##################################### #

NAME		=	philo

UNAME		=	$(shell uname)

NOCOLOR		=	\033[0m
BGREEN		=	\033[1;32m

HEADER		=	includes/philosophers.h

MAKEFILE	=	Makefile

CFLAGS 		= 	-Wall -Wextra -Werror #-g3 -fsanitize=thread
PFLAGS		=	-pthread

RM 			= 	rm -rf


# ##################################### #
#                 PATHS                 #
# ##################################### #

SRCS_PATH	=	sources/

OBJS_DIRS	=	$(SRCS_PATH).objs/


# ##################################### #
#                SOURCES                #
# ##################################### #

SRC_FILES	=	error.c main.c utils.c routine.c check_death.c actions.c init.c

SRCS	=	$(addprefix $(SRCS_PATH), $(SRC_FILES))


# ##################################### #
#                OBJECTS                #
# ##################################### #

OBJS	=	$(addprefix $(OBJS_DIRS),	\
								$(SRC_FILES:.c=.o))

$(OBJS_DIRS)%.o: $(SRCS_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<


# ##################################### #
#                 RULES                 #
# ##################################### #

all:		$(OBJS_DIRS) $(NAME)

$(OBJS_DIRS):
			mkdir -p $(OBJS_DIRS)

$(NAME):	$(OBJS)
ifeq ($(UNAME),Linux)
	$(CC) $(CFLAGS) $(PFLAGS) -o $(NAME) $(OBJS)
	@echo "$(BGREEN)Linux Compilation Done$(NOCOLOR)"
else ifeq ($(UNAME),Darwin)
	$(CC) $(CFLAGS) $(PFLAGS) -o $(NAME) $(OBJS)
	@echo "$(BGREEN)Mac OS Compilation Done$(NOCOLOR)"
endif

clean:
			$(RM) $(OBJS)
			@echo "$(BGREEN)Clean done$(NOCOLOR)"

fclean:
			$(MAKE) clean
			$(RM) $(NAME)
			$(RM) $(OBJS_DIRS)
			@echo "$(BGREEN)Fclean done$(NOCOLOR)"

re:
			$(MAKE) fclean
			$(MAKE) all

.PHONY:		all clean fclean re