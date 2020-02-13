// ----------------------------------------------------------------------------
// File: Utilities.h
// Desc: Common utilities for usage, like singletons, casts, helper functions, 
//       etc...
// Auth: Michael Petrou
// (C) Copyright:   2004
// ----------------------------------------------------------------------------
#ifndef UTILITIES_H
#define UTILITIES_H


// ----------------------------------------------------------------------------
// We dont need all of windows whistles, bells, and overheads
// ----------------------------------------------------------------------------
#ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
#endif


// ----------------------------------------------------------------------------
// We want to keep to the ISO standard
// ----------------------------------------------------------------------------
#ifndef STRICT
#  define STRICT
#endif


// ----------------------------------------------------------------------------
// Common header files
// ----------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
#include <new>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <time.h>


// ----------------------------------------------------------------------------
// Define epsilon for our float
// ----------------------------------------------------------------------------
#ifndef EPSILON
#define EPSILON 0.001f
#endif


// ----------------------------------------------------------------------------
// Name: Utility (namespace)
// Desc: Namespace for all utility functions and classes
// ----------------------------------------------------------------------------
namespace Utility
{

    // ----------------------------------------------------------------------------
    // Name: Clamp
    // Temp: The type of the object we are going to clamp.  Note - must have the 
    //       less-than and greater-than operators defined.
    // Desc: Useful here and there, allows the user to 'snap' a variable to lie 
    //       within the bounds of two inputted vars
    // Parm: T &a          - the object we are clamping
    // Parm: const T &min  - the lower bound
    // Parm: const T &max  - the upper bound
    // ----------------------------------------------------------------------------
    template <class T>
    static void Clamp(T &a, const T &min, const T &max)
    {
        if (a < min)
            a = min;
        if (a > max) 
            a = max;
    } // Clamp


    // ----------------------------------------------------------------------------
    // Name: Swap
    // Temp: The type of the items we are swapping
    // Desc: Swaps the values of A and B
    // Parm: T &a - the first item
    // Parm: T &b - the second item
    // ----------------------------------------------------------------------------
    template<class T>
    void Swap(T &a, T &b)
    {
        const T temp = a;
        a = b;
        b = temp;
    } // Swap


    // ----------------------------------------------------------------------------
    // Name: Unique (class)
    // Desc: A base class for all classes that should not be copied through a copy 
    //       constructor or through assignment, making the class unique. Such non-
    //       copyable classes should be derived privately from the Unique class.
    // ----------------------------------------------------------------------------
    class Unique
    {
    protected:
        // ------------------------------------------------------------------------
        // Constructor and destructor
        // ------------------------------------------------------------------------
                 Unique() {}
        virtual ~Unique() {}

    private:
        // ------------------------------------------------------------------------
        // Private copy constructor and assignment operator
        // ------------------------------------------------------------------------
              Unique           (const Unique &);
        const Unique &operator=(const Unique &);
    }; // class Unique


    // ----------------------------------------------------------------------------
    // Name: NoInstance (class)
    // Desc: A base class for all classes that should not be instantiated - for
    //       example a static factory.
    // ----------------------------------------------------------------------------
    class NoInstance
    {
    public:
        // ------------------------------------------------------------------------
        // Public destructor
        // ------------------------------------------------------------------------
        virtual ~NoInstance() {}


    private:
        // ------------------------------------------------------------------------
        // Private constructor
        // ------------------------------------------------------------------------
        NoInstance() {}
        
    }; // class NoInstance
}; // namespace Utility


// ------------------------------------------------------------------------
// Name: Binary (namespace)
// Desc: Binary read / write functions
// ------------------------------------------------------------------------
namespace Binary
{
    // --------------------------------------------------------------------
    // Name: WriteBinaryString
    // Desc: Write a std::string to a binary file
    // Parm: FILE *file              - the file
    // Parm: const std::string &text - the string
    // Retn: bool                    - true if successful
    // --------------------------------------------------------------------
    inline bool WriteBinaryString(FILE *file, const std::string &text)
    {
        int written = 0;
	    for (size_t i = 0; i < text.size(); i++)
		    written += fwrite(&text[i], sizeof(char), 1, file);

	    char zero = 0;
	    written += fwrite(&zero, sizeof(char), 1, file);

        return (written == text.size() + 1);
    } // WriteBinaryString


    // --------------------------------------------------------------------
    // Name: ReadBinaryString
    // Desc: Read a std::string from a binary file
    // Parm: FILE *file        - the file
    // Parm: std::string &text - a reference to the string
    // Retn: bool              - true if successful
    // --------------------------------------------------------------------
    inline bool ReadBinaryString(FILE *file, std::string &text)
    {
        text.clear();
        int read = 0, size = 0;

        char character;
        read += fread(&character, sizeof(char), 1, file);
        size++;

        while (character != 0)
        {
            text += character;
            read += fread(&character, sizeof(char), 1, file);
            size++;
        } // while

        return (read == size);
    } // ReadBinaryString


}; // namespace Binary


// ------------------------------------------------------------------------
// Name: Memory (namespace)
// Desc: Namespace for all memory utilities
// ------------------------------------------------------------------------
namespace Memory
{
    // ----------------------------------------------------------------------------
    // Name: SafeRelease
    // Temp: The interface type we are releasing
    // Desc: The Right Way to release our COM interfaces. If they're still valid, 
    //       release them, then invalidate them.
    // Parm: T& iface - the interface to release
    // ----------------------------------------------------------------------------
    template <class T>
    inline void SafeRelease(T& iface)
    {
        if (iface)
        {
            iface->Release();
            iface = 0;
        } // if
    } // SafeRelease


    // ----------------------------------------------------------------------------
    // Name: AutoZero  (struct)
    // Temp: The DirectX structure type we are going to zero-out
    // Desc: This struct takes care of the annoying gruntwork of having to zero-out 
    //       and set the size parameter of our Windows and DirectX structures.
    // ----------------------------------------------------------------------------
    template <class T>
    struct AutoZero : public T
    {
        AutoZero()
        {
            memset(this, 0, sizeof(T));
            dwSize = sizeof(T);
        } // AutoZero
    }; // struct AutoZero


    // --------------------------------------------------------------------
    // Name: RefCounted (class)
    // Desc: Reference counting base class
    // --------------------------------------------------------------------
    class RefCounted
    {
    public:
        // ----------------------------------------------------------------
        // Constructor and destructor
        // ----------------------------------------------------------------
                    RefCounted() : m_ref_ctr(1) {}
        virtual    ~RefCounted()                {}

        
        // ----------------------------------------------------------------
        // Increment and decrement the reference count
        // ----------------------------------------------------------------
        int         Ref()           { return ++m_ref_ctr; }
        int         UnRef()         { m_ref_ctr--; 
                                      if (m_ref_ctr <= 0) 
                                          delete this; 
                                      return m_ref_ctr;   }

        
        // ----------------------------------------------------------------
        // Get the reference count
        // ----------------------------------------------------------------
        int         GetRefCount()   { return m_ref_ctr; }


    private:
        // ----------------------------------------------------------------
        // Privates for this class
        // ----------------------------------------------------------------
        int         m_ref_ctr;  // The reference count

    }; // class RefCounted


    // --------------------------------------------------------------------
    // Name: SafeUnRef
    // Desc: Derefernces an object, but checks that teh object exists first 
    //       (is not null)
    // Parm: RefCounted *pobj - the object to unref
    // Retn: int      - the final reference count, or -1 if the object does 
    //       not exist
    // --------------------------------------------------------------------
    inline int SafeUnRef(RefCounted *pobj)
    {
        if (pobj)
            return pobj->UnRef();
        return -1;
    } // SafeUnref


}; // namespace Memory


// ------------------------------------------------------------------------
// Name: Random (namespace)
// Desc: Namespace for all random number functions
// ------------------------------------------------------------------------
namespace Random
{
    // ----------------------------------------------------------------------------
    // Random seed
    // ----------------------------------------------------------------------------
    static unsigned long s_seed = timeGetTime();


    // ----------------------------------------------------------------------------
    // Name: IntRand
    // Desc: Get a random integer
    // Parm: int min = 0    - the minimum value
    // Parm: int max = 100  - the maximum value
    // Retn: int            - the random number
    // ----------------------------------------------------------------------------
    inline int IntRand(int min = 0, int max = 100)
    {
        return min + ((((s_seed = s_seed * 214013L + 2531011L) >> 16) & 0x7fff) % (max - min));
    } // IntRand


    // ----------------------------------------------------------------------------
    // Name: FloatRand
    // Desc: Get a random float
    // Parm: float min = 0.0f  - the minimum value
    // Parm: float max = 1.0f  - the maximum value
    // Retn: float             - the random number
    // ----------------------------------------------------------------------------
    inline float FloatRand(float min = 0.0f, float max = 1.0f)
    {
        // Dodgy algorithm - works, but dodgy.
        int     accuracy    = 4852;
        int     int_rand    = IntRand(0, accuracy);
        float   result      = min + (max-min) * ((float) int_rand / accuracy);

        return result;
    } // RandFloat


}; // namespace Random


// ------------------------------------------------------------------------
// Name: Singleton (namespace)
// Desc: Namespace for singleton classes
// ------------------------------------------------------------------------
namespace Singleton
{
    // ----------------------------------------------------------------------------
    // Name: CreateUsingNew (struct)
    // Temp: The type that is created and destroyed.
    // Desc: Implementation of the creation policy used by SingletonHolder. Creates 
    //       objects using a straight call to the new operator.
    // ----------------------------------------------------------------------------
    template <class T>
    struct CreateUsingNew
    {
        // ------------------------------------------------------------------------
        // Create using new, destroy using delete
        // ------------------------------------------------------------------------
        static T    *Create()       { return new T; }
        static void Destroy(T *p)   { delete p; }
    }; // struct CreateUsingNew


    // ----------------------------------------------------------------------------
    // Name: CreateUsingMalloc (struct)
    // Temp: The type that is created and destroyed.
    // Desc: Implementation of the creation policy used by SingletonHolder. Creates 
    //       objects using a call to std::malloc, followed by a call to the 
    //       placement new operator
    // ----------------------------------------------------------------------------
    template <class T>
    struct CreateUsingMalloc
    {
        // ------------------------------------------------------------------------
        // Create using malloc followed by placement new
        // ------------------------------------------------------------------------
        static T *Create()
        {
            // Allocate the memory
            void *p = std::malloc(sizeof(T));
            if (!p)
                return 0;

            // Construct the object
            return new(p) T;
        } // Create

        
        // ------------------------------------------------------------------------
        // Manually call the constructor, then free the memory using free
        // ------------------------------------------------------------------------
        static void Destroy(T *p)
        {
            p->~T();
            std::free(p);
        } // Destroy
    }; // struct CreateUsingMalloc


    // ----------------------------------------------------------------------------
    // Name: CreateStatic (struct)
    // Temp: The type that is created and destroyed.
    // Desc: Creates an object in static memory. Implementation is slightly non-
    //       portable because it uses the MaxAlign trick (a union of all types to 
    //       ensure proper memory alignment). This trick is non-portable in theory, 
    //       but highly portable in practice.
    // ----------------------------------------------------------------------------
    template <class T>
    struct CreateStatic
    {
        // ------------------------------------------------------------------------
        // Create a union to align memory
        // ------------------------------------------------------------------------
        union MaxAlign
        {
            char            m_t[sizeof(T)];
            short int       m_short_int;
            int             m_int;
            long int        m_long_int;
            float           m_float;
            double          m_double;
            long double     m_long_double;
            struct          Test;
            int             Test::* m_pmember;
            int            (Test::*m_pmember_func)(int);
        }; // MaxAlign

        // ------------------------------------------------------------------------
        // Create on the stack (static) and then call placement new
        // ------------------------------------------------------------------------
        static T *Create()
        {
            static MaxAlign s_static_memory;

            // Call the constructor using placement new
            return new(&s_static_memory) T;
        } // Create

        // ------------------------------------------------------------------------
        // Call the destructor - when the stack disappears the memory will be 
        // deallocated
        // ------------------------------------------------------------------------
        static void Destroy(T *p)
        {
            p->~T();
        } // Destroy
    }; // struct CreateStatic


    // ----------------------------------------------------------------------------
    // Name: SingletonHolder (class)
    // Temp: T              - the object type to make a singleton instance of.
    // Temp: CreationPolicy - the policy used to construct the songleton.  Must
    //       have the Create and Destroy functions.
    // Desc: Provides singleton amenities for type T. To protect that type from 
    //       spurious instantiations, you have to protect it yourself.
    // ----------------------------------------------------------------------------
    template <typename T, class CreationPolicy>
    class SingletonHolder
    {
    public:
        // ------------------------------------------------------------------------
        // Get the object by reference or pointer
        // ------------------------------------------------------------------------
        static T &Instance();
        static T *GetPtr();


        // ------------------------------------------------------------------------
        // Make the instance and destroy the instance - note these are called 
        // implicitly but may be called explicitly if a specific order of operation 
        // is required.'
        // ------------------------------------------------------------------------
        static void MakeInstance();
        static void DestroyInstance();

    private:
        // ------------------------------------------------------------------------
        // Protected constructor so that we can't try to instantiate it manually
        // ------------------------------------------------------------------------
                SingletonHolder();
                SingletonHolder<T, CreationPolicy> &operator=(const SingletonHolder<T, CreationPolicy> &other);
        explicit SingletonHolder(const SingletonHolder<T, CreationPolicy> &other);


        // ----------------------------------------------------------------------------
        // The data pointer type
        // ----------------------------------------------------------------------------
        typedef T *PtrInstanceType;


        // ------------------------------------------------------------------------
        // Privates for this class
        // ------------------------------------------------------------------------
        static PtrInstanceType  s_pinstance;    // The object instance
        static bool             s_destroyed;    // Is the instance destroyed
    }; // class SingletonHolder



    // ----------------------------------------------------------------------------
    // Instantiate the static data
    // ----------------------------------------------------------------------------
    template <class T, class C>
    typename SingletonHolder<T, C>::PtrInstanceType SingletonHolder<T, C>::s_pinstance = 0;
    template <class T, class C>
    bool SingletonHolder<T, C>::s_destroyed = false;


    // ----------------------------------------------------------------------------
    // Name: CreationPolicy>::Instance
    // Temp: T              - the object type to make a singleton instance of.
    // Temp: CreationPolicy - the policy used to construct the songleton.  Must
    //       have the Create and Destroy functions.
    // Desc: Returns a reference to the singleton class. If the class has not yet 
    //       been created it is created now.
    // Retn: T &SingletonHolder<T, - A reference to the singleton
    // ----------------------------------------------------------------------------
    template <class T, class CreationPolicy>
    inline T &SingletonHolder<T, CreationPolicy>::Instance()
    {
        if (!s_pinstance)
            MakeInstance();

        return *s_pinstance;
    } // Instance


    // ----------------------------------------------------------------------------
    // Name: CreationPolicy>::GetPtr
    // Temp: T              - the object type to make a singleton instance of.
    // Temp: CreationPolicy - the policy used to construct the songleton.  Must
    //       have the Create and Destroy functions.
    // Desc: Returns a pointer to the singleton class. If the class has not yet been
    //       created it returns 0.
    // Retn: T *SingletonHolder<T, - A pointer to the singleton
    // ----------------------------------------------------------------------------
    template <class T, class CreationPolicy>
    inline T *SingletonHolder<T, CreationPolicy>::GetPtr()
    {
        return s_pinstance;
    } // GetPtr


    // ----------------------------------------------------------------------------
    // Name: CreationPolicy>::MakeInstance
    // Temp: T              - the object type to make a singleton instance of.
    // Temp: CreationPolicy - the policy used to construct the singleton.  Must
    //       have the Create and Destroy functions.
    // Desc: Creates an instance of the singleton object
    // ----------------------------------------------------------------------------
    template <class T, class CreationPolicy>
    inline void SingletonHolder<T, CreationPolicy>::MakeInstance()
    {
        if (!s_pinstance)
        {
            s_destroyed = false;
            s_pinstance = CreationPolicy::Create();

            // Reigster with atexit to ensure destruction. If we manually
            // destroy then these extra calls to DestroyInstance will just
            // be without effect
            atexit(&SingletonHolder<T, CreationPolicy>::DestroyInstance);
        } // if
    } // MakeInstance


    // ----------------------------------------------------------------------------
    // Name: CreationPolicy>::DestroyInstance
    // Temp: T              - the object type to make a singleton instance of.
    // Temp: CreationPolicy - the policy used to construct the singleton.  Must
    //       have the Create and Destroy functions.
    // Desc: Destroys the singleton instance
    // ----------------------------------------------------------------------------
    template <class T, class CreationPolicy>
    inline void SingletonHolder<T, CreationPolicy>::DestroyInstance()
    {
        // Check that we aren't already destroyed
        if (!s_destroyed)
        {
            CreationPolicy::Destroy(s_pinstance);
            s_pinstance = 0;
            s_destroyed = true;
        } // if
    } // DestroyInstance
}; // namespace Singleton


// ------------------------------------------------------------------------
// Name: Functional (namespace)
// Desc: Namespace for functional classes and functions, for callbacks and 
//       member pointers, etc...
// ------------------------------------------------------------------------
namespace Functional
{
    // ----------------------------------------------------------------------------
    // Name: Callback (class)
    // Temp: Templated based on return type and argument type of callback function.
    // Desc: Base class for all call-backs that take one parameter.  To derive from
    //       this class create a suitable constructor, and define the () operator.
    // ----------------------------------------------------------------------------
    template <typename R, typename A>
    class Callback
    {
    public:
        // ------------------------------------------------------------------------
        // typedefs for adaptability (use as predicates, etc)
        // ------------------------------------------------------------------------
        typedef R result_type;
        typedef A argument_type;


    public:
        // ------------------------------------------------------------------------
        // Make destructor virtual
        // ------------------------------------------------------------------------
        virtual ~Callback() {}


        // ------------------------------------------------------------------------
        // Call operator for the callback
        // ------------------------------------------------------------------------
        virtual R operator()(A arg) const = 0;


        // ------------------------------------------------------------------------
        // Assignment from another callback
        // ------------------------------------------------------------------------
        virtual bool operator==(const Callback<R, A> &rhs) const = 0;


        // ------------------------------------------------------------------------
        // Clone this callback
        // ------------------------------------------------------------------------
        virtual Callback<R, A> *Clone() const = 0;

        
        // ------------------------------------------------------------------------
        // Get the callback type0id
        // ------------------------------------------------------------------------
        virtual int GetTypeID() const = 0;
    }; // class Callback


    // ----------------------------------------------------------------------------
    // Name: MemberCallback  (class)
    // Temp: R - the return type
    // Temp: O - the object type
    // Temp: A - the argument type
    // Desc: A class that acts as a callback to a member function. It thus requires 
    //       the address of the object whose member function will be called. 
    // Note: The () operator is const, so that it can be called even when the 
    //       callback object is const. To do this, we need to make the pointer to 
    //       the object mutable, so that we can modify this within a const (())
    //       function.
    // ----------------------------------------------------------------------------
    template <typename R, class O, typename A>
    class MemberCallback : public Callback<R, A>
    {
        public:
            // --------------------------------------------------------------------
            // Name: MemberCallback
            // Desc: Constructor
            // Parm: O *pobj        - the object that holds the member function that
            //       this callback will be attached to
            // Parm: R (O::*pm)(A)) - a pointer to the member function
            // --------------------------------------------------------------------
            MemberCallback(O *pobj, R (O::*pm)(A)) : m_pobj(pobj), m_pm(pm) { };


            // --------------------------------------------------------------------
            // Name: operator
            // Desc: The call operator that calls the member callback
            // Parm: A arg - the value to pass into the callback function
            // Retn: R     - the return value
            // --------------------------------------------------------------------
            virtual R operator()(A arg) const
            {
                return (m_pobj->*m_pm)(arg);
            } // operator()


            // --------------------------------------------------------------------
            // Name: operator==
            // Desc: Equality operator for comparing two callbacks
            // Parm: const Callback<R, A> &rhs - the callback to compare with this 
            //       callback
            // Retn: bool     - true if they are equal
            // --------------------------------------------------------------------
            virtual bool operator==(const Callback<R, A> &rhs) const
            {
                // If the incoming callback has the same () operator as this class
                // then the classes are the same. This is because we do not
                // want to use RTTI, which is the most obvious choice here.
                if (this->GetTypeID() != rhs.GetTypeID())
                    return false;

                // They are of the same type (if they didn't define (), then
                // something is wrong. Cast to this type, and compare member
                // variables
                const MemberCallback<R, O, A> *prhs = static_cast<const MemberCallback<R, O, A> *>(&rhs);
                if ((m_pm == prhs->m_pm) && (m_pobj == prhs->m_pobj))
                    return true;

                return false;
            } // operator==


            // --------------------------------------------------------------------
            // Name: Clone
            // Desc: Clone this member callback using new
            // Retn: MemberCallback<R, O, A> * - a pointer to the newly constructed 
            //       callback
            // --------------------------------------------------------------------
            virtual MemberCallback<R, O, A> *Clone() const
            {
                return new MemberCallback<R, O, A>(m_pobj, m_pm);
            } // Clone


            // --------------------------------------------------------------------
            // Name: GetTypeID
            // Desc: Get the member callback class type id (in this case 1)
            // Retn: int - the id
            // --------------------------------------------------------------------
            virtual int GetTypeID() const { return 1; }

        private:
            // --------------------------------------------------------------------
            // The member function type
            // --------------------------------------------------------------------
            typedef R (O::*MemFunType) (A);


            // --------------------------------------------------------------------
            // Privates for this class
            // --------------------------------------------------------------------
            mutable O      *m_pobj; // The object instance
            MemFunType      m_pm;   // The member function pointer
    }; // class MemberCallback


    // ----------------------------------------------------------------------------
    // Name: StaticCallback  (class)
    // Temp: R - the return type
    // Temp: A - the argument type
    // Desc: A class that acts as a callback to a static function. This can be 
    //       either a static member function, or a global function.
    // Note: The () operator is const, so that it can be called even when the 
    //       callback object is const. To do this, we need to make the pointer to 
    //       the object mutable, so that we can modify this within a const (())
    //       function.
    // ----------------------------------------------------------------------------
    template <typename R, typename A>
    class StaticCallback : public Callback<R, A>
    {
        public:
            // --------------------------------------------------------------------
            // Name: StaticCallback
            // Desc: Constructor
            // Parm: R (O::*pf)(A)) - a pointer to the static funtion
            // --------------------------------------------------------------------
            StaticCallback(R (*pf)(A)) : m_pf(pf) { };


            // --------------------------------------------------------------------
            // Name: operator
            // Desc: The call operator that calls the function callback
            // Parm: A arg - the value to pass into the callback function
            // Retn: R     - the return value
            // --------------------------------------------------------------------
            virtual R operator()(A arg) const
            {
                return (m_pf)(arg);
            } // operator()


            // --------------------------------------------------------------------
            // Name: operator==
            // Desc: Equality operator for comparing two callbacks
            // Parm: const Callback<R, A> &rhs - the callback to compare with this 
            //       callback
            // Retn: bool     - true if they are equal
            // --------------------------------------------------------------------
            virtual bool operator==(const Callback<R, A> &rhs) const
            {
                // If the incoming callback has the same () operator as this class
                // then the classes are the same. This is because we do not
                // want to use RTTI, which is the most obvious choice here.
                if (this->GetTypeID() != rhs.GetTypeID())
                    return false;

                // They are of the same type (if they didn't define (), then
                // something is wrong. Cast to this type, and compare member
                // variables
                const StaticCallback<R, A> *prhs = static_cast<const StaticCallback<R, A> *>(&rhs);
                if (m_pf == prhs->m_pf)
                    return true;

                return false;
            } // operator==


            // --------------------------------------------------------------------
            // Name: Clone
            // Desc: Clone this static callback using new
            // Retn: StaticCallback<R, A> * - the new callback
            // --------------------------------------------------------------------
            virtual StaticCallback<R, A> *Clone() const
            {
                return new StaticCallback<R, A>(m_pf);
            } // Clone


            // --------------------------------------------------------------------
            // Name: GetTypeID
            // Desc: Get the member callback class type id (in this case 2)
            // Retn: int - the id
            // --------------------------------------------------------------------
            virtual int GetTypeID() const { return 2; }

        public:
            // --------------------------------------------------------------------
            // The function pointer type
            // --------------------------------------------------------------------
            typedef R (*FunType) (A);


            // --------------------------------------------------------------------
            // Privates for this class
            // --------------------------------------------------------------------
            FunType     m_pf;   // the function pointer
    }; // class StaticCallback


    // ----------------------------------------------------------------------------
    // Name: MakeCallback
    // Temp: R - the return type
    // Temp: O - the object type
    // Temp: A - the argument type
    // Desc: Makes a callback and returns it by copy.  In this case, a member 
    //       callback is created.  Due to C++'s implicit template deduction, the 
    //       template args do not need to be specified, so it is very easy to use, 
    //       just pass in the member funtion and the object.
    // Parm: R (O::*pm)(A)           - the member function
    // Retn: MemberCallback<R, O, A> - the object
    // ----------------------------------------------------------------------------
    template <typename R, class O, typename A>
    MemberCallback<R, O, A> MakeCallback(R (O::*pm)(A), O *pobj)
    {
        return MemberCallback<R, O, A>(pobj, pm);
    } // MakeCallback


    // ----------------------------------------------------------------------------
    // Name: MakeCallback
    // Temp: R - the return type
    // Temp: A - the argument type
    // Desc: Makes a callback and returns it by copy.  In this case, a static
    //       callback is created.  Due to C++'s implicit template deduction, the 
    //       template args do not need to be specified, so it is very easy to use, 
    //       just pass in the funtion.
    // Parm: R (*pf)(A)              - the member function
    // Retn: MemberCallback<R, O, A> - the object
    // ----------------------------------------------------------------------------
    template <typename R, typename A>
    StaticCallback<R, A> MakeCallback(R (*pf)(A))
    {
        return StaticCallback<R, A>(pf);
    } // MakeCallback


    // --------------------------------------------------------------------
    // Name: Identity  (struct)
    // Temp: The type of object that we are an identity for. We accept this 
    //       is our input and return it as our output.
    // Desc: A functor that returns the value is supplied. Particularly 
    //       valuable for use with Compose.
    // --------------------------------------------------------------------
    template <class T>
    struct Identity : public std::unary_function<T, T>
    {
        // The call operator that returns its input
        const T &operator()(const T &object) const { return object; }
    }; // Identity

    
    // --------------------------------------------------------------------
    // Name: FirstSelector  (struct)
    // Temp: The type of structure to select the first of. Is intended for 
    //       some type of std::pair.
    // Desc: A stateless functor that will return the first element of the 
    //       pair object provided through the call operator. Useful for 
    //       stepping through sequences of pairs (such as maps), only 
    //       looking at one of the elements. Particularly useful in 
    //       conjunction with compose, or bind.
    // --------------------------------------------------------------------
    template <class Pair>
    struct FirstSelector : public std::unary_function<Pair, typename Pair::first_type>
    {
        // Call operator returns the first element of the pair provided
        const typename Pair::first_type &operator()(const Pair &object) const { return object.first; }
    }; // FirstSelector


    // --------------------------------------------------------------------
    // Name: SecondSelector  (struct)
    // Temp: The type of structure to select the first of. Is intended for 
    //       some type of std::second.
    // Desc: A stateless functor that will return the second element of the 
    //       pair object provided through the call operator. Useful for 
    //       stepping through sequences of pairs (such as maps), only 
    //       looking at one of the elements. Particularly useful in 
    //       conjunction with compose, or bind.
    // --------------------------------------------------------------------
    template <class Pair>
    struct SecondSelector : public std::unary_function<Pair, typename Pair::second_type>
    {
        // Call operator returns the first element of the pair provided
        const typename Pair::second_type &operator()(const Pair &object) const { return object.second; }
    }; // SecondSelector


    // --------------------------------------------------------------------
    // Name: MemberSelector  (struct)
    // Temp: The type of structure to select the element of, the element 
    //       type, and the address (offset) of the element. Because the 
    //       element 'address' is templated, it is defined at compile time, 
    //       and so is as efficient as possible (no worse than hard-coded 
    //       member dereferencing. 
    // Desc: A stateless functor that will return the nominated element of 
    //       the object provided through the call operator.
    // --------------------------------------------------------------------
    template <class T, typename R, R T::*Member>
    struct MemberSelector : public std::unary_function<T, R>
    {
        // Call operator returns the nominated element of the object provided
        const R &operator()(const T &object) const { return object.*Member; }
    }; // MemberSelector


    // --------------------------------------------------------------------
    // Name: NullaryFunction (struct)
    // Temp: The return type of the functor.
    // Desc: This is a supplement to the standard unary_function and 
    //       binary_function.
    // --------------------------------------------------------------------
    template <class Result>
    struct NullaryFunction
    {
        typedef Result result_type;
    }; // NullaryFunction


    // --------------------------------------------------------------------
    // Name: PointerToNullaryFunction  (class)
    // Temp: The return type of the functor.
    // Desc: A functor that adapts a pointer to a nullary function so that 
    //       it can be used by other compositional functors.
    // --------------------------------------------------------------------
    template <class Result>
    class PointerToNullaryFunction : public NullaryFunction<Result>
    {
    public:
        // ----------------------------------------------------------------
        // Default construction, copying etc are OK.
        // ----------------------------------------------------------------
                    PointerToNullaryFunction()                             {}
        explicit PointerToNullaryFunction(Result (*ptr)()) : m_ptr(ptr) {}

        
        // ----------------------------------------------------------------
        // The call operator just patches through to the function
        // ----------------------------------------------------------------
        Result operator()() const { return m_ptr(); }

    protected:
        Result (*m_ptr)();
    }; // PointerToNullaryFunction


    // --------------------------------------------------------------------
    // Name: ptr_fun
    // Temp: The result type of the nullary function.
    // Desc: Provides ptr_fun for nullary functions.
    // Parm: Result (*ptr)()                  - The function pointer we are
    //       wrapping in a functor.
    // Retn: PointerToNullaryFunction<Result> - A functor wrapping the 
    //       function.
    // --------------------------------------------------------------------
    template <class Result>
    inline PointerToNullaryFunction<Result> ptr_fun(Result (*ptr)())
    {
        return PointerToNullaryFunction<Result>(ptr);
    } // ptr_fun


}; // namespace Functional



// ------------------------------------------------------------------------
// Name: Compose (namespace)
// Desc: Provides compositional functors for facilitating the creation of 
//       functors for use with the standard template library algoiithsm. 
//       This code is taken from Boost, which is taken from "The C++ 
//       Standard Library - A Tutorial and Reference" by Nicolai Josuttis, 
//       Addison-Wesley, 1999
// ------------------------------------------------------------------------
namespace Compose
{
    // --------------------------------------------------------------------
    // (C) Copyright Nicolai M. Josuttis 1999.
    // Permission to copy, use, modify, sell and distribute this software
    // is granted provided this copyright notice appears in all copies.
    // This software is provided "as is" without express or implied
    // warranty, and with no claim as to its suitability for any purpose.
    // --------------------------------------------------------------------


    // --------------------------------------------------------------------
    // UNARY COMPOSITION (Single argument)
    // --------------------------------------------------------------------


    // --------------------------------------------------------------------
    // Name: F_Gx_t  (class)
    // Temp: The f and g functor types
    // Desc: A compositional functor implementing f(g(x))
    // --------------------------------------------------------------------
    template <class OP1, class OP2>
    class F_Gx_t : public std::unary_function<typename OP2::argument_type, typename OP1::result_type>
    {
    public:
        // ----------------------------------------------------------------
        // Constructor
        // ----------------------------------------------------------------
        F_Gx_t(const OP1& o1, const OP2& o2) : m_op1(o1), m_op2(o2) {}

        
        // ----------------------------------------------------------------
        // The call operator implements op1(op2(x))
        // ----------------------------------------------------------------
        typename OP1::result_type operator()(const typename OP2::argument_type& x) const { return m_op1(m_op2(x)); }

    private:
        // ----------------------------------------------------------------
        // The functors
        // ----------------------------------------------------------------
        OP1     m_op1;  // f
        OP2     m_op2;  // g
    }; // class F_Gx_t


    // --------------------------------------------------------------------
    // Name: F_Gx
    // Temp: class OP1 - The f functor type
    // Temp: class OP2 - The g functor type
    // Desc: A convenience function for creating a F_Gx_t functor.
    // Parm: const OP1 &o1 - the f functor
    // Parm: const OP2 &o2 - the g functor
    // Retn: F_Gx_t<OP1, OP2> - the composition functor
    // --------------------------------------------------------------------
    template <class OP1, class OP2>
    inline F_Gx_t<OP1, OP2> F_Gx(const OP1 &o1, const OP2 &o2)
    {
        return F_Gx_t<OP1, OP2>(o1, o2);
    } // F_Gx


    // --------------------------------------------------------------------
    // Name: F_Gx_Hx_t  (class)
    // Temp: The f, g and h functor types
    // Desc: A compositional functor implementing f(g(x), h(x))
    // --------------------------------------------------------------------
    template <class OP1, class OP2, class OP3>
    class F_Gx_Hx_t : public std::unary_function<typename OP2::argument_type, typename OP1::result_type>
    {
    public:
        // ----------------------------------------------------------------
        // Constructor
        // ----------------------------------------------------------------
        F_Gx_Hx_t(const OP1& o1, const OP2& o2, const OP3& o3) : m_op1(o1), m_op2(o2), m_op3(o3) {}

        
        // ----------------------------------------------------------------
        // The call operator implements op1(op2(x), op3(x))
        // ----------------------------------------------------------------
        typename OP1::result_type operator()(const typename OP2::argument_type& x) const { return m_op1(m_op2(x), m_op3(x)); }

    private:
        // ----------------------------------------------------------------
        // The functors
        // ----------------------------------------------------------------
        OP1     m_op1;  // f
        OP2     m_op2;  // g
        OP3     m_op3;  // h
    }; // class F_Gx_Hx_t


    // --------------------------------------------------------------------
    // Name: F_Gx_Hx
    // Temp: class OP1 - The f functor type
    // Temp: class OP2 - The g functor type
    // Temp: class OP3 - The h functor type
    // Desc: A convenience function for creating a F_Gx_Hx_t functor.
    // Parm: const OP1 &o1 - the f functor
    // Parm: const OP2 &o2 - the g functor
    // Parm: const OP3 &o3 - the h functor
    // Retn: F_Gx_t<OP1, OP2> - the composition functor
    // --------------------------------------------------------------------
    template <class OP1, class OP2, class OP3>
    inline F_Gx_Hx_t<OP1, OP2, OP3> F_Gx_Hx(const OP1 &o1, const OP2 &o2, const OP3 &o3)
    {
        return F_Gx_Hx_t<OP1, OP2, OP3>(o1, o2, o3);
    } // F_Gx_Hx


    // --------------------------------------------------------------------
    // BINARY COMPOSITION (Two arguments)
    // --------------------------------------------------------------------


    // --------------------------------------------------------------------
    // Name: F_Gxy_t  (class)
    // Temp: The f and g functor types
    // Desc: A compositional functor implementing f(g(x, y))
    // --------------------------------------------------------------------
    template <class OP1, class OP2>
    class F_Gxy_t : public std::binary_function<typename OP2::first_argument_type, typename OP2::second_argument_type, typename OP1::result_type>
    {
    public:
        // ----------------------------------------------------------------
        // Constructor
        // ----------------------------------------------------------------
        F_Gxy_t(const OP1& o1, const OP2& o2) : m_op1(o1), m_op2(o2) {}

        
        // ----------------------------------------------------------------
        // The call operator implements op1(op2(x, y))
        // ----------------------------------------------------------------
        typename OP1::result_type operator()(const typename OP2::first_argument_type &x, const typename OP2::second_argument_type &y) const { return m_op1(m_op2(x, y)); }

    private:
        // ----------------------------------------------------------------
        // The functors
        // ----------------------------------------------------------------
        OP1     m_op1;  // f
        OP2     m_op2;  // g
    }; // class F_Gxy_t


    // --------------------------------------------------------------------
    // Name: F_Gxy
    // Temp: class OP1 - The f functor type
    // Temp: class OP2 - The g functor type
    // Desc: A convenience function for creating a F_Gxy_t functor.
    // Parm: const OP1 &o1 - the f functor
    // Parm: const OP2 &o2 - the g functor
    // Retn: F_Gxy_t<OP1, OP2> - the composition functor
    // --------------------------------------------------------------------
    template <class OP1, class OP2>
    inline F_Gxy_t<OP1, OP2> F_Gxy(const OP1 &o1, const OP2 &o2)
    {
        return F_Gxy_t<OP1, OP2>(o1, o2);
    } // F_Gxy


    // --------------------------------------------------------------------
    // Name: F_Gx_Hy_t  (class)
    // Temp: The f, g and h functor types
    // Desc: A compositional functor implementing f(g(x), h(y))
    // --------------------------------------------------------------------
    template <class OP1, class OP2, class OP3>
    class F_Gx_Hy_t : public std::binary_function<typename OP2::argument_type, typename OP3::argument_type, typename OP1::result_type>
    {
    public:
        // ----------------------------------------------------------------
        // Constructor
        // ----------------------------------------------------------------
        F_Gx_Hy_t(const OP1& o1, const OP2& o2, const OP3& o3) : m_op1(o1), m_op2(o2), m_op3(o3) {}

        
        // ----------------------------------------------------------------
        // The call operator implements op1(op2(x), op3(y))
        // ----------------------------------------------------------------
        typename OP1::result_type operator()(const typename OP2::argument_type& x, const typename OP3::argument_type& y) const { return m_op1(m_op2(x), m_op3(y)); }

    private:
        // ----------------------------------------------------------------
        // The functors
        // ----------------------------------------------------------------
        OP1     m_op1;  // f
        OP2     m_op2;  // g
        OP3     m_op3;  // h
    }; // class F_Gx_Hy_t


    // --------------------------------------------------------------------
    // Name: F_Gx_Hy_t
    // Temp: class OP1 - The f functor type
    // Temp: class OP2 - The g functor type
    // Temp: class OP3 - The h functor type
    // Desc: A convenience function for creating a F_Gx_Hy_t functor.
    // Parm: const OP1 &o1 - the f functor
    // Parm: const OP2 &o2 - the g functor
    // Parm: const OP3 &o3 - the h functor
    // Retn: F_Gx_Hy_t<OP1, OP2, OP3> - the composition functor
    // --------------------------------------------------------------------
    template <class OP1, class OP2, class OP3>
    inline F_Gx_Hy_t<OP1, OP2, OP3> F_Gx_Hy(const OP1 &o1, const OP2 &o2, const OP3 &o3)
    {
        return F_Gx_Hy_t<OP1, OP2, OP3>(o1, o2, o3);
    } // F_Gx_Hy


    // --------------------------------------------------------------------
    // NULLARY COMPOSITION (No arguments)
    // --------------------------------------------------------------------


    // --------------------------------------------------------------------
    // Name: F_G_t  (class)
    // Temp: The f and g functor types
    // Desc: A compositional functor implementing f(g())
    // --------------------------------------------------------------------
    template <class OP1, class OP2>
    class F_G_t : public Functional::NullaryFunction<typename OP1::result_type>
    {
    public:
        // ----------------------------------------------------------------
        // Constructor
        // ----------------------------------------------------------------
        F_G_t(const OP1& o1, const OP2& o2) : m_op1(o1), m_op2(o2) {}

        
        // ----------------------------------------------------------------
        // The call operator implements op1(op2())
        // ----------------------------------------------------------------
        typename OP1::result_type operator()() const { return m_op1(m_op2()); }

    private:
        // ----------------------------------------------------------------
        // The functors
        // ----------------------------------------------------------------
        OP1     m_op1;  // f
        OP2     m_op2;  // g
    }; // class F_G_t


    // --------------------------------------------------------------------
    // Name: F_G
    // Temp: class OP1 - The f functor type
    // Temp: class OP2 - The g functor type
    // Desc: A convenience function for creating a F_G_t functor.
    // Parm: const OP1 &o1 - the f functor
    // Parm: const OP2 &o2 - the g functor
    // Retn: F_Gx_Hy_t<OP1, OP2> - the composition functor
    // --------------------------------------------------------------------
    template <class OP1, class OP2>
    inline F_G_t<OP1, OP2> F_G(const OP1 &o1, const OP2 &o2)
    {
        return F_G_t<OP1, OP2>(o1, o2);
    } // F_G


}; // namespace Compose


// ------------------------------------------------------------------------
// Name: Algorithm (namespace)
// Desc: Namespace for algorithm functors
// ------------------------------------------------------------------------
namespace Algorithm
{
    // --------------------------------------------------------------------
    // Name: RemoveFirstFromVector
    // Temp: The type of objects contained in the vector
    // Desc: Removes the first occurence of the requested object in the 
    //       vector
    // Parm: std::vector<T *> &vec - the vector
    // Parm: T *pobj       - the object
    // Retn: bool          - true if found and removed, otherwise false
    // --------------------------------------------------------------------
    template <class T>
    bool RemoveFirstFromVector(std::vector<T *> &vec, T *pobj)
    {
        std::vector<T *>::iterator iter = vec.begin();
        std::vector<T *>::iterator end  = vec.end();
        
        for (; iter != end; ++iter)
        {
            if ((* iter) == pobj)
            {
                vec.erase(iter);
                return true;
            } // if
        } // for

        return false;
    } // RemoveFirstFromVector


    // --------------------------------------------------------------------
    // Name: FindInVector
    // Temp: The type of objects contained in the vector
    // Desc: Searches for the given object in the vector
    // Parm: std::vector<T *> &vec - the vector
    // Parm: T *pobj       - the object
    // Retn: bool          - true if the object is in the vector
    // --------------------------------------------------------------------
    template <class T>
    bool FindInVector(std::vector<T *> &vec, T *pobj)
    {
        std::vector<T *>::iterator iter = vec.begin();
        std::vector<T *>::iterator end  = vec.end();
        
        for (; iter != end; ++iter)
        {
            if ((* iter) == pobj)
                return true;
        } // for

        return false;
    } // FindInVector


    // --------------------------------------------------------------------
    // Name: DestroyObject (struct)
    // Desc: A struct that deletes an object using a unary call operator
    // --------------------------------------------------------------------
    template <class T> 
    struct DestroyObject
    {
        // ----------------------------------------------------------------
        // Name: operator
        // Desc: The call operator that deletes the object
        // ----------------------------------------------------------------
        void operator()(T *ptr)
        {
            delete ptr;
        } // operator()
    }; // struct DestroyObject


    // --------------------------------------------------------------------
    // Name: DestroyVector
    // Temp: The type of objects contained in the vector
    // Desc: Destroys all objects between the start and end iterators
    // Parm: typename std::vector<T *>::iterator &begin - start iterator
    // Parm: typename std::vector<T *>::iterator &end   - end iterator
    // --------------------------------------------------------------------
    template <class T> 
    void DestroyVector(typename std::vector<T *>::iterator &begin, typename std::vector<T *>::iterator &end)
    {
        std::for_each(begin, end, DestroyObject<T>());
    } // DestroyVector


    // --------------------------------------------------------------------
    // Name: DestroyVector
    // Temp: The type of objects contained in the vector
    // Desc: Destroys all objects in the vector, then clears the vector if
    //       requested.
    // Parm: typename std::vector<T *> &vec - the vector
    // Parm: bool clear_vector = true       - flag to clear the vector
    // --------------------------------------------------------------------
    template <class T> 
    void DestroyVector(std::vector<T *> &vec, bool clear_vector = true)
    {
        std::for_each(vec.begin(), vec.end(), DestroyObject<T>());

        if (clear_vector)
            vec.clear();
    } // DestroyVector


    // --------------------------------------------------------------------
    // Name: DestroyList
    // Temp: The type of objects contained in the list
    // Desc: Destroys all objects between the start and end iterators
    // Parm: typename std::list<T *>::iterator &begin - start iterator
    // Parm: typename std::list<T *>::iterator &end   - end iterator
    // --------------------------------------------------------------------
    template <class T> 
    void DestroyList(typename std::list<T *>::iterator &begin, typename std::list<T *>::iterator &end)
    {
        std::for_each(begin, end, DestroyObject<T>());
    } // DestroyList


    // --------------------------------------------------------------------
    // Name: DestroyList
    // Temp: The type of objects contained in the list
    // Desc: Destroys all objects in the list, then clears the list if
    //       requested.
    // Parm: typename std::list<T *> &vec - the list
    // Parm: bool clear_list = true       - flag to clear the list
    // --------------------------------------------------------------------
    template <class T> 
    void DestroyList(std::list<T *> &list, bool clear_list = true)
    {
        std::for_each(list.begin(), list.end(), DestroyObject<T>());

        if (clear_list)
            list.clear();
    } // DestroyList


    // --------------------------------------------------------------------
    // Name: DestroyMapSecond
    // Temp: K - the key type in the map
    // Temp: V - the value type in the map
    // Desc: Destroys all objects between the start and end iterators
    // Parm: typename std::map<K, V>::iterator &begin - start iterator
    // Parm: typename std::map<K, V>::iterator &end   - end iterator
    // --------------------------------------------------------------------
    template <class K, class V> 
    void DestroyMapSecond(typename std::map<K, V *>::iterator &begin, typename std::vector<K, V *>::iterator &end)
    {
        std::for_each(begin, end, DestroyObject<V>());
    } // DestroyMapSecond


    // --------------------------------------------------------------------
    // Name: DestroyMapSecond
    // Temp: K - the key type in the map
    // Temp: V - the value type in the map
    // Desc: Destroys all objects in the map, then clears the map if
    //       requested.
    // Parm: typename std::map<K, V> &map - the map
    // Parm: bool clear_map = true        - flag to clear the map
    // --------------------------------------------------------------------
    template <class K, class V> 
    void DestroyMapSecond(std::map<K, V *> &map, bool clear_map = true)
    {
        std::for_each(map.begin(), map.end(), DestroyObject<V>());
        
        if (clear_map)
            map.clear();
    } // DestroyMapSecond


}; // namespace Algorithm


// ------------------------------------------------------------------------
// Name: String (namespace)
// Desc: String manipulation algorithms
// ------------------------------------------------------------------------
namespace String
{
    // --------------------------------------------------------------------
    // Name: Space
    // Desc: Create a string with the specified number of spaces in it
    // Parm: size_t num  - the number of spaces
    // Retn: std::string - the string
    // --------------------------------------------------------------------
    inline std::string Space(size_t num)
    {
        std::string str;
        for (size_t i = 0; i < num; i++)
            str += " ";
        
        return str;
    } // Space


    // --------------------------------------------------------------------
    // Name: AppendInt
    // Desc: Append an integer at the end of a string
    // Parm: std::string &str - the string to append the integer to
    // Parm: int i         - the integer
    // Retn: std::string & - the in string so this function can be chained
    // --------------------------------------------------------------------
    inline std::string &AppendInt(std::string &str, int i)
    {
        char buffer[32];
        sprintf(buffer, "%d", i);
        str += buffer;
        return str;
    } // AppendInt

    
    // --------------------------------------------------------------------
    // Name: GetQuotedString
    // Desc: Searhes through the given string to find the quoted string
    // Parm: const std::string &str - the string to search
    // Retn: std::string            - the text inside of the first pair of 
    //       quotes, or an empty string if there is not at least one set 
    //       of quotes.
    // --------------------------------------------------------------------
    inline std::string GetQuotedString(const std::string &str)
    {
        static const std::basic_string <char>::size_type npos = -1;

        std::basic_string<char>::size_type pos1;
        std::basic_string<char>::size_type pos2;

        // Find the first quote
        pos1 = str.find_first_of("\"", 0);
        if (pos1 == npos)
            return "";

        // Find the second quote
        pos2 = str.find_first_of("\"", pos1 + 1);
        if (pos2 == npos)
            return "";

        // Return the string between the quotes
        return str.substr(pos1 + 1, pos2 - (pos1 + 1));
    } // GetQuotedString


    // --------------------------------------------------------------------
    // Name: TrimString
    // Desc: Trims the leading and trailing whitespace from a string
    // Parm: std::string &str - the string to trim
    // Retn: std::string & - the in string so this function can be chained
    // --------------------------------------------------------------------
    inline std::string &TrimString(std::string &str)
    {
        // Bail out if the string is empty
        if (str.empty())
            return str;

        // Erase leading whitespace
        while (str.at(0) == ' ')
            str.erase(str.begin());

        // Bail out if the string is empty
        if (str.empty())
            return str;

        // Erase trailing whitespace
        while (str.at(str.size() - 1) == ' ')
            str = str.substr(0, str.size() - 1);

        // return trh string
        return str;
    } // TrimString


    // --------------------------------------------------------------------
    // Name: TrimQuotes
    // Desc: Trims the leading and trailing quotes from a string
    // Parm: std::string &str - the string to trim
    // Retn: std::string & - the in string so this function can be chained
    // --------------------------------------------------------------------
    inline std::string &TrimQuotes(std::string &str)
    {
        // Bail out if the string is empty
        if (str.empty())
            return str;

        // Erase leading whitespace
        while (str.at(0) == '"')
            str.erase(str.begin());

        // Bail out if the string is empty
        if (str.empty())
            return str;

        // Erase trailing whitespace
        while (str.at(str.size() - 1) == '"')
            str = str.substr(0, str.size() - 1);

        // return trh string
        return str;
    } // TrimQuotes


    // --------------------------------------------------------------------
    // Name: SplitPath
    // Desc: Split a string that contains a path and a name into two 
    //       seperate strings.  The name is the text after the final slash, 
    //       and the path is everythjing before (which may contain other 
    //       slashes)
    // Parm: const std::string &str - the string to decompose
    // Parm: std::string &path - the path
    // Parm: std::string &name - the name
    // --------------------------------------------------------------------
    inline void SplitPath(const std::string &str, std::string &path, std::string &name)
    {
        path = "/";
        name = "";

        // Check we have some text
        if (str.empty())
            return;

        // Get size type and npos
        typedef int size_type;
        static const size_type npos = std::string::npos;

        // See if the string has a slash in it
        size_type fs = str.find_last_of('/', str.size());
        size_type bs = str.find_last_of('\\', str.size());

        size_type last = std::max<size_type>(fs, bs);
        if (last == npos)
        {
            // No slash, name is str
            name = str;
        } // if
        else
        {
            // Extract the name and path
            path = str.substr(0, last);
            name = str.substr(last + 1, str.size());
        } // else
    } // SplitPath


    // ----------------------------------------------------------------------------
    // Name: LexicalCast
    // Temp: Target - the target value type
    // Temp: Source - the source value type
    // Desc: Casts a value from one type to another, performing the conversion 
    //       textually - that is, it is written out as text, and then interpreted, 
    //       equivalent to printing it and then scanning it.  If the conversion is 
    //       not possible, or fails for some reason, an InvalidParameterException 
    //       will be thrown.  The template arguments specify the type of the source
    //       infromation, and the type that we want to cast it to. The source type
    //       can be automaticallly determined from the input parameter, but the 
    //       return type needs to be specified as a template parameter.
    // Parm: Source in - The value to convert. This is done by value, not by 
    //       reference, to allow casting to also be performed on the function call
    // Retn: Target    - The converted value
    // ----------------------------------------------------------------------------
    template <typename Target, typename Source>
    Target LexicalCast(Source in)
    {
        // Create our string stream, which we will use to perform the conversion
        // for us
        std::stringstream interpreter;
        interpreter.unsetf(std::ios::skipws);

        Target result;

        // Now perform the conversion
        if (!(interpreter << in) || !(interpreter >> result) || !(interpreter >> std::ws).eof())
            throw InvalidParameterException(FLSTAMP) 
            << "Error casting the input '" << in 
            << "' to the desired type!";

        return result;
    } // LexicalCast


    // ----------------------------------------------------------------------------
    // Name: std::string>
    // Desc: Strings are a special case. In general, we want to use partial 
    //       specialization to form a special case when the source and target types 
    //       for the lexical cast are automatically convertible, or the same, but we
    //       can't do this using MSVC yet
    // Parm: std::string in                       - the source string
    // Retn: std::string LexicalCast<std::string, - the target string
    // ----------------------------------------------------------------------------
    template <>
    inline std::string LexicalCast<std::string, std::string>(std::string in)
    {
        return in;
    } // LexicalCast


}; // naemspace String




#endif // UTILITIES_H

// -- EOF
