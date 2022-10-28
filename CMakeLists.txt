cmake_minimum_required(VERSION 3.15)

project("CServer")

add_executable("Server" server.c)
add_executable("Client" client.c)

