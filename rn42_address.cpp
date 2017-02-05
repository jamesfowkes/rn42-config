#include <Arduino.h>

#include "rn42.h"
#include "rn42.private.h"

void rn42_address_store(Stream& stream, char * address)
{
	rn42_set(stream, 'R', address);
}

void rn42_address_clear(Stream& stream)
{
	rn42_set(stream, 'R', "Z");
}
