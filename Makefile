NAME	= zombie.exe
INC		= includes/

SFML_INC	= D:/CPP-LIBS/SFML-2.5.1/include
SFML_LIB	= D:/CPP-LIBS/SFML-2.5.1/lib
SFML_LINK	= -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCD		= src/
SRC     	= $(wildcard $(SRCD)*.cpp)
OBJ			= $(SRC:.cpp=.o)

CXX			= g++
CXX_FLAG	= -std=c++17 -I$(INC) -I$(SFML_INC)

all: $(NAME)

%.o: %.cpp
	$(CXX) $(CXX_FLAG) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(SFML_LINK)

clean:
	-@cmd /C del /Q /F src\*.o 2>nul

fclean: clean
	-@cmd /C del /Q /F $(NAME) 2>nul

re: fclean all

.PHONY: all clean fclean re
