#include <stdint.h>
#include <stdio.h>
#include "serial.h"
#include "parsing.h"

void receive_sbuspackets(uint8_t* sbus_packet) {
    // code here with the data
}

int main(int argc, char** argv) {
    char *port_name_1 = argv[1]; // Adjust path if necessary
    char *port_name_2 = argv[2];  // Adjust path if necessary

    FILE *sbus; 
    FILE *sabertooth;

    // To store SBUS packets
    uint8_t sbus_packet[25]; 

    // To store value of individual RC channel
    uint16_t *channel;

    // PWM value after interpolation 
    int pwm;

    // Opening serial port for serial communication with Sabertooth and SBUS
    sbus = open_file(port_name_1, "rb");
    sabertooth = open_file(port_name_2, "w+");
   
        // Read data from RC transmitter using SBUS
    read_SBUS(sbus_packet,sizeof(uint8_t), 25, sbus);

        // Parse SBUS packet
    channel = parse_buffer(sbus_packet);
        // Interpolate to get PWM range for Sabertooth 1
        pwm = interpolation(channel[0]);

        // Write data to Sabertooth 1
        write_to_SB(sabertooth, "%d\n", pwm);
       


    // Closing all serial ports
    close_file(sbus);
    close_file(sabertooth);

    return 0;
}
