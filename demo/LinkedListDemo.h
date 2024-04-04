//
// Created by vsx on 2024/3/20.
//

#ifndef ACCOUNTMANAGEMENT_LINKEDLISTDEMO_H
#define ACCOUNTMANAGEMENT_LINKEDLISTDEMO_H

#include "../model.h"
#include <stdlib.h>
#include <stdio.h>

void ll_init();
int ll_insert(int e,int index);
int ll_del(int index);
int ll_get(int index,int *pInt);
void ll_release();
void ll_show();


#endif //ACCOUNTMANAGEMENT_LINKEDLISTDEMO_H
