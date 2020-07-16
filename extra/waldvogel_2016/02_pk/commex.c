/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 15
 * @bonus10
 */

#include <stdio.h>

#define STATUS_DEFAULT 0 //begin
#define STATUS_CA      1 // char literal
#define STATUS_CAE     2 // char literal escape sequence
#define STATUS_S       3 // string literal
#define STATUS_SE      4 // string literal escape sequrnce
#define STATUS_C       5 // potential comment
#define STATUS_CB      6 // block comment begin
#define STATUS_CBE     7 // block comment potential end
#define STATUS_CL      8 // line comment


int main(void)
{
	int status = STATUS_DEFAULT;
	int c, buffer = 0;

	while ((c = getchar()) != EOF) {
		switch (status) {
		case STATUS_DEFAULT:
			switch (c) {
			case '/':
				buffer = c;
				status = STATUS_C;
				break;
			case '\'':
				putchar(c);
				status = STATUS_CA;
				break;
			case '"':
				putchar(c);
				status = STATUS_S;
				break;
			default:
				putchar(c);
				break;
			}
			break;
		case STATUS_CA:
			putchar(c);
			switch (c) {
			case '\\':
				status = STATUS_CAE;
				break;
			case '\'':
				status = STATUS_DEFAULT;
			default:
				break;
			}
			break;
		case STATUS_CAE:
			putchar(c);
			status = STATUS_CA;
			break;
		case STATUS_S:
			putchar(c);
			switch (c) {
			case '\\':
				status = STATUS_SE;
				break;
			case '"':
				status = STATUS_DEFAULT;
			default:
				break;
			}
			break;
		case STATUS_SE:
			putchar(c);
			status = STATUS_S;
			break;
		case STATUS_C:
			switch (c) {
			case '/':
				status = STATUS_CL;
				break;
			case '*':
				status = STATUS_CB;
				break;
			default:
				putchar(buffer);
				putchar(c);
				status = STATUS_DEFAULT;
				break;
			}
			break;
		case STATUS_CB:
			switch (c) {
			case '*':
				status = STATUS_CBE;
				break;
			default:
				break;
			}
			break;
		case STATUS_CBE:
			switch (c) {
			case '/':
				status = STATUS_DEFAULT;
				break;
			default:
				status = STATUS_CB;
				break;
			}
			break;
		case STATUS_CL:
			switch (c) {
			case '\n':
				status = STATUS_DEFAULT;
				break;
			default:
				status = STATUS_CL;
				break;
			}
			break;
		default:
			printf("illegal state");
			return -1;
		}
	}
	return 0;
}
