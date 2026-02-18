#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

// Declaring the assembly XOR function
extern "C" void crypto(char* data, size_t length, char key);

// Function to XOR a single file using the crypto(asm) function
void encryptDecryptFile(const string &filePath, char key) {
    ifstream inputFile(filePath, ios::binary);
    if (!inputFile.is_open()) {
        cout << "Error: Could not open file for reading: " << filePath << endl;
        return;
    }

    // Get file size
    inputFile.seekg(0, ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    // Reserve memory to hold the file data
    vector<char> buffer(fileSize);
    inputFile.read(buffer.data(), fileSize);
    inputFile.close();

    // Call the assembly function to XOR on the buffer
    crypto(buffer.data(), fileSize, key);

    // Write the XORed content back to the file
    ofstream outputFile(filePath, ios::binary);
    if (!outputFile.is_open()) {
        cout << "Error: Could not open file for writing: " << endl;
        return;
    }

    outputFile.write(buffer.data(), fileSize);
    outputFile.close();
    cout << "Encryption/Decryption complete: " << endl;
}

// Function to recursively XOR all files in a directory
void encryptDecryptDirectory(const string &dirPath, char key) {
    fs::path dir(dirPath);
    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        cout << "Error: Invalid directory path: " << endl;
        return;
    }

    for (auto &entry : fs::recursive_directory_iterator(dir)) {
        if (fs::is_regular_file(entry.status())) {
            cout << "\nProcessing file: " << entry.path() << endl;
            encryptDecryptFile(entry.path().string(), key);
        }
    }
}

int main() {
    string directoryPath = "/home/hacker/";
    char key = 'A';

    // Ask user for the directory path and key for encryption (if needed)
    // cout << "Enter the directory to encrypt/decrypt: ";
    // cin >> directoryPath;
    // cout << "Enter the cryption key (single character): ";
    // cin >> key;

    // Call the function
    encryptDecryptDirectory(directoryPath, key);

    return 0;
}
