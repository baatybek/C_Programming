#include <stdio.h>
#include <math.h>

double min(double a, double b);

int main()
{
	double x1=0.0, x2=0.0, x3=0.0, y1=0.0, y2=0.0, y3=0.0;
	double a1=0.0, a2=0.0, b1=0.0, b2=0.0, c1=0.0, c2=0.0;
	char c= ' ', start = ' ';
	int input;
	
	printf("Triangle #1:\n");
	if((input = scanf(" %c [ %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }%c", &start, &x1, &y1, &x2, &y2, &x3, &y3, &c))==8)
	{
			a1=sqrt(fabs(x2-x1)*fabs(x2-x1)+fabs(y2-y1)*fabs(y2-y1));
			b1=sqrt(fabs(x3-x1)*fabs(x3-x1)+fabs(y3-y1)*fabs(y3-y1));
			c1=sqrt(fabs(x3-x2)*fabs(x3-x2)+fabs(y3-y2)*fabs(y3-y2));

	}
	else if((input = scanf(" %lf , %lf , %lf }%c", &a1, &b1, &c1, &c))==4){}
	else
	{
			printf("Invalid input.\n");
			return 1;		
	}
/*	printf("a1+b1-c1:%.20f\n", a1+b1-c1);
	printf("a1+c1-b1:%.20f\n", a1+c1-b1);
	printf("b1+c1-a1:%.20f\n", b1+c1-a1);
*/
	if(start!='{')
	{
			printf("Invalid input.\n");
			return 1;		
	}
	if(a1+b1-c1<=(1e-12)*c1 || a1+c1-b1<=(1e-12)*b1 || c1+b1-a1<=(1e-12)*a1 )
	{
			printf("Invalid triangle.\n");
			return 1;
	}

	double xx1=0.0, yy1=0.0, xx2=0.0, yy2=0.0, xx3=0.0, yy3=0.0;
	printf("Triangle #2:\n");
	if((input = scanf(" %c [ %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }%c", &start, &xx1, &yy1, &xx2, &yy2, &xx3, &yy3, &c))==8)
	{
		a2=sqrt(fabs(xx2-xx1)*fabs(xx2-xx1)+fabs(yy2-yy1)*fabs(yy2-yy1));
		b2=sqrt(fabs(xx3-xx1)*fabs(xx3-xx1)+fabs(yy3-yy1)*fabs(yy3-yy1));
		c2=sqrt(fabs(xx3-xx2)*fabs(xx3-xx2)+fabs(yy3-yy2)*fabs(yy3-yy2));

	}
	else if((input = scanf(" %lf , %lf , %lf }%c", &a2, &b2, &c2, &c))==4){}
	else
	{
			printf("Invalid input.\n");
			return 1;						
	}
	if(start!='{')
	{
			printf("Invalid input.\n");
			return 1;		
	}
/*	printf("a2+b2-c2:%.20f\n", a2+b2-c2);
	printf("a2+c2-b2:%.20f\n", a2+c2-b2);
	printf("b2+c2-a2:%.20f\n", b2+c2-a2);
*/
	if(a2+b2-c2<=(1e-12)*c2 || a2+c2-b2<=(1e-12)*b2 || c2+b2-a2<=(1e-12)*a2)
	{
			printf("Invalid triangle.\n");
			return 1;
	}
	double circm1 = a1+b1+c1;
	double circm2 = a2+b2+c2;

	if((fabs(a1-a2)<=(1e-12)*min(a1,a2))&&(fabs(b1-b2)<=(1e-12)*min(b1,b2))&&(fabs(c1-c2)<=(1e-12)*min(c1,c2)))
	{
		printf("The triangles are identical.\n");
	}else if((fabs(a1-a2)<=(1e-12)*min(a1,a2))&&(fabs(b1-c2)<=(1e-12)*min(b1,c2))&&(fabs(c1-b2)<=(1e-12)*min(c1,b2))){
		printf("The triangles are identical.\n");
	}else if((fabs(b1-a2)<=(1e-12)*min(b1,a2))&&(fabs(a1-b2)<=(1e-12)*min(a1,b2))&&(fabs(c1-c2)<=(1e-12)*min(c1,c2))){
		printf("The triangles are identical.\n");
	}else if((fabs(b1-a2)<=(1e-12)*min(b1,a2))&&(fabs(c1-b2)<=(1e-12)*min(c1,b2))&&(fabs(a1-c2)<=(1e-12)*min(a1,c2))){
		printf("The triangles are identical.\n");
	}else if((fabs(c1-a2)<=(1e-12)*min(c1,a2))&&(fabs(a1-b2)<=(1e-12)*min(a1,b2))&&(fabs(b1-c2)<=(1e-12)*min(b1,c2))){
		printf("The triangles are identical.\n");
	}else if((fabs(c1-a2)<=(1e-12)*min(c1,a2))&&(fabs(b1-b2)<=(1e-12)*min(b1,b2))&&(fabs(a1-c2)<=(1e-12)*min(a1,c2))){
		printf("The triangles are identical.\n");
	}else{
		if(fabs(circm1-circm2)<=(1e-12)*min(circm1,circm2) && fabs(circm1-circm2)>=0)
		{
		printf("The triangles are not identical, however, they have the same circumference.\n");
		}else if(circm1-circm2>(1e-12)*min(circm1,circm2))
		{
		printf("Triangle #1 has a longer circumference.\n");
		}else if(circm2-circm1>(1e-12)*min(circm1,circm2))
		{
		printf("Triangle #2 has a longer circumference.\n");
		}
	}


			
	return 0;
}

double min(double a, double b)
{
	if(a>b)
	{
		return a;
	}
	return b;
}


