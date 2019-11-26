#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <string>
#include "ordenacao.h"
#include "randomCL.h"

using namespace std;

//Método auxiliar para resetar o vetor randômico:
void setRandomVec(RandomCL<unsigned long int> &gerador, unsigned long int *vec, int &n){
	gerador.reset();
	for (int k = 0; k < n; k++)
		vec[k] = gerador.nextr();
}

int main(){
	int n = 10000;
	const int count = 9;
	const int max = n * pow(3, (count - 1));
	unsigned long int *vec = new unsigned long int[max];

	//Saída para arquivo de texto:
	ofstream saida;
	saida.open("resultados.txt");
	saida << "\t";

	//Vetor para contabilizar os tempos de execução dos 6 algoritmos e 9 médias das variações de n
	int tempos[6][count];
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < count; j++)
			tempos[i][j] = 0;

	//Iterações Principais:
	for (int i = 0; i < count; i++)
	{
		saida << n << "\t";
		int tIni = 0, tFim = 0;

		for (int j = 0; j < 6; j++)
		{
			RandomCL<unsigned long int> gerador(j);

			//Heap:
			setRandomVec(gerador, vec, n);
			tIni = clock();
			ED::Ordenacao<unsigned long int>::heapSort(vec, n);
			tFim = clock();
			tempos[0][i] += ((double)(tFim - tIni) / CLOCKS_PER_SEC) * 1000;

			//Quick:
			setRandomVec(gerador, vec, n);
			tIni = clock();
			ED::Ordenacao<unsigned long int>::quickSort(vec, 0, n - 1);
			tFim = clock();
			tempos[1][i] += ((double)(tFim - tIni) / CLOCKS_PER_SEC) * 1000;

			//Merge:
			setRandomVec(gerador, vec, n);
			tIni = clock();
			ED::Ordenacao<unsigned long int>::mergeSort(vec, n);
			tFim = clock();
			tempos[2][i] += ((double)(tFim - tIni) / CLOCKS_PER_SEC) * 1000;

			//Shell:
			setRandomVec(gerador, vec, n);
			tIni = clock();
			ED::Ordenacao<unsigned long int>::shellSort(vec, n);
			tFim = clock();
			tempos[3][i] += ((double)(tFim - tIni) / CLOCKS_PER_SEC) * 1000;

			//Sort C++:
			setRandomVec(gerador, vec, n);
			tIni = clock();
			ED::Ordenacao<unsigned long int>::sortCpp(vec, n);
			tFim = clock();
			tempos[4][i] += ((double)(tFim - tIni) / CLOCKS_PER_SEC) * 1000;

			//Quick C:
			setRandomVec(gerador, vec, n);
			tIni = clock();
			ED::Ordenacao<unsigned long int>::quickSortC(vec, n);
			tFim = clock();
			tempos[5][i] += ((double)(tFim - tIni) / CLOCKS_PER_SEC) * 1000;
		}

		//Processa a média dos tempos:
		for (int j = 0; j < 6; j++)
			tempos[j][i] = tempos[j][i] / 6;

		//Aumenta o n pelo fator de 3
		n *= 3;
	}

	//Saída para arquivo de texto:
	string metodos[6] = { "Heap", "Quick", "Merge", "Shell", "SortC++", "QuickC" };
	saida << endl;
	for (int i = 0; i < 6; i++){
		saida << metodos[i] << "\t";
		for (int j = 0; j < count; j++)
			saida << tempos[i][j] << "\t";
		saida << endl;
	}
	saida.close();

	delete vec;
	return 0;
}
