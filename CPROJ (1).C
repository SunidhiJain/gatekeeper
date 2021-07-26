
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
//#define LEN 150

struct emp{
char empid[15];
char name[15];
char domain[15];
char time[15];
//int counter;
//int flag;

};

struct emp em;

//adding a employee

void insert()
{
 FILE *fp;
 fp = fopen("Record", "a+");
 printf("Enter the employee id  :");
 scanf("%s", em.empid);
 printf("Enter the Name      :");
 scanf("%s", em.name);
 printf("Enter domain     :");
 scanf("%s", em.domain);
 fwrite(&em, sizeof(em), 1, fp);
// fputs("\n",fp);
 fclose(fp);
}

// record retreival

void disp()
{
 FILE *fp1;
 fp1 = fopen("Record", "r");
 printf("\nemployee id\tName\tdomain\n\n");
 while (fread(&em, sizeof(em), 1, fp1))
 printf("  %s\t\t%s\t`%s\n", em.empid, em.name, em.domain);
 fclose(fp1);
}
// id availability

int avlid(char* id,char* filename)
{
 FILE *fp;

 fp = fopen(filename, "r");
 while (!feof(fp))
 {
  fread(&em, sizeof(em), 1, fp);

  if (strcmp(id ,em.empid)==0)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}



// search id---> return availability status of id
int search()
{ char id[15];
 int avl;
 printf("\nEnter the employee id you want to search  :");
 scanf("%s", &id);
 avl = avlid(id,"Record");
return avl;
 }

//delete existing employee record


void delet()
{
 FILE *fpo;
 FILE *fpt;
 char id[15];
 char s[15];
 printf("Enter the employee's id you want to delete :");
 scanf("%s", &id);
 if (avlid(id,"Record") == 0)
  printf("employee %s is not available in the file\n", id);
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&em, sizeof(em), 1, fpo))
  {
   strcpy(s ,em.empid);
   if (strcmp(s,id)!=0)
    fwrite(&em, sizeof(em), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&em, sizeof(em), 1, fpt))
   fwrite(&em, sizeof(em), 1, fpo);
  printf("\nRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }

}
struct emp emp1;
void login(char* id)
{

	FILE *fp;
	time_t curtime;
	time(&curtime);
	strcpy(emp1.time,ctime(&curtime));
	strcpy(emp1.empid,id);

	fp = fopen("login", "a+");
	fwrite(&emp1, sizeof(emp1), 1, fp);
	printf("logged in successfully");
      //	fputs("\n",fp);
	fclose(fp);

}





struct emp emp2;

void logout(char* id)
{
	FILE *fp;
	int avl;
	avl=avlid(id,"login");
	if(avl==1)
	{

	time_t curtime;
	time(&curtime);
       strcpy(emp2.time,ctime(&curtime));
	strcpy(emp2.empid,id);
	fp = fopen("logout", "a");
	fwrite(&emp2, sizeof(emp2), 1, fp);
	printf("\n\t logged out sucessfully");
	fclose(fp);

	}
	else
	printf("kindly first login");

}

int main()
{
	 int flag=0;
	 int pass;
	 char* g;
	 char* temp;
	 time_t tme;
	 char* user;
	int c1;
	int m=1;
	int c2;
	int n,r,i;
	char arg[10];
	int ch=1;
	do{
	printf("\n\t WELCOME TO SS COMPANY");
	printf("\n\t access to:");
	printf("\n\t1. Admin");
	printf("\n\t2. Employee");

	printf("\n\t Enter choice:");
	scanf("%d",&c1);
	switch(c1)
       {  case 1: while(flag!=1){
		  printf("\n\t enter user name:");
		  scanf("%s",user);
		  if(strcmp(user,"user")==0){
			 printf("\n\t enter password");
		       scanf("%d",&pass);
		   //   for(i=0;i<5;i++)
		    //  {
		    //   pass[i]=getch();
		    //  }
			 if(pass==12345){
				 printf("\n\t access granted");
				 flag=1;
			 }
		  }
		  else
		  printf("\n\t invalid access");
		  }
		  //actions by admin

		  while(m!=0){

		  printf("\n\t1.add new employee");
		  printf("\n\t2.Delete existing employee");
		  printf("\n\t3.retreive details");
		  printf("\n\t4. exit");


		  printf("\n\t enter choice");
		  scanf("%d",&c2);
		  switch(c2)
		  {
			case 1: insert();
				break;
			case 2: delet();
				break;
			case 3: disp();
				break;
			case 4: break;
		  }
		printf("\n\t do you want to continue:(1/0)");
		scanf("%d",&m);
		}
		break;
       //for employee
       case 2:
	printf("\n\t1.login");
	printf("\n\t2.logout");
	printf("\n\t3.exit");
	do{
		printf("\n\t enter action");
		scanf("%d",&n);

		switch(n)
		{
			case 1: printf("\n\t enter the employee id:");
				scanf("%s",&arg);
				r=avlid(arg,"Record");
				time(&tme);
				strcpy(g,ctime(&tme));
				for(i=0;i<10;i++)
				{
					temp[i]=g[i];
				}
				if(strstr(g,temp)&&avlid(arg,"login"))
				printf("\n\t already logged in");
				else
				{
				if(r)
					login(arg);
				else
					printf("\n\t invalid access");
				}
				break;
			case 2: printf("\n\t enter the employee id:");
				scanf("%s",&arg);
				logout(arg);
				break;
			/*case 3:  printf("\n\t enter the employee id:");
				scanf("%s",&arg);
				count(arg);
				break;*/
			case 3: exit(0);
				break;
			default: printf("\n\t enter valid choice");
		}
		printf("\n\t another user?:(1/0)");
		scanf("%d",ch);
		}while(ch==1);

		break;
	}
	}while(c1<=2);

return 0;
}
