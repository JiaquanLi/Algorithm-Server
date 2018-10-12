//======================================================================================
// HString.h
//======================================================================================
// $Author: Ledwith, James $
//======================================================================================
// Copyright (C) HandHeld Products  2001
//======================================================================================
#ifndef HSTRINGH
#define HSTRINGH

class HSTRING
{

private:

	// When resizing, this is the default number of bytes to add above and beyond what is required
	// for the next operation
#define	DEFAULT_AUTO_RESIZE_ADDITIONAL_SPACE	200

	// When resizing, this is the maximumnumber of bytes to add above and beyond what is required
	// for the next operation
#define	MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE	64000

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

public:
	//	unsigned int	MinimumResizeQuantity;	// User can set this to ensure that resize will be at least this amount.  Default is 0.
	//	unsigned int	MaximumResizeQuantity;	// User can set this to ensure that resize will be no more than this amount.  Default is
	//	MAXIMUM_AUTO_RESIZE_ADDITIONAL_SPACE.


protected:

	// Resize the allocated space, copying the existing string to the new one.  We will
	// determine, within this routine, what to use for a reallocation size.  The caller
	// tells us the minimum size needed, but we're responsible for adding enough new memory,
	// based on reallocation history, to avoid constant memory reallocation.
	bool SmartReallocate(unsigned int NewDeclaredMaximumSize);


protected:	// User declarations

	unsigned int	MaximumSize;        // Maximum size that local string may grow to.


public:		// User declarations

	unsigned char	*Char;              // Address of local string.

	unsigned int	Size;               // Current size of the local string.



	// Initialize auto resize information.  This is done at instantiation and whenever a reallocation is made that is
	// smaller than the current maximum size.
	void InitializeAutoResizingInformation( void );


	// Constructor for HSTRING (overloaded versions #1, with maximum size and autoresize defined by caller).
	// Reserve space for the local string and null it out.
	HSTRING(unsigned int DeclaredMaximumSize, bool InputAutoResize = false);


	// Constructor for HSTRING (overloaded versions #2, initializing with null terminated constant character string, autoresize,
	// and read only specifier sent by caller).
	// Reserve space for the local string and store the character string sent by the caller.
	HSTRING(const char *InitialString, bool InputAutoResize = false, bool InputReadOnly = false);


	// Constructor for HSTRING (overloaded versions #3, initializing with null terminated character string, autoresize
	// read only specifier, and initializer specifier sent by caller).
	// Reserve space for the local string and store the character string sent by the caller.
	HSTRING(char *InitialString, bool InputAutoResize = false, bool InputReadOnly = false,
			bool UseInitializerBuffer = false);


	// Constructor for HSTRING (overloaded versions #4, initializing with constant character string, length, autoresize,
	// and read only specifier by caller).
	// Reserve space for the local string and store the character string sent by the caller.
	HSTRING(const unsigned char *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize = false, bool InputReadOnly = false);


	// Constructor for HSTRING (overloaded versions #5, initializing with character string, length, autoresize, read only specifier,
	// and initializer sent by caller).
	// Reserve space for the local string and store the character string sent by the caller.
	HSTRING(unsigned char *InitialString, unsigned int LengthOfInitialString, bool InputAutoResize = false, bool InputReadOnly = false,
			bool UseInitializerBuffer = false);


	// Constructor for HSTRING (overloaded versions #6, initializing with HSTRING, autoresize, and read only specifier sent by caller).
	// Reserve space for the local string and store the character string sent by the caller.
	HSTRING(HSTRING *InitialString, bool InputAutoResize, bool InputReadOnly = false);


	// Constructor for HSTRING (overloaded versions #7, initializing with HSTRING and using the input string values for
	// autoresize and read only.
	// Reserve space for the local string and store the character string sent by the caller.
	HSTRING(HSTRING *InitialString);


	// Constructor for HSTRING (overloaded versions #8, initializing with HSTRING default maximum size.
	HSTRING( void );


	// Copy constructor (overloaded versions #9.
	HSTRING(const HSTRING & InitialString);


	// Destructor for HSTRING.
	// Free space allocated to the local string.
	~HSTRING(void);


	// Check to see if the range positions are valid for the string length set by the caller.  Note that the first position
	// may be greater than the last position, indicating that the range is in the reverse direction.
	bool RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length ) const;


	// Check to see if the range positions are valid for the length of the local string.  Note that the first position
	// may be greater than the last position, indicating that the range is in the reverse direction.
	bool RangePositionsAreValid( unsigned int FirstCharPosition, unsigned int LastCharPosition ) const;


	// Return the range length, where the range must be valid for the string length set by the caller.  Note that the first
	// position may be greater than the last position, indicating that the range is in the reverse direction.
	unsigned int RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length ) const;


	// Return the range length, where the range must be valid for the length of the local string.  Note that the first
	// position may be greater than the last position, indicating that the range is in the reverse direction.
	unsigned int RangeLength( unsigned int FirstCharPosition, unsigned int LastCharPosition ) const;


	// Return the range direction, where the range must be valid for the string length set by the caller.  Note that the first
	// position may be greater than the last position, indicating that the range is in the reverse direction.
	int RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition, unsigned int Length ) const;


	// Return the range direction, where the range must be valid for the length of the local string.  Note that the first
	// position may be greater than the last position, indicating that the range is in the reverse direction.
	int RangeDirection( unsigned int FirstCharPosition, unsigned int LastCharPosition ) const;


	// Copy operator (=) for HSTRING
	HSTRING operator = (HSTRING StringToCopy);

	// Append operator (+) for HSTRING
	HSTRING operator + (HSTRING StringToAppend);

	// Append operator (+) for char *
	HSTRING operator + (const char *StringToAppend);




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

	// Overloaded version #1 of string copy:  Copy another HSTRING over the local string.
	bool Copy(const HSTRING *StringToCopy);

	// Overloaded version #2 of string copy:  Copy a character string over the local string.
	bool Copy(const unsigned char *StringToCopy, unsigned int LengthOfStringToCopy);

	// Overloaded version #3 of string copy:  Copy a character string over the local string, using NULL for length.
	bool Copy(const unsigned char *StringToCopy);

	// Overloaded version #4 of string copy:  Copy a character string over the local string.
	bool Copy(const char *StringToCopy, unsigned int LengthOfStringToCopy);

	// Overloaded version #5 of string copy:  Copy a character string over the local string, using NULL for length.
	bool Copy(const char *StringToCopy);

	// Overloaded version #6 of string copy:  Copy a char* string in the range specified by the caller.
	bool Copy(const char *StringToCopy, unsigned int LengthOfStringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition);

	// Overloaded version #7 of string copy:  Copy an HSTRING in the range specified by the caller.
	bool Copy(HSTRING *StringToCopy, unsigned int FirstCharPosition, unsigned int LastCharPosition);

	// Overloaded version #1 of copy to range:  Copy a char* string to the range specified by the caller.
	bool CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, const char *StringToCopy,
			unsigned int LengthOfStringToCopy);

	// Overloaded version #2 of copy to range:  Copy an HSTRING to the range specified by the caller.
	bool CopyToRange(unsigned int FirstCharPosition, unsigned int LastCharPosition, HSTRING *StringToCopy);

	// Overloaded version #1 of string append:  Append another HSTRING to the end of the local string.
	bool Append(const HSTRING *StringToAppend);

	// Overloaded version #2 of string append:  Append a character string to the end of the local string.
	bool Append(const unsigned char *StringToAppend, unsigned int LengthOfStringToAppend);

	// Overloaded version #3 of string append:  Append a null terminated character string to the end of the local string.
	bool Append(const char *StringToAppend);

	// Overloaded version #4 of string append:  Append a character string to the end of the local string.
	bool Append(const char *StringToAppend, unsigned int LengthOfStringToAppend);

	// Overloaded version #5 of string append:  Append a null terminated character string to the end of the local string.
	bool Append(const unsigned char *StringToAppend);

	//  Search the local string for a caller specified character, returning true if
	//  found and false otherwise.
	bool FindChar(int IntInputCharacter);

	// Search the local string for a caller specified character:
	bool RemoveChar(int IntInputCharacter);

	//	CopyNumberFromString (overloaded version #1: unsigned char* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
			unsigned char *CopyDestination) const;

	//	CopyNumberFromString (overloaded version #2: unsigned short* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
			unsigned short *CopyDestination) const;


	//	CopyNumberFromString (overloaded version #3: unsigned int* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
			unsigned int *CopyDestination) const;

	//	CopyNumberFromString (overloaded version #4: int* output)
	bool CopyNumberFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy,
			int *CopyDestination) const;

	// CopyFromString (overloaded version #1: unsigned char* output with maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination,
			unsigned int MaximumDestinationLength) const;

	// CopyFromString (overloaded version #2: unsigned short* output with maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned short *CopyDestination,
			unsigned int MaximumDestinationLength) const;

	// CopyFromString (overloaded version #3: unsigned int* output with maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination,
			unsigned int MaximumDestinationLength) const;

	// CopyFromString (overloaded version #4: unsigned char* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned char *CopyDestination) const;

	// CopyFromString (overloaded version #5: unsigned short* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned short *CopyDestination) const;

	// CopyFromString (overloaded version #6: unsigned int* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, unsigned int *CopyDestination) const;

	// CopyFromString (overloaded version #7: unsigned char* output with maximum length, copying the entire string)
	unsigned int CopyFromString(unsigned char *CopyDestination, unsigned int MaximumDestinationLength) const;

	// CopyFromString (overloaded version #8: HSTRING* output WITHOUT maximum length)
	bool CopyFromString(unsigned int IndexToStartOfCopyLocation, unsigned int LengthToCopy, HSTRING *CopyDestination) const;

	// CopyFromString (overloaded version #9: HSTRING* output WITHOUT maximum length, copying the entire string)
	bool CopyFromString(HSTRING *CopyDestination) const;


	// Convert character at index sent by caller to the form '\XX', where XX is the 2 digit hexadecimal code.
	bool ConvertCharacterToHexFormat( int *CharacterIndex );

	// Convert character at index sent by caller to the form '[0xXX]', where XX is the 2 digit hexadecimal code.
	bool ConvertCharacterToBracketedHexFormat( int *CharacterIndex );

	// Convert control character at index sent by caller to a name.
	bool ConvertControlCharacterToName( int *CharacterIndex );


	// Convert each unprintable ASCII character in the local string to an unprintable ASCII format string (overload #1 with full control).
	bool UnprintableCharactersToFormats( bool TranslateControlCharacters, bool TranslateControlCharactersToHexadecimal,
			bool TranslateUsingBackslashHexadecimalFormat, bool TranslatePrintableASCII, bool TranslateExtendedASCII,
			bool ShowCRLFWhenControlCharactersAreTranslated );

	// Convert each unprintable ASCII character in the local string to an unprintable ASCII format string (overload #2).
	bool UnprintableCharactersToFormats( void );

	// Convert each unicode character in the local string to ASCII, throwing out upper byte.
	bool UniCodeToSimpleAsciiFormat(void);

	// Convert each ASCII character in the local string to UNICODE, making upper byte NULL.
	bool SimpleAsciiToUniCodeFormat(void);

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
	bool QuotedHEXStringToBinary(bool *IncompleteString = 0);

	// Resize the allocated space, copying the existing string the new one.
	bool Reallocate(unsigned int NewDeclaredMaximumSize, bool AllowResizingToASmallerSize = true );

	// Set size to the caller specified value, resizing the string if necessary to add space.  This can be used by application code
	// to set string length before directly writing to Char.
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
	//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
	//		characters beyond that length).
	int CompareSubstring(unsigned int LocalStringIndex, const unsigned char *InputString, unsigned int InputStringLength,
			bool CompareIsCaseSensitive);

	//	CompareSubstring (overloaded version #2, where starting index into the local string is assumed to be zero)
	//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
	// 		characters beyond that length).
	int CompareSubstring(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

	//	CompareSubstring (overloaded version #3, with a starting index into the local string and a
	//		char * argument)
	//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
	//		characters beyond that length).
	int CompareSubstring(unsigned int LocalStringIndex, const char *InputString, unsigned int InputStringLength,
			bool CompareIsCaseSensitive);

	//	CompareSubstring (overloaded version #4, where starting index into the local string is assumed to be zero
	//		and a char * argument)
	//		Compare the input string to the local HSTRING up to the length of the input string (ignoring any
	// 		characters beyond that length).
	int CompareSubstring(const char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

	//	CompareSubstring (overloaded version #5, with a starting index into the local string and a
	//		char * argument)
	//		Compare the input HSTRING to the local HSTRING up to the length of the input string (ignoring any
	//		characters beyond that length).
	int CompareSubstring(unsigned int LocalStringIndex, HSTRING *InputString, bool CompareIsCaseSensitive);

	//	CompareSubstring (overloaded version #6, where starting index into the local string is assumed to be zero
	//		and a char * argument)
	//		Compare the input HSTRING to the local HSTRING up to the length of the input string (ignoring any
	// 		characters beyond that length).
	int CompareSubstring(HSTRING *InputString, bool CompareIsCaseSensitive);

	//	CompareOnShorter (overloaded version #1, with a starting index into the local string)
	//		Compare the input string to the local HSTRING up to the length of the shorter string (ignoring any
	//		characters beyond that length).
	int CompareOnShorter(unsigned int LocalStringIndex, const unsigned char *InputString, unsigned int InputStringLength,
			bool CompareIsCaseSensitive) const;

	//	CompareOnShorter (overloaded version #2, where starting index into the local string is assumed to be zero)
	//		Compare the input string to the local HSTRING up to the length of the shorter string (ignoring any
	// 		characters beyond that length).
	int CompareOnShorter(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const;

	//	CompareOnShorter (overloaded version #3, with a starting index into the local string)
	//		Compare the input HSTRING to the local HSTRING up to the length of the shorter string (ignoring any
	//		characters beyond that length).
	int CompareOnShorter(unsigned int LocalStringIndex, HSTRING *InputString, bool CompareIsCaseSensitive) const;

	//	CompareOnShorter (overloaded version #4, where starting index into the local string is assumed to be zero)
	//		Compare the input HSTRING to the local HSTRING up to the length of the shorter string (ignoring any
	// 		characters beyond that length).
	int CompareOnShorter(HSTRING *InputString, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING (overloaded version #1 with unsigned char* input and specified length).
	int Compare(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING (overloaded version #2 with HSTRING* input).
	int Compare(const HSTRING *InputString, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING (overloaded version #3 with unsigned char* input).
	int Compare(const unsigned char *InputString, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING (overloaded version #4 with char* input and specified length).
	int Compare(const char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING (overloaded version #5 with char* input).
	int Compare(const char *InputString, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING up to the input length (overloaded version #1 with unsigned char* input
	// and specified length).
	int CompareFixedInputLength(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING up to the length of the input HSTRING (overloaded version #2
	// with HSTRING* input).
	int CompareFixedInputLength(HSTRING *InputString, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING up to the length of the input unsigned char string (overloaded
	// version #3 with unsigned char* input).
	int CompareFixedInputLength(const unsigned char *InputString, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING up to the input length (overloaded version #4 with char* input
	// and specified length).
	int CompareFixedInputLength(const char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive) const;

	// Compare the input string to the local HSTRING up to the length of the input char string (overloaded
	// version #5 with char* input).
	int CompareFixedInputLength(const char *InputString, bool CompareIsCaseSensitive) const;

	//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString.
	//	(overloaded version #1 with a unsigned char input string).
	bool FindString(const unsigned char *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
			int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound) const;

	//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString.
	//	(overloaded version #2 with an input HSTRING).
	bool FindString(HSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
			int *PositionWhereInputStringWasFound) const;



	// Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string
	// (overloaded version #1 with a unsigned char input string).
	bool Find(const unsigned char *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
			int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound) const;



	// Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of the input string
	// (overloaded version #2 with an input HSTRING).
	bool Find(HSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
			int *PositionWhereInputStringWasFound) const;


	//	Turn on autoresize
	void AutoResizeOn(void);

	//	Turn off autoresize
	void AutoResizeOff(void);

	// Overloaded version #1 of Insert:  Insert a string at the caller specified location
	void Insert(const unsigned char *StringToInsert, unsigned int SourceLength, unsigned int PositionToInsertAt);

	// Overloaded version #2 of Insert:  Insert a string at the caller specified location
	void Insert(HSTRING *StringToInsert, unsigned int PositionToInsertAt);

	// Overloaded version #3 of Insert:  Insert a string at the caller specified location
	void Insert(const unsigned char *StringToInsert, unsigned int PositionToInsertAt);

	// Overloaded version #4 of Insert:  Insert a string at the caller specified location
	void Insert(const char *StringToInsert, unsigned int SourceLength, unsigned int PositionToInsertAt);

	// Overloaded version #5 of Insert:  Insert a string at the caller specified location
	void Insert(const char *StringToInsert, unsigned int PositionToInsertAt);

	//	GetNumber (overloaded version #1 -> get an integer parameter (positive or negative)
	bool GetNumber(int *NumericParameterValue);

	//	GetNumber (overloaded version #2 -> get a non-negative integer parameter
	bool GetNumber(unsigned int *NumericParameterValue);


	//	CompareOnShorterWithWildcards (overloaded version #1, with a starting index into the local string)
	bool CompareOnShorterWithWildcards(unsigned int LocalStringIndex, const unsigned char *InputString, unsigned int InputStringLength,
			bool CompareIsCaseSensitive, unsigned int *NextPositionInInputStringBeyondSuccessfulCompare);


	//	CompareOnShorterWithWildcards (overloaded version #2, where starting index into the local string is
	//		assumed to be zero)
	bool CompareOnShorterWithWildcards(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive,
			unsigned int *NextPositionInInputStringBeyondSuccessfulCompare);

	//  CompareWithWildcards (overloaded version #1 with unsigned char* input).
	bool CompareWithWildcards(const unsigned char *InputString, unsigned int InputStringLength, bool CompareIsCaseSensitive);

	//  Compare (overloaded version #2 with HSTRING* input).
	bool CompareWithWildcards(HSTRING *InputString, bool CompareIsCaseSensitive);

	//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString,
	//	using wildcards (overloaded version #1 with a unsigned char input string).
	bool FindWildcardString(const unsigned char *InputString, unsigned int InputStringLength, bool FindIsCaseSensitive,
			int OccurrenceNumberToFindOfInputString, int *PositionWhereInputStringWasFound);

	//	Search the local string for the nth (OccurrenceNumberToFindOfInputString) occurrence of InputString,
	//	using wildcards (overloaded version #2 with an input HSTRING).
	bool FindWildcardString(HSTRING *InputString, bool FindIsCaseSensitive, int OccurrenceNumberToFindOfInputString,
			int *PositionWhereInputStringWasFound);


	// CopyToOffset (overloaded version #1: unsigned char* input)
	bool CopyToOffset(unsigned int IndexToStartOfCopyLocation, const unsigned char *InputString, unsigned int LengthToCopy);


	// Search from the start index forward for the first occurrence of the caller specified
	// character.
	bool FindCharacterForward(unsigned char Character, unsigned int StartIndex,
			int *PositionWhereCharacterWasFound) const;

	// Search from the start index backward for the first occurrence of the caller specified
	// character.
	bool FindCharacterBackward(unsigned char Character, unsigned int StartIndex,
			int *PositionWhereCharacterWasFound) const;

	// Search from the start index forward for the first occurrence of a character not equal
	// to the caller specified character.
	bool FindNonCharacterForward(unsigned char Character, unsigned int StartIndex,
			int *PositionWhereNonCharacterWasFound) const;


	// Search from the start index backward for the first occurrence of a character not equal
	// to the caller specified character.
	bool FindNonCharacterBackward(unsigned char Character, unsigned int StartIndex,
			int *PositionWhereNonCharacterWasFound) const;

	// Return maximum size to caller.
	int MaximumLength(void) const;


	// Replace all occurrences of a string
	bool ReplaceAll(const char *StringToReplace, const char *ReplacementString);

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

public:
	// Static functions that are included here in case a target compiler "C" library does not contain them.

	// Static member function to determine if input character is a numeric digit.
	static int hhpisdigit( int ch );

	// Static member function to do a case sensitive character compare.  Input strings are assumed to be null terminated
	// and the number of character to compare is based on the shortest input string length.  There is one difference between
	// this and strcmp: this routine may optionally be instructed to compare the entire strings, meaning that if the lengths
	// aren't equal, but the strings are equal up to the end of the shorter string, a non-zero value will be returned.
	static int hhpstrcmp(const char *string1, const char *string2, bool CompareEntireString = false );

	// Static member function to do a case sensitive character compare.  Number of characters to compare is specified
	// by the caller.  There is one difference between this and strncmp: this routine may optionally be instructed to
	// compare the entire strings, meaning that it won't quit if it finds a NULL in one of the strings before it reaches
	// the character count.
	static int hhpstrncmp(const char *string1, const char *string2, unsigned int count, bool CompareEntireString = false );

	// Static member function to do a case insensitive character compare.  Input strings are assumed to be null terminated
	// and the number of character to compare is based on the shortest input string length.  There is one difference between
	// this and strcmp: this routine may optionally be instructed to compare the entire strings, meaning that if the lengths
	// aren't equal, but the strings are equal up to the end of the shorter string, a non-zero value will be returned.
	static int hhpstricmp(const char *string1, const char *string2, bool CompareEntireString = false );

	// Static member function to do a case insensitive character compare.  Number of characters to compare is specified
	// by the caller.  There is one difference between this and strnicmp: this routine may optionally be instructed to
	// compare the entire strings, meaning that it won't quit if it finds a NULL in one of the strings before it reaches
	// the character count.
	static int hhpstrnicmp(const char *string1, const char *string2, unsigned int count, bool CompareEntireString = false );

	// Static member function to parse a version string into numeric segments.  Returns true if the entire string was
	// consumed, false otherwise (version #1, using HSTRING input).
	static bool ParseRevisionString( HSTRING *InputString, int *AmountOfCharactersConsumed,
			int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments );

	// Static member function to parse a version string into numeric segments.  Returns true if the entire string was
	// consumed, false otherwise (version #2, using character string input).
	static bool ParseRevisionString( const char *InputString, int InputStringLength, int *AmountOfCharactersConsumed,
			int MaximumNumberOfVersionSegments, int *NumberOfVersionSegments, int *VersionSegments );
};

#endif		//	HSTRINGH
