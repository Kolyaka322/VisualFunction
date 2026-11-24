#include <iostream>
#include <fstream>
#include <bitset>
#include <cctype>

class FileReader {
public:
    virtual ~FileReader() = default;

    
    virtual void Display(const char* path) const {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Помилка відкриття файлу: " << path << "\n";
            return;
        }

        std::cout << "[Звичайний текст] " << path << ":\n";
        char ch;
        while (file.get(ch)) {
            std::cout.put(ch);
        }
        std::cout << "\n";
    }
};

class AsciiFileReader : public FileReader {
public:
    void Display(const char* path) const override {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Помилка відкриття файлу: " << path << "\n";
            return;
        }

        std::cout << "[ASCII-коди] " << path << ":\n";
        char ch;
        while (file.get(ch)) {
            unsigned int code = static_cast<unsigned char>(ch);
            std::cout << code << " ";
        }
        std::cout << "\n";
    }
};

class BinaryFileReader : public FileReader {
public:
    void Display(const char* path) const override {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Помилка відкриття файлу: " << path << "\n";
            return;
        }

        std::cout << "[Двійковий вигляд] " << path << ":\n";
        char ch;
        while (file.get(ch)) {
            std::bitset<8> bits(static_cast<unsigned char>(ch));
            std::cout << bits << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    system("chcp 1251>null");
    const char* testPath = "sample.txt";
    {
        std::ofstream out(testPath);
        out << "Hi!";
    }

    FileReader baseReader;
    AsciiFileReader asciiReader;
    BinaryFileReader binaryReader;

    FileReader* readers[] = { &baseReader, &asciiReader, &binaryReader };

    for (FileReader* reader : readers) {
        reader->Display(testPath);
        std::cout << "-----------------------------\n";
    }

    return 0;
}
