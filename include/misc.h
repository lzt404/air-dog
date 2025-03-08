#ifndef MISC_H
#define MISC_H

#include "serialPort/SerialPort.h"
#include <unistd.h>

extern MotorCmd    cmd;
extern MotorData   data;

extern SerialPort  serial;

void all_init();
void all_zero_moment_mode();
#endif

