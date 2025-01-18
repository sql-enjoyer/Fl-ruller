# Имя исполняемого файла
TARGET = a.out

# Исходный файл
SRC = main.cxx

# Компилятор и флаги
CXX = g++
CXXFLAGS = -lfltk -lfltk_images

# Правило по умолчанию
all: $(TARGET) run

# Сборка исполняемого файла
$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)

# Запуск программы
run:
	./$(TARGET)

# Очистка сгенерированных файлов
clean:
	rm -f $(TARGET)
