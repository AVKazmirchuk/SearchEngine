# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс MonitorSender
Класс реализует отправку событий другому процессу. Инкапсулирует создание очереди сообщений и отправку сообщений с помощью класса boost::interprocess::message_queue.
### Выполняет следующие функции:
1. Запускает дополнительный процесс для вывода сообщений на консоль.
2. Отправляет сообщение в очередь сообщений для межпроцессного взаимодействия.
### Конструкторы:
Инициализирует: очередь сообщений для отправки сообщений другому процессу
```cpp
MonitorSender() : mq{boost::interprocess::open_or_create, "search_engine", 100, 256} {}
```
Объект является копируемым (неявно) и перемещаемым (неявно).\
Копирование - затратная операция.
### Общедоступные функции-члены:
#### Отправить сообщение в очередь сообщений:
```cpp
void send(const std::string& message);
```
Параметры: сообщение
#### Получить ссылку на объект класса boost::interprocess::message_queue:
```cpp
boost::interprocess::message_queue& get();
```
Возвращаемое значение: ссылка на объект класса boost::interprocess::message_queue
#### Получить константную ссылку на объект класса boost::interprocess::message_queue:
```cpp
const boost::interprocess::message_queue& get() const;
```
Возвращаемое значение: константная ссылка на объект класса boost::interprocess::message_queue
### Примеры
```cpp
#include <iostream>
#include "MonitorSender.h"

int main()
{
    //Создать объект класса MonitorSender
    MonitorSender monitorSender;

    //...
    //Получить сообщение (message)
    //...

    //Отправить сообщение в очередь сообщений
    monitorSender.send(message);
    //Получить ссылку на объект класса boost::interprocess::message_queue
    std::cout << "Всего сообщений в очереди: " << monitorSender.get().get_num_msg()  << std::endl;
}
```

