
#include <iostream>
#include <complex>
#include <time.h>
#include "global.h"
#include "common.h"
#include "random.h"
#include "sa.h"

using namespace std;

double temperature = 100.0;	//��ʼ�¶�
double alpha       = 0.98;	//��ȴϵ��
double epsilon     = 0.001;	//��ֹ�¶�
int    L           = 500;	//ѭ������


//����õ�һ�������
void ComputeNext(int *current, int *next)
{
    for(int i = 0; i < nbrCities; i++)
		next[i] = current[i];

    int i1 = randomInteger(0,nbrCities - 1);
    int i2 = randomInteger(0,nbrCities - 1);
	while( i1 == i2)
		i2 = randomInteger(0,nbrCities - 1);

	SwapOperator(i1, i2, next); 
}

//ģ���˻�������
void SimulatedAnnealing(int *current)
{
	srand((unsigned)time(NULL));						//����һ��ʱ�������

	int    delta;										//Ŀ�꺯��ֵ�ĸı���
	double proba;										//�����ӽ���ʱ���
	int    *next = new int[nbrCities];					//�½��ű���
	int    distance = ComputeDistance(current);			//���㵱ǰĿ�꺯��ֵ

    //���¶�û�дﵽ��ֹ�¶�ʱ����ѭ��
    while(temperature > epsilon)
    {
		for(int l = 0; l < L; l++)
		{
			ComputeNext(current,next);					//����õ�һ�������
			delta = ComputeDistance(next) - distance;	//�õ��½��Ŀ�꺯��ֵ�뵱ǰĿ�꺯��ֵ�Ĳ�ֵ
			if(delta < 0)								//�����Ľ���
			{
				Accept(current,next);					//�����½�
				distance = delta + distance;			//���µ�ǰĿ�꺯��ֵ
				if( distance < bestValue )				//�����ǰ���������Ž���������Ž�
				{
					bestValue = distance;
					CopySolution(current,best);
				}
				cout << distance << endl;				//���һ���ҿ���
			}
			else										//�����û�иĽ�
			{
				proba = random01();						//���ܸ���
				if( proba < exp(-delta / temperature) )	//���������ܸ��ʹ�ʽ������ӽ�
				{
					Accept(current,next);
					distance = delta + distance;
					cout << distance << endl;			//���һ���ҿ���
				}
			}
		}
        temperature *=alpha;							//��ȴ����
    }
}