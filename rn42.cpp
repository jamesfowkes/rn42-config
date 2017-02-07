#include <Arduino.h>

#include "rn42.h"

char read_exactly_one_char(Stream& stream)
{
	while (!stream.available()) {}
	return stream.read();	
}

void read_until_crnl(Stream& stream, char * buffer)
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

void read_with_timeout(Stream& stream, char * buffer, unsigned long timeout)
{
	unsigned long start = millis();

	if (buffer)
	{
		while ((millis() - start) < timeout)
		{
			if (stream.available())
			{
				*buffer++ = stream.read();
				*buffer = '\0';
			}
		}
	}
	else
	{
		while ((millis() - start) < timeout)
		{
			if (stream.available())
			{
				(void)stream.read();
			}
		}
	}
}

void read_exactly_n_chars(Stream& stream, int n, char * buffer)
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

void rn42_enter_command_mode(Stream& stream)
{
	stream.print("$$$");
	delay(1000);
	read_until_crnl(stream, NULL);
}

void rn42_leave_command_mode(Stream& stream)
{
	stream.print("---\n");
	read_until_crnl(stream, NULL);
}

void rn42_get_bluetooth_name(Stream& stream, char * buffer)
{
	rn42_get_setting_value(stream, 'N', buffer);
}
