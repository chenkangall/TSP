
#include <iostream>
#include "ls.h"
#include "global.h"
#include "common.h"

using namespace std;

void LocalSearch(int *current)//��������
{
	int  distance = ComputeDistance(current);//���㵱ǰĿ�꺯��ֵ
	int  *next = new int[nbrCities];
	int  delta;
	bool improved = true;

	while( improved )
	{
		improved = false;
	    for(int i = 0; i < nbrCities - 1; i++)
			for(int j = i + 1; j < nbrCities; j++)
		{
			CopySolution(current, next);
			SwapOperator(i, j, next);//���򽻻�
			delta = ComputeDistance(next) - distance;
			if( delta < 0 )//����иĽ�
			{
				improved = true;
				Accept(current,next);//���½�
				distance = delta + distance;//����Ŀ�꺯��ֵ
				bestValue = distance;//��������ֵ
				CopySolution(current,best);//�������Ž�
				cout << distance << endl;//�����ǰĿ�꺯��ֵ
			}
		}
	}
};