
#include <iostream>
#include "tabu.h"
#include "common.h"
#include "sort.h"

using namespace std;

int tenure = 15;//���ɳ���
int numberOfIterations = 400;//��������

int nbrOfCanSwaps;//�����ı�ĳ���
int tabulist[MaxNumOfCities][MaxNumOfCities];//���ɱ�
int canSwap[MaxNumOfCities*MaxNumOfCities][2];//�����ı�
int canSwapCost[MaxNumOfCities*MaxNumOfCities];//������Ŀ�꺯��ֵ��
int sortedIndex[MaxNumOfCities*MaxNumOfCities];//�����ı������

//����·����ӵ����ɱ���
void TabuMove(int city1, int city2)
{ 
	tabulist[city1][city2] += tenure;
    tabulist[city2][city1] += tenure;
}

//���ɱ������е�����1
void DecrementTabu()
{
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
			tabulist[i][j] -= (tabulist[i][j] <= 0 ? 0 : 1);
}

//�������������
int *GetBestNeighbour(int* current) 
{
	bool swap = false;
    int city1 = 0, city2 = 0;
	int *best = new int[nbrCities]; 
	CopySolution(current, best);
    int bestValue = ComputeDistance(best);

	int next[MaxNumOfCities];
	int nextValue;

	// �������� 
	nbrOfCanSwaps = 0;
    for(int i = 0; i < nbrCities - 1; i++) 
		for (int j = i + 1; j < nbrCities; j++) 
		{
			CopySolution(current, next);
            SwapOperator(i, j, next);
            nextValue = ComputeDistance(next);
			
			sortedIndex[nbrOfCanSwaps] = nbrOfCanSwaps;
			canSwapCost[nbrOfCanSwaps] = nextValue;
			canSwap[nbrOfCanSwaps][0]  = i;
			canSwap[nbrOfCanSwaps][1]  = j;
			nbrOfCanSwaps++;
		}

	sortNondecreasing(canSwapCost, sortedIndex, 0, nbrOfCanSwaps-1);//��С��������

	for(int n = 0; n < nbrOfCanSwaps; n++)
	{
		city1 = canSwap[sortedIndex[n]][0];
        city2 = canSwap[sortedIndex[n]][1];
		//���Ŀ�꺯��ֵ���Ľ��ˣ��򷵻�ֵ��Ϊ�ҵ��Ľ�
		if( (canSwapCost[sortedIndex[n]] < bestValue) && (tabulist[city1][city2] < tenure - 2) )
		{
			CopySolution(current, best);
			SwapOperator(city1, city2, best);
			bestValue = canSwapCost[sortedIndex[n]];
			cout << "C1  " ;
			PrintSolution(best, bestValue);
			swap = true;
			break;
		}
		//����ⲻ�ڽ��ɱ��У��򷵻�ֵ��Ϊ�ҵ��Ľ�
		else if( 0 == tabulist[city1][city2] )	
		{
			CopySolution(current, best);
			SwapOperator(city1, city2, best);
            bestValue = canSwapCost[sortedIndex[n]];
			cout << "C2  " ;
			PrintSolution(best, bestValue);
			swap = true;
			break;
		}
	}

	//û�ҵ����ԸĽ�Ŀ�꺯��ֵ�ĽⲢ�ҿ��нⶼ�ڽ��ɱ��У��򷵻�ֵ��Ϊ��������С�ĺ���ֵ��Ӧ�Ľ�
	if( !swap )									
	{
		city1 = canSwap[sortedIndex[0]][0];
        city2 = canSwap[sortedIndex[0]][1];
		CopySolution(current, best);
		SwapOperator(city1, city2, best);
        bestValue = canSwapCost[sortedIndex[0]];
		cout << "C3  " ;
		PrintSolution(best, bestValue);
	}
			
 	DecrementTabu();
    TabuMove(city1, city2);
	return best;
};

//��������������
void TabuSearch(int* current)
{
	int *next = new int[nbrCities];					//����һ��ָ�����ڴ洢�µĽ�

    for(int i = 0; i < nbrCities; i++)				//��ʼ�����ɱ�
		for(int j = 0; j < nbrCities; j++)
			tabulist[i][j] = 0;

	CopySolution(current, next);					//���Ƶ�ǰ�⵽next��
    for (int i = 0; i < numberOfIterations; i++)	//���Ƶ�������
	{
		next = GetBestNeighbour(next);				//�õ����������
        int nextValue = ComputeDistance(next);		//�����½��Ŀ�꺯��ֵ
        if (nextValue < bestValue)					//����ⱻ�Ľ�����������Ž�
		{
			bestValue = nextValue;
			CopySolution(next, best);
        }
    }
};