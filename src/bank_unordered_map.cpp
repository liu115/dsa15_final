// umap_unordered_map.cpp
// Copyright 2015-06 dsa_final15

#include "bank_unordered_map.h"

void BankUMap::loginAccount(const string& id, const string& passwd) {
  UMap::iterator it = umap.find(id);
  if (it == umap.end())
    cout << "ID " << id << " not found\n";
  else {
    if ((*it).second.verifyPassword(passwd)) {
      current_login_user = id;
      cout << "success\n";
    } else {
      cout << "wrong password\n";
    }
  }
}

void BankUMap::createAccount(const string& id, const string& passwd) {
  UMap::iterator it = umap.find(id);
  if (it == umap.end()) {
    Account new_ac(id, passwd);
    umap.insert(make_pair(id, new_ac));
    cout << "success\n";
  } else {
    cout << "ID " << id << " exists, ";
    // recommend 10 best account
    RecommendId best10;
    getRecommend(id, best10);
    cout << best10[0];
    for (int i = 1; i < 10; ++i)
      cout << "," <<  best10[i];
    cout << "\n";
  }
}

void BankUMap::deleteAccount(const string& id, const string& passwd) {
  UMap::iterator it = umap.find(id);
  if (it == umap.end()) {
    cout << "ID " << id << " not found\n";
  } else {
    if ((*it).second.verifyPassword(passwd)) {
      umap.erase(it);
      cout << "success\n";
    } else {
      cout << "wrong password\n";
    }
  }
}

void BankUMap::mergeAccount(const string& id1, const string& passwd1, const string& id2, const string& passwd2) {
  UMap::iterator it1 = umap.find(id1);
  UMap::iterator it2 = umap.find(id2);
  if (it1 == umap.end()) {
    cout << "ID " << id1 << " not found\n";
    return;
  }
  if (it2 == umap.end()) {
    cout << "ID " << id2 << " not found\n";
    return;
  }
  if (!(*it1).second.verifyPassword(passwd1)) {
    cout << "wrong password1\n";
    return;
  }
  if (!(*it2).second.verifyPassword(passwd2)) {
    cout << "wrong password2\n";
    return;
  }
  (*it1).second.mergeAccount((*it2).second);
  umap.erase(it2);
}

void BankUMap::accountDeposit(const int& money) {
  UMap::iterator it = umap.find(current_login_user);
  (*it).second.depositMoney(money);
}

void BankUMap::accountWithdraw(const int& money) {
  UMap::iterator it = umap.find(current_login_user);
  (*it).second.withdrawMoney(money);
}

void BankUMap::transfer(const string& id, const int& money) {
  UMap::iterator it2 = umap.find(id);
  if (it2 == umap.end()) {
    cout << "ID " << id << " not found, ";
    RecommendId rid;
    existRecommend(id, rid);
    if (rid.size() > 0)
      cout << rid[0];
    for (int i = 1; i < rid.size(); ++i)
      cout << "," << rid[i];
    cout << "\n";
  } else {
    UMap::iterator it1 = umap.find(current_login_user);
    (*it1).second.transferOut((*it2).second, money, lg);
  }
}

void BankUMap::findAccount(const string& reg_exp) {
  RecommendId vec;
  std::regex reg(regex_change(reg_exp));
  for (UMap::iterator it = umap.begin(); it != umap.end(); ++it) {
    if (std::regex_match(it->first, reg) && it->first != current_login_user)
      vec.push_back(it->first);
  }
  if (vec.size() > 0) {
    sort(vec.begin(), vec.end());
    cout << vec[0];
    for (int i = 1; i < vec.size(); ++i)
      cout << "," << vec[i];
  }
  cout << "\n";
}

void BankUMap::searchHistory(const string& id) {
  UMap::iterator it1 = umap.find(current_login_user);
  (*it1).second.searchHistory(id);
}

// following is for recommending accounts
int BankUMap::max_num(const int a, const int b) { return (a < b)?b:a;}

int BankUMap::min_num(const int a, const int b) { return (a < b)?a:b;}

int BankUMap::abs_num(const int a) { return (a < 0)?-a:a;}

char BankUMap::next_char(const char c) {
  char next_c = c + 1;
  if (next_c == 123) // if next_c is exceeding z
    next_c = 48;
  else if (next_c == 91) // if next_c is exceeding Z
    next_c = 97;
  else if (next_c == 58) // if next_c is exceeding 9
    next_c = 65;
  return next_c;
}

char BankUMap::prev_char(const char c) {
  char next_c = c - 1;
  if (next_c == 47) // if next_c is exceeding 0
    next_c = 122;
  else if (next_c == 96) // if next_c is exceeding z
    next_c = 90;
  else if (next_c == 64) // if next_c is exceeding 9
    next_c = 57;
  return next_c;
}

int BankUMap::computeScoring(const string& str1, const string& str2) {
  int score = 0, min_len = min_num(str1.length(), str2.length());
  for (int i = 0; i < min_len; i++) {
    if(str1[i] != str2[i]) score += (min_len - i);
  }
  int delta = abs_num((int)(str1.length() - str2.length()));
  score += delta * (delta + 1) / 2;
  return score;
}

void BankUMap::getRecommend(const string& oid, RecommendId& rid) {
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

void BankUMap::runRecommend(string id, string oid, int len, RecommendId& rid, int degree_c, int degree_a) {
  if (degree_c == 0 && degree_a == 0) {
    UMap::iterator it = umap.find(id);
    if (it == umap.end()) {
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

void BankUMap::existRecommend(const string& oid, RecommendId& id_container) {
  id_container.clear();
  id_container.reserve(10);
  vector< pair<int, string> > score_id;
  score_id.reserve(umap.size());
  int score;
  string id;
  for (UMap::iterator it = umap.begin(); it != umap.end(); ++it) {
    id = it->first;
    score = computeScoring(oid, id);
    score_id.push_back(make_pair(score, id));
  }
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

std::string regex_change(const std::string& wildcard_ID){
  std::string res = wildcard_ID;
  std::string reg = "[a-zA-Z0-9]";
  int pos = 0;
  while(pos != -1){
    pos = res.find("*", pos);
    if(pos != -1){
      res.insert(pos, reg);
      pos += 12;
    }
  }
  pos = 0;
  while( pos != -1){
    pos = res.find("?", pos);
    if( pos != -1){
      res.replace(pos, 1, reg);
      pos += 11;
    }
  }
  return res;
}
