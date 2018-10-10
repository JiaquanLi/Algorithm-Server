//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  This template class is disigned to mimic the STL vector as much as
//  practical.  When we can't/don't meet ISO vector spec are noted in
//  each method's documentation.  These notes will be labelled
//  "ISO Note:".
//
//  ISO Note:  no methods will throw an exception and there is no true
//  iterator support (we return a pointer instead of an iterator).
//
//  ISO Note:  this container requires a default constructor for the
//  class T.  This also affects how push_back() and clear() work.  We
//  can change this, but there's a fair amount of time to code and test.
//  The more proper implementation would use a local copy of a memory
//  pool allocated on the heap, per the capacity needs(placement new).
//  Then we use that pool of memory and the class' copy contstructor
//  for creating the objects.  We would call the classe' destructor
//  explicitly when we remove them.
//
//  Limitations:  There are many methods not implemented.
//---------------------------------------------------------------------------

#ifndef _hvector_h_
#define _hvector_h_

#include <stdlib.h>

template <class T> class hvector
{
public:
	hvector(size_t size = 0);
	hvector(const hvector<T> & TheVector);

	~hvector(void)
	{
		delete [] m_pArray;
	}

	T * begin() {return m_pArray;} // ISO Note:  returns a T pointer, not an iterator
	const T * begin() const {return m_pArray;} // ISO Note:  returns a T pointer, not an iterator
	size_t size(void) const {return m_Size;}
	size_t capacity(void) const {return m_Capacity;}

	T & operator[](size_t index);
	const T & operator[](size_t index) const;
	hvector<T> & operator=(const hvector<T> & rhs);

	bool reserve(size_t NewCapacity);
	bool push_back(const T & item);
	void erase(size_t index);
	void clear(void);


protected:
	T * m_pArray;
	size_t m_Size;
	size_t m_Capacity;
};



/*----------------------------------------------------------------------------------------
hvector

  Constructor.  Will construct a vector with the optional size.

  ISO Note:  since we can't throw an exception, if we can't allocate the memory, we create 
  an empty vector.
  
  Parameters:  
				size[in]:  size of vector

  Returns:  nothing
----------------------------------------------------------------------------------------*/
template <class T> hvector<T>::hvector(size_t size /*= 0*/)
{
	m_pArray = new T[size];  // ISO C++ says we'll get a pointer if size is 0.  This is handy because we don't have to check for NULL everywhere.
	if ( m_pArray )
	{
		m_Size = size;
		m_Capacity = size;
	}
	else
	{	// we're out of ram.  Gracefully handle this by creating an empty array
		m_Size = 0;
		m_Capacity = 0;
		m_pArray = new T[m_Size];  // if we're so low on memory that THIS fails, we have bigger issues, so don't bother checking
	}
}


/*----------------------------------------------------------------------------------------
hvector

  Copy constructor.  Will construct a vector with the same size and values of the one
  passed.

  Parameters:  
				TheVector[in]:  the vector we will be set to

  Returns:  nothing
----------------------------------------------------------------------------------------*/
template <class T> hvector<T>::hvector(const hvector<T> & TheVector)
{
	m_pArray = new T[TheVector.size()];
	if ( m_pArray )
	{
		m_Size = TheVector.size();
		m_Capacity = m_Size;
		const T * pRhs = TheVector.begin();
		T * pArray = m_pArray;
		for (size_t i = 0; i < m_Size; i++)
		{
			*pArray = *pRhs;
			pArray++;
			pRhs++;
		}
	}
	else
	{	// we're out of ram.  Gracefully handle this by creating an empty array
		m_Size = 0;
		m_Capacity = 0;
		m_pArray = new T[m_Size];  // if we're so low on memory that THIS fails, we have bigger issues, so don't bother checking
	}
}


/*----------------------------------------------------------------------------------------
reserve

  Ensures vector can hold the number of bytes passed in.

  ISO Note:  since we can't throw an exception, if we can't allocate the memory, we leave
  things unchanged and return false.

  Parameters:  
				NewCapacity[in]:  minimum size of new vector

  Returns:  true if OK, false otherwise.
----------------------------------------------------------------------------------------*/
template <class T> bool hvector<T>::reserve(size_t NewCapacity)
{
	if ( NewCapacity > m_Capacity )
	{	// We need to re-allocate.  Keep member variables intact untill we safely allocated space for new array
		T * pNewArray;
		pNewArray = new T[NewCapacity];
		if ( pNewArray == NULL )
		{	// Failed allocation. 
			return false;
		}

		// It's now safe to modify member variables
		T * pOldArrayBytes = m_pArray;
		T * pNewArrayBytes = pNewArray;
		// memcpy(pNewArray, m_pArray, m_Size * sizeof(T)); //this won't work with objects with destructors as they will get called twice (1st time when we delete m_pArray below)  
		for (size_t i = 0; i < m_Size; i++ )
		{
			*pNewArrayBytes = *pOldArrayBytes;
			pNewArrayBytes++;
			pOldArrayBytes++;
		}

		delete [] m_pArray;
		m_pArray = pNewArray;
		m_Capacity = NewCapacity;
	}
	return true;
}



/*----------------------------------------------------------------------------------------
operator[]

  Allows you to set an item at a particular offset.

  ISO Note:  since we can't throw an exception, if the index is out of range, we use the
  the last index.

  Parameters:  
				index[in]:  offset of item in the vector

  Returns:  the item at that index.
----------------------------------------------------------------------------------------*/
template <class T> T & hvector<T>::operator[](size_t index)
{
	if ( index >= m_Size ) index = m_Size - 1;  // size_t is an unsigned variable
	return *(m_pArray + index);
}

/*----------------------------------------------------------------------------------------
operator[]

  Allows you to read an item at a particular offset.

  ISO Note:  since we can't throw an exception, if the index is out of range, we use the
  the last index.

  Parameters:  
				index[in]:  offset of item in the vector

  Returns:  the item at that index.
----------------------------------------------------------------------------------------*/
template <class T> const T & hvector<T>::operator[](size_t index) const
{
	if ( index >= m_Size ) index = m_Size - 1;  // size_t is an unsigned variable
	return *(m_pArray + index);
}


/*----------------------------------------------------------------------------------------
operator=

  Allows you to set one vector to another.

  ISO Note:  since we can't throw an exception, if we can't expand, we don't and we don't
  bother copying the data over.  It's up to the caller to check size() to ensure the
  assignment went OK.

  Parameters:  
				rhs[in]:  the vector we will be set to

  Returns:  this vector.
----------------------------------------------------------------------------------------*/
template <class T> hvector<T> & hvector<T>::operator=(const hvector<T> & rhs)
{
	if ( this == &rhs ) return *this;  // someone is assigning me to me
	if ( rhs.size() > m_Capacity )
	{	// we need more space to hold the larger vector
		T * pNewArray;
		pNewArray = new T[rhs.size()];
		if ( pNewArray == NULL )
		{	// Failed allocation. 
			return *this;
		}
		delete [] m_pArray;
		m_pArray = pNewArray;
		m_Capacity = rhs.size();
	}
	m_Size = rhs.size();
	// now do the copying
	const T * pRhs = rhs.begin();
	T * pArray = m_pArray;
	for (size_t i = 0; i < m_Size; i++)
	{
		*pArray = *pRhs;
		pArray++;
		pRhs++;
	}

	return *this;
}




/*----------------------------------------------------------------------------------------
push_back

  Appends an item at the end of the vector.

  ISO Note:  since we can't throw an exception, if we need to grow the vector and can't,
  we return false.

  Parameters:  
				item[in]:  item to add to the vector

  Returns:  true if OK, false otherwise.
----------------------------------------------------------------------------------------*/
template <class T> bool hvector<T>::push_back(const T & item)
{
	if ( m_Size == m_Capacity )
	{
		size_t extra = m_Capacity/4;
		if ( ! extra ) extra = 4;
		size_t NewCapacity = m_Capacity + extra;  // increase by 25% to keep re-allocations down
		if ( ! reserve(NewCapacity) ) return false;
	}
	*(m_pArray + m_Size) = item;  // m_Size right now is the index of the new last item in the array
	m_Size++;
	return true;
}

/*----------------------------------------------------------------------------------------
erase

  Erases an item.

  ISO Note:  This returns void instead of an iterator.  There is no overload to allow
  removing a range of items.

  Parameters:  
				index[in]:  index of item to remove

  Returns:  nothing.
----------------------------------------------------------------------------------------*/
template <class T> void hvector<T>::erase(size_t index)
{
	if ( index >= m_Size ) return;

	T * pFirstVal = (m_pArray + index);
	T * pNextVal = (m_pArray + index + 1);
	size_t NumToMove = m_Size - index - 1;
	for (size_t i = 0; i < NumToMove; i++)
	{
		*pFirstVal = *pNextVal;
		pFirstVal++;
		pNextVal++;
	}
	m_Size--;
}


/*----------------------------------------------------------------------------------------
clear

  Removes all items from the list, but keeps the capacity.


  Parameters:  none

  Returns:  nothing.
----------------------------------------------------------------------------------------*/
template <class T> void hvector<T>::clear(void)
{
	m_Size = 0;
}

#endif
