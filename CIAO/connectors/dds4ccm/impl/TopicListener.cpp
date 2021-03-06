#include "dds4ccm/impl/TopicListener.h"
#include "dds4ccm/impl/Utils.h"
#include "dds4ccm/impl/DDSCallbackStatusHandler.h"
#include "dds4ccm/impl/logger/Log_Macros.h"
#include "ace/Reactor.h"

namespace CIAO
{
  namespace DDS4CCM
  {
    TopicListener::TopicListener (
        ::CCM_DDS::ConnectorStatusListener_ptr error_listener,
         ACE_Reactor* reactor) :
         error_listener_ (::CCM_DDS::ConnectorStatusListener::_duplicate (error_listener)),
         reactor_ (reactor)
    {
      DDS4CCM_TRACE ("CIAO::DDS4CCM::TopicListener::TopicListener");
    }

    TopicListener::~TopicListener (void)
    {
      DDS4CCM_TRACE ("CIAO::DDS4CCM::TopicListener::~TopicListener");
    }

    void
    TopicListener::on_inconsistent_topic (
        ::DDS::Topic_ptr the_topic,
         const ::DDS::InconsistentTopicStatus & status)
    {
      DDS4CCM_TRACE ("CIAO::DDS4CCM::TopicListener::on_inconsistent_topic");

      DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_DDS_STATUS, (LM_DEBUG, DDS4CCM_INFO
          ACE_TEXT ("TopicListener::on_inconsistent_topic: ")
      ACE_TEXT ("total count <%d> - total change <%d> - "),
      status.total_count, status.total_count_change));

      if (! ::CORBA::is_nil (this->error_listener_.in ()))
        {
          try
          {
              if (this->reactor_)
                {
                  ::CIAO::DDS4CCM::OnInconsistentTopicHandler* rh = 0;
                  ACE_NEW (rh,
                      ::CIAO::DDS4CCM::OnInconsistentTopicHandler (
                          this->error_listener_,
                          the_topic,
                          status));
                  ACE_Event_Handler_var safe_handler (rh);
                  if (this->reactor_->notify (rh) != 0)
                    {
                      DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
                          ACE_TEXT ("TopicListener::on_inconsistent_topic - ")
                      ACE_TEXT ("failed to use reactor.\n")));
                    }
                }
              else
                {
                  this->error_listener_->on_inconsistent_topic (the_topic, status);
                }
          }
          catch (const ::CORBA::BAD_INV_ORDER& ex)
            {
              DDS4CCM_PRINT_DEBUG_CORBA_EXCEPTION (
                                      DDS4CCM_LOG_LEVEL_ACTION,
                                      ex,
                                      "TopicListener::on_inconsistent_topic");
            }
          catch (const ::CORBA::Exception& ex)
            {
                DDS4CCM_PRINT_CORBA_EXCEPTION (
                    DDS4CCM_LOG_LEVEL_ERROR,
                    ex,
                    "TopicListener::on_inconsistent_topic");
            }
          catch (...)
            {
                DDS4CCM_ERROR (DDS4CCM_LOG_LEVEL_ERROR, (LM_ERROR, DDS4CCM_INFO
                    "TopicListener::on_inconsistent_topic - "
                    "Unexpected exception caught\n"));
            }
        }
      else
        {
          DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_ACTION, (LM_DEBUG, DDS4CCM_INFO
              ACE_TEXT ("TopicListener::on_inconsistent_topic - ")
          ACE_TEXT ("No error listener connected\n")));
        }
    }

    ::DDS::StatusMask
    TopicListener::get_mask (
         CCM_DDS::ConnectorStatusListener_ptr error_listener)
    {
      DDS4CCM_TRACE ("CIAO::DDS4CCM::TopicListener::get_mask");

      ::DDS::StatusMask mask = 0;

      if (! ::CORBA::is_nil (error_listener) ||
          DDS4CCM_debug_level >= DDS4CCM_LOG_LEVEL_DDS_STATUS)
        {
          mask = ::DDS::INCONSISTENT_TOPIC_STATUS;
        }

      if (DDS4CCM_debug_level >= DDS4CCM_LOG_LEVEL_DDS_STATUS)
        {
          ACE_CString msk;
          translate_statusmask (msk, mask);
          DDS4CCM_DEBUG (DDS4CCM_LOG_LEVEL_DDS_STATUS, (LM_DEBUG, DDS4CCM_INFO
              "TopicListener::get_mask - "
              "Mask becomes %C\n",
              msk.c_str ()));
        }
      return mask;
    }
  }
}

