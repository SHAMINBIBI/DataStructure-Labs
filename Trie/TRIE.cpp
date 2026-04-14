#include<iostream>
#include<list>
#include<unordered_map>
#include<string>
#include <vector>
#include <fstream>

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

    // Helper to convert string to vector<T>
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

