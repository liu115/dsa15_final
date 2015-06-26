// char_func.h
// Copyright 2015-06 dsa_final15

#ifndef SRC_CHAR_FUNC_H_
#define SRC_CHAR_FUNC_H_

char next_char(const char& c) {
  char next_c = c + 1;
  if (next_c == 123) // if next_c is exceeding z
    next_c = 48;
  else if (next_c == 91) // if next_c is exceeding Z
    next_c = 97;
  else if (next_c == 58) // if next_c is exceeding 9
    next_c = 65;
  return next_c;
}

#endif // SRC_CHAR_FUNC_H_

