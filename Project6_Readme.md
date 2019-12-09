## PES Project Six Readme

Student Name: Kyle Bryan

#### Running Code, General description

The program implements a DAC and ADC.  It has multiple
run modes with which it runs it, which is explained below.  At a high level
the program drives the DAC with generated sinusoid values that are fed into an
ADC. The application then samples the ADC and DMAs those values to a buffer where
the max, min, mean, and std deviation are calculated.  The program uses freeRTOS
and has 3 seperate tasks(DAC, ADC, and value calculations)

This code is written to be run on the FRDM board using MCUExpresso.  To run the project, you must first enable the
DAC0 and ADC0 in the pin GUI.  You also need freeRTOS support in the SDK.

##### Use Defines.h to select run mode


###### Log Type Options
The log types options selects if you want to run in:    
*Debug Mode* - prints more detailed info about processes that are running during runtime  
*Status Mode* - only prints the Signal processing outputs

###### Program1 vs Program2
Selects whether to run just the DAC or the full program w. freeRTOS:  
*By commenting Proram1 Program 2 is run.*


##### Repository Contents
###### Source Code
*main.c*, *led_control.h*, *led_control.c*, *logger.h*,*logger.c*,
, *testSuite.c/h*, *circularbuffer.c/h*, *dac.c/h*, *defines.h*, *adc.c/h*,
*dma.c/h*, *program1.c/h*, *program2.c/h*

The main.c is where the main program is run.  It is where the peripheral inits
are called and the tasks are set up.  

There was some code taken from online sources and those are called out in the
files they are used in.  A lot of the code was also leveraged from the SDK examples
and that is called out as well.

###### Extra Project Documents
*Program1_Capture*, *Program2_Capture*,

These documents are in the /.bin folder and are other(non-source code) project5
deliverables.  They include the oscilloscope capture of the DAC out for Program1
and Program2.


#### Observations for Project:
This project was one of the more smoothly run projects of the semester.  One thing
I was a little confused of(and still am) is about interrupt IRQs.  I am unsure if
when running an RTOS you should or should not disable interrupts in the IRQ.  It
does not seem like they are disables by the SDK example code.  The examples were
very helpful for initializing and using the peripherals/dma as well as setting up
tasks and timers.  
