#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "costreams.h"

#define _(a,b) stream_add(a,b)

int main(void){
	
	cstream *a = _(_(_(0,"Testing stream_add_stream "),123)," + ");
	cstream *b = _(_(_(_(0,321.5)," = "),123+321.5),"\n");

	ccerr (_(a,b));

	ccout	(_(_(_(_(_(_(_(0,
			"Testing print streams: "),
			123),
			" + "),
			321.5),
			" = "),
			123+321.5),
			"\n")
		);

	cstream *building = NULL;
	
	int i;
	for(i=0;i<10;i++){
		building = _(building,i);
		building = _(building,": ");
		building = _(building,1.0/i);
		building = _(building,"\n");
	}
	ccout(building);
	return 0;
}
