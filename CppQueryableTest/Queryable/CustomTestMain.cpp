#include "../../DataStructures/PersonLibrary.hpp"

#include "TestSuiteCollection.hpp"

int main(int argc, char ** argv)
{
  TestSuiteCollection tests;
  if (argc <= 1 || !tests.IsValidSuite(argv[1])) tests.RunAll();
  else for (int i = 1; i < argc; i++) tests.RunTestSuite(argv[i]);
}