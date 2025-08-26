# Парсер аргументов командной строки

## Описание

Реализация библиотеки для парсинга аргументов командной строки на C++. Поддерживает обработку целочисленных, строковых и булевых аргументов, включая флаги, multi-value аргументы и позиционные параметры.

## Особенности

- Поддержка коротких (`-f`) и длинных (`--flag`) имен аргументов
- Аргументы со значениями (`--param=value`)
- Флаги (без значений)
- Multi-value аргументы (несколько значений для одного параметра)
- Позиционные аргументы
- Значения по умолчанию
- Валидация минимального количества аргументов
- Генерация help-сообщений
- Сохранение значений в переменные

## Использование

### Пример программы

```cpp
#include <lib/ArgParser.h>
#include <iostream>
#include <numeric>

struct Options {
    bool sum = false;
    bool mult = false;
};

int main(int argc, char** argv) {
    Options opt;
    std::vector<int> values;

    ArgumentParser::ArgParser parser("Program");
    parser.AddIntArgument("N").MultiValue(1).Positional().StoreValues(values);
    parser.AddFlag("sum", "add args").StoreValue(opt.sum);
    parser.AddFlag("mult", "multiply args").StoreValue(opt.mult);
    parser.AddHelp('h', "help", "Program accumulate arguments");

    if(!parser.Parse(argc, argv)) {
        std::cout << "Wrong argument" << std::endl;
        std::cout << parser.HelpDescription() << std::endl;
        return 1;
    }

    if(parser.Help()) {
        std::cout << parser.HelpDescription() << std::endl;
        return 0;
    }

    if(opt.sum) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 0) << std::endl;
    } else if(opt.mult) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 1, std::multiplies<int>()) << std::endl;
    } else {
        std::cout << "No one options had chosen" << std::endl;
        std::cout << parser.HelpDescription();
        return 1;
    }

    return 0;
}
```

### Запуск примеров

Сложение чисел:
```bash
./labwork4 --sum 1 2 3 4 5
```

Умножение чисел:
```bash
./labwork4 --mult 1 2 3 4 5
```

## API

### Добавление аргументов

```cpp
// Строковые аргументы
AddStringArgument(char short_name, const char* long_name, const char* help)
AddStringArgument(const char* long_name, const char* help)

// Целочисленные аргументы  
AddIntArgument(char short_name, const char* long_name, const char* help)
AddIntArgument(const char* long_name, const char* help)

// Флаги
AddFlag(char short_name, const char* long_name, const char* help)
AddFlag(const char* long_name, const char* help)
```

### Методы аргументов

- `.Default(value)` - установка значения по умолчанию
- `.MultiValue(min_count)` - разрешение multiple values
- `.Positional()` - пометка как позиционный аргумент
- `.StoreValue(var)` - сохранение значения в переменную
- `.StoreValues(vector)` - сохранение значений в вектор

### Парсинг и получение значений

```cpp
bool Parse(int argc, char** argv)
bool Parse(const std::vector<std::string>& args)

// Получение значений
GetStringValue(name)
GetIntValue(name) 
GetFlag(name)

// Работа со help
AddHelp(short_name, long_name, description)
HelpDescription()
Help()
```

## Тестирование

Тесты используют Google Test framework и находятся в `tests/argparser_test.cpp`. Для запуска тестов:

```bash
make test
```

## Структура проекта

```
├── lib/           # Исходный код библиотеки
│   ├── ArgParser.h
│   ├── ArgParser.cpp  
│   ├── Argument.h
│   └── CMakeLists.txt
├── tests/         # Тесты
│   └── argparser_test.cpp
├── bin/           # Пример использования
│   └── main.cpp
└── CMakeLists.txt # Основной CMake файл
```

## Требования

- C++17 или новее
- CMake 3.10+
- Google Test (для тестов)