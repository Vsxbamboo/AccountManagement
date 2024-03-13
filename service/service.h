#ifndef ACCOUNTMANAGEMENT_SERVICE_H
#define ACCOUNTMANAGEMENT_SERVICE_H

#include "../model.h"
#include "card_service.h"

Status service_add(Card *cardp);
void service_show(Card *cardp);
Card* service_query(char* aName);
Status service_saveCard();
Status service_readCard();
int service_getCount();
Status service_updateCard(Card *p,int n);
int service_ifinFile(char *pName);

#endif //ACCOUNTMANAGEMENT_SERVICE_H
