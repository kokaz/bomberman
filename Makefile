SRC		=	main.cpp \
			Game.cpp \
			Fault.cpp \
			Graphics.cpp \
			Ia.cpp \
			GameEngine.cpp \
			Map.cpp \
			Menu.cpp \
			PThread.cpp \
			PMutex.cpp \
			PCondVar.cpp \
			ScopeLock.cpp \
			Player.cpp \
			Wall.cpp \
			Box.cpp \
			Bomb.cpp \
			AObject.cpp \
			Cube.cpp \
			ACamera.cpp \
			FreeCam.cpp

MAKEDEPEND	=	-MD
CC			=	g++
FILETYPE		=	.cpp

RM			=	rm -f

NAME			=	bomberman

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	include/
DEPEND		=	.depend

CFLAGS		+=	-I$(INCDIR) -ILibBomberman_linux_x64/includes/
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe

LDFLAGS		+=	-Wl,-O1
LDFLAGS		+=	-lpthread
LDFLAGS		+=	-Wl,-rpath="`pwd`/LibBomberman_linux_x64/libs/"
LDFLAGS		+=	-LLibBomberman_linux_x64/libs/ -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2


OBJ		=	$(patsubst %${FILETYPE},${OBJDIR}%.o, $(SRC))

PRINTFLAGS	=	0

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

-include .depend

$(OBJDIR)%.o:		$(patsubst %${FILETYPE},${SRCDIR}%${FILETYPE}, %${FILETYPE})
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifneq ("$(shell tty)", "not a tty")
			@if [ $(PRINTFLAGS) = "0" ]; then \
			echo -e "Compile flags { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g'; fi
			$(eval PRINTFLAGS = 1)
			@echo -e "Compiling $<" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g'
			@$(CC) $(CFLAGS) $(MAKEDEPEND) -c $< -o $@
else
			$(CC) $(CFLAGS) $(MAKEDEPEND) -c $< -o $@
endif
			sed 's/\\\n/@/' < $(patsubst %.o,%.d, $@) >> $(DEPEND)

$(NAME):	$(OBJ)
ifneq ("$(shell tty)", "not a tty")
		@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
		| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
		@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
else
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
endif

all:	$(NAME)

clean:
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJ)
else
	$(RM) $(OBJ)
endif

fclean:	clean
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing ${NAME} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(NAME)
else
	$(RM) $(NAME)
endif

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, ${NAME}, clean, fclean\033[00m" | sed 's/^-e //'

.PHONY:	all clean fclean re help
