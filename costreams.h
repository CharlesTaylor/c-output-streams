#ifndef C_O_STREAMS
#define C_O_STREAMS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cstream{
	char *text;
	struct cstream *next;
} cstream;


cstream *stream_add_double( cstream *st, double val){
	cstream *nw = malloc(sizeof(cstream));
	size_t 	buf_size = snprintf(nw->text,0,"%lf",val);
	nw->text = malloc(buf_size+1);
	sprintf(nw->text,"%lf",val);
	nw->next = st;
	return nw;
}



cstream *stream_add_int( cstream *st, int val){
	cstream *nw = malloc(sizeof(cstream));
	size_t 	buf_size = snprintf(nw->text,0,"%d",val);
	nw->text = malloc(buf_size+1);
	sprintf(nw->text,"%d",val);
	nw->next = st;
	return nw;
}



cstream *stream_add_string( cstream *st, char *val){
	cstream *nw = malloc(sizeof(cstream));
	nw->text = val;
	nw->next = st;
	return nw;
}

cstream *stream_add_stream( cstream *st, cstream *ts){

	cstream *tmp = ts;
	while(tmp->next !=NULL){
		tmp = tmp->next;
	}
	tmp->next = st;
	return ts;
}


//Generics cant differentitate const types, This doesn't work
cstream *stream_add_const_string( cstream *st, const char *val){
	cstream *nw = malloc(sizeof(cstream));
	nw->text = malloc(strlen(val)+1);
	sprintf(nw->text,"%s",val);
	nw->next = st;
	return nw;
}

#define stream_add(stream,val) _Generic((val), \
                cstream *:stream_add_stream,\
                int:stream_add_int,\
                double:stream_add_double,\
                char*:stream_add_const_string\
                        )((stream),(val))



void cfout(FILE *fptr, cstream *stream){
	if(stream->next !=NULL){
		cfout(fptr,stream->next);
	}
	fprintf(fptr,"%s",stream->text);
	free(stream->text);
	free(stream);
}

void ccerr(cstream *stream){
	cfout(stderr,stream);
}

void ccout(cstream *stream){
	cfout(stdout, stream);
}

#endif
