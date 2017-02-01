#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

static char s_valid_flags[] = {
	'7', // Seven bit mode
	'E', // Encryption (version < 5.40)
	'F', // Factory defaults (flag must be set to '1')
	'Z', // Accept bonding only from stored address
	'?', // Enable role switch
	'\0'
};

static void send_set_flag_command(Stream& stream, char flag, bool value)
{
	rn42_enter_command_mode(stream);
	stream.print('S');
	stream.print(flag);
	stream.print(',');
	stream.print(value ? '1' : '0');
	stream.print('\n');
	rn42_leave_command_mode(stream);
}

bool rn42_set_flag(Stream& stream, char flag, bool value)
{
	bool result = is_valid_flag(flag, s_valid_flags);

	if (result)
	{
		send_set_flag_command(stream, flag, value);
	}

	return result;
}
