#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024 * 10
int get_sum(FILE *handler) {
  int sum = 0;
  int chars_read = 0;
  int current, previous, first;
  int buf[MAX_SIZE];
  while ((current = getc(handler)) != EOF) {
    if (chars_read + 1 > MAX_SIZE) {
      printf("file is too large\n");
      return 0;
    }
    buf[chars_read] = current - '0';
    chars_read++;
  }

  if (chars_read % 2 != 0) {
    printf("invalid input, needs to be even number of digits\n");
  }

  int i;
  int half_of_chars_read = chars_read / 2;
  for (i = 0; i < chars_read; ++i) {
    int index_to_check = (i + half_of_chars_read) % chars_read;
    if (buf[i] == buf[index_to_check]) {
      sum += buf[index_to_check];
    }
  }

  return sum;
}

int main(int argc, char **argv) {
  if (!argv[1]) {
    printf("give input file");
    return 1;
  }
  FILE *handler = fopen(argv[1], "r");
  if (handler) {
    int sum = get_sum(handler);
    fclose(handler);
    printf("%d\n", sum);
    return 0;
  } else {
    printf("failed reading file");
    return 1;
  }
}