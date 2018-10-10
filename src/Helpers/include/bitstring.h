//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------
#ifndef BITSTRINGH
#define BITSTRINGH

#include "hstring.h"

class BITSTRING : public HSTRING
{

private:	// User declarations


public:		// User declarations

    unsigned long	BytePointer;

    unsigned long	   BitPointer;

    unsigned long	   NumberOfBitsUsed;


	bool	EndReached;


    BITSTRING(unsigned int DeclaredMaximumSize);
	BITSTRING(unsigned int DeclaredMaximumSize, bool InputAutoResize);


    ~BITSTRING(void);



    void ResetBitPointer(void);

	void Zero(void);



    bool AppendBits(unsigned long NumberToAppend, unsigned long NumberOfBitsToAppend);



    unsigned long	 CopyNextBits(unsigned long NumberOfBitsToCopy);


// If not at a byte boundary, because we're in the middle of a bitstream in a byte, move to the next byte,
// filling the remaining bits in the current byte with a 1 or 0 as specified by the caller.
	void FillToNextByteBoundary(bool TurnRemainingBitsOn = false);


// If not at a byte boundary, because we're in the middle of a bitstream in a byte, move to the next byte.
	void MoveToNextByteBoundary(void);



    unsigned long	 GetNumber(void);


    bool EndOfBitString(void);

    
};
#endif

