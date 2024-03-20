//
// Created by vsx on 2024/3/6.
//

#include "card_file.h"


/*************************************************
[函数名] saveCard
[功能]  将卡信息保存到文件中
[参数]  pCard：需要保存到卡信息中的卡结构体指针
        pPath：保存卡信息的文件路径
[返回值] int型，TRUE表示成功，FALSE表示失败
*************************************************/
int saveCard(const Card* pCard, const char* pPath)
{
  FILE* fp = NULL;   // 文件结构体指针

  // 以追加的模式打开文件，如果打开失败，则以只写的模式打开文件
  if((fp = fopen(pPath,"ab")) == NULL)
  {
    if((fp = fopen(pPath,"wb")) == NULL)
    {
      return FALSE;
    }
  }

  fwrite(pCard, sizeof(Card), 1, fp);

  // 关闭文件
  fclose(fp);
  return TRUE;
}

int readCard()
{
    Card temp;
    FILE* fp = NULL;  // 文件结构体指针

    // 以只读的方式打开文件
    if((fp = fopen(CARDPATH, "rb")) == NULL)
    {
        return FALSE;
    }
    cardlength=0;
    while(!feof(fp))
    {
        if(fread(&temp, sizeof(Card), 1, fp) != 0)
        {
            /*
            cards[cardlength]=temp;
            cardlength++;
             */
            CardList temp_pointer=cardList;
            while(temp_pointer->next!=NULL){
                temp_pointer=temp_pointer->next;
            }
            temp_pointer->next->data=temp;
            temp_pointer->next->next=NULL;
        }
    }
    fclose(fp);
    return 0;
}

/*************************************************
[功能]  更新卡信息文件中的一条卡信息
[参数]  pCard:更新后的卡内容。   pPath:卡信息文件的路径
     nIndex:需要更新的卡信息在文件中的序号
*************************************************/
int updateCard(const Card* pCard, const char* pPath, int nIndex)
{  FILE* fp = NULL;    // 文件指针
    int nLine = 0;      // 文件卡信息数
    long lPosition = 0; // 文件位置标记
    Card bBuf;
    if((fp = fopen(pPath, "rb+")) == NULL)
    {    return FALSE;  }
    while((!feof(fp)) && (nLine < nIndex-1))
    {    if(fread(&bBuf, sizeof(Card), 1, fp) != 0)
        {      // 获取文件标识位置
            lPosition = ftell(fp);      nLine++;
        }
    }
    fseek(fp, lPosition, 0);
    fwrite(pCard, sizeof(Card), 1, fp);
    fclose(fp);
    return TRUE;
}


/*************************************************
[函数名] getCardCount
[功能]  获取卡信息文件中，卡信息数量
[参数]  pPath：卡信息文件的路径
[返回值] int:卡信息文件中的卡信息数量
*************************************************/
int getCardCount(const char* pPath)
{  FILE* fp = NULL;  // 文件指针
    int nIndex = 0;   // 卡信息数量
    Card* pCard = (Card*)malloc(sizeof(Card));
    if((fp = fopen(pPath, "rb")) == NULL)
    {    return 0; }
    while(!feof(fp))
    {
        if(fread(pCard, sizeof(Card), 1, fp) != 0)  nIndex++;
    }
    fclose(fp);
    free(pCard);
    return nIndex;
}



/*************************************************
[功能]  根据卡号判断卡是否存在
[参数]  pNum:卡号    pPath:卡信息文件的路径
[返回值] int: TRUE 表示卡存在，FALSE 表示卡不存在
*************************************************/
int isExsit(const char* pNum, const char* pPath)
{
    FILE* fp = NULL;  // 文件结构体指针
    char aName[19]={0};   // 存放读取出的卡号
    if((fp = fopen(pPath, "rb")) == NULL)
    {
        return FALSE;
    }
    while(!feof(fp))
    {    // 读取卡号，并比较卡号是否为当前查找的卡号
        if(fread(aName, sizeof(aName), 1, fp) != 0)
        {
            if(strcmp(aName, pNum) == 0)
            {
            fclose(fp);
            return TRUE;
            }
            else
                fseek(fp, sizeof(Card) - sizeof(aName), SEEK_CUR);
        }
    }
    fclose(fp);
    return FALSE;
}


