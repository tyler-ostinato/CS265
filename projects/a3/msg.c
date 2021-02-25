#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


bool foo(char *string, int count)
{
    enum STATE {STEP1, STEP2, STEP3, STEP4};
    enum STATE state=STEP1;
    while(string[count] != ' ')
    {
        switch (state)
        {
        case STEP1: // Check first character is an 'E'
            if(string[count] == 'E'){
                state=STEP2;
                break;
            }
            else{return false;}
            break;
        case STEP2: // Check for 0,1,2 then followed by F and return status 
            {
                switch (string[count])
                {
                case '0':
                    state=STEP3;
                    break;
                case '1':
                    state=STEP3;
                    break;
                case '2':
                    state=STEP3;
                    break;    
                default:
                    return false;                               
                }
            }
            break;
        case STEP3: // Check for 0,1,2 then followed by F and return status 
            {
                switch (string[count])
                {
                case '0':
                    state=STEP3;
                    break;
                case '1':
                    state=STEP3;
                    break;
                case '2':
                    state=STEP3;
                    break;    
                case 'F':
                    state=STEP4;
                    break;
                default:
                    return false;                               
                }
            }
            break;
        case STEP4:
            {
                switch (string[count])
                {
                case '\0':
                    return true;
                    break;
                default:
                    return false;                               
                }
            }
            break;
        }   
        count++;
    }
}


bool eep(char *string, int count)
{
    enum STATE {STEP1, STEP2, STEP3};
    enum STATE state=STEP1;
    while(string[count] != ' ')
    {
        switch (state)
        {
        case STEP1: // Check first character is a 'P'
            if(string[count] == 'P'){
                state=STEP2;
                count++;
                break;
            }
            else
            {
                return false;
            }
            break;
        case STEP2: // Check for a B then go to C or return result
            {   
                switch (string[count])
                {
                case 'B':
                    state=STEP3;
                    count++;
                    break;
                case '\0':
                    return true;
                    break;
                default:
                    return false;                               
                }
            }
            break;
        case STEP3: // Check for a C then go back to B or return result
            {
                switch (string[count])
                {
                case 'C':
                    state=STEP2;
                    count++;
                    break;   
                case '\0':
                    return true;
                    break;
                default:
                    return false;                               
                }
            }
            break;
        count++;
        }   
    }
}


bool op(char *string, int count)
{
    enum STATE {STEP1, STEP2};
    enum STATE state=STEP1;
    int num_sevens=0;
    while(string[count] != ' ')
    {
        switch (state)
        {
        case STEP1:
            if(string[0] == 'Q'){ // Check first character is a 'Q'
                state=STEP2;
                count++;
                break;
            }
            else
            {
                return false;
            }
            break;
        case STEP2:
            {   
                switch (string[count]) // Check for 6s and odd number of 7s
                {
                case '6':
                    state=STEP2;
                    count++;
                    break;
                case '7':
                    state=STEP2;
                    count++;
                    num_sevens++;
                    break;
                case '\0':
                    if( (num_sevens % 2) == 0)
                    {
                        return false;
                        break;
                    }
                    else{return true;}
                default:
                    return false;                               
                }
            }
            break;
        count++;
        }   
    }
}


bool ork(char *string)
{
    enum STATE {STEP1, STEP2};
    enum STATE state=STEP1;
    int num_integers=0,count=0;
    bool result=false;
    while(string[count] != ' ')
    {
        switch (state)
        {
        // Check first character is a 'M'
        case STEP1:
            if(string[0] == 'M'){
                state=STEP2;
                count++;
                break;
            }
            else{return false;}
            break;
        case STEP2:
            {
                switch (string[count])
                {
                case 'E':           // If there is a foo
                    result = foo(string, 1);
                    // printf("%d", result);
                    return result;
                    break;
                case 'P':           // If there is an eep
                    result = eep(string, 1);
                    return result;
                    break;             
                default:            // Otherwise fail
                    return false;
                    break;
                }
            }
            break;
        }   
    }
}


int main(int argc, char *argv[])
{
    char string[100], *rows;
    char c_array[50][20]; // Capture input into character array
    int count=0;
    bool result;

    FILE *fp;

    if (argc == 2) // If there is a file input read it
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            printf("Cannot open '%s'. Please try again or make sure the file exists.\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        while(fgets(string, 100, fp) != NULL)
        {
            // split on newlines
            rows = strtok(string, "\n");
            // store into character array
            strcpy(c_array[count++], rows);
            rows = strtok(NULL, "\n");
        }   
    }
    else // read from stdin -- STOP READING INPUTS BY USING CRTL D
    {
        printf("\n");
        printf("Please a list of strings to test. (exit using CTRL D)\n");
        while(fgets(string, 100, stdin) != NULL)
        {
            // split on newlines
            rows = strtok(string, "\n");
            // store into character array
            strcpy(c_array[count++], rows);
            rows = strtok(NULL, "\n");
        }
    }

    // Loop through each string and put into corresponding function
    printf("\nResults--\n");
    for(int i=0; i<count; i++)
    {
        switch (c_array[i][0])
        {
            case 'E': // FOO
                result = foo(c_array[i], 0);              
                break;
            case 'P': // EEP
                result = eep(c_array[i], 0);
                break;
            case 'Q': // OP
                result = op(c_array[i], 0);
                break;
            case 'M': // ORK
                result = ork(c_array[i]);
                break;
            default:
                result = false;
                break;
        }
        // Check if string and detemine 'OK' or 'FAIL' and print
        if(result == true)
        {
            printf("%s OK\n", c_array[i]);
        }
        else
        {
            printf("%s FAIL\n", c_array[i]);
        }
    }
    printf("\n");
    return 0;
}
