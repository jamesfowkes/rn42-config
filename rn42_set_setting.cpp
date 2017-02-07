#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

static bool is_valid_flag(char flag, char * pflags)
{
	while (*pflags != '\0')
	{
		if(*pflags == flag)
		{
			return true;
		}
		pflags++;
	}

	return false;
}


static char s_setting_flags[] = {
	'7', // Seven bit mode
	'A', // Authentication mode
	'B', // Send break signal
	'C', // Set service field class
	'D', // Set device class
	'E', // Set UUID (versions >= 5.4) or encryption (version < 5.40)
	'F', // Factory defaults (flag must be set to '1')
	'H', // HID flag register
	'I', // Set inquiry scan window
	'J', // Set page scan window
	'L', // UART parity
	'M', // Mode
	'N', // Device name
	'O', // Extended status string
	'P', // PIN code
	'Q', // Special configuration mask
	'R', // Remote address
	'S', // Service name
	'T', // Remote config timer
	'U', // Baudrate
	'W', // Smiff mode interval
	'X', // Accept bonding only from stored address
	'Y', // Transmit power
	'Z', // Raw baudrate
	'~', // Profile
	'-', // Serialized friendly name
	'|', // Radio/LED low power settings
	'?', // Enable role switch	
	'\0'
};

static void send_set_command(Stream& stream, char flag, char const * const string)
{
	rn42_enter_command_mode(stream);
	stream.print('S');
	stream.print(flag);
	stream.print(',');
	stream.print(string);
	stream.print('\n');
	read_until_crnl(stream, NULL);
	rn42_leave_command_mode(stream);
}

bool rn42_set(Stream& stream, char flag, char const * const string)
{
	bool result = is_valid_flag(flag, s_setting_flags);

	if (result)
	{
		send_set_command(stream, flag, string);
	}

	return result;
}
