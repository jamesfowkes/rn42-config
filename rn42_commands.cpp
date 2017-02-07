#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

static const char s_local_echo[] PROGMEM = "+";
static const char s_get_gpio[] PROGMEM = "&";
static const char s_connect_stored_address[] PROGMEM = "C";
static const char s_connect_address[] PROGMEM = "C";
static const char s_connect_address_fast[] PROGMEM = "CF";
static const char s_connect_inquiry_fast[] PROGMEM = "CFI";
static const char s_connect_stored_address_fast[] PROGMEM = "CFR";
static const char s_connect_with_timeout[] PROGMEM = "CT";
static const char s_enter_fast_mode[] PROGMEM = "F,1";
static const char s_help[] PROGMEM = "H";
static const char s_inquiry_scan[] PROGMEM = "I";
static const char s_fast_inquiry_scan[] PROGMEM = "IN";
static const char s_quality_scan[] PROGMEM = "IQ";
static const char s_roving_networks_scan[] PROGMEM = "IS";
static const char s_cable_replacement_scan[] PROGMEM = "IR";
static const char s_hide_pin[] PROGMEM = "J";
static const char s_kill_connection[] PROGMEM = "K,";
static const char s_poll_link_quality[] PROGMEM = "L";
static const char s_remote_modem_status[] PROGMEM = "M";
static const char s_other_settings[] PROGMEM = "O";
static const char s_pass_chars[] PROGMEM = "P";
static const char s_quiet_mode[] PROGMEM = "Q";
static const char s_reboot[] PROGMEM = "R,1";
static const char s_enable_recv_passthru[] PROGMEM = "T";
static const char s_uart_config[] PROGMEM = "U";
static const char s_fw_version[] PROGMEM = "V";
static const char s_enable_discover_connect[] PROGMEM = "W";
static const char s_enter_sleep[] PROGMEM = "Z";

static char const * const s_commands[] = {
	s_local_echo,
	s_get_gpio,
	s_connect_stored_address,
	s_connect_address,
	s_connect_address_fast,
	s_connect_inquiry_fast,
	s_connect_stored_address_fast,
	s_connect_with_timeout,
	s_enter_fast_mode,
	s_help,
	s_inquiry_scan,
	s_fast_inquiry_scan,
	s_quality_scan,
	s_roving_networks_scan,
	s_cable_replacement_scan,
	s_hide_pin,
	s_kill_connection,
	s_poll_link_quality,
	s_remote_modem_status,
	s_other_settings,
	s_pass_chars,
	s_quiet_mode,
	s_reboot,
	s_enable_recv_passthru,
	s_uart_config,
	s_fw_version,
	s_enable_discover_connect,
	s_enter_sleep,
	NULL
};

static bool leave_command_mode_after_cmd(char const * const cmd)
{
	bool leave = true;
	leave = leave && cmd[0] != 'K';
	leave = leave && cmd[0] != 'R';
	return leave;
}

bool rn42_is_valid_command(char const * const cmd)
{
	int i = 0;
	while (s_commands[i])
	{
		int command_length = strlen_P(s_commands[i]);
		if (strncmp_P(cmd, s_commands[i], command_length) == 0)
		{
			return true;
		}
		i++;
	}
	return false;
}

bool rn42_run_command(Stream& stream, char const * const cmd, char * buffer)
{
	bool valid = rn42_is_valid_command(cmd);

	if (valid)
	{
		rn42_enter_command_mode(stream);
		stream.print(cmd);
		stream.print('\n');
		read_with_timeout(stream, buffer, 1000);
		if (leave_command_mode_after_cmd(cmd))
		{
			rn42_leave_command_mode(stream);
		}
	}

	return valid;
}
