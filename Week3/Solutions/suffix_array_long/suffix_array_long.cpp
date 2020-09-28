#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
using namespace std;

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.

vector<int> SortCharacters(string S)
{
	vector<int> order(S.length());
	map<char,int> count;
	count.emplace('$',0);
	count.emplace('A',0);
	count.emplace('C',0);
	count.emplace('G',0);
	count.emplace('T',0);
	
	for(int i=0;i<=S.length()-1;i++)
	{
		count[S[i]]=count[S[i]]+1;
	}
	string temp="$ACGT";
	for(int j=1;j<=5-1;j++)
		count[temp[j]]=count[temp[j]]+count[temp[j-1]];
	for(int i=S.length()-1;i>=0;i--)
	{
		char c = S[i];
		count[c]=count[c]-1;
		order[count[c]]=i;
	}
	return order;
}
vector<int> ComputeCharClasses(string S,vector<int> &order)
{
	vector<int> Class(S.length());
	Class[order[0]]=0;
	for(int i=1;i<=S.length()-1;i++)
	{
		if(S[order[i]]!=S[order[i-1]])
			Class[order[i]]=Class[order[i-1]]+1;
		else
			Class[order[i]]=Class[order[i-1]];
	}
	return Class;
}
vector<int> SortDoubled(string S,int L,vector<int>& order,vector<int>& Class)
{
	vector<int> count(S.length(),0);
	vector<int> newOrder(S.length(),0);
	for(int i=0;i<=S.length()-1;i++)
		count[Class[i]]=count[Class[i]]+1;
	for(int j=1;j<=S.length()-1;j++)
		count[j]=count[j]+count[j-1];
	for(int i=S.length()-1;i>=0;i--)
	{
		int start = (order[i]-L+S.length())%S.length();
		int cl=Class[start];
		count[cl]=count[cl]-1;
		newOrder[count[cl]]=start;
	}
	return newOrder;
}

vector<int> UpdateClasses(vector<int> &newOrder,vector<int>& Class,int L)
{
	int n=newOrder.size();
	vector<int> newClass(n);
	newClass[newOrder[0]]=0;
	for(int i=1;i<=n-1;i++)
	{
		int cur =newOrder[i];
		int prev=newOrder[i-1];
		int mid=(cur+L)%n;
		int midPrev=(prev+L)%n;
		if((Class[cur]!=Class[prev])||(Class[mid]!=Class[midPrev]))
		{
			newClass[cur]=newClass[prev]+1;
		}
		else
			newClass[cur]=newClass[prev];
	}
	return newClass;
}

vector<int> BuildSuffixArray(const string& text) {
  // Implement this function yourself
  vector<int> order=SortCharacters(text);
  vector<int> Class=ComputeCharClasses(text,order);
  int L=1;
  while(L<text.length())
  {
	  order=SortDoubled(text,L,order,Class);
	  Class=UpdateClasses(order,Class,L);
	  L=2*L;
  }
  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}