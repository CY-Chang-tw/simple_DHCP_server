#include <stdlib.h>
#include <unistd.h>

#define DHCP_SERVER_PORT 67
#define DHCP_CLIENT_PORT 68
#define DHCP_HEADER_LEN 236
#define DHCP_OPTION_MAGIC_NUMBER (0x63825363)

typedef struct dhcp_header {
    uint8_t op;             // Message opcode
    uint8_t htype;          // Hardware address type
    uint8_t hlen;           // Hardware address length
    uint8_t hops;           // Hops
    uint32_t xid;           // Transaction ID
    uint16_t secs;          // Seconds elapsed (DHCP Client)
    uint16_t flags;         // Bootp flags (#define broadcast 1)
    uint32_t ciaddr;        // Client IP address
    uint32_t yiaddr;        // Your IP address (DHCP Offer / DHCP ACK)
    uint32_t siaddr;        // Next server IP address
    uint32_t giaddr;        // Relay agent IP address
    uint8_t chaddr[16];     // Client hardware address
    uint8_t padding[192];   // Padding to reach DHCP options
    uint32_t magic_cookie;  // DHCP magic cookie
    uint8_t option_message_type;    // DHCP option 53 (DHCP message type)
    uint8_t option_subnet_mask[6];  // DHCP option 1 (subnet mask)
    uint8_t option_router[12];      // DHCP option 3 (router/default gateway)
    uint8_t option_dns[12];         // DHCP option 6 (DNS servers)
    uint8_t option_end;             // DHCP option 255 (end)
}dhcp_header;


