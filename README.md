# TP prefork server
Запуск prefork сервера:

```
cd prefork_server
sudo docker build -t prefork .
sudo docker run -p 80:80 --name prefork -t prefork
```
Запуск nginx:
```
cd nginx
sudo docker build -t nginxserver .
sudo docker run -p 80:80 --name nginxserver -t nginxserver
```
Запуск функционального тестирования:
```
./httptest.py
```
## Нагрузочное тестирование
