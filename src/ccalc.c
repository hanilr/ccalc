// CALCULATOR IN C FOR NEWBIES//

// STANDARD LIBRARY
#include <stdio.h> // 'printf();' OUTPUT FUNCTION (TO TERMINAL)
#include <stdlib.h> // 'atoi();' STRING TO INTEGER
#include <string.h> // 'strcmp();' STRING COMPARE FUNCTION

// ASCII ESCAPE SEQUENCE COLOR CODES
#define esc_reset "\033[0m" // MUST USE AFTER EVERY COLOR CODE USE
#define colorfg_white "\033[38;2;233;233;233m" // #e9e9e9
#define colorfg_red "\033[38;2;200;55;55m" // #c83737
#define colorfg_green "\033[38;2;55;200;55m" // #37c837
// RGB CODES USED BUT EXPLAINED AS HEX CODES

void print_result(double result) // ONLY USED FOR RESULT
{
    printf("%s[Result] %s%lf%s", colorfg_green, colorfg_white, result, esc_reset);
} // GREEN AND WHITE COLORS USED

void print_error(char *error_reason) // ONLY USED FOR ERRORS
{
    printf("%s[ERROR] %s%s%s", colorfg_red, colorfg_white, error_reason, esc_reset);
} // RED AND WHITE COLORS USED

struct symbols_positions_lengths // IF USER TYPED MULTIPLE OPERATION OR MORE THAN TWO ARGUMENT IN OPERATION
{
    int symbol; // OPERATION SYMBOL
    int symbol_pos; // OPERATION SYMBOL POSITION
    int symbol_len; // OPERATION SYMBOL RESPONSIBILITY LENGTH
}; // VARIABLE NAME CASE IS 'snake_case'

// IF THE MAIN FUNCTION WAS ON THE TOP OF THE CODE, THE NAME OF THE OTHER FUNCTIONS SHOULD HAVE DEFINED 
// EXAMPLE: void print_error(char *error_reason);
// BECAUSE PARSER START FROM TOP OF THE CODE, YOU NEED TO LINK TO FUNCTION
int main(int argc, char *argv[])
{ // ARGC IS TYPED ARGUMENT NUMBER (STARTING FROM 1), ARGV IS ARGUMENTS (STARTING FROM 0)
    double result = 0; // WHY VARIABLE DATA TYPE IS DOUBLE? IF USER WANT TO DIVIDE
    int operator_count = 0; // HOW MANY OPERATOR WANTED TO USE?
    struct symbols_positions_lengths spl[16]; // STRUCT DEFINED AS 'spl' 17 TIMES

    for(int i = 1; argc > i; i+=1) // WILL LOOP ARGC-1 TIMES (IN TERMINAL NAME OF THE PROGRAM COUNT TOO, SO -1 FOR ARGC)
    {
        if(strcmp(argv[i], "+") == 0) // IF "+" EXIST IN 'argv[i]' WILL RETURN 0 (TRUE = 0, FALSE = 1)
        {
            int count = 1; // THIS VARIABLE WILL COUNT HOW MANY NUMBER IN OPERATION
            while(1) // INFINITE LOOP. IF THERE WAS NO 'break;' IN THE FUNCTION IT WOULD GO ON SO FAR. BUT IT WILL END WITH STACK OVERFLOW
            {
                // IF THERE IS A SYMBOL AFTER OPERATION NUMBERS OR IF ARGUMENTS OVER THAN BREAK THE LOOP
                if(strcmp(argv[i+count], "+") == 0) { break; }
                else if(strcmp(argv[i+count], "-") == 0) { break; }
                else if(strcmp(argv[i+count], "x") == 0) { break; }
                else if(strcmp(argv[i+count], "/") == 0) { break; }
                else { count+=1; } // IF THERE IS NO SYMBOL THAN CONTINUE TO NEXT ARGUMENT
                if(i + count == argc) { break; } // IF ARGUMENTS OVER THAN BREAK THE LOOP
            }
            spl[i-1].symbol = '+'; // ADDITION SYMBOL
            spl[i-1].symbol_pos = i; // SYMBOL POSITION
            spl[i-1].symbol_len = count-1; // OPERATION NUMBER COUNT
            operator_count+=1; // INCREASE THE COUNT AFTER FINISH LOOP
        }
        else if(strcmp(argv[i], "-") == 0)
        {
            int count = 1;
            while(1)
            {
                if(strcmp(argv[i+count], "+") == 0) { break; }
                else if(strcmp(argv[i+count], "-") == 0) { break; }
                else if(strcmp(argv[i+count], "x") == 0) { break; }
                else if(strcmp(argv[i+count], "/") == 0) { break; }
                else { count+=1; }
                if(i + count == argc) { break; }
            }
            spl[i-1].symbol = '-';
            spl[i-1].symbol_pos = i;
            spl[i-1].symbol_len = count-1;
            operator_count+=1;
        }
        else if(strcmp(argv[i], "x") == 0)
        {
            int count = 1;
            while(1)
            {
                if(strcmp(argv[i+count], "+") == 0) { break; }
                else if(strcmp(argv[i+count], "-") == 0) { break; }
                else if(strcmp(argv[i+count], "x") == 0) { break; }
                else if(strcmp(argv[i+count], "/") == 0) { break; }
                else { count+=1; }
                if(i + count == argc) { break; }
            }
            spl[i-1].symbol = 'x';
            spl[i-1].symbol_pos = i;
            spl[i-1].symbol_len = count-1;
            operator_count+=1;
        }
        else if(strcmp(argv[i], "/") == 0)
        {
            int count = 1;
            while(1)
            {
                if(strcmp(argv[i+count], "+") == 0) { break; }
                else if(strcmp(argv[i+count], "-") == 0) { break; }
                else if(strcmp(argv[i+count], "x") == 0) { break; }
                else if(strcmp(argv[i+count], "/") == 0) { break; }
                else { count+=1; }
                if(i + count == argc) { break; }
            }
            spl[i-1].symbol = '/';
            spl[i-1].symbol_pos = i;
            spl[i-1].symbol_len = count-1;
            operator_count+=1;
        }
        if((spl[i-1].symbol_pos+1) + spl[i-1].symbol_len == argc) { break; } // IF ARGUMENTS OVER
    } // OPERATOR COUNT HAS BEEN TAKEN AS 'operator_count' VARIABLE

    // OPERATION SECTION (MATH SECTION)
    for(int i = 0; operator_count > i; i+=1) // WILL LOOP 'operator_count' TIMES
    {
        if(spl[i].symbol == '+') // SYMBOL DETECTING
        {
            for(int x = 0; spl[i].symbol_len > x; x+=1) // LOOPING 'symbol_len' TIMES
            {
                result += atoi(argv[spl[i].symbol_pos+x+1]);
            }
        }
        else if(spl[i].symbol == '-')
        {
            if(i == 0) // IF OPERATION AT THE FIRST PLACE OF CALCULATING
            {
                result = atoi(argv[spl[i].symbol_pos+1]);
                for(int x = 1; spl[i].symbol_len > x; x+=1)
                {
                    result -= atoi(argv[spl[i].symbol_pos+x+1]);
                }
            }
            else // IF OPERATION NOT AT THE FIRST PLACE
            {
                for(int x = 1; spl[i].symbol_len > x; x+=1)
                {
                    result -= atoi(argv[spl[i].symbol_pos+x+1]);
                }
            }
        }
        else if(spl[i].symbol == 'x')
        {
            if(i == 0)
            {
                result = atoi(argv[spl[i].symbol_pos+1]);
                for(int x = 1; spl[i].symbol_len > x; x+=1)
                {
                    result *= atoi(argv[spl[i].symbol_pos+x+1]);
                }
            }
            else
            {
                for(int x = 1; spl[i].symbol_len > x; x+=1)
                {
                    result *= atoi(argv[spl[i].symbol_pos+x+1]);
                }
            }
        }
        else if(spl[i].symbol == '/')
        {
            if(i == 0)
            {
                result = atoi(argv[spl[i].symbol_pos+1]);
                for(int x = 1; spl[i].symbol_len > x; x+=1)
                {
                    result /= atoi(argv[spl[i].symbol_pos+x+1]);
                }
            }
            else
            {
                for(int x = 1; spl[i].symbol_len > x; x+=1)
                {
                    result /= atoi(argv[spl[i].symbol_pos+x+1]);
                }
            }
        }
    }

    for(int i = 0; operator_count > i; i+=1)
    {
        printf("%c, %d, %d.\n", spl[i].symbol, spl[i].symbol_pos, spl[i].symbol_len);
    }

    print_result(result); // RESULT PRINTED
    return 0; // WITH THAT, OPERATING SYSTEMS WILL KNOW PROGRAM EXECUTED WITH SUCCESSFULL
} // MADE BY @hanilr