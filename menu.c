#include "menu.h"


void Menu_OutputMenu(Menu *self) {
    printf("----------�˵�----------\n");
    printf("1.��ӿ�\n2.��ѯ��\n3.�ϻ�\n4.�»�\n5.��ֵ\n6.�˷�\n7.��ѯͳ��\n8.ע����\n9.���ļ�����\n10.�������\n0.�˳�\n");
    printf("��ѡ��˵�����(0~8):");
}

void Menu_Add(Menu *self) {
    Card card;
    printf("----------��ӿ�----------\n");
    Menu_InputCardNum(card.aName);
    Menu_InputCardPwd(card.aPwd);
    printf("�����뿪�����(RMB):");
    scanf("%f", &card.fBalance);
    //��������ȡĬ��ֵ
    card.nStatus = 0;
    card.tStart = time(NULL);
    card.fTotalUse = 0;
    card.tLast = card.tStart;
    struct tm *tm_pointer= localtime(&card.tStart);
    tm_pointer->tm_year+=1;
    card.tEnd = mktime(tm_pointer);//Ĭ�ϼ�һ��
    card.nUseCount = 0;
    card.nDel = 0;
    //���
    int rcode = self->service.AddCard(&self->service, &card);
    //��Ϣ����
    if (rcode == 0) {
        printf("------��ӵĿ���Ϣ����------\n");
        self->service.ShowCard(&self->service, &card);
    } else {
        printf("��ӿ�ʧ��\n");
    }


}

void Menu_Query(Menu *self) {
    printf("----------��ѯ��----------\n");
    printf("�����뿨��(����1~18):");
    char aName[19] = {0};
    scanf("%s", aName);
    printf("��ѡ���ѯ��ʽ(1.��׼��ѯ,2.ģ����ѯ):");
    char selection[20] = {0};
    scanf("%s", selection);
    if (strcmp(selection, "1") == 0) {
        Card *cardp = self->service.QueryCard(&self->service, aName);
        if (cardp == NULL) {
            printf("�ÿ�������\n");
        } else {
            self->service.ShowCard(&self->service, cardp);
        }
    } else if (strcmp(selection, "2") == 0) {
        LinkedList result_list = self->service.FuzzQueryCard(&self->service, aName);
        if (result_list.count == 0) {
            printf("�ÿ�������\n");
        } else {
            for (int i = 0; i < result_list.count; i++) {
                Card *cp;
                result_list.Get(&result_list, i, (void **) &cp);
                self->service.ShowCard(&self->service, cp);
            }
        }
        //�ͷŽ���ڴ�
        result_list.Release(&result_list);
    }

}

void Menu_ExitApp(Menu *self) {
    printf("��л����ʹ�ã��ټ���\n");
}

void Menu_LogOn(Menu *self) {
    //����˵���
    printf("----------�ϻ�----------\n");
    //��ȡ���ź�����
    Card temp_card;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("----------�ϻ���Ϣ----------\n");
    //��֤���ܷ��ϻ�
    LogonInfo logon_info;
    int rcode = self->service.LogOnCard(&self->service, &temp_card, &logon_info);
    if(rcode == 1){
        printf("����\t���\t�ϻ�ʱ��\n");
        char pBuf[20] = {0};
        timeToString(logon_info.tLogon, pBuf);
        printf("%s\t%.2f\t%s\n", logon_info.aCardName, logon_info.fBalance, pBuf);
    }else{
        printf("�ϻ�ʧ��\n");
        if(rcode==self->service.CARD_VERIFY_ERROR){
            printf("���Ż��������\n");
        }else if(rcode==self->service.CARD_CANNOT_LOGON){
            printf("�ÿ��޷���¼\n");
        }
    }
}

void Menu_Settle(Menu *self) {
    //����˵���
    printf("----------�»�----------\n");
    //��ȡ���ź�����
    Card temp_card;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("----------�»���Ϣ----------\n");
    //��֤���ܷ��»�
    SettleInfo settle_info;
    int rcode =self->service.LogOutCard(&self->service,&temp_card,&settle_info);

    if(rcode==1){
        printf("����\t����\t���\t�ϻ�ʱ��\t�»�ʱ��\n");
        char start_buf[20] = {0};
        char end_buf[20] = {0};
        timeToString(settle_info.tStart,start_buf);
        timeToString(settle_info.tEnd,end_buf);
        printf("%s\t%.2f\t%.2f\t%s\t%s\n",settle_info.aCardName,settle_info.fAmount,settle_info.fBalance,start_buf,end_buf);
    }else{
        printf("�»�ʧ��\n");
        if(rcode==self->service.CARD_VERIFY_ERROR){
            printf("���Ż��������\n");
        }else if(rcode==self->service.CARD_CANNOT_LOGOUT){
            printf("�ÿ��޷��»��������ǿ�������\n");
        }
    }
}

void Menu_Cancel(Menu *self) {
    printf("----------ע��----------\n");
    Card temp_card;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("----------ע����Ϣ----------\n");
    MoneyInfo money_info;
    int rcode = self->service.CancelCard(&self->service, &temp_card,&money_info);
    //����rcode���
    if(rcode==1){
        printf("ע���ɹ�\n");
        printf("----------�˷���Ϣ----------\n");
        printf("����\t���\t���\n");
        printf("%s\t%.2f\t%.2f\n", money_info.aCardName, money_info.fMoney, money_info.fBalance);
    }else if(rcode==self->service.CARD_VERIFY_ERROR){
        printf("���Ż��������\n");
    }else if(rcode==self->service.CARD_CANNOT_CANCEL){
        printf("��״̬�쳣���޷�ע��");
    }

}

void Menu_AddMoney(Menu *self) {
    printf("----------��ֵ----------\n");
    //��ȡ���ź�����
    Card temp_card;
    MoneyInfo money_info;
    Money money;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("�������ֵ���(RMB):");
    scanf("%f", &money.fMoney);
    if(money.fMoney<=0){
        printf("��ֵ�����Ч\n");
        return;
    }
    strcpy(money.aCardName, temp_card.aName);
    money.tTime = time(NULL);
    money.nStatus=0;
    money.nDel=0;

    printf("----------��ֵ��Ϣ----------\n");
    //��֤���ܷ��ֵ
    int rcode = self->service.AddMoney(&self->service, &temp_card, &money,&money_info);
    if (rcode == 1) {
        //�����ֵ��Ϣ
        printf("����\t���\t���\n");
        printf("%s\t%.2f\t%.2f\n", money_info.aCardName, money_info.fMoney, money_info.fBalance);
    } else {
        printf("��ֵʧ��\n");
        if (rcode == self->service.CARD_VERIFY_ERROR) {
            printf("���Ż��������\n");
        }else if(rcode==self->service.CARD_BLANCE_ADJUST_ERROR){
            printf("����޸�ʧ��\n");
        }else if(rcode==self->service.CARD_CANNOT_FUND){
            printf("��״̬�쳣,�޷���ֵ\n");
        }
    }
}

void Menu_RefundMoney(Menu *self) {
    printf("----------�˷�----------\n");
    //��ȡ���ź�����
    Card temp_card;
    MoneyInfo money_info;
    Money money;
    Menu_InputCardNum(temp_card.aName);
    Menu_InputCardPwd(temp_card.aPwd);
    printf("�������˷ѽ��(RMB):");
    scanf("%f", &money.fMoney);
    if(money.fMoney<=0){
        printf("�˷ѽ����Ч\n");
        return;
    }
    strcpy(money.aCardName, temp_card.aName);
    money.tTime = time(NULL);
    money.nStatus=1;
    money.nDel=0;

    printf("----------�˷���Ϣ----------\n");
    //��֤���ܷ��˷�
    int rcode = self->service.RefundMoney(&self->service, &temp_card, &money,&money_info);
    if (rcode == 1) {
        //�����ֵ��Ϣ
        printf("����\t���\t���\n");
        printf("%s\t%.2f\t%.2f\n", money_info.aCardName, money_info.fMoney, money_info.fBalance);
    } else {
        printf("�˷�ʧ��\n");
        if (rcode == self->service.CARD_VERIFY_ERROR) {
            printf("���Ż��������\n");
        }else if(rcode==self->service.CARD_BLANCE_ADJUST_ERROR){
            printf("����޸�ʧ��,��������Ƿ����\n");
        }
    }
}

void Menu_CardFile(Menu *self) {
    CardFile demo_card_file = CardFile_Init("C:\\E\\c\\AccountManagement\\card.ams");
    int selection = -1;
    do {
        printf("----------���ļ���ʾ�˵�----------\n");
        printf("1.�������п���Ϣ\n");
        printf("2.��ȡ��չʾ�ļ��еĿ���Ϣ\n");
        printf("3.��ȡ���ļ��п���Ϣ������\n");
        printf("4.���¿��ļ���һ������Ϣ\n");
        printf("5.���ݿ����ж��ļ����Ƿ���ڸÿ�\n");
        printf("0.�˳��Ӳ˵�\n");
        printf("��ѡ����:");
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
                printf("������Ϊ:%d\n", demo_card_file.GetCardCout(&demo_card_file));
                break;
            case 4:
                printf("��������Ҫ���µĿ���Ϣ\n");
                Card card;
                printf("�����뿨��(����1~18):");
                scanf("%s", card.aName);
                printf("����������(����1~8):");
                scanf("%s", card.aPwd);
                printf("�����뿪�����(RMB):");
                scanf("%f", &card.fBalance);
                card.nStatus = 0;
                card.tStart = time(NULL);
                card.fTotalUse = 0;
                card.tLast = card.tStart;
                card.tEnd = card.tStart;//��ʱ����ռλ
                card.nUseCount = 0;
                card.nDel = 0;

                printf("���������λ��:");
                int n;
                scanf("%d", &n);
                demo_card_file.UpdateCard(&demo_card_file, n, &card);
                break;
            case 5:
                printf("�������Ӧ����:");
                char aName[19] = {0};
                scanf("%s", aName);
                if (demo_card_file.Exist(&demo_card_file, aName) == 1) {
                    printf("���Ŵ���\n");
                } else {
                    printf("���Ų�����\n");
                }
                break;
            case 0:
                printf("�����˳����ļ���ʾ�˵�...\n");
                break;
            default:
                printf("����ѡ�����\n");
        }
    } while (selection != 0);

}

void Menu_LinkList(Menu *self) {
    LinkedList demolist;
    int selection = -1;
    int *num = NULL;
    int index;
    do {
        printf("----------������ʾ�˵�----------\n");
        printf("1.��ʼ������\n"
               "2.����\n"
               "3.ɾ��\n"
               "4.��ѯ\n"
               "5.�ͷ�\n"
               "6.չʾ����\n"
               "0.�˳��Ӳ˵�\n");
        printf("ѡ��:");
        scanf("%d", &selection);
        switch (selection) {
            case 1:
                demolist = LinkedList_Init();
                break;
            case 2:
                printf("����������:");
                num = (int *) malloc(sizeof(int));
                scanf("%d", num);
                demolist.Add(&demolist, num);
                break;
            case 3:
                printf("������ɾ����λ��:");
                scanf("%d", &index);
                demolist.Delete(&demolist, index);
                break;
            case 4:
                printf("�������ѯ��λ��:");
                scanf("%d", &index);
                demolist.Get(&demolist, index, (void **) &num);
                printf("ȡ��%d\n", *num);
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
                printf("�����˳�������ʾ�˵�...\n");
                break;
            default:
                printf("��Ч����");
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
    //���ó�Ա�����Ĺ��캯��
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
    //������Ա����
    self->service.Release(&self->service);
}

void Menu_InputCardNum(char* aName){
    printf("�����뿨��(1~18):");
    scanf("%18s",aName);
}

void Menu_InputCardPwd(char* aPwd){
    printf("����������(1~8):");
    scanf("%8s",aPwd);
}






