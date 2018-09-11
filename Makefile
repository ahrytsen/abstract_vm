#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/26 17:26:54 by ahrytsen          #+#    #+#              #
#    Updated: 2018/09/11 15:56:30 by ahrytsen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	avm
DIRSRC		=	./src/
DIROBJ		=	./obj/
INCLUDE		=	-I./inc/
INC_LIB		=

SRC			=	main.cpp\
				OFactory.cpp

HDRS		=	inc/IOperand.hpp\
				inc/TOperand.hpp\
				inc/OFactory.hpp

OBJ			=	$(addprefix $(DIROBJ), $(SRC:.cpp=.o))

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror -Wc++11-extensions -Wc++14-extensions
endif

CC			=	clang++
RM			=	rm -rf
ECHO		=	echo

all		:		$(NAME)

$(NAME)	:		$(DIROBJ) $(OBJ)
				@$(CC) $(INCLUDE) $(INC_LIB) $(CFLAGS) -o $(NAME) $(OBJ)
				@$(ECHO) "\033[31m> \033[32m"$(NAME)": Compiled\033[0m"

clean	:
				@($(RM) $(DIROBJ))
				@$(ECHO) "\033[31m> \033[33m"$(NAME)": Directory cleaned\033[0m"

fclean	:		clean
				-@$(RM) $(NAME)
				@$(ECHO) "\033[31m> \033[33m"$(NAME)": Executable removed\033[0m"

re		:		fclean all

.PHONY	:		all clean re

$(DIROBJ):
				@mkdir -p $(DIROBJ)

$(OBJ)	:		$(DIROBJ)%.o : $(DIRSRC)%.cpp $(HDRS)
				@$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $<
