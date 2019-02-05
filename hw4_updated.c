#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}

int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];   
    int i = (low - 1); 
  
    for (int j = low; j <= high- 1; j++) { 
        if (arr[j] <= pivot) { 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void quickSort(int arr[], int low, int high) { 
    if (low < high) { 

        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 

    } 
} 

int billboard(int length, int array[], int distances, int size_arr){
    int billboards = 0, compare = distances;
    quickSort(array, 0, size_arr);


    for(int m = 0; m <= size_arr; m++){
        if(m!=size_arr){
            if(distances<array[m+1]-array[m]){
                return -1;
            }
        }
    }
    
    if(length - array[size_arr]>distances || array[0]>distances){
        return -1;
    }

    if((length-distances) <= 0){
        return 0;
    }

    if((length - distances <= array[0]) && (distances >= array[size_arr]))
            return 1;

    int i = 0;

    for (int j = 0; j <= size_arr; ++j)
    {
        if( j < size_arr && array[j+1]-array[j]>distances){
            return -1;
        }
        do{
            if(length - compare <= 0){
                return billboards;
            }
            if(array[i]>compare && i!=0){
                billboards++;
                compare = array[i-1] + distances;
                i=i-1;
                j = i;
            }
            if(i==0 && array[i]>compare){
                billboards ++;
                compare = array[i] + distances;
                j = i;
            }
            i++;

        }while(array[i]<=compare);
    }

    return billboards;
}

int main()
{
    int length = 0, distances = 0, input = 0, i =0;
    char c = 0, start = 0;
    int array[1000000];

    printf("Suitable positions:\n");
    if((input=scanf(" %d : %c", &length, &start))==2) {
    if(start!='{'){
     printf("Invalid input.\n");
                    return 1;
    }

        while (c != '}'){
            if((input=scanf(" %d %c", &array[i], &c))==2){
                if(input != 2 || array[i]>=length || array[i]<1 || c=='\n' || (c!=',' && c!='}')) {
                    printf("Invalid input.\n");
                    return 1;
                }
                if(c!='}'){
                    i++;
                }
            } else {
                printf("Invalid input.\n");
                return 1;
            }
        }
        if(c!='}' || length<=0 || i>1000000 ){
            printf("Invalid input.\n");
            return 1;   
        }
    }
    else{
        printf("Invalid input.\n");
        return 1;
    }
        printf("Distances:\n");
    while(1){
        input=scanf("%d", &distances );
        if(input==EOF) {
            break;
        }
        if(input!=1 || distances<=0) {
            printf("Invalid input.\n");
            return 1;
        }
        //printf("i=%d\n", i);
       /*int tmp_arr [] = {47,134,104,64,76,106,135,110,35,28,85,81,5,3,125,26,38,128,47,103,108,131,69,24,36,132,117,79,36,28,56,139,30,120,9,34,19,89,129,29,62,1,14,108};
        if(length==141 && tmp_arr==array && distances == 19){
            printf("Billboards: \n");
        }*/
        int billboard_result = billboard(length, array, distances, i);
        if(billboard_result<0){
            printf("N/A\n");
        }
        else{
        printf("Billboards: %d\n", billboard_result);
        }
    }
    return 0;   
}