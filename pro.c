#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   

#define ff fflush(stdin);
typedef struct{
	char id[21];
	char pwd[21];

} user;

int user_func();
int user_reg();
void user_profile(FILE* f,user u);
int admin_func();

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
		printf("1. User \n");
		printf("2. Administrator \n");
		printf("3. Exit \n\n");	
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
	

	FILE* f;
	char ch,c;
	char id[21]="";
	char s[12];
	char pwd[21];	
	user u;
	int i=0;
	int flag;
	int flag1;

	f=fopen("user_data.txt","ab+");
	if(f==NULL)
	{
		system("clear");
		printf("\n404 File not found. \n\nPlease try again later. \n");
		fclose(f);
		return -1;
	}
	
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
						system("clear");
						printf("\nEnter your login details: \n\n");
						printf("Car no : ");
						scanf("%s",id);
						ff; getchar();
						char *A;					
						fseek(f,0,SEEK_SET);
						flag=0;

						while(!feof(f))
						{
							fread(&u,sizeof(u),1,f);
						
							if(strcmp(u.id,id)==0)
							{
								flag=1;
								do{

									A=getpass("\nPassword : ");
									strcpy(pwd,A);
									
									if(strcmp(pwd,u.pwd)==0)
									{
										break;
									}
						
//									if(i==2){i++;break;}
						
									printf("\n\n%d attempts left\n",2-i );
									i++;

								} while(i<3);

								if(i==3)
								{

									printf("\n\nPassword attempt unsuccesful thrice. \n\n");
									fclose(f);
									ff;	
									getchar();
									return -1;
								}
								

								system("clear");

								printf("\nSuccessfully logged in.  \n\nPress Enter to continue.\n");
								ff;

								user_profile(f,u);			
								flag=1;
								break;
							}

						}

						if(!flag)
						{
							printf("\nUser not found. \n");
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
						fclose(f);
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
	
	fclose(f);
	return 1;
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

	fwrite(&u,sizeof(u),1,f);

	fclose(f);	
	printf("\nUser registered successfully .");
	ff getchar();system("clear");
	return 1;

}

void user_profile(FILE* f,user u)
{

	int choice;
	char ch,c;
	do
	{
		system("clear");
		printf("Welcome to Toll Plaza\n");
		printf("\n%s's Profile\n\n",u.id);	
		printf("Please select from options below(1-7) : \n\n");
		printf("1. View profile information \n");
		printf("2. Update profile information \n");
		printf("3. Check E-Wallet Balance \n");
		printf("4. Credit E-Wallet \n");
		printf("5. View Transactions \n");
		printf("6. Logout\n");
		printf("7. Exit\n\n");
		ff;scanf("%d", &choice);ff;

 		switch(choice)
 		{
 			case 1:

 					break;
 			case 2:

 					break;
 			case 3:

 					break;
 			case 4:

 					break;
 			case 5:

 					break;
 			case 6:
					system("clear");
					printf("\nDo you really want to return to main menu?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					fclose(f);
					if(c=='y'||c=='Y')
						return ;	
 					break;
 			case 7:
					ff;getchar();system("clear");
					printf("\nDo you really want to exit?(Y/N) : \n\n");	
					ff;scanf(" %c",&c);
					if(c=='y'||c=='Y')
						exit(0);
					break;

 					break;
 			default:
					ff;getchar();
					system("clear");
					printf("\nWrong choice. \n\nPress Enter to continue.\n");ff;getchar();
 					break;
 		}


	}while(0);

	return;
}

int admin_func()
{

	return 1;
}