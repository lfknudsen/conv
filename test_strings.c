#include <assert.h>
#include "strings.h"
#include "stdlib.h"
#include "ctype.h"

int main()
{
	char *a = "HelLo! :)";
	char *b = "HelLo! :)";
	char *c = "hello! :)";
	char *d = "what?";
	char *e = "";

	assert(str_len(a) == 9);
	assert(str_len(b) == 9);
	assert(str_len(c) == 9);
	assert(str_len(d) == 5);
	assert(str_len(e) == 0);

	assert(str_until(a, '!') == 5);
	assert(str_until(b, 'm') == -1);
	assert(str_until(c, 'L') == -1);
	assert(str_until(d, 'w') == 0);
	assert(str_until(e, '\0') == 0);
	assert(str_until(a, ')') == 8);

	assert(str_match(a,a));
	assert(str_match(a,b));
	assert(str_match(a,c));
	assert(!str_match(a,d));
	assert(str_match(e,e));
	assert(!str_match(a,e));

	assert(str_comp(a,a));
	assert(str_comp(a,b));
	assert(!str_comp(a,c));
	assert(!str_comp(a,d));
	assert(str_comp(e,e));
	assert(!str_comp(a,e));

	char *super = "Test string";
	assert(str_len(super) == 11);
	char *sub	= "str";
	assert(str_len(sub) == 3);
	printf("%d\n", str_sub(super, sub));
	return 0;
}
