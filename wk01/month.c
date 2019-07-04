#include <stdio.h>
#include <stdlib.h>

char *printMonth(int month);
int main(int argc, char *argv[]){
    printf ("Enter a number between 1 to 12: \n");
    int month;
    scanf("%d", &month);
    printf ("The month name of %d is %s\n", month, printMonth(month));


    return EXIT_SUCCESS;
}

char *printMonth(int month) {
	char *monthName;
	switch(month){
		case 1: monthName = "January"; break;
		case 2: monthName = "Feb"; break;
		case 3: monthName = "March"; break;
		case 4: monthName = "April"; break;
		case 5: monthName = "May"; break;
		case 6: monthName = "June"; break;
		case 7: monthName = "July"; break;
		case 8: monthName = "August"; break;
		case 9: monthName = "September"; break;
		case 10: monthName = "October"; break;
		case 11: monthName = "November"; break;
		case 12: monthName = "December"; break;
		default: monthName = "?????";
	}
	return monthName;
}
