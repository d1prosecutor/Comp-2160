#ifndef PROCESSCOMMANDS_H
#define PROCESSCOMMANDS_H

#include "common.h"
#include "province.h"
#include "industry.h"
#include "income.h"

// Variable
extern const char COMMAND_SEPARATOR_STRING[];

// Functions
void process_commands(Province *, int, Industry *, int, Income *, int);

#endif