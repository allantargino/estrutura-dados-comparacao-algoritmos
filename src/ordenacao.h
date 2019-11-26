#ifndef _ORDENACAO_H
#define _ORDENACAO_H

#include <algorithm>
#include <stdlib.h>

namespace ED {

	//Definições:
	template<typename T>
	class Ordenacao
	{
	public:
		static void heapSort(T *vet, unsigned int n);
		static void quickSort(T *valor, int esquerda, int direita);
		static void mergeSort(T *vet, unsigned int n);
		static void shellSort(T *vet, unsigned int n);
		static void sortCpp(T *vet, unsigned int n);
		static void quickSortC(T *vet, unsigned int n);
	private:
		static void troca(T &a, T &b);
		static void heapify(T *vet, unsigned int pai, unsigned int heapsize);
		static void build_heap(T *vet, unsigned int n);
		static void m_sort(T *vet, T *aux, unsigned int esq, unsigned int dir);
		static void merge(T *vet, T *aux, unsigned int esq, unsigned int meio, unsigned int dir);
		static int compare(const void * a, const void * b);
	};


	//Implementações:

	//Heap Sort:
	template<typename T>
	void Ordenacao<T>::troca(T &a, T &b){
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<typename T>
	void Ordenacao<T>::heapify(T* vet, unsigned int pai, unsigned int heapsize) {
		int fl, fr, imaior;
		while (true) {
			fl = (pai << 1) + 1; fr = fl + 1;
			if ((fl < heapsize) && (vet[fl] > vet[pai])) imaior = fl; else imaior = pai;
			if ((fr < heapsize) && (vet[fr] > vet[imaior])) imaior = fr; if (imaior != pai){
				troca(vet[pai], vet[imaior]);
				pai = imaior;
			}
			else break;
		}
	}

	template<typename T>
	void Ordenacao<T>::build_heap(T *vet, unsigned int n) {
		for (int i = (n >> 1) - 1; i >= 0; i--)
			heapify(vet, i, n);
	}

	template<typename T>
	void Ordenacao<T>::heapSort(T *vet, unsigned int n) {
		build_heap(vet, n);
		for (int t = n - 1; t > 0; t--) {
			troca(vet[0], vet[t]);
			heapify(vet, 0, t);
		}
	}

	//Quick Sort (Pivô Central):
	template<typename T>
	void Ordenacao<T>::quickSort(T *vet, int l, int r) {
		if (r <= l) return;
		int i, j;
		i = (l + r) / 2;
		T pivo = vet[i]; vet[i] = vet[l]; vet[l] = pivo;
		i = l; j = r;
		while (true) {
			while ((j > i) && (vet[j] > pivo)) j--;
			if (i == j) break;
			vet[i] = vet[j]; i++;
			while ((i < j) && (vet[i] < pivo)) i++;
			if (i == j) break;
			vet[j] = vet[i]; j--;
		}
		vet[i] = pivo;
		quickSort(vet, l, i - 1);
		quickSort(vet, i + 1, r);
	}

	//Merge Sort:
	template<typename T>
	void Ordenacao< T>::merge(T *vet, T *aux, unsigned int esq, unsigned int meio, unsigned int dir) {
		int i, j, k;
		i = k = esq; j = meio + 1;
		while ((i <= meio) && (j <= dir)) {
			if (vet[i] < vet[j]) aux[k++] = vet[i++];
			else aux[k++] = vet[j++];
		}
		while (i <= meio) aux[k++] = vet[i++];
		while (j <= dir) aux[k++] = vet[j++];
		while (esq <= dir) vet[esq] = aux[esq++];
	}

	template<typename T>
	void Ordenacao<T>::m_sort(T *vet, T *aux, unsigned int esq, unsigned int dir) {
		if (dir <= esq) return;
		int meio = (dir + esq) >> 1;
		m_sort(vet, aux, esq, meio);
		m_sort(vet, aux, meio + 1, dir);
		if (vet[meio] <= vet[meio + 1]) return;
		merge(vet, aux, esq, meio, dir);
	}

	template<typename T>
	void Ordenacao<T>::mergeSort(T *vet, unsigned int n) {
		T *aux = new T[n];
		m_sort(vet, aux, 0, n - 1);
		delete aux;
	}

	//Shell Sort (Pardons):
	template<typename T>
	void Ordenacao< T>::shellSort(T *vet, unsigned int n){
		int i, j, h, k = 0;
		int aux;
		int increments[] = { 217378076, 45806244, 9651787, 2034035, 428481, 90358, 19001, 4025, 836, 182, 34, 9, 1 };
		while (increments[k]>n) k++;
		do{
			h = increments[k++];
			for (i = h; i < n; i++){
				aux = vet[i]; // copia o elemento a ser inserido
				j = i - h;
				while ((j >= 0) && (aux < vet[j])){
					vet[j + h] = vet[j]; // desloca o elemento na subsequencia
					j -= h;
				}
				vet[j + h] = aux; // insere o elemento
			}
		} while (h != 1);
	}

	//Sort C++:
	template<typename T>
	void Ordenacao<T>::sortCpp(T *vet, unsigned int n){
		std::sort(vet, vet + n);
	}

	//Quick Sort C:
	template<typename T>
	int Ordenacao<T>::compare(const void * a, const void * b){
		return (*(T*)a - *(T*)b);
	}

	template<typename T>
	void Ordenacao<T>::quickSortC(T *vet, unsigned int n){
		qsort(vet, n, sizeof(T), compare);
	}
}
#endif