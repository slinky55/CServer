# CServer
A simple socket server written in C

A message is sent from the client, which is then displayed on the server

### To compile
<strong>Be sure to have cmake installed</strong>

Server: `cmake --build build --target Server`

Client: `cmake --build build --target Client`

### To use
1. Start the server:  `./Server [port]`
2. Start the client   `./Client [hostname] [port]`
3. Send a message
4. Repeat
