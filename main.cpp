/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"

DigitalOut myled(LED1);
UnbufferedSerial pc(USBTX, USBRX);  // Serial is deprecated in OS6. Use UnbufferedSerial
UnbufferedSerial dev(PA_2, PA_3);   // pins 9 and 10 are called PA_2 and PA_3 (pinmap not found for peripheral)

char buff;

void dev_recv(){
    while(dev.readable()){
        dev.read(&buff, 1);     // pc.putc(dev.getc()) is for Serial
        pc.write(&buff, 1);     // .read .write are for BufferedSerial and UnbufferedSerial
    }    
}

void pc_recv(){
    while(pc.readable()){
        pc.read(&buff, 1);
        dev.write(&buff, 1);    
    }    
}

int main() {
    pc.baud(9600);
    dev.baud(115200);          // dev not device1
    pc.attach(&pc_recv);
    dev.attach(&dev_recv);
    printf("Hello!! \r\n");
    
    while(1) {
        myled = 1;
        ThisThread::sleep_for(1s); // wait(1) is deprecated. could use wait_us(1000000) but is also deprecated
        myled = 0;
        ThisThread::sleep_for(1s);
    }
}