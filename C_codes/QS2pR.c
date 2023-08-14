#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);
int partition(int* arr, int low, int high, int* lp,long long int *comparisons,long long int *assignments);
void QS2pR(int array[],int low,int high,long long int *comparisons,long long int *assignments);
int main(int argc,char *argv[]) {
	int *array, N, i,start, end;
	long long int  comparisons=0, assignments=0;
	
	srand(time(NULL));
	
	scanf("%d", &N);
	array=(int *)malloc(sizeof(int)*N);
	if (array==NULL) {
		return -1;
	}
	for (i=0; i<N; i++) {
		array[i]=rand()%(2*N+1);
	}
	
	start=clock();
	QS2pR(array,0,N-1,&comparisons,&assignments);
	end=clock();
	printf("QS2pR: Execution Time=%f sec, Comparisons=%lld, Assignments=%lld\n", ((double)end-start)/CLOCKS_PER_SEC,comparisons,assignments);
	
	free(array);
	return 0;
}
 
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
 
void QS2pR(int* array, int low, int high,long long int *comparisons,long long int *assignments) {
	if (low < high) {
		int lp, rp;
		int random1=low + rand()%(high-low+1);
		int random2=low + rand()%(high-low+1);
		while (random1==random2) {
			random1=low + rand()%(high-low+1);
		}
		if ((random1>low&&random1<high)&&(random2>low&&random2<high)) {
			if (array[random1]>array[random2]) {
				swap(&array[random1], &array[high]);
				swap(&array[random2], &array[low]);
				*assignments=*assignments+6;
			}
			else {
				swap(&array[random1], &array[low]);
				swap(&array[random2], &array[high]);
				*assignments=*assignments+6;
			}
			(*comparisons)++;
		}
		else {
			if ((random1==high&&random2==low)||(random2==high&&random1==low)) {
				if (array[low]>array[high]) {
					swap(&array[low], &array[high]);
					*assignments=*assignments+3;
				}
				(*comparisons)++;
			}
			else {
				if (random1==low) {
					if (array[random1]<array[random2]) {
						swap(&array[random2],&array[high]);
						*assignments=*assignments+3;
					}
					else {
						swap(&array[random1],&array[high]);
						swap(&array[random2],&array[low]);
						*assignments=*assignments+6;
					}
					(*comparisons)++;
				}
				else {
					if (random1==high) {
						if (array[random2]<array[random1]) {
							swap(&array[random2],&array[low]);
							*assignments=*assignments+3;
						}
						else {
							swap(&array[random1],&array[low]);
							swap(&array[random2],&array[high]);
							*assignments=*assignments+6;
						}
						(*comparisons)++;
					}
					else {
						if (random2==low) {
							if (array[random2]<array[random1]) {
								swap(&array[random1],&array[high]);
								*assignments=*assignments+3;
							}
							else {
								swap(&array[random2],&array[high]);
								swap(&array[random1],&array[low]);
								*assignments=*assignments+6;
							}
							(*comparisons)++;
						}
						else {
							if (random2==high) {
								if (array[random2]>array[random1]) {
									swap(&array[random1],&array[low]);
									*assignments=*assignments+3;
								}
								else {
									swap(&array[random2],&array[low]);
									swap(&array[random1],&array[high]);
									*assignments=*assignments+6;
								}
								(*comparisons)++;
							}
						}
					}
				}
			}
		}
		rp = partition(array, low, high, &lp,comparisons,assignments);
		QS2pR(array, low, lp - 1,comparisons,assignments);
		QS2pR(array, lp + 1, rp - 1,comparisons,assignments);
		QS2pR(array, rp + 1, high,comparisons,assignments);
	}
}
 
int partition(int* arr, int low, int high, int* lp,long long int *comparisons,long long int *assignments) {
	
	int j = low + 1;
	int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
	while (k <= g) {
 
		if (arr[k] < p) {
			swap(&arr[k], &arr[j]);
			*assignments=*assignments+3;
			j++;
		}
		else {
			if (arr[k] >= q) {
				while (arr[g] > q && k < g) {
					g--;
					(*comparisons)++;
				}
				swap(&arr[k], &arr[g]);
				*assignments=*assignments+3;
				g--;
				if (arr[k] < p) {
					swap(&arr[k], &arr[j]);
					*assignments=*assignments+3;
					j++;
				}
				*comparisons=*comparisons+2;
			}
			(*comparisons)++;
		}
		(*comparisons)++;
		k++;
	}
	j--;
	g++;
 
	swap(&arr[low], &arr[j]);
	swap(&arr[high], &arr[g]);
	*assignments=*assignments+6;
 
	*lp = j;
	
	return g;
}
 
