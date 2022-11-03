#include <gtest/gtest.h>

#include "../../../DataStructures/PersonLibrary.hpp"

#include "Headers/FunctionalTests.hpp"

int main(int argc, char ** argv)
{
  ::testing::GTEST_FLAG(throw_on_failure) = true;
  FunctionalTests tests;
  if (argc <= 1 || !tests.IsValidSuite(argv[1])) tests.RunAll();
  else for (int i = 1; i < argc; i++) tests.RunTestSuite(argv[i]);
}