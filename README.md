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
# Нагрузочное тестирование
## baton
Параметры теста:
```
baton -u http://localhost/httptest/wikipedia_russia.html -c 8 -r 100000
```
### prefork server
```
=========================== Results ========================================

Total requests:                                100000
Time taken to complete requests:        24.607942684s
Requests per second:                             4064
Max response time (ms):                            17
Min response time (ms):                             0
Avg response time (ms):                          1.46

========= Percentage of responses by status code ==========================

Number of connection errors:                        0
Number of 1xx responses:                            0
Number of 2xx responses:                       100000
Number of 3xx responses:                            0
Number of 4xx responses:                            0
Number of 5xx responses:                            0

========= Percentage of responses received within a certain time (ms)======

        66% : 1 ms
        93% : 2 ms
        96% : 3 ms
        97% : 4 ms
        98% : 5 ms
        99% : 6 ms
        99% : 7 ms
        99% : 8 ms
        99% : 9 ms
       100% : 17 ms

===========================================================================

```
### nginx
```
=========================== Results ========================================

Total requests:                                100000
Time taken to complete requests:        13.163869292s
Requests per second:                             7597
Max response time (ms):                            14
Min response time (ms):                             0
Avg response time (ms):                          0.51

========= Percentage of responses by status code ==========================

Number of connection errors:                        0
Number of 1xx responses:                            0
Number of 2xx responses:                       100000
Number of 3xx responses:                            0
Number of 4xx responses:                            0
Number of 5xx responses:                            0

========= Percentage of responses received within a certain time (ms)======

        95% : 1 ms
        98% : 2 ms
        99% : 3 ms
        99% : 4 ms
        99% : 5 ms
        99% : 6 ms
        99% : 7 ms
        99% : 8 ms
        99% : 9 ms
       100% : 14 ms

===========================================================================

```
## ab
Параметры теста:
```
ab -c 8 -n 100000 http://localhost/httptest/wikipedia_russia.html
```
### prefork server
```
Server Software:        PreforkServer
Server Hostname:        localhost
Server Port:            80

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      8
Time taken for tests:   41.312 seconds
Complete requests:      100000
Failed requests:        0
Total transferred:      95493400000 bytes
HTML transferred:       95482400000 bytes
Requests per second:    2420.61 [#/sec] (mean)
Time per request:       3.305 [ms] (mean)
Time per request:       0.413 [ms] (mean, across all concurrent requests)
Transfer rate:          2257348.64 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       1
Processing:     1    3   1.9      3      22
Waiting:        0    0   0.3      0       7
Total:          1    3   2.0      3      22

Percentage of the requests served within a certain time (ms)
  50%      3
  66%      3
  75%      3
  80%      3
  90%      4
  95%      7
  98%     11
  99%     13
 100%     22 (longest request)

```
### nginx
```
Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /httptest/wikipedia_russia.html
Document Length:        954824 bytes

Concurrency Level:      8
Time taken for tests:   36.272 seconds
Complete requests:      100000
Failed requests:        0
Total transferred:      95507100000 bytes
HTML transferred:       95482400000 bytes
Requests per second:    2756.93 [#/sec] (mean)
Time per request:       2.902 [ms] (mean)
Time per request:       0.363 [ms] (mean, across all concurrent requests)
Transfer rate:          2571350.21 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       1
Processing:     1    3   0.8      3      20
Waiting:        0    0   0.2      0       9
Total:          1    3   0.9      3      20

Percentage of the requests served within a certain time (ms)
  50%      3
  66%      3
  75%      3
  80%      3
  90%      3
  95%      3
  98%      4
  99%      6
 100%     20 (longest request)

```
