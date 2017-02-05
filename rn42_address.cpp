#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

bool rn42_address_store(Stream& stream, char * address)
{
	rn42_set_string(stream, 'R', address);
}

bool rn42_address_clear(Stream& stream)
{
	rn42_set_string(stream, 'R', "Z");
}
