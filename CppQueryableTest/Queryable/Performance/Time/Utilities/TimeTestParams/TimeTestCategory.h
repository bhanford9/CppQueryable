#ifndef CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H
#define CPPQUERYABLE_CPPQUERYABLETEST_QUERYABLE_PERFORMANCE_TIME_UTILITIES_TIMETESTPARAMS_TIMETESTCATEGORY_H

#include <string>

enum class TimeTestCategory
{
  BuiltInLowLoad,
  BuiltInMediumLoad,
  BuiltInHeavyLoad,
  ClassLowLoad,
  ClassMediumLoad,
  ClassHeavyLoad,
  Other
};

static std::string GetCategoryName(TimeTestCategory category)
{
  switch (category)
  {
    case TimeTestCategory::BuiltInLowLoad: return "BuiltInTypeWithLowLoad";
    case TimeTestCategory::BuiltInMediumLoad: return "BuiltInTypeWithMediumLoad";
    case TimeTestCategory::BuiltInHeavyLoad: return "BuiltInTypeWithHeavyLoad";
    case TimeTestCategory::ClassLowLoad: return "ClassTypeWithLowLoad";
    case TimeTestCategory::ClassMediumLoad: return "ClassTypeWithMediumLoad";
    case TimeTestCategory::ClassHeavyLoad: return "ClassTypeWithHeavyLoad";
    case TimeTestCategory::Other:
    default:
      return "Other";
  }
}

#endif
