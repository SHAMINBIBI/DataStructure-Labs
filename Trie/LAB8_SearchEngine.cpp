#include<iostream>
#include<list>
#include<unordered_map>
#include<string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <conio.h> // Required for _getch() : captures key instantly without waiting for Enter 

/**conio.h is a header file in C and C++ that provides console input/output functions.
 It is commonly used in Windows environments for tasks such as capturing keyboard input without waiting for the Enter key, 
 manipulating the console screen**/

using namespace std;

template <class T>
struct trieNode {
    unordered_map <T, trieNode<T>*>m;
    bool flag;
    trieNode() { flag = false; }
};

template <class T>
class trie {
    trieNode<T>* root;
public:
    trie() { root = new trieNode<T>(); }

    // Helper to convert string to vector<T> , needed to work with template 
    vector<T> toVec(string s) {
        return vector<T>(s.begin(), s.end());
    }

    void insertTrie(string word) { 
        trieNode<T>* temp = root;
        vector<T> v = toVec(word);
        for (int i = 0; i < v.size(); i++) {
            if (temp->m.find(v[i]) == temp->m.end()) {
                temp->m[v[i]] = new trieNode<T>();
            }
            temp = temp->m[v[i]];
        }
        temp->flag = true;
    }

    bool searchPrefix(string word) {
        trieNode<T>* temp = root;
        vector<T> v = toVec(word);
        for (int i = 0; i < v.size(); i++) {
            if (temp->m.find(v[i]) == temp->m.end()) return false;
            temp = temp->m[v[i]];
        }
        return true;
    }

    bool search(string word) {
        trieNode<T>* temp = root;
        vector<T> v = toVec(word);
        for (int i = 0; i < v.size(); i++) {
            if (temp->m.find(v[i]) == temp->m.end()) return false;
            temp = temp->m[v[i]];
        }
        return temp->flag;
    }

    void deleteWord(string word) {
        trieNode<T>* temp = root;
        vector<T> v = toVec(word);
        for (int i = 0; i < v.size(); i++) {
            if (temp->m.find(v[i]) == temp->m.end()) return;
            temp = temp->m[v[i]];
        }
        temp->flag = false;
    }

    void retrieveAllWords(vector<string>& allWords) {
        retrieveHelper(root, "", allWords);
    }

    void retrieveHelper(trieNode<T>* node, string curr, vector<string>& allWords) {
        if (node->flag) allWords.push_back(curr);
        typename unordered_map<T, trieNode<T>*>::iterator temp;
        for (temp = node->m.begin(); temp != node->m.end(); temp++) {
            retrieveHelper(temp->second, curr + temp->first, allWords);
        }
    }
	trieNode<T>* findNode(string prefix)
	{  trieNode<T> *temp = root;
		vector<T> v = toVec(prefix);  //cuz of tempate
		for (int i=0;i<v.size();i++)  
		{ if (temp->m.find(v[i]) == temp->m.end())
			{return NULL;}
			temp = temp->m[v[i]]; //follow the path of prefix in trie
		}
		return temp;  //jdr prefix khtm wo return
	}
	vector<string> getSuggestions(string prefix)
	{  vector<string> allMatches; 
		trieNode<T>* startNode = findNode(prefix);
		if(startNode!= NULL) //if prefix exists in trie
		{
			retrieveHelper(startNode,prefix,allMatches); //retrieve all words starting with prefix
		}
		 // Return only the first 3 matches
    sort(allMatches.begin(), allMatches.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });
    vector<string> top3;
    for (int i = 0; i < allMatches.size() && i < 3; i++) {
        top3.push_back(allMatches[i]);
    }
    return top3;
	}
	string toLower(string s) //helper to convert string to lowercase
	{  for (int i=0;i<s.size();i++)
	{  s[i] = tolower(s[i]); }
		return s;
	}
    
};
int main() {
    trie<char> t;
    ifstream file("C:/Users/khawa/OneDrive/Desktop/4TH SEM/DS/LAB/MANUALS/Lab 8 Helper File words.txt");
    string word;
    
    if (file.is_open()) {
        while (file >> word) t.insertTrie(t.toLower(word));
        file.close();
    }
    string prefix = "";
    char ch;    
    cout << "Start typing (Press Enter to stop): " << endl;
    while (true) {
        ch = _getch(); // Captures key instantly without Enter
        if (ch == 13) break; // Enter key to stop    
        if (ch == 8) { // Backspace key
            if (!prefix.empty()) prefix.pop_back();
        } else {
            prefix += tolower(ch);
        }
        cout << "Search: " << prefix << endl;
        cout << "Top 3 Suggestions:" << endl;     
        vector<string> suggestions = t.getSuggestions(t.toLower(prefix));
        if (suggestions.empty()) {
            cout << " (No matches found)" << endl;
        } else {
            for (int i = 0; i < suggestions.size(); i++) {
                cout << i + 1 << ". " << suggestions[i] << endl;
            }
        }
    }
    return 0;
}