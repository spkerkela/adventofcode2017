#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1024

long long parse_num(long int *smallest, long int *biggest, char *number_buffer,
                    int j) {
  number_buffer[j] = '\0';
  long int number = atol(number_buffer);
  if (number < *smallest) {
    *smallest = number;
  }
  if (number > *biggest) {
    *biggest = number;
  }
  number_buffer = "";
  return number;
}

int get_checksum(FILE *handle) {
  int checksum = 0;
  char str[MAX_LINE_LENGTH];
  while (fgets(str, MAX_LINE_LENGTH, handle)) {
    int length = strlen(str);
    if (str[length - 1] == '\n') {
      str[length - 1] = '\0';
    }
    char *number_buffer = "";
    long int biggest, smallest;
    smallest = LONG_MAX;
    biggest = 0;
    int i, j;
    j = 0;
    for (i = 0; i < length; ++i) {
      char current = str[i];
      if (isdigit(current)) {
        number_buffer[j] = current;
        j++;
        if (i == length - 1) {
          parse_num(&smallest, &biggest, number_buffer, j);
        }
      } else {
        parse_num(&smallest, &biggest, number_buffer, j);
        j = 0;
      }
    }
    checksum += biggest - smallest;
  }

  return checksum;
}

int main(int argc, char **argv) {
  if (!argv[1]) {
    printf("give input file");
    return 1;
  }
  FILE *handler = fopen(argv[1], "r");
  if (handler) {
    int sum = get_checksum(handler);
    fclose(handler);
    printf("%d\n", sum);
    return 0;
  } else {
    printf("failed reading file");
    return 1;
  }
}