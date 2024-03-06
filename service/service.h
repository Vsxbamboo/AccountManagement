#ifndef ACCOUNTMANAGEMENT_SERVICE_H
#define ACCOUNTMANAGEMENT_SERVICE_H

#include "../model.h"
#include "cardService.h"

Status service_add(Card *cardp);
void service_show(Card *cardp);

#endif //ACCOUNTMANAGEMENT_SERVICE_H
