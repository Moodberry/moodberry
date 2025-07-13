// moodberry.cpp - CLI client for moodberryd

#include <iostream> #include <string> #include <sys/socket.h> #include <sys/un.h> #include <unistd.h> #include <cstring>

const char* SOCKET_PATH = "/run/moodberry.sock";

int main(int argc, char* argv[]) { if (argc != 3) { std::cerr << "Usage: moodberry <service> <start|stop|enable|disable|status>\n"; return 1; }

std::string service = argv[1];
std::string command = argv[2];
std::string message = service + " " + command;

int sock = socket(AF_UNIX, SOCK_STREAM, 0);
if (sock < 0) {
    perror("socket");
    return 1;
}

sockaddr_un addr{};
addr.sun_family = AF_UNIX;
strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("connect");
    close(sock);
    return 1;
}

if (send(sock, message.c_str(), message.length(), 0) < 0) {
    perror("send");
    close(sock);
    return 1;
}

char buffer[1024];
ssize_t n;
while ((n = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
    buffer[n] = '\0';
    std::cout << buffer;
}

close(sock);
return 0;

}

