#include <Arduino.h>

#include "rn42.h"

void rn42_connect_stored_address(Stream& stream)
{
	rn42_enter_command_mode(stream);
	rn42_run_command(stream, "K,", NULL);
	rn42_leave_command_mode(stream);	
}

void rn42_connect_address(Stream& stream, char * address)
{
	char command[] = "C,000000000000";
	if (address)
	{
		memcpy(&command[2], address, 12);
		rn42_enter_command_mode(stream);
		rn42_run_command(stream, command, NULL);
		rn42_leave_command_mode(stream);
	}
}

void rn42_connect_address_fast(Stream& stream, char * address)
{
	char command[] = "CF,000000000000";
	if (address)
	{
		memcpy(&command[3], address, 12);
		rn42_enter_command_mode(stream);
		rn42_run_command(stream, command, NULL);
		rn42_leave_command_mode(stream);
	}
}

void rn42_connect_inquiry_fast(Stream& stream)
{
	rn42_enter_command_mode(stream);
	rn42_run_command(stream, "CFI", NULL);
	rn42_leave_command_mode(stream);
}

void rn42_connect_stored_address_fast(Stream& stream)
{
	rn42_enter_command_mode(stream);
	rn42_run_command(stream, "CFR", NULL);
	rn42_leave_command_mode(stream);
}

void rn42_connect_with_timeout(Stream& stream, char * address, char * timeout)
{
	char command[] = "CT,000000000000\0\0\0\0";
	if (address)
	{
		memcpy(&command[3], address, 12);
		if (timeout)
		{
			command[15] = ',';
			strncpy(&command[16], timeout, 3);
		}
		rn42_enter_command_mode(stream);
		rn42_run_command(stream, command, NULL);
		rn42_leave_command_mode(stream);
	}
}

void rn42_disconnect(Stream& stream)
{
	rn42_enter_command_mode(stream);
	rn42_run_command(stream, "K,", NULL);
	// RN42 modules automatically leaves command mode after a disconnect
}

void rn42_set_quiet_mode(Stream& stream, char mode)
{
	char command[] = "Q\0\0";

	if (mode != '\0')
	{
		command[1] = ',';
		command[2] = mode;
	}

	rn42_enter_command_mode(stream);
	rn42_run_command(stream, command, NULL);
	rn42_leave_command_mode(stream);
}