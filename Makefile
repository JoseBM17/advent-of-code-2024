CC = gcc 							# Compiler
CFLAGS = -Wall -g -I$(INCLUDE_DIR)	# Compiler flags: Warnings, debug info, and include directory
LDFLAGS = 							# Linker flags

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Day-specific source files (with main)
DAY_SRCS = $(wildcard $(SRC_DIR)/day_*/day_*.c)

# Utility and shared source files (without main)
UTILS_SRC = $(SRC_DIR)/utils.c
LOCATION_SRC = $(SRC_DIR)/day_01/location.c

# Object files
DAY_OBJS = $(DAY_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
UTILS_OBJ = $(UTILS_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LOCATION_OBJ = $(LOCATION_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executables for day-specific programs
DAY_EXES = $(DAY_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%)

# Default target: Build all executables
all: $(DAY_EXES)

# Rule to build individual day executables
$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(UTILS_OBJ) $(LOCATION_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run a specific day
run:
	@if [ -z "$(DAY)" ]; then \
		echo "Usage: make run DAY=day_XX"; \
	else \
		if [ -f $(BUILD_DIR)/$(DAY)/$(DAY) ]; then \
			echo "Running $(DAY):"; \
			./$(BUILD_DIR)/$(DAY)/$(DAY); \
		else \
			echo "Executable for $(DAY) not found. Did you compile it?"; \
		fi \
	fi

# Run all days
run-all: all
	@for exe in $(DAY_EXES); do \
		echo "Running $$exe:"; \
		./$$exe || exit 1; \
	done

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Automatic dependency generation
DEP = $(DAY_OBJS:.o=.d) $(UTILS_OBJ:.o=.d) $(LOCATION_OBJ:.o=.d)

-include $(DEP)

%.d: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	@$(CC) -MM $(CFLAGS) $< | sed 's,\($(notdir $*)\.o\), $(dir $@)\1,g' > $@
