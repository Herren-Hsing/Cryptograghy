CXX = g++                    # 编译器
CXXFLAGS = -std=c++11 -Wall  # 编译标志

SRC = SPN.cpp               # 源代码文件
EXECUTABLE = SPN      # 可执行文件

# 默认目标，编译程序
all: $(EXECUTABLE)

# 编译可执行文件
$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 运行程序并将输入输出重定向到文件
run: $(EXECUTABLE)
	@echo "Running tests..."
	@for i in $$(seq 1 2 $$(wc -l < plain.txt)); do \
		head -n $$(($$i + 1)) plain.txt | tail -n 2 | ./$(EXECUTABLE) >> cipher.txt; \
	done
	@echo "Tests completed."

# 清理生成的文件
clean:
	rm -f $(EXECUTABLE) cipher.txt

.PHONY: all run clean
