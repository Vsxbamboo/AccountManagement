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
    clearthisline();
    printf("����������(����1~8):");
    scanf("%s",card.aPwd);
    clearthisline();
    card.nStatus=0;
    card.tStart=time(NULL);
    card.fTotalUse=0;
    card.tLast=card.tStart;
    card.tEnd=card.tStart;//��ʱ����ռλ
    card.nUseCount=0;
    printf("�����뿪�����(RMB):");
    scanf("%f",&card.fBalance);
    clearthisline();
    card.nDel=0;
    //
    printf("------��ӵĿ���Ϣ����------\n");
    service_show(&card);
    service_add(&card);
}
void menu_query(){
    printf("----------��ѯ��----------\n");
    printf("�����뿨��(����1~18):");
    char *aName[19];
    scanf("%s",aName);
    clearthisline();
    Card *cardp=service_query(aName);
    if(cardp==NULL){
        printf("�ÿ�������\n");
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
            clearthisline();
            printf("����������(����1~8):");
            scanf("%s",card.aPwd);
            clearthisline();
            card.nStatus=0;
            card.tStart=time(NULL);
            card.fTotalUse=0;
            card.tLast=card.tStart;
            card.tEnd=card.tStart;//��ʱ����ռλ
            card.nUseCount=0;
            printf("�����뿪�����(RMB):");
            scanf("%f",&card.fBalance);
            clearthisline();
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
