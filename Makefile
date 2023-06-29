# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrulhar <tbrulhar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:06:30 by tbrulhar          #+#    #+#              #
#    Updated: 2023/06/29 16:12:44 by tbrulhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	Source/main.cpp
SRC +=	${addprefix Network/Socket/, ASocket.cpp BindSocket.cpp ConnectSocket.cpp \
ListenSocket.cpp}
SRC +=	${addprefix Network/Server/, AServer.cpp TestServer.cpp}
SRC +=	${addprefix Network/Parsing/RequestInfo/, RequestParsing.cpp GetInfo.cpp}
SRC +=	${addprefix Network/Method/, Utils.cpp}
SRC +=	${addprefix Network/Method/Delete/, DeleteFile.cpp}
SRC +=	${addprefix Network/Method/Post/, FormParsing.cpp GetFormValue.cpp}
SRC +=	${addprefix Network/Method/Get/, OpenFile.cpp}
SRC +=	${addprefix Network/Respons/, CreateRespons.cpp}

OBJ = $(SRC:.cpp=.o) 
GPP = c++
RM = rm -f 
GFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

NAME = webserv

all: $(NAME) 

$(NAME): $(OBJ) 
		$(GPP) $(GFLAGS) -o $(NAME) $(OBJ) 

clean: 
		$(RM) $(OBJ) 

fclean: clean 
		$(RM) $(NAME) 

re: fclean $(NAME) 

.PHONY:        all clean fclean re