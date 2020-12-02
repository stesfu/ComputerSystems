

## Salem Tesfu

##### https://github.com/lmu-cmsi284-spring2020/wedd-include-c-remony-stesfu

| Category/Feedback | Points |
| --- | ---: |
| **Chord Consolidated** | |
| • _Consolidated code compiles and runs as specified?_ All files compile and run successfully.  | 6/6 |
| • _All shared/“public” functions are defined only once across all files?_ No duplicate function definitions found. | 4/4 |
| **Mine-C-Weeper** | |
| • _All programs compile and run without unexpected errors?_ All files compile and run successfully. | 10/10 |
| • _Game memory allocation is precise—no shotgun approach?_ The correct amount of memory is allocated, but `game->status` should use `sizeof(mcw_status*)` and its contents should use `sizeof(mcw_status)` rather than finding the size of an `mcw_square` (a copy-pasting error, perhaps?). An `mcw_square` and an `mcw_status` are both enums, which are also ints; so the correct amount of memory is still being allocated, but this makes the code more error prone should the implementation of `mcw_status` change. (–1) | 19/20 |
| • _Game memory is freed correctly?_ Memory is correctly freed. | 20/20 |
| • _Implemented functions produce correct results and behaviors?_ Fails on 1 out of 10 tests. | 36/40 |
| • _Complete game is playable?_ Game is playable. | 10/10 |
| • _Failure to write functions as defined?_ No divergences from function specifications were seen. |  |
| **System Call Me Maybe** | |
| The Frank (Serious) One | |
| • _Assembles, links, and runs without unexpected errors?_ Assembles, links, and appears to run successfully. | 2/2 |
| • _Correct system call invocation (`syscall`)?_ System call appears to be invoked correctly. | 3/3 |
| • _Correct program output or result?_ Program appears to work as intended. | 8/8 |
| • _Correct handling of invalid user input or erroneous results?_ Error checking appears to be performed. | 2/2 |
| The Prank (Combo) One | |
| • _Well-described expected behavior?_ Description of expected behavior is provided. | 3/3 |
| • _Assembles, links, and runs without unexpected errors?_ Assembles, links, and appears to run successfully. | 2/2 |
| • _Correct _multiple_ system call invocations (`syscall`)?_ Multiple system calls appear to be invoked correctly. | 5/5 |
| • _Correct program output or result?_ Program appears to work as intended. | 10/10 |
| • _Correct handling of invalid user input or erroneous results?_ Error checking appears to be performed. | 5/5 |
| _Insufficiently-commented instructions?_ Instruction-level comments are provided. |  |
| **Hard-to-maintain or error-prone code** No major error-prone or maintainability issues found. |  |
| **Hard-to-read code** No major readability issues found. |  |
| **Version Control** 15 commits; good commit frequency and granularity, and commit messages are descriptive. Good work! |  |
| **Punctuality** First commit on 4/17 7:04pm; last commit on 4/23 9:58pm. |  |
| **Total** | **145/150** |
