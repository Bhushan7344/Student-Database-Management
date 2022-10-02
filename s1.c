#include<stdio.h>
#include<stdlib.h>


struct student
{
    int rno;
    char name[20];
    struct subject
    {
        int score;
        char sname[20];
        int mark;
    }sub[5];
    int total;
    float per;
};
typedef struct student Student;




void create()
{
    Student *s;
    FILE *fp;
    int n,i,j; //i for each student and j for each subject
    printf("Enter the number of students: ");
    scanf("%d",&n);
    s=(Student*)calloc(n,sizeof(Student));
    fp=fopen("StudentDB.txt","w");
    for(i=0;i<n;i++)
    {
        s[i].total=0;
        s[i].per=0;
        printf("Enter the Roll Number: ");
        scanf("%d",&s[i].rno);
        printf("Enter the Name: ");
        scanf("%s",s[i].name);
        for(j=0;j<5;j++)
        {
            printf("Enter the Marks of Subject %d: ",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total+=s[i].sub[j].mark;
        }
        s[i].per=s[i].total/5.0;
        fwrite(&s[i],sizeof(Student),1,fp);
    }
    fclose(fp);
}




void display()
{
    Student s1;
    int j;
    FILE *fp;
    fp=fopen("StudentDB.txt","r");
    while(fread(&s1,sizeof(Student),1,fp))
    {
        printf("\n%d %s ",s1.rno,s1.name);
        for(j=0;j<5;j++)
        {
           printf("%d ",s1.sub[j].mark);
        }
        printf("%d %.2f",s1.total,s1.per);
    }
    fclose(fp);
}





void append()
{
    Student *s;
    FILE *fp;
    int n,i,j; //i for each student and j for each subject
    printf("Enter the number of students: ");
    scanf("%d",&n);
    s=(Student*)calloc(n,sizeof(Student));
    fp=fopen("StudentDB.txt","a");
    for(i=0;i<n;i++)
    {
        s[i].total=0;
        s[i].per=0;
        printf("Enter the Roll Number: ");
        scanf("%d",&s[i].rno);
        printf("Enter the Name: ");
        scanf("%s",s[i].name);
        for(j=0;j<5;j++)
        {
            printf("Enter the Marks of Subject %d: ",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total+=s[i].sub[j].mark;
        }
        s[i].per=s[i].total/5.0;
        fwrite(&s[i],sizeof(Student),1,fp);
    }
    fclose(fp);
}





void noofrec()
{
    Student s1;
    FILE *fp;
    fp=fopen("StudentDB.txt","r");
    fseek(fp,0,SEEK_END);
    int n=ftell(fp)/sizeof(Student);
    printf("\nNumber of Records: %d\n",n);
    fclose(fp);
}





void search()
{
    Student s1;
    FILE *fp;
    int j,roll,found;
    fp=fopen("StudentDB.txt","r");
    printf("Enter the Roll number to Search: ");
    scanf("%d",&roll);
    while(fread(&s1,sizeof(Student),1,fp))
    {
        if(s1.rno==roll)
        {
            found=1;
            printf("\nROLL   Name  Marks1  Marks2  Marks3  Marks4  Marks5  Total  Percentage\n");
            printf("\n  %d  %s  ",s1.rno,s1.name);
            for(j=0;j<5;j++)
            {
               printf("   %d   ",s1.sub[j].mark);
            }
            printf("   %d   %.2f   ",s1.total,s1.per);
        }
    }
    if(!found)
    printf("\nRecord not found.\n");

    fclose(fp);
}





void update()
{
    Student s1;
    FILE *fp,*fp1;
    int j,roll,found;
    fp=fopen("StudentDB.txt","r");
    fp1=fopen("temp.txt","w");
    printf("Enter the Roll number to Update: ");
    scanf("%d",&roll);
    while(fread(&s1,sizeof(Student),1,fp))
    {
        if(s1.rno==roll)
        {
            s1.total=0;
            s1.per=0;
            found=1;
            printf("Enter the new Name: ");
            scanf("%s",s1.name);
            for(j=0;j<5;j++)
            {
                printf("Enter the new Marks of Subject %d: ",j+1);
                scanf("%d",&s1.sub[j].mark);
                s1.total+=s1.sub[j].mark;
            }
            s1.per=s1.total/5.0;
        }
        fwrite(&s1,sizeof(Student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found)
    {
        fp1=fopen("temp.txt","r");
        fp=fopen("StudentDB.txt","w");
        while(fread(&s1,sizeof(Student),1,fp1))
        {
          fwrite(&s1,sizeof(Student),1,fp);
        }
        fclose(fp);
        fclose(fp1);
    }
    else
    {
      printf("\nRecord not found.\n");
    }
}


void delete_rec()
{
    Student s1;
    FILE *fp,*fp1;
    int j,roll,found=0;
    fp=fopen("StudentDB.txt","r");
    fp1=fopen("temp.txt","w");
    printf("Enter the Roll number to Delete: ");
    scanf("%d",&roll);
    while(fread(&s1,sizeof(Student),1,fp))
    {
        if(s1.rno==roll)
          found=1;
        else
          fwrite(&s1,sizeof(Student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found)
    {
        fp1=fopen("temp.txt","r");
        fp=fopen("StudentDB.txt","w");
        while(fread(&s1,sizeof(Student),1,fp1))
        {
          fwrite(&s1,sizeof(Student),1,fp);
        }
        fclose(fp);
        fclose(fp1);
        printf("Record deleted successfully\n");
    }
    else
    {
      printf("\nRecord not found.\n");
    }
}



sort_temp()
{
    Student *s,s1;
    FILE *fp;
    int i,j;
    fp=fopen("StudentDB.txt","r");
    fseek(fp,0,SEEK_END);
    int n=ftell(fp)/sizeof(Student);
    s=(Student*)calloc(n,sizeof(Student));
    rewind(fp);
    for(i=0;i<n;i++)
        fread(&s[i],sizeof(Student),1,fp);
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(s[i].total<s[j].total)
            {
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
            }

        }
    }
    for(i=0;i<n;i++)
    {
        printf("\n%d %s ",s[i].rno,s[i].name);
        for(j=0;j<5;j++)
        {
          printf(" %d ",s[i].sub[j].mark);
        }
        printf(" %d  %.2f ",s[i].total,s[i].per);
    }
    fclose(fp);
}





void sort_perma()
{
       Student *s,s1;
    FILE *fp;
    int i,j;
    fp=fopen("StudentDB.txt","r");
    fseek(fp,0,SEEK_END);
    int n=ftell(fp)/sizeof(Student);
    s=(Student*)calloc(n,sizeof(Student));
    rewind(fp);
    for(i=0;i<n;i++)
        fread(&s[i],sizeof(Student),1,fp);
    fclose(fp);
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(s[i].total<s[j].total)
            {
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
            }
        }
    }
    fp=fopen("StudentDB.txt","w");
    for(i=0;i<n;i++)
    {
        printf("\n%d %s ",s[i].rno,s[i].name);
        for(j=0;j<5;j++)
        {
          printf(" %d ",s[i].sub[j].mark);
        }
        printf(" %d  %.2f ",s[i].total,s[i].per);
        fwrite(&s[i],sizeof(Student),1,fp);
    }
    fclose(fp);
}
void sort_name()
{
    Student *s,s1;
    FILE *fp;
    int i,j;
    fp=fopen("StudentDB.txt","r");
    fseek(fp,0,SEEK_END);
    int n=ftell(fp)/sizeof(Student);
    s=(Student*)calloc(n,sizeof(Student));
    rewind(fp);
    for(i=0;i<n;i++)
        fread(&s[i],sizeof(Student),1,fp);
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(strcmp(s[i].name,s[j].name)>0)
            {
                s1=s[i];
                s[i]=s[j];
                s[j]=s1;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        printf("\n %d %s ",s[i].rno,s[i].name);
        for(j=0;j<5;j++)
        {
          printf(" %d ",s[i].sub[j].mark);
        }
        printf(" %d  %.2f ",s[i].total,s[i].per);
        }
    fclose(fp);

}



void sort()
{
    int ch;
    printf("\n1.Temporarily Sort\n2.Permanently Sort\n3.Sort by Name\nChoose an option: ");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:sort_temp();break;
        case 2:sort_perma();break;
        case 3:sort_name();break;
        default:printf("\nInvalid option.\n");
    }
}



void encrypt()
{
    char ch;
    FILE *fps, *fpt;
    fps = fopen("StudentDB.txt", "r");
    if(fps == NULL)
        return;
    fpt = fopen("temp1.txt", "w");
    if(fpt == NULL)
        return;
    ch = fgetc(fps);
    while(ch != EOF)
    {
        ch = ch+100;
        fputc(ch, fpt);
        ch = fgetc(fps);
    }
    fclose(fps);
    fclose(fpt);
    fps = fopen("StudentDB.txt", "w");
    if(fps == NULL)
        return 0;
    fpt = fopen("temp1.txt", "r");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = fputc(ch, fps);
        ch = fgetc(fpt);
    }
    fclose(fps);
    fclose(fpt);
    printf("\n************************File Encrypted Successfully!************************\n");
}
void decrypt()
{
    char ch;
    FILE *fps, *fpt;
    fps = fopen("StudentDB.txt", "w");
    if(fps == NULL)
        return 0;
    fpt = fopen("temp1.txt", "r");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = ch-100;
        fputc(ch, fps);
        ch = fgetc(fpt);
    }
    fclose(fps);
    fclose(fpt);
    printf("\n************************File Decrypted Successfully!************************\n");
}


void passw()
{
    FILE *fp;
    char ch;
    int j,i=0;
    char pass[10],password[10];
    fp=fopen("Password.txt","w+");
    printf("\nEnter password: ");
    while(ch!=13)
    {
        ch=getch();
        if(ch!=13 && ch!=8)
        {
            putch('*');
            pass[i]=ch;
            i++;
        }
    }
    pass[i]='\0';
    for(j=0;j<=9;j++)
    {
        password[j]=fgetc(fp);
    }
    password[j]='\0';
    if(strcmp(password,pass)>0)
    {
        printf("\nPassword matched\n");
    }
    else
    {
        printf("\nWrong password\n");
        passw();
    }
}


void encrypt_password()
{
    char ch;
    FILE *fps, *fpt;
    fps = fopen("Password.txt", "r");
    if(fps == NULL)
        return;
    fpt = fopen("temp2.txt", "w");
    if(fpt == NULL)
        return;
    ch = fgetc(fps);
    while(ch != EOF)
    {
        ch = ch+100;
        fputc(ch, fpt);
        ch = fgetc(fps);
    }
    fclose(fps);
    fclose(fpt);
    fps = fopen("Password.txt", "w");
    if(fps == NULL)
        return 0;
    fpt = fopen("temp2.txt", "r");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = fputc(ch, fps);
        ch = fgetc(fpt);
    }
    fclose(fps);
    fclose(fpt);
    printf("\n************************Password Encrypted Successfully!************************\n");
}

void decrypt_password()
{
    char ch;
    FILE *fps, *fpt;
    fps = fopen("Password.txt", "w");
    if(fps == NULL)
        return 0;
    fpt = fopen("temp2.txt", "r");
    if(fpt == NULL)
        return 0;
    ch = fgetc(fpt);
    while(ch != EOF)
    {
        ch = ch-100;
        fputc(ch, fps);
        ch = fgetc(fpt);
    }
    fclose(fps);
    fclose(fpt);
    printf("\n************************Password Decrypted Successfully!************************\n");
}

void main()
{
    int ch;
    decrypt_password();
    passw();
    decrypt();
    while(1)
    {
        printf("\n1.CREATE\n2.DISPLAY\n3.APPEND\n4.Number of Records\n5.Search a record\n6.Update\n7.Delete a Record\n8.Sort the Data\n9.EXIT\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:create();break;
            case 2:display();break;
            case 3:append();break;
            case 4:noofrec();break;
            case 5:search();break;
            case 6:update();break;
            case 7:delete_rec();break;
            case 8:sort();break;
            case 9:encrypt();encrypt_password();exit(0);
            default:printf("\nInvalid choice!\n");encrypt();encrypt_password();
        }
    }
}

