//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//  The purpose of this class is to provide a template for data object arrays.
//	It is based on the Microsoft CObArray.
//
//  NOTE:  The method Add(DataType *) requires the class to have the following
//  constructor:  DataType(DataType*).  That is, a constructor that has a
//  single parameter that is a pointer to the class.
//---------------------------------------------------------------------------

#ifndef	__DATA_ARRAY_H
#define	__DATA_ARRAY_H

// Alignment math functions.
//template <class DataType> DataType ComputeAlignment(DataType AlignmentBase, DataType Offset);
//template <class DataType> DataType ComputeMisAlignment(DataType MisAlignmentBase, DataType Offset);



//template <class DataType> bool MemoryCopy(DataType *Destination, DataType *Source, int AmountOfDataToCopy);

//template <class DataType> int StringLength(DataType *InputString);



template <typename DataType> class DATA_ARRAY
{
private:
	#define		MINIMUM_SIZE_CHANGE_ON_REALLOCATION		10
	#define		MAXIMUM_SIZE_CHANGE_ON_REALLOCATION		20
	int			ElementsAddedDuringLastResize;
	bool		AutoResizeEnabled;
	int			NumberOfNewElementsSinceAutoResize;
	int			MinimumSizeChangeOnReallocation;


	
	int						ItemSize;
	int						AllocatedSize;


private:
	int						NumberOfElements;
	int						MaximumNumberOfElements;
	DataType				**Elements;


public:
// Constructors
	DATA_ARRAY( void );

// Destructor
	~DATA_ARRAY(void);

// Allow instantiator to change minimum reallocation size.
	void SetMinimumSizeChangeOnReallocation( int NewMinimumSizeChangeOnReallocation );

// Zero the elements in the range specied by the caller, and shift any elements above the range to fill in the vacant spaces.
	void RemoveAt( int ElementToBeginZeroingAt, int Count = 1 );

// Zero the upper part of the array
	void RemoveUpperElements( int ElementToBeginZeroingAt = 0 );

// Zero the array
	void RemoveAll( void );

// Return the number of elements in the array.
	int GetSize( void );

// Set the number of elements in the array to the caller specified value.  If this new size is less than the number
// of elements currently defined, zero the extraneous elements.  If the new size is greater than the current maximum,
// reallocate over and above what is needed by either the caller specified amount (if not -1) or the default amount.
	void SetSize( int NewSize, int GrowBy = -1 );

// Resize the allocated space, copying the existing string to the new one.  Don't resize if the string will be too small
// to retain existing data.
	bool Reallocate( int NewNumberOfElements, int GrowBy = -1 );

// Return the address of the caller specified element in the array.
	DataType *& ElementAt( int ElementNumber );

// Return the address of the elements array.
	DataType ** GetData( void );

// Add a new element
	int Add( DataType *Element );

// Return the highest number element in the array.
	int GetUpperBound( void );

};












// Constructors
template <typename DataType> DATA_ARRAY<DataType>::DATA_ARRAY( void )
{
	NumberOfElements = 0;
	MinimumSizeChangeOnReallocation = MINIMUM_SIZE_CHANGE_ON_REALLOCATION;
	MaximumNumberOfElements = MinimumSizeChangeOnReallocation;
	Elements = new DataType * [ MaximumNumberOfElements ];

	return;
}





template <typename DataType> DATA_ARRAY<DataType>::~DATA_ARRAY(void)
{
	RemoveAll();

	delete [] Elements;

	return;
}






//
//	SetMinimumSizeChangeOnReallocation
//		Allow instantiator to change minimum reallocation size.
//
template <typename DataType> void DATA_ARRAY<DataType>::SetMinimumSizeChangeOnReallocation
							( int NewMinimumSizeChangeOnReallocation )
{
	MinimumSizeChangeOnReallocation = NewMinimumSizeChangeOnReallocation;
	return;
} // SetMinimumSizeChangeOnReallocation





//
//	RemoveAt
//		Zero the elements in the range specied by the caller, and shift any elements above the range to fill in the vacant
//		spaces.
//
template <typename DataType> void DATA_ARRAY<DataType>::RemoveAt( int ElementToBeginZeroingAt, int Count )
{
	int		i;


	if(( ElementToBeginZeroingAt >= 0 ) && ( Count <= NumberOfElements ) &
						( ( ElementToBeginZeroingAt + Count ) <= NumberOfElements ))
	{
		for( i = ElementToBeginZeroingAt;    i < ( ElementToBeginZeroingAt + Count );    ++i )
		{
			delete Elements[ i ];
		}

	// Squeeze out the upper elements.
		for( i = ElementToBeginZeroingAt + Count;    i < NumberOfElements;    ++i )
		{
			Elements[ i - Count ] = Elements[ i ];
		}


		NumberOfElements -= Count;
	}


	return;
} // RemoveAt





//
//	RemoveUpperElements
//		Zero the upper elements of the array beginning at the caller specified element (default is zero).
//
template <typename DataType> void DATA_ARRAY<DataType>::RemoveUpperElements( int ElementToBeginZeroingAt )
{
	RemoveAt( ElementToBeginZeroingAt, NumberOfElements - ElementToBeginZeroingAt );

	return;
} // RemoveUpperElements





//
//	RemoveAll
//		Zero the array.
//
template <typename DataType> void DATA_ARRAY<DataType>::RemoveAll( void )
{
	RemoveUpperElements( 0 );

	return;
} // RemoveAll






//
//	GetSize
//		Return the number of elements in the array.
//
template <typename DataType> int DATA_ARRAY<DataType>::GetSize( void )
{
	return NumberOfElements;
} // GetSize





//
//	SetSize
//		Set the number of elements in the array to the caller specified value.  If this new size is less than the number
//		of elements currently defined, zero the extraneous elements.  If the new size is greater than the current maximum,
//		reallocate over and above what is needed by either the caller specified amount (if not -1) or the default amount.
//
template <typename DataType> void DATA_ARRAY<DataType>::SetSize( int NewSize, int GrowBy )
{
	if( NewSize < NumberOfElements )
	{
		RemoveUpperElements( NewSize );
	}
	else
	{
		Reallocate( NewSize, GrowBy );
		
		while( NumberOfElements < NewSize )
		{
			Elements[ NumberOfElements ] = new DataType();
			++NumberOfElements;
		}
	}


	return;
} // SetSize






//
//	Reallocate
//      Resize the allocated space, copying the existing string to the new one.  Don't resize if the string will be too small
//		to retain existing data.
//
template <typename DataType> bool DATA_ARRAY<DataType>::Reallocate( int NewNumberOfElements, int GrowBy )
{
	bool			Status = false;		// Haven't succeeded yet.



// If reallocating will make the array too small to retain existing data, don't do the reallocate!
	if( NewNumberOfElements <= NumberOfElements )
	{
		Status = true;
	}

// We know we're getting bigger (otherwise, we would have quit above), so we won't reallocate the maximum unless we've run
// out of space.
	else if( NewNumberOfElements <= MaximumNumberOfElements )
	{
		Status = true;
	}

// We've run out of space, so we have to reallocate.
	else
	{
		MaximumNumberOfElements = NewNumberOfElements + (( GrowBy > -1 ) ? GrowBy : MinimumSizeChangeOnReallocation );

		DataType		**TempElements = new DataType * [ MaximumNumberOfElements ];

		if( TempElements != 0 )
		{
			int		i;

			for( i = 0;    i < NumberOfElements;    ++i )
			{
				TempElements[ i ] = Elements[ i ];
			}

			delete Elements;
		    Elements = TempElements;

			Status = true;
		}
	}

    return(Status);
} // Reallocate






//
//	ElementAt
//		Return the address of the caller specified element in the array.
//
template <typename DataType> DataType *& DATA_ARRAY<DataType>::ElementAt( int ElementNumber )
{
	if(( ElementNumber >= 0 ) && ( ElementNumber < NumberOfElements ))
	{
		return Elements[ ElementNumber ];
	}
	else
	{
		return Elements[ 0 ];
	}
} // ElementAt






//
//	GetData
//		Return the address of the elements array.
//
template <typename DataType> DataType ** DATA_ARRAY<DataType>::GetData( void )
{
	return Elements;
} // GetData






//
//	Add
//		Add a new element.
//
template <typename DataType> int DATA_ARRAY<DataType>::Add( DataType *Element )
{
	int		NewElementIndex = -1;


	if( Reallocate( NumberOfElements + 1 ) )
	{
		NewElementIndex = NumberOfElements;

		Elements[ NumberOfElements ] = new DataType( Element );

		++NumberOfElements;
	}

	return NewElementIndex;
} // Add




//
//	GetUpperBound
//		Return the highest number element in the array.
//
template <typename DataType> int DATA_ARRAY<DataType>::GetUpperBound( void )
{
	return ( NumberOfElements - 1 );
} // GetUpperBound

#endif
