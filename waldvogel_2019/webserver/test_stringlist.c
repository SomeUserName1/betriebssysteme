#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "stringlist.h"

void testempty(void){
	stringlist* sl = stringlist_new(NULL);
	char *string = stringlist_string(sl);
	assert(strlen(string) == 0);
	free(string);
	stringlist_free(sl);
}

void testempty2(void){
	stringlist* sl = stringlist_new("");
	char *string = stringlist_string(sl);
	assert(strlen(string) == 0);
	free(string);
	stringlist_free(sl);
}

void testappend(void){
	stringlist* sl = stringlist_new("abc");
	stringlist_append(sl, "defg");
	stringlist_append(sl, "hij");
	stringlist_append(sl, "klmnopqrst");
	stringlist_append(sl, "vwxyz");
	char *string = stringlist_string(sl);
	assert(strcmp(string, "abcdefghijklmnopqrstuvxyz"));
	free(string);
	stringlist_free(sl);
}

void testappendnull(void){
	stringlist* sl = stringlist_new("abc");
	stringlist_append(sl, NULL);
	stringlist_append(sl, "def");
	char *string = stringlist_string(sl);
	assert(strcmp(string, "abcdef") == 0);
	free(string);
	stringlist_free(sl);
}

void testappendempty(void){
	stringlist* sl = stringlist_new("abc");
	stringlist_append(sl, "");
	stringlist_append(sl, "def");
	char *string = stringlist_string(sl);
	assert(strcmp(string, "abcdef") == 0);
	free(string);
	stringlist_free(sl);
}

void testlength(void){
	stringlist* sl = stringlist_new("abc");
	stringlist_append(sl, "defg");
	stringlist_append(sl, "hij");
	stringlist_append(sl, "klmnopqrst");
	stringlist_append(sl, "vwxyz");
	stringlist_append(sl, " ");
	char *string = stringlist_string(sl);
	assert(strlen(string) == stringlist_length(sl));
	free(string);
	stringlist_free(sl);
}

int main(void)
{
	testempty();
	testempty2();
	testappend();
	testappendempty();
	testappendnull();
	testlength();
	return 0;
}
