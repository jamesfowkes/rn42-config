#ifndef _BLUESMIRF_H_
#define _BLUESMIRF_H_

void rn42_enter_command_mode(Stream& stream);
void rn42_leave_command_mode(Stream& stream);

void rn42_get_flag_name(char flag, char * buffer);
void rn42_get_flag_value(Stream& stream, char flag, char * buffer);

bool rn42_set_flag(Stream& stream, char flag, bool value);
bool rn42_set_string(Stream& stream, char flag, char * value);

#endif
