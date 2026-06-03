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
    int choice;
    string input;

    while (true) {
        cout << "\n=== URL Shortener Menu ===\n";
        cout << "1. Shorten URL\n";
        cout << "2. Retrieve Original URL\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        if (choice == 1) {
            cout << "Enter long URL: ";
            cin >> input;
            string shortCode = shortener.shortenURL(input);
            if (shortCode == "Invalid URL") {
                cout << "Error: The URL format is invalid.\n";
            } else {
                cout << "Shortened URL: short.ly/" << shortCode << "\n";
            }
        } else if (choice == 2) {
            cout << "Enter short code (or full shortened URL): ";
            cin >> input;
            size_t slashPos = input.find_last_of('/');
            string code = (slashPos == string::npos) ? input : input.substr(slashPos + 1);
            
            string originalURL = shortener.getOriginalURL(code);
            if (originalURL == "Short code not found.") {
                cout << "Error: " << originalURL << "\n";
            } else {
                cout << "Original URL: " << originalURL << "\n";
            }
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please choose 1, 2, or 3.\n";
        }
    }
    return 0;
}