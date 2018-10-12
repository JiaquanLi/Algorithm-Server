//======================================================================================
// HString.cpp
//======================================================================================
// $RCSfile: hstring.cpp $
// $Revision: 5107 $
// $Date: 2013-04-25 20:17:41 +0200 (jeu., 25 avr. 2013) $
// $Author: Ledwith, James $
//======================================================================================
//	Copyright (C) HandHeld Products  2001
//======================================================================================




//---------------------------------------------------------------------------
//
//  Class name:     HSTRING
//
//  Class description:
//      This class defines an interface to an unsigned character (unsigned char) string.
//      The string characteristics tracked are the current length (Size) and
//      the maximum size it may grow to (MaximumSize).  The maximum size is
//      defined at instantiation.  The Size will change as the string is erased,
//      rewritten, appended, etc.  Both the Size and the address (Char) of the
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
//      CopyString will copy either another HSTRING or a character string to
//      the local string.
//
//      Append will append either another HSTRING or a character string to
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

//---------------------------------------------------------------------------


#include <ctype.h>		// data type conversion functions
#include <string.h>		// 'C' string functions
#include <stdio.h>		// Standard I/O
#include <math.h>		// Standard math functions

#include "hstring.h"








//
//	InitializeAutoResizingInformation
//		Initialize auto resize information.  This is done at instantiation and whenever a reallocation is made that is
//		smaller than the current maximum size.
//
void HSTRING::InitializeAutoResizingInformation( void )
{
	ResizeQuantity = DEFAULT_AUTO_RESIZE_ADDITIONAL_SPACE;
	NumberOfCyclesSinceLastResize = 0;
	FirstAutoResizeAfterInstantiationOrReallocationToSmallerMaximumSize = true;
//	MinimumResizeQuantity = 0;
//	MaximumResizeQuantity = MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE;

	return;
} // InitializeAutoResizingInformation






//
// Constructor for HSTRING (overloaded versions #1, with maximum size and autoresize defined by caller).
// Reserve space for the local string and null it out.
//
HSTRING::HSTRING(unsigned int DeclaredMaximumSize, bool InputAutoResize)
{
	Char = new unsigned char[DeclaredMaximumSize+2];     // Leave space for a NULL.
	Size = 0;
    Char[0] = 0;
	MaximumSize = DeclaredMaximumSize;
    AutoResize = InputAutoResize;
	ReadOnly = false;		// Don't make it read only when there is no initializer data.
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
}





//
// Constructor for HSTRING (overloaded versions #2, initializing with null terminated constant character string, autoresize,
// and read only specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HSTRING::HSTRING(const char *InitialString, bool InputAutoResize, bool InputReadOnly)
{
    unsigned int       i;


	Size = strlen(InitialString);

    MaximumSize = Size;
	Char = new unsigned char[MaximumSize + 2];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
	{
		Char[i] = InitialString[i];
    }

	Char[Size] = 0;

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;

    return;
}





//
// Constructor for HSTRING (overloaded versions #3, initializing with null terminated character string, autoresize,
// read only specifier , and initializer specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HSTRING::HSTRING(char *InitialString, bool InputAutoResize, bool InputReadOnly, bool UseInitializerBuffer)
{
    unsigned int       i;


	Size = strlen(InitialString);

	if( UseInitializerBuffer )
	{
	    MaximumSize = Size;
		Char = (unsigned char *) InitialString;
	}
	else
	{
	    MaximumSize = Size;
		Char = new unsigned char[MaximumSize + 2];     // Leave space for a NULL.
	    for(i=0; i<Size; ++i)
		{
			Char[i] = InitialString[i];
	    }

		Char[Size] = 0;
	}

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = UseInitializerBuffer;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;

    return;
}




//
// Constructor for HSTRING (overloaded versions #4, initializing with constant character string, length, autoresize,
// and read only specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HSTRING::HSTRING(const unsigned char *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize, bool InputReadOnly)
{
    unsigned int       i;


	Size = LengthOfInitialString;

    MaximumSize = Size;
	Char = new unsigned char[MaximumSize + 2];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
	{
		Char[i] = InitialString[i];
    }

	Char[Size] = 0;

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;

    return;
}




//
// Constructor for HSTRING (overloaded versions #5, initializing with character string, length, autoresize, read only specifier,
// and initializer specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HSTRING::HSTRING(unsigned char *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize, bool InputReadOnly,
					bool UseInitializerBuffer)
{
    unsigned int       i;


	Size = LengthOfInitialString;

	if( UseInitializerBuffer )
	{
	    MaximumSize = Size;
		Char = InitialString;
	}
	else
	{
	    MaximumSize = Size;
		Char = new unsigned char[MaximumSize + 2];     // Leave space for a NULL.
	    for(i=0; i<Size; ++i)
		{
			Char[i] = InitialString[i];
	    }

		Char[Size] = 0;
	}

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = UseInitializerBuffer;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;

    return;
}





//
// Constructor for HSTRING (overloaded versions #6, initializing with HSTRING, autoresize, and read only specifier  sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
//
HSTRING::HSTRING(HSTRING *InitialString, bool InputAutoResize, bool InputReadOnly)
{
    unsigned int       i;


	Size = InitialString->Size;
    MaximumSize = Size;
	Char = new unsigned char[MaximumSize + 2];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
    {
        Char[i] = InitialString->Char[i];
    }

	Char[Size] = 0;

    AutoResize = InputAutoResize;
	ReadOnly = InputReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;

    return;
}










//
// Constructor for HSTRING (overloaded versions #7, initializing with HSTRING and using the input string values for
// autoresize and read only.
// Reserve space for the local string and store the character string sent by the caller.
//
HSTRING::HSTRING(HSTRING *InitialString)
{
    unsigned int       i;


	Size = InitialString->Size;
    MaximumSize = Size;
	Char = new unsigned char[MaximumSize + 2];     // Leave space for a NULL.
    for(i=0; i<Size; ++i)
    {
        Char[i] = InitialString->Char[i];
    }

	Char[Size] = 0;

    AutoResize = InitialString->AutoResize;
	ReadOnly = InitialString->ReadOnly;
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;

    return;
}






//
// Constructor for HSTRING (overloaded versions #8, using default size).
// Reserve space for the local string and null it out.
//
HSTRING::HSTRING( void )
{
	MaximumSize = DEFAULT_AUTO_RESIZE_ADDITIONAL_SPACE;
	Char = new unsigned char[ MaximumSize + 2 ];     // Leave space for a NULL.
	Size = 0;
    Char[0] = 0;
    AutoResize = true;
	ReadOnly = false;		// Don't make it read only when there is no initializer data.
	InitializerBufferUsed = false;
	InitializeAutoResizingInformation();
	UseXInHexadecimalFormat = false;
}






// Copy constructor for HSTRING (overloaded versions #9).
HSTRING::HSTRING(const HSTRING & InitialString)
{
	AutoResize = InitialString.AutoResize;
	ReadOnly = InitialString.ReadOnly;
	InitializerBufferUsed = false;  // false means we are creating Char[] on heap
	UseXInHexadecimalFormat = InitialString.UseXInHexadecimalFormat;;
	MaximumSize = InitialString.MaximumSize;  // Note:  above constructor with HSTRING * sets MaxmimumSize to the passed in string's size not it's MaxmimumSize.  There's no explanation.  It doesn't seem right to do this (so I'm not going to do it).
	Size = InitialString.Size;
	InitializeAutoResizingInformation();
	Char = new unsigned char[ MaximumSize + 2 ]; // Leave space for a NULL.  Note:  above code has +2 here instead of +1 with no explanation. Perhaps it has something to do with Unicode.  In case it's needed, we'll do it too.

	memcpy(Char, InitialString.Char, Size);
	Char[Size] = 0;
}








//
// Free space allocated to the local string.
//
HSTRING::~HSTRING(void)
{
	if( !InitializerBufferUsed )
	{
		delete [] Char;
	}
}



//
//	RangePositionsAreValid
//      Check to see if the range positions are valid for the string length set by the caller.  Note that the first position
//		may be greater than the last position, indicating that the range is in the reverse direction.
//
bool HSTRING::RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length ) const
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
bool HSTRING::RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition ) const
{
	return RangePositionsAreValid( FirstCharPosition, LastCharPosition, Size );
} // RangePositionsAreValid





//
//	RangeLength
//      Return the range length, where the range must be valid for the string length set by the caller.  Note that the first
//		position may be greater than the last position, indicating that the range is in the reverse direction.
//
unsigned int HSTRING::RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length ) const
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
unsigned int HSTRING::RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition ) const
{
	return RangeLength( FirstCharPosition, LastCharPosition, Size );
} // RangeLength





//
//	RangeDirection
//      Return the range direction, where the range must be valid for the string length set by the caller.  Note that the first
//		position may be greater than the last position, indicating that the range is in the reverse direction.
//
int HSTRING::RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length ) const
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
int HSTRING::RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition ) const
{
	return RangeDirection( FirstCharPosition, LastCharPosition, Size );
} // RangeDirection



//
// Reallocate
//      Resize the allocated space, copying the existing string to the new one.  Don't resize if the string will be too small
//		to retain existing data.
//
bool HSTRING::Reallocate(unsigned int NewDeclaredMaximumSize, bool AllowResizingToASmallerSize )
{
	bool	Status = true;	// No errors yet.
    unsigned char	*Temp;      // Temporary pointer to new string memory
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

    Temp = new unsigned char[NewDeclaredMaximumSize + 2];    // Leave space for a NULL.

	if(Temp != NULL)
	{
	    for(i=0; ((i < Size) && (i < NewDeclaredMaximumSize)); ++i)
		{
			Temp[i] = Char[i];
	    }

		Size = i;
	    MaximumSize = NewDeclaredMaximumSize;

		delete [] Char;
	    Char = Temp;
		Char[Size] = 0;
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
bool HSTRING::SmartReallocate(unsigned int NewSize)
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

				if(ResizeQuantity > MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE)
				{
					ResizeQuantity = MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE;
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
//		code to set string length before directly writing to Char.
//
bool HSTRING::Resize(unsigned int NewSize)
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
bool HSTRING::AppendFillChar(int InputCharacter, unsigned int NumberOfTimesToAppend)
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
		for(i=0; i<NumberOfTimesToAppend; ++i)
		{
			Char[i+Size] = ((unsigned char) (InputCharacter & 0xff));
		}
		Size += NumberOfTimesToAppend;

        Char[Size] = 0;

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
bool HSTRING::InsertFillChar(int InputCharacter, unsigned int NumberOfTimesToInsert)
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
        	Char[j--] = Char[i--];
        }

    // Now, insert the characters
		for(i = 0;    i < NumberOfTimesToInsert;    ++i)
		{
			Char[i] = ((unsigned char) (InputCharacter & 0xff));
		}

    	Size += NumberOfTimesToInsert;

        Char[Size] = 0;

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
bool HSTRING::CopyChar(int InputCharacter)
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
		Char[Size++] = ((unsigned char) (InputCharacter & 0xff));
        Char[Size] = 0;

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
bool HSTRING::AppendChar(int InputCharacter)
{
// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

   	SmartReallocate(Size + 1);

	if(Size < MaximumSize)
	{
		Char[Size++] = ((unsigned char) (InputCharacter & 0xff));
        Char[Size] = 0;

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
bool HSTRING::InsertNumber(int Position, unsigned char InputNumber, unsigned int Length)
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
			Char[Position++] = InputNumber;
			--Length;
		}

		while(Length)
		{
			Char[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			Char[Size] = 0;
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
bool HSTRING::InsertNumber(int Position, unsigned short InputNumber, unsigned int Length)
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
			Char[Position++] = ((unsigned char) ((InputNumber / Divisor) & 0xFF));
			Divisor *= 256;
			i--;
			--Length;
		}

		while(Length)
		{
			Char[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			Char[Size] = 0;
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
bool HSTRING::InsertNumber(int Position, unsigned int InputNumber, unsigned int Length)
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
			Char[Position++] = ((unsigned char) ((InputNumber / Divisor) & 0xFF));
			Divisor *= 256;
			i--;
			--Length;
		}

		while(Length)
		{
			Char[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			Char[Size] = 0;
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
bool HSTRING::InsertNumber(int Position, int InputNumber, unsigned int Length)
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
			Char[Position++] = ((unsigned char) ((InputNumber / Divisor) & 0xFF));
			Divisor *= 256;
			i--;
			--Length;
		}

		while(Length)
		{
			Char[Position++] = 0;
			--Length;
		}

		if(((unsigned int) Position) > Size)
		{
			Size = ((unsigned int) Position);
			Char[Size] = 0;
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
bool HSTRING::AppendNumber(unsigned char InputNumber, unsigned int Length)
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
bool HSTRING::AppendNumber(unsigned short InputNumber, unsigned int Length)
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
bool HSTRING::AppendNumber(unsigned int InputNumber, unsigned int Length)
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
bool HSTRING::AppendNumber(int InputNumber, unsigned int Length)
{
	return(InsertNumber(Size, InputNumber, Length));
}



// Copy operator (=) for HSTRING
HSTRING HSTRING::operator = (HSTRING StringToCopy)
{
	Copy(&StringToCopy);

	return *this;
}







// Append operator (+) for HSTRING
HSTRING HSTRING::operator + (HSTRING StringToAppend)
{
	HSTRING		Temp(StringToAppend.Size + Size, true);
	Temp.Copy(Char, Size);
//	Temp.Append(&StringToAppend);

	return Temp;
}



// Append operator (+) for char *
HSTRING HSTRING::operator + (const char *StringToAppend)
{
	HSTRING		Temp(strlen(StringToAppend) + Size, true);
	Temp.Copy(Char, Size);
//	Temp.Append(StringToAppend, strlen(StringToAppend));

	return Temp;
}




//
// Overloaded version #1 of string copy:  Copy another HSTRING over the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Copy(const HSTRING *StringToCopy)
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
			Char[i] = StringToCopy->Char[i];
		}
		Size = StringToCopy->Size;

        Char[Size] = 0;

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
bool HSTRING::Copy(const unsigned char *StringToCopy, unsigned int LengthOfStringToCopy)
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
			Char[i] = StringToCopy[i];
		}
		Size = LengthOfStringToCopy;

        Char[Size] = 0;

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
bool HSTRING::Copy(const unsigned char *StringToCopy)
{
    return(Copy(StringToCopy, ((unsigned int) (strlen(((char *) StringToCopy))))));
}





//
// Overloaded version #4 of string copy:  Copy a character string over the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Copy(const char *StringToCopy, unsigned int LengthOfStringToCopy)
{
    return(Copy(((unsigned char *) StringToCopy), LengthOfStringToCopy));
}





//
// Overloaded version #5 of string copy:  Copy a character string over the local string, using the NULL to
// determine length.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Copy(const char *StringToCopy)
{
    return(Copy(((unsigned char *) StringToCopy), ((unsigned int) (strlen(StringToCopy)))));
}





//
// Overloaded version #6 of string copy:  Copy a char* string in the range specified by the caller.
// Note that if the last position is before the first position, then the string will have to
// be reversed.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Copy(const char *StringToCopy, unsigned int LengthOfStringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition)
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
				Char[j++] = StringToCopy[i];
			}
		}
		else
		{
			i = FirstCharPosition;
			for(j = 0;    j < NewSize;    ++j)
			{
				Char[j] = StringToCopy[i];
				--i;
			}
		}

		Size = NewSize;

        Char[Size] = 0;

		return(true);
	}

	else
	{
		return(false);
	}
}





//
// Overloaded version #7 of string copy:  Copy an HSTRING in the range specified by the caller.
// Note that if the last position is before the first position, then the string will have to
// be reversed.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Copy(HSTRING *StringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition)
{
	return(Copy(((char *) StringToCopy->Char), StringToCopy->Size, FirstCharPosition, LastCharPosition));
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
bool HSTRING::CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, const char *StringToCopy,
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
			Char[i++] = StringToCopy[j];
		}
	}
	else
	{
		i = FirstCharPosition;
		for(j = 0;    j < NumberOfCharactersToCopy; ++j)
		{
			Char[i--] = StringToCopy[j];
		}
	}

    Char[Size] = 0;

	return(true);
}





//
// Overloaded version #2 of copy to range:  Copy an HSTRING to the range specified by the caller.
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
bool HSTRING::CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, HSTRING *StringToCopy)
{
	return(CopyToRange(FirstCharPosition, LastCharPosition, ((char *) StringToCopy->Char),
																StringToCopy->Size));
}






//
// Overloaded version #1 of string append:  Append another HSTRING to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Append(const HSTRING *StringToAppend)
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
			Char[i+Size] = StringToAppend->Char[i];
		}
		Size += StringToAppend->Size;

        Char[Size] = 0;

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
bool HSTRING::Append(const unsigned char *StringToAppend, unsigned int LengthOfStringToAppend)
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
			Char[i+Size] = StringToAppend[i];
		}
		Size += LengthOfStringToAppend;

        Char[Size] = 0;

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
bool HSTRING::Append(const char *StringToAppend)
{
	return(Append(((unsigned char *) StringToAppend), ((unsigned int) strlen(StringToAppend))));
}





//
// Overloaded version #4 of string append:  Append a character string to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Append(const char *StringToAppend, unsigned int LengthOfStringToAppend)
{
	return(Append(((unsigned char *) StringToAppend), LengthOfStringToAppend));
}





//
// Overloaded version #5 of string append:  Append a null terminated character string to the end of the local string.
//
// The resulting length must not exceed the maximum size of the string, or the
// operation will fail.
//
bool HSTRING::Append(const unsigned char *StringToAppend)
{
	return(Append(((unsigned char *) StringToAppend), ((unsigned int) strlen(((char *) StringToAppend)))));
}





//
//  Search the local string for a caller specified character, returning true if
//  found and false otherwise.
//
bool HSTRING::FindChar(int IntInputCharacter)
{
	unsigned int	i;
	unsigned char	InputCharacter;


	i = 0;
	InputCharacter = ((unsigned char) (IntInputCharacter & 0xff));
	while((i < Size) && (Char[i] != InputCharacter))
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
bool HSTRING::RemoveChar(int IntInputCharacter)
{
	unsigned int	i, j;
	unsigned char	InputCharacter;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	i = 0;
	InputCharacter = ((unsigned char) (IntInputCharacter & 0xff));
	while((i < Size) && (Char[i] != InputCharacter))
	{
		++i;
	}

	if(i < Size)
	{
		j = 0;
		++i;
		while(i < Size)
		{
			Char[j++] = Char[i++];
		}
		Size = j;

        Char[Size] = 0;

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
bool HSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned char *CopyDestination) const
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
//	    *CopyDestination += ((unsigned char) (((unsigned short) Char[IndexToStartOfCopyLocation++]) * Multiplier));
	    *CopyDestination = ((unsigned char) (*CopyDestination + ((unsigned char) (((unsigned short) Char[IndexToStartOfCopyLocation++]) * Multiplier))));
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
bool HSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned short *CopyDestination) const
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
//	    *CopyDestination += ((unsigned short) (((unsigned short) Char[IndexToStartOfCopyLocation++]) * Multiplier));
	    *CopyDestination = ((unsigned short) (*CopyDestination + ((unsigned short) (((unsigned short) Char[IndexToStartOfCopyLocation++]) * Multiplier))));
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
bool HSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned int *CopyDestination) const
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
	    *CopyDestination += ((unsigned int) (((unsigned int) Char[IndexToStartOfCopyLocation++]) * Multiplier));
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
bool HSTRING::CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   int *CopyDestination) const
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
	    *CopyDestination += ((int) (((int) Char[IndexToStartOfCopyLocation++]) * Multiplier));
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
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination,
										unsigned int MaximumDestinationLength) const
{
    bool        ReturnStatus;               //
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
	    *CopyDestination = Char[IndexToStartOfCopyLocation++];
        CopyDestination++;
	}


    return(ReturnStatus);
}





//
//	CopyFromString (overloaded version #2: unsigned short* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.  Otherwise, copy characters according to the requested or maximum length, whichever is
//		smaller.
//		Call overloaded version #1 with a recast destination.
//
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned short *CopyDestination,
										unsigned int MaximumDestinationLength) const
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((unsigned char *) CopyDestination), MaximumDestinationLength));
}





//
//	CopyFromString (overloaded version #3: unsigned int* output with maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.  Otherwise, copy characters according to the requested or maximum length, whichever is
//		smaller.
//		Call overloaded version #1 with a recast destination.
//
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination,
										unsigned int MaximumDestinationLength) const
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((unsigned char *) CopyDestination), MaximumDestinationLength));
}





//
//	CopyFromString (overloaded version #4: unsigned char* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination) const
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, CopyDestination, LengthToCopy));
}





//
//	CopyFromString (overloaded version #5: unsigned short* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned short *CopyDestination) const
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((unsigned char *) CopyDestination), LengthToCopy));
}





//
//	CopyFromString (overloaded version #6: unsigned int* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, return an
//		error.
//		Call overloaded version #1 with a recast destination and a maximum length equal to requested length to copy.
//
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination) const
{
	return(CopyFromString(IndexToStartOfCopyLocation, LengthToCopy, ((unsigned char *) CopyDestination), LengthToCopy));
}





//
//  CopyFromString (overloaded version #7: unsigned char* output with maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified maximum length, only copy up to the maximum length.  Return the number of unsigned chars
//      actually copied.
//
unsigned int HSTRING::CopyFromString(unsigned char *CopyDestination, unsigned int MaximumDestinationLength) const
{
	unsigned int		i;	// Index



    for(i=0; ((i < Size) && (i < MaximumDestinationLength)); ++i)
    {
        *CopyDestination = Char[i];
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
//	CopyFromString (overloaded version #8: HSTRING* output WITHOUT maximum length)
//		Copy characters from the local string to the caller specified location from the caller specified
//		index in the local string.  If there are not enough characters in the local string, copy what there
//      is.  Otherwise, copy characters according to the requested length.
//
bool HSTRING::CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, HSTRING *CopyDestination) const
{
    if((IndexToStartOfCopyLocation + LengthToCopy) > Size)
    {
        LengthToCopy = Size - IndexToStartOfCopyLocation;
    }

    return(CopyDestination->Copy(&Char[IndexToStartOfCopyLocation], LengthToCopy));
}




//
//  CopyFromString (overloaded version #9: HSTRING* output WITHOUT maximum length, copying the entire string)
//		Copy characters from the entire local string to the caller specified location.  If the local string is larger
//      than the caller specified HSTRING allows, only copy up to the maximum length.  Return true is successful,
//      false if the string was too long.
//
bool HSTRING::CopyFromString(HSTRING *CopyDestination) const
{
    return(CopyDestination->Copy(Char, Size));
}





// SimpleAsciiToUniCodeFormat
// 	Takes a string in ASCII format and translates into unicode, assuming LITTLE ENDIAN
//

bool HSTRING::SimpleAsciiToUniCodeFormat(void)
{
	unsigned int	uiCtr;
	unsigned int	wcSize = sizeof(wchar_t);
	wchar_t *pwcSerialString;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	pwcSerialString = new wchar_t[Size + 1];

	for(uiCtr=0;uiCtr<Size;uiCtr++)
		pwcSerialString[uiCtr]=Char[uiCtr];
	pwcSerialString[Size]=0;				//terminate this UNICODE string
	Copy((char *) pwcSerialString, (Size + 1) * wcSize);
	Size -= wcSize;

	delete [] pwcSerialString;

	return(true);
}





// UniCodeToSimpleAsciiFormat
// 	Takes a string in unicode format (16 or 32 bit) and strips the upper byte, assuming LITTLE ENDIAN
//

bool HSTRING::UniCodeToSimpleAsciiFormat(void)
{
	unsigned int	uiCtr;
	unsigned int	wcSize = sizeof(wchar_t);
// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	for(uiCtr=0;uiCtr<(Size / wcSize);uiCtr++)
		Char[uiCtr] = Char[uiCtr*wcSize];
	Size /= wcSize;
	Char[Size] = 0;

	return(true);
}





//
//  ConvertCharacterToHexFormat
//      Convert character at index sent by caller to the form '\XX', where XX is the 2 digit hexadecimal code
//      of the character.  Since the conversion will result in a larger string (each unprintable character
//      will now require four unsigned chars instead of one), return false if we ran out of room
//      and true otherwise.  If UseXInHexadecimalFormat is true, we'll insert an 'x' between
//		the '\' and the two hexadecimal digits.
//
bool HSTRING::ConvertCharacterToHexFormat( int *CharacterIndex )
{
    bool			ReturnStatus;           // Indicates whether or not we ran out of room.
	int				i;
    unsigned char	CharacterToConvert;     // Holds unprintable character to be converted to format string
	unsigned char	UpperNibble;			// Printable hexadecimal character corresponding to upper
											//	nibble of character being converted.
	unsigned char	LowerNibble;			// Printable hexadecimal character corresponding to lower
											//	nibble of character being converted.



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

	int		NumberOfNewCharacters = 2 + ( (UseXInHexadecimalFormat) ? 1 : 0 );
	SmartReallocate(Size + NumberOfNewCharacters );

// Shift everything from this point forward up to make space for the format string
	if(( Size + NumberOfNewCharacters ) <= MaximumSize )		// Is there enough room for the new format string?
	{
		CharacterToConvert = Char[ *CharacterIndex ];       // Save the character to be converted

		for(i=Size+NumberOfNewCharacters-1; i > (*CharacterIndex + NumberOfNewCharacters); i--)     // Make space for the format string
		{
			Char[i] = Char[i-NumberOfNewCharacters];
		}
		Size += NumberOfNewCharacters;

		Char[(*CharacterIndex)++] = '\\';                   // Create the format string.
		if( UseXInHexadecimalFormat )
		{
			Char[(*CharacterIndex)++] = 'x';
		}
		UpperNibble = ((unsigned char) (CharacterToConvert / 0x10));
		Char[(*CharacterIndex)++] = ((unsigned char) ((UpperNibble > 9) ? (UpperNibble + 'A' - 10) : (UpperNibble + '0')));
		LowerNibble = ((unsigned char) (CharacterToConvert & 0x0F));
		Char[(*CharacterIndex)++] = ((unsigned char) ((LowerNibble > 9) ? (LowerNibble + 'A' - 10) : (LowerNibble + '0')));
	}

	else            // Not enough room; return with error.
	{
		ReturnStatus = false;
	}

    Char[Size] = 0;

    return(ReturnStatus);
}





//
//  ConvertCharacterToBracketedHexFormat
//      Convert character at index sent by caller to the form '[0xXX]', where XX is the 2 digit hexadecimal code
//      of the character.  Since the conversion will result in a larger string (each unprintable character
//      will now require six unsigned chars instead of one), return false if we ran out of room
//      and true otherwise.
//
bool HSTRING::ConvertCharacterToBracketedHexFormat( int *CharacterIndex )
{
    bool			ReturnStatus;           // Indicates whether or not we ran out of room.
	int				i;
    unsigned char	CharacterToConvert;     // Holds unprintable character to be converted to format string
	unsigned char	UpperNibble;			// Printable hexadecimal character corresponding to upper
											//	nibble of character being converted.
	unsigned char	LowerNibble;			// Printable hexadecimal character corresponding to lower
											//	nibble of character being converted.



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

	int		NumberOfNewCharacters = 5;
	SmartReallocate(Size + NumberOfNewCharacters );

// Shift everything from this point forward up to make space for the format string
	if(( Size + NumberOfNewCharacters ) <= MaximumSize )		// Is there enough room for the new format string?
	{
		CharacterToConvert = Char[ *CharacterIndex ];       // Save the character to be converted

		for(i=Size+NumberOfNewCharacters-1; i > (*CharacterIndex + NumberOfNewCharacters); i--)     // Make space for the format string
		{
			Char[i] = Char[i-NumberOfNewCharacters];
		}
		Size += NumberOfNewCharacters;

		Char[(*CharacterIndex)++] = '[';                   // Create the format string.
		Char[(*CharacterIndex)++] = '0';
		Char[(*CharacterIndex)++] = 'x';
		UpperNibble = ((unsigned char) (CharacterToConvert / 0x10));
		Char[(*CharacterIndex)++] = ((unsigned char) ((UpperNibble > 9) ? (UpperNibble + 'A' - 10) : (UpperNibble + '0')));
		LowerNibble = ((unsigned char) (CharacterToConvert & 0x0F));
		Char[(*CharacterIndex)++] = ((unsigned char) ((LowerNibble > 9) ? (LowerNibble + 'A' - 10) : (LowerNibble + '0')));
		Char[(*CharacterIndex)++] = ']';                   // Create the format string.
	}

	else            // Not enough room; return with error.
	{
		ReturnStatus = false;
	}

    Char[Size] = 0;

    return(ReturnStatus);
}





//
//  ConvertControlCharacterToName
//      Convert control character at index sent by caller to a name.  Since the conversion will result in a larger
//		string (each unprintable character will now require five unsigned chars instead of one), return false if
//		we ran out of room and true otherwise.
//
#define	NAME_CHARS	3
#define	NAME_COUNT	32
bool HSTRING::ConvertControlCharacterToName( int *CharacterIndex )
{
    bool			ReturnStatus;           // Indicates whether or not we ran out of room.
	int				i;
    int				CharacterToConvert;     // Holds unprintable character to be converted to format string

	const char	CharacterNames[NAME_COUNT][NAME_CHARS+1] =
	{
		"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
		" BS"," HT"," LF"," VT"," FF"," CR"," SO"," SI",
		"DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
		"CAN"," EM","SUB","ESC"," FS"," GS"," RS"," US" };



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

	CharacterToConvert = (int) Char[ *CharacterIndex ];       // Save the character to be converted

	if( CharacterToConvert >= NAME_COUNT )
	{
		return false;
	}

	int		NumberOfNewCharacters = NAME_CHARS + 1;
	SmartReallocate(Size + NumberOfNewCharacters );

// Shift everything from this point forward up to make space for the format string
	if(( Size + NumberOfNewCharacters ) <= MaximumSize )		// Is there enough room for the new format string?
	{

		for(i=Size+NumberOfNewCharacters-1; i > (*CharacterIndex + NumberOfNewCharacters); i--)     // Make space for the format string
		{
			Char[i] = Char[i-NumberOfNewCharacters];
		}
		Size += NumberOfNewCharacters;

		Char[(*CharacterIndex)++] = '[';                   // Create the format string.
		Char[(*CharacterIndex)++] = CharacterNames[ CharacterToConvert ][ 0 ];
		Char[(*CharacterIndex)++] = CharacterNames[ CharacterToConvert ][ 1 ];
		Char[(*CharacterIndex)++] = CharacterNames[ CharacterToConvert ][ 2 ];
		Char[(*CharacterIndex)++] = ']';                   // Create the format string.
	}

	else            // Not enough room; return with error.
	{
		ReturnStatus = false;
	}

    Char[Size] = 0;

    return(ReturnStatus);
}





//
//  UnprintableCharactersToFormats (overload #1 with control over what is translated)
//      Convert each unprintable ASCII character in the local string to an unprintable
//      ASCII format string of the form '\XX', where XX is the 2 digit hexadecimal code
//      of the character.  Also, convert single '\' characters to two '\' characters.
//      Since the conversion will result in a larger string (each unprintable character
//      will now require four unsigned chars instead of one), return false if we ran out of room
//      and true otherwise.  If UseXInHexadecimalFormat is true, we'll insert an 'x' between
//		the '\' and the two hexadecimal digits.
//
bool HSTRING::UnprintableCharactersToFormats( bool TranslateControlCharacters, bool TranslateControlCharactersToHexadecimal,
		bool TranslateUsingBackslashHexadecimalFormat, bool TranslatePrintableASCII, bool TranslateExtendedASCII,
		bool ShowCRLFWhenControlCharactersAreTranslated )
{
    bool    ReturnStatus;           // Indicates whether or not we ran out of room.
    int		i;                      // Indices
    int		j;
	int		CRLFEncountered;		// Set to 2 when <CR> is encountered and decremented each time through the loop.
									//	If set to 1 when we encounter a <LF>, then we'll tack on a <CR><LF> after translation
									//	if instructed to do so by the caller.
	int		LFCREncountered;		// Set to 2 when <LF> is encountered and decremented each time through the loop.
									//	If set to 1 when we encounter a <CR>, then we'll tack on a <CR><LF> after translation
									//	if instructed to do so by the caller.



	CRLFEncountered = 0;
	LFCREncountered = 0;

// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

    ReturnStatus = true;        // We haven't run out of room yet.

// Process all characters; quit if we run out of space.
    i = 0;
    while((i < (int) Size) && (ReturnStatus))
    {
        if(( Char[i] == '\\' ) && ( !TranslatePrintableASCII ) &&
						( TranslateUsingBackslashHexadecimalFormat ))     // Convert single backslash to double backslash
        {
		   	SmartReallocate(Size + 1);

        // Shift everything from this point forward up by one unsigned char to make space for the extra backslash
            if((Size + 1) <= MaximumSize)           // Is there enough room for the new backslash?
            {
                for(j=Size; j > (i + 1); j--)     // Make space for the new backslash
                {
                    Char[j] = Char[j-1];
                }
                Size += 1;

                Char[i++] = '\\';                   // Create the double backslash.
                Char[i++] = '\\';                   // Create the double backslash.
            }

            else            // Not enough room; return with error.
            {
                ReturnStatus = false;
            }
        }
        else if((Char[i] < 32) && ( TranslateControlCharacters ))
        {
			bool	InsertCRLF = false;

			if( Char[ i ] == 13 )
			{
				if( LFCREncountered == 0 )
				{
					CRLFEncountered = 2;
				}
				else
				{
					LFCREncountered = 0;
					InsertCRLF = true;
				}
			}
			else if( Char[ i ] == 10 )
			{
				if( CRLFEncountered == 1 )
				{
					CRLFEncountered = 0;
					InsertCRLF = true;
				}
				else
				{
					LFCREncountered = 2;
				}
			}

			if( TranslateControlCharactersToHexadecimal )
			{
				if( TranslateUsingBackslashHexadecimalFormat )
				{
					ReturnStatus = ConvertCharacterToHexFormat( &i );
				}
				else
				{
					ReturnStatus = ConvertCharacterToBracketedHexFormat( &i );
				}
			}
			else
			{
				ReturnStatus = ConvertControlCharacterToName( &i );
			}

			if( InsertCRLF && ShowCRLFWhenControlCharactersAreTranslated )
			{
				this->Insert( "\r\n", i );
				i += 2;
			}
        }
        else if((Char[i] == 127) && ( TranslateControlCharacters ))
        {
			if( TranslateUsingBackslashHexadecimalFormat )
			{
				ReturnStatus = ConvertCharacterToHexFormat( &i );
			}
			else
			{
				ReturnStatus = ConvertCharacterToBracketedHexFormat( &i );
			}
        }
        else if((Char[i] > 127) && ( TranslateExtendedASCII ))
        {
			if( TranslateUsingBackslashHexadecimalFormat )
			{
				ReturnStatus = ConvertCharacterToHexFormat( &i );
			}
			else
			{
				ReturnStatus = ConvertCharacterToBracketedHexFormat( &i );
			}
        }
        else if((Char[i] >= 32) && (Char[i] <= 126) && ( TranslatePrintableASCII ))       // Unprintable character; convert it
        {
			if( TranslateUsingBackslashHexadecimalFormat )
			{
				ReturnStatus = ConvertCharacterToHexFormat( &i );
			}
			else
			{
				ReturnStatus = ConvertCharacterToBracketedHexFormat( &i );
			}
        }
        else        // Text character; leave it alone.
        {
            ++i;
        }

		if( CRLFEncountered > 0 )
		{
			--CRLFEncountered;
		}
		if( LFCREncountered > 0 )
		{
			--LFCREncountered;
		}
    }

    Char[Size] = 0;

    return(ReturnStatus);
}





//
//  UnprintableCharactersToFormats (overload #2)
//      Convert each unprintable ASCII character in the local string to an unprintable
//      ASCII format string of the form '\XX', where XX is the 2 digit hexadecimal code
//      of the character.  Also, convert single '\' characters to two '\' characters.
//      Since the conversion will result in a larger string (each unprintable character
//      will now require four unsigned chars instead of one), return false if we ran out of room
//      and true otherwise.  If UseXInHexadecimalFormat is true, we'll insert an 'x' between
//		the '\' and the two hexadecimal digits.
//
bool HSTRING::UnprintableCharactersToFormats(void)
{
    bool    ReturnStatus;           // Indicates whether or not we ran out of room.
    unsigned int   i;                      // Indices
    unsigned int   j;
    unsigned char	CharacterToConvert;     // Holds unprintable character to be converted to format string
	unsigned char	UpperNibble;			// Printable hexadecimal character corresponding to upper
									//	nibble of character being converted.
	unsigned char	LowerNibble;			// Printable hexadecimal character corresponding to lower
									//	nibble of character being converted.



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
        if(Char[i] == '\\')     // Convert single backslash to double backslash
        {
		   	SmartReallocate(Size + 1);

        // Shift everything from this point forward up by one unsigned char to make space for the extra backslash
            if((Size + 1) <= MaximumSize)           // Is there enough room for the new backslash?
            {
                for(j=Size; j > (i + 1); j--)     // Make space for the new backslash
                {
                    Char[j] = Char[j-1];
                }
                Size += 1;

                Char[i++] = '\\';                   // Create the double backslash.
                Char[i++] = '\\';                   // Create the double backslash.
            }

            else            // Not enough room; return with error.
            {
                ReturnStatus = false;
            }
        }
        else if((Char[i] < 32) || (Char[i] > 126))       // Unprintable character; convert it
        {
			int		NumberOfNewCharacters = 2 + ( (UseXInHexadecimalFormat) ? 1 : 0 );
			SmartReallocate(Size + NumberOfNewCharacters );

        // Shift everything from this point forward up to make space for the format string
            if((Size + NumberOfNewCharacters ) <= MaximumSize)		// Is there enough room for the new format string?
            {
                CharacterToConvert = Char[i];       // Save the character to be converted

                for(j=Size+1; j > (i + NumberOfNewCharacters); j--)     // Make space for the format string
                {
                    Char[j] = Char[j-NumberOfNewCharacters];
                }
                Size += NumberOfNewCharacters;

                Char[i++] = '\\';                   // Create the format string.
				if( UseXInHexadecimalFormat )
				{
					Char[i++] = 'x';
				}
                UpperNibble = ((unsigned char) (CharacterToConvert / 0x10));
				Char[i++] = ((unsigned char) ((UpperNibble > 9) ? (UpperNibble + 'A' - 10) : (UpperNibble + '0')));
                LowerNibble = ((unsigned char) (CharacterToConvert & 0x0F));
				Char[i++] = ((unsigned char) ((LowerNibble > 9) ? (LowerNibble + 'A' - 10) : (LowerNibble + '0')));
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

    Char[Size] = 0;

    return(ReturnStatus);
}






//
//  AllCharactersToFormats
//      Convert each ASCII character in the local string to an unprintable ASCII format
//		string of the form '\XX', where XX is the 2 digit hexadecimal code of the character.
//      Since the conversion will result in a larger string (each character will now require
//		four unsigned chars instead of one), return false if we ran out of room and true otherwise.
//		If UseXInHexadecimalFormat is true, we'll insert an 'x' between the '\' and the two
//		hexadecimal digits.
//
bool HSTRING::AllCharactersToFormats(void)
{
    bool    ReturnStatus;           // Indicates whether or not we ran out of room.
    unsigned int   i;                      // Indices
    unsigned int   j;
    unsigned char    CharacterToConvert;     // Holds character to be converted to format string
	unsigned char	UpperNibble;			// Printable hexadecimal character corresponding to upper
									//	nibble of character being converted.
	unsigned char	LowerNibble;			// Printable hexadecimal character corresponding to lower
									//	nibble of character being converted.



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
		int		NumberOfNewCharacters = 2 + ( (UseXInHexadecimalFormat) ? 1 : 0 );
	   	SmartReallocate(Size + NumberOfNewCharacters);

    // Shift everything from this point forward up to make space for the format string
        if((Size + NumberOfNewCharacters) <= MaximumSize)           // Is there enough room for the new format string?
        {
            CharacterToConvert = Char[i];       // Save the character to be converted

            for(j=Size+1; j > (i + NumberOfNewCharacters); j--)     // Make space for the format string
            {
                Char[j] = Char[j-NumberOfNewCharacters];
            }
            Size += NumberOfNewCharacters;

            Char[i++] = '\\';                   // Create the format string.
			if( UseXInHexadecimalFormat )
			{
				Char[i++] = 'x';
			}
            UpperNibble = ((unsigned char) (CharacterToConvert / 0x10));
			Char[i++] = ((unsigned char) ((UpperNibble > 9) ? (UpperNibble + 'A' - 10) : (UpperNibble + '0')));
            LowerNibble = ((unsigned char) (CharacterToConvert & 0x0F));
			Char[i++] = ((unsigned char) ((LowerNibble > 9) ? (LowerNibble + 'A' - 10) : (LowerNibble + '0')));
        }

        else            // Not enough room; return with error.
        {
        	ReturnStatus = false;
        }
    }

    Char[Size] = 0;

    return(ReturnStatus);
}






//
//  UnprintableFormatsToCharacters
//      Convert each unprintable ASCII format string in the form of "\XX" or "\xXX" back to
//      an unprintable ASCII character, where XX is the hexadecimal code of a value.
//      Also, two "\" in a row will be treated as one "\".
//
//      Using the same string for output as input works here, because the output
//      will never be longer than the input.
//
//      Return true if all format strings converted OK; false otherwise
//
bool HSTRING::UnprintableFormatsToCharacters(void)
{
    bool			ReturnStatus;	// Indicates whether or not we ran out of room.
    unsigned int    DecodedValue;   // Holds unprintable characters as they're decoded;
    unsigned int    i;              // Indices
    unsigned int    j;
    unsigned int    k;



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
        if(Char[i] != '\\')              // If the next character is not a '\', copy it.
        {
            Char[j++] = Char[i++];
        }
        else                                // Next character is '\', so start decoding.
        {
            ++i;
            if(i < Size)
            {
                if(Char[i] == '\\')      // If next character is also '\', then copy one '\' to output
                {
                    Char[j++] = Char[i++];
                }
                else                        // Next character wasn't '\', so it better be a number.
                {
					if(( i < Size ) && (( Char[i] == 'x' ) || ( Char[i] == 'X' )))
					{
					// Remove an 'x' character.
						++i;
					}
                    DecodedValue = 0;       // The next two characters had better be a hexadecimal number.
                    k = 0;
                    while((k < 2) && (i < Size) &&
                            (((Char[i] >= '0') && (Char[i] <= '9')) ||
                             ((Char[i] >= 'A') && (Char[i] <= 'F')) ||
                             ((Char[i] >= 'a') && (Char[i] <= 'f'))))
                    {
                        DecodedValue *= 0x10;
                        DecodedValue += (Char[i] <= '9') ? (((unsigned int) Char[i]) - '0') :
								(((unsigned int) (Char[i] & 0xDF)) - 'A' + 10);
						++i;
                        ++k;
                    }

                    if(k < 2)                       // If less than two digits were found, flag an error.
                    {
                        ReturnStatus = false;
                    }
                    else if(DecodedValue > 255)     // If two digits were found, but the number is too large, flag an error.
                    {
                        ReturnStatus = false;
                    }
                    else                            // Number decode was successful; copy it as a character to output position.
                    {
                        Char[j++] = ((unsigned char) DecodedValue);
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

    Char[Size] = 0;

    return ReturnStatus;
}
//---------------------------------------------------------------------------






//
//  BinaryToHex
//      Convert each ASCII character in the local string to a formatted two byte HEX representation.
//
bool HSTRING::BinaryToHex(void)
{
    bool    ReturnStatus;           // Indicates whether or not we ran out of room.
    unsigned int   i;                      // Indices
    unsigned int   j;
    unsigned char	CharacterToConvert;     // Holds unprintable character to be converted to format string
	unsigned char	UpperNibble;			// Printable hexadecimal character corresponding to upper
									//	nibble of character being converted.
	unsigned char	LowerNibble;			// Printable hexadecimal character corresponding to lower
									//	nibble of character being converted.



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
	   	SmartReallocate(Size + 1);

	// Shift everything from this point forward up by 1 unsigned char to make space for the format string
		if((Size + 1) <= MaximumSize)           // Is there enough room for the new format string?
        {
			CharacterToConvert = Char[i];       // Save the character to be converted

			for(j=Size; j > (i + 1); j--)     // Make space for the format string
			{
				Char[j] = Char[j-1];
			}
			++Size;

			UpperNibble = ((unsigned char) (CharacterToConvert / 0x10));
			Char[i++] = ((unsigned char) ((UpperNibble > 9) ? (UpperNibble + 'A' - 10) : (UpperNibble + '0')));
			LowerNibble = ((unsigned char) (CharacterToConvert & 0x0F));
			Char[i++] = ((unsigned char) ((LowerNibble > 9) ? (LowerNibble + 'A' - 10) : (LowerNibble + '0')));
		}

		else            // Not enough room; return with error.
		{
			ReturnStatus = false;
		}
    }

    Char[Size] = 0;

    return(ReturnStatus);
}






//
//  HexToBinary
//      Convert each formatted two byte HEX character representation in the local string to the ASCII equivalent value.
//
bool HSTRING::HexToBinary(void)
{
    bool			ReturnStatus;	// Indicates whether or not we ran out of room.
    unsigned int    DecodedValue;   // Holds unprintable characters as they're decoded;
    unsigned int    i;              // Indices
    unsigned int    j;
    unsigned int    k;



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
		DecodedValue = 0;       // The next two characters had better be a hexadecimal number.
		k = 0;
		while((k < 2) && (i < Size) &&
                            (((Char[i] >= '0') && (Char[i] <= '9')) ||
                             ((Char[i] >= 'A') && (Char[i] <= 'F')) ||
                             ((Char[i] >= 'a') && (Char[i] <= 'f'))))
		{
			DecodedValue *= 0x10;
			DecodedValue += (Char[i] <= '9') ? (((unsigned int) Char[i]) - '0') :
								(((unsigned int) (Char[i] & 0xDF)) - 'A' + 10);
			++i;
			++k;
		}

		if((k < 2) && (i < Size))		// If less than two digits were found, flag an error.
		{
			ReturnStatus = false;
		}
		else if(DecodedValue > 255)     // If two digits were found, but the number is too large, flag an error.
		{
			ReturnStatus = false;
		}
		else                            // Number decode was successful; copy it as a character to output position.
		{
			Char[j++] = ((unsigned char) DecodedValue);
		}
	}

    Size = j;       // Reflect new string size

    Char[Size] = 0;

    return ReturnStatus;
}
//---------------------------------------------------------------------------






//
//  QuotedHEXStringToBinary
//      Convert each formatted two byte HEX character representation in the local string to the ASCII equivalent value.
//		Any characters between quotes will not be translated as HEX characters, but will be stored directly into the
//		local string.
//
bool HSTRING::QuotedHEXStringToBinary(bool *IncompleteString)
{
    bool			ReturnStatus;	// Indicates whether or not we ran out of room.
    unsigned int    DecodedValue;   // Holds unprintable characters as they're decoded;
    unsigned int    i;              // Indices
    unsigned int    j;
    unsigned int    k;
	bool			InsideQuotes;	// Indicate when we're supposed to be looking for character data rather than
									//	HEX data.
	bool			ProcessingIncomplete;	// Indicate when we ran out of string before we found a closing quote or the
											//	second nibble of a HEX character.



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
		if( Char[i] == '"' )
		{
			InsideQuotes = !InsideQuotes;
			++i;
		}

		else if( InsideQuotes )
		{
			Char[ j++ ] = Char [ i++ ];
		}

		else
		{
			DecodedValue = 0;       // The next two characters had better be a hexadecimal number.
			k = 0;
			while((k < 2) && (i < Size) &&
                            (((Char[i] >= '0') && (Char[i] <= '9')) ||
                             ((Char[i] >= 'A') && (Char[i] <= 'F')) ||
                             ((Char[i] >= 'a') && (Char[i] <= 'f'))))
			{
				DecodedValue *= 0x10;
				DecodedValue += (Char[i] <= '9') ? (((unsigned int) Char[i]) - '0') :
								(((unsigned int) (Char[i] & 0xDF)) - 'A' + 10);
				++i;
				++k;
			}

			if((k < 2) && (i < Size))		// If less than two digits were found, flag an error.
			{
				ReturnStatus = false;
			}
			else if(DecodedValue > 255)     // If two digits were found, but the number is too large, flag an error.
			{
				ReturnStatus = false;
			}
			else                            // Number decode was successful; copy it as a character to output position.
			{
				Char[j++] = ((unsigned char) DecodedValue);

				if(( k < 2 ) && ( i == Size ))		// Indicate that we didn't get both nibbles.
				{
					ProcessingIncomplete = true;
				}
			}
		}
	}

    Size = j;       // Reflect new string size

    Char[Size] = 0;

	if( InsideQuotes )
		ProcessingIncomplete = true;

	if( IncompleteString != NULL )
		*IncompleteString = ProcessingIncomplete;

    return ReturnStatus;
} // QuotedHEXStringToBinary
//---------------------------------------------------------------------------




// Remove characters from the string within the requested index range.
bool HSTRING::Remove(unsigned int StartingIndexOfCharactersToBeRemoved, unsigned int NumberOfCharactersToBeRemoved)
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
        	Char[NextWritePosition++] = Char[NextReadPosition++];
        }

        Size = NextWritePosition;

        Char[Size] = 0;

    	ReturnStatus = true;
	}

    return(ReturnStatus);
}
//---------------------------------------------------------------------------




//
//	Move
//		Move characters from the one location to another within the string.
//
bool HSTRING::Move(unsigned int StartingIndexOfCharactersToBeMoved, unsigned int LocationToMoveTo,
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
    	unsigned char *MoveBuffer = new unsigned char[NumberOfCharactersToBeMoved];
        for(i = 0;    i < NumberOfCharactersToBeMoved;    ++i)
        {
            MoveBuffer[i] = Char[StartingIndexOfCharactersToBeMoved + i];
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
            	Char[--NextWritePosition] = Char[--NextReadPosition];
            }
        }
		else
        {
        // Shift upward
			NextReadPosition = StartingIndexOfCharactersToBeMoved + NumberOfCharactersToBeMoved;
			NextWritePosition = StartingIndexOfCharactersToBeMoved;
            while(NextWritePosition < LocationToMoveTo)
            {
            	Char[NextWritePosition++] = Char[NextReadPosition++];
            }
        }

    // Move the data being shifted to its' final destination.
        for(i = 0;    i < NumberOfCharactersToBeMoved;    ++i)
        {
            Char[LocationToMoveTo + i] = MoveBuffer[i];
        }

        delete [] MoveBuffer;

        Char[Size] = 0;

    	ReturnStatus = true;
	}

    return(ReturnStatus);
}
//---------------------------------------------------------------------------




// Remove all <CR>s, <LF>s, tabs, spaces, and nulls (overloaded version #1).
bool HSTRING::RemoveSpaceCharacters(void)
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
    	if((Char[NextLocationToRead] == ' ') || (Char[NextLocationToRead] == 9) || (Char[NextLocationToRead] == 0) ||
	    	 (Char[NextLocationToRead] == 13) || (Char[NextLocationToRead] == 10))
        {
			SpaceCharactersWereFoundAndRemoved = true;
        }
        else
        {
        	Char[NextLocationToWrite++] = Char[NextLocationToRead];
        }
    }

// Store the new size.
    Size = NextLocationToWrite;

    Char[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}



// Remove all <CR>s, <LF>s, tabs, spaces, and nulls up to caller specified character (overloaded version #2).
bool HSTRING::RemoveSpaceCharacters(int CharacterToRemoveUpTo)
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
			    		(NextLocationToRead < Size) && (Char[NextLocationToRead] != CharacterToRemoveUpTo);
    										    ++NextLocationToRead)
    {
    	if((Char[NextLocationToRead] == ' ') || (Char[NextLocationToRead] == 9) || (Char[NextLocationToRead] == 0) ||
	    	 (Char[NextLocationToRead] == 13) || (Char[NextLocationToRead] == 10))
        {
			SpaceCharactersWereFoundAndRemoved = true;
        }
        else
        {
        	Char[NextLocationToWrite++] = Char[NextLocationToRead];
        }
    }

// In case we quit because of reaching CharacterToRemoveUpTo, continue shifting the remainder of the string.
    while(NextLocationToRead < Size)
    {
    	Char[NextLocationToWrite++] = Char[NextLocationToRead++];
    }

// Store the new size.
    Size = NextLocationToWrite;

    Char[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}





// Remove all leading <CR>s, <LF>s, tabs, spaces, and nulls.
bool HSTRING::RemoveLeadingSpaceCharacters(void)
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
    	((Char[NextLocationToRead] == ' ') || (Char[NextLocationToRead] == 9) || (Char[NextLocationToRead] == 0) ||
    	 (Char[NextLocationToRead] == 13) || (Char[NextLocationToRead] == 10)))
    {
    	SpaceCharactersWereFoundAndRemoved = true;
	    ++NextLocationToRead;
    }


// Shift the remainder of the string.
	NextLocationToWrite = 0;
    while(NextLocationToRead < Size)
    {
    	Char[NextLocationToWrite++] = Char[NextLocationToRead++];
    }

// Store the new size.
    Size = NextLocationToWrite;

    Char[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}





// Remove all trailing <CR>s, <LF>s, tabs, spaces, and nulls.
bool HSTRING::RemoveTrailingSpaceCharacters(void)
{
	bool	SpaceCharactersWereFoundAndRemoved;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

	SpaceCharactersWereFoundAndRemoved = false;		// None found yet.

    while((Size > 0) &&
    	((Char[ Size - 1 ] == ' ') || (Char[ Size - 1 ] == 9) || (Char[ Size - 1 ] == 0) ||
    	 (Char[ Size - 1 ] == 13) || (Char[ Size - 1 ] == 10)))
    {
    	SpaceCharactersWereFoundAndRemoved = true;
	    --Size;
    }

    Char[Size] = 0;

    return(SpaceCharactersWereFoundAndRemoved);
}






//
//	CompareSubstring (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareSubstring(unsigned int LocalStringIndex, const unsigned char *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive)
{
	int		StringComparisonResult;
    unsigned int	i;
    unsigned char	LocalChar;
    unsigned char	InputChar;


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
//			StringComparisonResult = hhpstrncmp(((char *) InputString), ((char *) &Char[LocalStringIndex]),
//            																InputStringLength, true );
    		StringComparisonResult = 0;

	    // Do case sensitive compare.
    		for(i = 0;    (i < InputStringLength) && (StringComparisonResult == 0);    ++i)
        	{
	        	LocalChar = ((unsigned char) Char[i + LocalStringIndex]);
        		InputChar = ((unsigned char) InputString[i]);
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
	        	LocalChar = ((unsigned char) (((Char[i + LocalStringIndex] >= 97) && (Char[i + LocalStringIndex] <= 122)) ?
                				Char[i + LocalStringIndex] & 0xdf : Char[i + LocalStringIndex]));
        		InputChar = ((unsigned char) (((InputString[i] >= 97) && (InputString[i] <= 122)) ?
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
//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareSubstring(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(0L, InputString, InputStringLength, CompareIsCaseSensitive));
}






//
//	CompareSubstring (overloaded version #3, with a starting index into the local string and a
//		char * argument)
//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareSubstring(unsigned int LocalStringIndex, const char *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive)
{
	return(CompareSubstring(LocalStringIndex, ((unsigned char *) InputString), InputStringLength,
																	CompareIsCaseSensitive));
}





//	CompareSubstring (overloaded version #4, where starting index into the local string is assumed to be zero
//		and a char * argument)
//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareSubstring(const char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(0L, ((unsigned char *) InputString), InputStringLength, CompareIsCaseSensitive));
}






//
//	CompareSubstring (overloaded version #5, with a starting index into the local string and a
//		char * argument)
//		Compare the input HSTRING to the local HSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareSubstring(unsigned int LocalStringIndex, HSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(LocalStringIndex, InputString->Char, InputString->Size,
																	CompareIsCaseSensitive));
}





//	CompareSubstring (overloaded version #6, where starting index into the local string is assumed to be zero
//		and a char * argument)
//		Compare the input HSTRING to the local HSTRING up to the length of the input string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareSubstring(HSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareSubstring(0L, InputString->Char, InputString->Size, CompareIsCaseSensitive));
}





//
//	CompareOnShorter (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareOnShorter(unsigned int LocalStringIndex, const unsigned char *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive) const
{
	unsigned int	ShortestInputStringLength;
	int		StringComparisonResult;
    unsigned int	i;
    unsigned char	LocalChar;
    unsigned char	InputChar;


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
//			StringComparisonResult = hhpstrncmp(((char *) InputString), ((char *) &Char[LocalStringIndex]),
//            																ShortestInputStringLength, true );
    		StringComparisonResult = 0;

	    // Do case sensitive compare.
    		for(i = 0;    (i < ShortestInputStringLength) && (StringComparisonResult == 0);    ++i)
        	{
	        	LocalChar = ((unsigned char) Char[i + LocalStringIndex]);
        		InputChar = ((unsigned char) InputString[i]);
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
	        	LocalChar = ((unsigned char) (((Char[i + LocalStringIndex] >= 97) && (Char[i + LocalStringIndex] <= 122)) ?
                				Char[i + LocalStringIndex] & 0xdf : Char[i + LocalStringIndex]));
        		InputChar = ((unsigned char) (((InputString[i] >= 97) && (InputString[i] <= 122)) ?
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
//		Compare the input string to the local HSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareOnShorter(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const
{
	return(CompareOnShorter(0L, InputString, InputStringLength, CompareIsCaseSensitive));
}





//
//	CompareOnShorter (overloaded version #3, with a starting index into the local string)
//		Compare the input HSTRING to the local HSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareOnShorter(unsigned int LocalStringIndex, HSTRING *InputString, bool CompareIsCaseSensitive) const
{
	return(CompareOnShorter(LocalStringIndex, InputString->Char, InputString->Size, CompareIsCaseSensitive));
}






//
//	CompareOnShorter (overloaded version 4, where starting index into the local string is assumed to be zero)
//		Compare the input HSTRING to the local HSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.
//
int HSTRING::CompareOnShorter(HSTRING *InputString, bool CompareIsCaseSensitive) const
{
	return(CompareOnShorter(0L, InputString->Char, InputString->Size, CompareIsCaseSensitive));
}






//
//  Compare (overloaded version #1 with unsigned char* input and specified length).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HSTRING, then the result will be -1.
//
int HSTRING::Compare(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const
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
//  Compare (overloaded version #2 with HSTRING* input).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HSTRING, then the result will be -1.
//
int HSTRING::Compare(const HSTRING *InputString, bool CompareIsCaseSensitive) const
{
	return(Compare(InputString->Char, InputString->Size, CompareIsCaseSensitive));
}




//
//  Compare (overloaded version #3 with unsigned char* input).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HSTRING, then the result will be -1.
//
int HSTRING::Compare(const unsigned char *InputString, bool CompareIsCaseSensitive) const
{
	return(Compare(InputString, ((unsigned int) strlen(((char *) InputString))), CompareIsCaseSensitive));
}




//
//  Compare (overloaded version #4 with char* input and specified length).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HSTRING, then the result will be -1.
//
int HSTRING::Compare(const char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const
{
	return(Compare(((unsigned char *) InputString), InputStringLength, CompareIsCaseSensitive));
}




//
//  Compare (overloaded version #5 with char* input).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter thanthe local HSTRING, then the result will be -1.
//
int HSTRING::Compare(const char *InputString, bool CompareIsCaseSensitive) const
{
	return(Compare(((unsigned char *) InputString), ((unsigned int) strlen(InputString)), CompareIsCaseSensitive));
}





//
//	Compare the input string to the local HSTRING up to the input length (overloaded version #1 with unsigned char* input
//	and specified length).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HSTRING::CompareFixedInputLength(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const
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
//	Compare the input string to the local HSTRING up to the length of the input HSTRING (overloaded version #2
//	with HSTRING* input).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HSTRING::CompareFixedInputLength(HSTRING *InputString, bool CompareIsCaseSensitive) const
{
	return(CompareFixedInputLength(InputString->Char, InputString->Size, CompareIsCaseSensitive));
}




//
//	Compare the input string to the local HSTRING up to the length of the input unsigned char string (overloaded
//	version #3 with unsigned char* input).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HSTRING::CompareFixedInputLength(const unsigned char *InputString, bool CompareIsCaseSensitive) const
{
	return(CompareFixedInputLength(InputString, ((unsigned int) strlen(((char *) InputString))), CompareIsCaseSensitive));
}




//
//	Compare the input string to the local HSTRING up to the input length (overloaded version #4 with char* input
//	and specified length).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HSTRING::CompareFixedInputLength(const char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const
{
	return(CompareFixedInputLength(((unsigned char *) InputString), InputStringLength, CompareIsCaseSensitive));
}




//
//	Compare the input string to the local HSTRING up to the length of the input char string (overloaded
//	version #5 with char* input).
//		Compare the input string to the local HSTRING.  This routine returns a value < 0 when the input string
//		is less than the local HSTRING, = 0 when they are exactly the same, and > 0 when the input string is
//		greater than the local HSTRING.  If the strings are not of equal length, then the result is computed
//		in the following manner by comparing the strings up to the length of the smaller of the two, and if
//		the result is that they're equal to that point, then the result will be computed based on string length
//		in the following manner:
//		1) If the input string is longer than the local HSTRING, then the result will be 1.
//		2) If the input string is shorter than the local HSTRING, then the result will be 0 when they are equal
//			up to the length of the input string.
//
int HSTRING::CompareFixedInputLength(const char *InputString, bool CompareIsCaseSensitive) const
{
	return(CompareFixedInputLength(((unsigned char *) InputString), ((unsigned int) strlen(InputString)), CompareIsCaseSensitive));
}





//
// FindString (overloaded version #1 with a unsigned char input string).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HSTRING::FindString(const unsigned char *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound) const
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
// FindString (overloaded version #2 with an input HSTRING).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HSTRING::FindString(HSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound) const
{
	return(FindString(InputString->Char, InputString->Size, FindIsCaseSensitive,
                				OccurrenceNumberToFindOfInputString, PositionWhereInputStringWasFound));
}





//
// Find (overloaded version #1 with a unsigned char input string).
//		Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HSTRING::Find(const unsigned char *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound) const
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
// Find (overloaded version #2 with an input HSTRING).
//		Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.
//
bool HSTRING::Find(HSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound) const
{
	return(Find(InputString->Char, InputString->Size, FindIsCaseSensitive,
                				OccurrenceNumberToFindOfInputString, PositionWhereInputStringWasFound));
}




//
//	AutoResizeOn
//		Turn on autoresize
//
void HSTRING::AutoResizeOn(void)
{
	AutoResize = true;
}





//
//	AutoResizeOff
//		Turn off autoresize
//
void HSTRING::AutoResizeOff(void)
{
	AutoResize = false;
}




// Overloaded version #1 of Insert:  Insert a string at the caller specified location
void HSTRING::Insert(const unsigned char *StringToInsert, unsigned int SourceLength, unsigned int PositionToInsertAt)
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
            	Char[--i] = Char[--j];
            }

	    // Copy the string
    		for(i = 0;    i < SourceLength;    ++i)
        	{
				Char[PositionToInsertAt++] = StringToInsert[i];
	        }

    	    Size += SourceLength;

			Char[Size] = 0;
        }
    }

    return;
}




// Overloaded version #2 of Insert:  Insert a string at the caller specified location
void HSTRING::Insert(HSTRING *StringToInsert, unsigned int PositionToInsertAt)
{
	Insert(StringToInsert->Char, StringToInsert->Size, PositionToInsertAt);

    return;
}




// Overloaded version #3 of Insert:  Insert a string at the caller specified location
void HSTRING::Insert(const unsigned char *StringToInsert, unsigned int PositionToInsertAt)
{
	Insert(StringToInsert, ((unsigned int) strlen(((char *) StringToInsert))), PositionToInsertAt);

    return;
}




// Overloaded version #4 of Insert:  Insert a string at the caller specified location
void HSTRING::Insert(const char *StringToInsert, unsigned int SourceLength, unsigned int PositionToInsertAt)
{
	Insert(((unsigned char *) StringToInsert), SourceLength, PositionToInsertAt);

    return;
}




// Overloaded version #5 of Insert:  Insert a string at the caller specified location
void HSTRING::Insert(const char *StringToInsert, unsigned int PositionToInsertAt)
{
	Insert(((unsigned char *) StringToInsert), ((unsigned int) strlen(StringToInsert)), PositionToInsertAt);

    return;
}





//
//	GetNumber (overloaded version #1 -> get an integer parameter (positive or negative)
//		Process the next number and comma in the format specifier, removing those characters from the format
// 		specifier and returning the resulting number to the caller.  This routine assumes that all nulls and
// 		spaces have been removed from the format specifier prior to invoking this routine.
//
bool HSTRING::GetNumber(int *NumericParameterValue)
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
	else if(Char[0] == '-')
    {
    	++i;
        NegateTheResult = true;
		if((i < Size) && (!HSTRING::hhpisdigit(Char[i])))
		{
			Status = false;
		}
    }

// If first character is '+', remove it and verify that a digit follows.
	else if(Char[0] == '+')
    {
    	++i;
 	    if((i < Size) && (!HSTRING::hhpisdigit(Char[i])))
		{
			Status = false;
		}
    }

// Verify that the first character is a digit.
    else if(!HSTRING::hhpisdigit(Char[0]))
	{
		Status = false;
	}


    if(Status)
    {
		*NumericParameterValue = 0;

// Process all numeric digits and store the result.
		while((i < Size) && (HSTRING::hhpisdigit(Char[i])))
		{
			*NumericParameterValue = *NumericParameterValue * 10 +
								((int) (Char[i] - '0'));
			++i;
		}

// If the next character is a comma, remove it.
		if((i < Size) && (Char[i] == ','))
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
bool HSTRING::GetNumber(unsigned int *NumericParameterValue)
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
    else if(!HSTRING::hhpisdigit(Char[0]))
	{
		Status = false;
	}


    if(Status)
    {
		*NumericParameterValue = 0;

// Process all numeric digits and store the result.
		while((i < Size) && (HSTRING::hhpisdigit(Char[i])))
		{
			*NumericParameterValue = *NumericParameterValue * 10 +
								((int) (Char[i] - '0'));
			++i;
		}

// If the next character is a comma, remove it.
		if((i < Size) && (Char[i] == ','))
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
//		Compare the input string to the local HSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length), using the '*', '?', and '#' wildcards in the local string.  This routine
//		returns true if the strings match and false otherwise.
//
bool HSTRING::CompareOnShorterWithWildcards(unsigned int LocalStringIndex, const unsigned char *InputString, unsigned int InputStringLength,
				bool CompareIsCaseSensitive, unsigned int *NextPositionInInputStringBeyondSuccessfulCompare)
{
	bool	StringComparisonResult;
    unsigned int	i, j;
    unsigned char	LocalChar;
    unsigned char	InputChar;




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
        	LocalChar = ((unsigned char) ((CompareIsCaseSensitive) ? Char[i] :
            			(((Char[i] >= 97) && (Char[i] <= 122)) ? Char[i] & 0xdf : Char[i])));
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
            	    	if(!(StringComparisonResult))
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
                	if((Char[i] == '^') || (Char[i] == '*') || (Char[i] == '?') || (Char[i] == '#'))
		            {
	    		    	LocalChar = ((unsigned char) ((CompareIsCaseSensitive) ? Char[i] :
            				(((Char[i] >= 97) && (Char[i] <= 122)) ? Char[i] & 0xdf : Char[i])));
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
			if(Char[i] == '*')
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
//		Compare the input string to the local HSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length), using the '*', '?', and '#' wildcards in the local string.  This routine
//		returns true if the strings match and false otherwise.
//
bool HSTRING::CompareOnShorterWithWildcards(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive,
				unsigned int *NextPositionInInputStringBeyondSuccessfulCompare)
{
	return(CompareOnShorterWithWildcards(((unsigned int) 0L), InputString, InputStringLength, CompareIsCaseSensitive,
    														NextPositionInInputStringBeyondSuccessfulCompare));
}






//
//  CompareWithWildcards (overloaded version #1 with unsigned char* input).
//		Compare the input string to the local HSTRING, using the '*', '?', and '#' wildcards.  This routine returns
//		a value of false when the local HSTRING is not found in the input string, false when the local HSTRING is
//		found in the input string leaving characters left over at the end of the input string, and true otherwise
//		(exact comparison).
//
bool HSTRING::CompareWithWildcards(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive)
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
//  CompareWithWildcards (overloaded version #2 with HSTRING* input).
//		Compare the input string to the local HSTRING, using the '*', '?', and '#' wildcards.  This routine returns
//		a value of false when the local HSTRING is not found in the input string, false when the local HSTRING is
//		found in the input string leaving characters left over at the end of the input string, and true otherwise
//		(exact comparison).
//
bool HSTRING::CompareWithWildcards(HSTRING *InputString, bool CompareIsCaseSensitive)
{
	return(CompareWithWildcards(InputString->Char, InputString->Size, CompareIsCaseSensitive));
}





//
// FindWildcardString (overloaded version #1 with a unsigned char input string).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.  Wildcards '*', '?', and '#' are processed.
//
bool HSTRING::FindWildcardString(const unsigned char *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
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
    	if(Char[i] == '^')
        {
            ++i;
        	if((i + 1) < Size)
            {
        		++SizeMinusWildcards;
	            ++i;
            }
        }
    	else if(Char[i] == '*')
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
// FindWildcardString (overloaded version #2 with an input HSTRING).
//		Search the input string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the local string.
//		If OccurrenceNumberToFindOfInputString is negative, search for the abs(nth) position starting from
//		the end, else start from the beginning.  Wildcards '*', '?', and '#' are processed.
//
bool HSTRING::FindWildcardString(HSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound)
{
	return(FindWildcardString(InputString->Char, InputString->Size, FindIsCaseSensitive,
                				OccurrenceNumberToFindOfInputString, PositionWhereInputStringWasFound));
}







//
//	CopyToOffset (overloaded version #1: unsigned char* input)
//		Copy characters to the local string at the caller specified location from the caller specified
//		index in the input string.  If there is not enough room in the local string, autoresize (if enabled)
//      or return an error.  Otherwise, copy characters.
//
bool HSTRING::CopyToOffset(unsigned int IndexToStartOfCopyLocation, const unsigned char *InputString, unsigned int LengthToCopy)
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
        	Char[i + IndexToStartOfCopyLocation] = InputString[i];
        }

		Char[Size] = 0;

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
bool HSTRING::FindCharacterForward(unsigned char Character, unsigned int StartIndex,
								   int *PositionWhereCharacterWasFound) const
{
	bool	CharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereCharacterWasFound = StartIndex;

	// Keep searching until we find the character or we run out of string.
		while((!CharacterFound) && (*PositionWhereCharacterWasFound < ((int) Size)))
		{
			if(Char[*PositionWhereCharacterWasFound] == Character)
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
bool HSTRING::FindCharacterBackward(unsigned char Character, unsigned int StartIndex,
								   int *PositionWhereCharacterWasFound) const
{
	bool	CharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereCharacterWasFound = StartIndex;

	// Keep searching until we find the character or we run out of string.
		while((!CharacterFound) && (*PositionWhereCharacterWasFound >= 0))
		{
			if(Char[*PositionWhereCharacterWasFound] == Character)
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
bool HSTRING::FindNonCharacterForward(unsigned char Character, unsigned int StartIndex,
								   int *PositionWhereNonCharacterWasFound) const
{
	bool	NonCharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereNonCharacterWasFound = StartIndex;

	// Keep searching until we find the non-character or we run out of string.
		while((!NonCharacterFound) && (*PositionWhereNonCharacterWasFound < ((int) Size)))
		{
			if(Char[*PositionWhereNonCharacterWasFound] != Character)
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
bool HSTRING::FindNonCharacterBackward(unsigned char Character, unsigned int StartIndex,
								   int *PositionWhereNonCharacterWasFound) const
{
	bool	NonCharacterFound = false;		// Not found yet


// Only do the search if the start index is in range
	if(StartIndex < Size)
	{
		*PositionWhereNonCharacterWasFound = StartIndex;

	// Keep searching until we find the non-character or we run out of string.
		while((!NonCharacterFound) && (*PositionWhereNonCharacterWasFound >= 0))
		{
			if(Char[*PositionWhereNonCharacterWasFound] != Character)
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
int HSTRING::MaximumLength(void) const
{
	return(MaximumSize);
}	// MaximumLength





//
//	ReplaceAll
//		Replace all occurrences of a string
//
bool HSTRING::ReplaceAll(const char *StringToReplace, const char *ReplacementString)
{
    bool	Status = true;				// Set to false if we run out of space, true otherwise.
    int		NextSearchPosition = 0;



// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return false;
	}

// Keep searching for the source string until we run out of local string
	while(((NextSearchPosition + strlen(StringToReplace)) <= Size) && (Status))
	{
		if(CompareOnShorter(NextSearchPosition, ((unsigned char *) StringToReplace), strlen(StringToReplace), true) == 0)
		{
			Status = Remove(NextSearchPosition, strlen(StringToReplace));
			Insert(ReplacementString, NextSearchPosition);
			NextSearchPosition += strlen(ReplacementString);
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
void HSTRING::FindFirstNonSpaceCharacter(int StartingIndex,
										 int *PositionWhereFirstNonSpaceCharacterWasFound)
{
	bool	NonSpaceCharacterFound=false;	// Haven't found a non-space character yet.


// Keep moving until we encounter a non-space character.
	*PositionWhereFirstNonSpaceCharacterWasFound = StartingIndex;
	while((!NonSpaceCharacterFound) && (*PositionWhereFirstNonSpaceCharacterWasFound < ((int) Size)))
	{
	// Ignore blanks, <TAB>s, <CR>s, <LF>s, and <FF>s.
		if((Char[*PositionWhereFirstNonSpaceCharacterWasFound] == ' ') ||
			(Char[*PositionWhereFirstNonSpaceCharacterWasFound] == 9) ||
			(Char[*PositionWhereFirstNonSpaceCharacterWasFound] == 10) ||
			(Char[*PositionWhereFirstNonSpaceCharacterWasFound] == 12) ||
			(Char[*PositionWhereFirstNonSpaceCharacterWasFound] == 13))
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
int HSTRING::ConvertToNumber(int StartingPosition, int EndingPosition, int *NumberOfCharactersUsedInConversion)
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
					(Char[NextPositionToCheck] == '+'))
	{
		NumberIsPositive = true;
		++NextPositionToCheck;
		FindFirstNonSpaceCharacter(NextPositionToCheck, ((int *) &NextPositionToCheck));
	}
	else if((NextPositionToCheck <= EndingPosition) &&
					(Char[NextPositionToCheck] == '-'))
	{
		NumberIsPositive = false;
		++NextPositionToCheck;
		FindFirstNonSpaceCharacter(NextPositionToCheck, ((int *) &NextPositionToCheck));
	}


// Get the number
	while((NextPositionToCheck <= EndingPosition) &&
					(Char[NextPositionToCheck] >= '0') &&
					(Char[NextPositionToCheck] <= '9') &&
					(NumberOfDigitsFound < 10))
	{
		ConvertedNumber = (ConvertedNumber * 10) + ((int) (Char[NextPositionToCheck] - '0'));
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
int HSTRING::ConvertToNumber(int StartingPosition, int *NumberOfCharactersUsedInConversion)
{
	return(ConvertToNumber(StartingPosition, Size - 1, NumberOfCharactersUsedInConversion));
} // ConvertToNumber (overloaded version #2)







//
//	ConvertHexToNumber (overloaded version #1 using a length limit).
//		Return a decimal number converted from the local string starting at the caller specified
//		location, where the string is assumed to be in hexadecimal format.
//
int HSTRING::ConvertHexToNumber(int StartingPosition, int EndingPosition, int *NumberOfCharactersUsedInConversion)
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
					(((Char[NextPositionToCheck] >= '0') && (Char[NextPositionToCheck] <= '9')) ||
						((Char[NextPositionToCheck] >= 'A') && (Char[NextPositionToCheck] <= 'F')) ||
						((Char[NextPositionToCheck] >= 'a') && (Char[NextPositionToCheck] <= 'f'))) &&
					(NumberOfDigitsFound < 8))
	{
		if((Char[NextPositionToCheck] >= '0') && (Char[NextPositionToCheck] <= '9'))
		{
			HexCharacterCode = ((int) (Char[NextPositionToCheck] - '0'));
		}
		else if((Char[NextPositionToCheck] >= 'A') && (Char[NextPositionToCheck] <= 'F'))
		{
			HexCharacterCode = ((int) (Char[NextPositionToCheck] - 'A' + 10));
		}
		else
		{
			HexCharacterCode = ((int) (Char[NextPositionToCheck] - 'a' + 10));
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
int HSTRING::ConvertHexToNumber(int StartingPosition, int *NumberOfCharactersUsedInConversion)
{
	return(ConvertHexToNumber(StartingPosition, Size - 1, NumberOfCharactersUsedInConversion));
} // ConvertHexToNumber (overloaded version #2)





//
//	UpperCase
//		Convert local string to upper case
//
void HSTRING::UpperCase(void)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return;
	}

	for(i = 0;    i < Size;    ++i)
	{
		if((Char[i] >= 'a') && (Char[i] <= 'z'))
		{
			Char[i] &= 0xDF;
		}
	}

	return;
} // UpperCase





//
//	LowerCase
//		Convert local string to upper case
//
void HSTRING::LowerCase(void)
{
	unsigned int	i;


// If this string shouldn't be writable, WOOF!
	if( ReadOnly )
	{
		return;
	}

	for(i = 0;    i < Size;    ++i)
	{
		if((Char[i] >= 'A') && (Char[i] <= 'Z'))
		{
			Char[i] |= 0x20;
		}
	}

	return;
} // LowerCase




//
//	RangeCheck
//		Check the current string to see if all characters fall within the specified range.  Multiple (up to 15
//		ranges) may be selected.
//
bool HSTRING::RangeCheck(int LowRange1, int HighRange1, int LowRange2, int HighRange2, 
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

			if(((int) Char[j] >= NextLowRangeValue) && ((int) Char[j] <= NextHighRangeValue))
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
//	hhpisdigit
//		Static member function to determine if input character is a numeric digit.  Used in place of C library isdigit
//		function, which is not available on all platforms.
//
int HSTRING::hhpisdigit( int ch )
{
    return( ((ch >= '0') && (ch <= '9')) ? 1 : 0 );
} // hhpisdigit






//
//	hhpstrcmp
//		Static member function to do a case sensitive character compare.  Input strings are assumed to be null terminated
//		and the number of character to compare is based on the shortest input string length.  Used in place of C library
//		stricmp function, which is not available on all platforms.
//
//		There is one difference between this and strcmp: this routine may optionally be instructed to compare the entire
//		strings, meaning that if the lengths aren't equal, but the strings are equal up to the end of the shorter string,
//		a non-zero value will be returned.
//
int HSTRING::hhpstrcmp(const char *string1, const char *string2, bool CompareEntireString )
{
	int		StringComparisonResult;
    int		i;
    char	Char1;
    char	Char2;
	int		LengthString1 = strlen(string1);
	int		LengthString2 = strlen(string2);


	StringComparisonResult = 0;

	for(i = 0;    (i < LengthString1) && (i < LengthString2) && (StringComparisonResult == 0);    ++i)
    {
		Char1 = ((unsigned char) string1[i]);
		Char2 = ((unsigned char) string2[i]);
        if(Char1 < Char2)
	    {
			StringComparisonResult = -1;
    	}
        else if(Char1 > Char2)
        {
			StringComparisonResult = 1;
        }
    }

	if(StringComparisonResult == 0)
	{
		if( CompareEntireString )
		{
			if(i < LengthString1)
			{
				StringComparisonResult = 1;
			}
			else if(i < LengthString2)
			{
				StringComparisonResult = -1;
			}
		}
	}

	return(StringComparisonResult);
} // hhpstrcmp






//
//	hhpstrncmp
//		Static member function to do a case sensitive character compare.  Number of characters to compare is specified
//		by the caller.  Used in place of C library strncmp function, which is not available on all platforms.
//
//		There is one difference between this and strncmp: this routine may optionally be instructed to compare the entire
//		strings, meaning that it won't quit if it finds a NULL in one of the strings before it reaches the character count.
//
int HSTRING::hhpstrncmp(const char *string1, const char *string2, unsigned int count, bool CompareEntireString )
{
	int		StringComparisonResult;
    int		i;
    char	Char1;
    char	Char2;

	int		LengthToCompare = count;
	if( !CompareEntireString )
	{
		if( (int) strlen( string1 ) < LengthToCompare )
		{
			LengthToCompare = strlen( string1 );
		}
		if( (int) strlen( string2 ) < LengthToCompare )
		{
			LengthToCompare = strlen( string2 );
		}
	}

	StringComparisonResult = 0;

	for(i = 0;    (i < LengthToCompare) && (StringComparisonResult == 0);    ++i)
    {
		Char1 = ((unsigned char) string1[i]);
		Char2 = ((unsigned char) string2[i]);
        if(Char1 < Char2)
	    {
			StringComparisonResult = -1;
    	}
        else if(Char1 > Char2)
        {
			StringComparisonResult = 1;
        }
    }

	return(StringComparisonResult);
} // hhpstrncmp






//
//	hhpstricmp
//		Static member function to do a case insensitive character compare.  Input strings are assumed to be null terminated
//		and the number of character to compare is based on the shortest input string length.  Used in place of C library
//		stricmp function, which is not available on all platforms.
//
//		There is one difference between this and stricmp: this routine may optionally be instructed to compare the entire
//		strings, meaning that if the lengths aren't equal, but the strings are equal up to the end of the shorter string,
//		a non-zero value will be returned.
//
int HSTRING::hhpstricmp(const char *string1, const char *string2, bool CompareEntireString )
{
	int		StringComparisonResult;
    int		i;
    char	Char1;
    char	Char2;
	int		LengthString1 = strlen(string1);
	int		LengthString2 = strlen(string2);


	StringComparisonResult = 0;

	for(i = 0;    (i < LengthString1) && (i < LengthString2) && (StringComparisonResult == 0);    ++i)
    {
		Char1 = ((unsigned char) (((string1[i] >= 97) && (string1[i] <= 122)) ? (string1[i] & 0xdf) : string1[i]));
		Char2 = ((unsigned char) (((string2[i] >= 97) && (string2[i] <= 122)) ? (string2[i] & 0xdf) : string2[i]));
        if(Char1 < Char2)
	    {
			StringComparisonResult = -1;
    	}
        else if(Char1 > Char2)
        {
			StringComparisonResult = 1;
        }
    }

	if(StringComparisonResult == 0)
	{
		if( CompareEntireString )
		{
			if(i < LengthString1)
			{
				StringComparisonResult = 1;
			}
			else if(i < LengthString2)
			{
				StringComparisonResult = -1;
			}
		}
	}

	return(StringComparisonResult);
} // hhpstricmp






//
//	hhpstrnicmp
//		Static member function to do a case insensitive character compare.  Number of characters to compare is specified
//		by the caller.  Used in place of C library strnicmp function, which is not available on all platforms, with one
//		difference: if one string is shorter than the other, and the strings compare to the length of the shorter, we'll
//		return a non-zero value to indicate that they were not equal.
//
//		There is one difference between this and strnicmp: this routine may optionally be instructed to compare the entire
//		strings, meaning that it won't quit if it finds a NULL in one of the strings before it reaches the character count.
//
int HSTRING::hhpstrnicmp(const char *string1, const char *string2, unsigned int count, bool CompareEntireString )
{
	int		StringComparisonResult;
    int		i;
    char	Char1;
    char	Char2;


	int		LengthToCompare = count;
	if( !CompareEntireString )
	{
		if( (int) strlen( string1 ) < LengthToCompare )
		{
			LengthToCompare = strlen( string1 );
		}
		if( (int) strlen( string2 ) < LengthToCompare )
		{
			LengthToCompare = strlen( string2 );
		}
	}


	StringComparisonResult = 0;

	for(i = 0;    (i < LengthToCompare) && (StringComparisonResult == 0);    ++i)
    {
		Char1 = ((unsigned char) (((string1[i] >= 97) && (string1[i] <= 122)) ? string1[i] & 0xdf : string1[i]));
		Char2 = ((unsigned char) (((string2[i] >= 97) && (string2[i] <= 122)) ? string2[i] & 0xdf : string2[i]));
        if(Char1 < Char2)
	    {
			StringComparisonResult = -1;
    	}
        else if(Char1 > Char2)
        {
			StringComparisonResult = 1;
        }
    }

	return(StringComparisonResult);
} // hhpstrnicmp






//
//	ParseRevisionString (version #1, using HSTRING input)
//		Static member function to parse a version string into numeric segments.  Returns true if the entire string was
//		consumed, false otherwise.
//
bool HSTRING::ParseRevisionString( HSTRING *InputString, int *AmountOfCharactersConsumed,
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
					( InputString->Char[ *AmountOfCharactersConsumed ] == '.' ))
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
bool HSTRING::ParseRevisionString( const char *InputString, int InputStringLength, int *AmountOfCharactersConsumed,
								  int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments )
{
	HSTRING		hstrInputString( (unsigned char *) InputString, (unsigned int) InputStringLength, false, true, true );
	return ParseRevisionString( &hstrInputString, AmountOfCharactersConsumed, MaximumNumberOfVersionSegments,
					NumberOfVersionSegments, VersionSegments );
} // ParseRevisionString (version #2, using character string input)




// $Log: hstring.cpp  $
// Revision 1.56 2011/04/27 14:56:09EDT Rosetti,James (E412202) 
// Added const keyword to parameters and methods that do Compare() so we can pass const HSTRING pointers.
// Revision 1.55 2009/10/06 12:54:30EDT Rosetti,James (E412202) 
//  - See Jira MATRI-70, "HSTRING lacks a copy constructor":  Added a copy constructor;  Removed odd and incorrect = operator for HSTRING pointer;  Added a correct = operator. 
//  - Changed param in Copy() from "HSTRING *" to "const HSTRING *".
// Revision 1.54 2009/09/29 11:55:18EDT Walczyk Jr, Joseph A (E412257) 
// array delete Klockwork warning removal
// Revision 1.53.1.3 2009/05/01 17:00:52EDT Walczyk Jr, Joseph A (E412257) 
// array delete klockwork
// Revision 1.53.1.2 2009/04/28 14:40:56EDT Walczyk Jr, Joseph A (E412257) 
// use array delete syntax to delete array items -- klockwork
// Revision 1.53 2008/08/27 15:13:21EDT WalczykJ 
// remove warning assignment in condition and use of :: in class declaration
// Revision 1.52 2005/06/08 11:04:11EDT KeysB 
// Changed UnprintableCharactersToFormats in HSTRING to look for <LF><CR> as well as <CR><LF>.
// Revision 1.51 2005/05/31 09:03:58EDT KeysB 
// Fixed RangeCheck so it doesn't quit on first success.
// Revision 1.50 2004/12/13 15:29:34EST keysb 
// Fixed problem where an initializer string was used in the constructor and MaximumSize was
// set to 2 + initializer string size, and if the next appends were either one character each or two
// characters, then the heap could be corrupted.
// Revision 1.49 2004/11/16 11:09:59EST keysb 
// Added void constructor.
// Revision 1.48 2004/10/07 14:40:01EDT keysb 
// In Reallocate, allow the reallocate if the new maximum size is >= the current string size.  It
// was being stopped if equal.
// Revision 1.47 2004/09/21 07:39:33EDT keysb 
// Changed SmartReallocate to only update ResizeQuantity if this isn't the first time through.
// Revision 1.46 2004/09/20 09:27:51EDT keysb 
// Activated new HSTRING static string comparison functions that optionally search through the
// end of both strings.  Changed HSTRING and HWSTRING reallocation as follows:  1) Reallocate
// uses a flag that specifies whether to resize smaller (default is true).  Reallocate calls in this
// space should set this to false; 2) SmartReallocate should NOT add on the minimum additional
// amount for the first resize; and 3) Reallocate needs to track the last resize amount (set to
// MaximumSize at instantiation).  SmartReallocate needs to track the last smart reallocation amount
// (0 at outset).  When we go to do a SmartReallocate, if the last reallocate amount is less than the
// last smart reallocate amount, indicating that someone deliberately made the string smaller, then
// behave according to condition two above, as if this is the first resize.
// Revision 1.45 2004/09/09 11:12:30EDT keysb 
// Replaced memcmp with our own compare.
// Revision 1.44 2004/09/09 10:39:10EDT keysb 
// Replaced calls to strncmp with call to memcmp, since I don't want to quit on NULLs.
// Revision 1.43 2004/08/04 16:01:43EDT keysb 
// Added ParseRevisionString methods.
// Revision 1.42 2004/05/19 09:39:11EDT keysb 
// Added ConvertCharacterToHexFormat, ConvertCharacterToBracketedHexFormat, ConvertControlCharacterToName, and a new
// UnprintableCharactersToFormats that allows control over how characters are translated.
// Revision 1.41 2004/04/02 07:35:30EST keysb 
// Rebuilt to reflect new hhpisdigit, hhpstricmp, and hhpstrnicmp static members in HSTRING.  These were renamed in order to prevent conflicts in some builds.
// Revision 1.40 2004/03/31 10:44:20EST keysb 
// Added static functions isdigit, stricmp, and strnicmp.  These functions are sometimes missing from the C libraries on some
// platforms, and our libraries will stick with using these versions instead.
// Revision 1.39 2004/03/24 11:19:21EST montoroj 
// - replaced standard C Library function Isdigit() calls with hhpIsDigit() which is located at the
//   top of the file.  This is to accomodate SH3 & SH4 HPC/2.11 builds that don't have IsDigit().
// Revision 1.38 2004/01/08 08:23:37EST keysb 
// Added ability to remove trailing space characters and included <CR> and <LF> as space characters.  Fixed assignment operator so that it works properly
// and will not try to copy an undefinedl string.
// Revision 1.37 2003/11/18 06:35:11EST keysb 
// Added '\x' to HSTRING and '\x' and '\u' to HWSTRING.
// Revision 1.36 2003/11/06 07:21:50EST keysb 
// Remove strnicmp and strcmp.  Added range and resize routines.  Removed language.h / platform.h dependencies.
// Revision 1.35 2003/10/08 07:43:40EDT keysb 
// Changed Reallocate to not allow a reallocation smaller than the size of existing data.
// Revision 1.34 2003/09/16 16:02:08EDT keysb 
// Consolidated constructors.  Added parameters to allow a char or UCHAR initializer to be the actual buffer, so that new data doesn't have to be allocated.
// Added ReadOnly attribute to make the contents of the string unwritable.
// Revision 1.33 2003/08/26 14:51:43EDT keysb 
// Put a const qualifier on many parameters.
// Revision 1.32 2003/07/17 16:07:48EDT holzhaud 
// Updated/changed these files to compile and link for the WinCE ARM 3.0 PPC environment.
// Revision 1.31 2003/05/20 09:26:02EDT keysb 
// Added QuotedHEXStringToBinary.
// Revision 1.30 2003/05/15 10:52:45EDT keysb 
// Fixed HHPL and MatrixInterface DLL conflicts.
// Revision 1.29 2003/05/15 10:11:34EDT montoroj 
// - Added #ifdef on overloaded functions where the overload difference is only int vs
//   INT32 which is already defined in windows.
// Revision 1.28 2003/05/01 08:36:43EDT keysb 
// Added missing "else" in Move routine.
// Revision 1.27 2003/04/24 07:37:00EDT keysb 
// Added placeholders for settable minimum and maximum resize quantity, which I'm not going to use until I figure out why it causes reader code to
// blow up on download.
// Revision 1.26 2003/04/01 09:54:37EST keysb 
// When converting numbers, the start and end positions are now range checked.
// Revision 1.25 2003/03/13 11:37:16EST keysb 
// Changed condition for including strnicmp and stricmp from WIN32 to NEED_STRNICMP_AND_STRICMP.
// Revision 1.24 2003/02/18 08:55:30EST keysb 
// Fixed #if problem.
// Revision 1.23 2003/02/18 08:43:57EST keysb 
// Changed #if DLL >0 to WIN32.
// Revision 1.22 2003/01/28 12:44:47EST KeysB 
// Added RangeCheck.
// Revision 1.21  2003/01/21 13:47:15  KeysB
// Updated comments.
// Revision 1.20  2003/01/07 13:27:04  KeysB
// When copying after a reallocate, the string is now null terminated.
// Revision 1.19  2002/11/25 17:12:09  LivingJ2
// Cleanup from Barry to support various sizes.
// Revision 1.18  2002/11/22 22:09:36  LivingJ2
// Added Unicode Functions
// Revision 1.17  2002/11/18 13:41:39  LivingJ2
// BK Hex Binary string conversions
// Revision 1.16  2002/10/24 13:02:02  KeysB
// Reallocate now returns status.
// Revision 1.15  2002/10/03 12:51:23  KeysB
// SmartReallocate now returns a bool value to indicate if it was successful or not.
// Find methods were added to allow searching the local string for an occurrence of
// the input string (the opposite of FindString).
// Revision 1.14  2002/09/17 12:56:21  KeysB
// Added new ConvertToNumber and ConvertHexToNumber routines that take
// and ending position as a parameter.
// Revision 1.13  2002/09/12 13:25:16  KeysB
// Added ConvertHexToNumber.
// Revision 1.12  2002/09/09 17:24:45  PankowM
// - fixed revision integrity below. No code changes.
// Revision 1.11  2002/08/14 17:05:08  KeysB
// Fixed ConvertToNumber so that the return argument for the # of characters used in conversion
// is the actual # of characters rather than the position relative to the beginning of the string.
// Revision 1.10  2002/08/06 16:44:36  KeysB
// Removed DLL API definition.
// Revision 1.9  2002/07/29 18:18:52  WalczykJ
// fixed cast to unsigned char should be short
// --- Added comments ---  WalczykJ [2002/07/29 18:19:34 GMT]
// sennt from barry 7/29
// Revision 1.8  2002/07/25 17:54:27  KeysB
// Fix to remove warning messages.
// Revision 1.7  2002/07/24 20:53:06  LivingJ2
// corrected warning-producing code: *PositionWhereNonCharacterWasFound--
// ^^added parentheses to decrement data pointed to
// Revision 1.6  2002/07/24 17:40:36  LivingJ2
// Revision 1.5 added back in to get around integrity program.  Rev 1.5 was lost but Joe put back in those
// changes in rev 1.7 above.
// Revision 1.4  2002/05/29 11:33:09  KeysB
// Fixed case insensitive compare where lower case characters were being
// converted to upper case.  The conversion used the ?: mechanism to evaluate
// and the middle part needed to be encapsulated with parenthesis.
// Revision 1.3  2002/05/14 11:43:37  KeysB
// Added stricmp for the benefit of embedded code, which may not otherwise have
// access to a stricmp library function.
// Revision 1.2  2002/05/08 11:50:57  KeysB
// Added InsertNumber.
// Revision 1.2  2002/04/26 18:57:35  KeysB
// Added strnicmp and fixed FindCharacterBackward.
// Revision 1.1  2002/04/11 12:28:03  KeysB
// Initial revision
// Revision 1.5  2002/02/12 19:32:45  KeysB
// Added two versions of CompareSubstring and CompareOnShorter (with and
// without local index) for an input HSTRING string.  Also, several functions, including
// the constructors, now NULL terminate the updated local string.
// Revision 1.4  2002/01/29 13:59:16  KeysB
// The '#' wildcard comparison character may now be used to search for
// a single numeric digit.
// Fixed wildcard comparisons, where the following two cases would
// indicate a mismatch when they should indicate a match:
// - When the search string is "ab#*??" and the string to search is
//     "ab1c2d", the compare would return false.  This is because the
//     recursive asterisk (*) search would try to do a substring match of
//     "??" to "c2d" and would only consume "c2" against "??", leaving
//     the "d" unprocessed, which ultimately caused a failure.  Instead,
//     this has been corrected to keep recursively performing the (*) search,
//     incrementing the pointer to the string to search, until we encounter
//     a failure, thus ensuring that we've matched as much of the string
//     to search as we can.
// - When the search string is "ab*" and the string to search is "ab", the
//     compare would fail when it should pass.  This is because the compare
//     operation quit as soon as the string to search was consumed.  In
//     this situation, we now check to see if the unused characters in the
//     search string are all '*' and if they are, and everything else matches,
//     we'll indicate that the compare succeeded.
// Revision 1.3  2001/12/11 20:53:04  KeysB
// Reverse copies were not working in the HSTRING range copy
// routine; the copy was proceeding past the lower limit index.  This
// has been fixed.
// Revision 1.2  2001/12/04 13:11:51  KeysB
// In CompareOnShorterWithWildcards, we now return an error if
// there are characters still to be processed in the local string.
// Revision 1.1  2001/11/19 20:49:52  KeysB
// Initial revision
//
