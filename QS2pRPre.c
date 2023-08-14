#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void find_limits(int *array,int *pivots,int low,int high,int *max,int *min,int pivots_size,int array_size,long long int *comparisons);
void find_position(int *array,int pivot1,int pivot2,int low,int high,int *pos1,int *pos2,long long int *comparisons);
void QS1pL(int array[],int left,int right);
int *pick_pivots(int *array,int left,int right,int size);
void swap(int* a, int* b);
int partition(int* arr, int low, int high, int* lp,long long int *comparisons,long long int *assignments);
void QS2pR(int array[],int low,int high,long long int *comparisons,long long int *assignments);
void QS2pRPre(int array[],int **pivots,int low,int high,int *pivots_size,long long int *comparisons,long long int *assignments,int array_size);
int main(int argc,char *argv[]) {
	int *array, N, i,start, end, *pivots, size;
	long long int  comparisons=0, assignments=0;
	
	srand(time(NULL));
	
	scanf("%d", &N);
	size=sqrt(N);
	array=(int *)malloc(sizeof(int)*N);
	if (array==NULL) {
		return -1;
	}
	for (i=0; i<N; i++) {
		array[i]=rand()%(2*N+1);
	}
	pivots=pick_pivots(array,0,N-1,size);
	if (pivots==NULL) {
		return -1;
	}
	QS1pL(pivots,0,size-1);

	start=clock();
	QS2pRPre(array,&pivots,0,N-1,&size,&comparisons,&assignments,N);
	end=clock();
	printf("QS2pRPre: Execution Time=%f sec, Comparisons=%lld, Assignments=%lld\n", ((double)end-start)/CLOCKS_PER_SEC,comparisons,assignments);

	free(pivots);
	free(array);
	return 0;
}
int *pick_pivots(int *array,int left,int right,int size) {
	int i, random, now_size=0, j=-1, *pivots=(int *)malloc(sizeof(int)*size), pivot;
	
	if (pivots==NULL) {
		return NULL;
	}
	for (i=0; i<size; i++) {
		random=left + rand()%(right-left+1);
		while (1) {
			while ((j!=-1&&j!=0)&&pivots[--j]!=random);
			if(j==-1||(j==0&&pivots[j]!=random)) {
				break;
			}
			else {
				random=left + rand()%(right-left+1);
				j=now_size;
			}
		}
		pivots[now_size]=random;
		now_size++;
		j=now_size;
	}
	for (i=0; i<size; i++) {
		pivot=pivots[i];
		pivots[i]=array[pivot];
	}
	return pivots;
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void QS2pR(int* array,int low, int high,long long int *comparisons,long long int *assignments) {
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
void QS2pRPre(int array[],int **pivots,int low,int high,int *pivots_size,long long int *comparisons,long long int *assignments,int array_size) {
	if (low < high) {
		int lp, rp;
		int pos1=-1,pos2=-1,max=-1,min=-1,random1, random2;
		if ((low!=0||high!=array_size-1)&&*pivots_size!=0) {
			find_limits(array,*pivots,low,high,&max,&min,*pivots_size,array_size,comparisons);
			if (min<max) {
				random1=min + rand()%(max-min+1);
				random2=min + rand()%(max-min+1);
				while (random1==random2) {
					random1=min + rand()%(max-min+1);
				}
			}
			else {
				if (min!=max) {
					random1=max + rand()%(min-max+1);
					random2=max + rand()%(min-max+1);
					while (random1==random2) {
						random1=max + rand()%(min-max+1);
					}
				}
			}
		}
		else {
			if (*pivots_size!=0) {
				min=0;
				max=1;
				random1=rand()%(*pivots_size);
				random2=rand()%(*pivots_size);
				while (random1==random2) {
					random1=rand()%(*pivots_size);
				}
			}
		}
		if ((*pivots_size!=0&&min!=max)&&min!=-1&&max!=-1) {
			find_position(array,(*pivots)[random1],(*pivots)[random2],low,high,&pos1,&pos2,comparisons);
		}
		else {
			pos1=-2;
			pos2=-2;
		}
		if (*pivots_size!=0&&(pos1!=-2&&pos2!=-2)&&(min!=max)) {
			if (random1>random2) {
				for (int k=random2+1; k<*pivots_size; k++) {
					(*pivots)[k-1]=(*pivots)[k];
					if ((*pivots)[k]==random1&&*pivots_size>2) {
						(*pivots)[k-1]=(*pivots)[k+1];
					}
				}
				*pivots_size=*pivots_size-2;
				*pivots=(int *)realloc(*pivots,sizeof(int)*(*pivots_size));
			}
			random1=pos1;
			random2=pos2;
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
			QS2pRPre(array,pivots, low, lp - 1,pivots_size,comparisons,assignments,array_size);
			QS2pRPre(array,pivots, lp + 1, rp - 1,pivots_size,comparisons,assignments,array_size);
			QS2pRPre(array,pivots, rp + 1, high,pivots_size,comparisons,assignments,array_size);
		}
		else {
			QS2pR(array,low, high,comparisons,assignments);
		}
	}
}
void QS1pL(int array[],int left,int right) {
	int i=left, j=right+1;
	int pivot=array[left];
	
	while (1) {
		while (array[++i]<pivot) {
			if (i>=right) {
				break;
			}
		}
		while (array[--j]>pivot) {
			if (j<=left) {
				break;
			}
		}
		if (i>=j) {
			break;
		}
		if (array[i]==array[j]) {
			continue;
		}
		swap(&array[i],&array[j]);
	}
	swap(&array[left],&array[j]);
	
	if (left<j-1) {
		QS1pL(array,left,j-1);
	}
	if (j+1<right) {
		QS1pL(array,j+1,right);
	}
}
void find_position(int *array,int pivot1,int pivot2,int low,int high,int *pos1,int *pos2,long long int *comparisons) {
	
	
	for (int i=low; i<=high; i++) {
		if (pivot1==array[i]&&*pos1==-1) {
			*pos1=i;
		}
		if (pivot2==array[i]&&*pos2==-1) {
			*pos2=i;
		}
		if (*pos1!=-1&&*pos2!=-1) {
			break;
		}
		*comparisons=*comparisons+2;
	}
	if (*pos1==-1||*pos2==-1) {
		*pos1=-2;
		*pos2=-2;
	}
}
void find_limits(int *array,int *pivots,int low,int high,int *max,int *min, int pivots_size,int array_size,long long int *comparisons) {
	int flag1=0, i, flag2=0;
	
	if (low==0) {
		*min=0;
		*max=high+1;
		for (i=0; i<pivots_size; i++) {
			(*comparisons)++;
			if (array[high+1]<=pivots[i]) {
				*max=i-1;
				break;
			}
		}
		if (*max==high+1) {
			*max=i-1;
		}
		return;
	}
	if (high==array_size-1) {
		*max=pivots_size-1;
		for (i=0; i<pivots_size; i++) {
			(*comparisons)++;
			if (array[low-1]<=pivots[i]) {
				*min=i;
				break;
			}
		}
		return;
	}
	for (i=0; i<pivots_size; i++) {
		if (array[low-1]<=pivots[i]&&flag1==0) {
			*min=i;
			flag1=1;
		}
		if (array[high+1]<=pivots[i]&&flag2==0) {
			*max=i-1;
			flag2=1;
		}
		*comparisons=*comparisons+2;
		if (flag1==1&&flag2==1) {
			break;
		}
	}
	
}
