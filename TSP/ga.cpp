
#include <iostream>
#include <time.h>
#include "global.h"
#include "ga.h"
#include "random.h"
#include "common.h"

using namespace std;

int    individual[2*PopSize][MaxNumOfCities];				//��Ⱥ
int    fitness[2*PopSize];									//��ȺĿ�꺯��ֵ
double prob[PopSize];

int    Gen = 3000;											//ѭ������
double Pc  = 0.5;											//�������
double Pm  = 0.2;											//�������

//�����������
void GenerateRandomTour(int *tour) 
{
	int  numUnVisitedCities = nbrCities - 1;				//δ������г��еļ�����
	int *unVisitedCities    = new int[nbrCities];			//δ������г����б�

	//δ����Ľ��еĳ����б��ʼ��
	for(int i = 0; i < nbrCities; i++) 
    	unVisitedCities[i] = i;

	for(int i = 0; i < nbrCities; i++)						//���ܳ��и�����ѭ��
    {
	    int index = randomInteger(0, numUnVisitedCities--);	//�������һ������
      	tour[i] = unVisitedCities[index];					//���ó�����ӵ���ǰ��ĵ�ǰλ��
      	for(int j = index; j <= numUnVisitedCities; j++)	//��δ����ĳ����б���ɾ���ó���
      		unVisitedCities[j] = unVisitedCities[j+1];      	 
    }
};

//����Ŀ�꺯��ֵ
void ComputeFitness()
{
	int max = -1;
	for(int i = 0; i < PopSize; i++)
	{
		fitness[i] = ComputeDistance(individual[i]);		//����ÿ������������ܾ���
		max = fitness[i] > max ? fitness[i] : max;			//�ҳ���ǰ���е������ܾ������ֵ
		if( fitness[i] < bestValue )						//�ҳ���ǰ���е����Ž�
		{
			bestValue = fitness[i];
			CopySolution(individual[i],best);
			cout << bestValue << endl;
		}
	}

	max = max + 1;
	for(int i = 0; i < PopSize; i++)						//��fitness���������ܾ������ֵ�뵱ǰ�������ܾ���Ĳ�ֵ
		fitness[i] = max - fitness[i];
};

//�������̶ĵ�����
void BuildWheel()
{
	double sum = 0;
	for(int i = 0; i < PopSize; i++)						//������Ⱥÿ������Ŀ�꺯��ֵ֮��
		sum += fitness[i];
	prob[0] = (double)fitness[0] / (double)sum;				//��һ������ռ�ܺ͵ķ���
	for( int i = 1 ; i < PopSize ; i++ )					//����ÿ������ռ�ܺ͵��ۼƷ���
		prob[i] = prob[i-1] + fitness[i] / sum;
};

//���̶ķ�ʽѡȡһ������
int  SelectIndividual()
{
	double p = random01();
	if( p < prob[0] )
		return 0;
	if( p >= prob[PopSize - 1] )
		return (PopSize - 1);
	for( int i = 1 ; i < PopSize ; i++ )
		if( (p >= prob[i-1]) && (p < prob[i]) )
			return i;
	return -1;
};

//��lo��hi������
void PMX(int lo, int hi, int *tour1, int *tour2, int *newtour1, int *newtour2)
{
	int j, pos1, pos2;
	CopySolution(tour1, newtour1);
	CopySolution(tour2, newtour2);

	j = lo;
	while( j <= hi )
	{
		pos1  = FindCity(tour2[j], newtour1);
		pos2  = FindCity(tour1[j], newtour2);
		SwapOperator(j, pos1, newtour1);
		SwapOperator(j, pos2, newtour2);
		j++;
	}
};

//����
void Mutation()
{
	for(int i = 0; i < PopSize; i++)					//����Ⱥ��ÿ��������ѭ��
	{
		if( random01() < Pm )							//�������
		{
			int i1 = randomInteger(0,nbrCities - 1);	//�������������
			int i2 = randomInteger(0,nbrCities - 1);
			while( i1 == i2)
				i2 = randomInteger(0,nbrCities - 1);

			SwapOperator(i1, i2, individual[i]);		//�Խ���������λ�õ�������
		}
	}
};

//��ʼ��
void Initialize()
{
	for(int i = 0; i < PopSize; i++)		//����ʼ��Ⱥ����PopSize������
		GenerateRandomTour(individual[i]);
};

//ѡ��ͽ���
void SelectionAndCrossover()
{
	BuildWheel();										//�������̶ĵ�����
	for(int i = PopSize; i < 2*PopSize; i = i + 2)		
	{
		int father = SelectIndividual();				//���̶ķ�ʽѡȡһ������
		int mother = SelectIndividual();				//���̶ķ�ʽѡȡ��һ������
		
		if( random01() < Pc )							//������㽻�����
		{
			int lo = randomInteger(1, nbrCities - 2);	//�����������Ϊ����ε���ʼ�����ֹ��
			int hi = randomInteger(1, nbrCities - 2);
			while( lo == hi)
				hi = randomInteger(1, nbrCities - 2);
			int min = lo < hi ? lo : hi;
			int max = lo < hi ? hi : lo;
			lo = min;
			hi = max;
			//��lo��hi��γ��ȶ�father��mother������Ȼ��浽indevidual��
			PMX(lo, hi, individual[father], individual[mother], individual[i], individual[i+1]);
		}
		else											//��������㽻�����
		{
			CopySolution(individual[father], individual[i]  );
			CopySolution(individual[mother], individual[i+1]);
		}
	}

	for(int i = 0; i < PopSize; i++)					//����������Ⱥ
		CopySolution(individual[PopSize+i], individual[i]);
}

//�Ŵ��㷨������
void GeneticAlgorithm()
{
	srand((unsigned)time(NULL));	//����һ��ʱ�������

	Initialize();					//��ʼ��
	ComputeFitness();				//�����ʼ�����õ���Ⱥ��Ŀ�꺯��ֵ

	for(int g = 1; g <= Gen; g++)	//ѭ���ܴ���
	{
		SelectionAndCrossover();	//ѡ��ͽ���
		Mutation();					//����
		ComputeFitness();			//��������Ⱥ��Ӧÿ�������Ŀ�꺯��ֵ
	}
}