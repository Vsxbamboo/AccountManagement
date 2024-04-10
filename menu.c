#include "menu.h"


void Menu_OutputMenu(Menu *self) {
    printf("----------菜单----------\n");
    printf("1.添加卡\n2.查询卡\n3.上机\n4.下机\n5.充值\n6.退费\n7.查询统计\n8.注销卡\n9.卡文件操作\n10.链表操作\n0.退出\n");
    printf("请选择菜单项编号(0~8):");
}

void Menu_Add(Menu *self) {
    Card card;
    printf("----------添加卡----------\n");
    Menu_InputCardNum(card.aName);
    Menu_InputCardPwd(card.aPwd);
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
    LogonInfo logon_info;
    int rcode = self->service.LogOnCard(&self->service, &temp_card, &logon_info);
    if(rcode == 1){
        printf("卡号\t余额\t上机时间\n");
        char pBuf[20] = {0};
        timeToString(logon_info.tLogon, pBuf);
        printf("%s\t%.2f\t%s\n", logon_info.aCardName, logon_info.fBalance, pBuf);
    }else{
        printf("上机失败\n");
        if(rcode==self->service.CARD_VERIFY_ERROR){
            printf("卡号或密码错误\n");
        }else if(rcode==self->service.CARD_CANNOT_LOGON){
            printf("该卡无法登录\n");
        }
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
    SettleInfo settle_info;
    int rcode =self->service.LogOutCard(&self->service,&temp_card,&settle_info);

    if(rcode==1){
        printf("卡号\t消费\t余额\t上机时间\t下机时间\n");
        char start_buf[20] = {0};
        char end_buf[20] = {0};
        timeToString(settle_info.tStart,start_buf);
        timeToString(settle_info.tEnd,end_buf);
        printf("%s\t%.2f\t%.2f\t%s\t%s\n",settle_info.aCardName,settle_info.fAmount,settle_info.fBalance,start_buf,end_buf);
    }else{
        printf("下机失败\n");
        if(rcode==self->service.CARD_VERIFY_ERROR){
            printf("卡号或密码错误\n");
        }else if(rcode==self->service.CARD_CANNOT_LOGOUT){
            printf("该卡无法下机，可能是卡的余额不足\n");
        }
    }
}

void Menu_Cancel(Menu *self) {
    printf("----------注销----------\n");
    Card temp_card;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("----------注销信息----------\n");
    MoneyInfo money_info;
    int rcode = self->service.CancelCard(&self->service, &temp_card,&money_info);
    //根据rcode输出
    if(rcode==1){
        printf("注销成功\n");
        printf("----------退费信息----------\n");
        printf("卡号\t金额\t余额\n");
        printf("%s\t%.2f\t%.2f\n", money_info.aCardName, money_info.fMoney, money_info.fBalance);
    }else if(rcode==self->service.CARD_VERIFY_ERROR){
        printf("卡号或密码错误\n");
    }else if(rcode==self->service.CARD_CANNOT_CANCEL){
        printf("卡状态异常，无法注销");
    }

}

void Menu_AddMoney(Menu *self) {
    printf("----------充值----------\n");
    //获取卡号和密码
    Card temp_card;
    MoneyInfo money_info;
    Money money;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("请输入充值金额(RMB):");
    scanf("%f", &money.fMoney);
    if(money.fMoney<=0){
        printf("充值金额无效\n");
        return;
    }
    strcpy(money.aCardName, temp_card.aName);
    money.tTime = time(NULL);
    money.nStatus=0;
    money.nDel=0;

    printf("----------充值信息----------\n");
    //验证卡能否充值
    int rcode = self->service.AddMoney(&self->service, &temp_card, &money,&money_info);
    if (rcode == 1) {
        //输出充值信息
        printf("卡号\t金额\t余额\n");
        printf("%s\t%.2f\t%.2f\n", money_info.aCardName, money_info.fMoney, money_info.fBalance);
    } else {
        printf("充值失败\n");
        if (rcode == self->service.CARD_VERIFY_ERROR) {
            printf("卡号或密码错误\n");
        }else if(rcode==self->service.CARD_BLANCE_ADJUST_ERROR){
            printf("余额修改失败\n");
        }else if(rcode==self->service.CARD_CANNOT_FUND){
            printf("卡状态异常,无法充值\n");
        }
    }
}

void Menu_RefundMoney(Menu *self) {
    printf("----------退费----------\n");
    //获取卡号和密码
    Card temp_card;
    MoneyInfo money_info;
    Money money;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("请输入退费金额(RMB):");
    scanf("%f", &money.fMoney);
    if(money.fMoney<=0){
        printf("退费金额无效\n");
        return;
    }
    strcpy(money.aCardName, temp_card.aName);
    money.tTime = time(NULL);
    money.nStatus=1;
    money.nDel=0;

    printf("----------退费信息----------\n");
    //验证卡能否退费
    int rcode = self->service.RefundMoney(&self->service, &temp_card, &money,&money_info);
    if (rcode == 1) {
        //输出充值信息
        printf("卡号\t金额\t余额\n");
        printf("%s\t%.2f\t%.2f\n", money_info.aCardName, money_info.fMoney, money_info.fBalance);
    } else {
        printf("退费失败\n");
        if (rcode == self->service.CARD_VERIFY_ERROR) {
            printf("卡号或密码错误\n");
        }else if(rcode==self->service.CARD_BLANCE_ADJUST_ERROR){
            printf("余额修改失败,请检查余额是否充足\n");
        }
    }
}

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
    self->Cancel = Menu_Cancel;
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






