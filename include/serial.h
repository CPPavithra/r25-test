#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>

// Function to open the serial port
FILE* open_file(const char* portname, char* mode); // Ensure this matches

// Function to read data from SBUS
void read_SBUS(uint8_t* buffer, size_t size, size_t n, FILE* fd);

// Function to write data to Sabertooth
void write_to_SB(FILE* fd, char* fmt, ...); // Ensure this matches

// Function to close the serial port
void close_file(FILE* fd);
