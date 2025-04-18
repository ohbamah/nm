# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanchon <ymanchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 16:21:19 by ymanchon          #+#    #+#              #
#    Updated: 2025/03/17 14:05:36 by ymanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################ #
#*    COULEURS    *#
# ################ #

CLASSIC	= \e[0m
BOLD	= \e[1m
BLACK	= \e[30m
RED   	= \e[31m
GREEN  	= \e[32m
BLUE 	= \e[34m
PURPLE 	= \e[35m
CYAN   	= \e[36m
YELLOW 	= \e[93m

# ############### #
#*   VARIABLES   *#
# ############### #

NAME = libft.a

CC =	@cc

AR =  @ar -rcs

SRCS = 	./binary_tree/btree_apply_infix.c \
		./binary_tree/btree_apply_prefix.c \
		./binary_tree/btree_apply_suffix.c \
		./binary_tree/btree_cmp.c \
		./binary_tree/btree_create_node.c \
		./binary_tree/btree_insert_data.c \
		./binary_tree/btree_search_item.c \
		./binary_tree/btree_size.c \
		./binary_tree/btree_strict_size.c \
		\
		./file/ft_swap_fd.c \
		./file/ft_cat.c \
		\
		./ft_maths/ft_abs.c \
		./ft_maths/ft_lerp.c \
		./ft_maths/ft_pow.c \
		\
		./gnl/get_next_line_utils_bonus.c \
		./gnl/get_next_line_bonus.c \
		\
		./lst/ft_lstadd_back_bonus.c \
		./lst/ft_lstadd_front_bonus.c \
		./lst/ft_lstclear_bonus.c \
		./lst/ft_lstdelone_bonus.c \
		./lst/ft_lstiter_bonus.c \
		./lst/ft_lstlast_bonus.c \
		./lst/ft_lstmap_bonus.c \
		./lst/ft_lstnew_bonus.c \
		./lst/ft_lstsize_bonus.c \
		\
		./mem/ft_realloc.c\
		./mem/ft_dfree.c \
		./mem/ft_va_free.c \
		./mem/ft_va_free_exit.c \
		./mem/ft_bzero.c \
		./mem/ft_calloc.c \
		./mem/ft_memchr.c \
		./mem/ft_memcmp.c \
		./mem/ft_memcpy.c \
		./mem/ft_memmove.c \
		./mem/ft_memset.c \
		\
		./parsing/ft_isspace.c \
		./parsing/ft_rev_isspace.c \
		./parsing/ft_rev_isspaceptr.c \
		./parsing/ft_owsequence.c \
		\
		./str/ft_containsanychr.c\
		./str/ft_strisdigits.c \
		./str/ft_chrocc.c \
		./str/ft_strtrunc.c \
		./str/ft_strsjoinstr.c \
		./str/ft_str_add_strs.c \
		./str/ft_lastword.c \
		./str/ft_strnchr.c \
		./str/ft_strsjoin.c \
		./str/ft_strs_insert.c \
		./str/ft_strs_add_at.c \
		./str/ft_strtolower.c \
		./str/ft_strtoupper.c \
		./str/ft_split.c \
		./str/ft_strchr.c \
		./str/ft_strdup.c \
		./str/ft_strdup_at.c \
		./str/ft_strndup.c \
		./str/ft_striteri.c \
		./str/ft_strjoin.c \
		./str/ft_strfjoin.c \
		./str/ft_strlen.c \
		./str/ft_strlen2.c \
		./str/ft_strmapi.c \
		./str/ft_strncmp.c \
		./str/ft_strcmp.c \
		./str/ft_strrchr.c \
		./str/ft_strtrim.c \
		./str/ft_strslcpy.c \
		./str/ft_strlcpy.c \
		./str/ft_strlcat.c \
		./str/ft_strnstr.c \
		./str/ft_strstr.c \
		./str/ft_substr.c \
		./str/ft_strdelete.c \
		./str/ft_strerase.c \
		./str/ft_strinsert.c \
		./str/ft_va_strjoin.c \
		\
		./utils/ft_max.c\
		./utils/ft_count_words.c \
		./utils/ft_intlen.c \
		./utils/ft_convert_base2.c \
		./utils/ft_convert_base.c \
		./utils/ft_swap_addr.c \
		./utils/ft_swap.c \
		\
		./zbasic/ft_atod.c \
		./zbasic/ft_atof.c \
		./zbasic/ft_atoi.c \
		./zbasic/ft_isalnum.c \
		./zbasic/ft_isalpha.c \
		./zbasic/ft_isascii.c \
		./zbasic/ft_isdigit.c \
		./zbasic/ft_isprint.c \
		./zbasic/ft_itoa.c \
		./zbasic/ft_tolower.c \
		./zbasic/ft_toupper.c \
		./zbasic/ft_putchar_fd.c \
		./zbasic/ft_putendl_fd.c \
		./zbasic/ft_putnbr_fd.c \
		./zbasic/ft_putstr_fd.c \

LMAKE = @make --no-print-directory -C

OBJS_DIR =	.objs

OBJS =			$(SRCS:%.c=$(OBJS_DIR)/%.o)

INCLUDES = -I .

OPTIFLAGS =	-O3 -march=native -mtune=generic -funroll-loops -fomit-frame-pointer -ffast-math -fopenmp

CFLAGS =	-Wall -Wextra -Werror -Wno-unused-result $(OPTIFLAGS) -fPIE

PRINTF_P = ./ft_printf

# ############## #
#*    REGLES    *#
# ############## #

#pre_comp
all: check_compilation $(NAME)

$(NAME): $(OBJS)
	$(LMAKE) $(PRINTF_P) re
	$(AR) -o $@ $(PRINTF_P)/.objs/*/*.o
	$(AR) -o $@ $(OBJS)
	@echo "$(BOLD)$(CYAN)Bibliothèque $(NAME) créée avec succès!$(CLASSIC)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "$(GREEN)🗸 Compilation $(BOLD)$(YELLOW)$<$(CLASSIC)"
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

check_compilation:
	@if [ -f $(NAME) ] && \
		[ -n "$(strip $(OBJS))" ] && \
		[ -z "$$(find $(SRCS) -newer $(NAME) 2>/dev/null)" ]; then \
		echo "$(BOLD)$(PURPLE)Tous les fichiers $(UNDERLINE)$(YELLOW)$(NAME)$(CLASSIC)$(BOLD)$(PURPLE) sont déjà compilés !$(CLASSIC)"; \
		exit 0; \
	fi

clean:
	@echo "$(BOLD)$(RED)"
	rm $(OBJS_DIR) -rf
	@echo "$(CLASSIC)"

fclean: clean
	rm $(NAME) -f
	@echo "$(BOLD)$(GREEN)Tout a été supprimé... 🗑️\n$(CLASSIC)"

re: fclean all

.PHONY: all clean fclean re

pre_comp:
	@echo "$(BOLD)"
	@echo "$(PURPLE)"
	@echo "\\t\\t╔────────────────────────────────────────────╗"
	@sleep 0.008
	@echo "\\t\\t│                                            │"
	@sleep 0.008
	@echo "\\t\\t│                                            │"
	@sleep 0.008
	@echo "\\t\\t│    ██╗     ██╗██████╗ ███████╗████████╗    │"
	@sleep 0.008
	@echo "\\t\\t│    ██║     ██║██╔══██╗██╔════╝╚══██╔══╝    │"
	@sleep 0.008
	@echo "\\t\\t│    ██║     ██║██████╔╝█████╗     ██║       │"
	@sleep 0.008
	@echo "\\t\\t│    ██║     ██║██╔══██╗██╔══╝     ██║       │"
	@sleep 0.008
	@echo "\\t\\t│    ███████╗██║██████╔╝██║        ██║       │"
	@sleep 0.008
	@echo "\\t\\t│    ╚══════╝╚═╝╚═════╝ ╚═╝        ╚═╝       │"
	@sleep 0.008
	@echo "\\t\\t│                                            │"
	@sleep 0.008
	@echo "\\t\\t│                                            │"
	@sleep 0.008
	@echo "\\t\\t╚────────────────────────────────────────────╝"
	@sleep 0.008
	@echo "$(CLASSIC)"
