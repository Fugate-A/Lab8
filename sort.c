
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void mergeSort(int a[], int l, int r);
void merge( int a[], int l, int mid, int r);
void heapSort(int arr[], int n);
void heapify( int arr[], int size, int base );

void swap( int *x, int *y )
{
  int temp = *x;
  *x = *y;
  *y = temp; 
}

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	for( int i = n/2 - 1; i >= 0; i-- )
	{
		heapify(arr, n, i);
	}
  
    for( int i = n - 1; i >= 0; i-- )
	{
		swap(&arr[0], &arr[i]);
		
		heapify(arr, i, 0);
    }
}

void heapify( int arr[], int size, int base )
{
	if( size == ( 0 || 1 ) )
	{
		return;
	}

	else
	{
		int max = base;

		int left = 2*base + 1;
		int right = 2*base + 2;

		if( left < size && arr[left] > arr[max] )
		{
			max = left;
		}

		if( right < size && arr[right] > arr[max] )
		{
			max = right;
		}

		if( max != base )
		{
			swap( &arr[base], &arr[max] );
			heapify( arr, size, max );
		}
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(r > l)  
  {
    int mid = (l+r)/2;

    mergeSort(pData, l, mid);

    mergeSort(pData, mid+1, r);

    merge(pData, l, mid, r);
  }
}

void merge( int a[], int l, int mid, int r)
{
  int sizeLeft = mid - l + 1;
  int sizeRight = r - mid;

  int *L = malloc( sizeof(int) * sizeLeft );
  extraMemoryAllocated = extraMemoryAllocated + sizeLeft;
  int *R = malloc( sizeof(int) * sizeRight );
  extraMemoryAllocated = extraMemoryAllocated + sizeRight;

  for( int i = 0; i < sizeLeft; i++ )
    {
      L[i] = a[l+i];     
    }

  for( int j = 0; j < sizeRight; j++ )
    {
      R[j] = a[mid+1+j];
    }

  int i = 0;
  int j = 0;
  int k = l;

  while( i < sizeLeft && j < sizeRight )
    {
      if( L[i] < R[j])
      {
        a[k] = L[i];
        i++;
        //k++;
      }
      else              //either the same or R > L
      {
        a[k] = R[j];
        j++;
        //k++;
      }
      k++;
    }
  
  while( i < sizeLeft )
    {
      a[k] = L[i];
      i++;
      k++;
    }
  
  while( j < sizeRight )
    {
      a[k] = R[j];
      j++;
      k++;
    }

  free(L);
  free(R);
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	if( dataSz - 100 < 0 )
	{
		//printf("\n");

		for (int i=0;i<dataSz;++i)
		{
			printf("%d ",pData[i]);
		}

		printf("\n");
	}

	else
	{
		int i, sz = dataSz - 100;
		printf("\tData:\n\t");
		for (i=0;i<100;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\t");
		
		for (i=sz;i<dataSz;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\n");
		}
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}