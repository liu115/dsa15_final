//bank_rb_tree.cpp
//Copyright 2015-6 dsa_final15

#include "bank_rb_tree.h"
int word_compare(const void *pa, const void *pb, void *param){
  const DataNode *a = ((const DataNode *)pa);
  const DataNode *b = ((const DataNode *)pb);

  if (a->first->compare(*(b->first)) < 0) return -1;
  else if (a->first->compare(*(b->first)) > 0) return +1; 
  else return 0;
}


void BankRBTree::loginAccount(const string& id, const string& passwd){
  string now_id = id;
  DataNode la = DataNode(&now_id, NULL);
  DataNode* res = (DataNode*)rb_find(rb_tree, &la);
  if(res == NULL)
    cout << "ID " << id << " not found\n";
  else{
    if(res->second->verifyPassword(passwd) == true){
      current_login_user = id;
      cout << "success\n";
    }
    else {
      cout << "wrong password\n";
    }
  }
}

void BankRBTree::createAccount(const string& id, const string& passwd){
  string now_id = id;
  DataNode la = DataNode(&now_id, NULL);
  if(rb_find(rb_tree, &la) == NULL){
    string* now_id = new string(id);
    Account* new_ac = new Account(id, passwd);
    DataNode* data = new DataNode(now_id, new_ac);
    rb_probe(rb_tree, data);
    cout << "success\n";
  }
  else{
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

void BankRBTree::deleteAccount(const string& id, const string& passwd){
  //if(&rb_tree == NULL)
    //cout << "ID " << id << " not found\n";
  string now_id = id;
  DataNode la = DataNode(&now_id, NULL);
  DataNode* res = (DataNode*)rb_find(rb_tree, &la);
  if(res == NULL)
    cout << "ID " << id << " not found\n";
  else
    if(res->second->verifyPassword(passwd) == true){
      rb_delete(rb_tree, res);
      cout << "success\n";
    }
    else
      cout << "wrong password\n";
}

void BankRBTree::mergeAccount(const string& id1, const string& passwd1, const string& id2, const string& passwd2){
  string now_id1 = id1;
  DataNode la1 = DataNode(&now_id1, NULL);
  DataNode* res1 = (DataNode*)rb_find(rb_tree, &la1);
  string now_id2 = id2;
  DataNode la2 = DataNode(&now_id2, NULL);
  DataNode* res2 = (DataNode*)rb_find(rb_tree, &la2);
  if(res1 == NULL){
    cout << "ID " << id1 << " not found\n";
    return;
  }
  if(res2 == NULL){
    cout << "ID " << id2 << " not found\n";
    return;
  }
  if(res1->second->verifyPassword(passwd1) == false){
    cout << "wrong password1\n";
    return;
  }
  if(res2->second->verifyPassword(passwd2) == false){
    cout << "wrong password2\n";
    return;
  }
  res1->second->mergeAccount(*(res2->second));
  rb_delete(rb_tree, res2);
}

void BankRBTree::accountDeposit(const int& money){
  DataNode la = DataNode(&current_login_user, NULL);
  DataNode* res = (DataNode*)rb_find(rb_tree, &la);
  res->second->depositMoney(money);
}

void BankRBTree::accountWithdraw(const int& money){
  DataNode la = DataNode(&current_login_user, NULL);
  DataNode* res = (DataNode*)rb_find(rb_tree, &la);
  res->second->withdrawMoney(money);
}

void BankRBTree::transfer(const string& id, const int& money){
  string now_id = id;
  DataNode la2 = DataNode(&now_id, NULL);
  DataNode* res2 = (DataNode*)rb_find(rb_tree, &la2);
  if(res2 == NULL){
    cout << "ID " << id << " not found, ";
    RecommendId rid;
    existRecommend(id, rid);
    if(rid.size() > 0)
      cout << rid[0];
    for (int i = 1; i < rid.size(); ++i)
      cout << "," << rid[i];
    cout << "\n";
  }
  else{
    DataNode la = DataNode(&current_login_user, NULL);
    DataNode* res = (DataNode*)rb_find(rb_tree, &la);
    res->second->transferOut((*(res2->second)), money, lg);
  }
}

void BankRBTree::findAccount(const string& rex_exp){
  cout << "\n";
}

void BankRBTree::searchHistory(const string& id){
  DataNode la = DataNode(&current_login_user, NULL);
  DataNode* res = (DataNode*)rb_find(rb_tree, &la);
  //Account* res1 = (Account*)rb_find(&rb_tree, &current_login_user);
  res->second->searchHistory(id);   
}

// following is for recommending accounts
int BankRBTree::max_num(const int a, const int b) { return (a < b)?b:a;}

int BankRBTree::min_num(const int a, const int b) { return (a < b)?a:b;}

int BankRBTree::abs_num(const int a) { return (a < 0)?-a:a;}

char BankRBTree::next_char(const char c) {
  char next_c = c + 1;
  if (next_c == 123) // if next_c is exceeding z
    next_c = 48;
  else if (next_c == 91) // if next_c is exceeding Z
    next_c = 97;
  else if (next_c == 58) // if next_c is exceeding 9
    next_c = 65;
  return next_c;
}

char BankRBTree::prev_char(const char c) {
  char next_c = c - 1;
  if (next_c == 47) // if next_c is exceeding 0
    next_c = 122;
  else if (next_c == 96) // if next_c is exceeding z
    next_c = 90;
  else if (next_c == 64) // if next_c is exceeding 9
    next_c = 57;
  return next_c;
}

int BankRBTree::computeScoring(const string& str1, const string& str2) {
  int score = 0, min_len = min_num(str1.length(), str2.length());
  for (int i = 0; i < min_len; i++) {
    if(str1[i] != str2[i]) score += (min_len - i);
  }
  int delta = abs_num((int)(str1.length() - str2.length()));
  score += delta * (delta + 1) / 2;
  return score;
}

void BankRBTree::getRecommend(const string& oid, RecommendId& rid) {
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

void BankRBTree::runRecommend(string id, string oid, int len, RecommendId& rid, int degree_c, int degree_a) {
  if (degree_c == 0 && degree_a == 0) {
    string now_id = id;
  DataNode la = DataNode(&now_id, NULL);
  DataNode* res = (DataNode*)rb_find(rb_tree, &la);
    //Account* res = (Account*)rb_find(&rb_tree, &id);
    if (res == NULL) {
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

void BankRBTree::existRecommend(const string& oid, RecommendId& id_container) {
  id_container.clear();
  id_container.reserve(10);
  vector< pair<int, string> > score_id;
  //score_id.reserve(umap.size() + 1);
  int score;
  string id;
  rb_traverser bank_traverser;
  rb_t_init(&bank_traverser, rb_tree);
  DataNode* res = (DataNode*)rb_t_first(&bank_traverser, rb_tree);
  while(res != NULL){
    id = (*(res->first));
    score = computeScoring(oid, id);
    score_id.push_back(make_pair(score, id));
    res = (DataNode*)rb_t_next(&bank_traverser);
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