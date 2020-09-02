cmake_minimum_required(VERSION 3.18)

project(cmake-mem-checker-issue)

set(VALGRIND "Valgrind")
set(ASAN "AddressSanitizer")

if(NOT MEMORY_SANITIZER)
  set(MEMORY_SANITIZER
      "None"
      CACHE STRING "Memory sanitizer for build, choose from ${VALGRIND}, ${ASAN} and None" FORCE)
  set_property(CACHE MEMORY_SANITIZER PROPERTY STRINGS ${VALGRIND} ${ASAN} "None")
endif()

if(${MEMORY_SANITIZER} MATCHES ${VALGRIND})
  find_program(MEMORYCHECK_COMMAND valgrind REQUIRED)
  set(MEMORYCHECK_TYPE Valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS
      "--leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --verbose --error-exitcode=1"
  )
endif()

if(${MEMORY_SANITIZER} MATCHES ${ASAN})
  set(MEMORYCHECK_TYPE AddressSanitizer)
  set(MEMORYCHECK_SANITIZER_OPTIONS
      "ASAN_OPTIONS=verbosity=1:fast_unwind_on_malloc=0:strict_string_checks=1:detect_stack_use_after_return=1:check_initialization_order=1:strict_init_order=1"
  )
  add_compile_options(
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang,GNU>:-fsanitize=address;-fno-omit-frame-pointer;-fsanitize-address-use-after-scope;-fstack-protector-all>"
  )
  add_link_options("$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang,GNU>:-fsanitize=address>")
endif()

if(NOT ${MEMORY_SANITIZER} MATCHES "None")
  message(STATUS "Build with enabled sanitizer: ${MEMORY_SANITIZER}")
else()
  message(STATUS "Sanitizers are disabled in build")
endif()

add_compile_options("$<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-stdlib=libc++>")

include(CTest)
enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(ok.ut ok_test.cpp)
target_link_libraries(ok.ut PRIVATE GTest::gmock GTest::gtest GTest::gtest_main)
gtest_discover_tests(ok.ut)

add_executable(leaking.ut leaking_test.cpp)
target_link_libraries(leaking.ut PRIVATE GTest::gmock GTest::gtest GTest::gtest_main)
gtest_discover_tests(leaking.ut)

add_executable(double-free.ut double_free_test.cpp)
target_link_libraries(double-free.ut PRIVATE GTest::gmock GTest::gtest GTest::gtest_main)
gtest_discover_tests(double-free.ut)