#include <iostream>

#include "tcpserversocket.h"
#include "udpsocket.h"

void HandleTCPClient(TCPSocket *sock, size_t length) {
  std::cout << "Handling client ";
  try {
    std::cout << sock->getRemoteAddress() << ":";
  } catch (SocketException e) {
    std::cerr << "Unable to get foreign address\n";
  }
  try {
    std::cout << sock->getRemotePort();
  } catch (SocketException e) {
    std::cerr << "Unable to get foreign port\n";
  }
  std::cout << "\n";

  // Send received string and receive again until the end of transmission
  char r_buffer[length];
  ssize_t recvMsgSize;
  while ((recvMsgSize = sock->recv(r_buffer, length)) > 0) {
  }

  std::cout << "TCPServer: Received the following msg from client:\n";
  std::cout << r_buffer << "\n";
  delete sock;
}



int main(int argc, char *argv[])
{
    int id = 0;

    if (argc != 2){
        std::cerr << "The test program expects exactly 1 arguement!\n";
        std::cerr << "Input the id for the role to assume: 1 for client / 2 for server\n";
        exit(1);
    } else {
        try {
            id = std::atoi(argv[1]);
            if (id < 1 || id > 2){
                std::cerr << "Invalid arguement. Id should be either 1 or 2\n";
                exit(1);
            }
        } catch (std::invalid_argument) {
            std::cerr << "Invalid arguement passed to program\n";
            exit(1);
        }
    }


    constexpr unsigned short server_port = 14598;
    const std::string server_address = "localhost";
    std::string msg("This is a test message");
    const char *message = msg.c_str();
    size_t msg_length = strlen(message);

    unsigned short client_port = 17893;
    std::string client_address = "localhost";


    //Client
    if (id == 1){
        /*TCP*/
//        try {
//            TCPSocket client_sock(server_address, server_port);
//            std::cout << "Client sending msg\n";
//            client_sock.send(message, msg_length);
//        } catch (SocketException& e) {
//            std::cerr << e.what() <<"\n";
//            exit(1);
//        }

        /*UDP*/
        try {
            UDPSocket u_sock;

            u_sock.sendTo(message, msg_length, server_address, server_port);
        } catch (SocketException& e) {
            std::cerr << e.what() <<"\n";
            exit(1);
        }

    }//Server
    else if (id == 2)
    {
        /*TCP*/
//        try {
//            TCPServerSocket server_sock(server_port);

//            for (;;) {
//                HandleTCPClient(server_sock.accept(), msg_length);
//            }
//        } catch (SocketException& e) {
//            std::cerr << e.what() <<"\n";
//            exit(1);
//        }

        /*UDP*/
        try {
            UDPSocket s_sock(server_port);
            ssize_t rcv_size;
            char serv_buffer[msg_length];
            for (;;) {
                rcv_size = s_sock.recvFrom(serv_buffer, msg_length, client_address, client_port);
                std::cout << "Received from " << client_address << ":" << client_port << " the message:\n";
                std::cout << serv_buffer << "\n";
            }

        } catch (SocketException& e) {
            std::cerr << e.what() <<"\n";
            exit(1);
        }

    }

/*TO-DO
  Write code for UDP sockets
*/

    return 0;
}
