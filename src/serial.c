#include "serial.h"
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>

// Function to open the serial port
FILE* open_file(const char* portname, const char* mode) {
    FILE* file_ptr = fopen(portname, mode);
    if (file_ptr == NULL) {
        perror("Error opening file");
        return NULL;
    }
    return file_ptr;
}

// Function to read data from SBUS
void read_SBUS(uint8_t* buffer, size_t size, size_t n, FILE* file_ptr) {
    size_t rc = fread(buffer, size, n, file_ptr);
    if (rc != n) {
        perror("Error reading file");
    }
}

// Function to write data to Sabertooth
void write_to_SB(FILE* file_ptr, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int rc = vfprintf(file_ptr, fmt, args);
    va_end(args);
    if (rc < 0) {
        perror("Error writing to file");
    }
}

// Function to close the serial port
void close_file(FILE* file_ptr) { 
    fclose(file_ptr); 
}
