#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <thread>
#include <fstream>
#include <filesystem>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define BUFFER_SIZE 1024*32
#define RESPONSE_BUILDER(code, code_msg, content, content_len, content_type) std::string("HTTP/1.1 " + std::to_string(code) + " " + code_msg + "\r\nContent-Type: " + content_type + "\r\nContent-Length: "+ std::to_string(content_len)+"\r\nConnection: keep-alive\r\n\r\n"+ content)
using namespace std;
class Server {
	string ip;//¥˝…Ë÷√ip
	int port;//¥˝…Ë÷√∂Àø⁄∫≈
	SOCKET srvsocket;
	WSADATA wsadata;
	thread server_thread;
	map<SOCKET, std::thread> clients;
	map<std::string, std::string> content_types{ {"html","text/html;charset=utf-8"},{"htm","text/html;charset=utf-8"},{"jpg","image/jpeg"},{"jpeg","image/jpeg"},{"png","image/png"} };
public:
	Server(string ip, int port);
	void start();
};