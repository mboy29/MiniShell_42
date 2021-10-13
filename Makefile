# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 13:56:27 by mboy              #+#    #+#              #
#    Updated: 2021/10/11 17:13:50 by alabalet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

RED		= 	\033[1;31m

CFLAGS	=	-Wall -Werror -Wextra -I ./Includes -I ~/.brew/opt/readline/include -g

SDIR	=	Sources

SRCS_C	=	builtin.c\
			builtin_cd.c\
			builtin_echo.c\
			builtin_env.c\
			builtin_exit.c\
			builtin_export1.c\
			builtin_export2.c\
			builtin_pwd.c\
			builtin_unset.c\
			error.c\
			exec.c\
			exec2.c\
			expanser.c\
			free.c\
			lexer.c\
			main.c\
			parser.c\
			parser2.c\
			redir.c\
			signal.c\
			syntax.c\
			tokenize.c\
			utils.c

SRCS	=	$(patsubst %, $(SDIR)/%, $(SRCS_C))

ODIR	=	.objs
OBJS_O	=	$(SRCS_C:.c=.o)
OBJS	=	$(patsubst %, $(ODIR)/%, $(OBJS_O))

LDIR 	=	./Libft
LIBFT 	=	Libft/libft.a

all: $(NAME)

$(NAME): .objs $(OBJS)
	make -C $(LDIR)
	gcc $(CFLAGS) -lreadline -L ~/.brew/opt/readline/lib $(LIBFT) $(OBJS) -o $@
	@echo "$(RED)      ___                       ___                       ___           ___           ___                                      "
	@echo "$(RED)     /__/\        ___          /__/\        ___          /  /\         /__/\         /  /\      ___             ___            "
	@echo "$(RED)    |  |::\      /  /\         \  \:\      /  /\        /  /:/_        \  \:\       /  /:/_    /__/\           /__/\           "
	@echo "$(RED)    |  |:|:\    /  /:/          \  \:\    /  /:/       /  /:/ /\        \__\:\     /  /:/ /\   \  \:\     ___  \  \:\     ___  "
	@echo "$(RED)  __|__|:|\:\  /__/::\      _____\__\:\  /__/::\      /  /:/ /::\   ___ /  /::\   /  /:/ /:/_   \  \:\   /  /\  \  \:\   /  /\ "
	@echo "$(RED) /__/::::| \:\ \__\/\:\__  /__/::::::::\ \__\/\:\__  /__/:/ /:/\:\ /__/\  /:/\:\ /__/:/ /:/ /\   \  \:\ /  /:/   \  \:\ /  /:/ "
	@echo "$(RED) \  \:\~~\__\/    \  \:\/\ \  \:\~~\~~\/    \  \:\/\ \  \:\/:/~/:/ \  \:\/:/__\/ \  \:\/:/ /:/    \  \:\  /:/     \  \:\  /:/  "
	@echo "$(RED)  \  \:\           \__\::/  \  \:\  ~~~      \__\::/  \  \::/ /:/   \  \::/       \  \::/ /:/      \  \:\/:/       \  \:\/:/   "
	@echo "$(RED)   \  \:\          /__/:/    \  \:\          /__/:/    \__\/ /:/     \  \:\        \  \:\/:/        \  \::/         \  \::/    "
	@echo "$(RED)    \  \:\         \__\/      \  \:\         \__\/       /__/:/       \  \:\        \  \::/          \__\/           \__\/     "
	@echo "$(RED)     \__\/                     \__\/                     \__\/         \__\/         \__\/                                     "
	@echo "$(RED)						Successful compilation of $(NAME)"

.objs:
	mkdir .objs

$(ODIR)/%.o: $(SDIR)/%.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	make -C $(LDIR) clean
	rm -f $(OBJS)
	rm -rf .objs

fclean: clean
	make -C $(LDIR) fclean
	rm -f $(NAME)

re: fclean all
