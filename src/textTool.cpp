#include <string>
#include <vector>

using namespace std;

const string const delimiter = "\t";

char asciitolower(char c) { // finds lowercase of char if need
    if (c <= 'Z' && c >= 'A') // range of the uppercase
        return c + 32; // converts to uppercase
    return c;
}

string strToLower(string& str) { // converts string to lowercase
    for (int i = 0; i < str.size(); i++) { // cycles through each char
        str[i] = asciitolower(str[i]);
    }
    return str;
}

bool strInVec(string str, vector<string> v) {
    //str = str;// +delimiter;
    str = strToLower(str);
    for (int i = 0; i < v.size(); i++) {
        if (str == v[i]) {
            return true;
        }
    }
    return false;
}

bool isNumber(string str) {
    for (int i = 0; i < str.size(); i++)
    {
        //cout << i << " : {" << str[i] << "}\n";
        if (isdigit(str[i]) == 0) {
            return false;

        }
    }
    return true;
}

vector<string> strToVector(string str) {
    vector<string> v;

    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + delimiter.length());
        v.push_back(token);
    }
    return v;
}

void strCharSwap(string& str, const char c1, const char c2) {
    // This tool will parse though str and replace c1 with c2
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == c1) {
            str[i] = c2;
        }
    }
}
