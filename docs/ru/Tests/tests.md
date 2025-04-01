# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Тесты
В проекте использована система юнит-тестирования GoogleTest; реализована как отдельный проект, - в репозитории в директории "tests" имеются исходные тесты и необходимые дополнительные файлы конфигурации и запросов, которые модифицированы под используемые тесты. С помощью них тестируются основные классы и функции, а именно: 
- класс InvertedIndex (реализует инвертированную индексацию документов);
- класс RelevantResponse (определяет релевантность ответов);
- свободная функция checkFile (проверяет файлы конфигурации и ответов на существование, на целостность JSON-структуры, на соответствие шаблону);
- класс ConverterJSON (проверяет пути файлов документов и запросы (соответствующие массивы в объектах); создание JSON-объекта ответов).\
  
Также опосредованно тестируется функция чтения JSON-файла.\
Функции чтения текстовых файлов и записи JSON-файлов не тестируются, в виду их тривиальности.\
Тесты можно запустить как по отдельности каждый, так и все сразу.\

В таблицах указано покрытие кода для заголовков и исходных файлов

| Element              | Line Coverage,%    | Branch Coverage,%     | 
|----------------------| -------------------|---------------------- |
| checkFile.h          |                    |                       |   
| checkFileException.h | 88% lines covered  | 20% branches covered  | 
| converterJSON.h      | 100% lines covered | 27% branches covered  |  
| documents.h		       |                    |                       |
| entry.h              | 100% lines covered | 50% branches covered  |
| general.h		         |                    |                       |
| invertedIndex.h      | 100% lines covered | 100% branches covered |
| logger.h		         |                    |                       |
| readTextFile.h	     |                    |                       |
| readWriteJSONFile.h	 |                    |                       |
| relativeIndex.h      | 100% lines covered | 50% branches covered  |
| relevantResponse.h   | 100% lines covered | 50% branches covered  |
| requests.h		       |                    |                       |        
| searchEngine.h	     |                    |                       |


		
		
		

		

		

	

		
		

	

checkFile	100% files, 96% lines covered	57% branches covered
converterJSON	100% files, 76% lines covered	44% branches covered
documents	0% files, 0% lines covered	
general	100% files, 80% lines covered	66% branches covered
invertedIndex	100% files, 92% lines covered	54% branches covered
Logger	100% files, 25% lines covered	100% branches covered
readTextFile	0% files, 0% lines covered	0% branches covered
readWriteJSONFile	100% files, 50% lines covered	20% branches covered
relevantResponse	100% files, 99% lines covered	74% branches covered
requests	0% files, 0% lines covered	
searchEngine	0% files, 0% lines covered	0% branches covered
main.cpp		

