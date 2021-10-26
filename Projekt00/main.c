/* ***************************************
* projekt00 : symulacja komputerowa *
*************************************** */
#include <stdio.h>
void foo();

int main ( void ) {
	int k;
	for (k=0; k<21; ++k)
	{
		foo();
	}
		while (1) ;
}


void foo () {
	static char text [175] = "GIGPCIGXSDEJYCMMXTYYLLYGMJAFJQXXMYMPCSYCTLVBPQZXOWHWGMSKUHPEVNIGRHLYNOHDWEOBSEWXUIFCXBPVGRYYNPHERFHENYUPHGBKYSFICHXVLIPAJMIHTOKYFGPLOWTDAQHJZRKPYAOCOHYPUUIFWKSXPKRGMWHABKHOIYU";
	static unsigned int i = 1;
	static char * buforp [4] = {0};
	char bufor [4] = "";
	if(i == 1) {
		buforp [0] = & text [13];
		buforp [1] = & text [01];
		buforp [2] = & text [19];
		buforp [3] = & text [90];
	} else {
		buforp [0] += 1;
		buforp [1] += 2;
		buforp [2] += 3;
		buforp [3] += 4;
	}
	bufor [0] = * buforp [0];
	bufor [1] = * buforp [1];
	bufor [2] = * buforp [2];
	bufor [3] = * buforp [3];
	++i; // tutaj warto postawic pulapke
}
