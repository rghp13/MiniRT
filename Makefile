define HEADER

███╗   ███╗██╗███╗   ██╗██╗    ██████╗ ████████╗
████╗ ████║██║████╗  ██║██║    ██╔══██╗╚══██╔══╝
██╔████╔██║██║██╔██╗ ██║██║    ██████╔╝   ██║   
██║╚██╔╝██║██║██║╚██╗██║██║    ██╔══██╗   ██║   
██║ ╚═╝ ██║██║██║ ╚████║██║    ██║  ██║   ██║   
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝    ╚═╝  ╚═╝   ╚═╝   
                                                
endef
export HEADER

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[32m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m
CYAN = \033[36m

PATH_SRC				=		./srcs
PATH_HEAD				=		./includes
PATH_LIB				=		./libft
SRC_NAME				=		main.c

NAME					=		minirt
OBJ_NAME				=		$(SRC_NAME:.c=.o)
CC						=		clang
RM						=		rm -f
CFLAG					=		-Wall -Wextra -Werror -g #-fsanitize=address
SRC						=		$(addprefix $(PATH_SRC)/,$(SRC_NAME))
OBJ						=		$(addprefix $(PATH_SRC)/,$(OBJ_NAME))
LIBFT_A					=		libft.a
.c.o:
								@${CC} ${CFLAG} -I${PATH_HEAD} -c $< -o ${<:.c=.o}
								@printf "${GREEN}[ OK ] ${<:.s=.o}${NC}                \r"
${NAME}:						${OBJ}
								@printf "${GREEN}[DONE]\n"
								@make --no-print-directory -C ${PATH_LIB} 
								@${CC} $^ -o $@ ${CFLAG} ${PATH_LIB}/${LIBFT_A} -lreadline
								@printf "${CYAN}[COMPILATION COMPLETE]${NC}\n"
								@printf "${PURPLE}$$HEADER${NC}\n"
all:							${NAME}

clean:
								@${RM} ${OBJ}
								@make --no-print-directory -C ${PATH_LIB} clean
								@printf "\n${GREEN}[ OK ]${NC}${RED} *.o files DELETED${NC}\n"
fclean:							clean
								@${RM} ${NAME}
								@make --no-print-directory -C ${PATH_LIB} fclean
								@printf "${GREEN}[ OK ]${NC}${RED} ${NAME} DELETED${NC}\n"
re:								fclean ${NAME}
.PHONY:							all clean fclean re