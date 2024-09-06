# R-25 Test

<p align="center">
  <img src="https://github.com/teamrudra/r25-test/blob/main/datasheets/rover.jpeg" width="600" height="300"/>

#### Some Instructions
1. You may use any online resources, datasheets, or documentation needed, but be mindful of your time and stay focused on the task.
2. The duration of the test is 90 mins from 5:15pm to 6:45 pm.
3. There will be a MCQ test conducted [here](https://r25.munmap.net)
4. There are 3 tasks in the tests. Complete all of them.
5. In case you are not able to complete all the tasks, do upload the whatever you are able to do.
6. In the `README.md` of your repository include your thought process, places where you got stuck, where you used the help of chatGPT, google or other online resources.
7. Even if you are not able to solve anything. Do fill the readme and what your thought process would have been.
8. Carefully read the instructions to implement the required functionality.
9. Install [mingw(c compiler)](https://www.mingw-w64.org/downloads/#w64devkit) and [git](https://git-scm.com/downloads) if you haven't already done it.
10. After finishing your test, provide the link to your forked repository in the google form provided at the end.
     
### Aim/Objective: You are implementing code to control motors for a rover using data received from an RC transmitter.
## Description
You are implementing code to control a sabrtooth motor driver(we are only trying to control motor 1 using S1 of Sabertooth), connected to drive motors of the rover, using data received from an [RC transmitter](datasheets/transmitter-manual.pdf)(make note that the transmitter is configured to transmit data in extended limits). The data from the transmitter is being recieved by a SBUS reciever module, you can find about the data protocol used [here](https://github.com/bolderflight/sbus/blob/main/README.md). 

### Task 0: Fork the provided repository and ensure it is set to PUBLIC so we can access and assess your work.
### Task 1: Interpolation for Sabertooth.
The motor driver (`Sabertooth 2x60`) in the simplified serial mode (check out the [datasheets](datasheets/sabertooth(2x60).pdf))
Your task is to interpolate a channel value into the format accepted by the motor driver, and make the rover move in forward or backward direction.
### Task 2: Compile and run the code.

#### Code
1. [src/main.c](src/main.c): Code for running the test.
2. [lib/parsing.c](lib/parsing.c): Complete the defined `interpolation` function here.

#### How to Compile & Check your code
(make sure you are in the root directory)   
1. Compile your code by running: `make build`
2. To check if your code is implemented correctly run: `make check`
   
If you are able to compile your code successfully you should see something like this on your screen:

<p align="center">
  <img src="https://github.com/teamrudra/r25-test/blob/main/datasheets/make_check_succesfull.png" width="600" height="300"/>
</p>

4. If your make check was unsuccesfull, you can clean your attempt by running `make clean`, review your implementation and repeat the previous steps.

# Solution
## Understanding
I understood that the channel values must be interpolated to pwm(pulse width modulation value)- to control the amount of power delivered to the motor for it to move. I have implemented LINEAR INTERPOLATION here. 

## Thought Process
I checked up the scaling used for the particular motor and implemented the interpolation formula related to it.
What I have understood from here is that-
1. First read the SBus data from the RC
2. Then it extracts thee data from the channels
3. Then it calculated the PWM by using the linear interpolation formula
4. The readsbus function reads the data of the sbus into the buffer
5. The write_to_sb function writes the data to the saberbooth 
6. The interpolation changes the RC channel value to pwm values
7. Then it takes the pwm value and sends it to the motor driver
8. I have also included a 5ms (5000) delay to control the speed of the while loop

The imported header files were originally of the form #include<parsing.h> and #include<serial.h>, I changed it to #include "parsing.h" and "serial.h" as it is a custom header file.

## Implementation
How did you decide to implement your solution.

I moved the custom header folders into one file(src) as it was showing error while compilation. I also changed the makefile build function to
build:
	gcc -g -Wall main.c serial.c parsing.c -o program
For the interpolation of pwm(pulse width modulation)
	  int min_sbus = 0; (for the Sabertooth 2x60 motor driver)
    int max_sbus = 2047;
    int min_pwm = 1000;
    int max_pwm = 2000;
    int pwm = min_pwm+(channel-min_sbus)*(max_pwm-min_pwm)/(max_sbus - min_sbus); (formula checked)
    return pwm;
(in parsing.c file, the function is only declared in parsing.h, not defined)

(Moved every file to src, so make build make check will be run from that directory.It also runs otherwise(i.e.I have changed the makefile build inside the src makefile and kept the original in the other makefile for testing purpose))

Mention the details, such as the scaling used in the interpolation and how you tested it.
Scaling Used-
min_sbus = 0; (These values I have checked for the Sabertooth 2x60 motor driver)
max_sbus = 2047;
min_pwm = 1000;
max_pwm = 2000;
//I have included this to avoid errors and to ensure that the channel is within the range
    if (channel < min_sbus) channel = min_sbus;
    if (channel > max_sbus) channel = max_sbus;
    
# Google Form
[Link to Repo Submission](https://docs.google.com/forms/d/e/1FAIpQLSeKVbm2dqWxwA5lbEkRfzY8KF619mI5ibGs0Cm2e5wrb0hoWQ/viewform)


<p align="center">
  <img src="https://github.com/teamrudra/r25-test/blob/main/datasheets/feynman-simple.jpg" width="600" height="600"/>
</p>
