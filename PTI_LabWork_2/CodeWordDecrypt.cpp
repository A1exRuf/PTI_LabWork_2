#include "CodeWordDecrypt.h"

CodeWordDecrypt::CodeWordDecrypt(string text, string key)
{
    this->text = text;
    this->key = key;
}

string CodeWordDecrypt::decrypt()
{
    string textDectypted;
    string alphabet = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
    string alphabetdecrypted = alphabet;

    for (int i = 0; i < key.length(); i++) {
        int index = alphabetdecrypted.find(key[i]);
        if (index != string::npos) {
            alphabetdecrypted.erase(index, 1);
        }
    }

    alphabetdecrypted = key + alphabetdecrypted;

    for (int i = 0; i < text.length(); i++) {
        char chr = text[i];
        int j = alphabetdecrypted.find(chr);
        if (j != string::npos) {
            chr = alphabet[j];
        }
        textDectypted.push_back(chr);
    }

    return textDectypted;
}