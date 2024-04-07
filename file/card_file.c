#include "card_file.h"

int CardFile_AppendCard(CardFile *self, Card *pCard) {
    // 文件结构体指针
    FILE *fp = NULL;
    // 以追加的模式打开文件，如果打开失败，则以只写的模式打开文件
    if ((fp = fopen(self->filepath, "ab")) == NULL) {
        if ((fp = fopen(self->filepath, "wb")) == NULL) {
            return -1;
        }
    }

    fwrite(pCard, sizeof(Card), 1, fp);

    // 关闭文件
    fclose(fp);
    return 0;
}

int CardFile_ReadFileToLinkedList(CardFile *self, LinkedList *target_list_pointer) {
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

int CardFile_UpdateCard(CardFile *self, int index, Card *pCard) {
    FILE *fp = NULL;    // 文件指针
    int nLine = 0;      // 文件卡信息数
    long lPosition = 0; // 文件位置标记
    Card bBuf;
    if ((fp = fopen(self->filepath, "rb+")) == NULL) {
        return -1;
    }
    while ((!feof(fp)) && (nLine < index - 1)) {
        if (fread(&bBuf, sizeof(Card), 1, fp) != 0) {      // 获取文件标识位置
            lPosition = ftell(fp);
            nLine++;
        }
    }
    fseek(fp, lPosition, 0);
    fwrite(pCard, sizeof(Card), 1, fp);
    fclose(fp);
    return 0;
}

int CardFile_GetCardCout(struct CardFile *self) {
    FILE *fp = NULL;  // 文件指针
    int nIndex = 0;   // 卡信息数量
    Card *pCard = (Card *) malloc(sizeof(Card));
    if ((fp = fopen(self->filepath, "rb")) == NULL) { return 0; }
    while (!feof(fp)) {
        if (fread(pCard, sizeof(Card), 1, fp) != 0) nIndex++;
    }
    fclose(fp);
    free(pCard);
    return nIndex;
}

int CardFile_Exist(struct CardFile *self, char *pNum) {
    FILE *fp = NULL;  // 文件结构体指针
    char aName[19] = {0};   // 存放读取出的卡号
    if ((fp = fopen(self->filepath, "rb")) == NULL) {
        return 0;
    }
    while (!feof(fp)) {    // 读取卡号，并比较卡号是否为当前查找的卡号
        if (fread(aName, sizeof(aName), 1, fp) != 0) {
            if (strcmp(aName, pNum) == 0) {
                fclose(fp);
                return 1;
            } else
                fseek(fp, sizeof(Card) - sizeof(aName), SEEK_CUR);
        }
    }
    fclose(fp);
    return 0;
}


CardFile CardFile_Init(char *filepath) {
    CardFile self;
    CardFile_InitVariable(&self, filepath);
    CardFile_InitFunction(&self);
    return self;
}

void CardFile_InitVariable(CardFile *self, char *filepath) {
    self->filepath = filepath;
}

void CardFile_InitFunction(CardFile *self) {
    self->SaveWithOverwrite = CardFile_SaveWithOverwrite;
    self->AppendCard = CardFile_AppendCard;
    self->ReadFileToLinkedList = CardFile_ReadFileToLinkedList;
    self->UpdateCard = CardFile_UpdateCard;
    self->GetCardCout = CardFile_GetCardCout;
    self->Exist = CardFile_Exist;
    self->Release = CardFile_Release;
}

void CardFile_Release(CardFile *self) {

}

int CardFile_SaveWithOverwrite(struct CardFile *self, LinkedList card_list) {
    // 文件结构体指针
    FILE *fp = NULL;
    // 以只写的模式打开文件
    if ((fp = fopen(self->filepath, "wb")) == NULL) {
        return -1;
    }
    //写入
    Card *pCard;
    for (int i = 0; i < card_list.count; i++) {
        card_list.Get(&card_list, i, (void **) &pCard);
        fwrite(pCard, sizeof(Card), 1, fp);
    }
    // 关闭文件
    fclose(fp);
    return 0;
}