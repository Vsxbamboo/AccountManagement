#include "model.h"
#include <malloc.h>
#include <stdio.h>
#include "menu.h"

//��ʼ����������ȫ�ֱ������г�ʼ��
Status init();

int main() {
    //�����˵�
    Menu menu=Menu_Init();
    //ȫ�ֱ�����ʼ��
    if(init()!=0){
        printf("�����ʼ�����󣬼����˳�...\n");
        return 0;
    }
    //�����˵�ѡ��
    int nSelection=-1;
    //������ʾ��
    printf("\n��ӭ����Ʒѹ���ϵͳ\n");
    //����ѡ��˵�
    do{
        //���ѡ��
        menu.OutputMenu(&menu);
        //��ȡ�û�����
        scanf("%d",&nSelection);
        //�����û�����ִ�ж�Ӧ����
        switch (nSelection) {
            case 1://��ӿ�
                menu.Add(&menu);
                break;
            case 2://��ѯ��
                menu.Query(&menu);
                break;
            case 3://�ϻ�
                menu.LogOn(&menu);
                break;
            case 4://�»�
                menu.Settle(&menu);
                break;
            case 5://��ֵ
                menu.AddMoney(&menu);
                break;
            case 6://�˷�
                menu.RefundMoney(&menu);
                break;
            case 7://��ѯͳ��
                break;
            case 8://ע����
                break;
            case 9://��ʱ���ļ������˵�
                menu.CardFile(&menu);
                break;
            case 10://������ʾ�˵�
                menu.LinkList(&menu);
                break;
            case 0://�˳�
                menu.ExitApp(&menu);
                break;
            default://�Ƿ�ѡ���
                printf("����Ĳ˵���Ŵ���\n");
                break;
        }
        //ѡ��0�˳�
    }while(nSelection!=0);
    //����menu
    menu.Release(&menu);
    return 0;
}

Status init(){

    return 0;
}