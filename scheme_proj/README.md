refactoring in progress
//readList & readCdr similarity
//tokenize first. pull in buffer, populate token stream, parse token stream
//remove globals, current magic sequence 4, 'a, (* 6 7) //access vector.size() elem
//using c++17 inline to avoid "externs"
//using c++17 variant Atom definition, do not leak variant outside of Atom!!
put symbol as separate type, and move global defined symbols under Symbol
keep track memory allocation
