#include <iostream>
#include <string>
#include <set>
#include <bitset>
#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;
const int B = 10000;

static int pw3[9] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561};
int squares;
int max_operators;
bool has_brackets;
int result;

bitset<B * 2> f[4][9]; // f[符号数][占位数] 结果 外层为 +-*/纯数字括号
bitset<B * 2> g[4][9]; // g[符号数][占位数] 结果 外层为 */纯数字括号
bitset<B * 2> h[4][9]; // h[符号数][占位数] 结果 纯数字 or 带括号()

map<int, vector<string>> dp[4][9][3];

int place[256];

int check_num[16];

inline bool checkValue(const int& val) {
  return val > -B && val < B;
}

vector<string> solve(int squares, int operators, int result, int level) {
  if (operators == 0) {
    if (checkValue(result) && h[0][squares][result + B]) {
      return vector<string>{to_string(result)};
    }
    return vector<string>();
  }
  if (level == 2) {
    vector<string> results = solve(squares - 2, operators, result, 0);
    vector<string> new_results;
    for (auto v : results) {
      new_results.push_back("(" + v + ")");
    }
    return new_results;
  }
  if (dp[operators][squares][level].find(result) != dp[operators][squares][level].end()) {
    return dp[operators][squares][level][result];
  }

  vector<string> results;

  // G*H=result
  for (int lop = 0; lop < operators; ++lop) {
    int rop = operators - lop - 1;
    for (int l = 1; l <= squares - 2; ++l) {
      int r = squares - 1 - l;
      if (!h[rop][r].any()) continue;
       for (int uB = g[lop][l]._Find_first(); uB < g[lop][l].size(); uB = g[lop][l]._Find_next(uB)) {
          int u = uB - B;
          if (result != 0 && (u == 0 || result % u != 0)) continue;
          if (result == 0 && u == 0) {
            // v can be any number
            vector<string> lvalue = solve(l, lop, u, 1);
            for (int vB = h[rop][r]._Find_first(); vB < h[rop][r].size(); vB = h[rop][r]._Find_next(vB)) {
              vector<string> rvalue = solve(r, rop, vB - B, 2);
              for (auto x : lvalue)
                for (auto y : rvalue) {
                  results.push_back(x + "*" + y);
                }
            }
          } else {
            int v = result / u;
            if (!h[rop][r][v + B]) continue;
            //printf("ok, s=%d, op=%d, equa=%d*%d\n", squares, operators, u, v);
            vector<string> rvalue = solve(r, rop, v, 2);
            vector<string> lvalue = solve(l, lop, u, 1);
            for (auto x : lvalue)
              for (auto y : rvalue) {
                results.push_back(x + "*" + y);
              }
          }
       }
    }
  }
  
  // G/H=result
  for (int lop = 0; lop < operators; ++lop) {
    int rop = operators - lop - 1;
    for (int l = 1; l <= squares - 2; ++l) {
      int r = squares - 1 - l;
      if (!h[rop][r].any()) continue;
       for (int uB = g[lop][l]._Find_first(); uB < g[lop][l].size(); uB = g[lop][l]._Find_next(uB)) {
          int u = uB - B;
          if (result == 0 && u != 0) continue;
          if (result != 0 && u == 0) continue;
          if (result == 0) {
            // v can be any number
            vector<string> lvalue = solve(l, lop, u, 1);
            for (int vB = h[rop][r]._Find_first(); vB < h[rop][r].size(); vB = h[rop][r]._Find_next(vB)) {
              vector<string> rvalue = solve(r, rop, vB - B, 2);
              for (auto x : lvalue)
                for (auto y : rvalue) {
                  results.push_back(x + "/" + y);
                }
            }
          } else {
            if (u % result != 0 || !checkValue(u / result)) continue;
            int v = u / result;
            if (!h[rop][r][v + B]) continue;
            //printf("ok, s=%d, op=%d, equa=%d/%d\n", squares, operators, u, v);
            vector<string> rvalue = solve(r, rop, v, 2);
            vector<string> lvalue = solve(l, lop, u, 1);
            for (auto x : lvalue)
              for (auto y : rvalue) {
                results.push_back(x + "/" + y);
              }
            }
       }
    }
  }

  if (level == 1) {
    if (squares >= 5 && f[operators][squares - 2][result + B]) {
      vector<string> low_level_results = solve(squares - 2, operators, result, 0);
      for (auto v : low_level_results) {
        results.push_back("(" + v + ")");
      }
    }
    return results;
  }

  // F+G=result
  for (int lop = 0; lop < operators; ++lop) {
    int rop = operators - lop - 1;
    for (int l = 1; l <= squares - 2; ++l) {
      int r = squares - 1 - l;
      if (!g[rop][r].any()) continue;
       for (int uB = f[lop][l]._Find_first(); uB < f[lop][l].size(); uB = f[lop][l]._Find_next(uB)) {
          int u = uB - B;
          if (!checkValue(result - u)) continue;
          int v = result - u;
          if (!g[rop][r][v + B]) continue;
          //printf("ok, s=%d, op=%d, equa=%d+%d\n", squares, operators, u, v);
          vector<string> rvalue = solve(r, rop, v, 1);
          vector<string> lvalue = solve(l, lop, u, 0);
          for (auto x : lvalue)
            for (auto y : rvalue) {
              results.push_back(x + "+" + y);
            }
       }
    }
  }

  // F-G=result
  for (int lop = 0; lop < operators; ++lop) {
    int rop = operators - lop - 1;
    for (int l = 1; l <= squares - 2; ++l) {
      int r = squares - 1 - l;
      if (!g[rop][r].any()) continue;
       for (int uB = f[lop][l]._Find_first(); uB < f[lop][l].size(); uB = f[lop][l]._Find_next(uB)) {
          int u = uB - B;
          if (!checkValue(u - result)) continue;
          int v = u - result;
          if (!g[rop][r][v + B]) continue;
          //printf("ok, s=%d, op=%d, equa=%d-%d\n", squares, operators, u, v);
          vector<string> rvalue = solve(r, rop, v, 1);
          vector<string> lvalue = solve(l, lop, u, 0);
          for (auto x : lvalue)
            for (auto y : rvalue) {
              results.push_back(x + "-" + y);
            }
       }
    }
  }

  return dp[operators][squares][level][result] = results;
}

bool check_different(string exp) {
  static int num[16];
  memset(num, 0, sizeof(num));
  for (char c : exp) {
    if (num[place[c]]) return false;
    num[place[c]] = 1;
  }
  return true;
}

vector<string> all_different(vector<string> results) {
  vector<string> different_results;
  for (auto exp : results) {
    if (check_different(exp)) {
      different_results.push_back(exp);
    }
  }
  return different_results;
}

void init() {
  for (int i = 0; i < 10; ++i) {
    place['0' + i] = i;
  }
  place['+'] = 10;
  place['-'] = 11;
  place['*'] = 12;
  place['/'] = 13;
  place['('] = 14;
  place[')'] = 15;

  for (int i = 0; i < 10; ++i) g[0][1][i+B]=1, f[0][1][i+B]=1, h[0][1][i+B]=1;
  for (int i = 10; i < 100; ++i) g[0][2][i+B]=1, f[0][2][i+B]=1, h[0][2][i+B]=1;
  for (int i = 100; i < 1000; ++i) g[0][3][i+B]=1, f[0][3][i+B]=1, h[0][3][i+B]=1;
  for (int i = 1000; i < 10000; ++i) g[0][4][i+B]=1, f[0][4][i+B]=1, h[0][4][i+B]=1;
}

void pre_cal() {
  for (int op = 1; op <= max_operators; ++op) {
    for (int lop = 0; lop < op; ++lop) {
      int rop = op - lop - 1;
      for (int l = 1; l <= squares - 2; ++l) {
        for (int uB = f[lop][l]._Find_first(); uB < f[lop][l].size(); uB = f[lop][l]._Find_next(uB)) {
          int u = uB - B;
          // F(+-)G = F
          for (int r = 1; l + r + 1 <= squares; ++r) {
            for (int vB = g[rop][r]._Find_first(); vB < g[rop][r].size(); vB = g[rop][r]._Find_next(vB)) {
              int v = vB - B;
              if (checkValue(u + v)) {
                f[op][l + r + 1][u + v + B] = 1;
                if (has_brackets && l + r + 1 + 2 <= squares - 2) { // 套上括号，整个式子最外层套括号没有意义，预留至少 2 个空
                  h[op][l + r + 3][u + v + B] = 1;
                }
              }
              if (checkValue(u - v)) {
                f[op][l + r + 1][u - v + B] = 1;
                if (has_brackets && l + r + 1 + 2 <= squares - 2) {
                  h[op][l + r + 3][u + v + B] = 1;
                }
              }
            }
          }
        }
        for (int uB = g[lop][l]._Find_first(); uB < g[lop][l].size(); uB = g[lop][l]._Find_next(uB)) {
          int u = uB - B;
          // G(*/)H = G
          for (int r = 1; l + r + 1 <= squares; ++r) {
            for (int vB = h[rop][r]._Find_first(); vB < h[rop][r].size(); vB = h[rop][r]._Find_next(vB)) {
              int v = vB - B;
              if (checkValue(u * v)) {
                g[op][l + r + 1][u * v + B] = 1;
                if (has_brackets && l + r + 1 + 2 <= squares - 2) {
                  h[op][l + r + 3][u * v + B] = 1;
                }
              }
              if (v != 0 && u % v == 0 && checkValue(u / v)) {
                g[op][l + r + 1][u / v + B] = 1;
                if (has_brackets && l + r + 1 + 2 <= squares - 2) {
                  h[op][l + r + 3][u / v + B] = 1;
                }
              }
            }
          }
        }
      }
    }
  }
}

int calc_diff(string exp, string exp2) {
  static int num[16];
  memset(num, 0, sizeof(num));
  int ret = 0;
  for (int i = 0, base = 1; i < squares; ++i, base *= 3) {
    if (exp2[i] != exp[i]) {
      num[place[exp2[i]]]++;
    }
  }
  for (int i = 0, base = 1; i < squares; ++i, base *= 3) {
    if (exp2[i] == exp[i]) {
      ret += 2 * base;
    } else {
      if (num[place[exp[i]]]) {
        --num[place[exp[i]]];
        ret += base;
      }
    }
  }

  return ret;
}

string choose_one(vector<string> all_results, vector<string> selected_results, int test_num) {
  if (all_results.size() == 1) {
    cout << "choose " << all_results[0] << endl;
    exit(0);
    return all_results[0];
  }
  if (all_results.size() == 0) {
    cout << "something wrong, no valid expression!" << endl;
    exit(0);
  }
  if (selected_results.size() > test_num) {
    random_shuffle(selected_results.begin(), selected_results.end());
  }
  double maxv = -1e100;
  string choose_one;
  for (int i = 0; i < test_num; ++i) {
    string exp = selected_results[i];
    static int num[6561];
    memset(num, 0, sizeof(num));
    for (auto exp2 : all_results) {
      // maxv = max(maxv, ++num[calc_diff(exp, exp2)]);
      ++num[calc_diff(exp, exp2)];
    }
    double e = 0;
    for (int i = 0; i < pw3[squares]; ++i) {
      if (num[i] > 0) {
        e += 1.0 * num[i] / all_results.size() * (log(1.0 * all_results.size() / num[i]) / log(2));
        if (i == pw3[squares] - 1) {
          e += 1.0 * num[i] / all_results.size() * (log(1.0 * all_results.size() / num[i]) / log(2));
        }
      }
    }
    if (e > maxv) {
      maxv = e;
      choose_one = exp;
    }
  }
  cout << "choose " << choose_one << endl;
  return choose_one;
}

vector<string> filter(vector<string> all_results, string enter_exp, string ret) {
  int value = 0;
  for (int i = 0, base = 1; i < squares; ++i, base *= 3) {
    value += (ret[i] - '0') * base;
  }

  vector<string> filtered;
  for (auto exp : all_results) {
    assert(exp.size() == squares);
    if (calc_diff(enter_exp, exp) == value) {
      filtered.push_back(exp);
    }
  }
  return filtered;
}

int main() {
  cout << "squares(no more than 8): " << endl;
  cin >> squares;
  cout << "max operators(no more than 3): " << endl;
  cin >> max_operators;
  cout << "has brackets('y' or 'n'): " << endl;
  string tmp;
  cin >> tmp;
  has_brackets = tmp[0] == 'y';
  cout << "result(absolute value not exceed 9999): " << endl;
  cin >> result;

  init();
  pre_cal();

  vector<string> all_results;
  vector<string> results[max_operators + 1];

  for (int i = max_operators; i >= 0; --i) {
    results[i] = solve(squares, i, result, 0);
    cout << "operators: " << i << ", expressions: " << results[i].size() << endl;
    for (auto v : results[i]) {
      assert(v.size() == squares);
      all_results.push_back(v);
    }
  }
  cout << "all expressions: " << all_results.size() << endl;
  if (all_results.size() >= 1) {
    cout << "example: " << all_results[all_results.size()/2] << endl;
  }
  
  auto diff_results = all_different(results[max_operators]);
  cout << "different expressions with max operators: " << diff_results.size() << endl;
  // cout << "example: " << diff_results[diff_results.size() / 2] << endl;

  memset(check_num, -1, sizeof(check_num));
  int test_num = min(1000000/all_results.size(), diff_results.size());
  auto first = choose_one(all_results, diff_results, test_num);

  string first_ret;
  cout << "first return value(i.e. 0010201, 2 represent correct place, 1 represent in another place): " << endl;
  cin >> first_ret;
  while (first_ret.size() != squares) {
    cout << "wrong format! first return value: " << endl;
    cin >> first_ret;
  }
  auto filtered_results = filter(all_results, first, first_ret);
  cout << "remaining expressions num: " << filtered_results.size() << endl;
  // cout << "example: " << filtered_results[filtered_results.size()/2] << endl;

  while (true) {
    auto choose = choose_one(filtered_results, all_results, all_results.size());
    cout << "return value: " << endl;
    string ret;
    cin >> ret;
    while (ret.size() != squares) {
      cout << "wrong format! return value: " << endl;
      cin >> ret;
    }
    filtered_results = filter(filtered_results, choose, ret);
    cout << "remaining expressions num: " << filtered_results.size() << endl;
    // cout << "example: " << filtered_results[filtered_results.size()/2] << endl;
  }
}
