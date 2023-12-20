#include "CodeWordEncrypt.h"

CodeWordEncrypt::CodeWordEncrypt(string text, string key)
{
    this->text = text;
    this->key = key;
}

string CodeWordEncrypt::encrypt()
{
    string textEnctypted;
    string alphabet = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
    string alphabetEncrypted = alphabet;

    for (int i = 0; i < key.length(); i++) {
        int index = alphabetEncrypted.find(key[i]);
        if (index != string::npos) {
            alphabetEncrypted.erase(index, 1);
        }
    }

    alphabetEncrypted = key + alphabetEncrypted;
    
    for (int i = 0; i < text.length(); i++) {
        char chr = text[i];
        int j = alphabet.find(chr);
        if (j != string::npos) {
            chr = alphabetEncrypted[j];
        }
        textEnctypted.push_back(chr);
    }

    return textEnctypted;
}
