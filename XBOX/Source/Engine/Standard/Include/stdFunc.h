
#ifndef __STD_FUNC_H_
#define __STD_FUNC_H_

#include "stdType.h"

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


#endif // __STD_FUNC_H_

// -- EOF

