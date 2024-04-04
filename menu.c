#include "menu.h"


void Menu_OutputMenu(Menu* self){
    printf("----------菜单----------\n");
    printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n9.卡文件操作\n10.链表操作\n0.退出\n");
    printf("请选择菜单项编号(0~8):");
}
void Menu_Add(Menu* self){
    Card card;
    printf("----------添加卡----------\n");
    printf("请输入卡号(长度1~18):");
    scanf("%s",card.aName);
    printf("请输入密码(长度1~8):");
    scanf("%s",card.aPwd);
    printf("请输入开卡金额(RMB):");
    scanf("%f",&card.fBalance);
    //其他变量取默认值
    card.nStatus=0;
    card.tStart=time(NULL);
    card.fTotalUse=0;
    card.tLast=card.tStart;
    card.tEnd=card.tStart;//暂时用来占位
    card.nUseCount=0;
    card.nDel=0;
    //添加
    int rcode=self->service.AddCard(&self->service,&card);
    //信息回显
    if(rcode==0){
        printf("------添加的卡信息如下------\n");
        self->service.ShowCard(&self->service,&card);
    }else{
        printf("添加卡失败\n");
    }


}
void Menu_Query(Menu* self){
    printf("----------查询卡----------\n");
    printf("请输入卡号(长度1~18):");
    char aName[19]={0};
    scanf("%s",aName);
    printf("请选择查询方式(1.精准查询,2.模糊查询):");
    char selection[20]={0};
    scanf("%s",selection);
    if(strcmp(selection,"1")==0){
        Card *cardp=self->service.QueryCard(&self->service,aName);
        if(cardp==NULL){
            printf("该卡不存在\n");
        }else{
            self->service.ShowCard(&self->service,cardp);
        }
    }else if(strcmp(selection,"2")==0){
        LinkedList result_list=self->service.FuzzQueryCard(&self->service,aName);
        if(result_list.count==0){
            printf("该卡不存在\n");
        }else{
            for(int i=0;i<result_list.count;i++){
                Card* cp;
                result_list.Get(&result_list, i, (void **) &cp);
                self->service.ShowCard(&self->service,cp);
            }
        }
        //释放结果内存
        result_list.Release(&result_list);
    }

}
void Menu_ExitApp(Menu* self){
    printf("感谢您的使用，再见！\n");
}
void Menu_LogOn(Menu* self){}
void Menu_Settle(Menu* self){}
void Menu_Annul(Menu* self){}
void Menu_AddMoney(Menu* self){}
void Menu_RefundMoney(Menu* self){}
//void Menu_CardFile(Menu* self){
//    printf("欢迎进入卡文件交互界面\n");
//    printf("1.保存现有卡信息\n");
//    printf("2.读取并展示文件中的卡信息\n");
//    printf("3.获取卡文件中卡信息的数量\n");
//    printf("4.更新卡文件中一条卡信息\n");
//    printf("5.根据卡号判断文件中是否存在该卡\n");
//    printf("请选择功能:");
//    int selection=0;
//    scanf("%d",&selection);
//    switch (selection) {
//        case 1:
//            service_saveCard();
//            break;
//        case 2:
//            service_readCard();
//            break;
//        case 3:
//            printf("卡数量为:%d\n",service_getCount());
//            break;
//        case 4:
//            printf("请输入需要更新的卡信息\n");
//            Card card;
//            printf("请输入卡号(长度1~18):");
//            scanf("%s",card.aName);
//            printf("请输入密码(长度1~8):");
//            scanf("%s",card.aPwd);
//            card.nStatus=0;
//            card.tStart=time(NULL);
//            card.fTotalUse=0;
//            card.tLast=card.tStart;
//            card.tEnd=card.tStart;//暂时用来占位
//            card.nUseCount=0;
//            printf("请输入开卡金额(RMB):");
//            scanf("%f",&card.fBalance);
//            card.nDel=0;
//            printf("请输入插入位置:");
//            int n;
//            scanf("%d",&n);
//            service_updateCard(&card,n);
//            break;
//        case 5:
//            printf("请输入对应卡号:");
//            char aName[19]={0};
//            scanf("%s",aName);
//            if(service_ifinFile(aName)==TRUE){
//                printf("卡号存在\n");
//            }else{
//                printf("卡号不存在\n");
//            }
//            break;
//        default:
//            printf("输入选项错误\n");
//    }
//
//}

void Menu_LinkList(Menu* self){
    LinkedList demolist;
    int selection=-1;
    int* num=NULL;
    printf("请选择\n");
    printf("1.初始化链表\n2.插入\n3.删除\n4.查询\n5.释放\n6.展示链表\n");
    printf("选择:");
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            demolist=LinkedList_Init();
            break;
        case 2:
            printf("请输入数字:");
            num=(int*)malloc(sizeof (int));
            scanf("%d",num);
            demolist.Add(&demolist,&num);
            break;
        case 3:
            printf("请输入删除的位置:");
            num=(int*)malloc(sizeof (int));
            scanf("%d",num);
            demolist.Delete(&demolist,*num);
            free(num);
            num=NULL;
            break;
        case 4:
            printf("请输入查询的位置:");
            num=(int*)malloc(sizeof (int));
            scanf("%d",num);
            demolist.Get(&demolist,*num,(void*)num);
            printf("取得%d\n",*num);
            free(num);
            num=NULL;
            break;
        case 5:
            demolist.Release(&demolist);
            break;
        case 6:
            num=(int*)malloc(sizeof (int));
            for(int i=0;i<demolist.count;i++){
                demolist.Get(&demolist,i,(void*)num);
                printf("%d->",*num);
            }
            printf("\n");
            free(num);
            num=NULL;
            break;
        default:
            printf("无效输入");
    }
}






Menu Menu_Init(void){
    Menu self;
    Menu_InitVariable(&self);
    Menu_InitFunction(&self);
    return self;
}

void Menu_InitVariable(Menu* self){
    //调用成员变量的构造函数
    self->service=Service_Init();
}

void Menu_InitFunction(Menu* self){
    self->OutputMenu=Menu_OutputMenu;
    self->Add=Menu_Add;
    self->Query=Menu_Query;
    self->ExitApp=Menu_ExitApp;
    self->LogOn=Menu_LogOn;
    self->Settle=Menu_Settle;
    self->Annul=Menu_Annul;
    self->AddMoney=Menu_AddMoney;
    self->RefundMoney=Menu_RefundMoney;
//    self->CardFile=Menu_CardFile;
    self->LinkList=Menu_LinkList;
    self->Release=Menu_Release;
}

void Menu_Release(Menu* self){
    //析构成员变量
    self->service.Release(&self->service);
}







