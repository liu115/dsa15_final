// recommend.h
// Copyright 2015-06 DSA15_final15
// the functions for recommend.cpp
// will be merge into other .h later

#ifndef SRC_RECOMMEND_H_
#define SRC_RECOMMEND_H_

#include <vector>

#define RECOMMEND_SIZE 10
#define MAX_STRING_SIZE 100

using namespace std;
typedef vector<string> RecommendId;

int scoring(string&, string&);
void getRecommend(string&, RecommendId&);
void runRecommend(string, string, int, RecommendId&, int, int);


#endif // SRC_RECOMMEND_H_

