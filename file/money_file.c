#include "money_file.h"
MoneyFile MoneyFile_Init(char* filepath){
    MoneyFile self;
    MoneyFile_InitVariable(&self,filepath);
    MoneyFile_InitFunction(&self);
    return self;
}
void MoneyFile_InitVariable(MoneyFile* self,char* filepath){
    self->filepath=filepath;
}
void MoneyFile_InitFunction(MoneyFile* self){
    self->SaveWithOverwrite=MoneyFile_SaveWithOverwrite;
    self->ReadFileToLinkedList=MoneyFile_ReadFileToLinkedList;
    self->Release=MoneyFile_Release;
}

void MoneyFile_Release(MoneyFile* self){

}

int MoneyFile_SaveWithOverwrite(struct MoneyFile *self, LinkedList money_list){
    // 文件结构体指针
    FILE *fp = NULL;
    // 以只写的模式打开文件
    if ((fp = fopen(self->filepath, "wb")) == NULL) {
        return -1;
    }
    //写入
    Card *pCard;
    for (int i = 0; i < money_list.count; i++) {
        money_list.Get(&money_list, i, (void **) &pCard);
        fwrite(pCard, sizeof(Card), 1, fp);
    }
    // 关闭文件
    fclose(fp);
    return 0;
}

int MoneyFile_ReadFileToLinkedList(struct MoneyFile *self, LinkedList *target_list_pointer){
    //文件结构体指针
    FILE *fp = NULL;
    //以只读的方式打开文件
    if ((fp = fopen(self->filepath, "rb")) == NULL) {
        return -1;
    }
    while (!feof(fp)) {
        Card *cp = (Card *) malloc(sizeof(Card));
        if (fread(cp, sizeof(Card), 1, fp) != 0) {
            (*target_list_pointer).Add(target_list_pointer, cp);
        }
    }
    fclose(fp);
    return 0;
}