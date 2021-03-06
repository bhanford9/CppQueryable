#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TRIGGERTYPE_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TRIGGERTYPE_H

#include <string>

enum class TriggerType
{
  Begin,
  Quarter,
  Half,
  ThreeQuarter,
  End,
  Never,
  LowFrequency,
  MediumFrequency,
  HighFrequency,
  NotApplicable
};

static std::string GetTriggerName(TriggerType type)
{
  switch (type)
  {
    case TriggerType::Begin: return "Begin";
    case TriggerType::Quarter: return "Quarter";
    case TriggerType::Half: return "Half";
    case TriggerType::ThreeQuarter: return "ThreeQuarter";
    case TriggerType::End: return "End";
    case TriggerType::Never: return "Never";
    case TriggerType::LowFrequency: return "LowFrequency";
    case TriggerType::MediumFrequency: return "MediumFrequency";
    case TriggerType::HighFrequency: return "HighFrequency";
    case TriggerType::NotApplicable:
    default:
      return "NotApplicable";
  }
}

#endif
