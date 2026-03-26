#include <iostream> 
#include <filesystem> 
#include <fstream> 
#include <string> 
 
using namespace std; 
 
namespace fs = std::filesystem; 
 
void loadDirectory(const fs::path& directoryPath) { 
    if (!fs::is_directory(directoryPath)) { 
        cout << "Error: Not a valid directory path." << endl; 
        return; 
    } 
 
    cout << "Loading directory: " << directoryPath <<endl; 
    for (const auto& entry : fs::directory_iterator{ directoryPath }) { 
        fs::path entryPath = entry.path(); 
        cout << "Found entry: " << entryPath.filename() << endl; 
 
        // Check if it is a regular file and process it 
        if (fs::is_regular_file(entryPath)) { 
            cout << "  -> It's a file. Opening for reading..." << endl; 
            ifstream file(entryPath); 
            if (file.is_open()) { 
                string line; 
                while (getline(file, line)) { 
                    // Process file content here 
                } 
                file.close(); // Important to close the file a er use 
            } 
            else { 
                cout << "  -> Error opening file: " << entryPath << endl; 
            } 
        } 
        // Check if it is a subdirectory and recurse (if needed) 
        else if (fs::is_directory(entryPath)) { 
            cout << "  -> It's a directory." << endl; 
            // Op onally, call loadDirectory(entryPath) for recursive loading 
        } 
} 
} 
int main() { 
// Specify the path to the directory you want to load 
// "." refers to the current working directory 
// "path/to/your/directory" for a specific path 
loadDirectory("."); 
return 0; 
} 