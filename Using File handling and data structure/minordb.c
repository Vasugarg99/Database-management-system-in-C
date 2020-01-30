#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <dirent.h> 

typedef struct
{
  char* line;
  size_t input;
  ssize_t input_length;
   
}InputBuffer;

struct student
{
    char name[50];
    int roll;
    float marks;
    
};
struct employee
{
    char name[50];
    int id;
    float salary;
    
};

InputBuffer* create_Buffer()
{
  InputBuffer* input_buffer=malloc(sizeof(InputBuffer));
  input_buffer->line=NULL;
  input_buffer->input=0;
  input_buffer->input_length=0;
  return input_buffer;
}

void print_prompt()
{
  printf("DBMS>");
}

void check_input(InputBuffer* input_buffer)
{
  ssize_t input_read = getline(&(input_buffer->line),&(input_buffer->input_length),stdin);
  
  if(input_read<=0)
  {
    printf("     Error reading input");
    exit(EXIT_FAILURE);
  }
  input_buffer->input_length=input_read-1;
  input_buffer->line[input_read-1]=0;

}

void close_buffer(InputBuffer* input_buffer)
{
  free(input_buffer);
}

void insert_student()
{
  FILE *fptr;
    struct student *ptr;
    int i,j, noofrecords;
    printf("     Enter number of records: ");
    scanf("%d", &noofrecords);
    ptr = (struct student*) malloc (noofrecords * sizeof(struct student));
    fptr = fopen("Table/student", "a+"); //create a folder of name Table
    
    for(i=0; i<noofrecords; i++)
    {
        printf("     Name: ");
        scanf("%s",(ptr+i)->name);
        fprintf(fptr, "Name = %s \n", (ptr+i)->name);
        printf("     Roll no: ");
        scanf("%d",&(ptr+i)->roll);
       /* sscanf("%d","%s","%f",&(ptr+i)->roll,&(ptr+i)->name,&(ptr+i)->marks);*/
        fprintf(fptr, "Roll no = %d \n", (ptr+i)->roll);
        printf("     Marks: ");
        scanf("%f",&(ptr+i)->marks);
        fprintf(fptr, "Marks = %.2f \n", (ptr+i)->marks);
        
        printf("\n");
        //printf("\n");
    }
    fclose(fptr);
}

void insert_employee()
{
  FILE *fptr;
    struct employee *ptr;
    int i,j, noofrecords;
    printf("     Enter number of records: ");
    scanf("%d", &noofrecords);
    ptr = (struct employee*) malloc (noofrecords * sizeof(struct employee));
    fptr = fopen("Table/employee", "a+");
    
    for(i=0; i<noofrecords; i++)
    {
        printf("     Employee ID: ");
        scanf("%d",&(ptr+i)->id);
       /* sscanf("%d","%s","%f",&(ptr+i)->roll,&(ptr+i)->name,&(ptr+i)->marks);*/
        fprintf(fptr, "Emp id = %d \n", (ptr+i)->id);
        printf("     Name: ");
        scanf("%s",(ptr+i)->name);
        fprintf(fptr, "Name = %s \n", (ptr+i)->name);
        printf("     Salary: ");
        scanf("%f",&(ptr+i)->salary);
        fprintf(fptr, "Salary = %.2f \n", (ptr+i)->salary);

        printf("\n");
        //printf("\n");
    }
    fclose(fptr);
}

void execute_insert()
{
   char input[8];
   int i,j;
   char a[8]="student";
   printf("     Enter table name: ");
   fgets(input,sizeof(input),stdin);
  
   int result=strcmp(a,input);
   
   if(result==0)
   {
    insert_student();
   }
   else
   {
    insert_employee();
   }
   
}

void select_student()
{
  FILE *infile; 
  struct student input; 
  
  infile = fopen ("Table/student", "r"); 
  if (infile == NULL) 
  { 
    fprintf(stderr, "\n Error opening file\n"); 
    exit (1); 
  } 
  
  // read file contents till end of file 
  while(fread(&input, sizeof(struct student), 1, infile))
  {
    printf("%s\n%d\n%.2f\n",input.name,input.roll,input.marks); 
  }
  // close file 
  fclose (infile); 

}

void select_employee()
{
  FILE *infile; 
  struct employee input; 
  
  infile = fopen ("Table/employee", "r"); 
  if (infile == NULL) 
  { 
    fprintf(stderr, "\n Error opening file\n"); 
    exit (1); 
  } 
  
  // read file contents till end of file 
  while(fread(&input, sizeof(struct student), 1, infile)) 
    printf ("%s\n%d\n%.2f\n", input.name, input.id, input.salary); 

  // close file 
  fclose (infile); 
}

void execute_select()
{
   char input[8];
   int i,j;
   char a[8]="student";
   printf("     Enter table name: ");
   fgets(input,sizeof(input),stdin);
  
   int result=strcmp(a,input);
   
   if(result==0)
   {
    select_student();
   }
   else
   {
    select_employee();
   }
  
}

void show_table()
{
  struct dirent *de; // Pointer for directory entry 

  // opendir() returns a pointer of DIR type. 
  DIR *dr = opendir("Table"); 

  if (dr == NULL) // opendir returns NULL if couldn't open directory 
  { 
    printf(" Could not open current directory" ); 
     
  } 

  // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
  // for readdir() 
  while ((de = readdir(dr)) != NULL) 
      printf("%s\n", de->d_name); 

  closedir(dr);  
}

void execute_delete()
{
  char input[8];
   int i,j;
   char a[8]="student";
   printf("     Enter table name to delete: ");
   fgets(input,sizeof(input),stdin);
  
   int result=strcmp(a,input);
   
   if(result==0)
   {
    remove("Table/student");
    printf("\n     Table deleted sucessfully!\n");
    
   }
   else
   {
    remove("Table/employee");
    printf("\n     Table deleted sucessfully!\n");
   }
  
}

int main()
{
  InputBuffer* input_buffer = create_Buffer();
    
  printf("\n\t                              MINOR PROJECT\t\n\n\t                    ACESSSING FILE SYSTEM THROUGH C\t\n\n");
  while(true)
  {
    print_prompt();
    check_input(input_buffer);
    if(strcmp(input_buffer->line,"exit")==0)
    {
      close_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    }
    if(strcmp(input_buffer->line,"insert")==0)
    {
      execute_insert();
      /*Row* a= malloc(sizeof(Row));
      int args_assigned = sscanf(input_buffer->line,"insert %d %s %s",&(a->id),a->name,a->email);*/
    }
    if (strcmp(input_buffer->line,"select")==0)
    {
      execute_select();
    }
    if (strcmp(input_buffer->line,"delete")==0)
    {
      execute_delete();
    }
    if(strncmp(input_buffer->line,"show",4)==0)
    {
      show_table();
    }
    /*else
    {
      printf("Unrecognized command '%s'\n",input_buffer->line);
    }*/

  }
  return 0;
}