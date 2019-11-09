
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ERROR 0

char ch=0;
int error;
int parenthesis;
int calc(void);
int main(void)
{
	while(ch!=EOF){
		error=0; //initialize the error flag
		parenthesis=0;//initialize the parenthsis counter
		printf("Enter your input : ");
		printf("\nThe result is: %d\n",calc());
	}
}

int GetFactor(void);

//Main function that calculates simple arithmetic expressions
int calc(void)
{
	int num;
	char operation;
	int result=0;


	if(error) return ERROR; //error case handling

	result=GetFactor(); //get the first number-factor
	while(ch != '\n' && ch !=')') //loop while
	{
		operation=ch; //get the operation symbol
		num=GetFactor(); //get the following number-factor
		if(operation=='+') result+=num; //add the factor to the result
		else if(operation=='-')result-=num; //subtract the factor from the result
	}

	if(ch==')')
	{
		ch=getchar(); //if we've just exited a parenthesized expression get the next character to know what to do next
		parenthesis--;
	}

	if(ch=='\n' && parenthesis!=0)
	{
		printf("Error: Wrong parenthesis allocation.Try Again;\n");
		error=1;
		return ERROR;
	}

	if(error)
		return ERROR;
	else
		return result;
}

int GetNum(void);
//Funciton that returns the factor that is estimated (either a real factor , a number or even a parenthetic expression)
int GetFactor(void)
{
	int factor,num;
	factor=num=GetNum();

	if(error) return 0; //error case handling

	while(ch=='*')//while we keep getting '*' as an operation character we multiply the result with the next factor
	{
		num=GetNum();
		factor*=num;
	}

	return factor;
}

int GetNum(void)
{
	int num=0;
	int blank=0;
	//simple loop to build the number from a
	while((((ch=getchar())!=EOF && ch!='\n' && ch>='0' && ch<='9')) || ch==' ' || ch=='\t')
	{
		if(ch==' ' || ch=='\t')
		{
			if(num !=0 && blank==0)
				blank = 1;
			else
				continue;
		}
		else
		{
			//if the number
			num=10*num + (ch - '0');
			if(blank==1) blank=2;
		}

		if(blank == 2)
		{
			printf("Error: No blanks between spaces! Try Again\n");
			int error=1;
			return ERROR;
		}
	}

	if(ch!='+' && ch!='-' && ch!='*' && ch!='(' && ch!=')' && !error && ch!='\n' && ch!=EOF)
	{
		error=1;
		printf("Error: Unknown character read. Try Again!\n");
		return ERROR;
	}
	if(ch=='(' && num==0)
	{
		ch=0;
		parenthesis++;/*printf("Exiting Parenthesis\n");*/
		num=calc();
	}
	return num;
}
