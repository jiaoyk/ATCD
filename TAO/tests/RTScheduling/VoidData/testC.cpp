// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from
// be/be_codegen.cpp:351


#include "testC.h"
#include "tao/Stub.h"
#include "tao/Invocation.h"
#include "tao/PortableInterceptor.h"

#if TAO_HAS_INTERCEPTORS == 1
#include "tao/RequestInfo_Util.h"
#include "tao/ClientRequestInfo_i.h"
#include "tao/ClientInterceptorAdapter.h"
#endif  /* TAO_HAS_INTERCEPTORS == 1 */


#if defined (__BORLANDC__)
#pragma option -w-rvl -w-rch -w-ccc -w-aus -w-sig
#endif /* __BORLANDC__ */

#if !defined (__ACE_INLINE__)
#include "testC.i"
#endif /* !defined INLINE */

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_cs.cpp:63

int test::_tao_class_id = 0;

test_ptr
tao_test_life::tao_duplicate (
    test_ptr p
  )
{
  return test::_duplicate (p);
}

void
tao_test_life::tao_release (
    test_ptr p
  )
{
  CORBA::release (p);
}

test_ptr
tao_test_life::tao_nil (
    void
  )
{
  return test::_nil ();
}

CORBA::Boolean
tao_test_life::tao_marshal (
    test_ptr p,
    TAO_OutputCDR &cdr
  )
{
  return p->marshal (cdr);
}

test_ptr
tao_test_cast::tao_narrow (
    CORBA::Object *p
    ACE_ENV_ARG_DECL
  )
{
  return test::_narrow (p ACE_ENV_ARG_PARAMETER);
}

CORBA::Object *
tao_test_cast::tao_upcast (
    void *src
  )
{
  test **tmp =
    ACE_static_cast (test **, src);
  return *tmp;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
  template class
    TAO_Objref_Var_T<
        test,
        tao_test_life
      >;
  template class
    TAO_Objref_Out_T<
        test,
        tao_test_life
      >;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
# pragma instantiate \
    TAO_Objref_Var_T< \
        test, \
        tao_test_life \
      >
# pragma instantiate \
    TAO_Objref_Out_T< \
        test, \
        tao_test_life \
      >
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

// TAO_IDL - Generated from 
// be/be_visitor_interface/interface_cs.cpp:245

test::test (void)
{}

test::~test (void)
{}

void 
test::_tao_any_destructor (void *_tao_void_pointer)
{
  test *tmp = ACE_static_cast (test *, _tao_void_pointer);
  CORBA::release (tmp);
}

test_ptr
test::_narrow (
    CORBA::Object_ptr obj
    ACE_ENV_ARG_DECL
  )
{
  return test::_unchecked_narrow (obj ACE_ENV_ARG_PARAMETER);
}

test_ptr 
test::_unchecked_narrow (
    CORBA::Object_ptr obj
    ACE_ENV_ARG_DECL_NOT_USED
  )
{
  if (CORBA::is_nil (obj))
    {
      return test::_nil ();
    }
  
  return
      ACE_reinterpret_cast (
          test_ptr,
          obj->_tao_QueryInterface (
              ACE_reinterpret_cast (
                  ptrdiff_t,
                  &test::_tao_class_id
                )
            )
        );
}

test_ptr
test::_duplicate (test_ptr obj)
{
  if (! CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void *test::_tao_QueryInterface (ptrdiff_t type)
{
  void *retv = 0;
  
  if (type == ACE_reinterpret_cast (
              ptrdiff_t,
              &test::_tao_class_id)
            )
    {
      retv = ACE_reinterpret_cast (void*, this);
    }
  else if (type == ACE_reinterpret_cast (
               ptrdiff_t,
               &CORBA::Object::_tao_class_id)
             )
    {
      retv =
        ACE_reinterpret_cast (
            void *,
            ACE_static_cast (CORBA::Object_ptr, this)
          );
    }
  
  if (retv != 0)
    {
      this->_add_ref ();
    }
  
  return retv;
}

const char* test::_interface_repository_id (void) const
{
  return "IDL:test:1.0";
}

CORBA::Boolean
test::marshal (TAO_OutputCDR &)
{
  return 0;
}

// TAO_IDL - Generated from
// be/be_visitor_typecode/typecode_defn.cpp:284

static const CORBA::Long _oc_test[] =
{
    TAO_ENCAP_BYTE_ORDER, // byte order
  13,
  ACE_NTOHL (0x49444c3a), 
  ACE_NTOHL (0x74657374), 
  ACE_NTOHL (0x3a312e30), 
  ACE_NTOHL (0x0),  // repository ID = IDL:test:1.0
    5,
  ACE_NTOHL (0x74657374), 
  ACE_NTOHL (0x0),  // name = test
  };

static CORBA::TypeCode _tc_TAO_tc_test (
    CORBA::tk_objref,
    sizeof (_oc_test),
    (char *) &_oc_test,
    0,
    sizeof (test)
  );

::CORBA::TypeCode_ptr _tc_test =
  &_tc_TAO_tc_test;

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_cs.cpp:50

// Copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    test_ptr _tao_elem
  )
{
  test_ptr _tao_objptr =
    test::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

// Non-copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    test_ptr *_tao_elem
  )
{
  TAO::Any_Impl_T<test>::insert (
      _tao_any,
      test::_tao_any_destructor,
      _tc_test,
      *_tao_elem
    );
}

CORBA::Boolean
operator>>= (
    const CORBA::Any &_tao_any,
    test_ptr &_tao_elem
  )
{
  return
    TAO::Any_Impl_T<test>::extract (
        _tao_any,
        test::_tao_any_destructor,
        _tc_test,
        _tao_elem
      );
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)  || \
    defined (ACE_HAS_GNU_REPO)
  template class TAO::Any_Impl_T<test>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
# pragma instantiate TAO::Any_Impl_T<test>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

