.PHONY: all build clean run

# 默认目标
all: build

# 可执行文件名称
TARGET = dlmu-dog

# 如果 build 文件夹存在，则执行 make；否则执行 rebuild
build:
	@if [ -d "build" ]; then \
		cd build && make; \
	else \
		mkdir -p build; \
		cd build && cmake .. && make; \
	fi

# 清理 build 文件夹
clean:
	rm -rf build

# # 重新构建：清理并重新创建 build 文件夹，然后执行 make
# rebuild:
# 	rm -rf build
	

# 运行程序（假设生成的可执行文件在 build 目录下）
run:
	@if [ -d "build" ]; then \
		cd build && make && ./$(TARGET); \
	else \
		echo "Build directory does not exist. Run 'make build' first."; \
		$(MAKE) build; \
		cd build && make &&./$(TARGET); \
	fi
