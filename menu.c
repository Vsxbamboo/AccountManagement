#include "menu.h"


void Menu_OutputMenu(Menu* self){
    printf("----------�˵�----------\n");
    printf("1.��ӿ�\n2.��ѯ��\n3.�ϻ�\n4.�»�\n5.��ֵ\n6.�˷�\n7.��ѯͳ��\n8.ע����\n9.���ļ�����\n10.�������\n0.�˳�\n");
    printf("��ѡ��˵�����(0~8):");
}
void Menu_Add(Menu* self){
    Card card;
    printf("----------��ӿ�----------\n");
    printf("�����뿨��(����1~18):");
    scanf("%s",card.aName);
    printf("����������(����1~8):");
    scanf("%s",card.aPwd);
    printf("�����뿪�����(RMB):");
    scanf("%f",&card.fBalance);
    //��������ȡĬ��ֵ
    card.nStatus=0;
    card.tStart=time(NULL);
    card.fTotalUse=0;
    card.tLast=card.tStart;
    card.tEnd=card.tStart;//��ʱ����ռλ
    card.nUseCount=0;
    card.nDel=0;
    //���
    int rcode=self->service.AddCard(&self->service,&card);
    //��Ϣ����
    if(rcode==0){
        printf("------��ӵĿ���Ϣ����------\n");
        self->service.ShowCard(&self->service,&card);
    }else{
        printf("��ӿ�ʧ��\n");
    }


}
void Menu_Query(Menu* self){
    printf("----------��ѯ��----------\n");
    printf("�����뿨��(����1~18):");
    char aName[19]={0};
    scanf("%s",aName);
    printf("��ѡ���ѯ��ʽ(1.��׼��ѯ,2.ģ����ѯ):");
    char selection[20]={0};
    scanf("%s",selection);
    if(strcmp(selection,"1")==0){
        Card *cardp=self->service.QueryCard(&self->service,aName);
        if(cardp==NULL){
            printf("�ÿ�������\n");
        }else{
            self->service.ShowCard(&self->service,cardp);
        }
    }else if(strcmp(selection,"2")==0){
        LinkedList result_list=self->service.FuzzQueryCard(&self->service,aName);
        if(result_list.count==0){
            printf("�ÿ�������\n");
        }else{
            for(int i=0;i<result_list.count;i++){
                Card* cp;
                result_list.Get(&result_list, i, (void **) &cp);
                self->service.ShowCard(&self->service,cp);
            }
        }
        //�ͷŽ���ڴ�
        result_list.Release(&result_list);
    }

}
void Menu_ExitApp(Menu* self){
    printf("��л����ʹ�ã��ټ���\n");
}
void Menu_LogOn(Menu* self){}
void Menu_Settle(Menu* self){}
void Menu_Annul(Menu* self){}
void Menu_AddMoney(Menu* self){}
void Menu_RefundMoney(Menu* self){}
//void Menu_CardFile(Menu* self){
//    printf("��ӭ���뿨�ļ���������\n");
//    printf("1.�������п���Ϣ\n");
//    printf("2.��ȡ��չʾ�ļ��еĿ���Ϣ\n");
//    printf("3.��ȡ���ļ��п���Ϣ������\n");
//    printf("4.���¿��ļ���һ������Ϣ\n");
//    printf("5.���ݿ����ж��ļ����Ƿ���ڸÿ�\n");
//    printf("��ѡ����:");
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
//            printf("������Ϊ:%d\n",service_getCount());
//            break;
//        case 4:
//            printf("��������Ҫ���µĿ���Ϣ\n");
//            Card card;
//            printf("�����뿨��(����1~18):");
//            scanf("%s",card.aName);
//            printf("����������(����1~8):");
//            scanf("%s",card.aPwd);
//            card.nStatus=0;
//            card.tStart=time(NULL);
//            card.fTotalUse=0;
//            card.tLast=card.tStart;
//            card.tEnd=card.tStart;//��ʱ����ռλ
//            card.nUseCount=0;
//            printf("�����뿪�����(RMB):");
//            scanf("%f",&card.fBalance);
//            card.nDel=0;
//            printf("���������λ��:");
//            int n;
//            scanf("%d",&n);
//            service_updateCard(&card,n);
//            break;
//        case 5:
//            printf("�������Ӧ����:");
//            char aName[19]={0};
//            scanf("%s",aName);
//            if(service_ifinFile(aName)==TRUE){
//                printf("���Ŵ���\n");
//            }else{
//                printf("���Ų�����\n");
//            }
//            break;
//        default:
//            printf("����ѡ�����\n");
//    }
//
//}

void Menu_LinkList(Menu* self){
    LinkedList demolist;
    int selection=-1;
    int* num=NULL;
    printf("��ѡ��\n");
    printf("1.��ʼ������\n2.����\n3.ɾ��\n4.��ѯ\n5.�ͷ�\n6.չʾ����\n");
    printf("ѡ��:");
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            demolist=LinkedList_Init();
            break;
        case 2:
            printf("����������:");
            num=(int*)malloc(sizeof (int));
            scanf("%d",num);
            demolist.Add(&demolist,&num);
            break;
        case 3:
            printf("������ɾ����λ��:");
            num=(int*)malloc(sizeof (int));
            scanf("%d",num);
            demolist.Delete(&demolist,*num);
            free(num);
            num=NULL;
            break;
        case 4:
            printf("�������ѯ��λ��:");
            num=(int*)malloc(sizeof (int));
            scanf("%d",num);
            demolist.Get(&demolist,*num,(void*)num);
            printf("ȡ��%d\n",*num);
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
            printf("��Ч����");
    }
}






Menu Menu_Init(void){
    Menu self;
    Menu_InitVariable(&self);
    Menu_InitFunction(&self);
    return self;
}

void Menu_InitVariable(Menu* self){
    //���ó�Ա�����Ĺ��캯��
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
    //������Ա����
    self->service.Release(&self->service);
}







