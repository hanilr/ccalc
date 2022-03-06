#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define esc_reset "\033[0m"
#define colorfg_white "\033[38;2;233;233;233m"
#define colorfg_red "\033[38;2;200;55;55m"
#define colorfg_green "\033[38;2;55;200;55m"

void print_result(double result) { printf("%s[Result] %s%lf%s", colorfg_green, colorfg_white, result, esc_reset); }

void print_error(char *error_reason) { printf("%s[ERROR] %s%s%s", colorfg_red, colorfg_white, error_reason, esc_reset); }

struct symbols_positions_lengths
{
    int symbol;
    int symbol_pos;
    int symbol_len;
    int result_buffer;
};

int main(int argc, char *argv[])
{
    double result = 0;
    int operator_count = 0;
    struct symbols_positions_lengths spl[16];

    for(int i = 1; argc > i; i+=1)
    {
        if(strcmp(argv[i], "+") == 0 || strcmp(argv[i], "-") == 0 || strcmp(argv[i], "x") == 0 || strcmp(argv[i], "/") == 0)
        {
            if(strcmp(argv[i], "+") == 0) { spl[operator_count].symbol = '+'; }
            else if(strcmp(argv[i], "-") == 0) { spl[operator_count].symbol = '-'; }
            else if(strcmp(argv[i], "x") == 0) { spl[operator_count].symbol = 'x'; }
            else if(strcmp(argv[i], "/") == 0) { spl[operator_count].symbol = '/'; }
            spl[operator_count].symbol_pos = i;
            operator_count += 1;
        }
    }
    if(operator_count == 1) { spl[0].symbol_len = argc-2; }
    else
    { 
        for(int i = 0; operator_count-1 > i; i+=1) { spl[i].symbol_len = spl[i+1].symbol_pos - spl[i].symbol_pos - 1; }
        spl[operator_count-1].symbol_len = (argc-1) - spl[operator_count-1].symbol_pos;
    }

    for(int i = 0; operator_count > i; i+=1)
    {
        if(spl[i].symbol == '+')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1) { spl[i].result_buffer += atoi(argv[spl[i].symbol_pos+x+1]); }
        }
        else if(spl[i].symbol == '-')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1) { spl[i].result_buffer -= atoi(argv[spl[i].symbol_pos+x+1]); }
        }
        else if(spl[i].symbol == 'x')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1) { spl[i].result_buffer *= atoi(argv[spl[i].symbol_pos+x+1]); }
        }
        else if(spl[i].symbol == '/')
        {
            spl[i].result_buffer = atoi(argv[spl[i].symbol_pos+1]);
            for(int x = 1; spl[i].symbol_len > x; x+=1) { spl[i].result_buffer /= atoi(argv[spl[i].symbol_pos+x+1]); }
        }
    }
    result = spl[0].result_buffer;
    for(int i = 1; operator_count > i; i+=1)
    {
        if(spl[i].symbol == '+') { result += spl[i].result_buffer; }
        else if(spl[i].symbol == '-')
        {
            if(spl[i].result_buffer < 0) { result += spl[i].result_buffer; }
            else { result -= spl[i].result_buffer; }
        }
        else if(spl[i].symbol == 'x') { result *= spl[i].result_buffer; }
        else if(spl[i].symbol == '/') { result /= spl[i].result_buffer; }
    }

    print_result(result);
    return 0;
}