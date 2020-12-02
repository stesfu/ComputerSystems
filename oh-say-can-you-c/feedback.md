

## Salem Tesfu

##### https://github.com/lmu-cmsi284-spring2020/oh-say-can-you-c-stesfu

| Category/Feedback | Points |
| --- | ---: |
| **code-point-to-utf8.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs.  | 1/1 |
| • _Correct program output?_ All tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ The program should print out the exact string given in the assignment instructions when no arguments are supplied (–0.2). | 0.8/1 |
| **split-string-at-index.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 4/4 |
| • _Correct program output?_ All tests pass. | 12/12 |
| • _Correct handling of invalid user input?_ All tests pass. | 4/4 |
| **print-max-note-lengths.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 1/1 |
| • _Correct program output?_ Missing period in the output, but otherwise all tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ No deduction, but ideally, the program prints out some kind of message when arguments are unexpectedly supplied, to inform the user that these aren’t necessary. | 1/1 |
| **get-note-index.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs.  | 1/1 |
| • _Correct program output?_ All tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ All tests pass. | 1/1 |
| **get-chord-index.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs.  | 1/1 |
| • _Correct program output?_ All tests pass. | 3/3 |
| • _Correct handling of invalid user input?_ All tests pass. | 1/1 |
| **split-note-and-chord.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 6/6 |
| • _Correct program output?_ The overall program performs the computation correctly, and also does it in a generalized manner that is completely data-driven by the content of _notes.h_. However, it doesn’t do this in the most efficient way. Some points:<br><br>• The program quietly changes the definition of `split_note_and_chord` so that it returns a new special-case value of `1` when the chord suffix is the empty string. This is not necessary—the program can be written to avoid this special case<br><br>• `get_string_index` and the `split_string_at_index` call that calls this actually don’t have any effect on the computation—it can be completely removed, and that `if` statement can simply have a `return 0;`<br><br>These are indeed issues but they are all “under the hood” so we will apply just a –1 deduction total.<br><br>The change to `split_note_and_chord`’s return value counts as a divergence from the original function’s specified behavior and will be deducted from the corresponding grading category. | 17/18 |
| • _Correct handling of invalid user input?_ Missing period in the output, but otherwise all tests pass. | 6/6 |
| **print-chord.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 4/4 |
| • _Correct program output?_ All tests pass.<br><br>One deeper note: declarations like `char chords[CHORD_STEP_COUNT[chord_index] + 1]` should be avoided in the future because this is a dynamically-sized string that is being defined statically—something that will not work in some C compilers. The proper solution would use `malloc` but of course you didn’t know about `malloc` at this point (nor probably realized that a statically-allocated string based on a runtime variable is a no-no), so we’ll let it be. The chord can be printed without use of any temporary arrays or string concatenation: just print notes as you traverse `NOTES` within the loop. | 12/12 |
| • _Correct handling of invalid user input?_ Range checking is off-by-one: C-arrays are zero-based, so `NOTE_COUNT` and `CHORD_COUNT` themselves aren’t valid (–1).<br><br>Small typo in the output, but we won’t deduct for that. | 3/4 |
| **chord.c** | |
| • _Compiles and runs without unexpected errors?_ Program compiles and runs. | 2/2 |
| • _Correct program output?_ Tests fail for cases where a major chord is expected—i.e., the chord suffix is an empty string. This is where the “sneaky” change in `split_note_and_chord` comes back to haunt you: although _split-note-and-chord.c_ factors in the possibility of a return value of `1`, _chord.c_ does not do this. This leads to test failures for any cases where the chord suffix is an empty string.<br><br>No re-deduction for the change in `split_note_and_chord`’s behavior, but we do apply a deduction for missing that _chord.c_ missed considering that case as well (–2). | 4/6 |
| • _Correct handling of invalid user input?_ Missing period in the chord validity error message, but otherwise all tests pass. | 2/2 |
| **Input/output in functions other than `main`** No stray prints found. |  |
| **Failure to write functions as defined** `split_note_and_chord` has a change in behavior (a new return value) that was not part of the original specification (–3). | -3 |
| **Hard-to-maintain or error-prone code** No major error-prone or maintainability issues found. |  |
| **Hard-to-read code** Add spaces after reserved words like `for` and `if`, so that they don’t look like function calls. |  |
| **Version Control** 12 commits; good commit frequency and granularity, and commit messages are descriptive. Good work! |  |
| **Punctuality** First commit on 4/5 7:01pm; last commit on 4/7 11:59pm.  |  |
| **Total** | **92.8/100** |
