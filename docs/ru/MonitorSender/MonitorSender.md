# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс MonitorReceiver
Класс реализует получение событий от другого процесса. Инкапсулирует открытие очереди сообщений и получение сообщений с помощью класса boost::interprocess::message_queue.
### Выполняет следующие функции:
1. Получает сообщения из очереди сообщений.
2. Выводит полученные сообщения на консоль.
### Конструкторы:
Инициализирует: очередь сообщений для получения сообщений от другого процесса
```cpp
MonitorReceiver() : mq{boost::interprocess::open_only, "search_engine"} {}
```
Объект является копируемым (неявно) и перемещаемым (неявно).\
Копирование - затратная операция.
### Общедоступные функции-члены:
#### Получить сообщение из очереди сообщений:
```cpp
void receive();
```
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
#include "MonitorReceiver.h"

int main()
{
    //Создать объект класса MonitorReceiver
    MonitorReceiver monitorReceiver;
    
    //Отправить сообщение в очередь сообщений
    monitorReceiver.receive();
    //Получить ссылку на объект класса boost::interprocess::message_queue
    std::cout << "Всего сообщений в очереди: " << monitorReceiver.get().get_num_msg()  << std::endl;
}
```


