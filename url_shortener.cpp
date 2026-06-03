#include <iostream>
#include <unordered_map>
using namespace std;

class URLShortener {
private:
    unordered_map<string, string> shortToLong;
    int counter = 0;

public:
    string generateShortCode() {
      counter++;
      return "url" + to_string(counter);
    }

    string shortenURL(const string& longURL) {
        string shortCode = generateShortCode();
        shortToLong[shortCode] = longURL;
        return shortCode;
    }

    string getOriginalURL(const string& shortCode) {
        if (shortToLong.find(shortCode) != shortToLong.end()) {
            return shortToLong[shortCode];
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