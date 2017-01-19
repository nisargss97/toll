#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   
#include <time.h>
#define ADMINPASS "qwerty123"
#define ff fflush(stdin);
#define err printf("\n\nflag\n\n");

typedef struct{
	double amt;
	char time_stamp[40];
	char id[21];
} trans;
typedef struct{
	char id[21];
	char pwd[21];
	char name[30];
	char email[30];
	double amount;
} user;


typedef struct{ 
	char id[21];
	char pwd[21];
	double income;

}admin;

typedef struct{
	user u;
	admin a;
	int flag;
} stemp;

int user_func(); 
stemp user_login();
int user_reg();
void user_profile(user u);

int admin_func();
stemp admin_login();
int admin_reg();
void admin_profile(admin a);
void update_income();

void transaction();
void user_transaction(user u);
void admin_transaction(admin a);
void admin_income(admin a);

int main()
{
	char ch,c;
	int choice;
	int flag=1;
 
	do 
	{
		system("clear");
		printf("Welcome to Toll Plaza\n\n");
		printf("Please select from options below (1-3): \n\n");
		printf("1. User login \n");
		printf("2. Administrator login \n");
		printf("3. Perform Toll Transaction \n");
		printf("4. Exit \n\n");	
		scanf("%d", &choice);ff;

 		switch(choice)
		{
			case 1:	
					user_func();
					break;
			case 2:
					admin_func();
					break;
			case 3: 
					transaction();
					break;
			case 4: 
					ff;getchar();system("clear");
					printf("\nDo you really want to exit?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					if(c=='y'||c=='Y')
						exit(0);
					break;
			default:
					ff;getchar();
					system("clear");
					printf("\nWrong choice. \n\nPress Enter to continue.\n");ff;getchar();
					system("clear");
					break;
 
		}
 
	} while(1);

	return 0;		
}
 
 
int user_func()
{
	
	char ch,c;
	char id[21];
	char pwd[21];	
	user u;
	int i=0;
	int flag;
	int flag1;
	stemp s;
	c='a';
	
	do
	{
		ch=c;
		ff; getchar();	system("clear");
		printf("\nAre you a registered user? \n");
		printf("\n[Enter M to go back to main menu.] \n\nSelect your choice (Y/N/M)\n\n");
		scanf(" %c",&ch);
		ff getchar();
		switch(ch)
		{
			case 'Y':
			case 'y':	
						s=user_login();
						if(s.flag)
						{
							system("clear");
							user_profile(s.u);
						}
						break;
			case 'N':
			case 'n':
						system("clear");
						printf("\nYou have to register before going forward.");	
						printf("\n\nPress enter to continue. \n\n");
						ff;getchar();system("clear");

						flag1=user_reg();


						break;

			case 'M':
			case 'm':
						system("clear");
						printf("\nDo you really want to return to main menu?(Y/N) : \n\n");	
						ff;scanf(" %c",&c);
						if(c=='y'||c=='Y')
							return 0;	
						break;

			default:
						system("clear");
						printf("\nWrong choice. \n");
						printf("\nPress Enter to continue. \n\n");			
						break;
						

		}

	}while(1);
	

	return 1;
}

stemp user_login()
{
	stemp s;
	FILE* f;
	char ch;
	user u;
	char pwd[21];
	char id[21];
	char *A;
	s.flag=0;

	f=fopen("user_data.txt","ab+");
	if(f==NULL)
	{
		system("clear");
		printf("\n404 Not Found. \n\nPlease try again later. \n");
		//fclose(f);
		return s;
	}

	system("clear");
	
	printf("\nEnter your login details: \n\n");
	printf("Car no : ");
	ff scanf("%s",id);
					
	int flag=0;
	int temp;

	while(1)
	{
	
		if(feof(f))
		{
			break;
		}
	
		fread(&u,sizeof(u),1,f);
		
		if(strcmp(u.id,id)==0)
		{
		
			flag=1;
		
			do
			{

				A=getpass("\nPassword : ");
				strcpy(pwd,A);
									
				if(strcmp(pwd,u.pwd)==0)
				{
					break;
				}		
			
				printf("\nIncorrect Password. \n\nDo you want to ReEnter your password? (y/n)  : ");
				ff;scanf(" %c",&ch);

			} while(ch=='y'||ch=='Y');
			
			if(ch=='n')
			{
				printf("\nLogin Unsuccessful. \n\n. ");
				fclose(f);
				return s;
			}					
			system("clear");

			printf("\nSuccessfully logged in.  \n\nPress Enter to continue.\n");
			ff;	getchar();
			
			break;
		}

	}

	if(!flag)
	{
		printf("\nUser not found. \n");
		ff getchar();
		fclose(f);
		return s;
	}
	s.flag=1;
	s.u=u;
	fclose(f);
	return s;
}
int user_reg()
{

	char ch;
	char *A,*B;
	int flag;
	user u,v;
	FILE* f=fopen("user_data.txt","ab+");

	printf("\nYou are being redirected to registration page. ");
	printf("\n\nPress q followed by Enter to go back.\n");
	printf("\nPress Enter to continue.\n\n");
	ff;scanf("%c",&ch);

	if(ch=='q'||ch=='Q')
	{
		fclose(f);
		return -1;
	}
	ff;system("clear");

	printf("\nREGISTRATION PAGE.\n\n");
	printf("Enter the following details : \n\n");
	
	do{
		
		flag=1;
		printf("Car no : ");
		ff
		scanf("%s",u.id);					
	
		fseek(f,0,SEEK_SET);
	
		while(!feof(f))
		{				
			fread(&v,sizeof(u),1,f);
			if(strcmp(u.id,v.id)==0)
			{
				flag=0;
				break;
			}
		}
		if(!flag)
		{
			ff;system("clear");
			printf("\nUser Name already exists. \n\nReEnter ");
		}
		else
			break;
	}while(1);

	while(1)
	{
		ff
		A=getpass("\nPassword : ");
		strcpy(u.pwd,A);ff;
		B=getpass("\nConfirm Password : ");ff;
//		printf("\n%s",u.pwd);
//		printf("\n%s",B);

		if(strcmp(u.pwd,B)==0)
		{
			break;
		}
		else
		{
			printf("\n\nPasswords do not match. ReEnter :\n");
		}
	}

	strcpy(u.pwd,A);
	ff;
	printf("\nEmail id : ");ff;
	scanf("%s",u.email);ff;getchar();
	printf("\nName : ");ff;
	scanf("%[^\n]",u.name);
	ff; printf("\nAmount to be credited to E-Wallet : ");
	scanf(" %lf",&u.amount);
	//u.tcount=0;
	fwrite(&u,sizeof(u),1,f);
	fclose(f);	ff;getchar();
	system("clear");
	printf("\nUser registered successfully .");
	ff;//system("clear");
	return 1;

}

void user_profile(user u)
{
	FILE* f;
	user v;
	f=fopen("user_data.txt","rb+");
	fseek(f,0,SEEK_SET);
	while(1)
	{
		if(feof(f))
			break;
		fread(&v,sizeof(v),1,f);
		if(strcmp(v.id,u.id)==0)
			break;
	}
	fseek(f,-1*sizeof(u),SEEK_CUR);

	double amt;
	int choice;
	char ch,c;

	do
	{
		system("clear");
		printf("Welcome to Toll Plaza\n");
		printf("\n%s's Profile\n\n",u.id);	
		printf("Please select from options below(1-7) : \n\n");
		printf("1. View profile information \n");
		//printf(". Update profile information \n");
		printf("2. Check E-Wallet Balance \n");
		printf("3. Credit E-Wallet \n");
		printf("4. View Transactions \n");
		printf("5. Logout\n");
		printf("6. Exit\n\n");
		ff;scanf("%d", &choice);ff;

 		switch(choice)
 		{
 			case 1:
 					system("clear");
 					printf("\nProfile Information : \n");
 					printf("\nCar no : %s \n",u.id);
 					printf("\nName : %s \n",u.name);
					printf("\nEmail id : %s \n\nPress Enter to go back. \n\n",u.email);
//					printf("\nCar no : %s \n",u.id);
					ff;getchar();
					getchar();
 					break;
 			case 2:
 					system("clear");
 					printf("\nYour E-Wallet Balance : %lf",u.amount);
 					printf("\n\nPress Enter to continue. \n\n");
 					ff;getchar();getchar();
 					break;
 			case 3:
 					system("clear");
 					printf("\nCurrent Balance : %lf",u.amount);
 					printf("\nCredit E-Wallet Balance : \n");
 					printf("\nEnter Credit amount : ");
 					scanf("%lf",&amt);
 					u.amount+=amt;			
 					printf("\nUpdated Balance : %lf \n\nPress Enter to go back. ",u.amount);
 					//fseek(f,-1,SEEK_CUR);
 					fwrite(&u,sizeof(u),1,f);
 					ff;getchar();getchar();
 					break;
 			case 4:
 					user_transaction(u);
 					break;
 			case 5:
					system("clear");
					printf("\nDo you really want to Logout?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					//fclose(f);
					if(c=='y'||c=='Y')
					{
						fclose(f);
						return ;	
					}
 					break;
 			case 6:
					ff;getchar();system("clear");
					printf("\nDo you really want to exit?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					if(c=='y'||c=='Y')
					{
						fclose(f);
						exit(0);
					}
					break;
 			default:
					ff;getchar();
					system("clear");
					printf("\nWrong choice. \n\nPress Enter to continue.\n");ff;getchar();
 					break;
 		}


	}while(1);
	fclose(f);
	return;
}

int admin_func()
{
	char ch,c;
	char id[21];
	char pwd[21];	
	admin a;
	stemp s;
	int i=0;
	int flag;
	int flag1;
	c='a';
	
	do
	{
		ch=c;
		ff; getchar();	system("clear");
		printf("\nAre you a registered admin? \n");
		printf("\n[Enter M to go back to main menu.] \n\nSelect your choice (Y/N/M)\n\n");
		scanf(" %c",&ch);
		ff getchar();
		switch(ch)
		{
			case 'Y':
			case 'y':	
						s=admin_login();
						if(s.flag)
						{
							system("clear");
							admin_profile(s.a);
						}
						break;
			case 'N':
			case 'n':
						system("clear");
						printf("\nYou have to register before going forward.");	
						printf("\n\nPress enter to continue. \n\n");
						ff;getchar();system("clear");

						flag1=admin_reg();


						break;

			case 'M':
			case 'm':
						system("clear");
						printf("\nDo you really want to return to main menu?(Y/N) : \n\n");	
						ff;scanf(" %c",&c);
						if(c=='y'||c=='Y')
							return 0;	
						break;

			default:
						system("clear");
						printf("\nWrong choice. \n");
						printf("\nPress Enter to continue. \n\n");			
						break;
						

		}

	}while(1);
	

	return 1;
}

stemp admin_login()
{	
	stemp s;
	FILE* f;
	char ch;
	admin a;
	char pwd[21];
	char id[21];
	char *A;
	s.flag=0;
	getchar();
	f=fopen("admin_data.txt","ab+");
	if(f==NULL)
	{
		system("clear");
		printf("\n404 Not Found. \n\nPlease try again later. \n");
		//fclose(f);
		return s;
	}

	system("clear");
	
	printf("\nEnter your login details: \n\n");
	printf("Email id : ");
	ff scanf("%s",id);
					
	int flag=0;
	int temp;

	while(1)
	{
	
		if(feof(f))
		{
			break;
		}
	
		fread(&a,sizeof(a),1,f);
		
		if(strcmp(a.id,id)==0)
		{
		
			flag=1;
		
			do
			{

				A=getpass("\nPassword : ");
				strcpy(pwd,A);
									
				if(strcmp(pwd,a.pwd)==0)
				{
					break;
				}		
			
				printf("\nIncorrect Password. \n\nDo you want to ReEnter your password? (y/n)  : ");
				ff;scanf(" %c",&ch);

			} while(ch=='y'||ch=='Y');
			
			if(ch=='n')
			{
				printf("\nLogin Unsuccessful. \n\n. ");
				fclose(f);
				return s;
			}					

			system("clear");

			printf("\nSuccessfully logged in.  \n\nPress Enter to continue.\n");
			ff;	getchar();
			
			break;
		}

	}

	if(!flag)
	{
		printf("\nAdmin not found. \n");
		ff getchar();
		fclose(f);
		return s;
	}
	s.flag=1;
	s.a=a;
	fclose(f);	return s;
}

int admin_reg()
{

	char ch;
	char *A,*B,*C;
	int flag;
	admin u,v;

	printf("\nYou are being redirected to registration page. ");
	printf("\n\nPress q followed by Enter to go back.\n");
	printf("\nPress Enter to continue.\n\n");
	ff;scanf("%c",&ch);

	if(ch=='q'||ch=='Q')
	{
		return -1;
	}
	ff;system("clear");

	C=getpass("\nEnter Pass Key to register admin : ");
	if(strcmp(C,ADMINPASS)!=0)
	{
		printf("\n\nWrong Pass Key . \n\nCannot Register. \n\nPress Enter to continue. ");
		ff;
		return -1;
	}
	printf("\nPress Enter to continue. ");
	ff; getchar();
	system("clear");

	FILE* f=fopen("admin_data.txt","ab+");
	printf("\nREGISTRATION PAGE.\n\n");
	printf("Enter the following details : \n\n");
	
	do{
		
		flag=1;
		printf("Email id : ");
		ff; scanf("%s",u.id);					
	
		fseek(f,0,SEEK_SET);
	
		while(!feof(f))
		{				
			fread(&v,sizeof(u),1,f);
			if(strcmp(u.id,v.id)==0)
			{
				flag=0;
				break;
			}
		}
		if(!flag)
		{
			ff;system("clear");
			printf("\nAdmin already exists. \n\nReEnter ");
		}
		else
			break;
	}while(1);

	while(1)
	{
		ff
		A=getpass("\nPassword : ");
		strcpy(u.pwd,A);ff;
		B=getpass("\nConfirm Password : ");ff;
//		printf("\n%s",u.pwd);
//		printf("\n%s",B);

		if(strcmp(u.pwd,B)==0)
		{
			break;
		}
		else
		{
			printf("\n\nPasswords do not match. ReEnter :\n");
		}
	}

	strcpy(u.pwd,A);
	ff;
	u.income=0;
	//u.tcount=0;
	fwrite(&u,sizeof(u),1,f);

	fclose(f);	ff;getchar();
	system("clear");
	printf("\nAdmin registered successfully .");
	ff;//system("clear");
	return 1;

}

void admin_profile(admin u)
{
	FILE* f;
	admin v;
	f=fopen("admin_data.txt","rb+");
	fseek(f,0,SEEK_SET);
	while(1)
	{
		if(feof(f))
			break;
		fread(&v,sizeof(v),1,f);
		if(strcmp(v.id,u.id)==0)
			break;
	}
	fseek(f,-1*sizeof(u),SEEK_CUR);

	double amt;
	int choice;
	char ch,c;

	do
	{
		system("clear");
		printf("Welcome to Toll Plaza\n");
		printf("\nADMIN %s's Profile\n\n",u.id);	
		printf("Please select from options below(1-7) : \n\n");
		printf("1. View Total Income \n");
		//printf(". Update profile information \n");
		printf("2. View Transactions \n");
		printf("3. Logout\n");
		printf("4. Exit\n\n");
		ff;scanf("%d", &choice);ff;

 		switch(choice)
 		{
 			case 1:
 					system("clear");
 					admin_income(u);
// 					printf("\nProfile Information : \n");
// 					printf("\nTotal Income : %lf \n",u.income);
// 					printf("\nName : %s \n",u.name);
//					printf("\nEmail id : %s \n\nPress Enter to go back. \n\n",u.email);
//					printf("\nCar no : %s \n",u.id);
					ff;getchar();
					getchar();
 					break;
 			case 2:
 					admin_transaction(u);
  					break;
 			case 3:
					system("clear");
					printf("\nDo you really want to Logout?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					//fclose(f);
					if(c=='y'||c=='Y')
					{
						fclose(f);
						return ;	
					}
 					break;
 			case 4:
					ff;getchar();system("clear");
					printf("\nDo you really want to exit?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					if(c=='y'||c=='Y')
					{
						fclose(f);
						exit(0);
					}
					break;
 			default:
					ff;getchar();
					system("clear");
					printf("\nWrong choice. \n\nPress Enter to continue.\n");ff;getchar();
 					break;
 		}


	}while(1);
	fclose(f);
	return;
}

void transaction()
{
	FILE* f2=fopen("transaction.txt","ab+");
	FILE* f1=fopen("user_data.txt","rb+");
	user u,v;
	trans t;
	int flag=0;
	double amt=77.75;
//	char date[15]="19/01/2017";

	system("clear");
	if(f1==NULL)
	{
		printf("\nNo user Registered.\n\nUsers MUST be registered. \n\nPress Enter to continue.\n\n");
		ff; getchar();getchar();
		fclose(f2);
		return;
	}
	printf("\nToll Transaction Page : \n");
	printf("\nEnter Car no : ");
	ff;scanf("%s",u.id);

	while(!feof(f1))
	{

		fread(&v,sizeof(v),1,f1);
		if(strcmp(v.id,u.id)==0)
		{
			flag=1;
			break;
		}

		}

	if(!flag)
	{
		printf("\n1User not found. \n\nYou must register yourself.\n\nPress ENter to continue. ");
		ff;getchar();
		fclose(f1);fclose(f2);
		return;
	}
//	fseek(f,-1*sizeof(u),SEEK_CUR);

	fseek(f1,-1*sizeof(v),SEEK_CUR);
	printf("\nToll Tax : %lf\n",amt);
	if(v.amount<amt)
	{
		printf("\nCurrent amount in your E-Wallet : %lf\n",v.amount);

		printf("\nYou do not have the required amount in your E-Wallet. \n");
		printf("\nYou cannot pass... \n\nPress Enter to continue...\n");
		ff;getchar();
	}
	else
	{
		time_t ltime=time(NULL);
		strcpy(t.id,v.id);
		t.amt=amt;
		strcpy(t.time_stamp,asctime( localtime(&ltime)));
		
		printf("\nCurrent amount in your E-Wallet : %lf\n",v.amount);
		v.amount=v.amount-amt;
		printf("\nFinal amount in your E-Wallet : %lf\n",v.amount);
		printf("\nTransaction complete. \n");
/*		if(v.tcount>10)		
		{
			v.tcount=0;
		}
		v.t[v.tcount].amt=amt;
		strcpy(	v.t[v.tcount].date,date);
		v.tcount++;*/
		fwrite(&v,sizeof(v),1,f1);
		fwrite(&t,sizeof(t),1,f2);
		ff;getchar();
	}
	fclose(f1);
	fclose(f2);
	ff;getchar();
	return;
}

void update_income()
{
	
	return;
}

void user_transaction(user u)
{
	trans v;
	int i=1;
	system("clear");ff;
	getchar();
	printf("\nTransactions of user (Date wise) %s \n",u.id);
	FILE* f=fopen("transaction.txt","ab+");
	fseek(f,0,SEEK_CUR);
	while(!feof(f))
	{
		fread(&v,sizeof(v),1,f);
		if(strcmp(v.id,u.id)==0)
		{
			printf("\n%d . %s : %lf\n",i,v.time_stamp,v.amt);
			i++;
		}
	}
	fclose(f);
	ff;getchar();
	return;
}
void admin_transaction(admin a)
{
	trans v;
	int i=1;
	system("clear");ff;
	printf("\nADMIN'S PROFILE : \n\nTransactions (Date wise)  \n");
	FILE* f=fopen("transaction.txt","ab+");
	fseek(f,0,SEEK_CUR);
	while(!feof(f))
	{
		fread(&v,sizeof(v),1,f);
		
		printf("\n%d . Date : %s    Amount : %lf\n",i,v.time_stamp,v.amt);
		i++;
	}
	fclose(f);	
	ff;getchar();getchar();
	return;
}
void admin_income(admin a)
{
	trans v;
	admin u;
	int i=1;
	double inc=0;
	system("clear");ff;
	printf("\nADMIN's PROFILE : \n\nTotal Income :  ");
	FILE* f=fopen("transaction.txt","ab+");
	FILE* g=fopen("admin_data.txt","rb+");

	fseek(f,0,SEEK_SET);
	while(!feof(f))
	{
		fread(&v,sizeof(v),1,f);
		
		//printf("\n%d . %s : %lf\n",i,v.time_stamp,v.amt);
		inc+=v.amt;
		i++;
	}

	fseek(g,0,SEEK_SET);
	while(!feof(g))
	{
		fread(&u,sizeof(u),1,g);
		if(strcmp(u.id,a.id)==0)
		{
			break;
		}
	}
	a.income=inc;
	fseek(g,-1*sizeof(a),SEEK_CUR);
	fwrite(&a,sizeof(a),1,g);
	printf("%lf\n",a.income);
	printf("\nPress Enter to continue. 	");
	fclose(g);
	fclose(f);	
	ff;

	return;
}
