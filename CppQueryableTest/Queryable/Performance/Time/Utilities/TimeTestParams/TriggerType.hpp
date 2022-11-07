#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TRIGGERTYPE_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TRIGGERTYPE_H

#include <sstream>
#include <string>

namespace TriggerType
{

enum class Type
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

static std::string GetTriggerName(TriggerType::Type type)
{
  switch (type)
  {
    case TriggerType::Type::Begin: return "Begin";
    case TriggerType::Type::Quarter: return "Quarter";
    case TriggerType::Type::Half: return "Half";
    case TriggerType::Type::ThreeQuarter: return "ThreeQuarter";
    case TriggerType::Type::End: return "End";
    case TriggerType::Type::Never: return "Never";
    case TriggerType::Type::LowFrequency: return "LowFrequency";
    case TriggerType::Type::MediumFrequency: return "MediumFrequency";
    case TriggerType::Type::HighFrequency: return "HighFrequency";
    case TriggerType::Type::NotApplicable:
    default:
      return "NotApplicable";
  }
}
}

#endif
