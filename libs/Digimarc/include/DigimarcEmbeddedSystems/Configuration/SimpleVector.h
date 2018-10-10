// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_SIMPLEVECTOR_H
#define DMRC_DESSDK_SIMPLEVECTOR_H

#include <new>

#include "../SDK/ApiDefs.h"
#include "StatusCode.h"

namespace DigimarcEmbeddedSystems {

class Block;
class AdaptiveRegion;
class PerspectiveParams;

namespace Internal {

#ifdef _WIN32
template <typename T>
DMRC_API T* ArrayNew(unsigned int capacity);

template <typename T>
DMRC_API void ArrayDelete(const T* array);

template <> DMRC_API Block* ArrayNew<Block>(unsigned int capacity);
template <> DMRC_API void ArrayDelete<Block>(const Block* array);
template <> DMRC_API AdaptiveRegion* ArrayNew<AdaptiveRegion>(unsigned int capacity);
template <> DMRC_API void ArrayDelete<AdaptiveRegion>(const AdaptiveRegion* array);
template <> DMRC_API PerspectiveParams* ArrayNew<PerspectiveParams>(unsigned int capacity);
template <> DMRC_API void ArrayDelete<PerspectiveParams>(const PerspectiveParams* array);
template <> DMRC_API int* ArrayNew<int>(unsigned int capacity);
template <> DMRC_API void ArrayDelete<int>(const int* array);

#define ARRAY_NEW(type, n) ArrayNew<type>(n)
#define ARRAY_DELETE(ptr) ArrayDelete(ptr)

#else

#define ARRAY_NEW(type, n) new (std::nothrow) type[n]
#define ARRAY_DELETE(ptr) delete[] ptr

#endif

template <typename T>
class SimpleVector {
public:
	SimpleVector()
		: size(0)
		, capacity(0)
		, data(0)
	{
	}

	~SimpleVector() {
		ARRAY_DELETE(data);
	}

	StatusCode Append(const T& value) {
		StatusCode status = Resize();
		if (status == Success) {
			status = Copy(value, data[size]);
			if (status == Success) {
				++size;
			}
		}
		return status;
	}

	unsigned int GetSize() const {
		return size;
	}

	unsigned int GetCapacity() const {
		return capacity;
	}

	T& operator[](unsigned int i) {
		return data[i];
	}

	const T& operator[](unsigned int i) const {
		return data[i];
	}

	StatusCode CopyTo(SimpleVector& dst) const {
		StatusCode status = Success;
		if (this != &dst) {
			dst.size = 0;
			for (unsigned int i = 0; status == Success && i < size; ++i) {
				status = dst.Append(data[i]);
			}
		}
		return status;
	}

private:
	SimpleVector(const SimpleVector&);
	SimpleVector& operator=(const SimpleVector&);

	StatusCode Resize() {
		StatusCode status = Success;
		if (size == capacity) {
			status = Error_OutOfMemory;
			unsigned int newCapacity = capacity * 2;
			if (newCapacity == 0) {
				newCapacity = 1;
			}
			T* newData = ARRAY_NEW(T, newCapacity);
			if (newData) {
				status = Success;
				for (unsigned int i = 0; status == Success && i < size; ++i) {
					status = Copy(data[i], newData[i]);
				}
			}
			if (status == Success) {
				capacity = newCapacity;
				ARRAY_DELETE(data);
				data = newData;
				newData = 0;
			}
			ARRAY_DELETE(newData);
		}
		return status;
	}

	unsigned int size;
	unsigned int capacity;
	T* data;
};

}

}

#endif
