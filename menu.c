#include "menu.h"


void menu_outputMenu(){
    printf("----------�˵�----------\n");
    printf("1.��ӿ�\n2.��ѯ��\n3.�ϻ�\n4.�»�\n5.��ֵ\n6.�˷�\n7.��ѯͳ��\n8.ע����\n9.���ļ�����\n0.�˳�\n");
    printf("��ѡ��˵�����(0~8):");
}
void menu_add(){
    Card card;
    /*
     * typedef struct Card
    {
    char 	aName[18];	//����
    char 	aPwd[8];	//����
    int 		nStatus;		//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
    time_t	tStart;		//����ʱ��
    time_t	tEnd;		//���Ľ�ֹʱ��
    float	fTotalUse;	//�ۼƽ��
    time_t	tLast;		//���ʹ��ʱ��
    int		nUseCount;	//ʹ�ô���
    float	fBalance;	//���
    int		nDel;		//ɾ����ʶ 0-δɾ����1-ɾ��
    }Card;
     * */
    printf("----------��ӿ�----------\n");
    printf("�����뿨��(����1~18):");
    scanf("%s",card.aName);
    printf("����������(����1~8):");
    scanf("%s",card.aPwd);
    card.nStatus=0;
    card.tStart=time(NULL);
    card.fTotalUse=0;
    card.tLast=card.tStart;
    card.tEnd=card.tStart;//��ʱ����ռλ
    card.nUseCount=0;
    printf("�����뿪�����(RMB):");
    scanf("%f",&card.fBalance);
    card.nDel=0;
    //
    printf("------��ӵĿ���Ϣ����------\n");
    service_show(&card);
    service_add(&card);
}
void menu_query(){
    printf("----------��ѯ��----------\n");
    printf("�����뿨��(����1~18):");
    char aName[19];
    scanf("%s",aName);
    printf("��ѡ���ѯ��ʽ(1.��׼��ѯ,2.ģ����ѯ):");
    char selection[20];
    scanf("%s",selection);
    if(strcmp(selection,"1")==0){
        Card *cardp=service_query(aName);
        if(cardp==NULL){
            printf("�ÿ�������\n");
        }else{
            service_show(cardp);
        }
    }else if(strcmp(selection,"2")==0){
        CardList resultList=service_fuzz_query(aName);
        if(resultList->next==NULL){
            printf("�ÿ�������\n");
        }else{
            while(resultList->next!=NULL){
                service_show(&resultList->next->data);
                resultList=resultList->next;
            }
        }
        //�ͷŽ���ڴ�
        CardList clear_pointer;
        while(resultList->next!=NULL){
            clear_pointer=resultList;
            resultList=resultList->next;
            free(clear_pointer);
        }
    }

}
void menu_exitApp(){
    service_clear();
}
void menu_logon(){}
void menu_settle(){}
void menu_annul(){}
void menu_addMoney(){}
void menu_refundMoney(){}

void menu_cardfile(){
    printf("��ӭ���뿨�ļ���������\n");
    printf("1.�������п���Ϣ\n");
    printf("2.��ȡ��չʾ�ļ��еĿ���Ϣ\n");
    printf("3.��ȡ���ļ��п���Ϣ������\n");
    printf("4.���¿��ļ���һ������Ϣ\n");
    printf("5.���ݿ����ж��ļ����Ƿ���ڸÿ�\n");
    printf("��ѡ����:");
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
            printf("������Ϊ:%d\n",service_getCount());
            break;
        case 4:
            printf("��������Ҫ���µĿ���Ϣ\n");
            Card card;
            /*
             * typedef struct Card
            {
            char 	aName[18];	//����
            char 	aPwd[8];	//����
            int 		nStatus;		//��״̬��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
            time_t	tStart;		//����ʱ��
            time_t	tEnd;		//���Ľ�ֹʱ��
            float	fTotalUse;	//�ۼƽ��
            time_t	tLast;		//���ʹ��ʱ��
            int		nUseCount;	//ʹ�ô���
            float	fBalance;	//���
            int		nDel;		//ɾ����ʶ 0-δɾ����1-ɾ��
            }Card;
             * */
            printf("�����뿨��(����1~18):");
            scanf("%s",card.aName);
            printf("����������(����1~8):");
            scanf("%s",card.aPwd);
            card.nStatus=0;
            card.tStart=time(NULL);
            card.fTotalUse=0;
            card.tLast=card.tStart;
            card.tEnd=card.tStart;//��ʱ����ռλ
            card.nUseCount=0;
            printf("�����뿪�����(RMB):");
            scanf("%f",&card.fBalance);
            card.nDel=0;
            printf("���������λ��:");
            int n;
            scanf("%d",&n);
            service_updateCard(&card,n);
            break;
        case 5:
            printf("�������Ӧ����:");
            char aName[19]={0};
            scanf("%s",aName);
            if(service_ifinFile(aName)==TRUE){
                printf("���Ŵ���\n");
            }else{
                printf("���Ų�����\n");
            }
            break;
        default:
            printf("����ѡ�����\n");
    }

}

void menu_linklist(){
    int selection=-1;
    int num,index;
    printf("��ѡ��\n");
    printf("1.��ʼ������\n2.����\n3.ɾ��\n4.��ѯ\n5.�ͷ�\n6.չʾ����\n");
    printf("ѡ��:");
    scanf("%d",&selection);
    switch (selection) {
        case 1:
            ll_init();
            break;
        case 2:
            printf("���������ֺ�λ��:");
            scanf("%d %d",&num,&index);
            ll_insert(num,index);
            break;
        case 3:
            printf("������ɾ����λ��:");
            scanf("%d",&index);
            ll_del(index);
            break;
        case 4:
            printf("�������ѯ��λ��:");
            scanf("%d",&index);
            ll_get(index,&num);
            printf("ȡ��%d\n",num);
            break;
        case 5:
            ll_release();
            break;
        case 6:
            ll_show();
            break;
        default:
            printf("��Ч����");
    }
}