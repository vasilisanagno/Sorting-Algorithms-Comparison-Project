#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);
void QS1pL(int array[],int left,int right,long long int *comparisons,long long int *assignments);
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
	QS1pL(array,0,N-1,&comparisons,&assignments);
	end=clock();
	printf("QS1pL: Execution Time=%f sec, Comparisons=%lld, Assignments=%lld\n", ((double)end-start)/CLOCKS_PER_SEC,comparisons,assignments);

	free(array);
	return 0;
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void QS1pL(int array[],int left,int right,long long int *comparisons,long long int *assignments) {
	int i=left, j=right+1;
	int pivot=array[left];
	
	*assignments=*assignments+3;
	while (1) {
		while (array[++i]<pivot) {
			if (i>=right) {
				break;
			}
			(*comparisons)++;
		}
		(*comparisons)++;
		while (array[--j]>pivot) {
			if (j<=left) {
				break;
			}
			(*comparisons)++;
		}
		(*comparisons)++;
		if (i>=j) {
			break;
		}
		if (array[i]==array[j]) {
			(*comparisons)++;
			continue;
		}
		(*comparisons)++;
		swap(&array[i],&array[j]);
		*assignments=*assignments+3;
	}
	swap(&array[left],&array[j]);
	*assignments=*assignments+3;
	
	if (left<j-1) {
		QS1pL(array,left,j-1,comparisons,assignments);
	}
	if (j+1<right) {
		QS1pL(array,j+1,right,comparisons,assignments);
	}
}
