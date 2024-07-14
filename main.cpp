#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <bitset>
#include <string>
#include <sstream>

using namespace std;

class BinaryTreeNode {
public:
    char value;
    int frequency;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(char value, int frequency) {
        this->value = value;
        this->frequency = frequency;
        this->left = nullptr;
        this->right = nullptr;
    }
};

struct Compare {
    bool operator()(BinaryTreeNode* left, BinaryTreeNode* right) {
        return left->frequency > right->frequency;
    }
};

class HuffmanCode {
private:
    unordered_map<char, string> codes;
    unordered_map<string, char> reverseCodes;
    BinaryTreeNode* root;

    void buildFrequencyTable(const string& text, unordered_map<char, int>& frequency) {
        for (char ch : text) {
            frequency[ch]++;
        }
    }

    void buildHeap(const unordered_map<char, int>& frequency, priority_queue<BinaryTreeNode*, vector<BinaryTreeNode*>, Compare>& minHeap) {
        for (const auto& pair : frequency) {
            minHeap.push(new BinaryTreeNode(pair.first, pair.second));
        }
    }

    void buildBinaryTree(priority_queue<BinaryTreeNode*, vector<BinaryTreeNode*>, Compare>& minHeap) {
        while (minHeap.size() > 1) {
            BinaryTreeNode* left = minHeap.top();
            minHeap.pop();
            BinaryTreeNode* right = minHeap.top();
            minHeap.pop();

            int sum = left->frequency + right->frequency;
            BinaryTreeNode* newNode = new BinaryTreeNode('\0', sum);
            newNode->left = left;
            newNode->right = right;

            minHeap.push(newNode);
        }
        root = minHeap.top();
    }

    void buildCodes(BinaryTreeNode* node, const string& str) {
        if (!node) return;

        if (node->value != '\0') {
            codes[node->value] = str;
            reverseCodes[str] = node->value;
        }

        buildCodes(node->left, str + "0");
        buildCodes(node->right, str + "1");
    }

    string getEncodedText(const string& text) {
        string encodedText;
        for (char ch : text) {
            encodedText += codes[ch];
        }
        return encodedText;
    }

    string getPaddedEncodedText(const string& encodedText) {
        int extraPadding = 8 - (encodedText.size() % 8);
        string paddingInfo = bitset<8>(extraPadding).to_string();
        string paddedEncodedText = paddingInfo + encodedText;
        for (int i = 0; i < extraPadding; ++i) {
            paddedEncodedText += "0";
        }
        return paddedEncodedText;
    }

    vector<uint8_t> getByteArray(const string& paddedEncodedText) {
        vector<uint8_t> byteArray;
        for (size_t i = 0; i < paddedEncodedText.size(); i += 8) {
            string byteString = paddedEncodedText.substr(i, 8);
            uint8_t byte = bitset<8>(byteString).to_ulong();
            byteArray.push_back(byte);
        }
        return byteArray;
    }

    string removePadding(const string& bitString) {
        string paddingInfo = bitString.substr(0, 8);
        int extraPadding = bitset<8>(paddingInfo).to_ulong();
        return bitString.substr(8, bitString.size() - 8 - extraPadding);
    }

    string decodeText(const string& bitString) {
        string decodedText;
        string currentBits;
        for (char bit : bitString) {
            currentBits += bit;
            if (reverseCodes.find(currentBits) != reverseCodes.end()) {
                decodedText += reverseCodes[currentBits];
                currentBits = "";
            }
        }
        return decodedText;
    }

public:
    HuffmanCode() {
        root = nullptr;
    }

    string compress(const string& inputPath) {
        ifstream inputFile(inputPath, ios::in);
        stringstream buffer;
        buffer << inputFile.rdbuf();
        string text = buffer.str();
        inputFile.close();

        unordered_map<char, int> frequency;
        buildFrequencyTable(text, frequency);

        priority_queue<BinaryTreeNode*, vector<BinaryTreeNode*>, Compare> minHeap;
        buildHeap(frequency, minHeap);

        buildBinaryTree(minHeap);
        buildCodes(root, "");

        string encodedText = getEncodedText(text);
        string paddedEncodedText = getPaddedEncodedText(encodedText);
        vector<uint8_t> byteArray = getByteArray(paddedEncodedText);

        string outputPath = inputPath.substr(0, inputPath.find_last_of(".")) + ".bin";
        ofstream outputFile(outputPath, ios::out | ios::binary);
        for (uint8_t byte : byteArray) {
            outputFile << byte;
        }
        outputFile.close();

        return outputPath;
    }

    void decompress(const string& inputPath) {
        ifstream inputFile(inputPath, ios::in | ios::binary);
        stringstream buffer;
        buffer << inputFile.rdbuf();
        string bitString;
        for (char byte : buffer.str()) {
            bitString += bitset<8>(byte).to_string();
        }
        inputFile.close();

        string actualText = removePadding(bitString);
        string decodedText = decodeText(actualText);

        string outputPath = inputPath.substr(0, inputPath.find_last_of(".")) + "_decompressed.txt";
        ofstream outputFile(outputPath, ios::out);
        outputFile << decodedText;
        outputFile.close();
    }
};

int main() {
    string path;
    cout << "ENTER THE PATH OF YOUR FILE: ";
    cin >> path;

    HuffmanCode huffman;
    string outputPath = huffman.compress(path);
    huffman.decompress(outputPath);

    return 0;
}
