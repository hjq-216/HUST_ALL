#include "Server.h"
#include<filesystem>
using namespace std;
Server::Server(string ip, int port) :ip(move(ip)), port(port) {
	if (WSAStartup(0x0202, &wsadata) != 0)
		cout << "Startup failed!" << endl;
	else
		cout << "Startup successed!" << endl;
}
void Server::start() {
	server_thread = thread([&]()->void {
		addrinfo hints, * addr;
		memset(&hints, 0, sizeof(addrinfo));
		if (getaddrinfo(ip.c_str(), to_string(port).c_str(), &hints, &addr) == 0)
			cout << "Get address successed!" << endl;
		if ((srvsocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) != INVALID_SOCKET)
			cout << "Create socket successed!" << endl;
		if ((bind(srvsocket, addr->ai_addr, addr->ai_addrlen)) != SOCKET_ERROR)
			cout << "Bind successed!" << endl;
		if (listen(srvsocket, SOMAXCONN) != SOCKET_ERROR)
			cout << "Listen successed!" << endl;
		
		while (1) {
				SOCKET sessionsocket = accept(srvsocket, NULL, NULL);
				if (sessionsocket == INVALID_SOCKET) {
					cout << "Creat sessionsocket failed!" << endl;
					continue;
				}
				clients[sessionsocket] = thread([&]()->void {
					char* recv_buffer = new char[BUFFER_SIZE];
					int bytes_recv = 0;
					sockaddr_in client_addr;
					int client_addr_len = sizeof(sockaddr_in);
					if (getpeername(sessionsocket, (sockaddr*)(&client_addr), &client_addr_len) == SOCKET_ERROR) {
						cout << "Get client info failed" << endl;
						goto exit;
					}
					while (1) {
						bytes_recv = recv(sessionsocket, recv_buffer, BUFFER_SIZE, 0);
						char* buffer_ptr = recv_buffer;
						char* buffer_end = recv_buffer + bytes_recv;
						string ip_msg = string(buffer_ptr, buffer_end);
						if (bytes_recv > 0) {
							cout << "请求报文：" << endl;
							cout << ip_msg << endl;
							while (buffer_ptr < buffer_end && *++buffer_ptr != ' ');
							char* url_start = buffer_ptr;
							while (buffer_ptr < buffer_end && *++buffer_ptr != ' ');
							filesystem::path file_name(std::string(url_start + 2, buffer_ptr));//+2：空格和‘/’
							
							ifstream file(file_name, std::ios::binary | std::ios::ate);//ate将文件指针移到文件尾，为tellg做铺垫
							if (file.is_open()) {
								streamsize size = file.tellg();
								file.seekg(0, std::ios::beg);//将file移到文件开始
								char* buffer = new char[filesystem::file_size(file_name)];
								if (file.read(buffer,size)) {
									string ext(file_name.extension().generic_string());
									ext = ext.substr(1, ext.size() - 1);
									string x = (buffer, buffer + size);
									string response = RESPONSE_BUILDER(200, "OK", string(buffer,buffer+size), filesystem::file_size(file_name), content_types[ext]);
									send(sessionsocket, response.c_str(), response.length(), 0);
									cout << "响应报文：" << endl;
									cout << response.c_str()<<endl;
									continue;
								}
								delete[] buffer;
							}
							cout << "请求报文：" << endl;
							cout << ip_msg << endl;
							string content = "<html><head><title>404 not found</title></head><body><h1>404 Not Found.</h1><hr><p>PLEASE BEG HJQ.</p></body></html>";
							string response = RESPONSE_BUILDER(404, "NotFound", content, content.size(), "text/html; charset=UTF-8");
							send(sessionsocket, response.c_str(), strlen(response.c_str()), 0);
							cout << "响应报文：" << endl;
							cout << response.c_str() << endl;
						}
						else break;
					}
				
				exit:
				closesocket(sessionsocket);
				delete[] recv_buffer;
			});
				clients[sessionsocket].detach();
		}
			closesocket(srvsocket);
		}
	);
	server_thread.detach();
}