#include "menu.h"


void outputMenu(){
    printf("----------�˵�----------\n");
    printf("1.��ӿ�\n2.��ѯ��\n3.�ϻ�\n4.�»�\n5.��ֵ\n6.�˷�\n7.��ѯͳ��\n8.ע����\n0.�˳�\n");
    printf("��ѡ��˵�����(0~8):");
}
void add(){
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
    printf("------��ӵĿ���Ϣ����------\n");
    service_show(&card);
    service_add(&card);
}
void query(){
    printf("----------��ѯ��----------\n");
    printf("�����뿨��(����1~18):");
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

