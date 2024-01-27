#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include "dhcpd.h"

static void craft_and_send_dhcp_offer(int  sockfd, struct sockaddr_in client_addr,socklen_t addr_len, struct dhcp_header *dhcp_pkt) {
    memset(dhcp_pkt, 0, sizeof(dhcp_header));
    dhcp_pkt->op = 2;       // DHCP Reply
    dhcp_pkt->htype = 1;    // Ethernet
    dhcp_pkt->hlen = 6;     // MAC address length
    dhcp_pkt->xid = 123456789;  // Transaction ID
    dhcp_pkt->secs = htons(0);  // Seconds Elapsed
    dhcp_pkt->flags = htons(0); // Bootp flags
    dhcp_pkt->ciaddr = htonl(0);    // Client IP address (0 for DHCP Offer)
    dhcp_pkt->yiaddr = htonl(0x0A010101);   // Your IP address
    dhcp_pkt->siaddr = htonl(0);    // Next server IP address
    dhcp_pkt->giaddr = htonl(0);    // Relay agent IP address
    memcpy(dhcp_pkt->chaddr, &client_addr.sin_addr.s_addr, sizeof(dhcp_pkt->chaddr));
    // Client hardware address (copy the MAC address from client_addr to dhcp_pkt->chaddr)

    //------DHCP options--------
    dhcp_pkt->magic_cookie = htonl(DHCP_OPTION_MAGIC_NUMBER);   // DHCP magic cookie
    dhcp_pkt->option_message_type = 2;   // DHCP Offer
    dhcp_pkt->option_subnet_mask[0] = 1; // Option length
    dhcp_pkt->option_subnet_mask[1] = 4; // Length of subnet mask (IPv4 address)
    dhcp_pkt->option_subnet_mask[2] = 255; // Subnet mask: 255.255.255.0;
    dhcp_pkt->option_subnet_mask[3] = 255;
    dhcp_pkt->option_subnet_mask[4] = 255;
    dhcp_pkt->option_subnet_mask[5] = 0;

    dhcp_pkt->option_router[0] = 3;     // Option length
    dhcp_pkt->option_router[1] = 4;     // Length of router IP address
    dhcp_pkt->option_router[2] = 192;   // Router IP address: 192.168.1.1
    dhcp_pkt->option_router[3] = 168;
    dhcp_pkt->option_router[4] = 1;
    dhcp_pkt->option_router[5] = 1;

    dhcp_pkt->option_dns[0] = 6;    // Option length
    dhcp_pkt->option_dns[1] = 8;    // Length of DNS server IP addresses
    dhcp_pkt->option_dns[2] = 8;    // First DNS server: 8.8.8.8
    dhcp_pkt->option_dns[3] = 8;
    dhcp_pkt->option_dns[4] = 8;
    dhcp_pkt->option_dns[5] = 8;
    dhcp_pkt->option_dns[6] = 8;    // Second DNS server: 8.8.4.4
    dhcp_pkt->option_dns[7] = 8;
    dhcp_pkt->option_dns[8] = 4;
    dhcp_pkt->option_dns[9] = 4;

    dhcp_pkt->option_end = 0xFF;    // DHCP option end

    //-----Send DHCP Offer-----
    sendto(sockfd, dhcp_pkt, sizeof(dhcp_pkt), 0, (struct sockaddr *)&client_addr, addr_len);

    printf("Sent DHCP Offer: ");
    for (int i=0; i<sizeof(dhcp_pkt); i++) {
        printf("%02X ", ((unsigned char *)dhcp_pkt)[i]);
    }
    printf("\n");
}