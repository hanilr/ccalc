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
    int result_buffer; // OPERATION RESULT BUFFER
}; // VARIABLE NAME CASE IS 'snake_case'

// IF THE MAIN FUNCTION WAS ON THE TOP OF THE CODE, THE NAME OF THE OTHER FUNCTIONS SHOULD HAVE DEFINED 
// EXAMPLE: void print_error(char *error_reason);
// BECAUSE PARSER START FROM TOP OF THE CODE, YOU NEED TO LINK TO FUNCTION
int main(int argc, char *argv[])
{ // ARGC IS TYPED ARGUMENT NUMBER (STARTING FROM 1), ARGV IS ARGUMENTS (STARTING FROM 0)
    double result = 0; // WHY VARIABLE DATA TYPE IS DOUBLE? IF USER WANT TO DIVIDE
    int operator_count = 0; // HOW MANY OPERATOR WANTED TO USE?
    struct symbols_positions_lengths spl[16]; // STRUCT DEFINED AS 'spl' 17 TIMES

    // OPERATOR COUNT AND VALUE ASSIGN SECTION
    for(int i = 1; argc > i; i+=1)  // WILL LOOP ARGC-1 TIMES (IN TERMINAL NAME OF THE PROGRAM COUNT TOO, SO -1 FOR ARGC)
    {
        if(strcmp(argv[i], "+") == 0 || strcmp(argv[i], "-") == 0 || strcmp(argv[i], "x") == 0 || strcmp(argv[i], "/") == 0)
        { // IF THERE IS A SYMBOL OF OPERATION THEN ASSIGN THE VALUE TO STRUCT ARRAY
            if(strcmp(argv[i], "+") == 0) { spl[operator_count].symbol = '+'; }
            else if(strcmp(argv[i], "-") == 0) { spl[operator_count].symbol = '-'; }
            else if(strcmp(argv[i], "x") == 0) { spl[operator_count].symbol = 'x'; }
            else if(strcmp(argv[i], "/") == 0) { spl[operator_count].symbol = '/'; }
            spl[operator_count].symbol_pos = i; // SYBMOL POSITION ASSIGN
            operator_count += 1; // INCREASE OPERATOR COUNT WHEN FOUND A SYMBOL
        }
    }
    if(operator_count == 1) { spl[0].symbol_len = argc-2; } // IF THERE IS ONLY ONE SYMBOL THEN ASSING 'symbol_len' TO 'argc' BUT MINUS 2
    else // IF THERE IS MULTIPLE SYMBOL
    { 
        for(int i = 0; operator_count-1 > i; i+=1) // LOOP OPERATOR COUNT MINUS 1 (BECAUSE LAST OPERATOR NEED DIFFERENT MATH)
        {
            spl[i].symbol_len = spl[i+1].symbol_pos - spl[i].symbol_pos - 1; // FIRST SYMBOL POSITION - SECOND SYMBOL POSITION - 1 = FIRST SYMBOL LENGTH
        }
        spl[operator_count-1].symbol_len = (argc-1) - spl[operator_count-1].symbol_pos; // TOTAL ARGUMENT - 1 - LAST SYMBOL POSITION = LAST SYMBOL LENGTH
    }

    // OPERATION SECTION (MATH SECTION)
    for(int i = 0; operator_count > i; i+=1) // WILL LOOP 'operator_count' TIMES
    {
        if(spl[i].symbol == '+') // DETECT SYMBOL
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]); // ASSIGN THE FIRST VALUE TO BUFFER
            for(int x = 1; spl[i].symbol_len > x; x+=1)
            {
                spl[i].result_buffer += atoi(argv[spl[i].symbol_pos+x+1]); // AFTER THE FIRST VALUE WILL ASSIGN AND OPERATE TO RESULT BUFFER
            }
        }
        else if(spl[i].symbol == '-')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1)
            {
                spl[i].result_buffer -= atoi(argv[spl[i].symbol_pos+x+1]);
            }
        }
        else if(spl[i].symbol == 'x')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1)
            {
                spl[i].result_buffer *= atoi(argv[spl[i].symbol_pos+x+1]);
            }
        }
        else if(spl[i].symbol == '/')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1)
            {
                spl[i].result_buffer /= atoi(argv[spl[i].symbol_pos+x+1]);
            }
        }
    }
    result = spl[0].result_buffer; // FIRST ASSIGNED SYMBOL BUFFER
    for(int i = 1; operator_count > i; i+=1) // IN THIS SECTION RESULT BUFFERS WILL OPERATE AS THEY SYMBOLES. THEN WILL ASSIGN TO RESULT.
    {
        if(spl[i].symbol == '+') { result += spl[i].result_buffer; }
        else if(spl[i].symbol == '-')
        {
            if(spl[i].result_buffer < 0)
            {
                result += spl[i].result_buffer;
            }
            else
            {
                result -= spl[i].result_buffer;
            }
        }
        else if(spl[i].symbol == 'x') { result *= spl[i].result_buffer; }
        else if(spl[i].symbol == '/') { result /= spl[i].result_buffer; }
    }

    print_result(result); // RESULT PRINTED
    return 0; // WITH THAT, OPERATING SYSTEMS WILL KNOW PROGRAM EXECUTED WITH SUCCESSFULL
} // MADE BY @hanilr
