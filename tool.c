//
// Created by vsx on 2024/3/6.
//

#include "tool.h"

/*
 * 将time_t类型转换为字符串，字符串格式为“年-月-日 时:分”
 * */
void timeToString(time_t t,char* pBuf){
    struct tim *timeinfo;
    timeinfo= localtime(&t);
    strftime(pBuf,20,"%Y-%m-%d %H:%M",timeinfo);
}

time_t stringToTime(char *pTime){
    struct tm tml;
    time_t timel;
    sscanf(pTime,"%d-%d-%d %d:%d",&tml.tm_year,&tml.tm_mon,&tml.tm_mday,&tml.tm_hour,&tml.tm_min);
    tml.tm_year-=1900;
    tml.tm_mon-=1;
    tml.tm_sec=0;
    tml.tm_isdst=-1;
    timel=mktime(&tml);
    return timel;
}

void clearthisline(){
    char buf;
    do{
        scanf("%c",&buf);
    }while(buf!='\n');
}

/*
 * str类型的模糊查询，要求str以0结尾
 * 在a中找有没有等于b的子串
 * 存在返回1，不存在返回0
 * */
int fuzzstrcmp(char *a,char *b){
    int alen=strlen(a);
    int blen=strlen(b);
    if(blen>alen){
        return 0;
    }else if(alen==blen){
        return strcmp(a,b)==0;
    }else{//alen>blen
        for(int i=0;i<=alen-blen;i++){
            for(int j=0;j<blen;j++){
                if(a[i+j]!=b[j]){
                    return 0;
                }
            }
        }
        return 1;
    }
}