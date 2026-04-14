#include <iostream>
using namespace std;
#include <string>
#include <queue>
#include <fstream>
#include <unordered_map>
template <class T>
struct HuffmanNode  //Node structure
{
    T data;
    int frq;
    HuffmanNode<T>* left, * right;
    HuffmanNode(T d, int f)
    {
        data = d;
        frq = f;
        left = right = NULL;
    }
};
template <class T>
struct Compare
{
    bool operator()(HuffmanNode<T>* a, HuffmanNode<T>* b)
    {
        return a->frq > b->frq; //for min heap
    }
};
template <class T>
class HuffmanTree
{
private:
    HuffmanNode<T>* root;
    unordered_map<T, string> huffmanCode; //for traversing tree and allot "0" and "1" codes
    void encode(HuffmanNode<T>* node, string str)
    {
        if (node == NULL)
        {
            return;
        }
        if (node->left == NULL && node->right == NULL)
        {
            huffmanCode[node->data] = str.empty() ? "0" : str;  //or leaf node save code to map
        }
        encode(node->left, str + "0"); //0 for left
        encode(node->right, str + "1"); //1 for right
    }
    void serializeTree(HuffmanNode<T>* node, string& out)
    {
        if (node == NULL)
        {
            return;
        }
        if (node->left == NULL && node->right == NULL)
        {
            out += '1'; out += node->data;
        } //leaf node
        else
        {
            out += '0'; //internal node
            serializeTree(node->left, out);
            serializeTree(node->right, out);
        }
    }
    HuffmanNode<T>* deserializeTree(const string& s, int& pos)
    {
        char marker = s[pos++];
        if (marker == '1') //leaf node
        {
            T data = s[pos++];
            return new HuffmanNode<T>(data, 0);
        }
        else //internal node
        {
            HuffmanNode<T>* node = new HuffmanNode<T>(T(), 0);
            node->left = deserializeTree(s, pos);
            node->right = deserializeTree(s, pos);
            return node;
        }
    }
    void buildTree(const string& text)
    {
        unordered_map<T, int> freq; //frequency map
        for (T ch : text)
        {
            freq[ch]++;
        } //count frequency
        priority_queue<HuffmanNode<T>*, vector<HuffmanNode<T>*>, Compare<T>> prQ; //min heap
        typename unordered_map<T, int>::iterator it;
        for (it = freq.begin(); it != freq.end(); ++it)
        {
            prQ.push(new HuffmanNode<T>(it->first, it->second));
        } //push nodes to heap
        while (prQ.size() > 1)
        {
            HuffmanNode<T>* left = prQ.top(); prQ.pop();
            HuffmanNode<T>* right = prQ.top(); prQ.pop();
            HuffmanNode<T>* internal = new HuffmanNode<T>(T(), left->frq + right->frq); //internal node
            internal->left = left;
            internal->right = right;
            prQ.push(internal); //push internal node back to heap
        }
        root = prQ.top(); //final tree root
        encode(root, ""); //generate codes
    }
public:
    HuffmanTree() { root = NULL; } //constructor
    void compress(const string& inputFile, const string& outputFile)
    {
        ifstream fin(inputFile.c_str());
        if (!fin)
        {
            cerr << "Error in opening input file" << endl;
            return;
        }
        string text((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));
        fin.close();
        buildTree(text); //build tree and generate codes
        string compressed = "";
        for (T ch : text)
        {
            compressed += huffmanCode[ch];
        } //compress text
        int padding = (8 - compressed.size() % 8) % 8; //calculate padding
        compressed.append(padding, '0'); //add padding
        string treeSer;
        serializeTree(root, treeSer);
        ofstream fout(outputFile.c_str(), ios::binary);
        int len = text.size();
        int treeLen = treeSer.size();
        char pad = (char)padding;
        fout.write((char*)&len, sizeof(len)); //write original length
        fout.write(&pad, 1); //write padding
        fout.write((char*)&treeLen, sizeof(treeLen)); //write tree length
        fout.write(treeSer.c_str(), treeLen); //write tree structure
        for (int i = 0; i < (int)compressed.size(); i += 8)
        {
            char byte = 0;
            for (int j = 0; j < 8; j++)
            {
                if (compressed[i + j] == '1')
                {
                    byte |= (1 << (7 - j));
                } //set bit
            }
            fout.put(byte); //write byte
        }
        fout.close();
        cout << "Compressed the file : " << inputFile << " to " << outputFile << endl;
        cout << "Original size : " << len << " bytes" << endl;
        cout << "Compressed size : " << compressed.size() / 8 << " bytes" << endl;
    }
    void decompress(const string& inputFile, const string& outputFile)
    {
        ifstream fin(inputFile.c_str(), ios::binary);
        if (!fin)
        {
            cerr << "Error opening input file!" << endl;
            return;
        }
        int len, treeLen;
        char pad;
        fin.read((char*)&len, sizeof(int)); //read original length
        fin.read(&pad, 1); //read padding
        fin.read((char*)&treeLen, sizeof(int)); //read tree length
        string treeSer(treeLen, '\0');
        fin.read(&treeSer[0], treeLen); //read tree structure
        int pos = 0;
        root = deserializeTree(treeSer, pos); //load tree structure
        string compressed = "";
        char byte;
        while (fin.get(byte))
        {
            for (int i = 7; i >= 0; i--)
            {
                compressed += ((byte >> i) & 1) ? '1' : '0';
            } //convert byte to bits
        }
        fin.close();
        if ((int)compressed.size() > (int)pad)
            compressed.resize(compressed.size() - pad); //remove padding bits
        string result = "";
        HuffmanNode<T>* current = root;
        for (char bit : compressed)
        {
            current = (bit == '0') ? current->left : current->right; //traverse tree
            if (current->left == NULL && current->right == NULL) //leaf node
            {
                result += current->data; //append data
                current = root; //reset to root
                if ((int)result.size() == len) //stop if original length reached
                {
                    break;
                }
            }
        }
        ofstream fout(outputFile.c_str());
        fout << result; //write decompressed text
        fout.close();
        cout << "Decompressed the file : " << inputFile << " to " << outputFile << endl;
        cout << "Decompressed size : " << result.size() << " bytes" << endl;
    }
};
int main() {
    string in = "input.txt";
    string com = "compressing.huf";
    string dec = "decompressing.txt";
    ofstream sample(in.c_str());
    sample << "Huffman coding is a data compression algorithm.\n"
        << "Shamin is a good girl.\n"
        << "NUST COLLEGE OF E&ME-RWP.";
    sample.close();
    HuffmanTree<char> ht;
    ht.compress(in, com);
    ht.decompress(com, dec);
    ifstream file1(in.c_str());
    ifstream file2(dec.c_str());
    string str1((istreambuf_iterator<char>(file1)), (istreambuf_iterator<char>()));
    string str2((istreambuf_iterator<char>(file2)), (istreambuf_iterator<char>()));
    if (str1 == str2) cout << "\nIntegrity Check : PASSED" << endl;
    else cout << "\nIntegrity Check : FAILED" << endl;
    return 0;
}