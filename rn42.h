#ifndef _BLUESMIRF_H_
#define _BLUESMIRF_H_

void rn42_enter_command_mode(Stream& stream);
void rn42_leave_command_mode(Stream& stream);

bool rn42_get_setting_info_by_index(int n, char& flag, char * buffer);
bool rn42_get_setting_info_by_flag(char flag, char * buffer);

bool rn42_is_valid_set_flag(char flag);
bool rn42_set(Stream& stream, char flag, char const * const new_setting);

bool rn42_is_valid_get_flag(char flag);
void rn42_get_setting_value(Stream& stream, char flag, char * buffer);

bool rn42_is_valid_command(char const * const cmd);
bool rn42_run_command(Stream& stream, char const * const cmd, char * buffer);

void rn42_connect_stored_address(Stream& stream);
void rn42_connect_address(Stream& stream, char * address);
void rn42_connect_address_fast(Stream& stream, char * address);
void rn42_connect_inquiry_fast(Stream& stream);
void rn42_connect_stored_address_fast(Stream& stream);
void rn42_connect_with_timeout(Stream& stream, char * address, char * timeout);
void rn42_disconnect(Stream& stream);

void rn42_set_quiet_mode(Stream& stream, char mode);

#endif

