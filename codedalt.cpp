#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bitset>

void encodeAndWriteToFile(const std::unordered_map<char, std::string>& codes, std::ofstream& outFile) {
    char byte = 0; // To store current one starting with 0
    int bitCount = 0; // count no of bits being written

    for (const auto& pair : codes) {
        const std::string& code = pair.second;

        for (char bit : code) {
            if (bitCount == 8) {
                outFile.put(byte); // Write completed to file
                byte = 0; // Reset byte
                bitCount = 0; // Reset bit count
            }

            byte <<= 1; // Shift left by 1 for new bit
            byte |= bit - '0'; // Add the new bit to the byte
            ++bitCount; // Increment the bit count
        }
    }

    if (bitCount > 0) {
        // Handle any remaining bits in the last byte
        byte <<= (8 - bitCount);
        outFile.put(byte);
    }
}

int main() {
    std::ifstream inFile("clear.txt");
    std::ofstream outFile("codedalt.txt", std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    std::ifstream codeTableFile("codetable.txt");

    if (!codeTableFile.is_open()) {
        std::cerr << "Error opening code table file!" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::string> codes;

    std::string line;
    while (std::getline(codeTableFile, line)) {
        std::istringstream iss(line);
        std::string character;
        std::string code;

        if (iss >> character >> code) {
            if (character == "LF") {
                character = "\n";
            } else if (character == "SP") {
                character = " ";
            }
            codes[character] = code;
        }
    }

    codeTableFile.close();

    encodeAndWriteToFile(codes, outFile);

    inFile.close();
    outFile.close();

    return 0;
}