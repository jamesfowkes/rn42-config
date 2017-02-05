#include "rn42.h"

// Assumes that the rn42 is connected to Serial1
static Stream& s_rn42_serial = Serial1;

static bool s_command_ready = false;
static char s_command_buffer[32];
static int s_command_idx = 0;

static void print_rn42_settings()
{
	int i = 0;
	char flag;
	char flag_name[16];
	Serial.println("RN42 Settings:");

	while (rn42_get_setting_info_by_index(i++, flag, flag_name))
	{
		Serial.print(flag);
		Serial.print(": ");
		Serial.println(flag_name);		
	}
}


static void handle_list_cmd(char const * const cmd)
{
	(void)cmd;
	print_rn42_settings();
}

static void handle_get_cmd(char const * const cmd)
{
	char flag = cmd[0];
	char flag_name[16];
	char setting[32];

	rn42_get_setting_info_by_flag(flag, flag_name);
	Serial.print(flag_name);
	Serial.print(": ");
	
	rn42_get_setting_value(s_rn42_serial, flag, setting);
	Serial.println(setting);

	rn42_leave_command_mode(s_rn42_serial);

}

static void handle_set_cmd(char const * const cmd)
{
	char flag = cmd[0];
	char const * const new_setting = cmd + 1;

	rn42_set(s_rn42_serial, flag, new_setting);
	rn42_leave_command_mode(s_rn42_serial);
}

static void handle_command(char const * const cmd)
{
	switch(cmd[0])
	{
	case 'L':
		handle_list_cmd(&cmd[1]);
		break;
	
	case 'G':
		handle_get_cmd(&cmd[1]);
		break;

	case 'S':
		handle_set_cmd(&cmd[1]);
		break;
	}
}

void setup()
{
	Serial1.begin(115200);
	Serial.begin(115200);
}

void loop()
{
	if (s_command_ready)
	{
		handle_command(s_command_buffer);
		s_command_ready = false;
		s_command_idx = 0;
	}
}

void serialEvent()
{
	while(Serial.available())
	{
		char c = Serial.read();
		if (c != '\n')
		{
			s_command_buffer[s_command_idx++] = c;
			s_command_buffer[s_command_idx] = '\0';
		}
		else
		{
			s_command_ready = true;
		}
	}
}
