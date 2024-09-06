#ifndef PARSING_H
#define PARSING_H

#include <stdint.h>

// Function to parse SBUS channels from buffer
uint16_t *parse_buffer(uint8_t buff[]);

// Interpolate channel value and return PWM value
int interpolation(uint16_t channel);

#endif // PARSING_H
