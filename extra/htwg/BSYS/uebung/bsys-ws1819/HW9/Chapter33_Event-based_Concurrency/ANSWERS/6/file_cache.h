#ifndef __FILE_CACHE_H__
#define __FILE_CACHE_H__

#define FILE_CACHE_SIZE 3

typedef struct __file_cache_entry_t {
  char *file_path;
  char *content;
  off_t content_len;
  struct __file_cache_entry_t *next;
} file_cache_entry_t;

typedef struct __file_cache_t {
  int size;
  int current_size;
  file_cache_entry_t *head;
} file_cache_t;

void init_file_cache(file_cache_t *file_cache);
void insert_file_into_file_cache(file_cache_t *file_cache, char *file_path,
                                 char *file_content, off_t file_content_size);
file_cache_entry_t *create_file_cache_entry(char *file_path, char* file_content,
                                            off_t file_content_size);
int search_file_in_file_cache(file_cache_t *file_cache, char *file_path);
void print_files_in_file_cache(file_cache_t *file_cache);
void remove_oldest_entry_in_file_cache(file_cache_t *file_cache);
file_cache_entry_t *get_file_from_file_cache(file_cache_t *file_cache,
                                             char *file_path);
void clear_file_cache(file_cache_t *file_cache);


void init_file_cache(file_cache_t *file_cache) {
  file_cache->size = FILE_CACHE_SIZE;
  file_cache->current_size = 0;
  file_cache->head = NULL;
}

void insert_file_into_file_cache(file_cache_t *file_cache, char *file_path,
                                 char *file_content, off_t file_content_size) {

  if (file_cache->current_size < file_cache->size) {
    if (file_cache->head == NULL) {
      file_cache->head = create_file_cache_entry(file_path, file_content,
                                                 file_content_size);
    } else {
      file_cache_entry_t *old_head = file_cache->head;

      file_cache->head = create_file_cache_entry(file_path, file_content,
                                                 file_content_size);
      file_cache->head->next = old_head;
    }
    file_cache->current_size++;
    return;
  }
  remove_oldest_entry_in_file_cache(file_cache);
  insert_file_into_file_cache(file_cache, file_path, file_content,
                              file_content_size);
}

file_cache_entry_t *create_file_cache_entry(char *file_path, char* file_content,
                                            off_t file_content_size) {

  file_cache_entry_t *file_cache_entry = (file_cache_entry_t *)
                                          malloc(sizeof(file_cache_entry_t));

  file_cache_entry->file_path = malloc(strlen(file_path) + 1);
  file_cache_entry->content = malloc(strlen(file_content) + 1);
  strcpy(file_cache_entry->file_path, file_path);
  strcpy(file_cache_entry->content, file_content);
  file_cache_entry->content_len = file_content_size;
  file_cache_entry->next = NULL;

  return file_cache_entry;
}

int search_file_in_file_cache(file_cache_t *file_cache, char *file_path) {
  file_cache_entry_t *current_entry = file_cache->head;
  while(current_entry != NULL) {
    if (strcmp(current_entry->file_path, file_path) == 0) {
      printf("Found file: %s in file_cache.\n", file_path);
      return 1;
    }
    current_entry = current_entry->next;
  }
  printf("File: %s is not present in file_cache.\n", file_path);
  return 0;
}

void print_files_in_file_cache(file_cache_t *file_cache) {
  if (file_cache->current_size > 0) {
    file_cache_entry_t *current_entry = file_cache->head;
    while (current_entry != NULL) {
      printf("%s\n", current_entry->file_path);
      current_entry = current_entry->next;
    }
  }
  printf("File cache is empty.\n");
}

void remove_oldest_entry_in_file_cache(file_cache_t *file_cache) {
  file_cache_entry_t *current_entry = file_cache->head;

  while (current_entry->next->next != NULL) {
    current_entry = current_entry->next;
  }

  free(current_entry->next->file_path);
  free(current_entry->next->content);
  free(current_entry->next);
  current_entry->next = NULL;

  file_cache->current_size--;
}

file_cache_entry_t *get_file_from_file_cache(file_cache_t *file_cache, char *file_path) {
  file_cache_entry_t *current_entry = file_cache->head;

  while (current_entry != NULL) {
    if (strcmp(current_entry->file_path, file_path) == 0) {
      return current_entry;
    }
    current_entry = current_entry->next;
  }

  fprintf(stderr, "Error occured in get_file_from_file_cache(): No such element!\n");
  exit(-1);
}

void clear_file_cache(file_cache_t *file_cache) {
  while(file_cache->head != NULL) {
    file_cache_entry_t *tmp_entry = file_cache->head;
    file_cache->head = file_cache->head->next;
    free(tmp_entry->file_path);
    free(tmp_entry->content);
    free(tmp_entry);
  }
  file_cache->current_size = 0;
}

#endif
