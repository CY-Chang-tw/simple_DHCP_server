cmake_minimum_required(VERSION 3.25)
project(DHCPserver C)

set(CMAKE_C_STANDARD 99)

add_executable(DHCPserver main.c dhcpd.h dhcpoffer.h dhcpop.h)
