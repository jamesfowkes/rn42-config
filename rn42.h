#ifndef _BLUESMIRF_H_
#define _BLUESMIRF_H_

void rn42_enter_command_mode(Stream& stream, bool force=false);
void rn42_leave_command_mode(Stream& stream, bool force=false);

void rn42_get_setting_name(char flag, char * buffer);
void rn42_get_setting_value(Stream& stream, char flag, char * buffer);

bool rn42_set_flag(Stream& stream, char flag, bool value);
bool rn42_set_string(Stream& stream, char flag, char * value);

#endif
