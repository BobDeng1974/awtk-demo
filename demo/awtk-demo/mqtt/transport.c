#include "transport.h"

#define MQTT_SOCKET       5
static SOCKET mqtt_socket;
int transport_sendPacketBuffer(unsigned char *buf, int buflen)
{
    int rc;
    rc = send(mqtt_socket, buf, buflen, 0);  
    if (rc != buflen) {  

    }
    return rc;
}

int transport_getdata(unsigned char *buf, int count)
{
    int rc;
    rc = recv(mqtt_socket, buf, count, 0);
    if (rc == 0) {
        
    }
    return rc;
}

int8_t transport_open(unsigned char* servip, int port)
{
    uint32_t ret;
    WSADATA Data;  
    SOCKADDR_IN destSockAddr;  
    SOCKET destSocket;  
    unsigned long destAddr;  
    int status;  
    int numsnt;  
    char *toSendtxt="Test String";  
  
    /* initialize the Windows Socket DLL */  
    status=WSAStartup(MAKEWORD(1, 1), &Data);  
    if (status != 0) {
        log_debug("ERROR: WSAStartup unsuccessful");  
    }
    
    /* convert IP address into in_addr form */  
    destAddr=inet_addr(servip);  
    /* copy destAddr into sockaddr_in structure */  
    memcpy(&destSockAddr.sin_addr, &destAddr, sizeof(destAddr));  
    /* specify the port portion of the address */  
    destSockAddr.sin_port=htons(port);  
    /* specify the address family as Internet */  
    destSockAddr.sin_family=AF_INET;  
  
    /* create a socket */  
    destSocket=socket(AF_INET, SOCK_STREAM, 0);  
    if (destSocket == INVALID_SOCKET) {  
        log_debug("ERROR: socket unsuccessful");  
        status=WSACleanup();  
        if (status == SOCKET_ERROR) {
            log_debug("ERROR: WSACleanup unsuccessful");  
        }
        return(1);  
    }

    log_debug("Trying to connect to IP Address: ");  
  
    /* connect to the server */  
    status=connect(destSocket, (LPSOCKADDR)&destSockAddr, sizeof(destSockAddr));  
    if (status == SOCKET_ERROR)  
    {  
        log_debug("ERROR: connect unsuccessful");  
            
        status=closesocket(destSocket);  
        if (status == SOCKET_ERROR) {
            log_debug("ERROR: closesocket unsuccessful");  
        }
        status=WSACleanup();  
        if (status == SOCKET_ERROR) {
            log_debug("ERROR: WSACleanup unsuccessful");  
        }
            
        return(1);  
    }  
    mqtt_socket = destSocket;
    return ret;
}

int8_t transport_close()
{
    uint32_t rc;
    rc = closesocket(mqtt_socket);
    WSACleanup();
    return rc;
}
