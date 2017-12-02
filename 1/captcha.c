#include <stdio.h>
#include <stdlib.h>

int get_sum(FILE *handler)
{
    int sum = 0;
    int chars_read = 0;
    int current, previous, first;
    while ((current = getc(handler)) != EOF)
    {
        chars_read++;
        current = current - '0';
        if (chars_read > 2 && current == previous)
        {
            sum += current;
        }
        if (chars_read == 1)
        {
            first = current;
        }
        previous = current;
    }

    if (first == previous)
    {
        sum += first;
    }

    return sum;
}

int main(int argc, char **argv)
{
    if (!argv[1])
    {
        printf("give input file");
        return 1;
    }
    FILE *handler = fopen(argv[1], "r");
    if (handler)
    {
        int sum = get_sum(handler);
        fclose(handler);
        printf("%d\n", sum);
        return 0;
    }
    else
    {
        printf("failed reading file");
        return 1;
    }
}