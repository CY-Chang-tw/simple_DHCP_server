#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "dhcpop.h"



int main() {
    // create a UDP Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed.");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the DHCP server port
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DHCP_SERVER_PORT);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed.");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("DHCP Server listening on port %d...\n", DHCP_SERVER_PORT);

    while (1) {
        dhcp_header dhcp_pkt;
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        // Received DHCP packet
        ssize_t bytes_received = recvfrom(sockfd, &dhcp_pkt, sizeof(dhcp_pkt), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (bytes_received == -1) {
            perror("Received failed.");
            continue;
        }

        // Process the DHCP packet
        handle_dhcp_message(sockfd, client_addr, addr_len, &dhcp_pkt);

        // Process the IP address
        process_ip_address(&client_addr.sin_addr.s_addr);
    }
    return 0;
}
