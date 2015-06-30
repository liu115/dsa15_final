// bank_trie.cpp
// Copyright 2015-06 dsa_final15

#include "bank_trie.h"
Account *BankTrie::getAccount(const string &id) {
    Node *node = tree.find(tree.root, id, 0, id.length() - 1);
    if (node == NULL || node->element == NULL) return NULL;
    return node->element;
}
void BankTrie::addAccount(const string &id, Account *ac) {
  string *newid = new string(id);
  tree.insert(tree.root, *newid, 0, (*newid).length() - 1, ac);
}

void BankTrie::loginAccount(const string &id, const string &passwd) {
  Account *ac = getAccount(id);
  if (ac == NULL) {
    cout << "ID " << id << " not found\n";
  }
  else {
    if (ac->verifyPassword(passwd)) {
      current_login_user = id;
      cout << "success\n";
    }
    else {
      cout << "wrong password\n";
    }
  }
}
void BankTrie::createAccount(const string& id, const string& passwd) {
  Account *ac = getAccount(id);
  if (ac == NULL) {
    Account *new_ac = new Account(id, passwd);
    addAccount(id, new_ac);  //insert new element
    cout << "success\n";
  } else {
    cout << "ID " << id << " exists, ";
    RecommendId best10;
    getRecommend(id, best10);
    cout << best10[0];
    for (int i = 1; i < 10; i++) cout << "," << best10[i];
    cout << "\n";
    // recommend 10 best account
  }
}

void BankTrie::deleteAccount(const string& id, const string& passwd) {
  Account *ac = getAccount(id);
  if (ac == NULL) {
    cout << "ID " << id << " not found\n";
  } else {
    if (ac->verifyPassword(passwd)) {
      tree.remove(tree.root, id, 0, id.length() - 1);  //remove element
      cout << "success\n";
    } else {
      cout << "wrong password\n";
    }
  }
}

void BankTrie::mergeAccount(const string& id1, const string& passwd1, const string& id2, const string& passwd2) {
  Account *ac1 = getAccount(id1);
  Account *ac2 = getAccount(id2);
  if (ac1 == NULL) {
    cout << "ID " << id1 << " not found\n";
    return;
  }
  if (ac2 == NULL) {
    cout << "ID " << id2 << " not found\n";
    return;
  }
  if (!ac1->verifyPassword(passwd1)) {
    cout << "wrong password1\n";
    return;
  }
  if (!ac2->verifyPassword(passwd2)) {
    cout << "wrong password2\n";
    return;
  }
  ac1->mergeAccount(*ac2);
  tree.remove(tree.root, id2, 0, id2.length() - 1);
}

void BankTrie::accountDeposit(const int& money) {
  Account *ac = getAccount(current_login_user);
  ac->depositMoney(money);
}

void BankTrie::accountWithdraw(const int& money) {
  Account *ac = getAccount(current_login_user);
  ac->withdrawMoney(money);
}

void BankTrie::transfer(const string& id, const int& money) {
  Account *ac2 = getAccount(id);  //find
  if (ac2 == NULL) {
    cout << "ID " << id << " not found, ";
    // recommend 10 best exist id
    RecommendId rid;
    existRecommend(id, rid);
    if (rid.size() > 0)
      cout << rid[0];
    for (int i = 1; i < rid.size(); ++i)
      cout << "," << rid[i];
    cout << "\n";
  } else {
    Account *ac1 = getAccount(current_login_user);
    ac1->transferOut(*ac2, money, lg);
  }
}

void BankTrie::findAccount(const string& reg_exp) {
  cout << "\n";
}

void BankTrie::searchHistory(const string& id) {
  Account *ac = getAccount(current_login_user);
  ac->searchHistory(id);
}

//following is for recommending accounts
int BankTrie::max_num(const int a, const int b) { return (a < b)?b:a;}

int BankTrie::min_num(const int a, const int b) { return (a < b)?a:b;}

int BankTrie::abs_num(const int a) { return (a < 0)?-a:a;}

char BankTrie::next_char(const char c) {
  char next_c = c + 1;
  if (next_c == 123) // if next_c is exceeding z
    next_c = 48;
  else if (next_c == 91) // if next_c is exceeding Z
    next_c = 97;
  else if (next_c == 58) // if next_c is exceeding 9
    next_c = 65;
  return next_c;
}

char BankTrie::prev_char(const char c) {
  char next_c = c - 1;
  if (next_c == 47) // if next_c is exceeding 0
    next_c = 122;
  else if (next_c == 96) // if next_c is exceeding z
    next_c = 90;
  else if (next_c == 64) // if next_c is exceeding 9
    next_c = 57;
  return next_c;
}

int BankTrie::computeScoring(const string& str1, const string& str2) {
  int score = 0, min_len = min_num(str1.length(), str2.length());
  for (int i = 0; i < min_len; i++) {
    if(str1[i] != str2[i]) score += (min_len - i);
  }
  int delta = abs_num((int)(str1.length() - str2.length()));
  score += delta * (delta + 1) / 2;
  return score;
}

void BankTrie::getRecommend(const string& oid, RecommendId& rid) {
  rid.clear();
  int degree = 1, new_size = 0;
  while (rid.size() < RECOMMEND_SIZE) {
    for (int i = 0; i <= degree; i++) {
      runRecommend(oid, oid, 0, rid, i, degree - i);
    }
    sort(rid.begin() + new_size, rid.end());
    new_size = rid.size();
    if (rid.size() >= RECOMMEND_SIZE) break;
    degree++;
  }
}

void BankTrie::runRecommend(string id, string oid, int len, RecommendId& rid, int degree_c, int degree_a) {
  if (degree_c == 0 && degree_a == 0) {
    Account *ac = getAccount(id);
    if (ac == NULL) {
      // it means that the id isn't exist in the bank
      rid.push_back(id);
      return;
    }
  }
  string tmpid;
  int delta = abs_num((int)oid.length() - (int)id.length());
  if (degree_a > delta) {
    if (id.length() >= oid.length() && id.length() < MAX_STRING_SIZE) {
      for (char c = '0'; ; c = next_char(c)) {
        runRecommend(id + c, oid, id.length() + 1, rid, degree_c, degree_a - delta - 1);
        if (c == 'z') break;
      }
    }
    if (id.length() <= oid.length() && id.length() > len && id.length() > 1) {
      tmpid = id;
      tmpid.pop_back();
      runRecommend(tmpid, oid, len, rid, degree_c, degree_a - delta - 1);
    }
  }
  if (degree_c > 0) {
    for (int i = max_num(min_num(id.length(), oid.length()) - degree_c, len); i < min_num(oid.length(), id.length()); i++) {
      if (degree_c >= min_num(oid.length(), id.length()) - i) {
        for (char c = '0'; c <= 'z'; c = next_char(c)) {
          if (c != oid[i]) {
          tmpid = id;
          tmpid[i] = c;
          runRecommend(tmpid, oid, i + 1, rid, degree_c - (min_num(oid.length(), id.length()) - i), degree_a);
          }
          if (c == 'z') break;
        }
      }
    }
  } 
}

void BankTrie::existRecommend(const string& oid, RecommendId& id_container) {
  id_container.clear();
  id_container.reserve(10);
  vector< pair<int, string> > score_id;
  score_id.reserve(tree.getSize() + 1);
  int score;
  string id;
  computeAllScore(tree.root, score_id, oid);
  int i = 0, j, selected_index;
  while (i < 10 && i < score_id.size()) {
    score = score_id[i].first;
    id = score_id[i].second;
    selected_index = i;
    for (j = i; j < score_id.size(); ++j) {
      if (score_id[j].first < score) {
        score = score_id[j].first;
        id = score_id[j].second;
        selected_index = j;
      } else if (score_id[j].first == score && id.compare(score_id[j].second) > 0) {
        score = score_id[j].first;
        id = score_id[j].second;
        selected_index = j;
      }
    }
    std::swap(score_id[i], score_id[selected_index]);
    id_container.push_back(score_id[i].second);
    i++;
  }
}
