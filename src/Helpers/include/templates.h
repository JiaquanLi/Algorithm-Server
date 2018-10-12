#ifndef _TEMPLATES_H_09241376_697b_446e_94f9_1f75d6246c9c
#define _TEMPLATES_H_09241376_697b_446e_94f9_1f75d6246c9c

template <class T>
T bound(const T & lower, const T & t, const T & upper)
{
	if (t < lower)
		return lower;
	if (t > upper)
		return upper;
	return t;
}

template<typename T, size_t N>
constexpr size_t elementsof(T (&)[N]) { return N; }

// equal_any will compare object to the other arguments (first and rest).
// Returns true when it finds an argument it is equal to.  Otherwise, returns
// false.

template <typename T, typename ARG>
inline bool equal_any(T && object, ARG && first)
{
	return object == first;
}

template <typename T, typename ARG, typename ... ARGS>
inline bool equal_any(T && object, ARG && first, ARGS && ... rest)
{
	return object == first || equal_any(std::forward<T>(object), std::forward<ARGS>(rest)...);
}

// Forward declarations used by SharedAccess below.
namespace std{
	class mutex;
	template<typename _Mutex> class unique_lock;
};

/** @brief @c shared_access uses a mutex to protect a shared object of type @c T.
 *
 * @c shared_access manages a private object of type @c T.  @c shared_access insures
 * that a lock on a mutex must be held in order to access the object.
 * To get access to the object, the @c getlock method must be called to
 * create a @c lock object. The @c lock object holds a lock on a @c std::mutex
 * until it is destroyed.  The @c lock object has an @c operator-> that access
 * the @c T object.
 */

template <typename T, typename MTX = std::mutex>
class SharedAccess
{
public:
	/** @brief Constructor a @c shared_access object.
	 *
	 * The @c shared_access has a private object of type @c T.  The arguments, @c args, are passed
	 * to the constructor for the @c T object.
	 */
	template<typename... ARGS>
	SharedAccess(ARGS && ... args) : object(std::forward<ARGS>(args)...)
	{
	}

	/** @brief A @c lock object holds a lock on a mutex and allows access to the
	 * underlying @c T object.
	 */
	class lock
	{
	public:
		T * operator->() const { return pobject; }
		T * get() const { return pobject; }
		lock(lock && l) :
			pobject(l.pobject),
			lck(std::move(l.lck))
		{
			l.pobject = 0;
		}
		~lock() { pobject = 0; }
	private:
		friend class SharedAccess;
		T * pobject;
		std::unique_lock<MTX> lck;
		lock(MTX & mtx, T * pobject) : pobject(pobject), lck(mtx) {}
	};

	/** @brief Get a lock to allow access ot the @c T object. */
	lock getlock()
	{
		return lock(mtx, &object);
	}
private:


	MTX mtx;
	T object;
};

#endif // #ifndef _TEMPLATES_H_09241376_697b_446e_94f9_1f75d6246c9c
