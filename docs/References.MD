

# References

### Method 2: Using an HTML `<iframe>`
<iframe src="https://refactoring.guru/design-patterns/catalog" width="600" height="400"></iframe>

[Catalog desing patterns](https://refactoring.guru/design-patterns/catalog)

https://copyconstruct.medium.com/the-method-to-epolls-madness-d9d2d6378642

https://modern.ircdocs.horse/
https://modern.ircdocs.horse/#pass-message
# Allowed functions

* socket
* close
* setsockopt
* getsockname
* getprotobyname
* gethostbyname
* getaddrinfo 
* freeaddrinfo
* bind
* connect
* listen
* accept
* htons
* htonl
* ntohs
* ntohl
* inet_addr
* inet_ntoa
* send
* recv
* signal
* sigaction
* lseek
* fstat
* fcntl
* poll| epoll | select | kqueue

# Server 

# NC command
The `netcat` (or `nc`) command is a versatile networking tool that can be used for various purposes such as creating network connections, sending data, and listening for incoming connections. Here are some common use cases:

### 1. Connect to a Remote Host
To connect to a remote host on a specific port:
```sh
nc <hostname> <port>
```
Example:
```sh
nc example.com 80
```

### 2. Listen for Incoming Connections
To listen on a specific port for incoming connections:
```sh
nc -l <port>
```
Example:
```sh
nc -l 1234
```

### 3. Transfer a File
#### Sender:
```sh
nc <destination_host> <port> < file_to_send
```
Example:
```sh
nc 192.168.1.2 1234 < file.txt
```

#### Receiver:
```sh
nc -l <port> > received_file
```
Example:
```sh
nc -l 1234 > received_file.txt
```

### 4. Port Scanning
To scan for open ports on a remote host:
```sh
nc -zv <hostname> <start_port>-<end_port>
```
Example:
```sh
nc -zv example.com 20-80
```

### 5. Chatting
#### Listener:
```sh
nc -l <port>
```
Example:
```sh
nc -l 1234
```

#### Client:
```sh
nc <hostname> <port>
```
Example:
```sh
nc localhost 1234
```

You can then type messages in both terminals to chat.

### 6. HTTP Request
To send an HTTP request to a web server:
```sh
nc <hostname> 80
```
Then type the HTTP request manually:
```
GET / HTTP/1.1
Host: <hostname>

```
Example:
```sh
nc example.com 80
```
Then type:
```
GET / HTTP/1.1
Host: example.com

```

These are just a few examples of what you can do with `netcat`. It is a powerful tool with many options, so you can refer to the manual page for more details:
```sh
man nc
```