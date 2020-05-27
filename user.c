#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#define __MAX_SIZE 256

typedef struct Book book;
struct Book
{
	char ISBN[14];
	char Author[__MAX_SIZE];
	char Title[__MAX_SIZE];
	int All;
	int Free;
};

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

typedef struct User user;
struct User
{
	char Username[__MAX_SIZE];
	char Password[__MAX_SIZE];
	int ADbook;
	int ADstudent;
};

book Books[__MAX_SIZE];
student Students[__MAX_SIZE];
user Users[__MAX_SIZE];

//
char *trim(char *s);

//Part 1: Book

int part_1();
int readBook(const char *filename); 
int comparingISBN(char a[14]);
void look_all(const char *filename);
void addingNewBook(const char *filename);
void searchingBook(const char *filename);
void deletingBook(const char *filename);
void editingBook(const char *filename);

//Part 2: Student
void part_2();
int readStudent(const char *filename);
int comparingID(char a[7]);
void addingNewStudent(const char *filename);
void searchingStudent(const char *filename);
void deletingStudent(const char *filename);
void editingStudent(const char *filename);
void look_all_Students(const char *filename);


// Part_3- USer
int Login_or_register();
void add_user();
int readUser(const char *filename);
int comparingUser(char a[]);
int test_User(char a[], char b[]);
int check_users(const char *filename);
void addingNewUser(const char *filename);

// Access 
void Access_book(char*);
void Access_student(char*);
void Access_admin(char*);

// Time diary work
void gettime(const char s[], char ID[]);

                                  // Function main
int main(){
    int n;
	FILE *fs = fopen("User.csv", "a+");
	//read user
	int k = readUser("User.csv");
	// Confirm You wanna just Login  OR Add new user
	int i = Login_or_register();
    if(i==1){

		n = check_users("User.csv");
	}
	else if(i==2){

		add_user();
		n = check_users("User.csv");
	}
	// Verify account

    if(Users[n].Username == "admin" || (Users[n].ADbook == 1 && Users[n].ADstudent == 1)){

		Access_admin(Users[n].Username);

	}
	else if(Users[n].ADbook == 1 && Users[n].ADstudent == 0){

		Access_book(Users[n].Username);

	}
	else if(Users[n].ADbook == 0 && Users[n].ADstudent == 1){

		Access_student(Users[n].Username);

	}
    fclose(fs);
	return 0;
}
                                             // Get time - diary work with menu books and students
void gettime(const char s[], char *ID){
	FILE *fx;
   // Function time
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
    fprintf(fx,";\"Activities: %s\"",s);

    fclose(fx);
}

char *trim(char *s) // Function remove all string ',' from string s
{
    int i = strlen(s) - 1;
    while (s[i] == ',') i--;
    s[i+1] = 0;
    return s;
}
                                                 // Access menu students
void Access_student(char *ID){

	int n = readStudent("student.csv");
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
        printf("**      0. Finish. Return to function login **\n");
        printf("******************************************\n");
        printf("**          You want:                   **\n");
        
		scanf("%d", &x);
		fflush(stdin);
		switch(x)
		{
			case 1:
			{
				gettime("addingNewStudent", ID);
				addingNewStudent("student.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 2:
			{
				gettime("deletingStudent", ID);
				deletingStudent("student.csv");
				printf("\nEnter any buttons!");
                getch();
				break;				
			}
			case 3:
			{
				gettime("searchingStudent", ID);
				searchingStudent("student.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 4:
			{
				gettime("editingStudent", ID);
				editingStudent("student.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 5:
			{
				gettime("look_all_Students", ID);
				look_all_Students("student.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}

			case 0:
			{
				printf("\nFinished. \n");
                check_users("User.csv");
				return ;
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
}

                                               //Student File
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

                                        //Add New students
void addingNewStudent(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	student newstudent;
	
	printf("ID:");
	gets(newstudent.ID);
	if (comparingID(trim(newstudent.ID)) != -1)
		fclose(fs);
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

                                        //search students
void searchingStudent(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
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
                                       // Function show all student

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
                                                 // END Part Students

												 // ACCESS MENU BOOKS 
void Access_book(char *ID){

	printf("\n\t Access menu book \n");
	int n = readBook("book.csv");
	if (n == -1)
	{
		printf("\n\t ERROR #1: You opened file <<book.csv>>. You need close file!!!, to see and edit file.\n");
	}
	else
	{
	    int x;
		while(true){
		system("cls");
		printf("******************************************\n");
        printf("**    CHUONG TRINH QUAN LY SINH VIEN    **\n");
		printf("**                Menu books            **\n");
        printf("**      1. Add New Book                 **\n");
        printf("**      2. Delete Book                  **\n");
        printf("**      3. Search any Book              **\n");
        printf("**      4. Edit book                    **\n");
        printf("**      5. Show all Books               **\n");
        printf("**      0. Finish. Return to login       **\n");
        printf("******************************************\n");
        printf("**          You want:                   **\n");

		scanf("%d", &x);
		fflush(stdin);
		switch(x)
		{
			case 1:
			{
				gettime("addingNewBook", ID);
				addingNewBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 2:
			{
				gettime("deletingBook", ID);
				deletingBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;				
			}
			case 3:
			{
				gettime("searchingBook", ID);
				searchingBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 4:
			{
				gettime("editingBook", ID);
				editingBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 5:
			{
				gettime("look_all-books", ID);
				look_all("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 0:
			{
				printf("\nFinished\n");
				check_users("User.csv");
                return ;
			}
			default:
			{
			     printf("\nNot any function");
                 printf("\nEnter any buttons!!");
                 getch();
                 break;
			}
		}
	  }
	}
}
                                                    //read books
int readBook(const char *filename)
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
		fscanf(fs, "\n%[^,], %[^,], %[^,], %d, %d", Books[total].ISBN, Books[total].Author, Books[total].Title, &Books[total].All, &Books[total].Free);
		total++;
	}
	return total;
}

int comparingISBN(char a[14]) //compare which new ISBN existed or not
{
	int i;
	int temp = -1;
	for (i = 0; i < readBook("book.csv"); i++)
	{
		if(strcmp(a, trim(Books[i].ISBN)) == 0)
			temp = i;
	}
	return temp;
}

                                         //Add books
void addingNewBook(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	book newbook;
	
	printf("ISBN:");
	fflush(stdin);
	gets(newbook.ISBN);
	if (comparingISBN(trim(newbook.ISBN)) != -1)
	{
		printf("\nISBN existed, enter other ISBN.\n");
		fclose(fs);
	}
	
	else 
	{
		printf("\nAuthor's name:");
		gets(newbook.Author);
		printf("\nBook's title:");
		gets(newbook.Title);
		printf("\nAll:");
		scanf("%d", &newbook.All);
		printf("\nFree:");
		scanf("%d", &newbook.Free);
	
		fprintf(fs, "\n%10s, %10s, %10s, %d, %d", trim(newbook.ISBN), trim(newbook.Author), trim(newbook.Title), newbook.All, newbook.Free);
		fclose(fs);
		printf("\nMore of success!!!\n");
	}
}

                                           //Search books
void searchingBook(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	char searchitem[14];
	int total =0;
	printf("ISBN:");
	fflush(stdin);
	gets(searchitem);
	rewind(fs);
	int n = comparingISBN(trim(searchitem));
	
	if(n == -1)
	{
		printf("\nISBN doesn't exist. Book doesn't exist.");
		fclose(fs);
	}
	else
	{
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");

		while(!feof(fs)){
     
	     fscanf(fs, "\n%[^,], %[^,], %[^,], %d, %d", Books[total].ISBN, Books[total].Author, Books[total].Title, &Books[total].All, &Books[total].Free);
	     if(total == n){
		     printf("%10s, %10s, %10s, %d, %d\n", trim(Books[n].ISBN), trim(Books[n].Author), trim(Books[n].Title), Books[n].All, Books[n].Free);
	     }
	     total++;
	}
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
		fclose(fs);
	}
}

                                         //Delete books by ISBN
void deletingBook(const char *filename)
{
	FILE *fs;
	char deleteitem[__MAX_SIZE];
	printf("ISBN:");
	fflush(stdin);
	gets(deleteitem);
	
	fs = fopen(filename, "r");
	rewind(fs);
	int k = comparingISBN(trim(deleteitem)); 
	int n = readBook(filename);
	fclose(fs);
	if (k != -1)
	{
		fs = fopen(filename, "w");
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != k)
				//printf("%s, %s, %s, %d, %d\n", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);
				fprintf(fs, "\n%10s, %10s, %10s, %d, %d", trim(Books[i].ISBN), trim(Books[i].Author), trim(Books[i].Title), Books[i].All, Books[i].Free);
		}
		fclose(fs);
		printf("\nRemoved from the library.");
	}
	else
		printf("\n ISBN of book doesn't exist\n");
}

                                             //Edit books by ISBN
void editingBook(const char *filename)
{
	FILE *fs;
	book edititem;
	printf("\nISBN:");
	gets(edititem.ISBN);
	
	fs = fopen(filename, "r");
	rewind(fs);
	int k = comparingISBN(trim(edititem.ISBN)); 
	int n = readBook(filename);
	fclose(fs);
	if (k != -1)
	{
		printf("\nAuthor's name:");
		gets(edititem.Author);
		printf("\nBook's title:");
		gets(edititem.Title);
		printf("\nAll:");
		scanf("%d", &edititem.All);
		printf("\nFree:");
		scanf("%d", &edititem.Free);
		fs = fopen(filename, "w");
		int i;
		for (i = 0; i < n; i++)
		{
			if (i != k)

				fprintf(fs, "\n%10s, %10s, %10s, %d, %d", Books[i].ISBN, Books[i].Author, Books[i].Title, Books[i].All, Books[i].Free);

			else{

				fprintf(fs, "\n%10s, %10s, %10s, %d, %d", trim(edititem.ISBN), trim(edititem.Author), trim(edititem.Title), edititem.All, edititem.Free);
			}	
		}
		fclose(fs);
	}
	else
		printf("\n ISBN of book doesn't exist\n ");
}

                                               // SHOW all books

void look_all(const char *filename){
	FILE *fs;
	fs = fopen(filename, "r");
	rewind(fs);
	int k = readBook(filename);
	int i;
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	for(i = 0 ; i < k ; i++){
		
		printf("%10s,\t %10s,\t %10s,\t%d,\t %d\n", trim(Books[i].ISBN), trim(Books[i].Author), trim(Books[i].Title), Books[i].All, Books[i].Free);
	}
		printf("-----------------------------------------------------"
	"----------------------------------------------------------------\n");
	fclose(fs);
}
                                             // END part BOOKS.....

                                             // Access with admin
void Access_admin(char *ID){
    int x;
	system("cls");
	printf("******************************************\n");
	printf("**    You are admin.                    **\n");
	printf("**    You can go in menu books and students. **\n");
	printf("**      1. Menu Books                   **\n");
	printf("**      2. Menu Students                **\n");
	printf("**      0. Return login.                **\n");
	printf("**      You choice:                     **\n");
	scanf("%d", &x);
    fflush(stdin);

	switch(x)
		{
			case 1:
			{
				system("cls");
				Access_book( ID );
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 2:
			{
				system("cls");
				Access_student( ID );
				printf("\nEnter any buttons!");
                getch();
				break;				
			}
			case 0:
			{
				check_users("User.csv");
				return ;
			}
			
			default:{
			     printf("\nNot any function");
                 printf("\nEnter any buttons!!");
                 getch();
                 break;
			}
		}
}
                                                 // *****Function User Login *****
                                                  //***** CHECK LOGIN        *****
int Login_or_register(){
	int x;
	system("cls");
	printf("******************************************\n");
	printf("**    You wanna register or Login.        **\n");
	printf("**    You can go in menu books and students. **\n");
	printf("**      1. Login                     **\n");
	printf("**      2. Register                  **\n");
	printf("**      You choice:                     **\n");
	fflush(stdin);
	scanf("%d", &x);
	if(x == 1 || x == 2)
         return x;

}														  
int check_users(const char *filename){
	bool login = false;
    char a[__MAX_SIZE], b[__MAX_SIZE];
	FILE *f = fopen(filename , "a+");
	rewind(f);
	int k = readUser(filename);
	user sv[100];
	int i = 0, n;
	while(login == false){
		system("cls");
		printf("******************************************\n");
		printf("**    PROGRAM LOGIN                     **\n");
		fflush(stdin);
		printf("**      LOGIN: ");
		gets(a);
		printf("**      PASSWORD: ");
		gets(b);
		
		if(test_User(trim(a), trim(b)) != -1){
				n = test_User(trim(a), trim(b));
				printf("\n Logined successfully!");     /// IF LOGIN SUCCESFULLy
				login = true;
				break;
		}                                             // If login wrong. return, keeping on login again.
		if(login == false){           
		     printf("\nCan't login successfully. Login or password isn't right. Please login again.\n");
		     getch();
	    }

	}
	fclose(f);
	return n;
}
                                               // ADD User
void add_user(){          
    int n = readUser("User.csv");
	if (n == -1)
	{
		printf("\n\t ERROR #1: You opened file <<USer.csv>>. You need close file!!!, to see and edit file.\n");
	}
	else
	{
		int x;
		system("cls");
		printf("******************************************\n");
        printf("**    CHUONG TRINH QUAN LY User         **\n");
		printf("**                Menu                  **\n");
        printf("**      1. Add New User                 **\n");
        printf("**      0. Finish                       **\n");
        printf("******************************************\n");
        printf("**          You want:                   **\n");

		scanf("%d", &x);
		fflush(stdin);
		switch(x)
		{
			case 1:
			{
				addingNewUser("User.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			
			case 0:
			{
				printf("\nFinished\n");
				break;
			}
			default:
			{
			     printf("\nNot any function");
                 printf("\nEnter any buttons!!");
                 getch();
                 break;
			}
		}
	         
	}

}
int comparingUser(char a[]) //compare which User existed or not
{
	int i;
	int temp = -1;
	for (i = 0; i < readUser("User.csv"); i++)
	{
		if(strcmp(a, trim(Users[i].Username)) == 0 )
			temp = i;
	}
	return temp;
}
                                     // check login and password
int test_User(char a[], char b[]) //compare which login and password existed or not
{
	int i;
	int temp = -1;
	for (i = 0; i < readUser("User.csv"); i++)
	{
		if(strcmp(trim(Users[i].Username), a) == 0 && strcmp(trim(Users[i].Password), b) == 0)
			temp = i;
	}
	return temp;
}
                                       // Read file USER
int readUser(const char *filename)
{
	FILE *fs = fopen(filename, "a+");
	if(!fs)
		return -1;
	
	//Read file
	rewind(fs);
	char tmp[__MAX_SIZE];
	int total = 0;
	while (fgets(tmp, __MAX_SIZE, fs))
	{
		fscanf(fs, "\n%[^,], %[^,], %d, %d", Users[total].Username, Users[total].Password, &Users[total].ADbook, &Users[total].ADstudent);
		total++;
	}
	return total;
}
                                              // add new user
void addingNewUser(const char *filename)
{
	FILE * fs = fopen(filename, "a+");
	user newUser;
	
	printf("Username:");
	fflush(stdin);
	gets(newUser.Username);
	if (comparingUser(trim(newUser.Username)) != -1)
	{
		printf("\nUser existed, enter other User.\n");
		fclose(fs);
	}
	
	else 
	{
		printf("\nEnter password:");
		gets(newUser.Password);
		printf("\nUser_book:");
		scanf("%d", &newUser.ADbook);
		printf("\nUser_student:");
		scanf("%d", &newUser.ADstudent);
	
		fprintf(fs, "\n%10s, %10s, %d, %d", trim(newUser.Username), trim(newUser.Password), newUser.ADbook, newUser.ADstudent);
		fclose(fs);
		printf("\nADD user of success!!!\n");
	}
}