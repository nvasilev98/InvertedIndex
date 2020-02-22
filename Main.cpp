#include <iostream>
#include "dirent.h"
#include "listoperations.h"
#include<vector>
#include <fstream>
#include <stack>
#include <sstream>
#include <string>
#include <list>
#include<iterator>
using namespace std;


struct LLWord {
	string word;
	list<int> idx;
	LLWord(string word, list<int> idx) {
		this->word = word;
		this->idx = idx;

	}

};
void removeDup(vector<LLWord>& vec) {
	auto it = vec.begin();
	while (it != vec.end()) {
		it->idx.unique();
		it++;
	}

}
bool ifUpper(char symbol) {
	return (symbol >= 'A' && symbol <= 'Z');
}
void ToLowerCase(string& symbol) {
	for (int i = 0; i < symbol.size(); i++) {
		if (ifUpper(symbol[i])) {
			symbol[i] = char(((int)symbol[i]) + 32);
		}
	}
}
int binary_search(vector<LLWord> a, int first, int last, string x) {
	int mid;
	while (first < last) {
		mid = (first + last) / 2;
		if (a[mid].word == x)
			return mid;
		else if (a[mid].word > x)
			last = mid - 1;
		else
			first = mid + 1;
	}
	if (first == a.size())
		return a.size();
	else if (a[first].word > x)
		return first;
	else
		return first + 1;
}
int FindWordBS(vector<LLWord> a, int first, int last, string x) {
	int mid;
	while (first < last) {
		mid = (first + last) / 2;
		if (a[mid].word == x)
			return mid;
		else if (a[mid].word > x)
			last = mid - 1;
		else
			first = mid + 1;
	}
	return -1;
}
bool isOperation(char c)
{
	return c == '+' || c == '-' || c == '*';
}


bool isSymbol(char c)
{
	return c >= 'a' && c <= 'z';
}
list<int> FindWordIDXS(string& word, vector<LLWord> lst) {
	list<int> a;
	auto it = lst.begin();
	while (it != lst.end()) {
		if (it->word == word) {
			return it->idx;
		}
		it++;
	}
	return a;
}

int getWeight(char c)
{
	switch (c)
	{
	case '*':
		return 2;
	case '+': case '-':
		return 1;
	default:
		return 100;
	}
}


int main() {
	//zad1;
	string dr = "D:\\HW\\";
	DIR *dir;
	dirent *ent;
	dir = opendir(dr.c_str());
	ent = readdir(dir);


	vector <LLWord> lst;
	list<int> idxx;


	int curr = 0;
	vector<string> titles;
	while (ent) {

		if (ent->d_name[0] != '.') {
			titles.push_back(ent->d_name);
		}
		ent = readdir(dir);
	}

	//zad2;

	auto iter = titles.cbegin();
	while (iter != titles.cend()) {
		list<int> idxs;
		string word;
		string FileName = dr + *iter;
		cout << *iter << ": ";
		ifstream fin(FileName, ios::in);
		while (!fin.eof()) {
			fin >> word;
			ToLowerCase(word);
			idxs.push_back(curr);
			LLWord  elem(word, idxs);
			int check = 0;
			auto it = lst.begin();
			while (it != lst.end()) {
				if (it->word == elem.word) {
					check++;
				}
				it++;
			}
			if (lst.empty()) {

				lst.push_back(elem);
			}
			else if (!lst.empty() && check != 0) {

				auto it1 = lst.begin();
				while (it1 != lst.end()) {
					if (it1->word == elem.word) {

						it1->idx.push_back(curr);

					}
					it1++;
				}

			}
			else {

				int pos = binary_search(lst, 0, lst.size(), elem.word);

				auto it2 = lst.begin();
				while (it2 != lst.end() && pos != 0) {
					it2++;
					pos--;
				}

				lst.insert(it2, elem);

			}
			removeDup(lst);
			cout << word << ", ";

		}
		cout << endl;
		fin.close();
		curr++;
		iter++;
	}


	auto needle = lst.begin();
	while (needle != lst.end()) {
		cout << needle->word << ": ";
		auto n = needle->idx.begin();
		while (n != needle->idx.end()) {
			cout << *n << ",";
			n++;
		}
		cout << endl;
		needle++;
	}
	//zad3
	string content;
	cout << "Insert a word: " << endl;
	cin >> content;
	cout << content << ": ";
	int WordPos = FindWordBS(lst, 0, lst.size(), content);
	if (WordPos == -1) {
		cout << "No result found!" << endl;
	}
	else {
		auto iterat = lst[WordPos].idx.begin();
		while (iterat != lst[WordPos].idx.end()) {
			cout << titles[*iterat] << ", ";
			iterat++;
		}
		cout << endl;
	}
	//zad4;
	string str;
	while (getline(cin, str)) {
		string firstWord;
		list<int> first;
		list<int> second;
		char op;
		stack<char> st;
		istringstream expr(str);
		stack<list<int>> rpn;
		while (!expr.eof()) {
			char next = expr.peek();
			if (isOperation(next)) {
				expr >> op;

				while (!st.empty() && st.top() != '(' && getWeight(st.top()) >= getWeight(op))
				{
					char op2 = st.top();
					second = rpn.top();
					rpn.pop();
					first = rpn.top();
					rpn.pop();
					switch (op2)
					{
					case '+': rpn.push(first + second); break;
					case '*': rpn.push(first * second); break;
					case '-': rpn.push(first - second); break;

					}
					st.pop();
				}

				st.push(op);
			}
			else if (isSymbol(next))
			{
				expr >> firstWord;
				rpn.push(FindWordIDXS(firstWord, lst));

			}
			else if (next == '(')
			{
				expr.ignore();
				st.push('(');
			}
			else if (next == ')')
			{
				expr.ignore();
				while (st.top() != '(')
				{
					op = st.top();
					second = rpn.top();
					rpn.pop();
					first = rpn.top();
					rpn.pop();
					switch (op)
					{
					case '+': rpn.push(first + second); break;
					case '*': rpn.push(first * second); break;
					case '-': rpn.push(first - second); break;
					}
					st.pop();
				}

				st.pop();
			}
			else
			{

				expr.ignore();
			}

		}

		while (!st.empty()) {
			op = st.top();
			second = rpn.top();
			rpn.pop();
			first = rpn.top();
			rpn.pop();
			switch (op)
			{
			case '+': rpn.push(first + second); break;
			case '*': rpn.push(first * second); break;
			case '-': rpn.push(first - second); break;
			}
			st.pop();
		}

		if (!rpn.empty()) {
			list<int> fin = rpn.top();
			if (fin.empty()) {
				cout << "no result found";
			}
			else {
				cout << str << ": ";
				auto ItRPN = fin.begin();
				while (ItRPN != fin.end()) {
					cout << titles[*ItRPN] << ", ";
					ItRPN++;
				}
			}
			cout << endl;
		}
		cout << "input queries: " << endl;
	};




	system("pause");

	return 0;
}