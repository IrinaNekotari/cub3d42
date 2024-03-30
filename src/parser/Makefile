NAME 	= parser
AUTHOR	= nmascrier
FLAG	= -Wall -Wextra -Werror

SRC	= color.c checks.c parser.c utils.c main.c

OBJ  = $(SRC:c=o)

#Flags pour les nettoyages
CLEANCMD = rm -rf *o
FCLEANCMD = rm -f *.a parser

#Cree la lib, et garde les fichiers .o generes
all:$(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@cc $(FLAG) -o $(NAME) $(OBJ) -Iinclude -Llibft -lft -g

#compile un unique fichier .c en .o
%.o: %.c
	@printf "\033[0;33mCompilation de %-33.33s\r" $@
	@cc $(FLAG) -c $< -o $@ -Iinclude

clean:
	$(CLEANCMD)
	@echo "\e[91m\e[1m"
	$(MAKE) clean -C libft
	@echo "\e[91m\e[1mFichiers .o nettoyes\n"

fclean: clean
	@echo "\e[91m\e[1m"
	$(FCLEANCMD)
	$(MAKE) fclean -C libft
	@echo "\e[91m\e[1mFichiers crees nettoyes\n"

re: fclean all

.PHONY: all clean fclean re