# Data Structures

Note: exit(EXIT_FAILURE) is causing memory leaks (in general, need to check any function that fails deallocates correctly).

Note: Check input failure on index functions. E.g. delete_at(size_t index) makes index=18446744073709551615 for input -1.

Note: PLEASE GET CATCH2 TO WORK

Note: Override <<.