CC = gcc

CFLAGS = -march=native -O2 -Wall -Wextra -Wno-unused-parameter \
				 -isystem include -g3
LDFLAGS = -lglfw \
					-lGL \
					-ldl \
					-lm

TARGET = Simulator
GLAD_FILES = src/glad/gl.c

CSOURCES = $(shell find src -name '*.c') $(GLAD_FILES)
SOURCES = $(CSOURCES)

OBJECTS = $(patsubst src/%,build/%.o,$(CSOURCES))

.PHONY: all clean $(TARGET)

all: $(TARGET)


$(TARGET): $(OBJECTS)
	@echo "(LD) ... => $(notdir $@)"
	$(CC) $(LDFLAGS) -o $@ $^

build/%.c.o: src/%.c | $(GLAD_FILES)
	@mkdir -p $(dir $@)
	@echo "(CC) $(notdir $<) => $(notdir $@)"
	$(CC) $(CFLAGS) -o $@ -c $<

$(GLAD_FILES):
	@echo "(GL) Generating GLAD files ($@)"
	@glad --api gl:core=4.3 --out-path ./tmp c
	@mkdir -p ./src/glad/ ./include/glad/
	@mv ./tmp/include/* ./include/
	@mv ./tmp/src/gl.c $@
	@rm -rf ./tmp
	@echo "(GL) Generated GLAD files ($@)"

clean:
	@rm -rf build $(TARGET)

