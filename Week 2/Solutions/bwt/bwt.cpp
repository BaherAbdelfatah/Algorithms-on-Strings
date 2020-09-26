#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void rotate(std::string &a) {
    char t = a[a.length() - 1];
    for (int i = a.length() - 1; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = t;
}

string BWT(string& text) {
  string result = "";
  vector<string> M_text;
  for(int i=0;i<text.length();i++)
  {
	  rotate(text);
	  M_text.push_back(text);
  }
  std::sort(M_text.begin(), M_text.end());
   for(int i=0;i<text.length();i++)
  {
	  result+=M_text[i][text.length()-1];
  }
  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}