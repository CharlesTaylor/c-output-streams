#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "costreams.h"
#include <omp.h>
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
#define THREAD_COUNT 8
	omp_set_num_threads(THREAD_COUNT);
	cstream *building[THREAD_COUNT] = {NULL};
#pragma omp parallel
{
	int i;
	int id = omp_get_thread_num();

	building[id] = _(building[id],"This is thread ");
	building[id] = _(building[id],id);
	building[id] = _(building[id],"\n");
	for(i=0;i<3;i++){
		building[id] = _(building[id],i);
		building[id] = _(building[id],": ");
		building[id] = _(building[id],1.0/i);
		building[id] = _(building[id],"\n");
	}
}
	int i;
	for(i=0;i<THREAD_COUNT;i++){
		ccout(building[i]);
	}
	return 0;
}
