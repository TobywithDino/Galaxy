.PHONY: clean all

CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
PROJECT_NAME = main
# 定義頭文件位置
CXXFLAGS = -I$(INCLUDE_DIR)

# 定義庫文件位置
LDFLAGS = -Llib/SDL2 -Llib/SDL2Image -Llib/SDL2ttf

# 鏈接庫文件
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# 获取所有的源文件列表
CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# 从源文件列表生成目标文件列表	
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES))

# 默认目标：生成PROJECT_NAME文件
all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ_FILES)
	$(CC) -O3 -s $(LDFLAGS) -o $@ $^ $(LDLIBS)

# 模式规则：将每个源文件编译成对应的目标文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	del $(BUILD_DIR)\*.o *.exe
