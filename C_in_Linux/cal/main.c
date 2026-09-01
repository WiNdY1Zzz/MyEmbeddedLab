#include <stdio.h>
#include "amsd.h"

int main()
{
	int add_ab = add(10,20);
	int sub_ab = sub(10,20);
	int mul_ab = mul(10,20);
	int div_ab = div(10,20);

	printf("%d %d %d %d\n", add_ab, sub_ab, mul_ab, div_ab);

	return 0;
}
