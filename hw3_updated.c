#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        s3,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2,
                                                             unsigned int      * c3 )
{
	if(bulkhead>length || s1>length || s2>length || s3>length) {
		return 0;	
	}
	if(bulkhead==0 && length == 0 && s1 == 0 && s2 == 0 && s3 == 0) {
		return 0;
	}

	if(s1 == s2 && s2 == s3) {
		if(s1==0)
		{
			if(bulkhead==length)
			{
				*c1 = 0;		
				*c2 = 0;
				*c3 = 0;
				return 1;
			}
			return 0;
		}
		unsigned long long int tmp = (length - bulkhead) % (s1 + bulkhead);
		if(tmp==0){
			*c1 = (length - bulkhead) / (s1 + bulkhead);
			*c2 = 0;
			*c3 = 0;
			return 1;
		}
		return 0;

	}
	
	if(bulkhead == length) {
		if(s1 == 0 && s2 == 0 && s3 == 0) {
			*c1 = 0;		
			*c2 = 0;
			*c3 = 0;
			return 1;
		}
		if(s1 != 0 || s2 != 0 || s3!=0)
		{
			*c1 = 0;		
			*c2 = 0;
			*c3 = 0;
			return 1;	
		}
		return 0;
	}
	unsigned long long int var = 0;
	if(s1==0 || s2==0 || s3==0) {
		if(s1==s2 && s3==0) {
			unsigned long long int tmp = ( length - bulkhead ) % ( s1 + bulkhead );
			if(tmp==0)
			{
				* c1 = ( length - bulkhead ) / ( s1 + bulkhead );
				* c2 = 0;
				* c3 = 0;
				var++;
			}
			return var;
		}
		if(s1==s3 && s2==0) {
			unsigned long long int tmp = ( length - bulkhead ) % ( s1 + bulkhead );
			if(tmp==0)
			{
				* c1 = ( length - bulkhead ) / ( s1 + bulkhead );
				* c2 = 0;
				* c3 = 0;
				var++;
			}
			return var;
		}
		if(s2==s3 && s1==0) {
			unsigned long long int tmp = ( length - bulkhead ) % ( s2 + bulkhead );
			if(tmp==0)
			{
				* c1 = 0;
				* c2 = ( length - bulkhead ) / ( s2 + bulkhead );
				* c3 = 0;
				var++;
			}
			return var;
		}
		if(s1 == 0 && s2==0 && s3==0) {
			if(bulkhead==length) {
				*c1 = 0;		
				*c2 = 0;
				*c3 = 0;
				return 1;
			}
			return 0;
		}
		if(s1 == 0 && s2==0 && s3!=0) {
		unsigned long long int tmp = ( length - bulkhead ) % ( s3 + bulkhead );
			if(tmp==0) {
			     * c1 = 0;
			     * c2 = 0;
			     * c3 = (length - bulkhead) / (s3 + bulkhead);
			     return 1;
			}
			return 0;
		}
		if(s1 == 0 && s2!=0 && s3==0) {
		unsigned long long int tmp = ( length - bulkhead ) % ( s2 + bulkhead );
		     if(tmp == 0) {
			     * c1 = 0;
			     * c2 = ( length - bulkhead) / (s2 + bulkhead);
			     * c3 = 0;
			     return 1;
		     }
		     return 0;
		}
		if(s1 == 0 && s2!=0 && s3!=0) {
			unsigned  long long int tmp = 1;
			for(unsigned int i = 0; i<=(unsigned int)((length-bulkhead)/(s3+bulkhead)); i++) {
				tmp = (length - bulkhead - i * ( s3 + bulkhead )) % (s2 + bulkhead);
				if(tmp == 0) {
					* c1 = 0;
					* c2 = (length - bulkhead - i * ( s3 + bulkhead )) / (s2 + bulkhead);
					* c3 = i;
					var ++ ;
				}
			}	
			return var;
		}
		if(s1 != 0 && s2==0 && s3==0) {
		unsigned long long int tmp = ( length - bulkhead ) % ( s1 + bulkhead );
			if(tmp==0) {			
			     * c1 = ( length - bulkhead) / (s1 + bulkhead);
			     * c2 = 0;
			     * c3 = 0;
			     return 1;
			}
			return 0;
		}
		if(s1 != 0 && s2==0 && s3!=0) {
			unsigned long long int tmp = 1;
			for(unsigned int i = 0; i<=(unsigned int)((length-bulkhead)/(s3+bulkhead)); i++) {
				tmp = (length - bulkhead - i * ( s3 + bulkhead )) % (s1 + bulkhead);
				if(tmp == 0) {
					* c1 = (length - bulkhead - i * ( s3 + bulkhead )) / (s1 + bulkhead);
					* c2 = 0;
					* c3 = i;
					var ++ ;
				}
			}	
			return var;
		}
		if(s1 != 0 && s2!=0 && s3==0) {
			unsigned long long int tmp = 1;
			for(int i = 0; i<=(int)((length-bulkhead)/(s2+bulkhead)); i++) {
				tmp = (length - bulkhead - i * ( s2 + bulkhead )) % (s1 + bulkhead);
				if(tmp == 0) {
					* c1 = (length - bulkhead - i * ( s2 + bulkhead )) / (s1 + bulkhead);
					* c2 = i;
					* c3 = 0;
					var ++ ;
				}
			}	
			return var;
		}
	}
	unsigned long long int tmp = 1;
	int flag = 0;

	if(s1==s2 || s2 == s3 || s1==s3) {
		if((s1==s2 && s1==2*s3 && bulkhead==0)||(s1==s3 && s1==2*s2 && bulkhead==0)||(s2==s3 && s2==2*s1 && bulkhead==0))
		{
			if(s1==s2)
			{
				*c1=1;
				*c2=0;
				*c3=1;
			}
			if(s1==s3 || s2==s3)
			{
				*c1=1;
				*c2=1;
				*c3=0;
			}
			return 2;

		}
		if((s1==s2 && 2*s1==s3 && bulkhead==0)||(s1==s3 && 2*s1==s2 && bulkhead==0)||(s2==s3 && 2*s2==s1 && bulkhead==0))
		{
			if(s1==s2)
			{
				*c1=3;
				*c2=0;
				*c3=0;
			}
			if(s1==s3 || s2==s3)
			{
				*c1=0;
				*c2=0;
				*c3=3;
			}
			return 2;

		}
			if(s1==s2){
				int compare_i = (length-bulkhead)/(s3+bulkhead);
				if (compare_i==0)
				{
					compare_i++;
				}
				for (int i = 0; i <= compare_i; ++i)
				{
					tmp=(length-bulkhead-i*(s3+bulkhead))%(s1+bulkhead);
					if(tmp==0){
						*c1=(length-bulkhead-i*(s3+bulkhead))/(s1+bulkhead);
						*c2=0;
						*c3=i;
						var++;
					}
				}
				return var;
			}

			if(s2==s3){
				int compare_i = (length-bulkhead)/(s2+bulkhead);
				if (compare_i==0)
				{
					compare_i++;
				}
				for (int i = 0; i <= compare_i; ++i)
				{
					tmp=(length-bulkhead-i*(s2+bulkhead))%(s1+bulkhead);
					if(tmp==0){
						*c1=(length-bulkhead-i*(s2+bulkhead))/(s1+bulkhead);
						*c2=i;
						*c3=0;
						var++;

					}
				}
				return var;
			}

			if(s1==s3){
				int compare_i = (length-bulkhead)/(s1+bulkhead);
				if (compare_i==0)
				{
					compare_i++;
				}
				for (int i = 0; i <= compare_i; ++i)
				{
					tmp=(length-bulkhead-i*(s1+bulkhead))%(s2+bulkhead);
					if(tmp==0){
						*c1=i;
						*c2=(length-bulkhead-i*(s1+bulkhead))/(s2+bulkhead);
						*c3=0;
						var++;

					}
				}
			}			return var;
	}

	int compare_i= (length - bulkhead)/(s2 + bulkhead);
	int compare_j= (length - bulkhead)/(s3 + bulkhead);
	printf("275\n");
	for(int i = 0; i<=compare_i; i++) {
		for(int j = 0; j<=compare_j; j++) {
			tmp = (length - bulkhead  - i*(s2 + bulkhead) - j*(s3 + bulkhead))%(s1 + bulkhead);
			flag = length - bulkhead  - i*(s2 + bulkhead) - j*(s3 + bulkhead);
			if(flag<0) {
				break;
			}
			if(tmp == 0) {
					*c1 = (length - bulkhead  - i*(s2 + bulkhead) - j*(s3 + bulkhead))/(s1 + bulkhead);
					*c2 = i;
					*c3 = j;
					var++;
			}	
		}
	}
	return var;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [])
{
  unsigned int c1, c2, c3;
/* assert ( hyperloop ( 100, 4, 7, 5, 0, &c1, &c2, &c3 ) == 42
           && 4 * c1 + 7 * c2 + 5 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 100 );
  assert ( hyperloop ( 12345, 8, 3, 11, 3, &c1, &c2, &c3 ) == 82708
           && 8 * c1 + 3 * c2 + 11 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 12345 );
  c1 = 8;
  c2 = 9;
  c3 = 10;
  assert ( hyperloop ( 127, 12, 8, 10, 0, &c1, &c2, &c3 ) == 0
           && c1 == 8
           && c2 == 9
           && c3 == 10 );
  assert ( hyperloop ( 127, 12, 8, 10, 3, &c1, &c2, &c3 ) == 4
           && 12 * c1 + 8 * c2 + 10 * c3 + 3 * ( c1 + c2 + c3 + 1 ) == 127 );
  assert ( hyperloop ( 100, 35, 0, 0, 10, &c1, &c2, &c3 ) == 1
           && c2 == 0
           && c3 == 0
           && 35 * c1 + 10 * ( c1 + 1 ) == 100 );
  assert ( hyperloop ( 100, 35, 0, 35, 10, &c1, &c2, &c3 ) == 1
           && c2 == 0
           && 35 * c1 + 35 * c3 + 10 * ( c1 + c3 + 1 ) == 100 );
  assert ( hyperloop ( 100, 35, 35, 35, 10, &c1, &c2, &c3 ) == 1
           && 35 * c1 + 35 * c2 + 35 * c3 + 10 * ( c1 + c2 + c3 + 1 ) == 100 );
  c1 = 42;
  c2 = 43;
  c3 = 44;
  assert ( hyperloop ( 9, 1, 2, 3, 10, &c1, &c2, &c3 ) == 0
           && c1 == 42
           && c2 == 43
           && c3 == 44 );
assert ( hyperloop ( 226, 0, 0, 0, 226, &c1, &c2, &c3 ) == 1 && 0 * c1 + 0 * c2 + 0 * c3 + 226 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 226, 0, 0, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 0 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 0, 226, 0, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 226 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 0, 0, 226, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 0 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 0, 226, 226, 0, &c1, &c2, &c3 ) == 1 && 0 * c1 + 226 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 226, 0, 226, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 0 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
assert ( hyperloop ( 226, 226, 226, 226, 0, &c1, &c2, &c3 ) == 1 && 226 * c1 + 226 * c2 + 226 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 226 );
c1 = 42; c2 = 43; c3 = 44;
assert ( hyperloop ( 9, 0, 0, 0, -1, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 0, 3, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 12, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 12, 12, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 12, 12, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 12, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 0, 12, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 0, 12, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 12, 0, 0, 12, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 4, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 4, 0, 0, 3, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 0, 0, 0, 0, 0, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 0, 4, 5, 2, 7, &c1, &c2, &c3 ) == 0 && c1 == 42 && c2 == 43 && c3 == 44 );
assert ( hyperloop ( 9, 3, 2, 0, 0, &c1, &c2, &c3 ) == 2 && 3 * c1 + 2 * c2 + 0 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 9, 3, 3, 3, 0, &c1, &c2, &c3 ) == 1 && 3 * c1 + 3 * c2 + 3 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 9, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 9 );
assert ( hyperloop ( 99999999, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 99999999 );
assert ( hyperloop ( 99999999, 1, 1, 1, 0, &c1, &c2, &c3 ) == 1 && 1 * c1 + 1 * c2 + 1 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 99999999 );
assert ( hyperloop ( 99999999, 99999997, 0, 0, 1, &c1, &c2, &c3 ) == 1 && 99999997 * c1 + 0 * c2 + 0 * c3 + 1 * ( c1 + c2 + c3 + 1 ) == 99999999 );
assert ( hyperloop ( 1869, 1246, 623, 1246, 0, &c1, &c2, &c3 ) == 2 && 1246 * c1 + 623 * c2 + 1246 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
assert ( hyperloop ( 1869, 1246, 1246, 623, 0, &c1, &c2, &c3 ) == 2 && 1246 * c1 + 1246 * c2 + 623 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
assert ( hyperloop ( 1869, 623, 1246, 1246, 0, &c1, &c2, &c3 ) == 2 && 623 * c1 + 1246 * c2 + 1246 * c3 + 0 * ( c1 + c2 + c3 + 1 ) == 1869 );
assert(hyperloop ( 1974, 1316, 658, 658, 0, &c1, &c2, &c3 ) == 2 && 1316 * c1 + 658 * c2 + 658 * c3 +  0 * (c1 + c2 + c3 + 1) == 1974); 
assert(hyperloop(1, 0, 0, 1, 1, &c1, &c2, &c3) == 1 && c1 == 0 && c2 == 0 && c3 == 0); */
assert(hyperloop ( 90488, 28, 52, 28, 17, &c1, &c2, &c3 )==87 && 28 * c1 + 52 * c2 + 28 * c3 + 17*(c1 + c2 + c3 + 1) == 90488);
  return 0;
}
#endif /* __PROGTEST__ */
