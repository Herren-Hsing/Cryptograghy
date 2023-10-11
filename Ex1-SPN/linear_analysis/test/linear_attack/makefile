CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = linear_attack
INPUT_FILE = input.txt
OUTPUT_FILE = output.txt

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

run: $(TARGET)
	./$(TARGET) < $(INPUT_FILE) > $(OUTPUT_FILE)

clean:
	rm -f $(TARGET) $(OUTPUT_FILE)
