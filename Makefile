##
## Makefile for Nibbler in /home/hoerte_f/rendu/cpp_nibbler
##
## Made by Francois Hoertel
## Login   <hoerte_f@epitech.net>
##
## Started on  Wed Mar 11 17:36:34 2015 Francois Hoertel
## Last update Sun Apr  5 22:30:23 2015 Francois Hoertel
##

CC	= g++

SRC	= Elems.cpp \
	Exception.cpp \
	Snake.cpp \
	Game.cpp \
	Items.cpp \
	Menu.cpp \
	Main.cpp

SRC_GL	= libGL.cpp \
	Exception.cpp
SRC_SDL = LibSDL.cpp\
	Exception.cpp
SRC_CURSES =	LibCurses.cpp\
	Exception.cpp

OBJS	= $(SRC:.cpp=.o)
OBJS_GL	= $(SRC_GL:.cpp=.o)
OBJS_SDL	= $(SRC_SDL:.cpp=.o)
OBJS_CURSES	= $(SRC_CURSES:.cpp=.o)

LDFLAGS = -ldl
CFLAGS	+= -W -Wall -Wextra -Werror

NAME	= nibbler
NAME_GL	= lib_nibbler_gl.so
NAME_SDL	= lib_nibbler_sdl.so
NAME_CURSES	= lib_nibbler_curses.so

RM	= rm -rf

all	: $(NAME) $(NAME_CURSES) $(NAME_SDL) $(NAME_GL)

$(NAME)	: $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -lSDL -lSDL_image -lSDL_ttf

$(NAME_GL):
	$(CC) $(SRC_GL) -c -fPIC
	$(CC) $(OBJS_GL) -o $(NAME_GL) -shared -lSDL -lGL -lGLU -rdynamic

$(NAME_SDL):
	$(CC) $(SRC_SDL) -c -fPIC
	$(CC) $(OBJS_SDL) -o $(NAME_SDL) -shared -rdynamic -lSDL -lSDL_image -lSDL_ttf

$(NAME_CURSES):
	$(CC) $(SRC_CURSES) -c -fPIC
	$(CC) $(OBJS_CURSES) -o $(NAME_CURSES) -shared -rdynamic -lncurses


clean	:
	$(RM) $(OBJS) $(OBJS_SDL) $(OBJS_CURSES) $(OBJS_GL)
fclean	: clean
	$(RM) $(NAME) $(NAME_SDL) $(NAME_CURSES) $(NAME_GL)

re	: fclean all
