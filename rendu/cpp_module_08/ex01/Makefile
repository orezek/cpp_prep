# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 10:59:06 by mbartos           #+#    #+#              #
#    Updated: 2024/07/30 13:18:33 by mbartos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

#name
NAME =		span

#compiler
CCP =		c++
# CFLAGS =	-Wall -Wextra -Werror
CFLAGS =	-g -Wall -Wextra -Werror -std=c++98

#sources
SRC =	main.cpp Span.cpp

#objects
OBJ_PATH =	obj/
OBJ =		$(SRC:.cpp=.o)
OBJS =		$(addprefix $(OBJ_PATH), $(OBJ))

# dependency files
DEPS =      $(OBJ:.o=.d)
DEP_PATH =  $(OBJ_PATH)

all: $(NAME)

$(OBJ_PATH)%.o : %.cpp | $(OBJ_PATH)
	$(CCP) $(CFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(OBJS:.o=.d)

# $(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	$(CCP) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(GREEN)[ Program $(NAME) ready! ]$(NC)"

clean:
	@rm -Rf $(OBJ_PATH)
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

re: fclean all

.PHONY: all, re, clean, fclean