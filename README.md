# cmake_mem_checker_issue - fixed by https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5698

Project showing CMake/CTest issue related to lack of output from memchecks.

Reported issue: https://gitlab.kitware.com/cmake/cmake/-/issues/21155#note_885072

Pull request with fix: https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5698

Reproduce steps:
```
mkdir build && cd build
cmake .. -DMEMORY_SANITIZER="AddressSanitizer"
make all
ctest --schedule-random --output-on-failure -D ExperimentalMemCheck
```

Result:
- Sanitizers sucessfully executed test cases produce print about missing memory tester output.
- Valgrind failures have output saved into Testing/Temporary directory.
- Sanitizers (ASAN) failed tests output is not saved into Testing/Temporary directory.

Expected result:
- Sanitizers sucessfully executed test cases should not emit any warning/error print.
- Output from all failed tests with sanitizers should have output in Testing/Temporary.


Manual execution of each binary produces nice output, which can be checked under example_logs dir.
