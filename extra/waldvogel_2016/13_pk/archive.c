/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 24
 * @bonus10
 * */
#include <stdio.h>

void archive(const char *s1, char *s2)
{
	int j = 0;

	for (int i = 0; s1[i] != '\0'; i++) {
		if (s1[i] + 1 == s1[i+1])
			//the chain is at least 3 long.
			if (s1[i + 1] + 1 == s1[i + 2]) {
				s2[j] = s1[i]; //copy start of sequence
				j++;
				s2[j] = '-';//write '-'
				j++;
				//skip all following chars
				while (s1[i] + 1 == s1[i+1])
					i++;
			}

		//copy char
		s2[j] = s1[i];
		j++;
	}
	s2[j] = '\0'; //end string
}

void extract(const char *s1, char *s2)
{
	int j = 0;
	char start = '\0';

	for (int i = 0; s1[i] != '\0'; i++) {
		if (s1[i] == '-') {
			//check, if the dash indicates a sequence
			if (start != '\0' && start < s1[i + 1]) {
				i++;
				//write all chars in between start and end
				while ((s2[j] = (char) (s2[j-1] + 1)) < s1[i])
					j++;
				start = s1[i];
			} else
				//the dash was not part of a sequence
				start = '\0';
		} else {
			start = s1[i];
		}

		//copy the next char
		s2[j] = s1[i];
		j++;
	}
	s2[j] = '\0'; //terminate the string
}

int main(void)
{
	char c1[100] =
"-abc xyz fghijklmnopqrstuvwxyz-- c-a 0123456789 0123456789:;<=>?@ABCDEF";
	char c2[100] = "";
	char c3[100] = "";

	char e1[100] = "-a-c xyz f-z-- c-a 0-3-5-9 0-F";
	char e2[100] = "";

	archive(c1, c2);
	extract(c2, c3);
	printf("Compress and extract:\noriginal:\t\"%s\"\n"
		"compressed:\t\"%s\"\nextracted:\t\"%s\"\n", c1, c2, c3);

	extract(e1, e2);
	printf("\nExtract (assignment example):\n"
		"compressed:\t\"%s\"\nextracted:\t\"%s\"\n", e1, e2);

	return 0;
}
