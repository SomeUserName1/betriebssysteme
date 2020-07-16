#ifndef STRINGLIST_H
#define STRINGLIST_H
struct stringlistnode {
	char *string;
	size_t stringlength;
	struct stringlistnode *next;
};
struct stringlist {
	struct stringlistnode *first;
	struct stringlistnode *last;
	size_t length;
};
typedef struct stringlist stringlist;

/* Initializes a stringlist with initialstring, if no initialstring is desired
 * NULL should be passed */
stringlist *stringlist_new(const char *initialstring);
/* Appends a duplicate of the string to the list. Can be NULL or empty */
stringlist *stringlist_append(stringlist *list, const char *string);
/* Returns the entire string, caller needs to free it */
char *stringlist_string(stringlist *list);
/* Returns the length of the entire string without any NULL-bytes*/
size_t stringlist_length(stringlist *list);
/* Frees all memory associated for the stringlist */
void stringlist_free(stringlist *list);

#endif
