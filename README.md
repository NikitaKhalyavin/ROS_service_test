# ROS_service_test_package
В этом пакете реализованы узлы service_test_server 
и service_test_client, а также тип сообщений ServiceType.

## ServiceType
ServiceType содержит поля запроса firstValue и secindValue, 
в которых содержатся аргументы для математической операции 
(числовые значения с плавающей точкиой, float64),
а также поле action, содержащее саму операцию в виде символа.
Этот тип сервера также содержит поле ответа response для результата 
операции, также типа float64.

## service_test_server
service_test_server реализует сервис service_test. 
Сервис получает на вход сообщение типа ServiceType и выполняет
операцию из поля action для аргументов firstValue и
secondValue. Поддерживаются 4 операции: сложение, вычитание, 
умножение и деление (символы +,-,* и / сответственно).
Результат операции помещается в поле response 
принятого объекта ServerType.

## service_test_client
service_test_client с частотой один раз в секунду генерирует 
валидное сообщение типа ServiceType и отправляет его в сервис
service_test. В случае успешного выполения сервисом операции 
service_test_client выводит в консоль исходные данные запроса, 
а также ответ сервиса. В случает ошибки при вызове сервиса 
service_test_client выводит сообщение об ошибке и завершает работу

