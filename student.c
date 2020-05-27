#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <stdbool.h>
#define __MAX_SIZE 256


typedef struct Student student;
struct Student
{
	char ID[10];
	char FamilyName[__MAX_SIZE];
	char Name[__MAX_SIZE];
	char FatherName[__MAX_SIZE];
	char Faculty[10];
	char Specialist[__MAX_SIZE];
};


student Students[__MAX_SIZE];



//Part: Student
int readStudent(const char *filename); // Function read file student.csv
int comparingID(char a[7]); // check ID of student existed or not
void addingNewStudent(const char *filename); //add new students 
void searchingStudent(const char *filename); //searching information of any students in file "student.csv" by ID
void deletingStudent(const char *filename); // Delete students
void editingStudent(const char *filename); // Edit information of student 
void look_all_Students(const char *filename); // View All students
char *trim(char *s); // Function remove all string ',' in string s when read data in files


// Function MAIN

int main(int argc, char **argv)
{
	int n = readStudent("student.csv");
	bool daNhap = false;
	if (n == -1)
	{
		printf("\n\t ERROR #1: You opened file <<student.csv>>. You need close file!!!, to see and edit file.\n");
	}
	else
	{
		int x;
		while(true){
                system("cls");
		printf("******************************************\n");
                printf("**    CHUONG TRINH QUAN LY SINH VIEN    **\n");
		printf("**                Menu                  **\n");
                printf("**      1. Add New Student              **\n");
                printf("**      2. Delete Student               **\n");
                printf("**      3. Search any Student           **\n");
                printf("**      4. Edit Student                 **\n");
                printf("**      5. Show all students            **\n");
                printf("**      0. Finish                       **\n");
                printf("******************************************\n");
                printf("**          You want:                   **\n");
        
		scanf("%d", &x);
		fflush(stdin);
		switch(x)
		{
			case 1:
			{
				addingNewStudent("student.csv");
				printf("\nEnter any buttons!");
                                getch();
				break;
			}
			case 2:
			{
				deletingStudent("student.csv");
				printf("\nEnter any buttons!");
                                getch();
				break;				
			}
			case 3:
			{
				searchingStudent("student.csv");
				printf("\nEnter any buttons!");
                                getch();
				break;
			}
			case 4:
			{
				editingStudent("student.csv");
				printf("\nEnter any buttons!");
                                getch();
				break;
			}
			case 5:
			{
				look_all_Students("student.csv");
				printf("\nEnter any buttons!");
                                getch();
				break;
			}
			case 0:
			{
                                getch();
				return 0;
			}
			
			default:{
			     printf("\nNot any function");
                             printf("\nEnter any buttons!!");
                             getch();
                             break;
			}
		}
	    }
	}

	return 0;
}

char *trim(char *s) // Function remove all string ',' in string s when read data in files
{
    int i = strlen(s) - 1;
    while (s[i] == ',') i--;
    s[i+1] = 0;
    return s;
}

//Function read file student.csv
int readStudent(const char *filename)
{
	FILE *fs = fopen(filename, "a+");
	if (!fs) 
		return -1;
	
	//Read file
	rewind(fs);
	char tmp[__MAX_SIZE];
	int total = 0;
	while(fgets(tmp, __MAX_SIZE, fs))
	{
		fscanf(fs, "%s %s %s %s %s %[^\n]", Students[total].ID, Students[total].FamilyName, Students[total].Name, Students[total].FatherName, Students[total].Faculty, Students[total].Specialist);
		total++;
	}
	return total;
}

int comparingID(char a[7]) //compare which new ID existed or not
{
	int i;
	int temp = -1;
	for (i = 0; i < readStudent("student.csv"); i++)
	{
		if(strcmp(a, trim(Students[i].ID)) == 0)
			temp = i;
	}
	return temp;
}

//Add new students
void addingNewStudent(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	student newstudent;
	
	printf("ID:");
	gets(newstudent.ID);
	if (comparingID(trim(newstudent.ID)) != -1)
	{
		printf("ID of students existed!. Please enter other ID\n");
		fclose(fs);
	}	
	else 
	{
		printf("Family Name:");
		gets(newstudent.FamilyName);
		printf("Name:");
		gets(newstudent.Name);
		printf("Father Name:");
		gets(newstudent.FatherName);
		printf("Faculty:");
		gets(newstudent.Faculty);
		printf("Specialist:");
		gets(newstudent.Specialist);
		
		fprintf(fs, "\n%10s, %10s, %10s, %15s, %10s, %15s", trim(newstudent.ID), trim(newstudent.FamilyName), trim(newstudent.Name), trim(newstudent.FatherName), trim(newstudent.Faculty), trim(newstudent.Specialist));
		fclose(fs);
	}
}

//search information student by ID
void searchingStudent(const char *filename)
{
	FILE * fs = fopen(filename, "r");
	char searchitem[14];
	int total =0;
	rewind(fs);
	printf("ID:");
	fflush(stdin);
	gets(searchitem);
	int n = comparingID(trim(searchitem));
	
	if(n == -1)
	{
		printf("\nID doesn't exist. Students doesn't exist.");
		fclose(fs);
	}
	else
	{
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	        while(!feof(fs)){
     
	            fscanf(fs, "%s %s %s %s %s %[^\n]", Students[total].ID, Students[total].FamilyName, Students[total].Name, Students[total].FatherName, Students[total].Faculty, Students[total].Specialist);
	            if(total == n){
		           printf("%10s %10s %10s %15s %10s %15s\n", trim(Students[n].ID), trim(Students[n].FamilyName), trim(Students[n].Name), trim(Students[n].FatherName), trim(Students[n].Faculty), trim(Students[n].Specialist));
	            }
	            total++;
	        }
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
		fclose(fs);
	}
}
//delete students
void deletingStudent(const char *filename)
{
	FILE *fs;
	char deleteitem[__MAX_SIZE];
	printf("ID:");
	fflush(stdin);
	gets(deleteitem);
	
	fs = fopen(filename, "r");
	rewind(fs);
	int k = comparingID(trim(deleteitem)); 
	int n = readStudent(filename);
	fclose(fs);
	if (k != -1)
	{
		fs = fopen(filename, "w");
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != k)
				//printf("%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
				fprintf(fs, "\n%10s, %10s, %10s, %15s, %10s, %15s", trim(Students[i].ID), trim(Students[i].FamilyName), trim(Students[i].Name), trim(Students[i].FatherName), trim(Students[i].Faculty), trim(Students[i].Specialist));
		}
		fclose(fs);
		printf("\nRemoved from the library.");
	}
	else
		printf("\n ID of Students doesn't exist\n");
}
//Edit Students
void editingStudent(const char *filename)
{
	FILE *fs;
	student edititem;
	printf("\nID:");
	gets(edititem.ID);
	
	fs = fopen(filename, "r");
	rewind(fs);
	int k = comparingID(trim(edititem.ID)); 
	int n = readStudent(filename);
	fclose(fs);
	if (k != -1)
	{
		printf("Family Name:");
		gets(edititem.FamilyName);
		printf("Name:");
		gets(edititem.Name);
		printf("Father Name:");
		gets(edititem.FatherName);
		printf("Faculty:");
		gets(edititem.Faculty);
		printf("Specialist:");
		gets(edititem.Specialist);
		fs = fopen(filename, "w");
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != k)
				//printf("%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
				fprintf(fs, "\n%10s, %10s, %10s, %15s, %10s, %15s", trim(Students[i].ID), trim(Students[i].FamilyName), trim(Students[i].Name), trim(Students[i].FatherName), trim(Students[i].Faculty), trim(Students[i].Specialist));
			else
			    fprintf(fs, "\n%10s, %10s, %10s, %15s, %10s, %15s", trim(edititem.ID), trim(edititem.FamilyName), trim(edititem.Name), trim(edititem.FatherName), trim(edititem.Faculty), trim(edititem.Specialist));	
		}
		fclose(fs);
	}
	else
		printf("\n ID of Student doesn't exist\n ");
}
 // VIEW ALL students
 
void look_all_Students(const char *filename){
	FILE *fs;
	fs = fopen(filename, "r");
	rewind(fs);
	int k = readStudent(filename);
	int i;
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	for(i = 0 ; i < k ; i++){
		
		printf("%10s, %10s, %10s, %15s, %10s, %15s\n", trim(Students[i].ID), trim(Students[i].FamilyName), trim(Students[i].Name), trim(Students[i].FatherName), trim(Students[i].Faculty), trim(Students[i].Specialist));
	}
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	fclose(fs);
}
