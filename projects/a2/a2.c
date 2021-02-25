#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// make array with each entry in acsending order
int main()
{
    char string[100], *rows, *cols;
    char c_array[50][20]; //character array with 50 entries of 20 characters each
    int count=0;
    int sel1=0,sel2=0,sel3=0,sel4=0;
    int prod1=0,prod2=0,prod3=0,prod4=0,prod5=0;

    FILE *fp;
    fp = fopen("sales.csv", "r");

    while(fgets(string, 100, fp) != NULL)
    {
        // split csv lines
        rows = strtok(string, "\n");
        // split csv cells
        cols = strtok(rows, ",");

        while(cols != NULL)
        {   
            // store entries into character array
            strcpy(c_array[count++], cols);
            cols = strtok(NULL, ",");
        }
    }

    //calculate the totals for each person
    for(int i=5; i <= 29; i++)
    {
        if(i % 5 == 1){sel1 = sel1 + atoi(c_array[i]);}
        if(i % 5 == 2){sel2 = sel2 + atoi(c_array[i]);}
        if(i % 5 == 3){sel3 = sel3 + atoi(c_array[i]);}
        if(i % 5 == 4){sel4 = sel4 + atoi(c_array[i]);}
    }

    //calculate the totals for each product
    for(int i=5; i <= 29; i++)
    {
        if(i < 10){prod1 = prod1 + atoi(c_array[i]);}
        if((i > 10) && (i < 15)){prod2 = prod2 + atoi(c_array[i]);}
        if((i > 15) && (i < 20)){prod3 = prod3 + atoi(c_array[i]);}
        if((i > 20) && (i < 25)){prod4 = prod4 + atoi(c_array[i]);}
        if((i > 25) && (i < 30)){prod5 = prod5 + atoi(c_array[i]);}
    }

    // Print Table
    printf("%s %s %s %s %s %s\n", c_array[0],c_array[1],c_array[2],c_array[3],c_array[4], "Total");
    printf("%s    %s     %s     %s     %s     %d\n", c_array[5],c_array[6],c_array[7],c_array[8],c_array[9], prod1);
    printf("%s    %s     %s     %s     %s     %d\n", c_array[10],c_array[11],c_array[12],c_array[13],c_array[14], prod2);
    printf("%s    %s      %s     %s     %s     %d\n", c_array[15],c_array[16],c_array[17],c_array[18],c_array[19], prod3);
    printf("%s    %s     %s     %s      %s     %d\n", c_array[20],c_array[21],c_array[22],c_array[23],c_array[24], prod4);
    printf("%s    %s     %s     %s     %s     %d\n", c_array[25],c_array[26],c_array[27],c_array[28],c_array[29], prod5);
    printf("%s       %d    %d    %d    %d    %s\n", "Total", sel1, sel2, sel3, sel4, "0");
}