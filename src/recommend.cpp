// recomand.cpp
// Copyright 2015.06 DSA15_final15
// This providse the operation 'create' to make recommandetions for users when the accountId has already been created

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "recommend.h"
#include "char_func.h"
using namespace std;
int max_num(const int a, const int b) { return (a < b)?b:a;}
int min_num(const int a, const int b) { return (a < b)?a:b;}
int scoring(string& str1, string& str2) {
  int score = 0, min_len = min_num(str1.length(), str2.length());
  for (int i = 0; i < min_len; i++) {
    if(str1[i] != str2[i]) score += (min_len - i);
  }
  score += (str1.length() - min_len) + (str2.length() - min_len);
  return score;
}

/*
getRecommend: find id strings with smallest scores with origin id string, and put them into rid.

oid: the origin id string
rid: id strings of recommendations
*/
void getRecommend(string& oid, RecommendId& rid) {
  rid.clear();
  int degree = 1;
  while (rid.size() < RECOMMEND_SIZE) {
    
    for (int i = 0; i <= degree; i++) {
      if (rid.size() >= RECOMMEND_SIZE) break;
      runRecommend(oid, oid, 0, rid, i, degree - i);
    }
    degree++;
  }
}

/*
runRecommend: recursively find id strings that satisfied the given degree(score), and add them to the string vector.

id: the id string we're working on
oid: the origin id string
len: the length that is modify
rid: id strings of recommendations
degree_c: degree to change a characher in the string
degree_a: degree to add suffix string, or delete suffix
*/

void runRecommend(string id, string oid, int len, RecommendId& rid, int degree_c, int degree_a) {
  if (rid.size() >= RECOMMEND_SIZE) {
    return;
  }
  
  if (degree_c == 0 && degree_a == 0) {
    //if id it's ok (no same id)
      rid.push_back(id);
      return;
  }
  string tmpid;
  if (degree_c > 0) {
    for (int i = max_num(oid.length() - degree_c, len); i < min_num(oid.length(), id.length()); i++) {
      for (char c = '0'; c <= 'z'; c = next_char(c)) {
        if (c != oid[i]) {
          tmpid = id;
          tmpid[i] = c;
          runRecommend(tmpid, oid, i + 1, rid, degree_c - (oid.length() - i), degree_a);
        }
        if (c == 'z') break;
      }
    }
  }
  if (degree_a > 0) {
    if (id.length() >= oid.length() && id.length() < MAX_STRING_SIZE) {
      for (char c = '0'; ; c = next_char(c)) {
        runRecommend(id + c, id, len, rid, degree_c, degree_a - 1);
        if (c == 'z') break;
      }
    }
    if (id.length() <= oid.length() && id.length() > len && id.length() > 1) {
      tmpid = id;
      tmpid.pop_back();
      runRecommend(tmpid, id, len, rid, degree_c, degree_a - 1);
    }
  }
}

