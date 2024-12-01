#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

using Dictionary = unordered_map<string, string>;

void skipSpaces(const string& input, int& position) {
    while (position < input.length() && isspace(input[position])) {
        position++;
    }
}

bool readString(const string& input, int& position, string& result) {
    if (input[position] != '"') {
        return false; 
    }
    position++; 
    while (position < input.length() && input[position] != '"') {
        result += input[position];
        position++;
    }
    if (position >= input.length() || input[position] != '"') {
        return false; 
    }
    position++; 
    return true;
}


bool readDictionary(const string& input, int& position, Dictionary& result) {
    if (input[position] != '{') {
        return false; 
    }
    position++; 

    while (position < input.length()) {
        skipSpaces(input, position);

        
        if (input[position] == '}') {
            position++; 
            return true;
        }

        
        string key;
        if (!readString(input, position, key)) {
            return false;
        }

        skipSpaces(input, position);

        
        if (input[position] != ':') {
            return false;
        }
        position++; 
        skipSpaces(input, position);

        
        string value;
        if (!readString(input, position, value)) {
            return false;
        }

        result[key] = value;

        skipSpaces(input, position);

        
        if (input[position] == ',') {
            position++;
        } else if (input[position] == '}') {
            continue; 
        } else {
            return false;
        }
    }

    return false; 
}

int main() {
    cout << "Enter a JSON: \n";
    string userInput;
    getline(cin, userInput); 

    int position = 0;
    Dictionary data;

    if (readDictionary(userInput, position, data)) {
        cout << "\nYour Data:\n";
      for (const auto& pair : data) {
    cout << pair.first << ": " << pair.second << endl;
    }
    } else {
        cout << "Error: Invalid JSON format.\n";
    }

    return 0;
}
