# ======================================================= #
#                                                         #
#                      Definitions                        #
#                                                         #
# ======================================================= #

CC 	   	= 	g++
CFLAGS 	= 	-Wall -O2
TARGET 	= 	binaryDT

SRC_DIR = 	./src
OBJ_DIR = 	./obj

SRC 	= 	${wildcard $(SRC_DIR)/*.cpp}
OBJ 	= 	${patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC)}
LIB 	= 	-lpthread -lm

# ======================================================= #
#                                                         #
#                      Commands                           #
#                                                         #
# ======================================================= #

.PHONY: all clean 

all: clean init $(TARGET)

init:
	if [ ! -d "obj" ]; then mkdir obj; fi

clean:
	rm -rf obj
	if [ -f $(TARGET) ]; then rm $(TARGET); fi

test:
	

$(TARGET) 		: 	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $? $(LIB)

${OBJ_DIR}/%.o	:	${SRC_DIR}/%.cpp
	$(CC) -c $< -o $@