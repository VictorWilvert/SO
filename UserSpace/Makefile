PROJECT=bar
SOURCES_DIR := ./
INCLUDE_DIR := ./
CXXSOURCE=$(shell find $(SOURCES_DIR) -name "*.cc" -type f )
OBJ=$(patsubst %.c, %.o, $(CXXSOURCE))
CXXFLAGS= -c -g -Wall -Wextra -std=c++14 $(addprefix -I, $(INCLUDE_DIR)) 
LIBS=-g

all: $(PROJECT)

$(PROJECT): $(OBJ)
	@g++ -o $@ $^ $(LIBS)

run: $(PROJECT)
	@./$(PROJECT)

%.o: %.c
	@g++ -o $@ $^ $(CXXFLAGS)
	
clean: 
	@-rm -rf *.o $(PROJECT) *~
	@find . -type f -executable -exec rm '{}' \;

remade:
	@$(MAKE) clean
	@$(MAKE)

