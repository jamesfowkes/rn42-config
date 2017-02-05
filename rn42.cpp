#include <Arduino.h>

#include "rn42.h"

static bool in_command_mode = false;

char read_exactly_one_char(Stream& stream)
{
	while (!stream.available()) {}
	return stream.read();	
}

void read_until_crnl(Stream& stream, char * buffer=NULL)
{
	char c = '\0';

	while (c != '\r')
	{
		c = read_exactly_one_char(stream);
		if (c != '\r' && buffer)
		{
			*buffer++ = c;
			*buffer = '\0';
		}
	}

	read_exactly_one_char(stream);
}

void read_exactly_n_chars(Stream& stream, int n, char*buffer=NULL)
{
	int i;
	char c;
	for (i = 0; i < n; i++)
	{
		c = read_exactly_one_char(stream);
		if (buffer)
		{
			*buffer++ = c;
			*buffer = '\0';
		}
	}
}

void rn42_enter_command_mode(Stream& stream, bool force)
{
	if (!in_command_mode || force)
	{
		stream.print("$$$");
		delay(1000);
		read_until_crnl(stream, NULL);
		in_command_mode = true;
	}
}

void rn42_leave_command_mode(Stream& stream, bool force)
{
	if (in_command_mode || force)
	{
		stream.print("---\n");
		read_until_crnl(stream, NULL);
		in_command_mode = false;
	}
}

void rn42_get_bluetooth_name(Stream& stream, char * buffer)
{
	rn42_get_setting_value(stream, 'N', buffer);
}
