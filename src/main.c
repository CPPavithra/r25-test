#include <stdint.h>
#include <stdio.h>
#include <unistd.h> // For usleep function
#include "serial.h"
#include "parsing.h"

void receive_sbuspackets(uint8_t* sbus_packet)
{
    // code here with the data
}
int main(int argc, char** argv) {
    /*if (argc < 3) {
        fprintf(stderr, "Usage: %s <SBUS_PORT> <SABERTOOTH_PORT>\n", argv[0]);
        return 1;
    }(commented to test run it)*/
    char *port_name_1 = argv[1]; // SBUS 
    char *port_name_2 = argv[2]; // Sabertooth

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
    if (sbus == NULL) {
        perror("Error opening SBUS port");
        return 1;
    }
  //Error detection
    sabertooth = open_file(port_name_2, "w+");
    if (sabertooth == NULL) {
        perror("Error opening Sabertooth port");
        close_file(sbus);
        return 1;
    }
    
    // Main loop
    while (1) {
        // Read data from RC transmitter using SBUS
        read_SBUS(sbus_packet, sizeof(sbus_packet), 1, sbus);

        // Parse SBUS packet
        channel = parse_buffer(sbus_packet);
        if (channel == NULL) {
            fprintf(stderr, "Error parsing SBUS data\n");
            close_file(sbus);
            close_file(sabertooth);
            return 1;
        }

        // Interpolate to get PWM range for Sabertooth 1
        pwm = interpolation(channel[0]);

        // Write data to Sabertooth 1
        write_to_SB(sabertooth, "%d\n", pwm);
        
        // Delay to throttle loop
        usleep(5000); // Gives a 5ms delay
    }

    // Closing all serial ports
    close_file(sbus);
    close_file(sabertooth);

    return 0;
}
