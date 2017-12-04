#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 * 24
#define ARRAY_START_SIZE 10

typedef struct {
  char **array;
  size_t used;
  size_t size;
} DynamicStringList;

void list_push(DynamicStringList *list, char *item) {
  if (list->used == list->size) {
    list->size *= 2;
    list->array = realloc(list->array, list->size * sizeof(char *));
  }
  list->array[list->used++] = item;
}

int count_valid(FILE *handle) {
  int valid_count = 0;
  char str[MAX_LINE_LENGTH];
  while (fgets(str, MAX_LINE_LENGTH, handle)) {
    int length = strlen(str);
    if (str[length - 1] == '\n') {
      str[length - 1] = '\0';
    }

    DynamicStringList *list;
    list = malloc(sizeof(DynamicStringList));
    list->size = ARRAY_START_SIZE;
    list->used = 0;
    list->array = malloc(ARRAY_START_SIZE * sizeof(char *));
    char *buffer = "";
    int i, j;
    for (i = 0; i < length; ++i) {
      char current = str[i];
      if (isspace(current)) {
        buffer[j] = '\0';
        char *item;
        strcpy(item, buffer);
        list_push(list, item);
        printf("%s", item);
        j = 0;
        buffer = "";
      } else {
        buffer[j] = current;
        ++j;
      }
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  if (!argv[1]) {
    printf("give input file\n");
    return 1;
  }
  FILE *handler = fopen(argv[1], "r");
  if (handler) {
    int valid = count_valid(handler);
    fclose(handler);
    printf("%d\n", valid);
    return 0;
  } else {
    printf("failed reading file\n");
    return 1;
  }
}
