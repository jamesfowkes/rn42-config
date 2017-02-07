#include "rn42.h"

#include <TaskAction.h>

static void led_task_fn(TaskAction * this_task)
{
	(void)this_task;
	static bool led_on = false;
	digitalWrite(13, led_on = !led_on);
}
static TaskAction s_led_task(led_task_fn, 500, INFINITE_TICKS);

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
	char flag_name[16] = {'\0'};
	char setting[32] = {'\0'};

	if (rn42_is_valid_set_flag(flag))
	{
		rn42_get_setting_info_by_flag(flag, flag_name);
		Serial.print(flag_name);
		Serial.print(": ");
		
		rn42_get_setting_value(s_rn42_serial, flag, setting);
		Serial.println(setting);

	}
	else
	{
		Serial.print("Unknown flag '");
		Serial.print(flag);
		Serial.println("'");
	}
}

static void handle_set_cmd(char const * const cmd)
{
	char flag = cmd[0];
	char const * const new_setting = cmd + 1;

	rn42_set(s_rn42_serial, flag, new_setting);
}

static void handle_cmd_cmd(char const * const cmd)
{
	char reply[1024];
	if (rn42_is_valid_command(cmd))
	{
		Serial.print("Running '");
		Serial.print(cmd);
		Serial.println("'");
		rn42_run_command(s_rn42_serial, cmd, reply);	
		Serial.println("Reply:");
		Serial.println(reply);
	}
	else
	{
		Serial.print("Unknown command '");
		Serial.print(cmd);
		Serial.println("'");
	}
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

	case 'C':
		handle_cmd_cmd(&cmd[1]);
		break;
	}
}

void setup()
{
	Serial1.begin(115200);
	Serial.begin(115200);

	pinMode(13, OUTPUT);
}

void loop()
{
	if (s_command_ready)
	{
		handle_command(s_command_buffer);
		s_command_ready = false;
		s_command_idx = 0;
	}

	while(s_rn42_serial.available())
	{
		Serial.print((char)s_rn42_serial.read());
	}

	s_led_task.tick();
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
