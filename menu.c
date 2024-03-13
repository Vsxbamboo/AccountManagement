#include "menu.h"


void menu_outputMenu(){
    printf("----------菜单----------\n");
    printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n9.卡文件操作\n0.退出\n");
    printf("请选择菜单项编号(0~8):");
}
void menu_add(){
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
    clearthisline();
    printf("请输入密码(长度1~8):");
    scanf("%s",card.aPwd);
    clearthisline();
    card.nStatus=0;
    card.tStart=time(NULL);
    card.fTotalUse=0;
    card.tLast=card.tStart;
    card.tEnd=card.tStart;//暂时用来占位
    card.nUseCount=0;
    printf("请输入开卡金额(RMB):");
    scanf("%f",&card.fBalance);
    clearthisline();
    card.nDel=0;
    //
    printf("------添加的卡信息如下------\n");
    service_show(&card);
    service_add(&card);
}
void menu_query(){
    printf("----------查询卡----------\n");
    printf("请输入卡号(长度1~18):");
    char *aName[19];
    scanf("%s",aName);
    clearthisline();
    Card *cardp=service_query(aName);
    if(cardp==NULL){
        printf("该卡不存在\n");
    }else{
        service_show(cardp);
    }

}
void menu_exitApp(){}
void menu_logon(){}
void menu_settle(){}
void menu_annul(){}
void menu_addMoney(){}
void menu_refundMoney(){}

void menu_cardfile(){
    printf("欢迎进入卡文件交互界面\n");
    printf("1.保存现有卡信息\n");
    printf("2.读取并展示文件中的卡信息\n");
    printf("3.获取卡文件中卡信息的数量\n");
    printf("4.更新卡文件中一条卡信息\n");
    printf("5.根据卡号判断文件中是否存在该卡\n");
    printf("请选择功能:");
    int selection=0;
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            service_saveCard();
            break;
        case 2:
            service_readCard();
            break;
        case 3:
            printf("卡数量为:%d\n",service_getCount());
            break;
        case 4:
            printf("请输入需要更新的卡信息\n");
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
            printf("请输入卡号(长度1~18):");
            scanf("%s",card.aName);
            clearthisline();
            printf("请输入密码(长度1~8):");
            scanf("%s",card.aPwd);
            clearthisline();
            card.nStatus=0;
            card.tStart=time(NULL);
            card.fTotalUse=0;
            card.tLast=card.tStart;
            card.tEnd=card.tStart;//暂时用来占位
            card.nUseCount=0;
            printf("请输入开卡金额(RMB):");
            scanf("%f",&card.fBalance);
            clearthisline();
            card.nDel=0;
            printf("请输入插入位置:");
            int n;
            scanf("%d",&n);
            service_updateCard(&card,n);
            break;
        case 5:
            printf("请输入对应卡号:");
            char aName[19]={0};
            scanf("%s",aName);
            if(service_ifinFile(aName)==TRUE){
                printf("卡号存在\n");
            }else{
                printf("卡号不存在\n");
            }
            break;
        default:
            printf("输入选项错误\n");
    }

}
