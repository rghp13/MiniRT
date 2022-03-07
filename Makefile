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

SRC_NAME				=		main.c \
								parse.c \
								parse_utils.c \
								parse_utils2.c \
								parse_utils3.c \
								parse_ambient.c \
								parse_camera.c \
								parse_cone.c \
								parse_cylinder.c \
								parse_light.c \
								parse_plane.c \
								parse_sphere.c \
								parse_light.c \
								parse_plane.c \
								parse_sphere.c \
								tracing.c \
								draw_functions.c \
								position_functions.c \
								rotation_functions.c \
								color_functions.c \
								keyboard.c \
								simple_vector_math.c \
								advanced_vector_math.c \
								sphere_functions.c \
								plane_functions.c \
								cylinder_functions.c \
								free.c \
								free2.c

NAME					=		minirt
OBJ_NAME				=		$(SRC_NAME:.c=.o)
CC						=		clang
RM						=		rm -f
CFLAG					=		-g #-Wall -Wextra -Werror
SRC						=		$(addprefix $(PATH_SRC)/,$(SRC_NAME))
OBJ						=		$(addprefix $(PATH_SRC)/,$(OBJ_NAME))
LIBFT_A					=		libft.a
LIBX_FD					=		./minilibx-linux
LDLIBS					=		-lm -lXext -lX11
.c.o:
								@${CC} ${CFLAG} -I${PATH_HEAD} -c $< -o ${<:.c=.o}
								@printf "${GREEN}[ OK ] ${<:.s=.o}${NC}                \r"
${NAME}:						${OBJ}
								@printf "${GREEN}[DONE]\n"
								@make --no-print-directory -C ${PATH_LIB}
								@make --no-print-directory -C ${LIBX_FD}
								@${CC} $^ -o $@ ${CFLAG} ${PATH_LIB}/${LIBFT_A} ${LIBX_FD}/libmlx.a ${LDLIBS}
								@printf "${CYAN}[COMPILATION COMPLETE]${NC}\n"
								@printf "${GREEN}$$HEADER${NC}\n"
all:							${NAME}

clean:
								@${RM} ${OBJ}
								@make --no-print-directory -C ${PATH_LIB} clean
								@make --no-print-directory -C ${LIBX_FD} clean
								@printf "\n${GREEN}[ OK ]${NC}${RED} *.o files DELETED${NC}\n"
fclean:							clean
								@${RM} ${NAME}
								@make --no-print-directory -C ${PATH_LIB} fclean
								@printf "${GREEN}[ OK ]${NC}${RED} ${NAME} DELETED${NC}\n"
re:								fclean ${NAME}
.PHONY:							all clean fclean re