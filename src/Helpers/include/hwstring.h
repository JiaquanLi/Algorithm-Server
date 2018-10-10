//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

#ifndef HWSTRINGH
#define HWSTRINGH

#include	<stddef.h>

#include	"hstring.h"
#include	"wchar.h"

class HWSTRING
{

private:

// When resizing, this is the default number of bytes to add above and beyond what is required
// for the next operation
	#define	HWSTRING_DEFAULT_AUTO_RESIZE_ADDITIONAL_SPACE	40

// When resizing, this is the maximumnumber of bytes to add above and beyond what is required
// for the next operation
	#define	HWSTRING_MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE	64000

// Current setting for the number of bytes to add above what is needed when resizing the string
// to add space.  This number will be increased automatically if resizing operations are frequent.
	unsigned int	ResizeQuantity;

// Number of times Size has increased as a result of an internal operation, but a resize of the
// string was not needed.  We use this to determine how frequently we're resizing.
	unsigned int	NumberOfCyclesSinceLastResize;

// This value will be set to true at instantiation or after a reallocation was made to a smaller maximum size.
// If set, auto resize will not add any padding, but will clear this variable so that the next time an auto
// resize is performed, padding will be added.
	bool			FirstAutoResizeAfterInstantiationOrReallocationToSmallerMaximumSize;


	bool	AutoResize;				// Determines whether the string size will be increased automatically when
    								// more space is needed.

	bool	ReadOnly;				// Determines whether or not this string can be updated from it's initial value.

	bool	InitializerBufferUsed;	// Determines whether or not this string uses it's own buffer (default) or whether it uses
									//	the initializer buffer.

public:
	bool	UseXInHexadecimalFormat;// When converting a character to hexadecimal format, insert an 'x' between the backslash
									//	and the two digit hexadecimal number.
	bool	UseUnicodeHexadecimalFormatForCharacterConversion;
									// When converting a character to hexadecimal format, use the form \unnnn, where 'nnnn' is
									//	the four hexadecimal digit representation of the character being converted.  Note that
									//	this overrides UseXInHexadecimalFormat.


public:
//	unsigned int	MinimumResizeQuantity;	// User can set this to ensure that resize will be at least this amount.  Default is 0.
//	unsigned int	MaximumResizeQuantity;	// User can set this to ensure that resize will be no more than this amount.  Default is
											//	HWSTRING_MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE.


protected:

// Resize the allocated space, copying the existing string to the new one.  We will
// determine, within this routine, what to use for a reallocation size.  The caller
// tells us the minimum size needed, but we're responsible for adding enough new memory,
// based on reallocation history, to avoid constant memory reallocation.
	bool SmartReallocate(unsigned int NewDeclaredMaximumSize);


protected:	// User declarations

	unsigned int	MaximumSize;        // Maximum size that local string may grow to.
	unsigned int	wcSize;				// Size of a wide character


public:		// User declarations

	wchar_t	*WChar;				// Address of local string.

	unsigned int	Size;               // Current size of the local string.



// Initialize auto resize information.  This is done at instantiation and whenever a reallocation is made that is
// smaller than the current maximum size.
	void InitializeAutoResizingInformation( void );


// Constructor for HWSTRING (overloaded versions #1, with maximum size and autoresize defined by caller).
// Reserve space for the local string and null it out.
	HWSTRING(unsigned int DeclaredMaximumSize, bool InputAutoResize = false);


// Constructor for HWSTRING (overloaded versions #2, initializing with null terminated constant character string, autoresize,
// and read only specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
	HWSTRING(const wchar_t *InitialString, bool InputAutoResize = false, bool InputReadOnly = false);


// Constructor for HWSTRING (overloaded versions #3, initializing with null terminated character string, autoresize
// read only specifier, and initializer specifier sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
	HWSTRING(wchar_t *InitialString, bool InputAutoResize = false, bool InputReadOnly = false,
				bool UseInitializerBuffer = false);


// Constructor for HWSTRING (overloaded versions #4, initializing with constant character string, length, autoresize,
// and read only specifier by caller).
// Reserve space for the local string and store the character string sent by the caller.
	HWSTRING(const wchar_t *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize = false, bool InputReadOnly = false);


// Constructor for HWSTRING (overloaded versions #5, initializing with character string, length, autoresize, read only specifier,
// and initializer sent by caller).
// Reserve space for the local string and store the character string sent by the caller.
	HWSTRING(wchar_t *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize = false, bool InputReadOnly = false,
				bool UseInitializerBuffer = false);


// Constructor for HWSTRING (overloaded versions #6, initializing with HWSTRING, autoresize, and read only specifier sent by
// caller).
// Reserve space for the local string and store the character string sent by the caller.
	HWSTRING(HWSTRING *InitialString, bool InputAutoResize, bool InputReadOnly = false);

// Constructor for HWSTRING (overloaded versions #7, initializing with HWSTRING and using the input string values for
// autoresize and read only.
// Reserve space for the local string and store the character string sent by the caller.
	HWSTRING(HWSTRING *InitialString);


// Constructor for HWSTRING (overloaded versions #8, initializing with HWSTRING default maximum size.
	HWSTRING( void );


// Destructor for HWSTRING.
// Free space allocated to the local string.
	~HWSTRING(void);


// Check to see if the range positions are valid for the string length set by the caller.  Note that the first position
// may be greater than the last position, indicating that the range is in the reverse direction.
	bool RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length );


// Check to see if the range positions are valid for the length of the local string.  Note that the first position
// may be greater than the last position, indicating that the range is in the reverse direction.
	bool RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition );


// Return the range length, where the range must be valid for the string length set by the caller.  Note that the first
// position may be greater than the last position, indicating that the range is in the reverse direction.
	unsigned int RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length );


// Return the range length, where the range must be valid for the length of the local string.  Note that the first
// position may be greater than the last position, indicating that the range is in the reverse direction.
	unsigned int RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition );


// Return the range direction, where the range must be valid for the string length set by the caller.  Note that the first
// position may be greater than the last position, indicating that the range is in the reverse direction.
	int RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length );


// Return the range direction, where the range must be valid for the length of the local string.  Note that the first
// position may be greater than the last position, indicating that the range is in the reverse direction.
	int RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition );


// Copy operator (=) for HWSTRING
    void operator = (HWSTRING *StringToCopy);

// Copy operator (=) for char *
    void operator = (const wchar_t *StringToCopy);

// Append operator (+) for HWSTRING
    HWSTRING operator + (HWSTRING StringToAppend);

// Append operator (+) for char *
    HWSTRING operator + (const wchar_t *StringToAppend);




// Add a caller specified fill character multiple (NumberOfTimesToAppend)
// times to the end of the local string.
	bool AppendFillChar(int InputCharacter, unsigned int NumberOfTimesToAppend);


// Add a caller specified fill character multiple (NumberOfTimesToInsert)
// times to the beginning of the local string.
	bool InsertFillChar(int InputCharacter, unsigned int NumberOfTimesToInsert);


// Create a one character string consisting of the character sent by the caller.
	bool CopyChar(int InputCharacter);


// Append a single character, sent by the caller, to the end of the local string.
	bool AppendChar(int InputCharacter);


// InsertNumber (overloaded version #1: unsigned char)
	bool InsertNumber(int Position, unsigned char InputNumber, unsigned int Length);

// InsertNumber (overloaded version #2: unsigned short)
	bool InsertNumber(int Position, unsigned short InputNumber, unsigned int Length);

// InsertNumber (overloaded version #3: unsigned int)
	bool InsertNumber(int Position, unsigned int InputNumber, unsigned int Length);

// InsertNumber (overloaded version #4: int)
	bool InsertNumber(int Position, int InputNumber, unsigned int Length);

// AppendNumber (overloaded version #1: unsigned char)
	bool AppendNumber(unsigned char InputNumber, unsigned int Length);

// AppendNumber (overloaded version #2: unsigned short)
	bool AppendNumber(unsigned short InputNumber, unsigned int Length);

// AppendNumber (overloaded version #3: unsigned int)
	bool AppendNumber(unsigned int InputNumber, unsigned int Length);

// AppendNumber (overloaded version #4: int)
	bool AppendNumber(int InputNumber, unsigned int Length);

// Overloaded version #1 of string copy:  Copy another HWSTRING over the local string.
	bool Copy(HWSTRING *StringToCopy);

// Overloaded version #2 of string copy:  Copy a character string over the local string.
	bool Copy(const wchar_t *StringToCopy, unsigned int LengthOfStringToCopy);

// Overloaded version #3 of string copy:  Copy a character string over the local string, using NULL for length.
	bool Copy(const wchar_t *StringToCopy);

// Overloaded version #4 of string copy:  Copy a char* string in the range specified by the caller.
	bool Copy(const wchar_t *StringToCopy, unsigned int LengthOfStringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition);

// Overloaded version #5 of string copy:  Copy an HWSTRING in the range specified by the caller.
	bool Copy(HWSTRING *StringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition);

// Overloaded version #1 of copy to range:  Copy a char* string to the range specified by the caller.
	bool CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, const wchar_t *StringToCopy,
											unsigned int LengthOfStringToCopy);

// Overloaded version #2 of copy to range:  Copy an HWSTRING to the range specified by the caller.
	bool CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, HWSTRING *StringToCopy);

// Overloaded version #1 of string append:  Append another HWSTRING to the end of the local string.
	bool Append(HWSTRING *StringToAppend);

// Overloaded version #2 of string append:  Append a character string to the end of the local string.
	bool Append(const wchar_t *StringToAppend, unsigned int LengthOfStringToAppend);

// Overloaded version #3 of string append:  Append a null terminated character string to the end of the local string.
	bool Append(const wchar_t *StringToAppend);

//  Search the local string for a caller specified character, returning true if
//  found and false otherwise.
	bool FindChar(int IntInputCharacter);

// Search the local string for a caller specified character:
	bool RemoveChar(int IntInputCharacter);

//	CopyNumberFromString (overloaded version #1: unsigned char* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned char *CopyDestination);

//	CopyNumberFromString (overloaded version #2: unsigned short* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned short *CopyDestination);


//	CopyNumberFromString (overloaded version #3: unsigned int* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   unsigned int *CopyDestination);

//	CopyNumberFromString (overloaded version #4: int* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
												   int *CopyDestination);

// CopyFromString (overloaded version #1: unsigned char* output with maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination,
										unsigned int MaximumDestinationLength);

// CopyFromString (overloaded version #2: unsigned int* output with maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination,
										unsigned int MaximumDestinationLength);

// CopyFromString (overloaded version #3: wchar_t* output with maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination,
										unsigned int MaximumDestinationLength);

// CopyFromString (overloaded version #4: unsigned char* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination);

// CopyFromString (overloaded version #5: unsigned int* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination);

// CopyFromString (overloaded version #6: wchar_t* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination);

// CopyFromString (overloaded version #7: unsigned char* output with maximum length, copying the entire string)
	unsigned int CopyFromString(unsigned char *CopyDestination, unsigned int MaximumDestinationLength);

// CopyFromString (overloaded version #8: unsigned char* output with maximum length, copying the entire string)
	unsigned int CopyFromString(wchar_t *CopyDestination, unsigned int MaximumDestinationLength);

// CopyFromString (overloaded version #9: HWSTRING* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, HWSTRING *CopyDestination);

// CopyFromString (overloaded version #10: HWSTRING* output WITHOUT maximum length, copying the entire string)
	bool CopyFromString(HWSTRING *CopyDestination);

// CopyFromStringLittleEndian (overloaded version #1: unsigned char* output with maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination,
										unsigned int MaximumDestinationLength);

// CopyFromStringLittleEndian (overloaded version #2: unsigned int* output with maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination,
										unsigned int MaximumDestinationLength);

// CopyFromStringLittleEndian (overloaded version #3: wchar_t* output with maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination,
										unsigned int MaximumDestinationLength);

// CopyFromStringLittleEndian (overloaded version #4: unsigned char* output WITHOUT maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination);

// CopyFromStringLittleEndian (overloaded version #5: unsigned int* output WITHOUT maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination);

// CopyFromStringLittleEndian (overloaded version #6: wchar_t* output WITHOUT maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, wchar_t *CopyDestination);

// CopyFromStringLittleEndian (overloaded version #7: unsigned char* output with maximum length, copying the entire string)
	unsigned int CopyFromStringLittleEndian(unsigned char *CopyDestination, unsigned int MaximumDestinationLength);

// CopyFromStringLittleEndian (overloaded version #8: unsigned char* output with maximum length, copying the entire string)
	unsigned int CopyFromStringLittleEndian(wchar_t *CopyDestination, unsigned int MaximumDestinationLength);

// CopyFromStringLittleEndian (overloaded version #9: HWSTRING* output WITHOUT maximum length)
	bool CopyFromStringLittleEndian(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, HWSTRING *CopyDestination);

// CopyFromStringLittleEndian (overloaded version #10: HWSTRING* output WITHOUT maximum length, copying the entire string)
	bool CopyFromStringLittleEndian(HWSTRING *CopyDestination);

// Convert each unprintable ASCII character in the local string to an unprintable ASCII format string.
    bool UnprintableCharactersToFormats(void);

// Convert each ASCII character in the local string to an unprintable ASCII format string.
    bool AllCharactersToFormats(void);

// Convert each unprintable ASCII format string in the form of "\XX" back to an unprintable ASCII character.
    bool UnprintableFormatsToCharacters(void);

// Convert each ASCII character in the local string to a formatted two byte HEX representation.
	bool BinaryToHex(void);

// Convert each formatted two byte HEX character representation in the local string to the ASCII equivalent value.
	bool HexToBinary(void);

// Convert each formatted two byte HEX character representation in the local string to the ASCII equivalent value.
// Any characters between quotes will not be translated as HEX characters, but will be stored directly into the
// local string.
	bool QuotedHEXStringToBinary(bool *IncompleteString = NULL);

// Resize the allocated space, copying the existing string the new one.
    bool Reallocate(unsigned int NewDeclaredMaximumSize, bool AllowResizingToASmallerSize = true );

// Set size to the caller specified value, resizing the string if necessary to add space.  This can be used by application code
// to set string length before directly writing to WChar.
    bool Resize(unsigned int NewSize);

// Is this string auto-resizable?
    bool AutoResizing( void )    { return AutoResize; }

// Is this string read only?
    bool IsReadOnly( void )    { return ReadOnly; }

// Remove characters from the string within the requested index range.
    bool Remove(unsigned int StartingIndexOfCharactersToBeRemoved, unsigned int NumberOfCharactersToBeRemoved);

// Move characters from the one location to another within the string.
	bool Move(unsigned int StartingIndexOfCharactersToBeMoved, unsigned int LocationToMoveTo, unsigned int NumberOfCharactersToBeMoved);

// Remove all tabs, spaces, and nulls (overloaded version #1).
	bool RemoveSpaceCharacters(void);

// Remove all tabs, spaces, and nulls up to caller specified character (overloaded version #2).
	bool RemoveSpaceCharacters(int CharacterToRemoveUpTo);

// Remove all leading tabs, spaces, and nulls.
	bool RemoveLeadingSpaceCharacters(void);

// Remove all trailing tabs, spaces, and nulls.
	bool RemoveTrailingSpaceCharacters(void);

//	CompareSubstring (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HWSTRING up to the length of the input string (ignoring any
//		characters beyond that length).
	int CompareSubstring(unsigned int LocalStringIndex, const wchar_t *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive);

//	CompareSubstring (overloaded version #2, where starting index into the local string is assumed to be zero)
//		Compare the input string to the local HWSTRING up to the length of the input string (ignoring any
// 		characters beyond that length).
	int CompareSubstring(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

//	CompareSubstring (overloaded version #3, with a starting index into the local string and a
//		char * argument)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the input string (ignoring any
//		characters beyond that length).
	int CompareSubstring(unsigned int LocalStringIndex, HWSTRING *InputString, bool CompareIsCaseSensitive);

//	CompareSubstring (overloaded version #4, where starting index into the local string is assumed to be zero
//		and a char * argument)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the input string (ignoring any
// 		characters beyond that length).
	int CompareSubstring(HWSTRING *InputString, bool CompareIsCaseSensitive);

//	CompareOnShorter (overloaded version #1, with a starting index into the local string)
//		Compare the input string to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).
	int CompareOnShorter(unsigned int LocalStringIndex, const wchar_t *InputString, unsigned int InputStringLength,
															bool CompareIsCaseSensitive);

//	CompareOnShorter (overloaded version #2, where starting index into the local string is assumed to be zero)
//		Compare the input string to the local HWSTRING up to the length of the shorter string (ignoring any
// 		characters beyond that length).
	int CompareOnShorter(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

//	CompareOnShorter (overloaded version #3, with a starting index into the local string)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the shorter string (ignoring any
//		characters beyond that length).
	int CompareOnShorter(unsigned int LocalStringIndex, HWSTRING *InputString, bool CompareIsCaseSensitive);

//	CompareOnShorter (overloaded version #4, where starting index into the local string is assumed to be zero)
//		Compare the input HWSTRING to the local HWSTRING up to the length of the shorter string (ignoring any
// 		characters beyond that length).
	int CompareOnShorter(HWSTRING *InputString, bool CompareIsCaseSensitive);

// Compare the input string to the local HWSTRING (overloaded version #1 with unsigned char* input and specified length).
	int Compare(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

// Compare the input string to the local HWSTRING (overloaded version #2 with HWSTRING* input).
	int Compare(HWSTRING *InputString, bool CompareIsCaseSensitive);

// Compare the input string to the local HWSTRING (overloaded version #3 with unsigned char* input).
	int Compare(const wchar_t *InputString, bool CompareIsCaseSensitive);

// Compare the input string to the local HWSTRING up to the input length (overloaded version #1 with unsigned char* input
// and specified length).
	int CompareFixedInputLength(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

// Compare the input string to the local HWSTRING up to the length of the input HWSTRING (overloaded version #2
// with HWSTRING* input).
	int CompareFixedInputLength(HWSTRING *InputString, bool CompareIsCaseSensitive);

// Compare the input string to the local HWSTRING up to the length of the input unsigned char string (overloaded
// version #3 with unsigned char* input).
	int CompareFixedInputLength(const wchar_t *InputString, bool CompareIsCaseSensitive);

//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString.
//	(overloaded version #1 with a unsigned char input string).
	bool FindString(const wchar_t *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound);

//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString.
//	(overloaded version #2 with an input HWSTRING).
	bool FindString(HWSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
    									int *PositionWhereInputStringWasFound);



// Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string
// (overloaded version #1 with a wchar_t input string).
	bool Find(const wchar_t *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound);



// Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string
// (overloaded version #2 with an input HWSTRING).
	bool Find(HWSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
												int *PositionWhereInputStringWasFound);


//	Turn on autoresize
	void AutoResizeOn(void);

//	Turn off autoresize
	void AutoResizeOff(void);

// Overloaded version #1 of Insert:  Insert a string at the caller specified location
	void Insert(const wchar_t *StringToInsert, unsigned int SourceLength, unsigned int PositionToInsertAt);

// Overloaded version #2 of Insert:  Insert a string at the caller specified location
	void Insert(HWSTRING *StringToInsert, unsigned int PositionToInsertAt);

// Overloaded version #3 of Insert:  Insert a string at the caller specified location
	void Insert(const wchar_t *StringToInsert, unsigned int PositionToInsertAt);

//	GetNumber (overloaded version #1 -> get an integer parameter (positive or negative)
	bool GetNumber(int *NumericParameterValue);

//	GetNumber (overloaded version #2 -> get a non-negative integer parameter
	bool GetNumber(unsigned int *NumericParameterValue);


//	CompareOnShorterWithWildcards (overloaded version #1, with a starting index into the local string)
	bool CompareOnShorterWithWildcards(unsigned int LocalStringIndex, const wchar_t *InputString, unsigned int InputStringLength,
				bool CompareIsCaseSensitive, unsigned int *NextPositionInInputStringBeyondSuccessfulCompare);


//	CompareOnShorterWithWildcards (overloaded version #2, where starting index into the local string is
//		assumed to be zero)
	bool CompareOnShorterWithWildcards(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive,
				unsigned int *NextPositionInInputStringBeyondSuccessfulCompare);

//  CompareWithWildcards (overloaded version #1 with unsigned char* input).
	bool CompareWithWildcards(const wchar_t *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

//  Compare (overloaded version #2 with HWSTRING* input).
	bool CompareWithWildcards(HWSTRING *InputString, bool CompareIsCaseSensitive);

//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString,
//	using wildcards (overloaded version #1 with a unsigned char input string).
	bool FindWildcardString(const wchar_t *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
                				int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound);

//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString,
//	using wildcards (overloaded version #2 with an input HWSTRING).
	bool FindWildcardString(HWSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
    									int *PositionWhereInputStringWasFound);


// CopyToOffset (overloaded version #1: unsigned char* input)
	bool CopyToOffset(unsigned int IndexToStartOfCopyLocation, const wchar_t *InputString, unsigned int LengthToCopy);


// Search from the start index forward for the first occurrence of the caller specified
// character.
	bool FindCharacterForward(wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereCharacterWasFound);

// Search from the start index backward for the first occurrence of the caller specified
// character.
	bool FindCharacterBackward(wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereCharacterWasFound);

// Search from the start index forward for the first occurrence of a character not equal
// to the caller specified character.
	bool FindNonCharacterForward(wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereNonCharacterWasFound);


// Search from the start index backward for the first occurrence of a character not equal
// to the caller specified character.
	bool FindNonCharacterBackward(wchar_t Character, unsigned int StartIndex,
								   int *PositionWhereNonCharacterWasFound);

// Return maximum size to caller.
	int MaximumLength(void);


// Replace all occurrences of a string
	bool ReplaceAll(const wchar_t *StringToReplace, const wchar_t *ReplacementString);

// Move past blanks, <TAB>s, <CR>s, <LF>s, and <FF>s in the local string.
	void FindFirstNonSpaceCharacter(int StartingIndex,
										 int *PositionWhereFirstNonSpaceCharacterWasFound);

// Return a decimal number converted from the local string starting at the caller specified
// location (overloaded version #1 using a length limit).
	int ConvertToNumber(int StartingPosition, int EndingPosition, int *NumberOfCharactersUsedInConversion);

// Return a decimal number converted from the local string starting at the caller specified
// location (overloaded version #2 using the entire string).
	int ConvertToNumber(int StartingPosition, int *NumberOfCharactersUsedInConversion);

// Return a decimal number converted from the local string starting at the caller specified
// location, where the string is assumed to be in hexadecimal format (overloaded version #1 using a length limit).
	int ConvertHexToNumber(int StartingPosition, int EndingPosition, int *NumberOfCharactersUsedInConversion);

// Return a decimal number converted from the local string starting at the caller specified
// location, where the string is assumed to be in hexadecimal format (overloaded version #2 using the entire string).
	int ConvertHexToNumber(int StartingPosition, int *NumberOfCharactersUsedInConversion);

// Convert local string to upper case
	void UpperCase(void);

// Convert local string to lower case
	void LowerCase(void);

// Check the current string to see if all characters fall within the specified range.  Multiple (up to 15 ranges)
// may be selected.
	bool RangeCheck(int LowRange1 = -1, int HighRange1 = -1, int LowRange2 = -1, int HighRange2 = -1,
			int LowRange3 = -1, int HighRange3 = -1, int LowRange4 = -1, int HighRange4 = -1,
			int LowRange5 = -1, int HighRange5 = -1, int LowRange6 = -1, int HighRange6 = -1,
			int LowRange7 = -1, int HighRange7 = -1, int LowRange8 = -1, int HighRange8 = -1,
			int LowRange9 = -1, int HighRange9 = -1, int LowRange10 = -1, int HighRange10 = -1,
			int LowRange11 = -1, int HighRange11 = -1, int LowRange12 = -1, int HighRange12 = -1,
			int LowRange13 = -1, int HighRange13 = -1, int LowRange14 = -1, int HighRange14 = -1,
			int LowRange15 = -1, int HighRange15 = -1);

// Static member function to parse a version string into numeric segments.  Returns true if the entire string was
// consumed, false otherwise (version #1, using HWSTRING input).
	static bool ParseRevisionString( HWSTRING *InputString, int *AmountOfCharactersConsumed,
								  int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments );

// Static member function to parse a version string into numeric segments.  Returns true if the entire string was
// consumed, false otherwise (version #2, using character string input).
	static bool ParseRevisionString( wchar_t *InputString, int InputStringLength, int *AmountOfCharactersConsumed,
								  int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments );

// Append a range of characters in this string to an HSTRING, storing each wchar_t in little endian.
	bool AppendToHString( HSTRING *HStringToAppendTo, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Append this string to an HSTRING, storing each wchar_t in little endian.
	bool AppendToHString( HSTRING *HStringToAppendTo );

// Copy a range of characters in this string to an HSTRING, storing each wchar_t in little endian.
	bool CopyToHString( HSTRING *HStringToCopyTo, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Copy this string to an HSTRING, storing each wchar_t in little endian.
	bool CopyToHString( HSTRING *HStringToCopyTo );

// Append a range of characters from a character string to this string, retrieving each wchar_t in little endian format.
	bool AppendLittleEndian( unsigned char *StringToAppendFrom, unsigned int LengthOfStringToAppendFrom,
							unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Append characters from a character string to this string, retrieving each wchar_t in little endian format.
	bool AppendLittleEndian( unsigned char *StringToAppendFrom, unsigned int LengthOfStringToAppendFrom );

// Append a range of characters from an HSTRING to this string, retrieving each wchar_t in little endian format.
	bool AppendFromHString( HSTRING *HStringToAppendFrom, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Copy a range of characters from a character string to this string, retrieving each wchar_t in little endian format.
	bool CopyLittleEndian( unsigned char *StringToCopyFrom, unsigned int LengthOfStringToCopyFrom,
								unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Copy characters from a character string to this string, retrieving each wchar_t in little endian format.
	bool CopyLittleEndian( unsigned char *StringToCopyFrom, unsigned int LengthOfStringToCopyFrom );

// Copy a range of characters from an HSTRING to this string, retrieving each wchar_t in little endian format.
	bool CopyFromHString( HSTRING *HStringToCopyFrom, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Copy an HSTRING to this string, retrieving each wchar_t in little endian format.
	bool CopyFromHString( HSTRING *HStringToCopyFrom );

// Append a range of characters in this string to an HSTRING, storing each wchar_t as a single character.
	bool ConvertAndAppendToHString( HSTRING *HStringToAppendTo, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Append this string to an HSTRING, storing each wchar_t as a single character.
	bool ConvertAndAppendToHString( HSTRING *HStringToAppendTo );

// Copy a range of characters in this string to an HSTRING, storing each wchar_t as a single character.
	bool ConvertAndCopyToHString( HSTRING *HStringToCopyTo, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Copy this string to an HSTRING, storing each wchar_t as a single character.
	bool ConvertAndCopyToHString( HSTRING *HStringToCopyTo );

// Append a range of characters from an HSTRING to this string, retrieving each wchar_t as a single character.
	bool ConvertAndAppendFromHString( HSTRING *HStringToAppendFrom, unsigned int FirstCharPosition,
						unsigned int LastCharPosition );

// Copy a range of characters from an HSTRING to this string, retrieving each wchar_t as a single character.
	bool ConvertAndCopyFromHString( HSTRING *HStringToCopyFrom, unsigned int FirstCharPosition, unsigned int LastCharPosition );

// Copy from an HSTRING to this string, retrieving each wchar_t as a single character.
	bool ConvertAndCopyFromHString( HSTRING *HStringToCopyFrom );
};

#endif
