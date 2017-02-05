#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>

#include "global.h"
#include "common.h"
#include "random.h"
#include "ls.h"
#include "sa.h"
#include "tabu.h"
#include "ga.h"

using namespace std;

void Data_29();
void Data_EUC_2D_52();
void Data_ATT_48();

int main()
{
	clock_t start, finish;						//ʱ�����ڼ����㷨��ʱ��
	double  duration;							//�㷨��ʱ��duration = finish - start;

	cout << "������Ҫ�����������" << endl;
	cout << "A.29�����е����������м�����Է��������(bays29.dat)" << endl;
	cout << "B.52�����е������������Եѿ������������(berlin52.dat)" << endl;
	cout << "C.48�����е�������������att��ʽ������(att48.dat)" << endl;
	char dataName = ' ';
	cin >> dataName;
	while (dataName != 'A' && dataName != 'B' && dataName != 'C')
	{
		cout << "�����������������롣" << endl;
		cin >> dataName;
	}
	if (dataName == 'A')
		Data_29();								//29�����е����������м�����Է������
	else if (dataName == 'B')
		Data_EUC_2D_52();							//52�����е������������Եѿ����������
	else if (dataName == 'C')
		Data_ATT_48();							//48�����е�������������att��ʽ����

	int current[100] = {0};						//��ʼ��
	for(int i = 0; i < nbrCities; i++)
		current[i] = i;
	
	int distance = ComputeDistance(current);	//��ʼĿ�꺯��ֵ
	
	CopySolution(current, best);				//��ʼ������Ϊ��ʼ��
	
	bestValue = distance;						//��ʼ����Ŀ�꺯��ֵ��Ϊ��ʼĿ�꺯��ֵ
	
	start = clock();							//��ʼ��ʱ

	cout << "������ʹ�õ��㷨��" << endl;
	cout << "1.����������" << endl;
	cout << "2.���������㷨��" << endl;
	cout << "3.ģ���˻��㷨��" << endl;
	cout << "4.�Ŵ��㷨��" << endl;
	int algorithmName = 0;
	cin >> algorithmName;
	while (algorithmName != 1 && algorithmName != 2 && algorithmName != 3 && algorithmName != 4)
	{
		cout << "�����������������롣" << endl;
		cin >> algorithmName;
	}
	if (algorithmName == 1)
		LocalSearch(current);					//��������
	else if (algorithmName == 2)
		TabuSearch(current);					//���������㷨
	else if (algorithmName == 3)
		SimulatedAnnealing(current);			//ģ���˻��㷨
	else if (algorithmName == 4)
		GeneticAlgorithm();					//�Ŵ��㷨

	finish = clock();							//��ֹ��ʱ
	PrintSolution(best, bestValue);				//��ʾ���Ž�
	PrintSolution_txt(best, bestValue);			//���Ž������txt�ļ���
	duration = finish - start;					//���㻨��ʱ��
	cout << "duration : " << duration << endl;	//��ʾ����ʱ��
	system("PAUSE");							//ͣһ���ҿ���
	return 0;
};

void Data_29()
{
	vector<int> dist_vector;
	const char* filename = "bays29.dat";
	ifstream in(filename);
	while (in) 
	{
		int temp;
		in >> temp;
		dist_vector.push_back(temp);
	}
	dist_vector.pop_back();
	nbrCities = sqrt(double(dist_vector.size()));
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
			dist[i][j] = dist_vector[i * nbrCities + j];
}

void Data_EUC_2D_52()
{
	vector<int> dist_vector;
	const char* filename = "berlin52.dat";
	ifstream in(filename);
	while (in) 
	{
		int temp;
		in >> temp;
		dist_vector.push_back(temp);
	}
	dist_vector.pop_back();
	nbrCities = dist_vector.size()/2;
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
			dist[i][j] = sqrt(pow(double(dist_vector[i*2] - dist_vector[j*2]),2) + pow(double(dist_vector[i*2+1] - dist_vector[j*2+1]),2));
}

void Data_ATT_48()
{
	vector<int> dist_vector;
	const char* filename = "att48.dat";
	ifstream in(filename);
	while (in) 
	{
		int temp;
		in >> temp;
		dist_vector.push_back(temp);
	}
	dist_vector.pop_back();
	nbrCities = dist_vector.size()/2;
	double r12[48][48];
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
			r12[i][j] = sqrt((pow(double(dist_vector[i*2] - dist_vector[j*2]),2) + pow(double(dist_vector[i*2+1] - dist_vector[j*2+1]),2))/10);
	int t12[48][48];
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
			t12[i][j] = r12[i][j];
	int d12[48][48];
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
		{
			if (double(t12[i][j]) < r12[i][j])
				d12[i][j] = (int) t12[i][j] + 1;
			else
				d12[i][j] = (int) t12[i][j];
		}
	for(int i = 0; i < nbrCities; i++)
		for(int j = 0; j < nbrCities; j++)
			dist[i][j] = d12[i][j];
}

//srand((unsigned)time(NULL));