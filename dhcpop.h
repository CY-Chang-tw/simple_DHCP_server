#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "dhcpoffer.h"


void handle_dhcp_message(int sockfd, struct sockaddr_in client_addr, socklen_t addr_len, struct dhcp_header *dhcp_pkt) {
    switch (dhcp_pkt->option_message_type) {
        case 1:
            printf("Received DHCP Discover\n");
            craft_and_send_dhcp_offer(sockfd, client_addr, addr_len, dhcp_pkt);
            break;
        case 2:
            break;
        default:
            printf("Unhandled DHCP message type: %d\n", dhcp_pkt->option_message_type);
            break;
    }
}

void process_ip_address(const void *ip_address) {
    // Conver the IP address from network byte order to string representation
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, ip_address, ip_str, INET_ADDRSTRLEN);

    printf("Processing IP address: %s\n", ip_str);

    // Log the IP address to a file
    FILE *log_file = fopen("logfile.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "Processed IP address: %s\n", ip_str);
    }
    else {
        perror("Error opening log file.");
    }

    // Access control (not completed)
    if (strcmp(ip_str, "192.168.1.1") == 0) {
        printf("Access granted for IP address: %s\n", ip_str);
    }
    else {
        printf("Access denied for IP address: %s\n", ip_str);
        exit(EXIT_FAILURE);
    }

}