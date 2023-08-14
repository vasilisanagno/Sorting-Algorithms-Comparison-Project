#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void pick_positions(int *array,int random1, int random2,int random3,int *min,int *mid,int *max,long long int *comparisons);
int partition(int *array, int left, int right, int *lp,int *mp,long long int *comparisons,long long int *assignments);
void swap(int* a, int* b);
void QS3pR(int array[],int left,int right,long long int *comparisons,long long int *assignments);
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
	QS3pR(array,0,N-1,&comparisons,&assignments);
	end=clock();
	printf("QS3pR: Execution Time=%f sec, Comparisons=%lld, Assignments=%lld\n", ((double)end-start)/CLOCKS_PER_SEC,comparisons,assignments);
	
	free(array);
	return 0;
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
int partition(int *array, int left, int right, int *lp,int *mp,long long int *comparisons,long long int *assignments) {
	int i=left+2, j=left+2, n=right-1, k=right-1, rp;
	int p=array[left], q=array[left+1], r=array[right];
	
	if (left==right-1) {
		if (array[left]>array[right]) {
			swap(&array[left],&array[right]);
			*assignments=*assignments+3;
		}
		*mp=left;
		rp=left;
		*lp=left;
		
		return rp;
	}
	while (j<=n) {
		while (array[j]<q&&j<=n) {
			if (array[j]<p) {
				if (i!=j) {
					swap(&array[i],&array[j]);
					*assignments=*assignments+3;
				}
				i++;
			}
			j++;
			*comparisons=*comparisons+2;
		}
		(*comparisons)++;
		while (array[n]>q&&j<=n) {
			if (array[n]>r) {
				if (n!=k) {
					swap(&array[n],&array[k]);
					*assignments=*assignments+3;
				}
				k--;
			}
			n--;
			*comparisons=*comparisons+2;
		}
		(*comparisons)++;
		if (j<=n) {
			if (array[j]>r) {
				if (array[n]<p) {
					if (i!=j) {
						swap(&array[i],&array[j]);
						*assignments=*assignments+3;
					}
					if (i!=n) {
						swap(&array[i],&array[n]);
						*assignments=*assignments+3;
					}
					i++;
				}
				else {
					if (n!=j) {
						swap(&array[n],&array[j]);
						*assignments=*assignments+3;
					}
				}
				if (n!=k) {
					swap(&array[n],&array[k]);
					*assignments=*assignments+3;
				}
				j++;
				n--;
				k--;
				(*comparisons)++;
			}
			else {
				if (array[n]<p) {
					if (i!=j) {
						swap(&array[i],&array[j]);
						*assignments=*assignments+3;
					}
					if (i!=n) {
						swap(&array[i],&array[n]);
						*assignments=*assignments+3;
					}
					i++;
				}
				else {
					if (j!=n) {
						swap(&array[j],&array[n]);
						*assignments=*assignments+3;
					}
				}
				j++;
				n--;
				(*comparisons)++;
			}
			(*comparisons)++;
		}
	}
	i--;
	j--;
	n++;
	k++;
	if (i!=left+1) {
		swap(&array[left+1],&array[i]);
		*assignments=*assignments+3;
	}
	if (i!=j) {
		swap(&array[i],&array[j]);
		*assignments=*assignments+3;
	}
	i--;
	if (i!=left) {
		swap(&array[left],&array[i]);
		*assignments=*assignments+3;
	}
	if (k!=right) {
		swap(&array[right],&array[k]);
		*assignments=*assignments+3;
	}
	rp=k;
	*lp=i;
	*mp=j;
	
	
	return rp;
}
void QS3pR(int array[],int left,int right,long long int *comparisons,long long int *assignments) {
	if (left<right) {
		int lp, rp, mp, min, mid, max, min1, mid1, max1;
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
		if (left<right+1) {
			pick_positions(array,random1,random2,random3,&min,&mid,&max,comparisons);
			if (min>left+1&&min<right&&mid>left+1&&mid<right&&max>left+1&&max<right) {
				swap(&array[left],&array[min]);
				swap(&array[right],&array[max]);
				swap(&array[left+1],&array[mid]);
				*assignments=*assignments+9;
			}
			else {
				if ((min==left||min==left+1||min==right)&&(mid==left||mid==left+1||mid==right)&&(max==left||max==left+1||max==right)) {
					min1=array[min];
					mid1=array[mid];
					max1=array[max];
					*assignments=*assignments+3;
					
					array[left]=min1;
					array[left+1]=mid1;
					array[right]=max1;
					*assignments=*assignments+3;
				}
				else {
					if (min==left||min==left+1||min==right) {
						if (mid==left||mid==left+1||mid==right) {
							if (min==left) {
								if (mid==right) {
									swap(&array[mid],&array[left+1]);
									*assignments=*assignments+3;
								}
							}
							else {
								if (min==left+1) {
									if (mid==right) {
										swap(&array[mid],&array[left+1]);
										swap(&array[mid],&array[left]);
										*assignments=*assignments+6;
									}
									else {
										swap(&array[min],&array[mid]);
										*assignments=*assignments+3;
									}
								}
								else {
									if (mid==left+1) {
										swap(&array[min],&array[left]);
										*assignments=*assignments+3;
									}
									else {
										swap(&array[mid],&array[left+1]);
										swap(&array[min],&array[left]);
										*assignments=*assignments+6;
									}
								}
							}
							swap(&array[max],&array[right]);
							*assignments=*assignments+3;
						}
						else {
							if (max==left||max==left+1||max==right) {
								if (min==left) {
									if (max==left+1) {
										swap(&array[max],&array[right]);
										*assignments=*assignments+3;
									}
								}
								else {
									if (min==left+1) {
										if (max==left) {
											swap(&array[max],&array[right]);
											*assignments=*assignments+3;
										}
										swap(&array[min],&array[left]);
										*assignments=*assignments+3;
									}
									else {
										if (max==left+1) {
											swap(&array[max],&array[left]);
											*assignments=*assignments+3;
										}
										swap(&array[min],&array[left]);
										*assignments=*assignments+3;
									}
								}
								swap(&array[mid],&array[left+1]);
								*assignments=*assignments+3;
							}
							else {
								if (min!=left) {
									swap(&array[min],&array[left]);
									*assignments=*assignments+3;
								}
								swap(&array[max],&array[right]);
								swap(&array[mid],&array[left+1]);
								*assignments=*assignments+6;
							}
						}
					}
					else {
						if (mid==left||mid==left+1||mid==right) {
							if (max==left||max==left+1||max==right) {
								if (mid==left) {
									if (max==left+1) {
										swap(&array[max],&array[right]);
										*assignments=*assignments+3;
									}
									swap(&array[mid],&array[left+1]);
									*assignments=*assignments+3;
								}
								else {
									if (mid==left+1) {
										if (max==left) {
											swap(&array[max],&array[right]);
											*assignments=*assignments+3;
										}
									}
									else {
										if (max==left) {
											swap(&array[max],&array[left+1]);
											*assignments=*assignments+3;
										}
										swap(&array[mid],&array[left+1]);
										*assignments=*assignments+3;
									}
								}
								swap(&array[min],&array[left]);
								*assignments=*assignments+3;
							}
							else {
								swap(&array[mid],&array[left+1]);
								swap(&array[min],&array[left]);
								swap(&array[max],&array[right]);
								*assignments=*assignments+9;
							}
						}
						else {
							if (max!=right) {
								swap(&array[max],&array[right]);
								*assignments=*assignments+3;
							}
							swap(&array[mid],&array[left+1]);
							swap(&array[min],&array[left]);
							*assignments=*assignments+6;
						}
					}
				}
			}
		}
		rp = partition(array, left, right, &lp,&mp,comparisons,assignments);
		QS3pR(array, left, lp - 1,comparisons,assignments);
		QS3pR(array, lp + 1, mp - 1,comparisons,assignments);
		QS3pR(array, mp + 1, rp - 1,comparisons,assignments);
		QS3pR(array, rp + 1, right,comparisons,assignments);
	}
}
void pick_positions(int *array,int random1, int random2,int random3,int *min,int *mid,int *max,long long int *comparisons) {
	
	if (array[random1]>array[random2]) {
		if (array[random1]>array[random3]) {
			*max=random1;
			if (array[random2]>array[random3]) {
				*mid=random2;
				*min=random3;
			}
			else {
				*min=random2;
				*mid=random3;
			}
			(*comparisons)++;
		}
		else {
			*mid=random1;
			*min=random2;
			*max=random3;
		}
		(*comparisons)++;
	}
	else {
		if (array[random2]>array[random3]) {
			*max=random2;
			if (array[random1]>array[random3]) {
				*min=random3;
				*mid=random1;
			}
			else {
				*mid=random3;
				*min=random1;
			}
			(*comparisons)++;
		}
		else {
			*mid=random2;
			*min=random1;
			*max=random3;
		}
		(*comparisons)++;
	}
	(*comparisons)++;
}








