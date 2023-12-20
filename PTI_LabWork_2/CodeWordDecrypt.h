#pragma once

#include <iostream>

using namespace std;

class CodeWordDecrypt
{
private:
	string text;
	string key;
public:
	CodeWordDecrypt(string text, string key);
	string decrypt();
};