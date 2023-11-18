#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "value.h"


struct redis_value_t *redis_value_new(REDIS_VALUE_KIND kind, void *data) {
  struct redis_value_t *value;

  if(kind == REDIS_STRING_KIND) {
    value = malloc(sizeof(struct redis_value_t));
    value->kind = REDIS_STRING_KIND;
    value->data.string = (struct redis_string_t *)data;
    return value;
  }

  return NULL;
}

void redis_value_print(struct redis_value_t *data);

struct redis_string_t *redis_string_new(char *str) {
  int length;
  char *data;
  struct redis_string_t *output;

  length = strlen(str);
  data = malloc(length);
  memcpy(data, str, length);
  output = malloc(sizeof(struct redis_string_t));

  output->length = length;
  output->data = data;

  return output;
}

void redis_string_print(struct redis_string_t *str) {
  printf("\"%.*s\"", str->length, str->data);
}

void redis_string_free(struct redis_string_t *str) {
  free(str->data);
  free(str);
}

