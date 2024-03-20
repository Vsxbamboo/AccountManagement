//
// Created by vsx on 2024/3/6.
//

#ifndef ACCOUNTMANAGEMENT_TOOL_H
#define ACCOUNTMANAGEMENT_TOOL_H

#include <time.h>
#include <stdio.h>
#include <string.h>

void timeToString(time_t t,char* pBuf);
time_t stringToTime(char* pTime);
void clearthisline();
int fuzz_str_beinclude(char *a,char *b);

#endif //ACCOUNTMANAGEMENT_TOOL_H
