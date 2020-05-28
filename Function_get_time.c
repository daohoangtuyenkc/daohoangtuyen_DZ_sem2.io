#include <stdio.h>
#include <time.h>
#include <conio.h>
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
