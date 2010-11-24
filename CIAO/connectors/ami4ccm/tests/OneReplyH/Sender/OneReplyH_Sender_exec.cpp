// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.3
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

#include "OneReplyH_Sender_exec.h"
#include "OneReplyHA_conn_i.h"
#include "ace/OS_NS_unistd.h"


namespace CIAO_OneReplyH_Sender_Impl
{
  CORBA::Short nr_of_excep_received = 0;

  void HandleException (
       long id,
       long expect_id,
       const char* /*error_string*/,
       const char* func)
  {
    //expected exception
    if ( id == expect_id)
      {
        ++nr_of_excep_received;
      }
    else
      {
         ACE_ERROR ((LM_ERROR, "ERROR Sender: wrong exception received"
                               " for %C\n", func));
      }
  }
  //============================================================
  // Worker thread for asynchronous invocations for MyFoo
  //============================================================
  asynch_foo_generator::asynch_foo_generator (
        ::OneReplyH::CCM_Sender_Context_ptr context,
          Atomic_UShort  &nr_of_received)
        : context_(::OneReplyH::CCM_Sender_Context::_duplicate (context)),
          nr_of_received_(nr_of_received)
  {
    cb_ = new CIAO_OneReplyH_Sender_Impl::AMI4CCM_MyFooReplyHandler_i (
                                                      this->nr_of_received_);
  }

  int asynch_foo_generator::svc ()
  {
    ACE_OS::sleep (3);
    ::OneReplyH::AMI4CCM_MyFoo_var my_foo_ami_  =
        this->context_->get_connection_sendc_run_my_foo();

    if (CORBA::is_nil (my_foo_ami_))
      {
        ACE_ERROR ((LM_ERROR, "ERROR Sender (ASYNCH) :\tfoo_ami is NIL !\n"));
        return 1;
      }
    else
      {
        //Invoke Asynchronous calls ,test with  one replyhandler.
        my_foo_ami_->sendc_foo ( this->cb_.in(), "Hi from foo 1",
                                OneReplyH::cmd_asynch_foo_ok);
        //this should invoke a exception
        my_foo_ami_->sendc_foo (  this->cb_.in(), "",
                               OneReplyH::cmd_asynch_foo_nok);
        my_foo_ami_->sendc_foo ( this->cb_.in(), "Hi from foo 2",
                                OneReplyH::cmd_asynch_foo_ok);
        my_foo_ami_->sendc_bar ( this->cb_.in(), "Hi from bar",
                                OneReplyH::cmd_asynch_bar_ok);
        my_foo_ami_->sendc_foo ( this->cb_.in(), "Hi from foo 3",
                                OneReplyH::cmd_asynch_foo_ok);

         //this should invoke a exception
        my_foo_ami_->sendc_bar (  this->cb_.in(), "", OneReplyH::cmd_asynch_bar_nok);
      }
    return 0;
  }

  //============================================================
  // Worker thread for synchronous invocations for MyFoo
  //============================================================
  synch_foo_generator::synch_foo_generator (
      ::OneReplyH::CCM_Sender_Context_ptr context,
       Atomic_UShort  &nr_of_received)
     : context_(::OneReplyH::CCM_Sender_Context::_duplicate (context)),
     nr_of_received_(nr_of_received)
  {
  }

  int synch_foo_generator::svc ()
  {
    ACE_OS::sleep (3);
    ::OneReplyH::MyFoo_var my_foo_ami_ =
      this->context_->get_connection_run_my_foo ();

    //run some synch calls
    CORBA::String_var out_str;
    CORBA::Long l_cmd = 0;
    try
      {
        CORBA::Long result = my_foo_ami_->foo ("Do something synchronous",
                                                OneReplyH::cmd_synch_foo_ok,
                                                out_str.out ());
        if ( result == OneReplyH::cmd_synch_foo_ok)
          {
            ++this->nr_of_received_;
          }
      }
    catch (const OneReplyH::InternalError&)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: synch_foo_generator::foo: "
                              "Unexpected exception.\n"));
      }
    try
      {
        my_foo_ami_->foo ("",OneReplyH::cmd_synch_foo_nok, out_str);
      }
    catch (const OneReplyH::InternalError& ex)
      {
          HandleException (ex.id, OneReplyH::cmd_synch_foo_nok,
                           ex.error_string.in(),
                           "synch foo");
      }
    try
      {
        my_foo_ami_->bar ("Do something synchronous",
                           OneReplyH::cmd_synch_bar_ok,
                           out_str, l_cmd);
        if ( l_cmd == OneReplyH::cmd_synch_bar_ok)
          {
            ++this->nr_of_received_;
          }
      }
    catch (const OneReplyH::InternalError&)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: synch_foo_generator::bar: "
                              "Unexpected exception.\n"));
      }
    try
      {
        my_foo_ami_->bar ( "", OneReplyH::cmd_synch_bar_nok, out_str, l_cmd);
      }
    catch (const OneReplyH::InternalError& ex)
      {
          HandleException (ex.id, OneReplyH::cmd_synch_bar_nok,
                           ex.error_string.in(),
                           "synch bar");
      }
    return 0;
  }
  /**
   * Component Executor Implementation Class: Sender_exec_i
   */

  Sender_exec_i::Sender_exec_i (void){
  }

  Sender_exec_i::~Sender_exec_i (void)
  {
  }

  // Supported operations and attributes.

  // Component attributes and port operations.

  // Operations from Components::SessionComponent.

  void
  Sender_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::OneReplyH::CCM_Sender_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  Sender_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  Sender_exec_i::ccm_activate (void)
  {
    this->asynch_foo_gen =
      new asynch_foo_generator (this->ciao_context_.in (),
                                this->nr_of_received_);
    this->asynch_foo_gen->activate (THR_NEW_LWP | THR_JOINABLE, 1);

    this->synch_foo_gen =
      new synch_foo_generator (this->ciao_context_.in(),
          this->nr_of_received_);
    this->synch_foo_gen->activate (THR_NEW_LWP | THR_JOINABLE, 1);  }

  void
  Sender_exec_i::ccm_passivate (void)
  {
    /* Your code here. */
  }

  void
  Sender_exec_i::ccm_remove (void)
  {
    if (nr_of_excep_received != 4)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: not received the expected number of"
                              " exceptions"
                              "Expected: 4, Received: %u.\n",
                              nr_of_excep_received));
      }
    if (this->nr_of_received_.value() != 6)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: Sender not received the expected number"
                              " of callbacks and returns  for syn- and "
                              "asynchronous calls. Expected: 6,"
                              " Received: %u.\n",
                              this->nr_of_received_.value()));
      }
    if ((this->nr_of_received_.value() == 6) && (nr_of_excep_received == 4))
      {
        ACE_DEBUG ((LM_DEBUG, "OK: Sender received the expected number of"
                              " callbacks and exceptions for syn- and "
                              "asynchronous calls\n"));
      }
    if (this->asynch_foo_gen)
      {
         delete this->asynch_foo_gen;
         this->asynch_foo_gen = 0;
      }
    if (this->synch_foo_gen)
      {
        delete this->synch_foo_gen;
        this->synch_foo_gen = 0;
      }
  }

  extern "C" ONEREPLYH_T_SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_OneReplyH_Sender_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Sender_exec_i);

    return retval;
  }
}
