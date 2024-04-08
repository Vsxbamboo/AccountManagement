#include "menu.h"


void Menu_OutputMenu(Menu *self) {
    printf("----------菜单----------\n");
    printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n9.卡文件操作\n10.链表操作\n0.退出\n");
    printf("请选择菜单项编号(0~8):");
}

void Menu_Add(Menu *self) {
    Card card;
    printf("----------添加卡----------\n");
    printf("请输入卡号(长度1~18):");
    scanf("%s", card.aName);
    printf("请输入密码(长度1~8):");
    scanf("%s", card.aPwd);
    printf("请输入开卡金额(RMB):");
    scanf("%f", &card.fBalance);
    //其他变量取默认值
    card.nStatus = 0;
    card.tStart = time(NULL);
    card.fTotalUse = 0;
    card.tLast = card.tStart;
    struct tm *tm_pointer= localtime(&card.tStart);
    tm_pointer->tm_year+=1;
    card.tEnd = mktime(tm_pointer);//默认加一年
    card.nUseCount = 0;
    card.nDel = 0;
    //添加
    int rcode = self->service.AddCard(&self->service, &card);
    //信息回显
    if (rcode == 0) {
        printf("------添加的卡信息如下------\n");
        self->service.ShowCard(&self->service, &card);
    } else {
        printf("添加卡失败\n");
    }


}

void Menu_Query(Menu *self) {
    printf("----------查询卡----------\n");
    printf("请输入卡号(长度1~18):");
    char aName[19] = {0};
    scanf("%s", aName);
    printf("请选择查询方式(1.精准查询,2.模糊查询):");
    char selection[20] = {0};
    scanf("%s", selection);
    if (strcmp(selection, "1") == 0) {
        Card *cardp = self->service.QueryCard(&self->service, aName);
        if (cardp == NULL) {
            printf("该卡不存在\n");
        } else {
            self->service.ShowCard(&self->service, cardp);
        }
    } else if (strcmp(selection, "2") == 0) {
        LinkedList result_list = self->service.FuzzQueryCard(&self->service, aName);
        if (result_list.count == 0) {
            printf("该卡不存在\n");
        } else {
            for (int i = 0; i < result_list.count; i++) {
                Card *cp;
                result_list.Get(&result_list, i, (void **) &cp);
                self->service.ShowCard(&self->service, cp);
            }
        }
        //释放结果内存
        result_list.Release(&result_list);
    }

}

void Menu_ExitApp(Menu *self) {
    printf("感谢您的使用，再见！\n");
}

void Menu_LogOn(Menu *self) {
    //输出菜单项
    printf("----------上机----------\n");
    //获取卡号和密码
    Card temp_card;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("----------上机信息----------\n");
    //验证卡能否上机
    if(self->service.LogOnCard(&self->service,&temp_card)==1){
        printf("卡号\t余额\t上机时间\n");
        char pBuf[20] = {0};
        timeToString(temp_card.tLast,pBuf);
        printf("%s\t%.2f\t%s\n",temp_card.aName,temp_card.fBalance, pBuf);
    }else{
        printf("上机失败\n");
    }
}

void Menu_Settle(Menu *self) {
    //输出菜单项
    printf("----------下机----------\n");
    //获取卡号和密码
    Card temp_card;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("----------下机信息----------\n");
    //验证卡能否下机
    if(self->service.LogOutCard(&self->service,&temp_card)==1){
        printf("卡号\t余额\t上机时间\n");
        char pBuf[20] = {0};
        timeToString(temp_card.tLast,pBuf);
        printf("%s\t%.2f\t%s\n",temp_card.aName,temp_card.fBalance, pBuf);
    }else{
        printf("下机失败\n");
    }
}

void Menu_Annul(Menu *self) {}

void Menu_AddMoney(Menu *self) {}

void Menu_RefundMoney(Menu *self) {}

void Menu_CardFile(Menu *self) {
    CardFile demo_card_file = CardFile_Init("C:\\E\\c\\AccountManagement\\card.ams");
    int selection = -1;
    do {
        printf("----------卡文件演示菜单----------\n");
        printf("1.保存现有卡信息\n");
        printf("2.读取并展示文件中的卡信息\n");
        printf("3.获取卡文件中卡信息的数量\n");
        printf("4.更新卡文件中一条卡信息\n");
        printf("5.根据卡号判断文件中是否存在该卡\n");
        printf("0.退出子菜单\n");
        printf("请选择功能:");
        scanf("%d", &selection);
        switch (selection) {
            case 1:
                demo_card_file.SaveWithOverwrite(&demo_card_file, self->service.card_service.card_list);
                break;
            case 2:
                self->service.card_service.card_list.Release(&self->service.card_service.card_list);
                self->service.card_service.card_list = LinkedList_Init();
                demo_card_file.ReadFileToLinkedList(&demo_card_file, &self->service.card_service.card_list);
                for (int i = 0; i < self->service.card_service.card_list.count; i++) {
                    Card *cp;
                    self->service.card_service.card_list.Get(&self->service.card_service.card_list, i, (void **) &cp);
                    self->service.card_service.Show(&self->service.card_service, cp);
                }
                break;
            case 3:
                printf("卡数量为:%d\n", demo_card_file.GetCardCout(&demo_card_file));
                break;
            case 4:
                printf("请输入需要更新的卡信息\n");
                Card card;
                printf("请输入卡号(长度1~18):");
                scanf("%s", card.aName);
                printf("请输入密码(长度1~8):");
                scanf("%s", card.aPwd);
                printf("请输入开卡金额(RMB):");
                scanf("%f", &card.fBalance);
                card.nStatus = 0;
                card.tStart = time(NULL);
                card.fTotalUse = 0;
                card.tLast = card.tStart;
                card.tEnd = card.tStart;//暂时用来占位
                card.nUseCount = 0;
                card.nDel = 0;

                printf("请输入插入位置:");
                int n;
                scanf("%d", &n);
                demo_card_file.UpdateCard(&demo_card_file, n, &card);
                break;
            case 5:
                printf("请输入对应卡号:");
                char aName[19] = {0};
                scanf("%s", aName);
                if (demo_card_file.Exist(&demo_card_file, aName) == 1) {
                    printf("卡号存在\n");
                } else {
                    printf("卡号不存在\n");
                }
                break;
            case 0:
                printf("正在退出卡文件演示菜单...\n");
                break;
            default:
                printf("输入选项错误\n");
        }
    } while (selection != 0);

}

void Menu_LinkList(Menu *self) {
    LinkedList demolist;
    int selection = -1;
    int *num = NULL;
    int index;
    do {
        printf("----------链表演示菜单----------\n");
        printf("1.初始化链表\n"
               "2.插入\n"
               "3.删除\n"
               "4.查询\n"
               "5.释放\n"
               "6.展示链表\n"
               "0.退出子菜单\n");
        printf("选择:");
        scanf("%d", &selection);
        switch (selection) {
            case 1:
                demolist = LinkedList_Init();
                break;
            case 2:
                printf("请输入数字:");
                num = (int *) malloc(sizeof(int));
                scanf("%d", num);
                demolist.Add(&demolist, num);
                break;
            case 3:
                printf("请输入删除的位置:");
                scanf("%d", &index);
                demolist.Delete(&demolist, index);
                break;
            case 4:
                printf("请输入查询的位置:");
                scanf("%d", &index);
                demolist.Get(&demolist, index, (void **) &num);
                printf("取得%d\n", *num);
                num = NULL;
                break;
            case 5:
                demolist.Release(&demolist);
                break;
            case 6:
                for (int i = 0; i < demolist.count; i++) {
                    demolist.Get(&demolist, i, (void **) &num);
                    printf("%d->", *num);
                }
                printf("\n");
                num = NULL;
                break;
            case 0:
                printf("正在退出链表演示菜单...\n");
                break;
            default:
                printf("无效输入");
        }
    } while (selection != 0);

}


Menu Menu_Init(void) {
    Menu self;
    Menu_InitVariable(&self);
    Menu_InitFunction(&self);
    return self;
}

void Menu_InitVariable(Menu *self) {
    //调用成员变量的构造函数
    self->service = Service_Init();
}

void Menu_InitFunction(Menu *self) {
    self->OutputMenu = Menu_OutputMenu;
    self->Add = Menu_Add;
    self->Query = Menu_Query;
    self->ExitApp = Menu_ExitApp;
    self->LogOn = Menu_LogOn;
    self->Settle = Menu_Settle;
    self->Annul = Menu_Annul;
    self->AddMoney = Menu_AddMoney;
    self->RefundMoney = Menu_RefundMoney;
    self->CardFile = Menu_CardFile;
    self->LinkList = Menu_LinkList;
    self->Release = Menu_Release;
}

void Menu_Release(Menu *self) {
    //析构成员变量
    self->service.Release(&self->service);
}

void Menu_InputCardNum(char* aName){
    printf("请输入卡号(1~18):");
    scanf("%18s",aName);
}

void Menu_InputCardPwd(char* aPwd){
    printf("请输入密码(1~8):");
    scanf("%8s",aPwd);
}






