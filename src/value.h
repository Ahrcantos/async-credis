#ifndef REDIS_VALUE_H
#define REDIS_VALUE_H

#define REDIS_STRING_KIND 1

typedef int REDIS_VALUE_KIND;

// String
struct redis_string_t {
  char *data;
  size_t length;
};

struct redis_string_t *redis_string_new(char *str);
void redis_string_print(struct redis_string_t *str);
void redis_string_free(struct redis_string_t *str);


// Value
struct redis_value_t {
  REDIS_VALUE_KIND kind;
  union {
    struct redis_string_t *string;
  } data;
};

struct redis_value_t *redis_value_new(REDIS_VALUE_KIND kind, void *data);
void redis_value_print(struct redis_value_t *data);

#endif
