# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gchinaul <gchinaul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 08:51:38 by gchinaul          #+#    #+#              #
#    Updated: 2025/06/21 21:41:19 by gchinaul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

SOURCES := ./source
INCLUDE := ./include
OBJECTS := ./bin

EOC := \033[0m
GREEN := \033[32m
CYAN := \033[36m
YELLOW := \033[33m
RED := \033[31m

SRCS := $(shell find $(SOURCES) -name '*.c')
OBJS := $(patsubst $(SOURCES)/%.c,$(OBJECTS)/%.o,$(SRCS))

UNAME_S := $(shell uname -s)

# Flags communs
CFLAGS := -Wall -Wextra -Werror -g3 -fno-omit-frame-pointer -O1 -I$(INCLUDE)
LDFLAGS :=
LIBS := -lreadline

ifeq ($(UNAME_S),Darwin)
	# macOS Intel (Homebrew readline)
	BREW_PREFIX := /usr/local/opt/readline
	CFLAGS += -I$(BREW_PREFIX)/include
	LDFLAGS += -L$(BREW_PREFIX)/lib
endif

# === Pour activer AddressSanitizer ===
# décommente les lignes suivantes pour le debug mémoire
#CFLAGS += -fsanitize=address -g
#LDFLAGS += -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compilation ${NAME}.$(EOC)"
	@gcc $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $(NAME)

${OBJECTS}/%.o: ${SOURCES}/%.c
	@echo "Compilation $(YELLOW)$(notdir $<)$(EOC)"
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@echo "$(CYAN)Nettoyage des fichiers objets.$(EOC)"
	@rm -rf ${OBJECTS}

fclean: clean
	@echo "$(RED)Suppression de l'exécutable.$(EOC)"
	@rm -f $(NAME)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus
