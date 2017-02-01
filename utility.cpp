bool is_valid_flag(char flag, char * pflags)
{
	while (*pflags != '\0')
	{
		if(*pflags == flag)
		{
			return true;
		}
	}

	return false;
}
