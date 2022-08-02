//Michael Olagunju
//2022-02-01
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
struct subscriber
{
char number[20];
char name[50];
float amount;
}s;
void addrecords();
void listrecords();
void editrecords();
void clearrecords();
void searchrecords();
void pay();
char get;
int main()
{	int password;
	int number;
	char choice;



	system("cls");

	printf("\n\n\n\n\n\n\n\n\n*******************************************************");
	printf("\n\t\t------TELECOM BILLING MANAGEMENT SYSTEM---");
	printf("\n\t\t****************************************************************");
	Sleep(2000);
	getch();
    system("cls");
	while (1)
	{
		system("cls");
		printf("\n Enter\n A : add new record. \n L : for list of records");
		printf("\n M : modify record.\n P : for payment");
		printf("\n S : search record.");
		printf("\n D : delete record.\n E : Exit\n");
		choice=getche();
		choice=toupper(choice);
		switch(choice)
		{
			case 'P':
				pay();break;
			case 'A':
				addrecords();break;
			case 'L':
				listrecords();break;
			case 'M':
				editrecords();break;
			case 'S':
				searchrecords();break;
			case 'D':
				clearrecords();break;
			case 'E':
				system("cls");
				printf("\n\n\t\t\t\tTHANK YOU");
				printf("\n\n\n\n\n:\n\tFOR USING THIS SERVICE");
				Sleep(2000);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
		}
	}
}
void addrecords()
{
	FILE *f;
	char test;
	f=fopen("c:/file.ojs","ab+");
	if(f==0)
	{   f=fopen("c:/file.ojs","wb+");
		system("cls");
		printf("please wait while we configure your computer");
		printf("/npress any key to continue");
		getch();
	}
	while(1)
	{
		system("cls");
		printf("\n Enter phone number:");
		scanf("%s",&s.number);
		printf("\n Enter name:");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("\n Enter amount:");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("1 record successfully added");
		printf("\n Press esc key to exit, any other key to add other record:");
		test=getche();
		if(test==27)
			break;
	}
	fclose(f);
}
void listrecords()
{
	FILE *f;
	int i;
	if((f=fopen("c:/file.ojs","rb"))==NULL)
		exit(0);
	system("cls");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	for(i=0;i<79;i++)
		printf("-");
	while(fread(&s,sizeof(s),1,f)==1)
	{
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.number,s.name,s.amount);
	}
	printf("\n");
	for(i=0;i<79;i++)
		printf("-");

fclose(f);
getch();
}
void clearrecords()
{
	FILE *f,*t;
	int i=1;
	char number[20];
	if((t=fopen("c:/temp.ojs","w+"))==NULL)
	exit(0);
	if((f=fopen("c:/file.ojs","rb"))==NULL)
	exit(0);
	system("cls");
	printf("Enter the phone number to be deleted from the Database");
	fflush(stdin);
	scanf("%[^\n]",number);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.number,number)==0)
		{       i=0;
			continue;

		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i==1)
	{       system("cls");
		printf("Phone number \"%s\" not found",number);
		remove("c:/file.ojs");
		rename("c:/temp.ojs","c:/file.ojs");
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("c:/file.ojs");
	rename("c:/temp.ojs","c:/file.ojs");
	system("cls");
	printf("The Number %s Successfully Deleted!!!!",number);
	fclose(f);
	fclose(t);
	getch();
}
void searchrecords()
{
	FILE *f;
	char number[20];
	int flag=1;
	f=fopen("c:/file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("Enter Phone Number to search in our database");
	scanf("%s", number);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.number,number)==0)
		{	system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.number,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag==1)
		{	system("cls");
			printf("Requested Phone Number Not found in our database");
		}
	}
	getch();
	fclose(f);
}
void editrecords()
{
	FILE *f;
	char number[20];
	long int size=sizeof(s);
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the subscriber to modify:");
	scanf("%[^\n]",number);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.number,number)==0)
		{
			system("cls");
			printf("\n Enter phone number:");
			scanf("%s",&s.number);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}
void pay()
{
	FILE *f;
	char number[20];
	long int size=sizeof(s);
	float amt;
	int i;
	if((f=fopen("c:/file.ojs","rb+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the subscriber for payment");
	scanf("%[^\n]",number);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f)==1)
	{
		if(strcmp(s.number,number)==0)
		{
			system("cls");
			printf("\n Phone No.: %s",s.number);
			printf("\n Name: %s",s.name);
			printf("\n Current amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\nEnter amount of payment :");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount=s.amount-amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	system("cls");
	printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	getch();
	fclose(f);
}
