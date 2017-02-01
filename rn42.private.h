#ifndef _BLUESMIRF_PRIVATE_H_
#define _BLUESMIRF_PRIVATE_H_

char read_exactly_one_char(Stream& stream);
void read_until_crnl(Stream& stream, char * buffer=NULL);
void read_exactly_n_chars(Stream& stream, int n, char*buffer=NULL);

bool is_valid_flag(char flag, char * pflags);

#endif
