# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/03 15:18:41 by fgalaup           #+#    #+#              #
#    Updated: 2021/08/25 15:42:40 by seruiz           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= ircserv


# Dirrectory 

BINARY_DIR		:= Bin
SOURCES_DIR		:= Sources
INCLUDES_DIR	:= Includes



CC		:= clang++
RM		:= rm -f
CFLAGS	:= -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined

INCLUDES		:= -I $(INCLUDES_DIR) -g3

HEADERS_FILES	:=	IRC.hpp \
					Core/Core.hpp \
					Core/Logging.hpp \
					Core/ConnectionManager.hpp \
					Resources/Chanel.hpp \
					Resources/Client.hpp \
					Resources/Message.hpp \
					Resources/Request.hpp \
					Resources/Responce.hpp \
					Utilites/Networks/Socket.hpp \
					Utilites/Networks/Connection.hpp 

SOURCE_FILES	:=	Core/Core.cpp \
					Core/Logging.cpp \
					Core/ConnectionManager.cpp \
					Resources/Commands.cpp \
					Resources/Chanel.cpp \
					Resources/Client.cpp \
					Resources/Message.cpp \
					Resources/Request.cpp \
					Resources/Responce.cpp \
					Utilities/Networks/Socket.cpp \
					Utilities/Networks/Connection.cpp \
					Commands/NICK.cpp \
					Commands/OPER.cpp \
					Commands/PING.cpp \
					Commands/USER.cpp


OBJS			:= $(addprefix $(BINARY_DIR)/, $(SOURCE_FILES:.cpp=.o))
HEADERS_FILES	:= $(addprefix $(INCLUDES_DIR)/, $(HEADERS_FILES))

LIBRARIES	= -lpthread

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS_FILES)
			$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME) $(LIBRARIES)

$(BINARY_DIR)/%.o:	$(SOURCES_DIR)/%.cpp  $(HEADERS_FILES)
			@mkdir -p $(dir $@);
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -O3

clean:
			$(RM) $(OBJS)
			find . -type d -empty -delete

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
