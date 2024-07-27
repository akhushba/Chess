CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = chess

SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep

SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)
DEPS = $(SRCS:$(SRC_DIR)/%.cc=$(DEP_DIR)/%.d)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -lX11 -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(DEP_DIR):
	mkdir -p $@

-include $(DEPS)

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(DEP_DIR)/*.d $(EXEC)
