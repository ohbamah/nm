# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2025/03/18 18:24:47 by ymanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	= \e[0m
WHITE	= \e[38;2;238;232;213m
BOLD	= \e[1m
# BLACK	= \e[38;2;0;0;0m
BLACK	= \e[30m
RED   	= \e[31m
GREEN  	= \e[32m
BLUE 	= \e[38;2;0;36;148m
PURPLE 	= \e[38;2;211;54;130m
CYAN   	= \e[36m
YELLOW 	= \e[38;2;250;189;0m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = ft_nm

CC = @cc

LMAKE = @make $(1) --no-print-directory -C $(2)

SRCS =	./ft_nm.c \
		./cmp_funs.c

OBJS_DIR = .objs

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.obj)

DEPS = $(OBJS:%.obj=%.d)

CFLAGS = -Wall -Wextra -Wno-unused-result -MMD -g3

INCLUDES = -I. -I$(LIBFT_P)includes/ -I$(IELFT_P)includes/ -I$(HOPT_P)

# ############### #
#*      LIB      *#
# ############### #

ELFT_P = ./elft/
ELFTNAME = $(ELFT_P)libelft.a
LIBFT_P = ./libft/
LIBFTNAME = $(LIBFT_P)libft.a
HOPT_P = ./hopt/
HOPTNAME = $(HOPT_P)libhopt.a

LIB = -L$(LIBFT_P) -lft -L$(ELFT_P) -lelft -L$(HOPT_P) -lhopt

# ############## #
#*    REGLES    *#
# ############## #

all: lib check_compilation $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $@
	@echo "$(BOLD)$(CYAN)Exécutable $(NAME) créé avec succès!$(CLASSIC)"

$(OBJS_DIR)/%.obj: %.c
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

check_compilation:
	@if [ -f $(NAME) ] && \
		[ -n "$(strip $(OBJS))" ] && \
		[ -z "$$(find $(SRCS) -newer $(NAME) 2>/dev/null)" ] && \
		[ ! $(ELFTNAME) -nt $(NAME) ] && \
		[ ! $(HOPTNAME) -nt $(NAME) ] && \
		[ ! $(LIBFTNAME) -nt $(NAME) ]; then \
		echo "$(BOLD)$(PURPLE)Tous les fichiers $(UNDERLINE)$(YELLOW)$(NAME)$(CLASSIC)$(BOLD)$(PURPLE) sont déjà compilés !$(CLASSIC)"; \
		exit 0; \
	fi

clean:
	@echo "$(BOLD)$(RED)"
	rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	@echo "$(BOLD)$(RED)"
	rm $(LIBFTNAME) -f
	rm $(ELFTNAME) -f
	rm $(LIBFT_P).objs/ -rf
	rm $(LIBFT_P)ft_printf/.objs/ -rf
	rm $(ELFT_P).objs/ -rf
	rm $(NAME) -f
	@echo "$(BOLD)$(GREEN)Tout a été supprimé... 🗑️\n$(CLASSIC)"

re: lib_re clean all

lib_re:
	$(call LMAKE, re, $(LIBFT_P))
	$(call LMAKE, re, $(ELFT_P))

lib:
	$(call LMAKE, , $(LIBFT_P))
	$(call LMAKE, , $(ELFT_P))

.PHONY: check_compilation all clean fclean re lib_re lib
-include $(DEPS)
