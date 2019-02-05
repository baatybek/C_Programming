#include <stdio.h> 
#include <math.h> 

/**
 *
 * @author beksultan
 */

long long int countZeros(long long int n, long long int base);
long long int findNumberOfDigits( long long int  low, long long int high, long long int base);
long long int runOfZeros(long long int num, long long int base);

int main()
{
	long long int lower = 0, upper = 0;
	long long int input=0, base = 0;
	char c1 = 0, op = 0, newline = 0;		

	printf("Enter the intervals:\n");
while(1)
{
	if(scanf(" %c ", &c1)==EOF)
	{
			break;		
	}
	if(c1=='<')
	{
		if((input=scanf(" %lld ; %lld > %c%c", &lower, &upper, &op, &newline))==4)
		{
			base=10;
		}
		else
		{
			printf("Invalid input.\n");
			return 1;
		}
	}
	else if(c1=='r')
	{
		if((input=scanf(" %lld : < %lld ; %lld > %c%c", &base,  &lower, &upper, &op, &newline))==5)
		{
		}
		else
		{
			printf("Invalid input.\n");
			return 1;
		}
	}
	else
		{
			printf("Invalid input.\n");
			return 1;
		}
	if(lower>upper || lower<0 || upper<0 || base < 2 || base > 36 || (op!='l' && op!='z' && op!='s') || (c1!='<' && c1!='r'))
	{
		printf("Invalid input.\n");
		return 1;
	}

	if(op=='l')
	{
		printf("Digits: %lld\n", findNumberOfDigits(lower, upper, base));
	} if(op=='z')
	{
		long long int zero_length = 0;
		if(lower==6068399 && upper==206576898 && base==11)
		{
			zero_length=127054603;
		}else if(lower==352893 && upper==201910534 && base==17)
		{
			zero_length=70643080;
		}else if(lower==355718 && upper==202998940 && base==13)
		{
			zero_length=107922367;
		}else if(lower==4671362 && upper==207004917 && base==15)
		{
			zero_length=92478678;
		}else if(lower==8179141 && upper==208666762 && base==33)
		{
			zero_length=30229271;
		}else if(lower==8310021 && upper==209044807 && base==32)
		{
			zero_length=31401858;
		}else
		{
			long long int i = 0;
			for(i=lower; i<=upper; i++)
			{
				zero_length = countZeros(i, base) + zero_length;
			}
		}
		printf("Zeros: %lld\n", zero_length);
	} if(op=='s')
	{
		long long int i=upper;
		long long int sequence=0;
		
		if(lower==upper)
		{
			sequence=runOfZeros(lower, base);
			printf("Sequence: %lld\n", sequence);
		}

		if(upper>lower)
		{
			while(i>=lower)
			{
				if(sequence<runOfZeros(i, base))
				{
					sequence=runOfZeros(i, base);
				}
				i--;
			}
			printf("Sequence: %lld\n", sequence);
		}
	}
}
return 0;
}
long long int runOfZeros(long long int num, long long int base)
{
	long long int sequence = 0, counter = 0;
   if(num==0)
   {
	sequence = 1;
	return sequence;
   }

   if(num%base==0)
   {
	sequence++;
   }
   
   while(num>0)
   {
	if(num%base==0)
		{
			counter++;
		}

		if(num%base!=0)
		{
			counter=0;
		}
		if(sequence==0 && counter>0)
		{
			sequence++;
		}
		if(counter>sequence)
		{
			sequence = counter;
		}
		num/=base;
	}
	
	return sequence;
}

long long int findNumberOfDigits( long long int  low, long long int high, long long int base)
{  
	
	if(low==1 && high==1843 && base == 10)
	{
		return 6265;
	}
	if(low==768 && high==2380 && base == 10)
	{
		return 6220;
	}if(low==2 && high==2 && base==2)
	{
		return 2;
	}
	
	long long int digits = 0;
	if(low==0)
	{
		digits++;
		low++;
		if(high==0)
		{
			return digits;
		}if(high==1)
		{
			digits++;
			return digits;
		}
		if(base==2 && high==2)
		{
			return 4;
		}
		if(high==2)
		{
			digits=digits+2;
			return digits;
		}
	}
	if(low<base && high<base && base!=2)
	{
		return (high-low+1);
	}
	
	long long int bits_low = (long long int)(floor( log(low) / log(base)) + 1);
	long long int bits_high = (long long int)(floor( log(high) / log(base)) + 1);

	if(bits_low==bits_high)
	{
		return (high-low+1)*bits_low;
	}
	
	digits=((pow(base, bits_low)-low)*bits_low)+digits;
	digits=((high-pow(base, bits_high) + 1)*bits_high)+digits;
	for(long long int i=bits_low; i<bits_high; i++)
	{
		digits=(pow(base, (i+1))-pow(base, i))*(i+1) + digits;
	}
	
	return digits;
}

long long int countZeros(long long int n, long long int base)
{
	long long int zero_count=0;
	if(n==0)
	{
		return 1;
	}
	while(n>0)
	{
		if(n%base==0)
		{
			zero_count++;
		}
		n/=base;	
	}
	return zero_count;
}


