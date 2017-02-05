
#include <iostream>
#include <fstream>

#include "global.h"
#include "common.h"

using namespace std;

int ComputeDistance(int *tour)//����Ŀ�꺯����ֵ���������ܾ��롣
{
	int distance = 0;
	for(int i = 0; i < nbrCities - 1; i++)
		distance += dist[tour[i]][tour[i+1]];
	distance += dist[tour[nbrCities-1]][tour[0]];
	return distance;
};

int  FindCity(int city, int *tour)//���ݳ��б���ڽ���Ѱ�ҳ��е�λ��
{
	int j = 0;
	while( tour[j] != city )
		j++;
	return j;
};

void SwapOperator(int city1, int city2, int *tour)//���򽻻�
{
	int temp = tour[city1];
    tour[city1] = tour[city2];
    tour[city2] = temp;
};

void Accept(int *current, int *newSol)//��newSol�滻��ǰ��
{
    for(int i = 0; i < nbrCities; i++)
		current[i] = newSol[i];
};

void CopySolution(int *from, int *to)//����from���Ƶ�to��
{
    for(int i = 0; i < nbrCities; i++)
		to[i] = from[i];
};

void PrintSolution(int *tour, int cost)//�����������Ļ
{
	cout << "cost : " << cost << ", solution :  ";
	for(int i = 0; i < nbrCities; i++)
		cout << tour[i] << "  ";
	cout << endl;
};

void PrintSolution_txt(int *tour, int cost)//����������ı��ĵ�
{
	char result[] = "result.txt";
	ofstream fout(result);
	fout << "cost : " << cost << endl << "solution :  " << endl;
	for(int i = 0; i < nbrCities; i++)
		fout << tour[i] << "\t";
	fout << endl;
};