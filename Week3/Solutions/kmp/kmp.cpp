#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

vector<int> ComputePrefixFunction(string P)
{
	vector<int> s(P.length());
	s[0]=0;
	int border=0;
	for(int i=1;i<P.length();i++)
	{
		while((border>0)&&(P[i]!=P[border]))
			border=s[border-1];
		if(P[i]==P[border])
			border=border+1;
		else
			border=0;
		s[i]=border;
	}
	return s;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
  vector<int> result;
  // Implement this function yourself
  string S=pattern+"$"+text;
  vector<int> s=ComputePrefixFunction(S);
  for(int i=pattern.length()+1;i<S.length();i++)
	  if(s[i]==pattern.length())
		  result.push_back(i-2*pattern.length());
  return result;
}

int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}