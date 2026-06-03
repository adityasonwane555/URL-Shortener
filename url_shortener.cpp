#include <iostream>
#include <unordered_map>
using namespace std;

class URLShortener {
private:
    unordered_map<string, string> shortToLong;
    unordered_map<string, string> longToShort;
    int counter = 0;

    bool isValidURL(const string& url) {
        if (url.empty()) return false;
        if (url.find(' ') != string::npos) return false;
        size_t dotPos = url.find('.');
        if (dotPos == string::npos || dotPos == 0 || dotPos == url.length() - 1) {
            return false;
        }
        return true;
    }

public:
    string generateShortCode() {
        counter++;
        int temp = counter;
        const string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string shortCode = "";
        while (temp > 0) {
            shortCode = chars[temp % 62] + shortCode;
            temp /= 62;
        }
        return shortCode;
    }

    string shortenURL(const string& longURL) {
        if (!isValidURL(longURL)) {
            return "Invalid URL";
        }
        auto it = longToShort.find(longURL);
        if (it != longToShort.end()) {
            return it->second;
        }
        string shortCode = generateShortCode();
        shortToLong[shortCode] = longURL;
        longToShort[longURL] = shortCode;
        return shortCode;
    }

    string getOriginalURL(const string& shortCode) {
        auto it = shortToLong.find(shortCode);
        if (it != shortToLong.end()) {
            return it->second;
        }
        return "Short code not found.";
    }
};

int main() {
    URLShortener shortener;

    string longURL;
    cout << "Enter URL: ";
    cin >> longURL;

    string shortCode = shortener.shortenURL(longURL);
    cout << "Shortened URL: short.ly/" <<shortCode << endl;

    cout << "Enter short code to retrieve: ";
    string code;
    cin >> code;

    cout << "Original URL: " << shortener.getOriginalURL(code) << endl;
    return 0;
}