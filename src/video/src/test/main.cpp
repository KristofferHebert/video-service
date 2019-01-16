#include "gtest/gtest.h"

// Execute all Tests
int main(int argc, char**argv){ 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}