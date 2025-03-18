# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс CheckFileException
Класс реализует генерацию исключений.\
Также используется вспомогательный класс перечисления ErrorCode (содержит коды исключений).
### Выполняет следующие функции:
1. Создаёт исключение.
2. Возвращает информацию по исключению.
3. Возвращает код исключения.
### Конструкторы:
Инициализирует код исключения.
```cpp
CheckFileException(ErrorCode in_errorCode, const std::string& in_information = "")
: errorCode(in_errorCode)
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Получить информацию по исключению:
```cpp
const char* what() const noexcept override;
```
Возвращаемое значение: информация по исключению
#### Получить код исключения:
```cpp
ErrorCode getErrorCode() const;
```
Возвращаемое значение: код исключения
### Примеры
```cpp
#include "сheckFileException.h"

int main()
{
    //...
    //Получить путь файла (filePath)
    //...

    //Выбросить исключение с указанными ошибкой и путём файла
    throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath);
    
    //...
    //Получить объект класса CheckFileException (checkFileExceptionObj)
    //...

    //Получить код исключения
    ErrorCode errorCode{checkFileExceptionObj.getErrorCode()};

    //...
    //Что-то делать с errorCode
    //...
}
```

