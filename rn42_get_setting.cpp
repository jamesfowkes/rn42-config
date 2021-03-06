#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

static const char s_seven_bit_name[] PROGMEM = "7Seven Bit Mode";
static const char s_authentication_name[] PROGMEM = "AAuth Mode";
static const char s_service_class_name[] PROGMEM = "CService Class";
static const char s_device_class_name[] PROGMEM = "DDevice Class";
static const char s_uuid_or_encryption_name[] PROGMEM = "EUUID/Encryption";
static const char s_connected_address[] PROGMEM = "FConnectedAddress";
static const char s_hid_name[] PROGMEM = "HHID Profile";
static const char s_inquiry_scan_window_name[] PROGMEM = "IInq. Scan Window";
static const char s_page_scan_window_name[] PROGMEM = "JPage Scan Window";
static const char s_uart_parity_name[] PROGMEM = "LUART Parity";
static const char s_mode_name[] PROGMEM = "MMode";
static const char s_name_name[] PROGMEM = "NName";
static const char s_status_name[] PROGMEM = "OStatus";
static const char s_pin_name[] PROGMEM = "PPIN";
static const char s_special_config[] PROGMEM = "QSpecial Config";
static const char s_remote_addr_name[] PROGMEM = "RRemoteAddress";
static const char s_service_name_name[] PROGMEM = "SService Name";
static const char s_config_timer_name[] PROGMEM = "TConfig Timer";
static const char s_baudrate_name[] PROGMEM = "UBaudrate";
static const char s_sniff_mode_name[] PROGMEM = "WSniff Mode";
static const char s_bonding_enable_name[] PROGMEM = "XBonding";
static const char s_transmit_power_name[] PROGMEM = "YTx. Pwr.";
static const char s_profile_name[] PROGMEM = "~Profile";
static const char s_friendly_name_name[] PROGMEM = "-Friendly Name";
static const char s_role_switch_name[] PROGMEM = "?Role Switch";

static char const * const s_names[] = {
	s_seven_bit_name,
	s_authentication_name,
	s_service_class_name,
	s_device_class_name,
	s_uuid_or_encryption_name,
	s_connected_address,
	s_hid_name,
	s_inquiry_scan_window_name,
	s_page_scan_window_name,
	s_uart_parity_name,
	s_mode_name,
	s_name_name,
	s_status_name,
	s_pin_name,
	s_special_config,
	s_remote_addr_name,
	s_service_name_name,
	s_config_timer_name,
	s_baudrate_name,
	s_sniff_mode_name,
	s_bonding_enable_name,
	s_transmit_power_name,
	s_profile_name,
	s_friendly_name_name,
	s_role_switch_name,
	NULL
};

static int NUMBER_OF_SETTINGS = 25;
static const int FLAG_NOT_FOUND = -1;

static int get_flag_index(char flag)
{
	int i = 0;
	char pgm_flag;
	while (s_names[i])
	{
		pgm_flag = pgm_read_byte(s_names[i]);
		if (pgm_flag == flag)
		{
			return i;
		}
		i++;
	}
	return FLAG_NOT_FOUND;
}

bool rn42_is_valid_set_flag(char flag)
{
	return get_flag_index(flag) != FLAG_NOT_FOUND;
}

bool rn42_get_setting_info_by_index(int n, char& flag, char * buffer)
{
	flag = '\0';

	bool setting_exists = n < NUMBER_OF_SETTINGS;

	if (setting_exists)
	{
		flag = pgm_read_byte(s_names[n]);
		strcpy_P(buffer, s_names[n]+1);
	}

	return setting_exists;
}

bool rn42_get_setting_info_by_flag(char flag, char * buffer)
{
	int index = get_flag_index(flag);

	if (index != FLAG_NOT_FOUND)
	{
		strcpy_P(buffer, s_names[index]+1);
		return true;
	}
	return false;
}

void rn42_get_setting_value(Stream& stream, char flag, char * buffer)
{
	rn42_enter_command_mode(stream);

	stream.print('G');
	stream.print(flag);
	stream.print('\n');
	
	read_until_crnl(stream, buffer);

	rn42_leave_command_mode(stream);
}
