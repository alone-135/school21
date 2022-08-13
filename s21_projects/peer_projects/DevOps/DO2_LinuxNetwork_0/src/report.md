# DO2_LinuxNetwork-0

<br>

## Part 1. Инструмент ipcalc
<br>

### 1.1. Сети и маски

1. Адрес сети 192.167.38.54/13

    ```
    192.160.0.0
    ```


2.  - Перевод маски 255.255.255.0 в префиксную и двоичную
    запись

        ```
        /24
        11111111.11111111.11111111.00000000
        ```
    - /15 в обычную и двоичную

        ```
        255.254.0.0
        11111111.11111110.00000000.00000000
        ```
    - 11111111.11111111.11111111.11110000 в обычную и префиксную

        ```
        255.255.255.240
        28
        ```

3. Минимальный и максимальный хост в сети 12.167.38.4 при      
масках:
    - /8

        ```
        12.0.0.1
        12.255.255.254
        ``` 
    - 11111111.11111111.00000000.00000000

        ```
        12.167.0.1
        12.167.255.254
        ```
    - 255.255.254.0

        ```
        12.167.38.1
        12.167.39.254
        ``` 
    - /4

        ```
        0.0.0.1
        15.255.255.254
        ```

<br>

### 1.2. localhost

Определить и записать в отчёт, можно ли обратиться к приложению, работающему на localhost, со следующими IP:
- 194.34.23.100 - `нет`
- 127.0.0.2 - `да`
- 127.1.0.1 - `да`
- 128.0.0.1 - `нет`
    
```
localhost (так называемый, «местный» от англ. local, или «локальный хост», по смыслу — этот компьютер) — в компьютерных сетях, стандартное, официально зарезервированное доменное имя для частных IP-адресов (в диапазоне 127.0.0.1 — 127.255.255.254, RFC 2606).
```
<br>

### 1.3. Диапазоны и сегменты сетей

Определить и записать в отчёт:

1. какие из перечисленных IP можно использовать в качестве публичного, а какие только в качестве частных: 
- 10.0.0.45 - `частная`
- 134.43.0.2 - `публичная`
- 192.168.4.2 - `частная`
- 172.20.250.4 - `частная`
- 172.0.2.1 - `публичная`
- 192.172.0.1 - `публичная`
- 172.68.0.2 - `публичная`
- 172.16.255.255 - `частная`
- 10.10.10.10 - `частная`
- 192.169.168.1 - `публичная`

<br>

<t><img src="images/p1_privat_ip_table.png" alt="p1_privat_ip_table.png">  
[ Допустимые диапазоны ip адресов для LAN сетей ]
<br>

2. какие из перечисленных IP адресов шлюза возможны у сети 10.10.0.0/18: 
- 10.0.0.1 - `невозможен`
- 10.10.0.2 - `возможен`
- 10.10.10.10 - `возможен`
- 10.10.100.1 - `невозможен`
- 10.10.1.255 - `возможен`

---

<br>

## Part 2. Статическая маршрутизация между двумя машинами

- С помощью команды ip a посмотреть существующие сетевые интерфейсы

    <img src="images/p2_ip_addr.png" width=1000>
    [ Вывод команды сетевых интерфейсов машин ]

    <br>

- Описать сетевой интерфейс, соответствующий внутренней сети, на обеих машинах и задать следующие адреса и маски:   
    ws1 - 192.168.100.10, маска /16,   
    ws2 - 172.24.116.8, маска /12

    <img src="images/p2_static_change.png" alt="p2_static_change">
    [ Вывод конфига интерфейсов ]

    <br>

- Выполнить команду netplan apply для перезапуска сервиса сети

    <img src="images/p2_netplan_apply.png" alt="p2_netplan_apply">
    [ Перезапуск сервиса сетей ]

    <br>

- 2.1. Добавление статического маршрута вручную

    + Добавить статический маршрут от одной машины до другой и обратно при помощи команды вида ip r add

    + Пропинговать соединение между машинами

    <img src="images/p2_static.png" alt="p2_static">
    [ Добавление статического маршрута и пинговка соединения ]

    <br>

- 2.2. Добавление статического маршрута с сохранением

    Перезапустить машины

    + Добавить статический маршрут от одной машины до другой с помощью файла etc/netplan/00-installer-config.yaml

        <img src="images/p2_dynamic.png" alt="p2_dynamic">
        [ Вывод конфига сетей ]

    <br>

    + Пропинговать соединение между машинами

        <img src="images/p2_dynamic_ping.png" alt="p2_dynamic_ping">
        [ Пинговка соединения ]
    



    <br>


---

<br>

## Part 3. Утилита iperf3

- 3.1. Скорость соединения
 
    8 Mbps = `1 MB/s`  
    100 MB/s = `800000 Kbps`  
    1 Gbps = `1000 Mbps`  

- 3.2. Утилита iperf3

    Измерить скорость соединения между ws1 и ws2

    <img src="images/p3_speedtest.png" alt="p3_speedtest">
    
    [ Вывод теста скорости соединения ]
    
    <br>

___

<br>

## Part 4. Сетевой экран

### 4.1. Утилита iptables 

Создать файл /etc/firewall.sh, имитирующий фаерволл, на ws1 и ws2:

Нужно добавить в файл подряд следующие правила:
    1) на ws1 применить стратегию когда в начале пишется запрещающее правило, а в конце пишется разрешающее правило (этокасается пунктов 4 и 5)  
    2) на ws2 применить стратегию когда в начале пишется разрешающее правило, а в конце пишется запрещающее правило (этокасается пунктов 4 и 5)  
    3) открыть на машинах доступ для порта 22 (ssh) и порта 80 (http)  
    4) запретить echo reply (машина не должна "пинговаться”, т.е. должна быть блокировка на OUTPUT)  
    5) разрешить echo reply (машина должна "пинговаться")  

<br>

<img src="images/p4_firewall_1.png" alt="p4_firewall_1">
[ Вывод фаервола ]

<br>

<img src="images/p4_firewall_2.png" alt="p4_firewall_2">
[ Запуск фаервола ]

<br>

### 4.2. Утилита nmap  

Командой ping найти машину, которая не "пингуется", после чего утилитой nmap показать, что хост машины запущен
Проверка: в выводе nmap должно быть сказано: Host is up

<img src="images/p4_ping.png" alt="p4_ping">
[ Пинговка машины, у которой блокируется пинг ]

<br>

<img src="images/p4_nmap.png" alt="p4_nmap">
[ Вывод статуса машины, у которой заблочен пинг ]

<br>

---

<br>


## Part 5. Статическая маршрутизация сети

<br>

<img src="images/part5_network.png" alt="part5_network"/>
[ Сеть ]

<br>

### 5.1. Настройка адресов машин
<br>

- Настроить конфигурации машин в *etc/netplan/00-installer-config.yaml* согласно сети на рисунке
    
    <br>
    <img src="images/p5_11.png" alt="p5_11"/>
    [ Вывод конфига сетей машин ]

    <br>

- Перезапустить сервис сети. Если ошибок нет, то командой `ip -4 a` проверить, что адрес машины задан верно. Также пропинговать ws22 с ws21. Аналогично пропинговать r1 с ws11.
    
    <br>
    <img src="images/p5_12.png" alt="p5_12"/>
    [ Вывод адресов сетевых интерфейсов машин ]

    <br>
    <img src="images/p5_13.png" alt="p5_13"/>
    [ Пинг r1 с ws11 ]

    <br>
    <img src="images/p5_14.png" alt="p5_14"/>
    [ Пинг ws22 с ws21 ]

    ---

    <br>

### 5.2. Включение переадресации IP-адресов.
<br>

- Для включения переадресации IP, выполните команду на роутерах:
`sysctl -w net.ipv4.ip_forward=1`  
*При таком подходе переадресация не будет работать после перезагрузки системы.*
    <img src="images/p5_21.png" alt="p5_21"/>
    [  Включение переадресации ip командой ]

<br>

- Откройте файл */etc/sysctl.conf* и добавьте в него следующую строку:
`net.ipv4.ip_forward = 1`  
*При использовании этого подхода, IP-переадресация включена на постоянной основе.*
    <img src="images/p5_21.png" alt="p5_21"/>
    [ Вывод файла /etc/sysctl.conf ]

    ---

<br>

### 5.3. Установка маршрута по-умолчанию
<br>

Пример вывода команды `ip r` после добавления шлюза:
```
default via 10.10.0.1 dev eth0
10.10.0.0/18 dev eth0 proto kernel scope link src 10.10.0.2
```

- Настроить маршрут по-умолчанию (шлюз) для рабочих станций. Для этого добавить gateway4 \[ip роутера\] в файле конфигураций
    <img src="images/p5_31.png" alt="p5_31"/>
    [ Вывод файла /etc/netplan/00-installer-config.yaml ]
    
    <br>

- Вызвать `ip r` и показать, что добавился маршрут в таблицу маршрутизации
    <img src="images/p5_32.png" alt="p5_32"/>
    [ Вывод таблицы маршрутизации ]
    
    <br>
-  Пропинговать с ws11 роутер r2 и показать на r2, что пинг доходит. Для этого использовать команду:
`tcpdump -tn -i eth1`
    <img src="images/p5_33.png" alt="p5_33"/>
    [ Пинговка r2 с ws11 ]

    ---

<br>


### 5.4. Добавление статических маршрутов
<br>

- Добавить в роутеры r1 и r2 статические маршруты в файле конфигураций. Пример для r1 маршрута в сетку 10.20.0.0/26:
    ```shell
    # Добавить в конец описания сетевого интерфейса eth1:
    - to: 10.20.0.0
      via: 10.100.0.12
    ```
    <img src="images/p5_41.png" alt="p5_41"/>
    [ Вывод конфига сетей роутеров ]
    
    <br>

- Вызвать `ip r` и показать таблицы с маршрутами на обоих роутерах. Пример таблицы на r1:
    ```
    10.100.0.0/16 dev eth1 proto kernel scope link src 10.100.0.11
    10.20.0.0/26 via 10.100.0.12 dev eth1
    10.10.0.0/18 dev eth0 proto kernel scope link src 10.10.0.1
    ```
    <img src="images/p5_42.png" alt="p5_42"/>
    [ Вывод таблицы маршрутизации роутеров ]
    
    <br>

- Запустить команды на ws11:
`ip r list 10.10.0.0/[маска сети]` и `ip r list 0.0.0.0/0`
    <img src="images/p5_43.png" alt="p5_43"/>
    [ Вывод команд на ws11 ]
    
    <br>

    Для адреса 10.10.0.0/\[порт сети\] был выбран маршрут, отличный от 0.0.0.0/0, хотя он попадает под маршрут по-умолчанию потомучто при 0.0.0.0/0 маршрут строится напрямую к шлюзу

    ---

<br>

### 5.5. Построение списка маршрутизаторов
<br>

Пример вывода утилиты **traceroute** после добавления шлюза: 
```
1 10.10.0.1 0 ms 1 ms 0 ms
2 10.100.0.12 1 ms 0 ms 1 ms
3 10.20.0.10 12 ms 1 ms 3 ms
```

- Запустить на r1 команду дампа: `tcpdump -tnv -i eth0`

    <img src="images/p5_53.png" alt="p5_53"/>
    [ Вывод команы tcpdump на r1 ]

    <br>

- При помощи утилиты **traceroute** построить список маршрутизаторов на пути от ws11 до ws21
    
    <img src="images/p5_51.png" alt="p5_51"/>
    [ Вывод команы traceroute на ws 11 ]

    <br>
    
    <img src="images/p5_52.png" alt="p5_52"/>
    [ Вывод дампа на r1 ]

    <br>
    
    ```
    Утилита Traceroute формирует UDP-датаграмму (сообщение, которое нужно доставить целевому серверу), упаковывает её в IP-пакет и передаёт первому транзитному узлу. В заголовке такого IP-пакета есть поле TTL (Time To Live) — время жизни пакета. Оно определяет количество хопов, через которые пакет может пройти. На каждом узле TTL уменьшается на единицу. Если на пути к удалённому адресату время жизни пакета станет равно 0, маршрутизатор отбросит пакет и отправит источнику ICMP-сообщение об ошибке «Time Exceeded» (время истекло).
    ```

    ---

<br>

### 5.6. Использование протокола **ICMP** при маршрутизации
<br>

- Запустить на r1 перехват сетевого трафика, проходящего через eth0 с помощью команды: `tcpdump -n -i eth0 icmp`
    <img src="images/p5_61.png" alt="p5_61"/>
    [ Вывод дампа на r1 ]

    <br>

- Пропинговать с ws11 несуществующий IP (например, *10.30.0.111*) с помощью команды: `ping -c 1 10.30.0.111`
    <img src="images/p5_63.png" alt="p5_63"/>
    [ Вывод пина 10.30.0.111 с ws11 ]

    <br>

    <img src="images/p5_62.png" alt="p5_62"/>
    [ Вывод перехвата пига с ws1 ]
---

<br>

## Part 6. Динамическая настройка IP с помощью **DHCP**
<br>

- Для r2 настроить в файле */etc/dhcp/dhcpd.conf* конфигурацию службы **DHCP**:

    - Указать адрес маршрутизатора по-умолчанию, DNS-сервер и адрес внутренней сети. Пример файла для r2:
        ```shell
        subnet 10.100.0.0 netmask 255.255.0.0 {}

        subnet 10.20.0.0 netmask 255.255.255.192
        {
            range 10.20.0.2 10.20.0.50;
            option routers 10.20.0.1;
            option domain-name-servers 10.20.0.1;
        }
        ```

        <img src="images/p6_11.png" alt="p6_11"/>
        [ Вывод конфига dhcpd ]

        <br>

    - В файле *resolv.conf* прописать `nameserver 8.8.8.8.`

        <img src="images/p6_12.png" alt="p6_12"/>
        [ Вывод файла resolv.conf ]

    ---
<br>

- Перезагрузить службу **DHCP** командой `systemctl restart isc-dhcp-server`. 
    Машину ws21 перезагрузить при помощи `reboot` и через `ip a` показать, что она получила адрес. 
    Также пропинговать ws22 с ws21.

    <img src="images/p6_21.png" alt="p6_21"/>
        [ Перезагрузка dhcp ]

    <br>
    
    <img src="images/p6_22.png" alt="p6_22"/>
        [ Новый ip у ws21 ]

    <br>
    
    <img src="images/p6_23.png" alt="p6_23"/>
        [ Пинг ws22 с ws21 ]

    ---
<br>

- Указать MAC адрес у ws11, для этого в *etc/netplan/00-installer-config.yaml* надо добавить строки: `macaddress: 10:10:10:10:10:BA`, `dhcp4: true`
    <img src="images/p6_31.png" alt="p6_31"/>
        [ Замена MAC адреса ]

    ---
<br>

- Для r1 настроить аналогично r2, но сделать выдачу адресов с жесткой привязкой к MAC-адресу (ws11). Провести аналогичные тесты
    - В отчёте этот пункт описать аналогично настройке для r2.

    <img src="images/p6_41.png">
        [ Вывод конфига dhcp роутера 1 (r1) ]

    <br>
    
    <img src="images/p6_42.png">
        [ Перезагрузка ics-dhcp-server на r1 ]

    <br>
    
    <img src="images/p6_43.png">
        [ Новый ip у ws11 ]

    <br>

    <img src="images/p6_44.png">
        [ Пинг ws11 с r1 ]
    
    ---

<br>

- Запросить с ws21 обновление ip адреса
    <img src="images/p6_51.png" alt="p6_51"/>
    [ Получение нового ip ]
    
    <br>
    `sudo dhclient -r` - освобождает текущий ip адрес машины

---

<br>


## Part 7. **NAT**

<br>

- 7.1 В файле */etc/apache2/ports.conf* на ws22 и r1 изменить строку `Listen 80` на `Listen 0.0.0.0:80`, то есть сделать сервер Apache2 общедоступным
    - В отчёт поместить скрин с содержанием изменённого файла.

    <img src="images/p7_11.png">
    [ Конфиг apache на r1 ]
    
    <br>

    <img src="images/p7_12.png">
    [ Конфиг apache на ws22 ]

    ---
    
    <br>

- 7.2 Запустить веб-сервер Apache командой `service apache2 start` на ws22 и r1
    - В отчёт поместить скрины с вызовом и выводом использованной команды.

    <img src="images/p7_22.png">
    [ Запуск apache на r1 ]
    
    <br>

    <img src="images/p7_21.png">
    [ Запуск apache на ws22 ]

    ---
    
    <br>

- 7.3 Добавить в фаервол, созданный по аналогии с фаерволом из Части 4, на r2 следующие правила:
    1) Удаление правил в таблице filter - `iptables -F`
    2) Удаление правил в таблице "NAT" - `iptables -F -t nat`
    3) Отбрасывать все маршрутизируемые пакеты - `iptables --policy FORWARD DROP`  
    - Запускать файл также, как в Части 4    
    - Проверить соединение между ws22 и r1 командой `ping` (При запуске файла с этими правилами, ws22 не должна "пинговаться" с r1)
    
    <img src="images/p7_31.png">
    [ Пинг ws22 с r1 ]
    
    ---
    
    <br>

- 7.4 Добавить в файл ещё одно правило:  
    4) Разрешить маршрутизацию всех пакетов протокола **ICMP**
    - Запускать файл также, как в Части 4
    - Проверить соединение между ws22 и r1 командой `ping` *При запуске файла с этими правилами, ws22 должна "пинговаться" с r1*
    
    <img src="images/p7_41.png">
    [ Пинг ws22 с r1 ]

    ---
    
    <br>

- 7.5 Добавить в файл ещё два правила:  
    5) Включить **SNAT**, а именно маскирование всех локальных ip из   локальной сети, находящейся за r2 (по обозначениям из Части 5 - сеть 10.20.0.0)   
    *Совет: стоит подумать о маршрутизации внутренних пакетов, а также внешних пакетов с установленным соединением*  
    6) Включить **DNAT** на 8080 порт машины r2 и добавить к веб-серверу Apache, запущенному на ws22, доступ извне сети *Совет: стоит учесть, что при попытке подключения возникнет новое tcp-соединение, предназначенное ws22 и 80 порту*
    
    <img src="images/p7_51.png">
    [ firewall на r2 ]
    
    ---
    
    <br>

- 7.6 Запускать файл также, как в Части 4   
    *Перед тестированием рекомендуется отключить сетевой интерфейс **NAT** (его наличие можно проверить командой `ip a`) в VirtualBox, если он включен*

    - Проверить соединение по TCP для **SNAT**, для этого с ws22 подключиться к серверу Apache на r1 командой: `telnet [адрес] [порт]`
    
    - Проверить соединение по TCP для **DNAT**, для этого с r1 подключиться к серверу Apache на ws22 командой `telnet` (обращаться по адресу r2 и порту 8080)

    <img src="images/p7_61.png">
    [ Подключение к r1 с ws22 ]

    <br>

    <img src="images/p7_62.png">
    [ Подключение к ws22 с r1 через r2 ]

---

<br>


## Part 8. Дополнительно. Знакомство с **SSH Tunnels**
<br>

- Запустить на r2 фаервол с правилами из Части 7

    <img src="images/p8_11.png">
    [ Включение фаервола на r2 ]

    ---
    <br>

- Запустить веб-сервер **Apache** на ws22 только на localhost (то есть в файле */etc/apache2/ports.conf* изменить строку `Listen 80` на `Listen localhost:80`)

    <img src="images/p8_21.png">
    [ Изменение конфига apache ]

    <br>

    <img src="images/p8_22.png">
    [ Перезагрузка apache ]

    ---
    <br>

- Воспользоваться *Local TCP forwarding* с ws21 до ws22, чтобы получить доступ к веб-серверу на ws22 с ws21

    <img src="images/p8_32.png">
    [ Доступ к ws22 с ws21 ]

    ---
    <br>

- Воспользоваться *Remote TCP forwarding* c ws11 до ws22, чтобы получить доступ к веб-серверу на ws22 с ws11

    <img src="images/p8_32.png">
    [ Доступ к ws22 с ws11 ]

    ---
    <br>

---