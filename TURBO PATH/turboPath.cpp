#include <iostream>
#include <filesystem>
#include <string>
#include <queue>    
#include "AVL.h"    // templated AVL Tree for O(log n) search speed
using namespace std;
namespace fs = std::filesystem;
struct DirectoryNode {
    string folderName;
    DirectoryNode* parentDirectory;
    DirectoryNode* nextMemoryNode; 
};
struct FileNode {
    string fileName;           // Stores the name with extension (e.g report.pdf)
    DirectoryNode* parentDirectory;
    FileNode* nextDuplicate;    
    FileNode* nextMemoryNode;   // Background linked list 
};
class TurboPath {
private:
    // Key: string (File name used for search)
    // Value: FileNode* (Pointer to the actual data)
    AVL<string, FileNode*> fileSearchIndex;    
    // Tracking heads and tails for background " Linked Lists"
    DirectoryNode* memHeadDirs;
    DirectoryNode* memTailDirs;
    FileNode* memHeadFiles;
    FileNode* memTailFiles;
    int totalFilesIndexed;
    void clearAllMemory() {
        fileSearchIndex.clear(); // Clears the AVL tree nodes
        DirectoryNode* currDir = memHeadDirs;
        while (currDir != nullptr) {
            DirectoryNode* nextDir = currDir->nextMemoryNode;
            delete currDir;
            currDir = nextDir;
        }
        memHeadDirs = nullptr; memTailDirs = nullptr;
        FileNode* currFile = memHeadFiles;
        while (currFile != nullptr) {
            FileNode* nextFile = currFile->nextMemoryNode;
            delete currFile;
            currFile = nextFile;
        }
        memHeadFiles = nullptr; memTailFiles = nullptr;

        totalFilesIndexed = 0;
    }
    void addFileToIndex(string searchKey, string actualFullName, DirectoryNode* currentFolder) {
        // Create new node 
        FileNode* newFile = new FileNode{ actualFullName, currentFolder, nullptr, nullptr };
        if (memHeadFiles == nullptr) {
            memHeadFiles = newFile;
            memTailFiles = newFile;
        } else {
            memTailFiles->nextMemoryNode = newFile;
            memTailFiles = newFile;
        }
        // Search the AVL tree for this name 
        FileNode** existingDuplicateHead = fileSearchIndex.search(searchKey);
        if (existingDuplicateHead != nullptr) {
            newFile->nextDuplicate = *existingDuplicateHead;
            *existingDuplicateHead = newFile; 
        } else {
            fileSearchIndex.insert(searchKey, newFile);
        }
    }
public:
    TurboPath() {
        memHeadDirs = nullptr; memTailDirs = nullptr;
        memHeadFiles = nullptr; memTailFiles = nullptr;
        totalFilesIndexed = 0;
    }
    ~TurboPath() {
        clearAllMemory(); 
    }
    string buildAbsolutePath(FileNode* file) {
        string absolutePath = file->fileName; 
        DirectoryNode* currentFolder = file->parentDirectory;     
        while (currentFolder != nullptr) {
            // Check for root drives (C:/ or /) to avoid double slashes
            if (currentFolder->folderName == "C:\\" || currentFolder->folderName == "C:/" || currentFolder->folderName == "/") {
                absolutePath = currentFolder->folderName + absolutePath;
            } else {
                absolutePath = currentFolder->folderName + "\\" + absolutePath;
            }
            currentFolder = currentFolder->parentDirectory;
        }
        return absolutePath;
    }
    //   A Queue to perform Breadth-First Search (BFS)
    void indexDirectory(const string& rootPathString) {
        clearAllMemory(); 
        fs::path startPath(rootPathString);
        cout << "Turbo Path is indexing files into RAM.Please wait." << endl;
        // Create the directory node
        DirectoryNode* rootFolderNode = new DirectoryNode{ startPath.string(), nullptr, nullptr };
        memHeadDirs = rootFolderNode;
        memTailDirs = rootFolderNode;
        queue<pair<fs::path, DirectoryNode*>> traversalQueue;
        traversalQueue.push({startPath, rootFolderNode});

        while (!traversalQueue.empty()) {
            auto currentItem = traversalQueue.front();
            fs::path currentOsPath = currentItem.first;
            DirectoryNode* currentCustomFolder = currentItem.second;
            traversalQueue.pop();
            try {
                // Iterate through items in the directory using C++17 filesystem
                for (const auto& entry : fs::directory_iterator(currentOsPath)) {                   
                    if (fs::is_directory(entry.status())) {
                        // Found a sub-folder Create node and add to queue to explore later.
                        string folderName = entry.path().filename().string();
                        DirectoryNode* newFolder = new DirectoryNode{ folderName, currentCustomFolder, nullptr };                      
                        memTailDirs->nextMemoryNode = newFolder;
                        memTailDirs = newFolder;
                        traversalQueue.push({entry.path(), newFolder});
                    } 
                    else if (fs::is_regular_file(entry.status())) {
                        //  Found a file.
                        string fullName = entry.path().filename().string(); // e.g., report.pdf
                        string baseName = entry.path().stem().string();     // e.g., report
                        
                        //  Index the Full Name 
                        addFileToIndex(fullName, fullName, currentCustomFolder);

                        //  Index the base name separately
                        // This allows searching for "report" to find "report.pdf".
                        if (baseName != fullName) {
                            addFileToIndex(baseName, fullName, currentCustomFolder);
                        }

                        totalFilesIndexed++;
                    }
                }
            } catch (const exception& e) {
                continue; 
            }
        }
        cout << "Indexing is complete. TurboPath has indexed " << totalFilesIndexed << " files" << endl;
    }
    void searchFile(const string& targetFileName) {
        // fileSearchIndex.search returns a pointer to the FileNode* pointer in the tree
        FileNode** searchResult = fileSearchIndex.search(targetFileName);   
        if (searchResult != nullptr) {
            cout << "\nFound match(es) instantly:" << endl;        
            // Iterate through the linked list of files sharing this name
            FileNode* duplicateIterator = *searchResult;
            int matchCount = 0;
            while (duplicateIterator != nullptr) {
                // Reconstruct path to save space
                cout << " -> " << buildAbsolutePath(duplicateIterator) << endl;
                duplicateIterator = duplicateIterator->nextDuplicate;
                matchCount++;
            }
            cout << "(" << matchCount << " file(s) found)" << endl;
        } else {
            cout << "\nFile not found." << endl;
        }
    }
};
//  Encapsulates directory input and validation
string getValidDirectory() {
    string pathInput;
    while (true) {
        cout << "\nEnter the root directory path to index (e.g., . or C:/): ";
        getline(cin, pathInput);
        // Check for empty or whitespace inputs
        if (pathInput.empty() || pathInput.find_first_not_of(' ') == string::npos) {
            cout << "Input cannot be empty. Please try again." << endl;
            continue;
        }
               // Verify path actually exists on the hard drive
        if (fs::exists(pathInput) && fs::is_directory(pathInput)) {
            return pathInput; 
        } else {
            cout << "Error: Path does not exist or is not a directory. Please try again." << endl;
        }
    }
}
int main() {
    cout << "==============================================" << endl;
    cout << "      Welcome to Sham's Turbo-Path Search     " << endl;
    cout << "==============================================" << endl;
    TurboPath searchEngine;
    
    //  Get directory and build initial index
    string rootPathInput = getValidDirectory();
    searchEngine.indexDirectory(rootPathInput);

    string userQuery;
    while (true) {
        cout << "\nEnter file name (or 'refresh' to update, 'cd' to change directory, 'exit' to quit): ";
        getline(cin, userQuery);
        //  Input validation for search query
        if (userQuery.empty() || userQuery.find_first_not_of(' ') == string::npos) {
            cout << "Please enter a valid file name." << endl;
            continue;
        }

        if (userQuery == "exit") {
            break; // Closes program, destructor clears RAM
        }
        else if (userQuery == "refresh") {
            //  Re-scans current directory for new files
            searchEngine.indexDirectory(rootPathInput);
        }
        else if (userQuery == "cd") {
            rootPathInput = getValidDirectory();
            searchEngine.indexDirectory(rootPathInput);
        }
        else {
            searchEngine.searchFile(userQuery);
        }
    }
    return 0;
}