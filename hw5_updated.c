#include <stdio.h>
#include <stdlib.h>

typedef struct TollStruct
{
    long long int length;			// length of instance of a structure for a segment
    long double price[26];	// toll fare per segment per tax type
}TollStruct;

// void highWayPrint( TollStruct a[], int n){
//     for (int i = 0; i < n; i++) {
//         for(int j = 0; j<26; j++) {
//         	if(a[i].price[j]!=0)
//             	printf("Length = %d %c = %lf\n",a[i].length,j + 65, a[i].price[j]);
//         }
//         puts("");
//     }
// }

void swap(long long int *a,long long int *b)
{
    long long int t;
    t  = *b;
    *b = *a;
    *a = t;
}

void calculateArr(TollStruct tolls[], long long int low, long long  int high,long int size, long long int len[]){
    long double final_cost[26] = {0};

    for (int i = 0; i < size; ++i)
    {
        if(tolls[i].length  > low && tolls[i].length  == high){
            len[i] = high - low;
            break;
        }
        else if(tolls[i].length > low && tolls[i].length < high){
            len[i] = tolls[i].length  - low;
            low = tolls[i].length ;
        }
        else if(tolls[i].length >= high){
            len[i] = high - low;
            break;
        }
        else if(tolls[i].length < low && tolls[i].length < high){
            len[i] = 0;
        }
        else if(tolls[i].length >= low && tolls[i].length <= high){
            len[i] = tolls[i].length - low;
            low = tolls[i].length;
        }
    }

    int m_counter = 0;
    for(int m = 0; m < 26; m++){
        for (int counter = 0; counter < size; ++counter)
        {
            final_cost[m] = final_cost[m] + (len[counter] * tolls[counter].price[m]);
        }
        if(final_cost[m]!=0){
            m_counter++;
            if(m_counter!=1)
                printf(",");
            printf(" %c=%.6Lf", m+65, final_cost[m]);
        }
    }
    printf("\n");

}


int main()
{
    long int size_tolls = 1000, input = 0, i = 0;
    // printf("size_tolls:%d\n", size_tolls);
    TollStruct * tolls;
    tolls = (TollStruct *) malloc (size_tolls * sizeof(TollStruct));
    // int indexes[26] = {0};
    long double tmp_array[26] = {0};
    char c1 = 0, c2 = 0, c3 = 0;

    printf("Toll:\n");
    if(scanf(" %c", &c1)==1 && c1=='{'){
        while(1){

            long long int h_len = 0, tmp_len = 0;
            SEGMENT:
            tmp_len = 0;
            int input = scanf (" [ %lld :", &tmp_len);
            if(input==1){
                h_len += tmp_len;
                tolls[i].length = h_len;


                if(tolls[i].length<=0){
                    printf("Invalid input.\n");
                    free(tolls);
                    return 1;
                }

                long double tax_cost;
                int index_str;
                char tax_type;

                TAX_RATE:
                tax_cost = 0;
                if(scanf(" %c = %Lf %c", &tax_type, &tax_cost, &c2)==3){
                    index_str = tax_type - 65;
                    // indexes[tax_type-65] = 1;
                    if(tax_cost < 0 || index_str < 0 || index_str > 25){
                        printf("Invalid input.\n");
                        free(tolls);
                        return 1;
                    }

                    tmp_array[index_str] = tax_cost;
                    for (int l = 0; l < 26; ++l)
                    {
                        tolls[i].price[l] = tmp_array[l];
                    }

                    if(c2 == ',')
                        goto TAX_RATE;
                    else if(c2 == ']'){
                        i++;
                        if(i==size_tolls-5){
                        /*----------Realloc TOLLS  ARRAY IN CASE NOT ENOUGH MEMORY------------------------*/
                            size_tolls = size_tolls * 2;
                            tolls = (TollStruct *) realloc (tolls, sizeof(TollStruct) * size_tolls);
                       // printf("RALLOC: size_tolls:%d\n", size_tolls);
                        }
                        input = scanf (" %c", &c3);
                        if(input == 1){
                            if(c3==',')
                                goto SEGMENT;
                            else if(c3 == '}')
                                goto CONTINUE;
                            else{
                                printf("Invalid input.\n");
                                free(tolls);
                                return 1;
                            }
                        }else{
                            printf("Invalid input.\n");
                            free(tolls);
                            return 1;
                        }
                    }
                }else{
                    printf("Invalid input.\n");
                    free(tolls);
                    return 1;
                }

            }else{
                printf("Invalid input.\n");
                free(tolls);
                return 1;
            }
        }
    }else{
        printf("Invalid input.\n");
        free(tolls);
        return 1;
    }

    CONTINUE:
    // highWayPrint(tolls, i);
    // printf("[i]:%d\n", i);

    printf("Search:\n");
    while(1){
        long long int low = 0;
        long long int high = 0;
        input = scanf(" %lld %lld", &low, &high);
        if(input == EOF){
            break;
        }

        if(input != 2 || low == high || low < 0 || high < 0 || tolls[i-1].length < low || tolls[i-1].length < high){
            printf("Invalid input.\n");
            free(tolls);
            return 1;
        }

        long long int * len = (long long int *) calloc (i, sizeof(long long  int));
        printf("%lld - %lld:", low, high);
        if(low>high)
            swap(&low, &high);
        calculateArr(tolls,  low,  high,  i, len);
        free(len);
    }
    free(tolls);

    return 0;
}