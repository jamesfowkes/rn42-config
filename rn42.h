#ifndef _BLUESMIRF_H_
#define _BLUESMIRF_H_

void rn42_enter_command_mode(Stream& stream, bool force=false);
void rn42_leave_command_mode(Stream& stream, bool force=false);

bool rn42_get_setting_info_by_index(int n, char& flag, char * buffer);
bool rn42_get_setting_info_by_flag(char flag, char * buffer);

void rn42_get_setting_value(Stream& stream, char flag, char * buffer);

bool rn42_set(Stream& stream, char flag, char const * const new_setting);

#endif
