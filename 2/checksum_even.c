#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ROW_NUMBERS 1024 * 4

long int parse_num(char *number_buffer, int j) {
  number_buffer[j] = '\0';
  long int number = atol(number_buffer);
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
    long int row_numbers[MAX_ROW_NUMBERS];

    int i, j, number_count;
    j = 0;
    number_count = 0;
    for (i = 0; i < length; ++i) {
      char current = str[i];
      if (isdigit(current)) {
        number_buffer[j] = current;
        j++;
        if (i == length - 1) {
          long int parsed = parse_num(number_buffer, j);
          row_numbers[number_count] = parsed;
          number_count++;
        }
      } else {
        long int parsed = parse_num(number_buffer, j);
        row_numbers[number_count] = parsed;
        number_count++;
        j = 0;
      }
    }

    for (i = 0; i < number_count - 1; ++i) {
      int j;
      for (j = i + 1; j < number_count; ++j) {
        int num1, num2;
        num1 = row_numbers[i];
        num2 = row_numbers[j];
        if (num1 % num2 == 0) {
          checksum += num1 / num2;
        } else if (num2 % num1 == 0) {

          checksum += num2 / num1;
        }
      }
    }
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