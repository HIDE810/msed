TARGET	:=	msed
LIBS	:=	-lcrypto
SRC		:=	$(wildcard src/*.cpp)

ifeq ($(OS),Windows_NT)
	EXT = exe
else
	EXT = out
endif

all:
	@$(CXX) $(SRC) $(LIBS) -o $(TARGET).$(EXT)

clean:
	@$(RM) $(TARGET).$(EXT)