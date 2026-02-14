# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Тесты
В проекте использована система юнит-тестирования GoogleTest; в репозитории в директории "tests" имеются исходные тесты и необходимые дополнительные файлы конфигурации и запросов, которые модифицированы под используемые тесты.\ 
Протестирована обязательная проверка на недоступность файлов конфигурации и файлов документов, заявленная функциональность, а также наиболее сложные функции библиотек и основной программы.\
  
### kav_fileOperations_test

| Element              | Line Coverage,%               | Branch Coverage,%     | 
|----------------------| ------------------------------|---------------------- |
| src                  | 100% files, 100% lines covered| 70% branches covered  |   
| tests                | 80% files, 89% lines covered  | 46% branches covered  | 

### kav_logger_test
		
| Element              | Line Coverage,%               | Branch Coverage,%     | 
|----------------------| ------------------------------|---------------------- |
| include              | 100% files, 95% lines covered | 54% branches covered  |   
| src                  | 100% files, 83% lines covered | 53% branches covered  |   
| tests                | 85% files, 91% lines covered  | 49% branches covered  |   
		
### logger_monitor_test		
		
| Element              | Line Coverage,%               | Branch Coverage,%     | 
|----------------------| ------------------------------|---------------------- |
| include              | 100% files, 76% lines covered | 44% branches covered  |   
| src                  | 100% files, 84% lines covered | 57% branches covered  |   
| tests                | 100% files, 95% lines covered | 54% branches covered  |  		
		
Также, для тестирования записи сообщений на консоль, необходимо запустить файл теста вручную, так как тест читает из консоли записанные сообщения, что невозможно из встроенной консоли IDE.

### search_engine_test
		
| Element              | Line Coverage,%               | Branch Coverage,%     | 
|----------------------| ------------------------------|---------------------- |
| include              | 100% files, 100% lines covered| 31% branches covered  |   
| src                  | 100% files, 89% lines covered | 60% branches covered  |   
| tests                | 100% files, 84% lines covered | 50% branches covered  |  			
		
		
		
		

