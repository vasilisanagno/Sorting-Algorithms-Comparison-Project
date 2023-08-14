#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void pick_positions(int *array,int random1, int random2,int random3,int *min,int *mid,int *max,long long int *comparisons);
void find_limits(int *array,int *pivots,int low,int high,int *max,int *min,int pivots_size,int array_size,long long int *comparisons);
void find_position(int *array,int pivot1,int pivot2,int pivot3,int low,int high,int *pos1,int *pos2,int *pos3,long long int *comparisons);
void QS1pL(int array[],int left,int right);
int *pick_pivots(int *array,int left,int right,int size);
void swap(int* a, int* b);
int partition(int *array, int left, int right, int *lp,int *mp,long long int *comparisons,long long int *assignments);
void QS3pRPre(int array[],int **pivots,int low,int high,int *pivots_size,long long int *comparisons,long long int *assignments,int array_size);
void QS3pR(int array[],int left,int right,long long int *comparisons,long long int *assignments);
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
	QS3pRPre(array,&pivots,0,N-1,&size,&comparisons,&assignments,N);
	end=clock();
	printf("QS3pRPre: Execution Time=%f sec, Comparisons=%lld, Assignments=%lld\n", ((double)end-start)/CLOCKS_PER_SEC,comparisons,assignments);
	
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
void find_position(int *array,int pivot1,int pivot2,int pivot3,int low,int high,int *pos1,int *pos2,int *pos3,long long int *comparisons) {
	
	
	for (int i=low; i<=high; i++) {
		if (pivot1==array[i]&&*pos1==-1) {
			*pos1=i;
		}
		if (pivot2==array[i]&&*pos2==-1) {
			*pos2=i;
		}
		if (pivot3==array[i]&&*pos3==-1) {
			*pos3=i;
		}
		if (*pos1!=-1&&*pos2!=-1&&*pos3!=-1) {
			break;
		}
		*comparisons=*comparisons+3;
	}
	if (*pos1==-1||*pos2==-1||*pos3==-1) {
		*pos1=-2;
		*pos2=-2;
		*pos3=-2;
	}
}
void find_limits(int *array,int *pivots,int low,int high,int *max,int *min, int pivots_size,int array_size,long long int *comparisons) {
	int flag1=0,flag2=0, i;
	
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
void QS3pRPre(int array[],int **pivots,int left,int right,int *pivots_size,long long int *comparisons,long long int *assignments,int array_size) {
	if (left<right) {
		int lp, rp, mp, min, mid, max, min1, mid1, max1;
		int pos1=-1,pos2=-1,pos3=-1,max2=-1,min2=-1,random1, random2, random3;
		if ((left!=0||right!=array_size-1)&&*pivots_size!=0) {
			find_limits(array,*pivots,left,right,&max2,&min2,*pivots_size,array_size,comparisons);
			if (min2<max2&&max2-min2>1) {
				random1=min2 + rand()%(max2-min2+1);
				random2=min2 + rand()%(max2-min2+1);
				while (random1==random2 || random2>right) {
					random2=min2 + rand()%(max2-min2+1);
				}
				random3=min2 + rand()%(max2-min2+1);
				while (random1==random3 || random2==random3 || random3>right) {
					random3=min2 + rand()%(max2-min2+1);
					if(left==right-1){
						break;
					}
				}
			}
			else {
				if (min2!=max2&&max2-min2>1) {
					random1=max2 + rand()%(min2-max2+1);
					random2=max2 + rand()%(min2-max2+1);
					while (random1==random2 || random2>right) {
						random2=max2 + rand()%(min2-max2+1);
					}
					random3=max2 + rand()%(min2-max2+1);
					while (random1==random3 || random2==random3 || random3>right) {
						random3=max2 + rand()%(min2-max2+1);
						if(left==right-1){
							break;
						}
					}
				}
				else {
					min2=0;
					max2=0;
				}
			}
		}
		else {
			if (*pivots_size!=0) {
				min2=0;
				max2=1;
				random1=rand()%(*pivots_size);
				random2=rand()%(*pivots_size);
				while (random1==random2 || random2>right) {
					random2=rand()%(*pivots_size);
				}
				random3=rand()%(*pivots_size);
				while (random1==random3 || random2==random3 || random3>right) {
					random3=rand()%(*pivots_size);
					if(left==right-1){
						break;
					}
				}
			}
		}
		if ((*pivots_size!=0&&min2!=max2)&&min2!=-1&&max2!=-1) {
			find_position(array,(*pivots)[random1],(*pivots)[random2],(*pivots)[random3],left,right,&pos1,&pos2,&pos3,comparisons);
		}
		else {
			pos1=-2;
			pos2=-2;
			pos3=-2;
		}
		//printf("%d %d %d %d %d %d %d %d %d\n", pos1,pos2,pos3,min2,max2, random1, random2, random3, *pivots_size);
		if (left<right+1&&*pivots_size!=0&&(pos1!=-2&&pos2!=-2&&pos3!=-2)&&(min2!=max2)) {
			if (random1>random2&&random3>random2) {
				for (int k=random2+1; k<*pivots_size; k++) {
					(*pivots)[k-1]=(*pivots)[k];
					if (((*pivots)[k]==random1&&*pivots_size>3)||((*pivots)[k]==random3&&*pivots_size>3)) {
						(*pivots)[k-1]=(*pivots)[k+1];
					}
				}
				*pivots_size=*pivots_size-3;
				*pivots=(int *)realloc(*pivots,sizeof(int)*(*pivots_size));
			}
			else {
				if (random2>random1&&random3>random1) {
					for (int k=random1+1; k<*pivots_size; k++) {
						(*pivots)[k-1]=(*pivots)[k];
						if (((*pivots)[k]==random2&&*pivots_size>3)||((*pivots)[k]==random3&&*pivots_size>3)) {
							(*pivots)[k-1]=(*pivots)[k+1];
						}
					}
					*pivots_size=*pivots_size-3;
					*pivots=(int *)realloc(*pivots,sizeof(int)*(*pivots_size));
				}
				else {
					for (int k=random3+1; k<*pivots_size; k++) {
						(*pivots)[k-1]=(*pivots)[k];
						if (((*pivots)[k]==random2&&*pivots_size>3)||((*pivots)[k]==random1&&*pivots_size>3)) {
							(*pivots)[k-1]=(*pivots)[k+1];
						}
					}
					*pivots_size=*pivots_size-3;
					*pivots=(int *)realloc(*pivots,sizeof(int)*(*pivots_size));
				}
			}
			random1=pos1;
			random2=pos2;
			random3=pos3;
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
			rp = partition(array, left, right, &lp,&mp,comparisons,assignments);
			QS3pRPre(array,pivots, left, lp - 1,pivots_size,comparisons,assignments,array_size);
			QS3pRPre(array,pivots ,lp + 1, mp - 1,pivots_size,comparisons,assignments,array_size);
			QS3pRPre(array,pivots ,mp + 1, rp - 1,pivots_size,comparisons,assignments,array_size);
			QS3pRPre(array,pivots ,rp + 1, right,pivots_size,comparisons,assignments,array_size);
		}
		else {
			QS3pR(array,left,right,comparisons,assignments);
		}
	}
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
int partition(int *array, int left, int right, int *lp,int *mp,long long int *comparisons,long long int *assignments) {
	int i=left+2, j=left+2, n=right-1, k=right-1, rp;
	int p=array[left], q=array[left+1], r=array[right];
	
	if (left==right-1) {
		if (array[left]>array[right]) {
			swap(&array[left],&array[right]);
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
 
