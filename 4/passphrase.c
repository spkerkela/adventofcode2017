#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 * 24
#define ARRAY_START_SIZE 60
#define MAX_STR_LEN 60

typedef struct {
  char **array;
  size_t used;
  size_t size;
} DynamicStringList;

void list_push(DynamicStringList *list, char *item) {
  if (list->used == list->size) {
    list->size *= 2;
    list->array =
        realloc(list->array, list->size * sizeof(char *) * MAX_STR_LEN);
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
    list->array = malloc(ARRAY_START_SIZE * sizeof(char *) * MAX_STR_LEN);
    char *buffer = "";
    int i, j;
    printf("===== LINE: %s\n", str);
    for (i = 0; i < length; ++i) {
      char current = str[i];
      if (isspace(current)) {
        buffer[j] = '\0';
        char item[MAX_STR_LEN];
        strcpy(item, buffer);
        list_push(list, item);
        printf("pushed: %s\n", item);
        j = 0;
        buffer = "";
        int k;
        for (k = 0; k < list->used; k++) {
          printf("%s ", list->array[k]);
        }
        printf("\n");
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
