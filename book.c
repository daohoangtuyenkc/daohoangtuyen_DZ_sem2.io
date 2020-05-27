#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

book Books[__MAX_SIZE];


//Part: Book
int readBook(const char *filename);  
int comparingISBN(char a[14]);   // Check ISBN of book existed or not
void look_all(const char *filename); // VIew ALL BOOKS
void addingNewBook(const char *filename); // Add new books
void searchingBook(const char *filename); // Searching information book by ISBN
void deletingBook(const char *filename); // DELETE books
void editingBook(const char *filename); // EDIT information of book
char *trim(char *s); // Function remove all string ',' in string s when read data in files



int main(int argc, char **argv)
{
	int n = readBook("book.csv");
	bool daNhap = false;
	if (n == -1)
	{
		printf("\nERROR #1: empty file. You opened file <<book.csv>>. You need close file to run program.\n");
	}
	else
	{
		int x;
		while(true){
		system("cls");
		printf("******************************************\n");
        printf("**    CHUONG TRINH QUAN LY SINH VIEN    **\n");
		printf("**                Menu                  **\n");
        printf("**      1. Add New Book              **\n");
        printf("**      2. Delete Book               **\n");
        printf("**      3. Search any Book           **\n");
        printf("**      4. Edit book                 **\n");
        printf("**      5. Show all Books            **\n");
        printf("**      0. Finish                       **\n");
        printf("******************************************\n");
        printf("**          You want:                   **\n");

		scanf("%d", &x);
		fflush(stdin);
		switch(x)
		{
			case 1:
			{
				addingNewBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 2:
			{
				deletingBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;				
			}
			case 3:
			{
				searchingBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 4:
			{
				editingBook("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 5:
			{
				look_all("book.csv");
				printf("\nEnter any buttons!");
                getch();
				break;
			}
			case 0:
			{
                getch();
				return 0;
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
	return 0;
}

 // Function remove all string ',' in string s when read data in files
char *trim(char *s)
{
    int i = strlen(s) - 1;
    while (s[i] == ',') i--;
    s[i+1] = 0;
    return s;
}
 // Read file "book.csv"
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

//Add new book
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

//Search information book by ISBN
void searchingBook(const char *filename)
{
	FILE * fs = fopen(filename, "r");
	char searchitem[14];
	int total =0;
	rewind(fs);
	printf("ISBN:");
	fflush(stdin);
	gets(searchitem);
	int n = comparingISBN(trim(searchitem));
	
	if(n == -1)
	{
		printf("\nISBN doesn't exist. Book doesn't exist.");
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
	}
	fclose(fs);
}

//Delete Book
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
				
				fprintf(fs, "\n%10s, %10s, %10s, %d, %d", trim(Books[i].ISBN), trim(Books[i].Author), trim(Books[i].Title), Books[i].All, Books[i].Free);
		}
		fclose(fs);
		printf("\nRemoved from the library.");
	}
	else
		printf("\n ISBN of book doesn't exist\n");
}

//Edit information Books
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
// View ALL BOOKS
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



