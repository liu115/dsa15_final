// transfer_log.h
// Copyright 2015-06 dsa_final15

#ifndef SRC_TRANSFER_LOG_H_
#define SRC_TRANSFER_LOG_H_

#include <string>
using std::string;

struct logNode {
  int time_record;
  bool isFrom;
  string id;
  int amount;
  logNode *next, *pre;
  logNode(const int& t, const bool& cond, const string& s, const int& n): time_record(t), isFrom(cond), id(s), amount(n), next(0), pre(0) {}
};

class TransferLog {
 public:
  int timer;

  logNode *head, *current;

  TransferLog() {
    timer = 1;
    head = new logNode(0, false, "begin", 0);
    current = head;
  }

  ~TransferLog() {
    logNode *curr, *ptr;
    curr = ptr = head;
    while (ptr != NULL) {
      curr = ptr;
      ptr = ptr->next;
      delete curr;
    }
  }

  void addLog(const string& giver, const string& receiver, const int& n) {
    current->next = new logNode(timer, false, receiver, n); // TO
    (current->next)->pre = current;
    current = current->next;

    current->next = new logNode(timer, true, giver, n); // FROM
    (current->next)->pre = current;
    current = current->next;

    timer++;
  }

  logNode* getCurrPos() {
    return current;
  }

};

#endif // SRC_TRANSFER_LOG_H_
