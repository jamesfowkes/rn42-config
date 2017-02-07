#ifndef _BLUESMIRF_PRIVATE_H_
#define _BLUESMIRF_PRIVATE_H_

char read_exactly_one_char(Stream& stream);
void read_until_crnl(Stream& stream, char * buffer=NULL);
void read_exactly_n_chars(Stream& stream, int n, char*buffer=NULL);
void read_with_timeout(Stream& stream, char * buffer=NULL, unsigned long timeout = 500);

#endif
