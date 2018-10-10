//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

#include "bitstring.h"



//
// Reserve space for the local string and null it out.
//
BITSTRING::BITSTRING(unsigned int DeclaredMaximumSize) : HSTRING(DeclaredMaximumSize)
{
    ResetBitPointer();
    Char[BytePointer] = 0;
}



//
// Reserve space for the local string and null it out.
//
BITSTRING::BITSTRING(unsigned int DeclaredMaximumSize, bool InputAutoResize) : HSTRING(DeclaredMaximumSize, InputAutoResize)
{
    ResetBitPointer();
    Char[BytePointer] = 0;
}



//
// Free space allocated to the local string.
//
BITSTRING::~BITSTRING(void)
{
}



//
// ResetBitPointer
//
void BITSTRING::ResetBitPointer(void)
{
    BytePointer = 0;
    BitPointer = 0x80;
    NumberOfBitsUsed = 0;
	EndReached = false;
}




//
// Zero
//
void BITSTRING::Zero(void)
{
	ResetBitPointer();
	Copy("");
}




bool BITSTRING::AppendBits(unsigned long NumberToAppend, unsigned long NumberOfBitsToAppend)
{
    unsigned long	       Bit;


    if(BitPointer == 0x80)
    {
        Char[BytePointer] = 0;
    }

// If adding these bits will make the string too long, return an error.
    if(!SmartReallocate(BytePointer + ((NumberOfBitsToAppend + NumberOfBitsUsed) / 8) +
                        (((NumberOfBitsToAppend + NumberOfBitsUsed) % 8) ? 1 : 0)))
    {
        return(false);
    }

    Bit = 1;
    while(NumberOfBitsToAppend)
    {
        if(NumberToAppend & (1L << (NumberOfBitsToAppend - 1)))
        {
//           Char[BytePointer] |= ((unsigned char) BitPointer);
           Char[BytePointer] = ((unsigned char) (((unsigned char) BitPointer) | Char[BytePointer]));
        }

        --NumberOfBitsToAppend;
        Bit <<= 1L;
        BitPointer >>= 1L;
        ++NumberOfBitsUsed;
        if(BitPointer == 0)
        {
            BytePointer++;
            BitPointer = 0x80;
            Char[BytePointer] = 0;
            NumberOfBitsUsed = 0;
        }
    }

    Size = ((unsigned int) (BytePointer + ((BitPointer != 0x80) ? 1 : 0)));


    return(true);
}




unsigned long BITSTRING::CopyNextBits(unsigned long NumberOfBitsToCopy)
{
    unsigned long	   ReturnNumber;
    unsigned long	   Bit;


// If copying these bits will take us past the end of the string, return an error.
    if((BytePointer + ((NumberOfBitsToCopy + NumberOfBitsUsed) / 8) +
                        (((NumberOfBitsToCopy + NumberOfBitsUsed) % 8) ? 1 : 0)) > Size)
    {
		EndReached = true;
        return(0xFFFFFFFF);
    }

    else
    {
        ReturnNumber = 0;
        Bit = 1;

        while(NumberOfBitsToCopy)
        {
            if(Char[BytePointer] & BitPointer)
            {
                ReturnNumber |= (1L << (NumberOfBitsToCopy - 1));
            }
            Bit <<= 1L;
            --NumberOfBitsToCopy;
            BitPointer >>= 1L;
            ++NumberOfBitsUsed;
            if(BitPointer == 0)
            {
                BytePointer++;
                BitPointer = 0x80;
                NumberOfBitsUsed = 0;
            }
        }
    }

    return(ReturnNumber);
}






//
//	FillToNextByteBoundary
//		If not at a byte boundary, because we're in the middle of a bitstream in a byte, move to the next byte,
//		filling the remaining bits in the current byte with a 1 or 0 as specified by the caller.
//
void BITSTRING::FillToNextByteBoundary(bool TurnRemainingBitsOn)
{

// If we're not already at a byte boundary, get there.
	if(BitPointer != 0x80)
	{
	// Do the fill first.
		while(BitPointer != 0)
		{
			if(TurnRemainingBitsOn)
			{
				Char[BytePointer] = ((unsigned char) (((unsigned char) BitPointer) | Char[BytePointer]));
			}
			else
			{
				Char[BytePointer] = ((unsigned char) (((unsigned char) ~BitPointer) & Char[BytePointer]));
			}

	        BitPointer >>= 1L;
		    ++NumberOfBitsUsed;
		}

	// Move to the next byte.
		BytePointer++;
        BitPointer = 0x80;
		Char[BytePointer] = 0;
        NumberOfBitsUsed = 0;
	}

    Size = ((unsigned int) (BytePointer + ((BitPointer != 0x80) ? 1 : 0)));

	return;
} //	FillToNextByteBoundary






//
//	MoveToNextByteBoundary
//		If not at a byte boundary, because we're in the middle of a bitstream in a byte, move to the next byte.
//
void BITSTRING::MoveToNextByteBoundary(void)
{
// If we're not already at a byte boundary, get there.
	if(BitPointer != 0x80)
	{
		BytePointer++;
        BitPointer = 0x80;
        NumberOfBitsUsed = 0;
	}

	return;
} //	MoveToNextByteBoundary




unsigned long BITSTRING::GetNumber(void)
{
    unsigned long	   ReturnNumber;
    unsigned long	   Number;



    ReturnNumber = 0;
    if((Number = CopyNextBits(8)) != 0xFFFFFFFF)  ReturnNumber |= ((unsigned long) Number);
    if((Number = CopyNextBits(8)) != 0xFFFFFFFF)  ReturnNumber |= ((unsigned long) Number) << 8;
    ReturnNumber <<= 8;
    if((Number = CopyNextBits(8)) != 0xFFFFFFFF)  ReturnNumber |= ((unsigned long) Number) << 16;
    ReturnNumber <<= 8;
    if((Number = CopyNextBits(8)) != 0xFFFFFFFF)  ReturnNumber |= ((unsigned long) Number) << 24;

    if(Number == 0xFFFFFFFF)  ReturnNumber = Number;

    return(ReturnNumber);
}





bool BITSTRING::EndOfBitString(void)
{
    if(BytePointer >= Size)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}
