//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

/************************************************************************/
/* IBM SDLC uses the CCITT-16 CRC. The CRC is initialized to 0xFFFF     */
/* prior to any calculations. On transmit the CRC includes all bytes    */
/* except the end-of-frame. The CRC is inverted and transmitted LSB     */
/* first. On reception the CRC bytes are included in the calculation.   */
/* This results in a constant value (0xF0B8) when no errors are found.  */
/************************************************************************/

unsigned short calc_crc(unsigned char *ptr, int count)
{
	int	crc, i;

	crc = 0;
	while(--count >= 0)	{
		crc = crc ^ (int)*ptr++ << 8;
		for(i = 0; i < 8; ++i)
			if(crc & 0x8000)
				crc = crc << 1 ^ 0x1021;
			else
				crc = crc << 1;
	}

	return (((unsigned short) (crc & 0xFFFF)));
}
