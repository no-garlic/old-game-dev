// ------------------------------------------------------------------------
// File: Compose.h
// Desc: Provides compositional functors for facilitating the creation of 
//       functors for use with the standard template library algoiithsm. 
//       This code is taken from Boost, which is taken from "The C++ 
//       Standard Library - A Tutorial and Reference" by Nicolai Josuttis, 
//       Addison-Wesley, 1999
// ------------------------------------------------------------------------
#ifndef _COMPOSE_H_
#define _COMPOSE_H_


#include "Kernel/Types.h"

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
class F_G_t : public NullaryFunction<typename OP1::result_type>
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


#endif // _COMPOSE_H_

// -- EOF

