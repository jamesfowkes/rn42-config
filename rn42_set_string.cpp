#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

static char s_valid_flags[] = {
	'A', // Authentication mode
	'B', // Send break signal
	'C', // Set service field class
	'D', // Set device class
	'E', // Set UUID (versions > 5.4)
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
	'Y', // Transmit power
	'Z', // Raw baudrate
	'~', // Profile
	'-', // Serialized friendly name
	'|', // Radio/LED low power settings
	
	'\0'
};

static void send_set_string_command(Stream& stream, char flag, char * string)
{
	rn42_enter_command_mode(stream);
	stream.print('S');
	stream.print(flag);
	stream.print(',');
	stream.print(string);
	stream.print('\n');
	rn42_leave_command_mode(stream);
}

bool rn42_set_string(Stream& stream, char flag, char * string)
{
	bool result = is_valid_flag(flag, s_valid_flags);

	if (result)
	{
		send_set_string_command(stream, flag, string);
	}

	return result;
}
