/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 15
 * @bonus10
 */
#include <stdio.h>
#include <string.h>

void word_count(void)
{
	int wordLen = 0;
	int c;
	int wordCount[16];

	memset(wordCount, 0, sizeof(wordCount));
	printf("Bitte geben sie einen Text ein:\n");

	while ((c = getchar()) != EOF) {
		//check if no word char
		if (c == ' ' || c == '\t' || c == '\n') {
			if (wordLen > 0) {
				if (wordLen < 16)
					wordCount[wordLen - 1]++;
				else
					wordCount[15]++;
			}
			wordLen = 0;
		} else {
			wordLen++;
		}
	}
	//add last word, if there was no whitespace
	if (wordLen > 0) {
		if (wordLen < 16)
			wordCount[wordLen - 1]++;
		else
			wordCount[15]++;
	}


	int wctotal = 0;
	float wordPercentage[16];

	for (int i = 0; i < 16; i++)
		wctotal += wordCount[i];

	if (wctotal == 0) {
		printf("\nEs wurden keine Wörter eingegeben.\n");
		return;
	}

	for (int i = 0; i < 16; i++)
		wordPercentage[i] =
			(100 * (float) wordCount[i] / (float) wctotal);

	printf("\nword\toccurence\thistogram\n");
	printf("length\tcount\tpercent\tplot\n");

	for (int i = 0; i < 15; i++) {
		printf("%d\t%d\t%.2f%%\t", i + 1, wordCount[i],
			wordPercentage[i]);

		for (int j = 0; j < (int) wordPercentage[i]; j++)
			printf("%s", "*");
		printf("\n");
	}
	if (wordCount[15] > 0)
		printf("There are %d words of length >= 16.\n", wordCount[15]);
	if (wctotal == 1)
		printf("There is one word.\n");
	else
		printf("In total there are %d words.\n", wctotal);
}

int main(void)
{
	word_count();
}
