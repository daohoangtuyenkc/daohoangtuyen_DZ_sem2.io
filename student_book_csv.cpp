#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<conio.h>
#define MAX 100
#define __MAX_SIZE 256



typedef struct students{
        char ID[15];
        char name[10];
        char surname[15];
        char patronymic[15];
        char faculty[10];
        char special[20];
} typestudents;

typedef struct sach{
	char isbn[20];
	char author[50];
	char booksname[50];
	int number;
	int access;
} books;

typedef struct sinhvien{
	char isbn[15];
	char ID[15];
	char data[15];
} typebook;

// All Function in program

char *trim(char *s); 
void look_student(); //view information of students, who borrowed book by ISBN of book
void look_book();  // view information of book, which student borrowed by ID of student
void want_check(); // function borrow or return books
void gettime(const char s[], char *ID); // Get time
   
                // To run program, You need create 2 files "book.csv" and "student.csv".
		// In 2 file had availables a little information about books and student - like Data structure above
                // To have information about books and students, can borrow or return book
                // Then, You run code, choose borrow books, to from here, you can run other function.
              
int main(){
     int select;
     do{
		
  	system("cls");
        printf("\t\t*____LIBRARY____*\n\n");
        printf("\t1: View book by ID of student\n");
	printf("\t2: View of student by isbn of book\n");
        printf("\t3: Borrow, return books\n");
        printf("\t4: Complete the work\n");
        printf("\nChoose: ");
        scanf("%d", &select);

        switch(select)
        {
            case 1:
                {
                	system("cls");
			look_book();
			system("pause");
                        break;
                }

            case 2:
                {
                	system("cls");
                	look_student();
                	system("pause");
                        break;
                }

            case 3:
                {
                	system("cls");
                	want_check();
                	system("pause");
                        break;
                }

            case 4:
                {
                	system("cls");
                	goto END;
                        break;
                }
            default: printf("\nErrors occur when entering orders?");
        }
    }
    while((select == 1) || (select == 2) || (select == 3) || (select == 4));
    END: 
    system("pause");
}

// function to remove string ',' from string s
char *trim(char *s) 
{
    int i = strlen(s) - 1;
    while (s[i] == ',' ) i--;
    s[i+1] = 0;
    return s;
}

// view information of book by ID of students borrowed book
void look_book(){ 
	fflush(stdin);
	FILE *f = fopen("student_book.csv", "rb");
	
	typebook bai3;
	char record[MAX];
	char *k =NULL;
	printf("\nEnter the ID of students:");
	fflush(stdin);
	scanf("%s", record);
	printf("\nInformation of books:");
	printf("\n%15s %10s %20s %18s %8s" , "ISBN", "Author", "BookName", "Access", "Number");
	while(!feof(f)){
		fscanf(f, "%s %s %s\n", bai3.isbn, bai3.ID, bai3.data);
		if(strcmp(trim(bai3.ID), record)==0){
			k = trim(bai3.ID);
			FILE *fl= fopen("book.csv","rb");
			books sv;
			while(!feof(fl)){
					fscanf(fl, "\n%[^,], %[^,], %[^,], %d, %d" , sv.isbn, sv.author, sv.booksname, &sv.number, &sv.access);
					if(strcmp(trim(sv.isbn), trim(bai3.isbn))==0){
						
						printf("\n%15s %20s %20s %5d %5d" , sv.isbn, sv.author, sv.booksname, sv.number, sv.access);
						printf("\n");
					}
			}
			fclose(fl);

		}
	}
	if(k!= NULL){
		 gettime("View book by ID of student", k);
	}else 
	     printf("\nErrors occur when importing ID of students\n");

	fclose(f);
}
// FUndction Get time, you work
void gettime(const char s[], char *ID){
    FILE *fx;
    // function time
    time_t     now;
    struct tm  ts;
    char       buf[80];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);
    printf("%s\n", buf);

    fflush(stdin);
    fx=fopen("library.log","a+");

    fprintf(fx,"\n\"%s\"",buf);
    fprintf(fx,";\"ID of students: %s\"", ID);
    fprintf(fx,";\"Activity: %s\"",s);

    fclose(fx);
}

// View information students by ISBN of book, which you borrow
void look_student(){ 
	fflush(stdin);
	FILE *f = fopen("student_book.csv", "rb");
	typebook bai3;
	int x = 1;
	char record[MAX];
	char *k = NULL;
	printf("\nEnter the ISBN number of books:");
	scanf("%s", record);
	printf("\nInformation students:");
	printf("\n%8s %10s %10s %10s %5s %20s", "ID", "Name", "Surname", "Patronymic", "Faculty", "Special");
	while(!feof(f)){
		fscanf(f, "%s %s %s\n", bai3.isbn, bai3.ID, bai3.data);
		if(strcmp(trim(bai3.isbn), record)==0){
			k =trim(bai3.ID);
			FILE *fl= fopen("student.csv","rb");
			typestudents sv;
			while(!feof(fl)){
					fscanf(fl, "%s %s %s %s %s %[^\n]", sv.ID, sv.name, sv.surname, sv.patronymic, sv.faculty, sv.special);
					if(strcmp(trim(sv.ID), trim(bai3.ID))==0){
						printf("\n%8s %10s %10s %10s %5s %20s", trim(sv.ID), trim(sv.name), trim(sv.surname), trim(sv.patronymic), trim(sv.faculty), trim(sv.special));
						printf("\n");
					}
			}
			fclose(fl);

		}
	}
	if(k!= NULL){
		 gettime("View students by ISBN of books", k);
	}else 
	     printf("\nErrors occur when importing ISBN of books\n");

	fclose(f);
}

// can borrow or return book
void want_check(){          
	FILE *f = fopen("student_book.csv", "a+");
	char isbn[MAX], record[MAX], tra[MAX];
	typebook tt[MAX];
	int select, i=0, n;
	int k =0;
	printf("\n Information borrow, return books:");
	printf("\n\t 1. Borrow books.");
	printf("\n\t 2. Return books.");
	printf("\n");

	fflush(stdin);
	scanf("%d", &select);
	switch(select){
		case 1: {
			int c = 0;
			fflush(stdin);
			printf("\nEnter ISBN number: "); gets(isbn);
			printf("\nEnter the ID: "); gets(record);
			FILE *fl= fopen("book.csv","rb"); // check ISBN of book exists in library or not?
			books sv;
			while(!feof(fl)){
					fscanf(fl, "\n%[^,], %[^,], %[^,], %d, %d" , sv.isbn, sv.author, sv.booksname, &sv.access, &sv.number);
					if(strcmp(trim(sv.isbn), isbn) == 0){
						c = 1;
						break;
						
					}
			}
			fclose(fl); 
                        // if ISBN not exist at library when c != 1
			if( c != 1){ 
                              printf("\n There are no books available to issue. when it will be nearest book delivered\n");
			}
			
			// if ISBN exist at library when c = 1
			else{          
                               while(!feof(f)){
				     fscanf(f, "%s %s %s\n", tt[i].isbn , tt[i].ID , tt[i].data);
				     if(strcmp(trim(tt[i].isbn), isbn)==0  && strcmp(trim(tt[i].ID), record)==0){
					 printf("\nYou still borrow books. Repayment: %s\n", tt[i].data); 
					 k =1;
				     }
			       }
			       fclose(f);
			       // If you don't borrow books, going on enter data return book, to borrow
			       if(k != 1){
				     printf("\nData return book: ");
			             fflush(stdin); 
			             gets(tra);
				     f = fopen("student_book.csv", "a+");
			             fprintf(f, "\n%s, %s, %s ", isbn, record , tra);
			             fclose(f);
			             printf("\nsuccessful borrow books\n");
			             gettime("borrow books", record);
			        }
			}
			
			break;
		}
		// return books
		case 2: {
			fflush(stdin);
			printf("\nEnter ISBN number: "); gets(isbn);
			printf("\nEnter the ID: "); gets(record);
			//Read file student_book.csv
			while(!feof(f)){
				fscanf(f, "%s %s %s\n", tt[i].isbn , tt[i].ID, tt[i].data);
				i++;
			}
			fclose(f);
			n = i;
			f = fopen("student_book.csv", "w");
			for(i=0; i< n; i++){
				if(strcmp(trim(tt[i].isbn), isbn)!=0  || strcmp(trim(tt[i].ID), record)!=0){
				     fprintf(f, "\n%s, %s, %s ", tt[i].isbn, tt[i].ID, tt[i].data);
				 }	 
			}
                        printf("\nsuccessfully return books\n");
			gettime("Return books", record);
			fclose(f);
			break;
		}
	}	
}
