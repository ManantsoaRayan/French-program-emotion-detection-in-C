CC = gcc
EXEC = feeling

SRCS = main.c input.c analyzer.c

build: $(SRCS)
	@echo "Compiling..."
	@$(CC) -Iheaders -o $(EXEC) $(SRCS)
	@echo "Build complete."

run: build
	@echo "Running..."
	@./$(EXEC)
