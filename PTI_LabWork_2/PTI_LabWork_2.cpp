#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <Windows.h>
#include "CodeWordEncrypt.h"
#include "CodeWordDecrypt.h"

using namespace std;

string encryptVigenere(const string& plaintext, const string& key) {
    string ciphertext;
    int keyLength = key.length();

    for (int i = 0; i < plaintext.length(); i++) {
        char plainChar = plaintext[i];
        char keyChar = key[i % keyLength];

        char cipherChar;
        if (isalpha(plainChar)) {
            cipherChar = (plainChar + keyChar - 2 * 'A') % 26 + 'A';
        }
        else {
            cipherChar = plainChar;
        }
        ciphertext.push_back(cipherChar);
    }

    return ciphertext;
}

double calculateIndexOfCoincidence(const string& text) {
    unordered_map<char, int> charCount;
    int totalCount = 0;

    for (char ch : text) {
        if (isalpha(ch)) {
            charCount[ch]++;
            totalCount++;
        }
    }

    double indexOfCoincidence = 0.0;

    for (const auto& entry : charCount) {
        int count = entry.second;
        indexOfCoincidence += (count * (count - 1));
    }

    indexOfCoincidence /= (totalCount * (totalCount - 1));

    return indexOfCoincidence;
}

vector<string> kasiskiTest(const string& ciphertext, int keyLengthGuess) {
    unordered_map<string, vector<int>> substringMap;

    for (int i = 0; i < ciphertext.length() - keyLengthGuess + 1; i++) {
        string substring = ciphertext.substr(i, keyLengthGuess);
        if (substring.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
            continue;
        substringMap[substring].push_back(i);
    }

    vector<string> repeatedSubstrings;

    for (const auto& entry : substringMap) {
        const vector<int>& positions = entry.second;
        if (positions.size() > 1) {
            repeatedSubstrings.push_back(entry.first);
        }
    }

    return repeatedSubstrings;
}

string breakVigenere(const string& ciphertext, int keyLength) {
    string key;

    for (int i = 0; i < keyLength; i++) {
        string columnText;
        for (int j = i; j < ciphertext.length(); j += keyLength) {
            columnText.push_back(ciphertext[j]);
        }

        unordered_map<char, int> charCount;
        for (char ch : columnText) {
            if (isalpha(ch)) {
                charCount[ch]++;
            }
        }

        char mostFrequentChar;
        int maxCount = 0;

        for (const auto& entry : charCount) {
            char ch = entry.first;
            int count = entry.second;

            if (count > maxCount) {
                mostFrequentChar = ch;
                maxCount = count;
            }
        }

        int keyChar = (mostFrequentChar - 'E' + 26) % 26 + 'A';
        key.push_back(keyChar);
    }

    return key;
}

string decryptVigenere(const string& ciphertext, const string& key) {
    string plaintext;
    int keyLength = key.length();

    for (int i = 0; i < ciphertext.length(); i++) {
        char cipherChar = ciphertext[i];
        char keyChar = key[i % keyLength];

        char plainChar;
        if (isalpha(cipherChar)) {
            plainChar = (cipherChar - keyChar + 26) % 26 + 'A';
        }
        else {
            plainChar = cipherChar;
        }
        plaintext.push_back(plainChar);
    }

    return plaintext;
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string plaintext;
    string key;
    int choice;

    cout << " 1. Шифрование с использованием кодового слова; \n 2. Шифрование по методу Виженера.\n";
    cin >> choice;

    if (choice == 1)
    {
        string encrypted;
        string decrypted;

        cin.ignore();
        cout << "Введите исходный текст: ";
        getline(cin, plaintext);

        cin.ignore();
        cout << "Введите ключ шифрования: ";
        getline(cin, key);

        CodeWordEncrypt e(plaintext, key);
        encrypted = e.encrypt();

        CodeWordDecrypt d(encrypted, key);
        decrypted = d.decrypt();

        cout << "Зашифрованный текст: " << encrypted << endl;
        cout << "Расшифрованный текст: " << decrypted;
    }

    if (choice == 2)
    {
        cin.ignore();
        cout << "Введите исходный текст: ";
        getline(cin, plaintext);

        cin.ignore();
        cout << "Введите ключ шифрования: ";
        getline(cin, key);

        string ciphertext = encryptVigenere(plaintext, key);
        cout << "Зашифрованный текст: " << ciphertext << endl;

        cout << "Тест Касиски" << endl;
        vector<string> repeatedSubstrings = kasiskiTest(ciphertext, key.length());

        if (repeatedSubstrings.empty()) {
            cout << "Повторяющиеся подстроки не найдены." << endl;
        }
        else {
            cout << "Взлом ключа:" << endl;

            bool isOutputShown = false;

            for (const string& substring : repeatedSubstrings) {
                int keyLength = substring.length();
                string possibleKey = breakVigenere(ciphertext, keyLength);
                string decryptedText;
                for (int i = 0; i < ciphertext.length(); i++) {
                    char cipherChar = ciphertext[i];
                    char keyChar = possibleKey[i % keyLength];
                    char plainChar = (cipherChar - keyChar + 26) % 26 + 'A';
                    decryptedText.push_back(plainChar);
                }

                double indexOfCoincidence = calculateIndexOfCoincidence(decryptedText);

                if (!isOutputShown) {
                    cout << "Длина ключа: " << keyLength << ", Возможный ключ: " << possibleKey << endl;
                    isOutputShown = true;
                }
            }
        }
        cout << "Введите кодовое слово: ";
        cin >> key;
        cout << decryptVigenere(ciphertext, key);
    }
}