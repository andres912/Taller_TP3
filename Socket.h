//
// Created by andy on 3/11/20.
//

#ifndef TP_3_SOCKET_H
#define TP_3_SOCKET_H

#include <sys/socket.h>
#include <string>
#include <netdb.h>
#include <sstream>

typedef int (*connection_callback_t)(int sockfd, const struct sockaddr *addr,
                                     socklen_t addrlen);

class Socket {
public:
    explicit Socket(int connection_type);
    ~Socket();
    int establishConnection(const char* host, const char* port);
    void setConnection(int fd);
    int acceptConnection();
    int receiveMessage(std::stringbuf& buffer);
    int sendMessage(std::stringbuf& buffer, size_t len);
    void closeConnection(bool should_shutdown);
    void listenToConnections();
    void shutDownConnection(int mode);

private:
    int socket_fd;
    struct addrinfo* connection_info;
    struct addrinfo* results;
    struct addrinfo hints = addrinfo();
    int connection_type;
    connection_callback_t connection_callback;

    void initializeHints();
    void setConnectionCallback();
    void iterateAddressesForConnecting();
    bool is_closed = false;
};



#endif //TP_3_SOCKET_H
