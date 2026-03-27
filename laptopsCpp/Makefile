CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = laptop_store
SOURCES = main.cpp baza_noutov.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) laptops.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run