//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  Class name:     HWSTRING
//
//  Class description:
//      This class defines an interface to a wide character (wchar_t) string.
//      The string characteristics tracked are the current length (Size) and
//      the maximum size it may grow to (MaximumSize).  The maximum size is
//      defined at instantiation.  The Size will change as the string is erased,
//      rewritten, appended, etc.  Both the Size and the address (WChar) of the
//      created string are accessible to the outside world.
//
//      Instantiation reserves space for the local string.
//
//      Destruction will free space allocated to the local string.
//
//      AppendFillChar will add a caller specified fill character multiple
//      times to the end of the local string.
//
//      CopyChar will create a one character string consisting of the
//      character sent by the caller.
//
//      AppendChar will append a single character, sent by the caller, to the
//      end of the local string.
//
//      CopyString will copy either another HWSTRING or a character string to
//      the local string.
//
//      Append will append either another HWSTRING or a character string to
//      the end of the local string.
//
//      FindChar will search the local string for a caller specified character
//      and return true if found.
//
//      RemoveChar will search the local string for a caller specified character,
//      remove it and all the preceding characters from the local string, and
//      return true if found.
//
//
//
//	Changes to reallocation:
//		1) Reallocate uses a flag that specifies whether to resize smaller (default is true).  Reallocate calls in this space
//			should set this to false.
//		2) SmartReallocate should NOT add on the minimum additional amount for the first resize.
//		3) Reallocate needs to track the last resize amount (set to MaximumSize at instantiation).  SmartReallocate needs to
//			track the last smart reallocation amount (0 at outset).  When we go to do a SmartReallocate, if the last
//			reallocate amount is less than the last smart reallocate amount, indicating that someone deliberately made the
//			string smaller, then behave according to condition two above, as if this is the first resize.
//
//---------------------------------------------------------------------------

#include <ctype.h>		// data type conversion functions
#include <math.h>		// Standard math functions
#include <stdio.h>		// Standard I/O
#include <string.h>		// 'C' string functions

#include "hwstring.h"

//
//	InitializeAutoResizingInformation
//		Initialize auto resize information.  This is done at instantiation and whenever a reallocation is made that is
//		smaller than the current maximum size.
//
void HWSTRING::InitializeAutoResizingInformation( void )
{
	ResizeQuantity = HWSTRING_DEFAULT_AUTO_RESIZE_ADDITIONAL_SPACE;
	NumberOfCyclesSinceLastResize = 0;
	FirstAutoResizeAfterInstantiationOrReallocationToSmallerMaximumSize = true;
//	MinimumResizeQuantity = 0;
//	MaximumResizeQuantity = HWSTRING_MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE;

	return;
} // InitializeAutoResizingInformation






//
// Constructor for HWSTRING (overloaded versions #1, with maximum size and autoresize defined by caller).
// Reserve space for the local string and null it out.
//
HWSTRING::HWSTRING(unsigned int DeclaredMaximumSize, bool InputAutoResize)
{
	Size = 0;
	MaximumSize = DeclaredMaximumSize;
	wcSize = sizeof(wchar_t);
	WChar = new wchar_t[ MaximumSize + 1 ];     // Leave space for a NULL.
    WChar[0] = 0;
	MaximumSize = DeclaredMaximumSize;
    AutoResize = InputAutoResize;
	ReadOnly = false;		// Don't make it read only when there is no initializer data.
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;
}





//
// Constructor for HWSTRING (overloaded versions #2, initializing with null terminated constant character string, autoresize,
// and read only specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HWSTRING::HWSTRING(const wchar_t *InitialString, bool InputAutoResize, bool InputReadOnly)
{
    unsigned int       i;

	Size = wcslen(InitialString);

    MaximumSize = Size;
    wcSize = sizeof(wchar_t);
	WChar = new wchar_t[MaximumSize + 1 ];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
	{
		WChar[i] = InitialString[i];
    }

	WChar[Size] = 0;

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;

    return;
}





//
// Constructor for HWSTRING (overloaded versions #3, initializing with null terminated character string, autoresize,
// read only specifier , and initializer specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HWSTRING::HWSTRING(wchar_t *InitialString, bool InputAutoResize, bool InputReadOnly, bool UseInitializerBuffer)
{
    unsigned int       i;


	Size = wcslen(InitialString);
    wcSize = sizeof(wchar_t);

	if( UseInitializerBuffer )
	{
	    MaximumSize = Size;
		WChar = (wchar_t *) InitialString;
	}
	else
	{
	    MaximumSize = Size;
		WChar = new wchar_t[MaximumSize + 1 ];     // Leave space for a NULL.
	    for(i=0; i<Size; ++i)
		{
			WChar[i] = InitialString[i];
	    }

		WChar[Size] = 0;
	}

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = UseInitializerBuffer;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;

    return;
}




//
// Constructor for HWSTRING (overloaded versions #4, initializing with constant character string, length, autoresize,
// and read only specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HWSTRING::HWSTRING(const wchar_t *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize, bool InputReadOnly)
{
    unsigned int       i;


	Size = LengthOfInitialString;

    MaximumSize = Size;
    wcSize = sizeof(wchar_t);
	WChar = new wchar_t[MaximumSize + 1];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
	{
		WChar[i] = InitialString[i];
    }

	WChar[Size] = 0;

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;

    return;
}




//
// Constructor for HWSTRING (overloaded versions #5, initializing with character string, length, autoresize, read only specifier,
// and initializer specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HWSTRING::HWSTRING(wchar_t *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize, bool InputReadOnly,
					bool UseInitializerBuffer)
{
    unsigned int       i;


	Size = LengthOfInitialString;
    wcSize = sizeof(wchar_t);

	if( UseInitializerBuffer )
	{
	    MaximumSize = Size;
		WChar = InitialString;
	}
	else
	{
	    MaximumSize = Size;
		WChar = new wchar_t[MaximumSize + 1 ];     // Leave space for a NULL.
	    for(i=0; i<Size; ++i)
		{
			WChar[i] = InitialString[i];
	    }

		WChar[Size] = 0;
	}

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = UseInitializerBuffer;
	InitializeAutoResizingInformation();

    return;
}





//
// Constructor for HWSTRING (overloaded versions #6, initializing with HWSTRING, autoresize, and read only specifier  sent by
// caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HWSTRING::HWSTRING(HWSTRING *InitialString, bool InputAutoResize, bool InputReadOnly)
{
    unsigned int       i;


	Size = InitialString->Size;
    MaximumSize = Size;
    wcSize = sizeof(wchar_t);
	WChar = new wchar_t[MaximumSize + 1 ];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
    {
        WChar[i] = InitialString->WChar[i];
    }

	WChar[Size] = 0;

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;

    return;
}





//
// Constructor for HWSTRING (overloaded versions #7, initializing with HWSTRING and using the input string values for
// autoresize and read only.
// Reserve space for the local string and store the character string sent by the caller.
//
HWSTRING::HWSTRING(HWSTRING *InitialString)
{
    unsigned int       i;


	Size = InitialString->Size;
    MaximumSize = Size;
    wcSize = sizeof(wchar_t);
	WChar = new wchar_t[MaximumSize + 1 ];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
    {
        WChar[i] = InitialString->WChar[i];
    }

	WChar[Size] = 0;

    AutoResize = InitialString->AutoResize;
	ReadOnly = InitialString->ReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;

    return;
}






//
// Constructor for HWSTRING (overloaded versions #8, using default size).
// Reserve space for the local string and null it out.
//
HWSTRING::HWSTRING( void )
{
	Size = 0;
	MaximumSize = DEFAULT_AUTO_RESIZE_ADDITIONAL_SPACE;
    wcSize = sizeof(wchar_t);
	WChar = new wchar_t[ MaximumSize + 1 ];     // Leave space for a NULL.
    WChar[0] = 0;
    AutoResize = true;
	ReadOnly = false;		// Don't make it read only when there is no initializer data.
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
	UseUnicodeHexadecimalFormatForCharacterConversion = true;
}










//
// Free space allocated to the local string.
//
HWSTRING::~HWSTRING(void)
{
	if( !InitializerBufferUsed )
	{
		delete [] WChar;
	}
}



//
//	RangePositionsAreValid
//      Check to see if the range positions are valid for the string length set by the caller.  Note that the first position
//		may be greater than the last position, indicating that the range is in the reverse direction.
//
bool HWSTRING::RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length )
{
// Return an error if either range position is outside of the string length.
	if((FirstCharPosition >= Length) || (LastCharPosition >= Length))
	{
		return false;
	}
	else
	{
		return true;
	}
} // RangePositionsAreValid



//
//	RangePositionsAreValid
//      Check to see if the range positions are valid for the length of the local string.  Note that the first position
//		may be greater than the last position, indicating that the range is in the reverse direction.
//
bool HWSTRING::RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	return RangePositionsAreValid( FirstCharPosition, LastCharPosition, Size );
} // RangePositionsAreValid





//
//	RangeLength
//      Return the range length, where the range must be valid for the string length set by the caller.  Note that the first
//		position may be greater than the last position, indicating that the range is in the reverse direction.
//
unsigned int HWSTRING::RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length )
{
	if( RangePositionsAreValid( FirstCharPosition, LastCharPosition, Length ) )
	{
		return ((LastCharPosition >= FirstCharPosition) ?
									(LastCharPosition - FirstCharPosition + 1) :
									(FirstCharPosition - LastCharPosition + 1));
	}
	else
	{
		return 0;
	}
} // RangeLength





//
//	RangeLength
//      Return the range length, where the range must be valid for the length of the local string.  Note that the first
//		position may be greater than the last position, indicating that the range is in the reverse direction.
//
unsigned int HWSTRING::RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	return RangeLength( FirstCharPosition, LastCharPosition, Size );
} // RangeLength





//
//	RangeDirection
//      Return the range direction, where the range must be valid for the string length set by the caller.  Note that the first
//		position may be greater than the last position, indicating that the range is in the reverse direction.
//
int HWSTRING::RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length )
{
	int	Direction = 0;

	if( RangePositionsAreValid( FirstCharPosition, LastCharPosition, Length ) )
	{
		if( LastCharPosition >= FirstCharPosition)
		{
			Direction = 1;
		}
		else if( LastCharPosition < FirstCharPosition)
		{
			Direction = -1;
		}
	}

	return Direction;
} // RangeDirection






//
//	RangeDirection
//      Return the range direction, where the range must be valid for the length of the local string.  Note that the first
//		position may be greater than the last position, indicating that the range is in the reverse direction.
//
int HWSTRING::RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	return RangeDirection( FirstCharPosition, LastCharPosition, Size );
} // RangeDirection





//
// Reallocate
//      Resize the allocated space, copying the existing string to the new one.  Don't resize if the string will be too small
//		to retain existing data.
//
bool HWSTRING::Reallocate( unsigned int NewDeclaredMaximumSize, bool AllowResizingToASmallerSize )
{
	bool	Status = true;	// No errors yet.
    wchar_t	*Temp;      // Temporary pointer to new string memory
    unsigned int	i;          // Index



// If the size isn't changing, don't do anything.
	if( NewDeclaredMaximumSize == MaximumSize )
	{
		return true;
	}

// If reallocating will make the string too small to retain existing data, don't do the reallocate!
	if( NewDeclaredMaximumSize < Size )
	{
		return true;
	}

// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// If the new maximum size is smaller than the current maximum size, but we're not supposed to allow that, quit now.
	if( NewDeclaredMaximumSize < MaximumSize )
	{
		if( !AllowResizingToASmallerSize )
		{
			return true;
		}
		else
		{
		// New maximum is smaller, and it's OK to resize.  Reset the auto resizing information.
			InitializeAutoResizingInformation();
		}
	}

    wcSize = sizeof(wchar_t);
    Temp = new wchar_t[NewDeclaredMaximumSize + 1 ];    // Leave space for a NULL.

	if(Temp != NULL)
	{
	    for(i=0; ((i < Size) && (i < NewDeclaredMaximumSize)); ++i)
		{

			Temp[i] = WChar[i];
	    }

		Size = i;
	    MaximumSize = NewDeclaredMaximumSize;

		delete WChar;
	    WChar = Temp;
		WChar[Size] = 0;
	}
	else
	{
		Status = false;
	}

    return(Status);
} // Reallocate




//
// SmartReallocate
//      Resize the allocated space, copying the existing string to the new one.  We will
//		determine, within this routine, what to use for a reallocation size.  The caller
//		tells us the minimum size needed, but we're responsible for adding enough new memory,
//		based on reallocation history, to avoid constant memory reallocation.
//
bool HWSTRING::SmartReallocate(unsigned int NewSize)
{
	bool	Status = true;			// Assume success until we know otherwise.



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	++NumberOfCyclesSinceLastResize;

    if(NewSize >= MaximumSize)
	{
	    if(AutoResize)
		{
			if( FirstAutoResizeAfterInstantiationOrReallocationToSmallerMaximumSize )
			{
			// If this is the first time we've auto resized since startup or after reallocating to a smaller maximum, don't
			// do any padding.
				Reallocate( NewSize );
			}
			else
			{
				unsigned int	NewResizeQuantity = 100 * ResizeQuantity / NumberOfCyclesSinceLastResize;

				if(NewResizeQuantity > ResizeQuantity)
				{
					ResizeQuantity = NewResizeQuantity;
				}

				if(ResizeQuantity > HWSTRING_MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE)
				{
					ResizeQuantity = HWSTRING_MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE;
				}
/*
				if(ResizeQuantity > MaximumResizeQuantity)
				{
					ResizeQuantity = MaximumResizeQuantity;
				}

				if( ResizeQuantity < MinimumResizeQuantity )
				{
					ResizeQuantity = MinimumResizeQuantity;
				}
*/

//				if(ResizeQuantity > 2 * MaximumSize)
//				{
//					ResizeQuantity = 2 * MaximumSize;
//				}

				Reallocate( NewSize + ResizeQuantity );
			}

			FirstAutoResizeAfterInstantiationOrReallocationToSmallerMaximumSize = false;

			NumberOfCyclesSinceLastResize = 0;
		}

		else
		{
		// We need more space, but we're not allowed to get it; WOOF!
			Status = false;
		}
    }

    return(Status);
} // SmartReallocate




//
// Resize
//		Set size to the caller specified value, resizing the string if necessary to add space.  This can be used by application
//		code to set string length before directly writing to WChar.
//
bool HWSTRING::Resize(unsigned int NewSize)
{
	bool	Status = true;	// No errors yet.



// If NewSize is greater than the maximum size, reset it.
	if( NewSize > MaximumSize )
	{
		Status = Reallocate( NewSize );
	}

// If no errors so far, do the resize.
	if( Status )
	{
		Size = NewSize;
	}

    return(Status);
} // Resize




//
// Add a caller specified fill character multiple (NumberOfTimesToAppend)
// times to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::AppendFillChar(int InputCharacter, unsigned int NumberOfTimesToAppend)
{
	unsigned int	i;



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(Size + NumberOfTimesToAppend);

	if(NumberOfTimesToAppend <= (MaximumSize - Size))
	{
		if (wcSize == 2)
		{
			for(i=0; i<NumberOfTimesToAppend; ++i)
			{
				WChar[i+Size] = ((wchar_t) (InputCharacter & 0xffff));
			}
		}
		else
		{
			for(i=0; i<NumberOfTimesToAppend; ++i)
			{
				WChar[i+Size] = ((wchar_t) (InputCharacter));
			}
		}
		Size += NumberOfTimesToAppend;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Add a caller specified fill character multiple (NumberOfTimesToInsert)
// times to the beginning of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::InsertFillChar(int InputCharacter, unsigned int NumberOfTimesToInsert)
{
	unsigned int	i;
    unsigned int	j;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(Size + NumberOfTimesToInsert);

    if(NumberOfTimesToInsert == 0)
    {
    	return(true);
    }

    else if(NumberOfTimesToInsert <= (MaximumSize - Size))
	{
    // Shift upwards to make room for fill characters
    	j = Size + NumberOfTimesToInsert - 1;
        i = Size - 1;

        while(j >= NumberOfTimesToInsert)
        {
        	WChar[j--] = WChar[i--];
        }

    // Now, insert the characters
        if (wcSize == 2)
        {
			for(i = 0;    i < NumberOfTimesToInsert;    ++i)
			{
				WChar[i] = ((wchar_t) (InputCharacter & 0xffff));
			}
        }
        else
        {
			for(i = 0;    i < NumberOfTimesToInsert;    ++i)
			{
				WChar[i] = ((wchar_t) (InputCharacter));
			}
        }

    	Size += NumberOfTimesToInsert;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}




//
// Create a one character string consisting of the character sent by the caller.
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::CopyChar(int InputCharacter)
{
// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	Size = 0;


   	SmartReallocate(1);

	if(Size < MaximumSize)
	{
		if (wcSize == 2)
		{
			WChar[Size++] = ((wchar_t) (InputCharacter & 0xffff));
		}
		else
		{
			WChar[Size++] = ((wchar_t) (InputCharacter));
		}
        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}




//
// Append a single character, sent by the caller, to the end of the local string.
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::AppendChar(int InputCharacter)
{
// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(Size + 1);

	if(Size < MaximumSize)
	{
		if (wcSize == 2)
		{
			WChar[Size++] = ((wchar_t) (InputCharacter & 0xffff));
		}
		else
		{
			WChar[Size++] = ((wchar_t) (InputCharacter));
		}
        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}




//
//	InsertNumber (overloaded version #1: unsigned char)
//		Insert a unsigned char, sent by the caller, into the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than a unsigned char, then zero fill the
//		remaining unsigned chars.  Note that numbers are stored little endian.
//
bool HWSTRING::InsertNumber(int Position, unsigned char InputNumber, unsigned int Length)
{
// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Quit on invalid position.
	if(Position < 0)  return(false);

   	SmartReallocate(Position + Length);

	if((Position + Length) <= MaximumSize)
	{
		if(Length)
		{
			WChar[Position++] = (wchar_t) InputNumber;
			--Length;
		}

		while(Length)
		{
			WChar[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			WChar[Size] = 0;
		}

		return(true);
	}

	else
	{
		return(false);
	}
}




//
//	InsertNumber (overloaded version #2: unsigned short)
//		Insert a unsigned short, sent by the caller, into the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than a unsigned short, then zero fill the
//		remaining unsigned chars.  If the length is shorter than a unsigned short, truncate the input unsigned short.
//		Note that numbers are stored little endian.
//
bool HWSTRING::InsertNumber(int Position, unsigned short InputNumber, unsigned int Length)
{
	unsigned int		i;			// Counter for number of unsigned chars copied
	unsigned int		Divisor;	// Divisor (multiple of 256) to apply to next byte


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Quit on invalid position.
	if(Position < 0)  return(false);

   	SmartReallocate(Position + Length);

	if((Position + Length) <= MaximumSize)
	{
		i = sizeof(unsigned short);			// Maximum of 2 unsigned chars to write from the input number
		Divisor = 1;
		while((i) && (Length))
		{
			WChar[Position++] = ((wchar_t) ((InputNumber / Divisor) & 0xFF));
			Divisor *= 256;
			i--;
			--Length;
		}

		while(Length)
		{
			WChar[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			WChar[Size] = 0;
		}

		return(true);
	}

	else
	{
		return(false);
	}
}




//
//	InsertNumber (overloaded version #3: unsigned int)
//		Insert a unsigned int, sent by the caller, into the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than a unsigned int, then zero fill the
//		remaining unsigned chars.  If the length is shorter than a unsigned int, truncate the input unsigned int.
//		Note that numbers are stored little endian.
//
bool HWSTRING::InsertNumber(int Position, unsigned int InputNumber, unsigned int Length)
{
	unsigned int		i;			// Counter for number of unsigned chars copied
	unsigned int		Divisor;	// Divisor (multiple of 256) to apply to next byte


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Quit on invalid position.
	if(Position < 0)  return(false);

   	SmartReallocate(Position + Length);

	if((Position + Length) <= MaximumSize)
	{
		i = sizeof(unsigned int);			// Maximum of 4 unsigned chars to write from the input number
		Divisor = 1;
		while((i) && (Length))
		{
			WChar[Position++] = ((wchar_t) ((InputNumber / Divisor) & 0xFF));
			Divisor *= 256;
			i--;
			--Length;
		}

		while(Length)
		{
			WChar[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			WChar[Size] = 0;
		}

		return(true);
	}

	else
	{
		return(false);
	}
}




//
//	InsertNumber (overloaded version #4: int)
//		Insert an int, sent by the caller, into the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than an int, then zero fill the
//		remaining unsigned chars.  If the length is shorter than an int, truncate the input int.
//		Note that numbers are stored little endian.
//
bool HWSTRING::InsertNumber(int Position, int InputNumber, unsigned int Length)
{
	unsigned int		i;			// Counter for number of unsigned chars copied
	unsigned int		Divisor;	// Divisor (multiple of 256) to apply to next byte


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Quit on invalid position.
	if(Position < 0)  return(false);

   	SmartReallocate(Position + Length);

	if((Position + Length) <= MaximumSize)
	{
		i = sizeof(int);			// Maximum of size int unsigned chars to write from the input number
		Divisor = 1;
		while((i) && (Length))
		{
			WChar[Position++] = ((wchar_t) ((InputNumber / Divisor) & 0xFF));
			Divisor *= 256;
			i--;
			--Length;
		}

		while(Length)
		{
			WChar[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			WChar[Size] = 0;
		}

		return(true);
	}

	else
	{
		return(false);
	}
}



//
//	AppendNumber (overloaded version #1: unsigned char)
//		Append a unsigned char, sent by the caller, to the end of the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than a unsigned char, then zero fill the
//		remaining unsigned chars.  Note that numbers are stored little endian.
//
bool HWSTRING::AppendNumber(unsigned char InputNumber, unsigned int Length)
{
	return(InsertNumber(Size, InputNumber, Length));
}




//
//	AppendNumber (overloaded version #2: unsigned short)
//		Append a unsigned short, sent by the caller, to the end of the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than a unsigned short, then zero fill the
//		remaining unsigned chars.  If the length is shorter than a unsigned short, truncate the input unsigned short.
//		Note that numbers are stored little endian.
//
bool HWSTRING::AppendNumber(unsigned short InputNumber, unsigned int Length)
{
	return(InsertNumber(Size, InputNumber, Length));
}




//
//	AppendNumber (overloaded version #3: unsigned int)
//		Append a unsigned int, sent by the caller, to the end of the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than a unsigned int, then zero fill the
//		remaining unsigned chars.  If the length is shorter than a unsigned int, truncate the input unsigned int.
//		Note that numbers are stored little endian.
//
bool HWSTRING::AppendNumber(unsigned int InputNumber, unsigned int Length)
{
	return(InsertNumber(Size, InputNumber, Length));
}




//
//	AppendNumber (overloaded version #4: int)
//		Append an int, sent by the caller, to the end of the local string.
//		The resulting length must not exceed the maximum size of the string, or the
// 		operation will fail.  If the length is longer than an int, then zero fill the
//		remaining unsigned chars.  If the length is shorter than an int, truncate the input int.
//		Note that numbers are stored little endian.
//
bool HWSTRING::AppendNumber(int InputNumber, unsigned int Length)
{
	return(InsertNumber(Size, InputNumber, Length));
}



// Copy operator (=) for HWSTRING
void HWSTRING::operator = (HWSTRING *StringToCopy)
{
	if( StringToCopy == 0 )
		Size = 0;
	else
		Copy(StringToCopy);
}



// Copy operator (=) for char *
void HWSTRING::operator = (const wchar_t *StringToCopy)
{
	if( StringToCopy == 0 )
		Size = 0;
	else
		Copy(StringToCopy);
}



// Append operator (+) for HWSTRING
HWSTRING HWSTRING::operator + (HWSTRING StringToAppend)
{
	HWSTRING		Temp(StringToAppend.Size + Size, true);
	Temp.Copy(WChar, Size);
//	Temp.Append(&StringToAppend);

	return Temp;
}



// Append operator (+) for char *
HWSTRING HWSTRING::operator + (const wchar_t *StringToAppend)
{
	HWSTRING		Temp(wcslen(StringToAppend) + Size, true);
	Temp.Copy(WChar, Size);
//	Temp.Append(StringToAppend, wcslen(StringToAppend));

	return Temp;
}




//
// Overloaded version #1 of string copy:  Copy another HWSTRING over the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Copy(HWSTRING *StringToCopy)
{
	unsigned int	i;



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	Size = 0;

   	SmartReallocate(StringToCopy->Size);

	if(StringToCopy->Size <= MaximumSize)
	{
		for(i=0; i<StringToCopy->Size; ++i)
		{
			WChar[i] = StringToCopy->WChar[i];
		}
		Size = StringToCopy->Size;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Overloaded version #2 of string copy:  Copy a character string over the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Copy(const wchar_t *StringToCopy, unsigned int LengthOfStringToCopy)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	Size = 0;

   	SmartReallocate(LengthOfStringToCopy);

	if(LengthOfStringToCopy <= MaximumSize)
	{
		for(i=0; i<LengthOfStringToCopy; ++i)
		{
			WChar[i] = StringToCopy[i];
		}
		Size = LengthOfStringToCopy;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Overloaded version #3 of string copy:  Copy a character string over the local string, using the NULL to
// determine length.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Copy(const wchar_t *StringToCopy)
{
    return(Copy(StringToCopy, ((unsigned int) ( wcslen( StringToCopy ) ))));
}





//
// Overloaded version #4 of string copy:  Copy a char* string in the range specified by the caller.
// Note that if the last position is before the first position, then the string will have to
// be reversed.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Copy(const wchar_t *StringToCopy, unsigned int LengthOfStringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition)
{
	unsigned int	i, j;
	unsigned int	NewSize;



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Quit if either range position is outside of the string to copy
	if((FirstCharPosition >= LengthOfStringToCopy) || (LastCharPosition >= LengthOfStringToCopy))
	{
		return false;
	}


	Size = 0;

	NewSize = ((LastCharPosition >= FirstCharPosition) ?
		(LastCharPosition - FirstCharPosition + 1) :
					(FirstCharPosition - LastCharPosition + 1));

   	SmartReallocate(NewSize);

	if(NewSize <= MaximumSize)
	{
		j = 0;
	// Are we copying forward or reverse?
		if(LastCharPosition >= FirstCharPosition)
		{
			for(i = FirstCharPosition;    i <= LastCharPosition;    ++i)
			{
				WChar[j++] = StringToCopy[i];
			}
		}
		else
		{
			i = FirstCharPosition;
			for(j = 0;    j < NewSize;    ++j)
			{
				WChar[j] = StringToCopy[i];
				--i;
			}
		}

		Size = NewSize;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Overloaded version #5 of string copy:  Copy an HWSTRING in the range specified by the caller.
// Note that if the last position is before the first position, then the string will have to
// be reversed.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Copy(HWSTRING *StringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition)
{
	return(Copy( StringToCopy->WChar, StringToCopy->Size, FirstCharPosition, LastCharPosition));
}







//
// Overloaded version #1 of copy to range:  Copy a char* string to the range specified by the caller.
// Note that if the last position is before the first position, then the string will have to
// be reversed.
//
// If the string being copied contains more characters than the range allows, the characters will
// be right truncated. If the string being copied contains less characters than the range allows,
// then the remainder of the range will be untouched.
//
// The range must fall within the maximum size of the string being copied to.  If the range is
// within the maximum size, but exceeds the current size in use, then the current size in use is
// increased to include the range.
//
// NOTE:  Unlike other copy routines, which zero out the string being copied to so that it will
// only contain the new data, this routine doesn't do that.  If, for example, the current number
// of characters in use is 7 for string data "abcdefg", and a copy is done to range 2,3 of string
// "hi", the current number of characters in use will still be 7, and the string data will be
// "abhiefg".
//
bool HWSTRING::CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, const wchar_t *StringToCopy,
											unsigned int LengthOfStringToCopy)
{
	unsigned int	i, j;
	unsigned int	NumberOfCharactersToCopy;



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Quit if either range position is outside of the string being copied and we're not set to
// auto-resize.
	unsigned int	MaximumSizeRequiredByCopyRange =
		(FirstCharPosition > LastCharPosition) ? (FirstCharPosition + 1) : (LastCharPosition + 1);

   	SmartReallocate(MaximumSizeRequiredByCopyRange);


// If either range position is above Size, change Size to be one position above.
	if(FirstCharPosition >= Size)
	{
		Size = FirstCharPosition + 1;
	}
	if(LastCharPosition >= Size)
	{
		Size = LastCharPosition + 1;
	}


// First compute number of characters to copy as the distance between the first and last
// character position + 1.  If there aren't that many characters in the string to be copied,
// change this to the number of characters in the string to be copied.
	NumberOfCharactersToCopy = ((LastCharPosition >= FirstCharPosition) ?
		(LastCharPosition - FirstCharPosition + 1) :
					(FirstCharPosition - LastCharPosition + 1));
	if(NumberOfCharactersToCopy > LengthOfStringToCopy)
	{
		NumberOfCharactersToCopy = LengthOfStringToCopy;
	}


// Are we copying forward or reverse?
	if(LastCharPosition >= FirstCharPosition)
	{
		i = FirstCharPosition;
		for(j = 0;    j < NumberOfCharactersToCopy; ++j)
		{
			WChar[i++] = StringToCopy[j];
		}
	}
	else
	{
		i = FirstCharPosition;
		for(j = 0;    j < NumberOfCharactersToCopy; ++j)
		{
			WChar[i--] = StringToCopy[j];
		}
	}

    WChar[Size] = 0;

	return(true);
}





//
// Overloaded version #2 of copy to range:  Copy an HWSTRING to the range specified by the caller.
// Note that if the last position is before the first position, then the string will have to
// be reversed.
//
// If the string being copied contains more characters than the range allows, the characters will
// be right truncated. If the string being copied contains less characters than the range allows,
// then the remainder of the range will be untouched.
//
// The range must fall within the maximum size of the string being copied to.  If the range is
// within the maximum size, but exceeds the current size in use, then the current size in use is
// increased to include the range.
//
// NOTE:  Unlike other copy routines, which zero out the string being copied to so that it will
// only contain the new data, this routine doesn't do that.  If, for example, the current number
// of characters in use is 7 for string data "abcdefg", and a copy is done to range 2,3 of string
// "hi", the current number of characters in use will still be 7, and the string data will be
// "abhiefg".
//
bool HWSTRING::CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, HWSTRING *StringToCopy)
{
	return(CopyToRange(FirstCharPosition, LastCharPosition, ((wchar_t *) StringToCopy->WChar),
																StringToCopy->Size));
}






//
// Overloaded version #1 of string append:  Append another HWSTRING to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Append(HWSTRING *StringToAppend)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(StringToAppend->Size + Size);

	if(StringToAppend->Size <= (MaximumSize - Size))
	{
		for(i=0; i<StringToAppend->Size; ++i)
		{
			WChar[i+Size] = StringToAppend->WChar[i];
		}
		Size += StringToAppend->Size;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Overloaded version #2 of string append:  Append a character string to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Append(const wchar_t *StringToAppend, unsigned int LengthOfStringToAppend)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(LengthOfStringToAppend + Size);

	if(LengthOfStringToAppend <= (MaximumSize - Size))
	{
		for(i=0; i<LengthOfStringToAppend; ++i)
		{
			WChar[i+Size] = StringToAppend[i];
		}
		Size += LengthOfStringToAppend;

        WChar[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Overloaded version #3 of string append:  Append a null terminated character string to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::Append(const wchar_t *StringToAppend)
{
	return(Append(((wchar_t *) StringToAppend), ((unsigned int) wcslen(StringToAppend))));
}





//
//  Search the local string for a caller specified character, returning true if
//  found and false otherwise.
//
bool HWSTRING::FindChar(int IntInputCharacter)
{
	unsigned int	i;
	wchar_t	InputCharacter;


	i = 0;
	if (wcSize == 2)
	{
		InputCharacter = ((wchar_t) (IntInputCharacter & 0xffff));
	}
	else
	{
		InputCharacter = ((wchar_t) (IntInputCharacter));
	}
	while((i < Size) && (WChar[i] != InputCharacter))
	{
		++i;
	}

	if(i < Size)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}





//
// Search the local string for a caller specified character:
//  - If found, remove everything from the beginning of the string up to and
//      including the character; return true to indicate success.
//  - If not found, return false to indicate that no instance of the character
//      was found.
//
bool HWSTRING::RemoveChar(int IntInputCharacter)
{
	unsigned int	i, j;
	wchar_t	InputCharacter;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	i = 0;
	if (wcSize == 2)
	{
		InputCharacter = ((wchar_t) (IntInputCharacter & 0xffff));
	}
	else
	{
		InputCharacter = ((wchar_t) (IntInputCharacter));
	}
	while((i < Size) && (WChar[i] != InputCharacter))
	{
		++i;
	}

	if(i < Size)
	{
		j = 0;
		++i;
		while(i < Size)
		{
			WChar[j++] = WChar[i++];
		}
		Size = j;

        WChar[Size] = 0;

		return(true);
	}
	else
	{
		return(false);
	}
}




//
//	CopyNumberFromString (overloaded version #1: unsigned char* output)
//		Copy unsigned char number from the local string to the caller specified unsigned char from the caller
//		specified index in the local string .  If there are not enough characters in the local
//		string, copy what there is, but return an error.  Otherwise, copy characters according
//		to the requested length or the size of unsigned char, whichever is smaller.  Note that numbers
//		are stored little endian.
//
bool HWSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned char *CopyDestination)
{
    bool        ReturnStatus;               //
	unsigned int		IndexToEndOfCopyLocation;	// Index to the position after the end of the copy string
	unsigned int		Multiplier;					// Multiplier (multiple of 256) to apply to next byte



	if(sizeof(unsigned char) < LengthToCopy)
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + sizeof(unsigned char);
	}
	else
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + LengthToCopy;
	}


	if(IndexToEndOfCopyLocation > Size)
	{
        ReturnStatus = false;
	}
	else
	{
        ReturnStatus = true;
	}


	Multiplier = 1;
	*CopyDestination = 0;

    while(IndexToStartOfCopyLocation < IndexToEndOfCopyLocation)
	{
//	    *CopyDestination += ((unsigned char) (((unsigned short) WChar[IndexToStartOfCopyLocation++]) * Multiplier));
    	if (wcSize == 2)
    		*CopyDestination = ((unsigned char) (*CopyDestination + ((unsigned char) (((unsigned short) WChar[IndexToStartOfCopyLocation++]) * Multiplier))));
    	else
    		*CopyDestination = ((unsigned char) (*CopyDestination + ((unsigned char) (((unsigned int) WChar[IndexToStartOfCopyLocation++]) * Multiplier))));
		Multiplier *= 256;
	}

    return(ReturnStatus);
} // CopyNumberFromString #1




//
//	CopyNumberFromString (overloaded version #2: unsigned short* output)
//		Copy unsigned short number from the local string to the caller specified unsigned short from the caller
//		specified index in the local string .  If there are not enough characters in the local
//		string, copy what there is, but return an error.  Otherwise, copy characters according
//		to the requested length or the size of unsigned short, whichever is smaller.  Note that numbers
//		are stored little endian.
//
bool HWSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned short *CopyDestination)
{
    bool        ReturnStatus;               //
	unsigned int		IndexToEndOfCopyLocation;	// Index to the position after the end of the copy string
	unsigned int		Multiplier;					// Multiplier (multiple of 256) to apply to next byte



	if(sizeof(unsigned short) < LengthToCopy)
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + sizeof(unsigned short);
	}
	else
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + LengthToCopy;
	}


	if(IndexToEndOfCopyLocation > Size)
	{
        ReturnStatus = false;
	}
	else
	{
        ReturnStatus = true;
	}


	Multiplier = 1;
	*CopyDestination = 0;

    while(IndexToStartOfCopyLocation < IndexToEndOfCopyLocation)
	{
//	    *CopyDestination += ((unsigned short) (((unsigned short) WChar[IndexToStartOfCopyLocation++]) * Multiplier));
    	if (wcSize == 2)
    		*CopyDestination = ((unsigned short) (*CopyDestination + ((unsigned short) (((unsigned short) WChar[IndexToStartOfCopyLocation++]) * Multiplier))));
    	else
    		*CopyDestination = ((unsigned short) (*CopyDestination + ((unsigned short) (((unsigned int) WChar[IndexToStartOfCopyLocation++]) * Multiplier))));
		Multiplier *= 256;
	}

    return(ReturnStatus);
} // CopyNumberFromString #2







//
//	CopyNumberFromString (overloaded version #3: unsigned int* output)
//		Copy unsigned int number from the local string to the caller specified unsigned int from the caller
//		specified index in the local string .  If there are not enough characters in the local
//		string, copy what there is, but return an error.  Otherwise, copy characters according
//		to the requested length or the size of unsigned int, whichever is smaller.  Note that numbers
//		are stored little endian.
//
bool HWSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned int *CopyDestination)
{
    bool        ReturnStatus;               //
	unsigned int		IndexToEndOfCopyLocation;	// Index to the position after the end of the copy string
	unsigned int		Multiplier;					// Multiplier (multiple of 256) to apply to next byte



	if(sizeof(unsigned int) < LengthToCopy)
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + sizeof(unsigned int);
	}
	else
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + LengthToCopy;
	}


	if(IndexToEndOfCopyLocation > Size)
	{
        ReturnStatus = false;
	}
	else
	{
        ReturnStatus = true;
	}


	Multiplier = 1;
	*CopyDestination = 0;

    while(IndexToStartOfCopyLocation < IndexToEndOfCopyLocation)
	{
	    *CopyDestination += ((unsigned int) (((unsigned int) WChar[IndexToStartOfCopyLocation++]) * Multiplier));
		Multiplier *= 256;
	}

    return(ReturnStatus);
} // CopyNumberFromString #3




//
//	CopyNumberFromString (overloaded version #4: int* output)
//		Copy int number from the local string to the caller specified int from the caller
//		specified index in the local string .  If there are not enough characters in the local
//		string, copy what there is, but return an error.  Otherwise, copy characters according
//		to the requested length or the size of int, whichever is smaller.  Note that numbers
//		are stored little endian.
//
bool HWSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   int *CopyDestination)
{
    bool        ReturnStatus;               //
	unsigned int		IndexToEndOfCopyLocation;	// Index to the position after the end of the copy string
	unsigned int		Multiplier;					// Multiplier (multiple of 256) to apply to next byte



	if(sizeof(int) < LengthToCopy)
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + sizeof(int);
	}
	else
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + LengthToCopy;
	}


	if(IndexToEndOfCopyLocation > Size)
	{
        ReturnStatus = false;
	}
	else
	{
        ReturnStatus = true;
	}


	Multiplier = 1;
	*CopyDestination = 0;

    while(IndexToStartOfCopyLocation < IndexToEndOfCopyLocation)
	{
	    *CopyDestination += ((int) (((int) WChar[IndexToStartOfCopyLocation++]) * Multiplier));
		Multiplier *= 256;
	}

    return(ReturnStatus);
} // CopyNumberFromString #4



//
//	CopyFromString (overloaded version #1: unsigned char* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, copy what there
//      is, but return an error.  Otherwise, copy characters according to the requested or maximum length,
//      whichever is smaller.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination,
										unsigned int MaximumDestinationLength)
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((wchar_t *) CopyDestination), MaximumDestinationLength));
}





//
//	CopyFromString (overloaded version #2: unsigned int* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.  Otherwise, copy characters according to the requested or maximum length, whichever is
//		smaller.
//		Call overloaded version #1 with a recast destination.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination,
										unsigned int MaximumDestinationLength)
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((wchar_t *) CopyDestination), MaximumDestinationLength));
}





//
//	CopyFromString (overloaded version #3: wchar_t* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.  Otherwise, copy characters according to the requested or maximum length, whichever is
//		smaller.
//		Call overloaded version #1 with a recast destination.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination,
										unsigned int MaximumDestinationLength)
{
    bool				ReturnStatus;               //
	unsigned int		IndexToEndOfCopyLocation;	// Index to the position after the end of the copy string



	if(MaximumDestinationLength < LengthToCopy)
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + MaximumDestinationLength;
	}
	else
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + LengthToCopy;
	}


	if(IndexToEndOfCopyLocation > Size)
	{
        ReturnStatus = false;
	}
	else
	{
        ReturnStatus = true;
	}


    while(IndexToStartOfCopyLocation < IndexToEndOfCopyLocation)
	{
	    *CopyDestination = WChar[IndexToStartOfCopyLocation++];
        CopyDestination++;
	}


    return(ReturnStatus);
}





//
//	CopyFromString (overloaded version #4: unsigned char* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination)
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, (wchar_t *) CopyDestination, LengthToCopy));
}





//
//	CopyFromString (overloaded version #5: unsigned int* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination)
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((wchar_t *) CopyDestination), LengthToCopy));
}





//
//	CopyFromString (overloaded version #6: wchar_t* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination)
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, CopyDestination, LengthToCopy));
}





//
//  CopyFromString (overloaded version #7: unsigned char* output with maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified maximum length, only copy up to the maximum length.  Return the number of unsigned chars
//      actually copied.
//
unsigned int HWSTRING::CopyFromString( unsigned char *CopyDestination, unsigned int MaximumDestinationLength)
{
	return CopyFromString( (wchar_t *) CopyDestination, MaximumDestinationLength );
}





//
//  CopyFromString (overloaded version #8: wchar_t* output with maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified maximum length, only copy up to the maximum length.  Return the number of unsigned chars
//      actually copied.
//
unsigned int HWSTRING::CopyFromString( wchar_t *CopyDestination, unsigned int MaximumDestinationLength)
{
	unsigned int		i;	// Index



    for(i=0; ((i < Size) && (i < MaximumDestinationLength)); ++i)
    {
        *CopyDestination = WChar[i];
        CopyDestination++;
    }

// Only append a trailing NULL if there is space for it
	if(i < MaximumDestinationLength)
	{
	    *CopyDestination = 0;
	}

	return(i);
}



//
//	CopyFromString (overloaded version #9: HWSTRING* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, copy what there
//      is.  Otherwise, copy characters according to the requested length.
//
bool HWSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, HWSTRING *CopyDestination)
{
    if((IndexToStartOfCopyLocation + LengthToCopy) > Size)
    {
        LengthToCopy = Size - IndexToStartOfCopyLocation;
    }

    return(CopyDestination->Copy(&WChar[IndexToStartOfCopyLocation], LengthToCopy));
}




//
//  CopyFromString (overloaded version #10: HWSTRING* output WITHOUT maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified HWSTRING allows, only copy up to the maximum length.  Return true is successful,
//      false if the string was too long.
//
bool HWSTRING::CopyFromString(HWSTRING *CopyDestination)
{
    return(CopyDestination->Copy(WChar, Size));
}




//
//	CopyFromStringLittleEndian (overloaded version #1: unsigned char* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, copy what there
//      is, but return an error.  Otherwise, copy characters according to the requested or maximum length,
//      whichever is smaller.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination,
										unsigned int MaximumDestinationLength)
{
    bool				ReturnStatus;               //
	unsigned int		IndexToEndOfCopyLocation;	// Index to the position after the end of the copy string



	if(MaximumDestinationLength < LengthToCopy)
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + MaximumDestinationLength;
	}
	else
	{
		IndexToEndOfCopyLocation = IndexToStartOfCopyLocation + LengthToCopy;
	}


	if(IndexToEndOfCopyLocation > Size)
	{
        ReturnStatus = false;
	}
	else
	{
        ReturnStatus = true;
	}


	while(IndexToStartOfCopyLocation < IndexToEndOfCopyLocation)
	{
		*CopyDestination = ((unsigned char) ( WChar[ IndexToStartOfCopyLocation ] & 0xFF ));
		CopyDestination++;
		*CopyDestination = ((unsigned char) ( ( WChar[ IndexToStartOfCopyLocation ] / 256 ) & 0xFF ));
		CopyDestination++;
		if (wcSize == 4)
		{
			*CopyDestination = ((unsigned char) ( ( WChar[ IndexToStartOfCopyLocation ] / (256*256) ) & 0xFF ));
			CopyDestination++;
			*CopyDestination = ((unsigned char) ( ( WChar[ IndexToStartOfCopyLocation ] / (256*256*256) ) & 0xFF ));
			CopyDestination++;

		}
		IndexToStartOfCopyLocation++;
	}
// Only append a trailing NULL if there is space for it
	if(LengthToCopy < MaximumDestinationLength)
	{
		if (wcSize == 4)
		{
		    *CopyDestination++ = 0;
		    *CopyDestination++ = 0;
		}
	    *CopyDestination++ = 0;
	    *CopyDestination = 0;
	}


    return(ReturnStatus);
}





//
//	CopyFromStringLittleEndian (overloaded version #2: unsigned int* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.  Otherwise, copy characters according to the requested or maximum length, whichever is
//		smaller.
//		Call overloaded version #1 with a recast destination.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination,
										unsigned int MaximumDestinationLength)
{
	return(CopyFromStringLittleEndian(IndexToStartOfCopyLocation, LengthToCopy, ((wchar_t *) CopyDestination), MaximumDestinationLength));
}





//
//	CopyFromStringLittleEndian (overloaded version #3: wchar_t* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.  Otherwise, copy characters according to the requested or maximum length, whichever is
//		smaller.
//		Call overloaded version #1 with a recast destination.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination,
										unsigned int MaximumDestinationLength)
{
	return(CopyFromStringLittleEndian(IndexToStartOfCopyLocation, LengthToCopy, ((unsigned char *) CopyDestination),
						MaximumDestinationLength));
}





//
//	CopyFromStringLittleEndian (overloaded version #4: unsigned char* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination)
{
	return(CopyFromStringLittleEndian(IndexToStartOfCopyLocation, LengthToCopy, (wchar_t *) CopyDestination, LengthToCopy));
}





//
//	CopyFromStringLittleEndian (overloaded version #5: unsigned int* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination)
{
	return(CopyFromStringLittleEndian(IndexToStartOfCopyLocation, LengthToCopy, ((wchar_t *) CopyDestination), LengthToCopy));
}





//
//	CopyFromStringLittleEndian (overloaded version #6: wchar_t* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination)
{
	return(CopyFromStringLittleEndian(IndexToStartOfCopyLocation, LengthToCopy, CopyDestination, LengthToCopy));
}





//
//  CopyFromStringLittleEndian (overloaded version #7: unsigned char* output with maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified maximum length, only copy up to the maximum length.  Return the number of unsigned chars
//      actually copied.
//
unsigned int HWSTRING::CopyFromStringLittleEndian( unsigned char *CopyDestination, unsigned int MaximumDestinationLength)
{
	unsigned int		i;	// Index


	for(i=0; ((i < Size) && (i < MaximumDestinationLength)); ++i)
	{
		*CopyDestination = ((unsigned char) ( WChar[ i ] & 0xFF ));
		CopyDestination++;
		*CopyDestination = ((unsigned char) ( ( WChar[ i ] / 256 ) & 0xFF ));
		CopyDestination++;
		if (wcSize == 4)
		{
			*CopyDestination = ((unsigned char) ( ( WChar[ i ] / (256*256) ) & 0xFF ));
			CopyDestination++;
			*CopyDestination = ((unsigned char) ( ( WChar[ i ] / (256*256*256) ) & 0xFF ));
			CopyDestination++;
		}
	}

// Only append a trailing NULL if there is space for it
	if(i < MaximumDestinationLength)
	{
		if (wcSize == 4)
		{
		    *CopyDestination++ = 0;
		    *CopyDestination++ = 0;
		}
	    *CopyDestination++ = 0;
	    *CopyDestination = 0;
	}

	return(i);
}





//
//  CopyFromStringLittleEndian (overloaded version #8: wchar_t* output with maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified maximum length, only copy up to the maximum length.  Return the number of unsigned chars
//      actually copied.
//
unsigned int HWSTRING::CopyFromStringLittleEndian( wchar_t *CopyDestination, unsigned int MaximumDestinationLength)
{
	return CopyFromStringLittleEndian( (unsigned char *) CopyDestination, MaximumDestinationLength );
}



//
//	CopyFromStringLittleEndian (overloaded version #9: HWSTRING* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, copy what there
//      is.  Otherwise, copy characters according to the requested length.
//
bool HWSTRING::CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, HWSTRING *CopyDestination)
{
    if((IndexToStartOfCopyLocation + LengthToCopy) > Size)
    {
        LengthToCopy = Size - IndexToStartOfCopyLocation;
    }

    return(CopyDestination->Copy(&WChar[IndexToStartOfCopyLocation], LengthToCopy));
}




//
//  CopyFromStringLittleEndian (overloaded version #10: HWSTRING* output WITHOUT maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified HWSTRING allows, only copy up to the maximum length.  Return true is successful,
//      false if the string was too long.
//
bool HWSTRING::CopyFromStringLittleEndian(HWSTRING *CopyDestination)
{
    return(CopyDestination->Copy(WChar, Size));
}





//
//  UnprintableCharactersToFormats
//      Convert each unprintable ASCII character in the local string to an unprintable
//      ASCII format string of the form '\XX', where XX is the 2 digit hexadecimal code
//      of the character.  Also, convert single '\' characters to two '\' characters.
//      Since the conversion will result in a larger string (each unprintable character
//      will now require four unsigned chars instead of one), return false if we ran out of room
//      and true otherwise.  If UseUnicodeHexadecimalFormatForCharacterConversion is true,
//		convert to '\uXXXX', where XXXX is the 4 digit hexadecimal code of the character.
//		If this is not true and UseXInHexadecimalFormat is true, we'll insert an 'x' between
//		the '\' and the two hexadecimal digits.
//
bool HWSTRING::UnprintableCharactersToFormats(void)
{
    bool	ReturnStatus;           // Indicates whether or not we ran out of room.
    unsigned int	i;                      // Indices
    unsigned int	j;
    wchar_t	CharacterToConvert;     // Holds unprintable character to be converted to format string
	wchar_t	Nibble;					// Printable hexadecimal character corresponding to next nibble
									//	of character being converted.



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

// Process all characters; quit if we run out of space.
    i = 0;
    while((i < Size) && (ReturnStatus))
    {
        if(WChar[i] == '\\')     // Convert single backslash to double backslash
        {
		   	SmartReallocate(Size + 1);

        // Shift everything from this point forward up by one unsigned char to make space for the extra backslash
            if((Size + 1) <= MaximumSize)           // Is there enough room for the new backslash?
            {
                for(j=Size; j > (i + 1); j--)     // Make space for the new backslash
                {
                    WChar[j] = WChar[j-1];
                }
                Size += 1;

                WChar[i++] = '\\';                   // Create the double backslash.
                WChar[i++] = '\\';                   // Create the double backslash.
            }

            else            // Not enough room; return with error.
            {
                ReturnStatus = false;
            }
        }
        else if((WChar[i] < 32) || (WChar[i] > 126))       // Unprintable character; convert it
        {
			int		NumberOfNewCharacters = ( UseUnicodeHexadecimalFormatForCharacterConversion ) ? 5 :
											( 2 + ( (UseXInHexadecimalFormat) ? 1 : 0 ) );
		   	SmartReallocate(Size + NumberOfNewCharacters);

        // Shift everything from this point forward up to make space for the format string
            if((Size + NumberOfNewCharacters) <= MaximumSize)           // Is there enough room for the new format string?
            {
                CharacterToConvert = WChar[i];       // Save the character to be converted

                for(j=Size+1; j > (i + NumberOfNewCharacters); j--)     // Make space for the format string
                {
                    WChar[j] = WChar[j-NumberOfNewCharacters];
                }
                Size += NumberOfNewCharacters;

                WChar[i++] = '\\';                   // Create the format string.
				if( UseUnicodeHexadecimalFormatForCharacterConversion )
				{
					WChar[i++] = 'u';
	                Nibble = ((wchar_t) (CharacterToConvert / 0x1000));
					Nibble &= 0x0F;
					WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
				    Nibble = ((wchar_t) (CharacterToConvert / 0x100));
					Nibble &= 0x0F;
					WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
				}
				else if( UseXInHexadecimalFormat )
				{
					WChar[i++] = 'x';
				}
                Nibble = ((wchar_t) (CharacterToConvert / 0x10));
				Nibble &= 0x0F;
				WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
                Nibble = ((wchar_t) (CharacterToConvert & 0x0F));
				WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
            }

            else            // Not enough room; return with error.
            {
                ReturnStatus = false;
            }
        }
        else        // Text character; leave it alone.
        {
            ++i;
        }
    }

    WChar[Size] = 0;

    return(ReturnStatus);
}






//
//  AllCharactersToFormats
//      Convert each ASCII character in the local string to an unprintable ASCII format
//		string of the form '\XX', where XX is the 2 digit hexadecimal code of the character.
//      Since the conversion will result in a larger string (each character will now require
//		four unsigned chars instead of one), return false if we ran out of room and true otherwise.
//      If UseUnicodeHexadecimalFormatForCharacterConversion is true, convert to '\uXXXX', where
//		XXXX is the 4 digit hexadecimal code of the character.  If this is not true and
//		UseXInHexadecimalFormat is true, we'll insert an 'x' between the '\' and the two
//		hexadecimal digits.
//
bool HWSTRING::AllCharactersToFormats(void)
{
    bool	ReturnStatus;           // Indicates whether or not we ran out of room.
    unsigned int	i;                      // Indices
    unsigned int	j;
    wchar_t	CharacterToConvert;     // Holds character to be converted to format string
	wchar_t	Nibble;					// Printable hexadecimal character corresponding to next nibble
									//	of character being converted.



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

// Process all characters; quit if we run out of space.
    i = 0;
    while((i < Size) && (ReturnStatus))
    {
		int		NumberOfNewCharacters = ( UseUnicodeHexadecimalFormatForCharacterConversion ) ? 5 :
											( 2 + ( (UseXInHexadecimalFormat) ? 1 : 0 ) );
	   	SmartReallocate(Size + NumberOfNewCharacters);

    // Shift everything from this point forward up to make space for the format string
        if((Size + NumberOfNewCharacters) <= MaximumSize)           // Is there enough room for the new format string?
        {
            CharacterToConvert = WChar[i];       // Save the character to be converted

            for(j=Size+1; j > (i + NumberOfNewCharacters); j--)     // Make space for the format string
            {
                WChar[j] = WChar[j-NumberOfNewCharacters];
            }
            Size += NumberOfNewCharacters;

            WChar[i++] = '\\';                   // Create the format string.
			if( UseUnicodeHexadecimalFormatForCharacterConversion )
			{
				WChar[i++] = 'u';
                Nibble = ((wchar_t) (CharacterToConvert / 0x1000));
				Nibble &= 0x0F;
				WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
			    Nibble = ((wchar_t) (CharacterToConvert / 0x100));
				Nibble &= 0x0F;
				WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
			}
			else if( UseXInHexadecimalFormat )
			{
				WChar[i++] = 'x';
			}
			Nibble = ((wchar_t) (CharacterToConvert / 0x10));
			Nibble &= 0x0F;
			WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
			Nibble = ((wchar_t) (CharacterToConvert & 0x0F));
			WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
       }

        else            // Not enough room; return with error.
        {
        	ReturnStatus = false;
        }
    }

    WChar[Size] = 0;

    return(ReturnStatus);
}






//
//  UnprintableFormatsToCharacters
//      Convert each unprintable ASCII format string in the form of "\XX", "\xXX", or "\uXXXX"
//      back to an unprintable ASCII character, where XX is the hexadecimal code of a value.
//      Also, two "\" in a row will be treated as one "\".
//
//      Using the same string for output as input works here, because the output
//      will never be longer than the input.
//
//      Return true if all format strings converted OK; false otherwise
//
bool HWSTRING::UnprintableFormatsToCharacters(void)
{
    bool			ReturnStatus;	// Indicates whether or not we ran out of room.
    unsigned int    DecodedValue;   // Holds unprintable characters as they're decoded;
    unsigned int    NumberOfDigits;	// Number of digits in hexadecimal representation (2 by default, unless we see a 'u').
    unsigned int    i;              // Indices
    unsigned int    j;
    unsigned int    k;



	NumberOfDigits = 2;

// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't encountered a bad format string yet.

    i = 0;          // Point to the next character to be processed.
    j = 0;          // Point to the next character position to fill.


// Keep going as long as there are more characters to process and no errors have occurred.
    while((i < Size) && (ReturnStatus))
    {
        if(WChar[i] != '\\')              // If the next character is not a '\', copy it.
        {
            WChar[j++] = WChar[i++];
        }
        else                                // Next character is '\', so start decoding.
        {
            ++i;
            if(i < Size)
            {
                if(WChar[i] == '\\')      // If next character is also '\', then copy one '\' to output
                {
                    WChar[j++] = WChar[i++];
                }
                else                        // Next character wasn't '\', so it better be a number.
                {
					if(( i < Size ) && (( WChar[i] == 'x' ) || ( WChar[i] == 'X' )))
					{
					// Remove an 'x' character.
						++i;
					}
					else if(( i < Size ) && (( WChar[i] == 'u' ) || ( WChar[i] == 'U' )))
					{
					// Remove an 'u' character and indicate that we're looking for four digits.
						NumberOfDigits = 4;
						++i;
					}
                    DecodedValue = 0;       // The next two characters had better be a hexadecimal number.
                    k = 0;
                    while((k < NumberOfDigits) && (i < Size) &&
                            (((WChar[i] >= '0') && (WChar[i] <= '9')) ||
                             ((WChar[i] >= 'A') && (WChar[i] <= 'F')) ||
                             ((WChar[i] >= 'a') && (WChar[i] <= 'f'))))
                    {
                        DecodedValue *= 0x10;
                        DecodedValue += (WChar[i] <= '9') ? (((unsigned int) WChar[i]) - '0') :
								(((unsigned int) (WChar[i] & 0xDF)) - 'A' + 10);
						++i;
                        ++k;
                    }

                    if(k < NumberOfDigits)			// If we didn't get the required number of digits, flag an error.
                    {
                        ReturnStatus = false;
                    }
                    else if(DecodedValue > 65535)     // If two digits were found, but the number is too large, flag an error.
                    {
                        ReturnStatus = false;
                    }
                    else                            // Number decode was successful; copy it as a character to output position.
                    {
                        WChar[j++] = ((wchar_t) DecodedValue);
                    }
                }
            }
            else                // We ran out of string before completing a control code; flag an error!
            {
                ReturnStatus = false;
            }
        }
    }

    Size = j;       // Reflect new string size

    WChar[Size] = 0;

    return ReturnStatus;
}
//---------------------------------------------------------------------------






//
//  BinaryToHex
//      Convert each ASCII character in the local string to a formatted two byte HEX representation.
//
bool HWSTRING::BinaryToHex(void)
{
    bool	ReturnStatus;           // Indicates whether or not we ran out of room.
    unsigned int	i;                      // Indices
    unsigned int	j;
    wchar_t	CharacterToConvert;     // Holds unprintable character to be converted to format string
	wchar_t	Nibble;					// Printable hexadecimal character corresponding to next nibble
									//	of character being converted.



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

// Process all characters; quit if we run out of space.
    i = 0;
    while((i < Size) && (ReturnStatus))
    {
		int		NumberOfNewCharacters = ( UseUnicodeHexadecimalFormatForCharacterConversion ) ? 3 : 1;
	   	SmartReallocate(Size + NumberOfNewCharacters);

	// Shift everything from this point forward up to make space for the format string
		if((Size + NumberOfNewCharacters) <= MaximumSize)           // Is there enough room for the new format string?
        {
			CharacterToConvert = WChar[i];       // Save the character to be converted

			for(j=Size; j > (i + NumberOfNewCharacters); j--)     // Make space for the format string
			{
				WChar[j] = WChar[j-NumberOfNewCharacters];
			}
			Size += NumberOfNewCharacters;

			if( UseUnicodeHexadecimalFormatForCharacterConversion )
			{
                Nibble = ((wchar_t) (CharacterToConvert / 0x1000));
				Nibble &= 0x0F;
				WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
			    Nibble = ((wchar_t) (CharacterToConvert / 0x100));
				Nibble &= 0x0F;
				WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
			}
			Nibble = ((wchar_t) (CharacterToConvert / 0x10));
			Nibble &= 0x0F;
			WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
			Nibble = ((wchar_t) (CharacterToConvert & 0x0F));
			WChar[i++] = ((wchar_t) ((Nibble > 9) ? (Nibble + 'A' - 10) : (Nibble + '0')));
		}

		else            // Not enough room; return with error.
		{
			ReturnStatus = false;
		}
    }

    WChar[Size] = 0;

    return(ReturnStatus);
}






//
//  HexToBinary
//      Convert each formatted HEX character representation in the local string to the ASCII equivalent value.
//
bool HWSTRING::HexToBinary(void)
{
    bool			ReturnStatus;	// Indicates whether or not we ran out of room.
    unsigned int    DecodedValue;   // Holds unprintable characters as they're decoded;
    unsigned int    NumberOfDigits;	// Number of digits in hexadecimal representation (2 by default, unless using Unicode format).
    unsigned int    i;              // Indices
    unsigned int    j;
    unsigned int    k;



	if( UseUnicodeHexadecimalFormatForCharacterConversion )
	{
		NumberOfDigits = 4;
	}
	else
	{
		NumberOfDigits = 2;
	}

// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't encountered a bad format string yet.

    i = 0;          // Point to the next character to be processed.
    j = 0;          // Point to the next character position to fill.


// Keep going as long as there are more characters to process and no errors have occurred.
	while((i < Size) && (ReturnStatus))
	{
		DecodedValue = 0;       // The next characters had better be a hexadecimal number.
		k = 0;
		while((k < NumberOfDigits) && (i < Size) &&
                            (((WChar[i] >= '0') && (WChar[i] <= '9')) ||
                             ((WChar[i] >= 'A') && (WChar[i] <= 'F')) ||
                             ((WChar[i] >= 'a') && (WChar[i] <= 'f'))))
		{
			DecodedValue *= 0x10;
			DecodedValue += (WChar[i] <= '9') ? (((unsigned int) WChar[i]) - '0') :
								(((unsigned int) (WChar[i] & 0xDF)) - 'A' + 10);
			++i;
			++k;
		}

		if((k < NumberOfDigits) && (i < Size))		// If less than the expected number of digits were found, flag an error.
		{
			ReturnStatus = false;
		}
		else if(DecodedValue > 65535)     // If digits were found, but the number is too large, flag an error.
		{
			ReturnStatus = false;
		}
		else                            // Number decode was successful; copy it as a character to output position.
		{
			WChar[j++] = ((wchar_t) DecodedValue);
		}
	}

    Size = j;       // Reflect new string size

    WChar[Size] = 0;

    return ReturnStatus;
}
//---------------------------------------------------------------------------






//
//  QuotedHEXStringToBinary
//      Convert each formatted HEX character representation in the local string to the ASCII equivalent value.
//		Any characters between quotes will not be translated as HEX characters, but will be stored directly into the
//		local string.
//
bool HWSTRING::QuotedHEXStringToBinary(bool *IncompleteString)
{
    bool			ReturnStatus;	// Indicates whether or not we ran out of room.
    unsigned int    DecodedValue;   // Holds unprintable characters as they're decoded;
    unsigned int    NumberOfDigits;	// Number of digits in hexadecimal representation (2 by default, unless using Unicode format).
    unsigned int    i;              // Indices
    unsigned int    j;
    unsigned int    k;
	bool			InsideQuotes;	// Indicate when we're supposed to be looking for character data rather than
									//	HEX data.
	bool			ProcessingIncomplete;	// Indicate when we ran out of string before we found a closing quote or the
											//	second nibble of a HEX character.



	if( UseUnicodeHexadecimalFormatForCharacterConversion )
	{
		NumberOfDigits = 4;
	}
	else
	{
		NumberOfDigits = 2;
	}

// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;			// We haven't encountered a bad format string yet.
	ProcessingIncomplete = false;

    i = 0;          // Point to the next character to be processed.
    j = 0;          // Point to the next character position to fill.
	InsideQuotes = false;


// Keep going as long as there are more characters to process and no errors have occurred.
	while((i < Size) && (ReturnStatus))
	{
		if( WChar[i] == '"' )
		{
			InsideQuotes = !InsideQuotes;
			++i;
		}

		else if( InsideQuotes )
		{
			WChar[ j++ ] = WChar [ i++ ];
		}

		else
		{
			DecodedValue = 0;       // The next characters had better be a hexadecimal number.
			k = 0;
			while((k < NumberOfDigits) && (i < Size) &&
                            (((WChar[i] >= '0') && (WChar[i] <= '9')) ||
                             ((WChar[i] >= 'A') && (WChar[i] <= 'F')) ||
                             ((WChar[i] >= 'a') && (WChar[i] <= 'f'))))
			{
				DecodedValue *= 0x10;
				DecodedValue += (WChar[i] <= '9') ? (((unsigned int) WChar[i]) - '0') :
								(((unsigned int) (WChar[i] & 0xDF)) - 'A' + 10);
				++i;
				++k;
			}

			if((k < NumberOfDigits) && (i < Size))		// If less than the required digits were found, flag an error.
			{
				ReturnStatus = false;
			}
			else if(DecodedValue > 65535)     // If digits were found, but the number is too large, flag an error.
			{
				ReturnStatus = false;
			}
			else                            // Number decode was successful; copy it as a character to output position.
			{
				WChar[j++] = ((unsigned char) DecodedValue);

				if(( k < NumberOfDigits ) && ( i == Size ))		// Indicate that we didn't get all nibbles.
				{
					ProcessingIncomplete = true;
				}
			}
		}
	}

    Size = j;       // Reflect new string size

    WChar[Size] = 0;

	if( InsideQuotes )
		ProcessingIncomplete = true;

	if( IncompleteString != NULL )
		*IncompleteString = ProcessingIncomplete;

    return ReturnStatus;
} // QuotedHEXStringToBinary
//---------------------------------------------------------------------------




// Remove characters from the string within the requested index range.
bool HWSTRING::Remove(unsigned int StartingIndexOfCharactersToBeRemoved, unsigned int NumberOfCharactersToBeRemoved)
{
    bool        ReturnStatus;
	unsigned int		NextReadPosition;			// Next place to read data from above the area being squeezed out
	unsigned int		NextWritePosition;			// Next place to copy data being preserved as we're squeezing out
    										//	the requested data



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// If trying to remove non-existent characters, woof!
	if((StartingIndexOfCharactersToBeRemoved + NumberOfCharactersToBeRemoved) > Size)
	{
    	ReturnStatus = false;
	}

	else
	{
    // Squeeze out characters in the specified range.
    	NextWritePosition = StartingIndexOfCharactersToBeRemoved;
    	NextReadPosition =
        		StartingIndexOfCharactersToBeRemoved + NumberOfCharactersToBeRemoved;
        while(NextReadPosition < Size)
        {
        	WChar[NextWritePosition++] = WChar[NextReadPosition++];
        }

        Size = NextWritePosition;

        WChar[Size] = 0;

    	ReturnStatus = true;
	}

    return(ReturnStatus);
}
//---------------------------------------------------------------------------




//
//	Move
//		Move characters from the one location to another within the string.
//
bool HWSTRING::Move(unsigned int StartingIndexOfCharactersToBeMoved, unsigned int LocationToMoveTo,
													unsigned int NumberOfCharactersToBeMoved)
{
    bool        ReturnStatus;
    unsigned int		i;
	unsigned int		NextReadPosition;			// Next place to read data from above the area being squeeze out
	unsigned int		NextWritePosition;			// Next place to copy data being preserved as we're squeezing out
    										//	the requested data




// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// If trying to remove non-existent characters, woof!
	if(((StartingIndexOfCharactersToBeMoved + NumberOfCharactersToBeMoved) > Size) ||
					((LocationToMoveTo + NumberOfCharactersToBeMoved) > Size))
	{
    	ReturnStatus = false;
	}

// If caller told us to copy zero characters, return good status.
    else if(NumberOfCharactersToBeMoved < 1)
    {
    	ReturnStatus = true;
    }

	else
	{
    // Copy the code to be moved to a buffer.
    	wchar_t *MoveBuffer = new wchar_t[NumberOfCharactersToBeMoved];
        for(i = 0;    i < NumberOfCharactersToBeMoved;    ++i)
        {
            MoveBuffer[i] = WChar[StartingIndexOfCharactersToBeMoved + i];
        }

    // Shift data around to make room for the data that's moving.  There are two cases to be
    // handled:
    //		1) If the shifted direction is downward, then some preceding data must be moved above
    //			where the shifted data will be.
    //		2) If the shifted direction is upward, then some succeeding data must be moved below
    //			where the shifted data will be.
		if(StartingIndexOfCharactersToBeMoved >= LocationToMoveTo)
        {
        // Shift downward
			NextReadPosition = StartingIndexOfCharactersToBeMoved;
			NextWritePosition = StartingIndexOfCharactersToBeMoved + NumberOfCharactersToBeMoved;

            while(NextReadPosition != LocationToMoveTo)
            {
            	WChar[--NextWritePosition] = WChar[--NextReadPosition];
            }
        }
		else
        {
        // Shift upward
			NextReadPosition = StartingIndexOfCharactersToBeMoved + NumberOfCharactersToBeMoved;
			NextWritePosition = StartingIndexOfCharactersToBeMoved;
            while(NextWritePosition < LocationToMoveTo)
            {
            	WChar[NextWritePosition++] = WChar[NextReadPosition++];
            }
        }

    // Move the data being shifted to its' final destination.
        for(i = 0;    i < NumberOfCharactersToBeMoved;    ++i)
        {
            WChar[LocationToMoveTo + i] = MoveBuffer[i];
        }

        delete [] MoveBuffer;

        WChar[Size] = 0;

    	ReturnStatus = true;
	}

    return(ReturnStatus);
}
//---------------------------------------------------------------------------




// Remove all <CR>s, <LF>s, tabs, spaces, and nulls (overloaded version #1).
bool HWSTRING::RemoveSpaceCharacters(void)
{
	bool	SpaceCharactersWereFoundAndRemoved;
	unsigned int	NextLocationToRead;
	unsigned int	NextLocationToWrite;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	SpaceCharactersWereFoundAndRemoved = false;		// None found yet.

	NextLocationToWrite = 0;
    for(NextLocationToRead = 0;    NextLocationToRead < Size;    ++NextLocationToRead)
    {
    	if((WChar[NextLocationToRead] == ' ') || (WChar[NextLocationToRead] == 9) || (WChar[NextLocationToRead] == 0) ||
	    	 (WChar[NextLocationToRead] == 13) || (WChar[NextLocationToRead] == 10))
        {
			SpaceCharactersWereFoundAndRemoved = true;
        }
        else
        {
        	WChar[NextLocationToWrite++] = WChar[NextLocationToRead];
        }
    }

// Store the new size.
    Size = NextLocationToWrite;

    WChar[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}



// Remove all <CR>s, <LF>s, tabs, spaces, and nulls up to caller specified character (overloaded version #2).
bool HWSTRING::RemoveSpaceCharacters(int CharacterToRemoveUpTo)
{
	bool	SpaceCharactersWereFoundAndRemoved;
	unsigned int	NextLocationToRead;
	unsigned int	NextLocationToWrite;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	SpaceCharactersWereFoundAndRemoved = false;		// None found yet.

	NextLocationToWrite = 0;
    for(NextLocationToRead = 0;
			    		(NextLocationToRead < Size) && (WChar[NextLocationToRead] != CharacterToRemoveUpTo);
    										    ++NextLocationToRead)
    {
    	if((WChar[NextLocationToRead] == ' ') || (WChar[NextLocationToRead] == 9) || (WChar[NextLocationToRead] == 0) ||
	    	 (WChar[NextLocationToRead] == 13) || (WChar[NextLocationToRead] == 10))
        {
			SpaceCharactersWereFoundAndRemoved = true;
        }
        else
        {
        	WChar[NextLocationToWrite++] = WChar[NextLocationToRead];
        }
    }

// In case we quit because of reaching CharacterToRemoveUpTo, continue shifting the remainder of the string.
    while(NextLocationToRead < Size)
    {
    	WChar[NextLocationToWrite++] = WChar[NextLocationToRead++];
    }

// Store the new size.
    Size = NextLocationToWrite;

    WChar[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}





// Remove all leading <CR>s, <LF>s, tabs, spaces, and nulls.
bool HWSTRING::RemoveLeadingSpaceCharacters(void)
{
	bool	SpaceCharactersWereFoundAndRemoved;
	unsigned int	NextLocationToRead;
	unsigned int	NextLocationToWrite;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	SpaceCharactersWereFoundAndRemoved = false;		// None found yet.

    NextLocationToRead = 0;
    while((NextLocationToRead < Size) &&
    	((WChar[NextLocationToRead] == ' ') || (WChar[NextLocationToRead] == 9) || (WChar[NextLocationToRead] == 0) ||
	    	 (WChar[NextLocationToRead] == 13) || (WChar[NextLocationToRead] == 10)))
    {
    	SpaceCharactersWereFoundAndRemoved = true;
	    ++NextLocationToRead;
    }


// Shift the remainder of the string.
	NextLocationToWrite = 0;
    while(NextLocationToRead < Size)
    {
    	WChar[NextLocationToWrite++] = WChar[NextLocationToRead++];
    }

// Store the new size.
    Size = NextLocationToWrite;

    WChar[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}





// Remove all trailing <CR>s, <LF>s, tabs, spaces, and nulls.
bool HWSTRING::RemoveTrailingSpaceCharacters(void)
{
	bool	SpaceCharactersWereFoundAndRemoved;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	SpaceCharactersWereFoundAndRemoved = false;		// None found yet.

    while((Size > 0) &&
    	((WChar[ Size - 1 ] == ' ') || (WChar[ Size - 1 ] == 9) || (WChar[ Size - 1 ] == 0) ||
	    	 (WChar[ Size - 1 ] == 13) || (WChar[ Size - 1 ] == 10)))
    {
    	SpaceCharactersWereFoundAndRemoved = true;
	    --Size;
    }

    WChar[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}






//
//	CompareSubstring (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HWSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareSubstring(unsigned int LocalStringIndex, const wchar_t *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive)
{
	int		StringComparisonResult;
    unsigned int	i;
    wchar_t	LocalChar;
    wchar_t	InputChar;


// If local string index, input string size, and local string size all equal zero, return zero to indicate
// equality.
	if((LocalStringIndex == 0) && (Size == 0) && (InputStringLength == 0))
    {
	    StringComparisonResult = 0;
    }

// Else if the local string index is past the end of the local string, return 1 to indicate that input string
// is larger
	else if(LocalStringIndex >= Size)
    {
	    StringComparisonResult = 1;
    }

// Else if the local string size is zero, return 1 to indicate that input string is larger
	else if(Size == 0)
    {
	    StringComparisonResult = 1;
    }

// Else if the input string size is zero, return -1 to indicate that local string is larger
	else if(InputStringLength == 0)
    {
	    StringComparisonResult = -1;
    }

// Else if there are less characters in the local string than in the input string, return 1 to
// indicate that input string is larger.
	else if(InputStringLength > (Size - LocalStringIndex))
	{
	    StringComparisonResult = 1;
	}


// Else we have one or more characters to compare.
	else
    {
	// Compare the strings according to the input length.
		if(CompareIsCaseSensitive)
	    {
//			StringComparisonResult = wcsncpy( InputString, &WChar[LocalStringIndex], InputStringLength);
    		StringComparisonResult = 0;

	    // Do case sensitive compare.
    		for(i = 0;    (i < InputStringLength) && (StringComparisonResult == 0);    ++i)
        	{
	        	LocalChar = ((wchar_t) WChar[i + LocalStringIndex]);
        		InputChar = ((wchar_t) InputString[i]);
        		if(InputChar < LocalChar)
	            {
		    		StringComparisonResult = -1;
    	        }
        		else if(InputChar > LocalChar)
            	{
		    		StringComparisonResult = 1;
                }
            }
    	}
	    else
    	{
    		StringComparisonResult = 0;

	    // Embedded may not have strnicmp; we'll have to do it.
    		for(i = 0;    (i < InputStringLength) && (StringComparisonResult == 0);    ++i)
        	{
	        	LocalChar = ((wchar_t) (((WChar[i + LocalStringIndex] >= 97) && (WChar[i + LocalStringIndex] <= 122)) ?
                				WChar[i + LocalStringIndex] & 0xdf : WChar[i + LocalStringIndex]));
        		InputChar = ((wchar_t) (((InputString[i] >= 97) && (InputString[i] <= 122)) ?
                        		InputString[i] & 0xdf : InputString[i]));
        		if(InputChar < LocalChar)
	            {
		    		StringComparisonResult = -1;
    	        }
        		else if(InputChar > LocalChar)
            	{
		    		StringComparisonResult = 1;
                }
            }
        }
    }

	return(StringComparisonResult);
}






//
//	CompareSubstring (overloaded version #2, where starting index into the local string is assumed to be zero)
//		Compare the input string to the local HWSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareSubstring(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(0L, InputString, InputStringLength, CompareIsCaseSensitive));
}






//
//	CompareSubstring (overloaded version #3, with a starting index into the local string and a
//		char * argument)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareSubstring(unsigned int LocalStringIndex, HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(LocalStringIndex, InputString->WChar, InputString->Size,
																	CompareIsCaseSensitive));
}





//	CompareSubstring (overloaded version #4, where starting index into the local string is assumed to be zero
//		and a char * argument)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareSubstring(HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(0L, InputString->WChar, InputString->Size, CompareIsCaseSensitive));
}





//
//	CompareOnShorter (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareOnShorter(unsigned int LocalStringIndex, const wchar_t *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive)
{
	unsigned int	ShortestInputStringLength;
	int		StringComparisonResult;
    unsigned int	i;
    wchar_t	LocalChar;
    wchar_t	InputChar;


// If local string index, input string size, and local string size all equal zero, return zero to indicate
// equality.
	if((LocalStringIndex == 0) && (Size == 0) && (InputStringLength == 0))
    {
	    StringComparisonResult = 0;
    }

// Else if the local string index is past the end of the local string, return 1 to indicate that input string
// is larger
	else if(LocalStringIndex >= Size)
    {
	    StringComparisonResult = 1;
    }

// Else if the local string size is zero, return 1 to indicate that input string is larger
	else if(Size == 0)
    {
	    StringComparisonResult = 1;
    }

// Else if the input string size is zero, return -1 to indicate that local string is larger
	else if(InputStringLength == 0)
    {
	    StringComparisonResult = -1;
    }

// Else we have one or more characters to compare.
	else
    {
	// Find the shortest length
		if(InputStringLength < (Size - LocalStringIndex))
		{
			ShortestInputStringLength = InputStringLength;
		}
		else
		{
			ShortestInputStringLength = Size - LocalStringIndex;
		}

	// Compare the strings according to the shorter length.  If equal, then we'll have to check to see if one string
	// is longer than the other.
		if(CompareIsCaseSensitive)
	    {
//			StringComparisonResult = wcsncpy( InputString, &WChar[LocalStringIndex], ShortestInputStringLength);
    		StringComparisonResult = 0;

	    // Do case sensitive compare.
    		for(i = 0;    (i < ShortestInputStringLength) && (StringComparisonResult == 0);    ++i)
        	{
	        	LocalChar = ((wchar_t) WChar[i + LocalStringIndex]);
        		InputChar = ((wchar_t) InputString[i]);
        		if(InputChar < LocalChar)
	            {
		    		StringComparisonResult = -1;
    	        }
        		else if(InputChar > LocalChar)
            	{
		    		StringComparisonResult = 1;
                }
            }
    	}
	    else
    	{
    		StringComparisonResult = 0;

	    // Embedded may not have strnicmp; we'll have to do it.
    		for(i = 0;    (i < ShortestInputStringLength) && (StringComparisonResult == 0);    ++i)
        	{
	        	LocalChar = ((wchar_t) (((WChar[i + LocalStringIndex] >= 97) && (WChar[i + LocalStringIndex] <= 122)) ?
                				WChar[i + LocalStringIndex] & 0xdf : WChar[i + LocalStringIndex]));
        		InputChar = ((wchar_t) (((InputString[i] >= 97) && (InputString[i] <= 122)) ?
                        		InputString[i] & 0xdf : InputString[i]));
        		if(InputChar < LocalChar)
	            {
		    		StringComparisonResult = -1;
    	        }
        		else if(InputChar > LocalChar)
            	{
		    		StringComparisonResult = 1;
                }
            }
        }
    }

	return(StringComparisonResult);
}






//
//	CompareOnShorter (overloaded version #2, where starting index into the local string is assumed to be zero)
//		Compare the input string to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareOnShorter(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	return(CompareOnShorter(0L, InputString, InputStringLength, CompareIsCaseSensitive));
}





//
//	CompareOnShorter (overloaded version #3, with a starting index into the local string)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareOnShorter(unsigned int LocalStringIndex, HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareOnShorter(LocalStringIndex, InputString->WChar, InputString->Size, CompareIsCaseSensitive));
}






//
//	CompareOnShorter (overloaded version 4, where starting index into the local string is assumed to be zero)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.
//
int HWSTRING::CompareOnShorter(HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareOnShorter(0L, InputString->WChar, InputString->Size, CompareIsCaseSensitive));
}






//
//  Compare (overloaded version #1 with wchar_t* input and specified length).
//		Compare the input string to the local HWSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HWSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HWSTRING, then the result will be -1.
//
int HWSTRING::Compare(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	int		StringComparisonResult;


// Compare the strings according to the shorter length.  If equal, then we'll have to check to see if one string
// is longer than the other.
	StringComparisonResult = CompareOnShorter(InputString, InputStringLength, CompareIsCaseSensitive);

// If strings are equal up to the smaller of the two strings, then compute result based on string length.
	if(StringComparisonResult == 0)
	{
		if(InputStringLength < Size)
		{
			StringComparisonResult = -1;
		}
		if(InputStringLength > Size)
		{
			StringComparisonResult = 1;
		}
	}

	return(StringComparisonResult);
}






//
//  Compare (overloaded version #2 with HWSTRING* input).
//		Compare the input string to the local HWSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HWSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HWSTRING, then the result will be -1.
//
int HWSTRING::Compare(HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(Compare(InputString->WChar, InputString->Size, CompareIsCaseSensitive));
}




//
//  Compare (overloaded version #3 with unsigned char* input).
//		Compare the input string to the local HWSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HWSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HWSTRING, then the result will be -1.
//
int HWSTRING::Compare(const wchar_t *InputString, bool CompareIsCaseSensitive)
{
	return(Compare(InputString, ((unsigned int) wcslen( InputString )), CompareIsCaseSensitive));
}





//
//	Compare the input string to the local HWSTRING up to the input length (overloaded version #1 with unsigned char* input
//	and specified length).
//		Compare the input string to the local HWSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HWSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HWSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HWSTRING::CompareFixedInputLength(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	int		StringComparisonResult;


// Compare the strings according to the shorter length.  If equal, then we'll have to check to see if one string
// is longer than the other.
	StringComparisonResult = CompareOnShorter(InputString, InputStringLength, CompareIsCaseSensitive);

// If strings are equal up to the smaller of the two strings, then compute result based on string length.
	if(StringComparisonResult == 0)
	{
		if(InputStringLength > Size)
		{
			StringComparisonResult = 1;
		}
	}

	return(StringComparisonResult);
}




//
//	Compare the input string to the local HWSTRING up to the length of the input HWSTRING (overloaded version #2
//	with HWSTRING* input).
//		Compare the input string to the local HWSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HWSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HWSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HWSTRING::CompareFixedInputLength(HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareFixedInputLength(InputString->WChar, InputString->Size, CompareIsCaseSensitive));
}




//
//	Compare the input string to the local HWSTRING up to the length of the input unsigned char string (overloaded
//	version #3 with unsigned char* input).
//		Compare the input string to the local HWSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HWSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HWSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HWSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HWSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HWSTRING::CompareFixedInputLength(const wchar_t *InputString, bool CompareIsCaseSensitive)
{
	return(CompareFixedInputLength(InputString, ((unsigned int) wcslen( InputString )), CompareIsCaseSensitive));
}





//
// FindString (overloaded version #1 with a unsigned char input string).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HWSTRING::FindString(const wchar_t *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound)
{
	int		NextOccurrenceNumber;	// Next occurrence to search for
    bool	Status;					// Set to true when the caller specified occurrence of the input string
    								//	is found
    int		NumberOfPositionsYetToBeSearched;


	Status = false;					// Nothing found yet.
    NextOccurrenceNumber = 1;		// Start with first occurrence.

// The size of the search string must at least as big as the local string.
	if(InputStringLength >= Size)
    {
	    NumberOfPositionsYetToBeSearched = InputStringLength - Size + 1;

	// Are we searching forward?
	// Note: if occurrence number to search for is zero, return without success.
		if(OccurrenceNumberToFindOfInputString > 0)
	    {
			*PositionWhereInputStringWasFound = 0;

        // Keep looking until we reach the end of the string or we find the nth occurrence
            while((!Status) && (NumberOfPositionsYetToBeSearched > 0))
            {
            	if(CompareOnShorter(&InputString[*PositionWhereInputStringWasFound],
                		(InputStringLength - *PositionWhereInputStringWasFound), FindIsCaseSensitive) == 0)
                {
					if(NextOccurrenceNumber >= OccurrenceNumberToFindOfInputString)
                    {
                    	Status = true;
                    }
                    else
                    {
                    	NumberOfPositionsYetToBeSearched -= ((int) (Size));
					    ++NextOccurrenceNumber;
	    		    	*PositionWhereInputStringWasFound += Size;
                    }
                }
                else
                {
                	--NumberOfPositionsYetToBeSearched;
	        		++(*PositionWhereInputStringWasFound);
                }
            }
    	}

	// Are we searching backward?
		else if(OccurrenceNumberToFindOfInputString < 0)
	    {
        	OccurrenceNumberToFindOfInputString = -OccurrenceNumberToFindOfInputString;

			*PositionWhereInputStringWasFound = InputStringLength - Size;

        // Keep looking until we reach the beginning of the string or we find the nth occurrence
            while((!Status) && (NumberOfPositionsYetToBeSearched > 0))
            {
            	if(CompareOnShorter(&InputString[*PositionWhereInputStringWasFound],
                		(InputStringLength - *PositionWhereInputStringWasFound), FindIsCaseSensitive) == 0)
                {
					if(NextOccurrenceNumber >= OccurrenceNumberToFindOfInputString)
                    {
                    	Status = true;
                    }
                    else
                    {
                    	NumberOfPositionsYetToBeSearched -= ((int) (Size));
					    ++NextOccurrenceNumber;
	    		    	*PositionWhereInputStringWasFound -= Size;
                    }
                }
                else
                {
                	--NumberOfPositionsYetToBeSearched;
	        		--(*PositionWhereInputStringWasFound);
                }
            }
    	}
    }

    return(Status);
}





//
// FindString (overloaded version #2 with an input HWSTRING).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HWSTRING::FindString(HWSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound)
{
	return(FindString(InputString->WChar, InputString->Size, FindIsCaseSensitive,
                				OccurrenceNumberToFindOfInputString, PositionWhereInputStringWasFound));
}





//
// Find (overloaded version #1 with a unsigned char input string).
//		Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HWSTRING::Find(const wchar_t *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound)
{
	int		NextOccurrenceNumber;	// Next occurrence to search for
    bool	Status;					// Set to true when the caller specified occurrence of the input string
    								//	is found
    int		NumberOfPositionsYetToBeSearched;


	Status = false;					// Nothing found yet.
    NextOccurrenceNumber = 1;		// Start with first occurrence.

// The size of the search string must not be bigger than the local string.
	if(InputStringLength <= Size)
    {
	    NumberOfPositionsYetToBeSearched = Size - InputStringLength + 1;

	// Are we searching forward?
	// Note: if occurrence number to search for is zero, return without success.
		if(OccurrenceNumberToFindOfInputString > 0)
	    {
			*PositionWhereInputStringWasFound = 0;

        // Keep looking until we reach the end of the string or we find the nth occurrence
            while((!Status) && (NumberOfPositionsYetToBeSearched > 0))
            {
            	if(CompareOnShorter(*PositionWhereInputStringWasFound, InputString,
                		InputStringLength, FindIsCaseSensitive) == 0)
                {
					if(NextOccurrenceNumber >= OccurrenceNumberToFindOfInputString)
                    {
                    	Status = true;
                    }
                    else
                    {
                    	NumberOfPositionsYetToBeSearched -= ((int) (InputStringLength));
					    ++NextOccurrenceNumber;
	    		    	*PositionWhereInputStringWasFound += InputStringLength;
                    }
                }
                else
                {
                	--NumberOfPositionsYetToBeSearched;
	        		++(*PositionWhereInputStringWasFound);
                }
            }
    	}

	// Are we searching backward?
		else if(OccurrenceNumberToFindOfInputString < 0)
	    {
        	OccurrenceNumberToFindOfInputString = -OccurrenceNumberToFindOfInputString;

			*PositionWhereInputStringWasFound = Size - InputStringLength;

        // Keep looking until we reach the beginning of the string or we find the nth occurrence
            while((!Status) && (NumberOfPositionsYetToBeSearched > 0))
            {
            	if(CompareOnShorter(*PositionWhereInputStringWasFound, InputString,
                		InputStringLength, FindIsCaseSensitive) == 0)
                {
					if(NextOccurrenceNumber >= OccurrenceNumberToFindOfInputString)
                    {
                    	Status = true;
                    }
                    else
                    {
                    	NumberOfPositionsYetToBeSearched -= ((int) (InputStringLength));
					    ++NextOccurrenceNumber;
	    		    	*PositionWhereInputStringWasFound -= InputStringLength;
                    }
                }
                else
                {
                	--NumberOfPositionsYetToBeSearched;
	        		--(*PositionWhereInputStringWasFound);
                }
            }
    	}
    }

    return(Status);
}





//
// Find (overloaded version #2 with an input HWSTRING).
//		Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HWSTRING::Find(HWSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound)
{
	return(Find(InputString->WChar, InputString->Size, FindIsCaseSensitive,
                				OccurrenceNumberToFindOfInputString, PositionWhereInputStringWasFound));
}




//
//	AutoResizeOn
//		Turn on autoresize
//
void HWSTRING::AutoResizeOn(void)
{
	AutoResize = true;
}





//
//	AutoResizeOff
//		Turn off autoresize
//
void HWSTRING::AutoResizeOff(void)
{
	AutoResize = false;
}




// Overloaded version #1 of Insert:  Insert a string at the caller specified location
void HWSTRING::Insert(const wchar_t *StringToInsert, unsigned int SourceLength, unsigned int PositionToInsertAt)
{
    unsigned int		i, j;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return;
	}

    if((PositionToInsertAt <= Size) && (SourceLength))
    {
    // Resize if necessary (and allowed).
	   	SmartReallocate(Size + SourceLength);

    // Make space for the new string
		if(SourceLength <= (MaximumSize - Size))
		{
			i = SourceLength + Size;
        	j = Size;
            while(j != PositionToInsertAt)
            {
            	WChar[--i] = WChar[--j];
            }

	    // Copy the string
    		for(i = 0;    i < SourceLength;    ++i)
        	{
				WChar[PositionToInsertAt++] = StringToInsert[i];
	        }

    	    Size += SourceLength;

			WChar[Size] = 0;
        }
    }

    return;
}




// Overloaded version #2 of Insert:  Insert a string at the caller specified location
void HWSTRING::Insert(HWSTRING *StringToInsert, unsigned int PositionToInsertAt)
{
	Insert(StringToInsert->WChar, StringToInsert->Size, PositionToInsertAt);

    return;
}




// Overloaded version #3 of Insert:  Insert a string at the caller specified location
void HWSTRING::Insert(const wchar_t *StringToInsert, unsigned int PositionToInsertAt)
{
	Insert(StringToInsert, ((unsigned int) wcslen( StringToInsert )), PositionToInsertAt);

    return;
}





//
//	GetNumber (overloaded version #1 -> get an integer parameter (positive or negative)
//		Process the next number and comma in the format specifier, removing those characters from the format
// 		specifier and returning the resulting number to the caller.  This routine assumes that all nulls and
// 		spaces have been removed from the format specifier prior to invoking this routine.
//
bool HWSTRING::GetNumber(int *NumericParameterValue)
{
	unsigned int	i;			/* Indices	*/
	bool	Status;		/* TRUE / FALSE status that reflects the success of the edit operation.	*/
    bool	NegateTheResult;	// Indicates whether or not a minus sign was found.


	Status = true;			/* No errors encountered yet.	*/
	i = 0;				/* Next character in format specifier	*/
    RemoveLeadingSpaceCharacters();
    NegateTheResult = false;

// If the format is empty, quit.
	if(!(Size))
    {
		Status = false;
    }

// If first character is '-', remove it, indicate that the result is to be negated, and verify that
// a digit follows.
	else if(WChar[0] == '-')
    {
    	++i;
        NegateTheResult = true;
		if((i < Size) && (!HSTRING::hhpisdigit(WChar[i])))
		{
			Status = false;
		}
    }

// If first character is '+', remove it and verify that a digit follows.
	else if(WChar[0] == '+')
    {
    	++i;
		if((i < Size) && (!HSTRING::hhpisdigit(WChar[i])))
		{
			Status = false;
		}
    }

// Verify that the first character is a digit.
    else if(!HSTRING::hhpisdigit(WChar[0]))
	{
		Status = false;
	}


    if(Status)
    {
		*NumericParameterValue = 0;

// Process all numeric digits and store the result.
		while((i < Size) && (HSTRING::hhpisdigit(WChar[i])))
		{
			*NumericParameterValue = *NumericParameterValue * 10 +
								((int) (WChar[i] - '0'));
			++i;
		}

// If the next character is a comma, remove it.
		if((i < Size) && (WChar[i] == ','))
		{
			++i;
		}

// Remove the processed characters from the format string, and adjust the format specifier length and
// delimiter location accordingly.
	    Remove(0L, i);

// Negate the result if a '-' was found.
		if(NegateTheResult)
        {
			*NumericParameterValue = -(*NumericParameterValue);
        }
	}

	return(Status);
}  // GetNumber (version #1)





//
//	GetNumber (overloaded version #2 -> get a non-negative integer parameter
//		Process the next number and comma in the format specifier, removing those characters from the format
// 		specifier and returning the resulting number to the caller.  This routine assumes that all nulls and
// 		spaces have been removed from the format specifier prior to invoking this routine.
//
bool HWSTRING::GetNumber(unsigned int *NumericParameterValue)
{
	unsigned int	i;			/* Indices	*/
	bool	Status;		/* TRUE / FALSE status that reflects the success of the edit operation.	*/


	Status = true;			/* No errors encountered yet.	*/
	i = 0;				/* Next character in format specifier	*/
    RemoveLeadingSpaceCharacters();

// If the format is empty, quit.
	if(!(Size))
    {
		Status = false;
    }

// Verify that the first character is a digit.
    else if(!HSTRING::hhpisdigit(WChar[0]))
	{
		Status = false;
	}


    if(Status)
    {
		*NumericParameterValue = 0;

// Process all numeric digits and store the result.
		while((i < Size) && (HSTRING::hhpisdigit(WChar[i])))
		{
			*NumericParameterValue = *NumericParameterValue * 10 +
								((int) (WChar[i] - '0'));
			++i;
		}

// If the next character is a comma, remove it.
		if((i < Size) && (WChar[i] == ','))
		{
			++i;
		}

// Remove the processed characters from the format string, and adjust the format specifier length and
// delimiter location accordingly.
	    Remove(0L, i);
	}

	return(Status);
}  // GetNumber (version #2)






//
//	CompareOnShorterWithWildcards (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length), using the '*', '?', and '#' wildcards in the local string.  This routine
//		returns true if the strings match and false otherwise.
//
bool HWSTRING::CompareOnShorterWithWildcards(unsigned int LocalStringIndex, const wchar_t *InputString, unsigned int InputStringLength,
				bool CompareIsCaseSensitive, unsigned int *NextPositionInInputStringBeyondSuccessfulCompare)
{
	bool	StringComparisonResult;
    unsigned int	i, j;
    wchar_t	LocalChar;
    wchar_t	InputChar;




// If local string index, input string size, and local string size all equal zero, true to indicate
// equality.
	if((LocalStringIndex == 0) && (Size == 0) && (InputStringLength == 0))
    {
	    StringComparisonResult = true;
    }

// Else if the local string index is past the end of the local string, return false to indicate that input string
// is larger
	else if(LocalStringIndex >= Size)
    {
	    StringComparisonResult = false;
    }

// Else if the local string size is zero, return false to indicate that input string is larger
	else if(Size == 0)
    {
	    StringComparisonResult = false;
    }

// Else if the input string size is zero, return false to indicate that local string is larger
	else if(InputStringLength == 0)
    {
	    StringComparisonResult = false;
    }

// Else we have one or more characters to compare.
	else
    {
    	StringComparisonResult = true;
        i = LocalStringIndex;
        j = 0;

        while((StringComparisonResult) && (i < Size) && (j < InputStringLength))
        {
        // Get the next characters to compare, converting lower case alphabetic to upper case if not
        // comparing case sensitive.
        	LocalChar = ((unsigned char) ((CompareIsCaseSensitive) ? WChar[i] :
            			(((WChar[i] >= 97) && (WChar[i] <= 122)) ? WChar[i] & 0xdf : WChar[i])));
        	InputChar = ((unsigned char) ((CompareIsCaseSensitive) ?  InputString[j] :
            			(((InputString[j] >= 97) && (InputString[j] <= 122)) ?
                        		InputString[j] & 0xdf : InputString[j])));

        // If the next local character is a '?' wildcard, move to the next characters (success on
        //		this character).
        	if(LocalChar == '?')
            {
            	++i;
               	++j;
            }

        // If the next local character is a '*', start a recursive search through the input string
        	else if(LocalChar == '*')
            {
            	++i;

            // If the '*' isn't the last character, then try to do the recursive match.
                if(i < Size)
                {
	                StringComparisonResult = false;
    	            while((!StringComparisonResult) && (i < Size) && (j < InputStringLength))
        	        {
        	        	StringComparisonResult = CompareOnShorterWithWildcards(i, &InputString[j],
		                    		InputStringLength - j, CompareIsCaseSensitive,
        		                    NextPositionInInputStringBeyondSuccessfulCompare);
            	    	if(!StringComparisonResult)
                	    {
                    		++j;
                    	}
	                    else
    	                {
						// We've found a match, but could we move further on and still get a match?
							do  {
								++j;
							} while((j < InputStringLength) &&
									(CompareOnShorterWithWildcards(i, &InputString[j],
				                    		InputStringLength - j, CompareIsCaseSensitive,
						                    NextPositionInInputStringBeyondSuccessfulCompare)));

        	            	j = j + *NextPositionInInputStringBeyondSuccessfulCompare - 1;
            	            i = Size;		// Force an end to the search, because we found an occurrence.
                        }
                    }
                }
                else
                {
                // This IS the last character in the match string, so we succeeded!  Since everything in the
                // input string is considered to match the ending '*', set the index of the input string to
                // the end of the string in order to signify that we consumed the whole thing.
					j = InputStringLength;
                }
            }

        // If the next local character is a '#' wildcard, then the next input character must be a number.
        	else if(LocalChar == '#')
            {
            	if((InputChar >= '0') && (InputChar <= '9'))
                {
                	++i;
                    ++j;
                }
                else
                {
                	StringComparisonResult = false;
                }
            }

        // If the next local character is a '^', then do the following:
        //		- if the character immediately after is a '^', '?', '*', or '#', compare that second character
        //			and ignore the '^' at the beginning
        //		- Otherwise, report a false result, since a '^' must be followed by one of these three
        //			characters.
        	else if(LocalChar == '^')
            {
            	++i;
        		if(i < Size)
                {
                	if((WChar[i] == '^') || (WChar[i] == '*') || (WChar[i] == '?') || (WChar[i] == '#'))
		            {
	    		    	LocalChar = ((unsigned char) ((CompareIsCaseSensitive) ? WChar[i] :
            				(((WChar[i] >= 97) && (WChar[i] <= 122)) ? WChar[i] & 0xdf : WChar[i])));
		            	if(LocalChar == InputChar)
        		        {
                			++i;
		                    ++j;
        		        }
                		else
		                {
        		        	StringComparisonResult = false;
                		}
		            }
               		else
	                {
       		        	StringComparisonResult = false;
               		}
                }
                else
                {
                // We ran out of string after the first '^'; WOOF!
                	StringComparisonResult = false;
                }
            }

        // The next local character is not a wildcard, so it needs to compare directly.
        	else
            {
            	if(LocalChar == InputChar)
                {
                	++i;
                    ++j;
                }
                else
                {
                	StringComparisonResult = false;
                }
            }
        }

	// If we didn't make it all the way through our search string, but we've been successful so far,
	// see if the remaining search string characters are '*'.  It's OK to have '*'s in our search string
	// after the end of the input string has been reached, but nothing else.
		while((StringComparisonResult) && (i < Size))
		{
			if(WChar[i] == '*')
			{
				++i;
			}
			else
			{
			// WOOF!
				StringComparisonResult = false;
			}
		}

    // If we succeeded, return the next position beyond successful comparison
		if(StringComparisonResult)
        {
        	*NextPositionInInputStringBeyondSuccessfulCompare = j;
        }
    }

	return(StringComparisonResult);
}






//
//	CompareOnShorterWithWildcards (overloaded version #2, where starting index into the local string is
//		assumed to be zero)
//		Compare the input string to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length), using the '*', '?', and '#' wildcards in the local string.  This routine
//		returns true if the strings match and false otherwise.
//
bool HWSTRING::CompareOnShorterWithWildcards(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive,
				unsigned int *NextPositionInInputStringBeyondSuccessfulCompare)
{
	return(CompareOnShorterWithWildcards(((unsigned int) 0L), InputString, InputStringLength, CompareIsCaseSensitive,
    														NextPositionInInputStringBeyondSuccessfulCompare));
}






//
//  CompareWithWildcards (overloaded version #1 with unsigned char* input).
//		Compare the input string to the local HWSTRING, using the '*', '?', and '#' wildcards.  This routine returns
//		a value of false when the local HWSTRING is not found in the input string, false when the local HWSTRING is
//		found in the input string leaving characters left over at the end of the input string, and true otherwise
//		(exact comparison).
//
bool HWSTRING::CompareWithWildcards(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	bool	StringComparisonResult;
    unsigned int	NextPositionInInputStringBeyondSuccessfulCompare;


// Compare the strings according to the shorter length.  If equal, then we'll have to check to see if one string
// is longer than the other.
	StringComparisonResult = CompareOnShorterWithWildcards(InputString, InputStringLength, CompareIsCaseSensitive,
    									&NextPositionInInputStringBeyondSuccessfulCompare);

// If strings are equal, but the entire input string wasn't consumed, return false.
	if(StringComparisonResult)
	{
		if(NextPositionInInputStringBeyondSuccessfulCompare < InputStringLength)
		{
			StringComparisonResult = false;
		}
	}

	return(StringComparisonResult);
}






//
//  CompareWithWildcards (overloaded version #2 with HWSTRING* input).
//		Compare the input string to the local HWSTRING, using the '*', '?', and '#' wildcards.  This routine returns
//		a value of false when the local HWSTRING is not found in the input string, false when the local HWSTRING is
//		found in the input string leaving characters left over at the end of the input string, and true otherwise
//		(exact comparison).
//
bool HWSTRING::CompareWithWildcards(HWSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareWithWildcards(InputString->WChar, InputString->Size, CompareIsCaseSensitive));
}





//
// FindWildcardString (overloaded version #1 with a unsigned char input string).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.  Wildcards '*', '?', and '#' are processed.
//
bool HWSTRING::FindWildcardString(const wchar_t *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound)
{
	int		NextOccurrenceNumber;	// Next occurrence to search for
    bool	Status;					// Set to true when the caller specified occurrence of the input string
    								//	is found
    unsigned int	i;
    unsigned int	SizeMinusWildcards;
    unsigned int	NextPositionInInputStringBeyondSuccessfulCompare;
    int		NumberOfPositionsYetToBeSearched;
    unsigned int	AdjustedInputStringLength;	// When moving backwards, we want to avoid looking at that part of the
    									//	input string that has already been successfully compared, so we'll
                                        //	set this value in combination with the start position in the input
                                        //	string such that we'll never cover any part of an area twice.  The
                                        //	reason for this is that if we do cover any part twice, we risk
                                        //	miscounting the number of occurrences when using wildcards.  Consider
                                        //	the local (search) string '*a*b*' and the input string 'tabgaabbc'.
                                        //	The first successful search (moving backward) will occur with the
                                        //	input string 'abbc'.  If, to find the next occurrence, we move
                                        //	backward by only one count, we'll get another success on 'aabbc', when
                                        //	we really want the next success to occur on 'tabga'.  To prevent the
                                        //	false positive, we simply ensure that any data resulting in a
                                        //	successful compare will never be used again.




	Status = false;					// Nothing found yet.
    NextOccurrenceNumber = 1;		// Start with first occurrence.

// Compute size of the local string without the '*' wildcards.
	SizeMinusWildcards = 0;
    i = 0;
    while(i < Size)
    {
    	if(WChar[i] == '^')
        {
            ++i;
        	if((i + 1) < Size)
            {
        		++SizeMinusWildcards;
	            ++i;
            }
        }
    	else if(WChar[i] == '*')
        {
            ++i;
        }
        else
        {
        	++SizeMinusWildcards;
        	++i;
        }
    }



// The size of the search string must be no bigger than the local string.
	if(InputStringLength >= SizeMinusWildcards)
    {
	    NumberOfPositionsYetToBeSearched = InputStringLength - SizeMinusWildcards + 1;

	// Are we searching forward?
	// Note: if occurrence number to search for is zero, return without success.
		if(OccurrenceNumberToFindOfInputString > 0)
	    {
			*PositionWhereInputStringWasFound = 0;

        // Keep looking until we reach the end of the string or we find the nth occurrence
            while((!Status) && (NumberOfPositionsYetToBeSearched > 0))
            {
    	    	if(CompareOnShorterWithWildcards(&InputString[*PositionWhereInputStringWasFound],
                		InputStringLength - *PositionWhereInputStringWasFound,
                		FindIsCaseSensitive, &NextPositionInInputStringBeyondSuccessfulCompare))
                {
					if(NextOccurrenceNumber >= OccurrenceNumberToFindOfInputString)
                    {
                    	Status = true;
                    }
                    else
                    {
                    	NumberOfPositionsYetToBeSearched -= ((int) (NextPositionInInputStringBeyondSuccessfulCompare));
					    ++NextOccurrenceNumber;
	    		    	*PositionWhereInputStringWasFound += NextPositionInInputStringBeyondSuccessfulCompare;
                    }
                }
                else
                {
                	--NumberOfPositionsYetToBeSearched;
	        		++(*PositionWhereInputStringWasFound);
                }
            }
    	}

	// Are we searching backward?
		else if(OccurrenceNumberToFindOfInputString < 0)
	    {
        	OccurrenceNumberToFindOfInputString = -OccurrenceNumberToFindOfInputString;

			*PositionWhereInputStringWasFound = InputStringLength - SizeMinusWildcards;
    		AdjustedInputStringLength = InputStringLength;

        // Keep looking until we reach the beginning of the string or we find the nth occurrence
            while((!Status) && (NumberOfPositionsYetToBeSearched > 0))
            {
    	    	if(CompareOnShorterWithWildcards(&InputString[*PositionWhereInputStringWasFound],
                		AdjustedInputStringLength - *PositionWhereInputStringWasFound,
                		FindIsCaseSensitive, &NextPositionInInputStringBeyondSuccessfulCompare))
                {
					if(NextOccurrenceNumber >= OccurrenceNumberToFindOfInputString)
                    {
                    	Status = true;
                    }
                    else
                    {
                        AdjustedInputStringLength = *PositionWhereInputStringWasFound;
                    	NumberOfPositionsYetToBeSearched -= ((int) (SizeMinusWildcards));
					    ++NextOccurrenceNumber;
	    		    	*PositionWhereInputStringWasFound -= SizeMinusWildcards;
                    }
                }
                else
                {
                	--NumberOfPositionsYetToBeSearched;
	        		--(*PositionWhereInputStringWasFound);
                }
            }
    	}
    }

    return(Status);
}





//
// FindWildcardString (overloaded version #2 with an input HWSTRING).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.  Wildcards '*', '?', and '#' are processed.
//
bool HWSTRING::FindWildcardString(HWSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound)
{
	return(FindWildcardString(InputString->WChar, InputString->Size, FindIsCaseSensitive,
                				OccurrenceNumberToFindOfInputString, PositionWhereInputStringWasFound));
}







//
//	CopyToOffset (overloaded version #1: unsigned char* input)
//		Copy characters to the local string at the caller specified location from the caller specified
//		index in the input string.  If there is not enough room in the local string, autoresize (if enabled)
//      or return an error.  Otherwise, copy characters.
//
bool HWSTRING::CopyToOffset(unsigned int IndexToStartOfCopyLocation, const wchar_t *InputString, unsigned int LengthToCopy)
{
    bool        ReturnStatus;               //
	unsigned int		i;							// Index to the position after the end of the copy string



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(IndexToStartOfCopyLocation + LengthToCopy);

    if((IndexToStartOfCopyLocation + LengthToCopy) <= MaximumSize)
	{
    	if(Size < (IndexToStartOfCopyLocation + LengthToCopy))
        {
        	Size = IndexToStartOfCopyLocation + LengthToCopy;
        }

    	for(i = 0;    i < LengthToCopy;    ++i)
        {
        	WChar[i + IndexToStartOfCopyLocation] = InputString[i];
        }

		WChar[Size] = 0;

        ReturnStatus = true;
	}
	else
	{
        ReturnStatus = false;
	}


    return(ReturnStatus);
}





//
//	FindCharacterForward
//		Search from the start index forward for the first occurrence of the caller specified
//		character.
//
bool HWSTRING::FindCharacterForward( wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereCharacterWasFound )
{
	bool	CharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereCharacterWasFound = StartIndex;

	// Keep searching until we find the character or we run out of string.
		while((!CharacterFound) && (*PositionWhereCharacterWasFound < ((int) Size)))
		{
			if(WChar[*PositionWhereCharacterWasFound] == Character)
			{
				CharacterFound = true;
			}
			else
			{
				(*PositionWhereCharacterWasFound)++;
			}
		}
	}

	return(CharacterFound);
}	// FindCharacterForward





//
//	FindCharacterBackward
//		Search from the start index backward for the first occurrence of the caller specified
//		character.
//
bool HWSTRING::FindCharacterBackward( wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereCharacterWasFound )
{
	bool	CharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereCharacterWasFound = StartIndex;

	// Keep searching until we find the character or we run out of string.
		while((!CharacterFound) && (*PositionWhereCharacterWasFound >= 0))
		{
			if(WChar[*PositionWhereCharacterWasFound] == Character)
			{
				CharacterFound = true;
			}
			else
			{
				(*PositionWhereCharacterWasFound)--;
			}
		}
	}

	return(CharacterFound);
}	// FindCharacterBackward





//
//	FindNonCharacterForward
//		Search from the start index forward for the first occurrence of a character not equal
//		to the caller specified character.
//
bool HWSTRING::FindNonCharacterForward( wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereNonCharacterWasFound)
{
	bool	NonCharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereNonCharacterWasFound = StartIndex;

	// Keep searching until we find the non-character or we run out of string.
		while((!NonCharacterFound) && (*PositionWhereNonCharacterWasFound < ((int) Size)))
		{
			if(WChar[*PositionWhereNonCharacterWasFound] != Character)
			{
				NonCharacterFound = true;
			}
			else
			{
				(*PositionWhereNonCharacterWasFound)++;
			}
		}
	}

	return(NonCharacterFound);
}	// FindNonCharacterForward





//
//	FindNonCharacterBackward
//		Search from the start index backward for the first occurrence of a character not equal
//		to the caller specified character.
//
bool HWSTRING::FindNonCharacterBackward( wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereNonCharacterWasFound)
{
	bool	NonCharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereNonCharacterWasFound = StartIndex;

	// Keep searching until we find the non-character or we run out of string.
		while((!NonCharacterFound) && (*PositionWhereNonCharacterWasFound >= 0))
		{
			if(WChar[*PositionWhereNonCharacterWasFound] != Character)
			{
				NonCharacterFound = true;
			}
			else
			{
				(*PositionWhereNonCharacterWasFound)--;
			}
		}
	}

	return(NonCharacterFound);
}	// FindNonCharacterBackward




//
//	MaximumLength
//		Return maximum size to caller.
//
int HWSTRING::MaximumLength(void)
{
	return(MaximumSize);
}	// MaximumLength





//
//	ReplaceAll
//		Replace all occurrences of a string
//
bool HWSTRING::ReplaceAll(const wchar_t *StringToReplace, const wchar_t *ReplacementString)
{
    bool	Status = true;				// Set to false if we run out of space, true otherwise.
    int		NextSearchPosition = 0;



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Keep searching for the source string until we run out of local string
	while(((NextSearchPosition + wcslen( StringToReplace )) <= Size) && (Status))
	{
		if(CompareOnShorter(NextSearchPosition, StringToReplace, wcslen( StringToReplace ), true) == 0)
		{
			Status = Remove(NextSearchPosition, wcslen( StringToReplace ));
			Insert(ReplacementString, NextSearchPosition);
			NextSearchPosition += wcslen( ReplacementString );
		}
		else
		{
			++NextSearchPosition;
		}
	}


	return Status;
}





//
//	FindFirstNonSpaceCharacter
//		Move past blanks, <TAB>s, <CR>s, <LF>s, and <FF>s in the local string.
//
void HWSTRING::FindFirstNonSpaceCharacter(int StartingIndex,
										 int *PositionWhereFirstNonSpaceCharacterWasFound)
{
	bool	NonSpaceCharacterFound=false;	// Haven't found a non-space character yet.


// Keep moving until we encounter a non-space character.
	*PositionWhereFirstNonSpaceCharacterWasFound = StartingIndex;
	while((!NonSpaceCharacterFound) && (*PositionWhereFirstNonSpaceCharacterWasFound < ((int) Size)))
	{
	// Ignore blanks, <TAB>s, <CR>s, <LF>s, and <FF>s.
		if((WChar[*PositionWhereFirstNonSpaceCharacterWasFound] == ' ') ||
			(WChar[*PositionWhereFirstNonSpaceCharacterWasFound] == 9) ||
			(WChar[*PositionWhereFirstNonSpaceCharacterWasFound] == 10) ||
			(WChar[*PositionWhereFirstNonSpaceCharacterWasFound] == 12) ||
			(WChar[*PositionWhereFirstNonSpaceCharacterWasFound] == 13))
		{
			++(*PositionWhereFirstNonSpaceCharacterWasFound);
		}

	// We must have found a non-space character
		else
		{
			NonSpaceCharacterFound = true;
		}
	}


	return;
} // FindFirstNonSpaceCharacter








//
//	ConvertToNumber (overloaded version #1 using a length limit).
//		Return a decimal number converted from the local string starting at the caller specified
//		location.
//
int HWSTRING::ConvertToNumber(int StartingPosition, int EndingPosition, int *NumberOfCharactersUsedInConversion)
{
	int		ConvertedNumber = 0;		// Number converted from string.
	int		NumberOfDigitsFound = 0;	// Number of digits found in the string (maximum of 10).
	bool	NumberIsPositive = true;	// Assume number is positive until we know otherwise
	int		NextPositionToCheck;		// Next position in the local string to check



// Indicate that we haven't used any characters yet.
	*NumberOfCharactersUsedInConversion = 0;

	NextPositionToCheck = StartingPosition;

// If the starting position is out of range, WOOF!
	if(StartingPosition >= (int) Size)
		return 0;

// If the ending position is out of range, adjust it to the end of the string.
	if(EndingPosition >= (int) Size)
		EndingPosition = (int) Size - 1;

// Move past space characters.
	FindFirstNonSpaceCharacter(NextPositionToCheck, ((int *) &NextPositionToCheck));


// Get a sign
	if((NextPositionToCheck <= EndingPosition) &&
					(WChar[NextPositionToCheck] == '+'))
	{
		NumberIsPositive = true;
		++NextPositionToCheck;
		FindFirstNonSpaceCharacter(NextPositionToCheck, ((int *) &NextPositionToCheck));
	}
	else if((NextPositionToCheck <= EndingPosition) &&
					(WChar[NextPositionToCheck] == '-'))
	{
		NumberIsPositive = false;
		++NextPositionToCheck;
		FindFirstNonSpaceCharacter(NextPositionToCheck, ((int *) &NextPositionToCheck));
	}


// Get the number
	while((NextPositionToCheck <= EndingPosition) &&
					(WChar[NextPositionToCheck] >= '0') &&
					(WChar[NextPositionToCheck] <= '9') &&
					(NumberOfDigitsFound < 10))
	{
		ConvertedNumber = (ConvertedNumber * 10) + ((int) (WChar[NextPositionToCheck] - '0'));
		++NumberOfDigitsFound;
		++NextPositionToCheck;
	}


// We have a number if we found at least one digit.
	if(NumberOfDigitsFound)
	{
		*NumberOfCharactersUsedInConversion = NextPositionToCheck - StartingPosition;
		if(!NumberIsPositive)
		{
			ConvertedNumber = -ConvertedNumber;
		}
	}


	return(ConvertedNumber);
} // ConvertToNumber (overloaded version #1)







//
//	ConvertToNumber (overloaded version #2 using the entire string).
//		Return a decimal number converted from the local string starting at the caller specified
//		location.
//
int HWSTRING::ConvertToNumber(int StartingPosition, int *NumberOfCharactersUsedInConversion)
{
	return(ConvertToNumber(StartingPosition, Size - 1, NumberOfCharactersUsedInConversion));
} // ConvertToNumber (overloaded version #2)







//
//	ConvertHexToNumber (overloaded version #1 using a length limit).
//		Return a decimal number converted from the local string starting at the caller specified
//		location, where the string is assumed to be in hexadecimal format.
//
int HWSTRING::ConvertHexToNumber(int StartingPosition, int EndingPosition, int *NumberOfCharactersUsedInConversion)
{
	int		ConvertedNumber = 0;		// Number converted from string.
	int		NumberOfDigitsFound = 0;	// Number of digits found in the string (maximum of 8).
	int		NextPositionToCheck;		// Next position in the local string to check
	int		HexCharacterCode;



// Indicate that we haven't used any characters yet.
	*NumberOfCharactersUsedInConversion = 0;

	NextPositionToCheck = StartingPosition;

// If the starting position is out of range, WOOF!
	if(StartingPosition >= (int) Size)
		return 0;

// If the ending position is out of range, adjust it to the end of the string.
	if(EndingPosition >= (int) Size)
		EndingPosition = (int) Size - 1;

// Move past space characters.
	FindFirstNonSpaceCharacter(NextPositionToCheck, ((int *) &NextPositionToCheck));


// Get the number
	while((NextPositionToCheck <= EndingPosition) &&
					(((WChar[NextPositionToCheck] >= '0') && (WChar[NextPositionToCheck] <= '9')) ||
						((WChar[NextPositionToCheck] >= 'A') && (WChar[NextPositionToCheck] <= 'F')) ||
						((WChar[NextPositionToCheck] >= 'a') && (WChar[NextPositionToCheck] <= 'f'))) &&
					(NumberOfDigitsFound < 8))
	{
		if((WChar[NextPositionToCheck] >= '0') && (WChar[NextPositionToCheck] <= '9'))
		{
			HexCharacterCode = ((int) (WChar[NextPositionToCheck] - '0'));
		}
		else if((WChar[NextPositionToCheck] >= 'A') && (WChar[NextPositionToCheck] <= 'F'))
		{
			HexCharacterCode = ((int) (WChar[NextPositionToCheck] - 'A' + 10));
		}
		else
		{
			HexCharacterCode = ((int) (WChar[NextPositionToCheck] - 'a' + 10));
		}
		ConvertedNumber = (ConvertedNumber * 16) + HexCharacterCode;
		++NumberOfDigitsFound;
		++NextPositionToCheck;
	}


// We have a number if we found at least one digit.
	if(NumberOfDigitsFound)
	{
		*NumberOfCharactersUsedInConversion = NextPositionToCheck - StartingPosition;
	}


	return(ConvertedNumber);
} // ConvertHexToNumber (overloaded version #1)







//
//	ConvertHexToNumber (overloaded version #2 using the entire string).
//		Return a decimal number converted from the local string starting at the caller specified
//		location, where the string is assumed to be in hexadecimal format.
//
int HWSTRING::ConvertHexToNumber(int StartingPosition, int *NumberOfCharactersUsedInConversion)
{
	return(ConvertHexToNumber(StartingPosition, Size - 1, NumberOfCharactersUsedInConversion));
} // ConvertHexToNumber (overloaded version #2)





//
//	UpperCase
//		Convert local string to upper case
//
void HWSTRING::UpperCase(void)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return;
	}

	for(i = 0;    i < Size;    ++i)
	{
		if((WChar[i] >= 'a') && (WChar[i] <= 'z'))
		{
			WChar[i] &= 0xDF;
		}
	}

	return;
} // UpperCase





//
//	LowerCase
//		Convert local string to upper case
//
void HWSTRING::LowerCase(void)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return;
	}

	for(i = 0;    i < Size;    ++i)
	{
		if((WChar[i] >= 'A') && (WChar[i] <= 'Z'))
		{
			WChar[i] |= 0x20;
		}
	}

	return;
} // LowerCase




//
//	RangeCheck
//		Check the current string to see if all characters fall within the specified range.  Multiple (up to 15
//		ranges) may be selected.
//
bool HWSTRING::RangeCheck(int LowRange1, int HighRange1, int LowRange2, int HighRange2, 
			int LowRange3, int HighRange3, int LowRange4, int HighRange4, 
			int LowRange5, int HighRange5, int LowRange6, int HighRange6, 
			int LowRange7, int HighRange7, int LowRange8, int HighRange8, 
			int LowRange9, int HighRange9, int LowRange10, int HighRange10, 
			int LowRange11, int HighRange11, int LowRange12, int HighRange12, 
			int LowRange13, int HighRange13, int LowRange14, int HighRange14, 
			int LowRange15, int HighRange15)
{
	bool	Status = true;				// Assume success until we know otherwise.
	int		i;
	int		j;
	int		NextLowRangeValue, NextHighRangeValue;
	int		LowRange[15] = {LowRange1, LowRange2, LowRange3, LowRange4, LowRange5, LowRange6, LowRange7, LowRange8,
							LowRange9, LowRange10, LowRange11, LowRange12, LowRange13, LowRange14, LowRange15};
	int		HighRange[15] = {HighRange1, HighRange2, HighRange3, HighRange4, HighRange5, HighRange6, HighRange7, HighRange8,
							HighRange9, HighRange10, HighRange11, HighRange12, HighRange13, HighRange14, HighRange15};


// Determine number of ranges.
	int		NumberOfRanges = 0;
	while(( NumberOfRanges < 15 ) && ( LowRange[ NumberOfRanges ] >= 0 ))
		++NumberOfRanges;

// Loop through all the ranges until we reach the maximum or encounter a -1.
// Check all the values
	j = 0;
	while(( Status ) && ( j < (int) Size ))
	{
		i = 0;
		Status = false;					// Assume we fail until we find a range match.
		while(( !Status ) && ( i < NumberOfRanges ))
		{
			NextLowRangeValue = LowRange[i];
			NextHighRangeValue = HighRange[i];

		// Swap the ranges if the caller specified them in the wrong order.
			if(LowRange[i] > HighRange[i])
			{
				NextHighRangeValue = LowRange[i];
				NextLowRangeValue = HighRange[i];
			}

			if(((int) WChar[j] >= NextLowRangeValue) && ((int) WChar[j] <= NextHighRangeValue))
			{
				Status = true;
			}
			++i;
		}

		++j;
	}


	return Status;	
} // RangeCheck






//
//	ParseRevisionString (version #1, using HWSTRING input)
//		Static member function to parse a version string into numeric segments.  Returns true if the entire string was
//		consumed, false otherwise.
//
bool HWSTRING::ParseRevisionString( HWSTRING *InputString, int *AmountOfCharactersConsumed,
								  int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments )
{
	bool	Status = true;		// Assume success until we know otherwise.

	int		NumberOfCharactersUsedInLastConversion = 1;	// Set to non-zero so we don't quit the first time through.

	*AmountOfCharactersConsumed = 0;
	*NumberOfVersionSegments = 0;

	while(( *NumberOfVersionSegments < MaximumNumberOfVersionSegments ) &&
			( *AmountOfCharactersConsumed < (int) InputString->Size ) && ( NumberOfCharactersUsedInLastConversion > 0 ))
	{
		VersionSegments[ *NumberOfVersionSegments ] = InputString->ConvertToNumber( *AmountOfCharactersConsumed,
											&NumberOfCharactersUsedInLastConversion );
		++(*NumberOfVersionSegments);
		*AmountOfCharactersConsumed += NumberOfCharactersUsedInLastConversion;

	// If there is a period next, move past it.
		if(( NumberOfCharactersUsedInLastConversion > 0 ) && ( *AmountOfCharactersConsumed < (int) InputString->Size ) &&
					( InputString->WChar[ *AmountOfCharactersConsumed ] == '.' ))
		{
			++(*AmountOfCharactersConsumed);
		}
	}

	if( *AmountOfCharactersConsumed < (int) InputString->Size )
	{
		Status = false;
	}

	return Status;
} // ParseRevisionString (version #1, using HSTRING input)






//
//	ParseRevisionString (version #2, using character string input)
//		Static member function to parse a version string into numeric segments.  Returns true if the entire string was
//		consumed, false otherwise.
//
bool HWSTRING::ParseRevisionString( wchar_t *InputString, int InputStringLength, int *AmountOfCharactersConsumed,
								  int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments )
{
	HWSTRING		hstrInputString( InputString, (unsigned int) InputStringLength, false, true, true );
	return ParseRevisionString( &hstrInputString, AmountOfCharactersConsumed, MaximumNumberOfVersionSegments,
					NumberOfVersionSegments, VersionSegments );
} // ParseRevisionString (version #2, using character string input)






//
// Append a range of characters in this string to an HSTRING, storing each wchar_t in little endian.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::AppendToHString( HSTRING *HStringToAppendTo, unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	int		NextHStringLocation = (int) HStringToAppendTo->Size;
	int		NextLocalStringLocation = (int) FirstCharPosition;
	int		Length;
	int		Direction;
	int		i;
	bool	Status = true;		// No errors yet.



// Verify range.
	Status = RangePositionsAreValid( FirstCharPosition, LastCharPosition );

// First, resize the output string.
	if( Status )
	{
		Length = (int) RangeLength( FirstCharPosition, LastCharPosition );
		Direction = RangeDirection( FirstCharPosition, LastCharPosition );
		Status = HStringToAppendTo->Reallocate( HStringToAppendTo->Size + ( Length * sizeof(wchar_t) ), false );
	}


// If the resize worked, copy this string in little endian format.
	if( Status )
	{
		for( i = 0;    i < (int) Length;    ++i )
		{
			HStringToAppendTo->Char[ NextHStringLocation++ ] = ((unsigned char) ( WChar[ NextLocalStringLocation ] & 0xFF ));
			HStringToAppendTo->Char[ NextHStringLocation++ ] = ((unsigned char) ( ( WChar[ NextLocalStringLocation ] / 256 ) & 0xFF ));
			if (wcSize == 4)
			{
				HStringToAppendTo->Char[ NextHStringLocation++ ] = ((unsigned char) ( ( WChar[ NextLocalStringLocation ] / (256*256) ) & 0xFF ));
				HStringToAppendTo->Char[ NextHStringLocation++ ] = ((unsigned char) ( ( WChar[ NextLocalStringLocation ] / (256*256*256) ) & 0xFF ));
			}
			NextLocalStringLocation += Direction;
		}
	}

// Append NULL onto the end.
	HStringToAppendTo->Size = NextHStringLocation;
	HStringToAppendTo->Char[ NextHStringLocation ] = 0;

	return Status;
} // AppendToHString






//
// Append this string to an HSTRING, storing each wchar_t in little endian.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::AppendToHString( HSTRING *HStringToAppendTo )
{
	if( Size > 0 )
	{
		return AppendToHString( HStringToAppendTo, 0, Size - 1 );
	}
	else
	{
		return true;
	}
} // AppendToHString






//
// Copy a range of characters in this string to an HSTRING, storing each wchar_t in little endian.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::CopyToHString( HSTRING *HStringToCopyTo, unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	bool	Status = true;		// No errors yet.


// First, resize the output string.  Note that the resize is redundantly done again in AppendToHString.  The reason for this
// is that we don't want to erase the existing string by setting Size to zero until we know that there will be enough room
// for the new string.
	Status = HStringToCopyTo->Reallocate( RangeLength( FirstCharPosition, LastCharPosition ) * sizeof(wchar_t), false );

// If the resize worked, copy this string in little endian format by setting the size to zero and calling the append function.
	if( Status )
	{
		HStringToCopyTo->Size = 0;
		AppendToHString( HStringToCopyTo, FirstCharPosition, LastCharPosition );
	}

	return Status;
} // CopyToHString






//
// Copy this string to an HSTRING, storing each wchar_t in little endian.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::CopyToHString( HSTRING *HStringToCopyTo )
{
	if( Size > 0 )
	{
		return CopyToHString( HStringToCopyTo, 0, Size - 1 );
	}
	else
	{
		HStringToCopyTo->Copy( "" );
		return true;
	}
} // CopyToHString






//
//	AppendLittleEndian
//		Append a range of characters from a character string to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::AppendLittleEndian( unsigned char *StringToAppendFrom, unsigned int LengthOfStringToAppendFrom,
									unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	int				Length;
	int				Direction;
	unsigned int	NumberOfWideCharactersToCopy;
	unsigned int	i;
    bool	Status = true;				// No errors yet.



// Verify range.
	Status = RangePositionsAreValid( FirstCharPosition, LastCharPosition, LengthOfStringToAppendFrom );

// First, resize the output string.
	if( Status )
	{
		Length = (int) RangeLength( FirstCharPosition, LastCharPosition, LengthOfStringToAppendFrom );
		Direction = RangeDirection( FirstCharPosition, LastCharPosition, LengthOfStringToAppendFrom );
		NumberOfWideCharactersToCopy = Length / wcSize;
		Status = Reallocate( Size + NumberOfWideCharactersToCopy, false );
	}


// Do the append if no errors.
	if( Status )
	{
		if( Direction == 1 )
		{
			int		NextHStringLocation = (int) FirstCharPosition;
			for( i = 0;    i < NumberOfWideCharactersToCopy;    ++i )
			{
				WChar[ Size ] = ((wchar_t) StringToAppendFrom[ NextHStringLocation ] );
				WChar[ Size] += ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction ] ) << 8;
				if (wcSize == 4)
				{
					WChar[ Size ] += ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction * 2 ] ) << 16;
					WChar[ Size ] += ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction * 3 ] ) << 24;
				}
				Size++;
				NextHStringLocation += Direction * wcSize;
			}
		}
		else
		{
			int		NextHStringLocation = (int) FirstCharPosition;
			for( i = 0;    i < NumberOfWideCharactersToCopy;    ++i )
			{
				if (wcSize == 4)
				{
					WChar[ Size ] = ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction * 3 ] );
					WChar[ Size ] = ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction * 2 ] ) << 8;
					WChar[ Size ] = ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction ] ) << 16;
					WChar[ Size ] += ((wchar_t) StringToAppendFrom[ NextHStringLocation ] ) << 24;
				}
				else
				{
					WChar[ Size ] = ((wchar_t) StringToAppendFrom[ NextHStringLocation + Direction ] );
					WChar[ Size ] += ((wchar_t) StringToAppendFrom[ NextHStringLocation ] ) << 8;
				}
				Size++;
				NextHStringLocation += Direction * wcSize;
			}
		}
	}

// Append NULL onto the end.
	WChar[ Size ] = 0;


    return Status;
} // AppendLittleEndian






//
//	AppendLittleEndian
//		Append characters from a character string to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::AppendLittleEndian( unsigned char *StringToAppendFrom, unsigned int LengthOfStringToAppendFrom )
{
	if( LengthOfStringToAppendFrom > 0 )
	{
		return AppendLittleEndian( StringToAppendFrom, LengthOfStringToAppendFrom, 0, LengthOfStringToAppendFrom - 1 );
	}
	else
	{
		return true;
	}
} // AppendLittleEndian






//
//	AppendFromHString
//		Append a range of characters from an HSTRING to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::AppendFromHString( HSTRING *HStringToAppendFrom, unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	return AppendLittleEndian( HStringToAppendFrom->Char, HStringToAppendFrom->Size, FirstCharPosition, LastCharPosition );
} // AppendFromHString




//
//	CopyLittleEndian
//		Copy a range of characters from a character string to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::CopyLittleEndian( unsigned char *StringToCopyFrom, unsigned int LengthOfStringToCopyFrom,
								unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	bool	Status = true;		// No errors yet.



// First, resize this string.  Note that the resize is redundantly done again in AppendToHString.  The reason for this
// is that we don't want to erase the existing string by setting Size to zero until we know that there will be enough room
// for the new string.
	Status = Reallocate( RangeLength( FirstCharPosition, LastCharPosition, LengthOfStringToCopyFrom ) / wcSize, false );

// If the resize worked, copy to this string in little endian format by setting the size to zero and calling the append function.
	if( Status )
	{
		Size = 0;
		AppendLittleEndian( StringToCopyFrom, LengthOfStringToCopyFrom, FirstCharPosition, LastCharPosition );
	}

	return Status;
} // CopyLittleEndian




//
//	CopyLittleEndian
//		Copy characters from a character string to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::CopyLittleEndian( unsigned char *StringToCopyFrom, unsigned int LengthOfStringToCopyFrom )
{
	if( LengthOfStringToCopyFrom > 0 )
	{
		return CopyLittleEndian( StringToCopyFrom, LengthOfStringToCopyFrom, 0, LengthOfStringToCopyFrom - 1 );
	}
	else
	{
		Copy( (const wchar_t *)("") );
		return true;
	}
} // CopyLittleEndian




//
//	CopyFromHString
//		Copy a range of characters from an HSTRING to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::CopyFromHString( HSTRING *HStringToCopyFrom, unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	return CopyLittleEndian( HStringToCopyFrom->Char, HStringToCopyFrom->Size, FirstCharPosition, LastCharPosition );
} // CopyFromHString




//
//	CopyFromHString
//		Copy an HSTRING to this string, retrieving each wchar_t in little endian format.
//
bool HWSTRING::CopyFromHString( HSTRING *HStringToCopyFrom )
{
	if( HStringToCopyFrom->Size > 0 )
	{
		return CopyLittleEndian( HStringToCopyFrom->Char, HStringToCopyFrom->Size, 0, HStringToCopyFrom->Size - 1 );
	}
	else
	{
		Copy( (const wchar_t *)("") );
		return true;
	}
} // CopyFromHString






//
// Append a range of characters in this string to an HSTRING, storing each wchar_t as a single character.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::ConvertAndAppendToHString( HSTRING *HStringToAppendTo, unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	int		NextLocalStringLocation = (int) FirstCharPosition;
	int		Length;
	int		Direction;
	int		i;
	bool	Status = true;		// No errors yet.



// Verify range.
	Status = RangePositionsAreValid( FirstCharPosition, LastCharPosition );

// First, resize the output string.
	if( Status )
	{
		Length = (int) RangeLength( FirstCharPosition, LastCharPosition );
		Direction = RangeDirection( FirstCharPosition, LastCharPosition );
		Status = HStringToAppendTo->Reallocate( HStringToAppendTo->Size + Length, false );
	}


// If the resize worked, copy this string in little endian format.
	if( Status )
	{
		for( i = 0;    i < (int) Length;    ++i )
		{
			HStringToAppendTo->Char[ HStringToAppendTo->Size++ ] = ((unsigned char) ( WChar[ NextLocalStringLocation ] & 0xFF ));
			NextLocalStringLocation += Direction;
		}
	}

// Append NULL onto the end.
	HStringToAppendTo->Char[ HStringToAppendTo->Size ] = 0;


	return Status;
} // ConvertAndAppendToHString






//
// Append this string to an HSTRING, storing each wchar_t as a single character.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::ConvertAndAppendToHString( HSTRING *HStringToAppendTo )
{
	if( Size > 0 )
	{
		return ConvertAndAppendToHString( HStringToAppendTo, 0, Size - 1 );
	}
	else
	{
		return true;
	}
} // ConvertAndAppendToHString






//
// Copy a range of characters in this string to an HSTRING, storing each wchar_t as a single character.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::ConvertAndCopyToHString( HSTRING *HStringToCopyTo, unsigned int FirstCharPosition, unsigned int LastCharPosition )
{
	bool	Status = true;		// No errors yet.


// First, resize the output string.  Note that the resize is redundantly done again in AppendToHString.  The reason for this
// is that we don't want to erase the existing string by setting Size to zero until we know that there will be enough room
// for the new string.
	Status = HStringToCopyTo->Reallocate( RangeLength( FirstCharPosition, LastCharPosition ), false );

// If the resize worked, copy this string in little endian format by setting the size to zero and calling the append function.
	if( Status )
	{
		HStringToCopyTo->Size = 0;
		ConvertAndAppendToHString( HStringToCopyTo, FirstCharPosition, LastCharPosition );
	}

	return Status;
} // ConvertAndCopyToHString






//
// Copy this string to an HSTRING, storing each wchar_t as a single character.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HWSTRING::ConvertAndCopyToHString( HSTRING *HStringToCopyTo )
{
	if( Size > 0 )
	{
		return ConvertAndCopyToHString( HStringToCopyTo, 0, Size - 1 );
	}
	else
	{
		HStringToCopyTo->Copy( "" );
		return true;
	}
} // ConvertAndCopyToHString






//
//	ConvertAndAppendFromHString
//		Append a range of characters from an HSTRING to this string, retrieving each wchar_t as a single character.
//
bool HWSTRING::ConvertAndAppendFromHString( HSTRING *HStringToAppendFrom, unsigned int FirstCharPosition,
										unsigned int LastCharPosition )
{
	int		Length;
	int		Direction;
	int		i;
    bool	Status = true;				// No errors yet.



// Verify range.
	Status = RangePositionsAreValid( FirstCharPosition, LastCharPosition, HStringToAppendFrom->Size );

// First, resize the output string.
	if( Status )
	{
		Length = (int) RangeLength( FirstCharPosition, LastCharPosition, HStringToAppendFrom->Size );
		Direction = RangeDirection( FirstCharPosition, LastCharPosition, HStringToAppendFrom->Size );
		Status = Reallocate( Size + Length, false );
	}


// Do the append if no errors.
	if( Status )
	{
		int		NextHStringLocation = (int) FirstCharPosition;
		for( i = 0;    i < Length;    ++i )
		{
			WChar[ Size++ ] = ((wchar_t) HStringToAppendFrom->Char[ NextHStringLocation ] );
			NextHStringLocation += Direction;
		}
	}

// Append NULL onto the end.
	WChar[ Size ] = 0;


    return Status;
} // ConvertAndAppendFromHString




//
//	ConvertAndCopyFromHString
//		Copy a range of characters from an HSTRING to this string, retrieving each wchar_t as a single character.
//
bool HWSTRING::ConvertAndCopyFromHString( HSTRING *HStringToCopyFrom, unsigned int FirstCharPosition,
										 unsigned int LastCharPosition )
{
	bool	Status = true;		// No errors yet.



// First, resize this string.  Note that the resize is redundantly done again in AppendToHString.  The reason for this
// is that we don't want to erase the existing string by setting Size to zero until we know that there will be enough room
// for the new string.
	Status = Reallocate( RangeLength( FirstCharPosition, LastCharPosition, HStringToCopyFrom->Size ), false );

// If the resize worked, copy to this string in little endian format by setting the size to zero and calling the append function.
	if( Status )
	{
		Size = 0;
		ConvertAndAppendFromHString( HStringToCopyFrom, FirstCharPosition, LastCharPosition );
	}

	return Status;
} // ConvertAndCopyFromHString




//
//	ConvertAndCopyFromHString
//		Copy an HSTRING to this string, retrieving each wchar_t as a single character.
//
bool HWSTRING::ConvertAndCopyFromHString( HSTRING *HStringToCopyFrom )
{
	if( HStringToCopyFrom->Size > 0 )
	{
		return ConvertAndCopyFromHString( HStringToCopyFrom, 0, HStringToCopyFrom->Size - 1 );
	}
	else
	{
		Copy( (const wchar_t *)("") );
		return true;
	}
}
