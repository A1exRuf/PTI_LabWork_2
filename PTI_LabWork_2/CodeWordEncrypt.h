#define CODEWORDENCRYPTY_H
#ifdef CODEWORDENCRYPTY_H

#include <iostream>

using namespace std;

class CodeWordEncrypt
{
private:
	string text;
	string key;
public:
	CodeWordEncrypt(string text, string key);
	string encrypt();
};

#endif

