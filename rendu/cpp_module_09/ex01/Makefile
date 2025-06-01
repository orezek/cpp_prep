# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:59:06 by mbartos           #+#    #+#              #
#    Updated: 2024/08/12 11:55:23 by mbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

#name
NAME =		RPN

#compiler
CCP =		c++
CFLAGS =	-Wall -Wextra -Werror -std=c++98

#sources
SRC =	main.cpp RPN.cpp

#objects
OBJ_PATH =	obj/
OBJ =		$(SRC:.cpp=.o)
OBJS =		$(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o : %.cpp
	$(CCP) $(CFLAGS) -c $< -o $@

$(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	$(CCP) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(BOLD)$(GREEN)[ Program $(NAME) ready! ]$(NC)"

clean:
	@rm -Rf $(OBJ_PATH)
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

re: fclean all

.PHONY: all, re, clean, fclean