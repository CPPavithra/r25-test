#ifndef PARSING_H
#define PARSING_H

#include <stdint.h>

// Function to parse SBUS channel
uint16_t *parse_buffer(uint8_t buff[]);

// Function to interpolate channel and return PWM value 
int interpolation(uint16_t channel);

#endif
