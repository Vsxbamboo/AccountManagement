#include "menu.h"


void outputMenu(){
    printf("----------菜单----------\n");
    printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n0.退出\n");
    printf("请选择菜单项编号(0~8):");
}
void add(){
    Card card;
    /*
     * typedef struct Card
{
    char 	aName[18];	//卡号
    char 	aPwd[8];	//密码
    int 		nStatus;		//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
    time_t	tStart;		//开卡时间
    time_t	tEnd;		//卡的截止时间
    float	fTotalUse;	//累计金额
    time_t	tLast;		//最后使用时间
    int		nUseCount;	//使用次数
    float	fBalance;	//余额
    int		nDel;		//删除标识 0-未删除，1-删除
}Card;
     * */
    printf("----------添加卡----------\n");
    printf("请输入卡号(长度1~18):");
    scanf("%s",card.aName);
    printf("请输入密码(长度1~8):");
    scanf("%s",card.aPwd);
    card.nStatus=0;
    card.tStart=time(NULL);
    card.fTotalUse=0;
    card.tLast=card.tStart;
    card.tEnd=card.tStart;//暂时用来占位
    card.nUseCount=0;
    printf("请输入开卡金额(RMB):");
    scanf("%f",&card.fBalance);
    card.nDel=0;
    printf("------添加的卡信息如下------\n");
    service_show(&card);
    service_add(&card);
}
void query(){
    printf("----------查询卡----------\n");
    printf("请输入卡号(长度1~18):");
    char *aName[19];
    scanf("%s",aName);
    Card card=cards[findCard(aName)];

    service_show(&card);
}
void exitApp(){}
void logon(){}
void settle(){}
void annul(){}
void addMoney(){}
void refundMoney(){}

