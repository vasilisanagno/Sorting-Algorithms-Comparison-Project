#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);
int median_pivot(int *array, int random1,int random2,int random3);
void QS1pM(int array[],int left,int right,long long int *comparisons,long long int *assignments);
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
	QS1pM(array,0,N-1,&comparisons,&assignments);
	end=clock();
	printf("QS1pM: Execution Time=%f sec, Comparisons=%lld, Assignments=%lld\n", ((double)end-start)/CLOCKS_PER_SEC,comparisons,assignments);

	free(array);
	return 0;
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void QS1pM(int array[],int left,int right,long long int *comparisons,long long int *assignments) {
	
	if (left<right) {
		int i=left, j=right+1, pivot;
		int random1=left + rand()%(right-left+1);
		int random2=left + rand()%(right-left+1);
		while (random1==random2 || random2>right) {
			random2=left + rand()%(right-left+1);
		}
		int random3=left + rand()%(right-left+1);
		while (random1==random3 || random2==random3 || random3>right) {
			random3=left + rand()%(right-left+1);
			if(left==right-1){
				break;
			}
		}
		int median=median_pivot(array,random1,random2,random3);
		if (median!=left) {
			swap(&array[left],&array[median]);
			*assignments=*assignments+3;
		}
		pivot=array[left];
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
		swap(&array[j],&array[left]);
		*assignments=*assignments+3;
		QS1pM(array,left,j-1,comparisons,assignments);
		QS1pM(array,j+1,right,comparisons,assignments);
	}
}
int median_pivot(int *array, int random1,int random2,int random3) {
	int median;
	
	if (array[random1]<array[random2]) {
		if (array[random1]>=array[random3]) {
			median=random1;
			return median;
		}
		if (array[random3]>=array[random2]) {
			median=random2;
		}
		else {
			median=random3;
		}
	}
	else {
		if (array[random2]>=array[random3]) {
			median=random2;
			return median;
		}
		if (array[random3]>=array[random1]) {
			median=random1;
		}
		else {
			median=random3;
		}
	}
	return median;
}
