#include"Server.h"
int main() {
	Server s("10.211.55.3", 80);
	s.start();
	std::cin.get();
}