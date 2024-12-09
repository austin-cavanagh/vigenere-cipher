// Austin Cavanagh
// CIS-7 Online
// 12/08/24
// Course Project

#include <iostream>
#include <string>
using namespace std;

// Define constants
const string CHAR_STR = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&* ";
const string BUFFER = "==========================================";

// Define prototypes
string displayMenu();
void handleEncryption(string &, string &, string &);
void handleDecryption(string &, string &, string &);
string getInput(string );
bool isValidInput(const string &);
string resizeKey(const string &, size_t);
string encryptStr(string, string);
string decryptStr(string, string);
void displayEndMessage();

int main() {
    // Define variables
    string keyStr;
    string encryptedStr;
    string decryptedStr;
    string menuSelection;
    
    // Loop through program until used selections option 3 to exit
    do {
        // Clear variables at the start of each iteration to avoid errors
        keyStr.clear();
        encryptedStr.clear();
        decryptedStr.clear();
        
        // Display menu to the user
        menuSelection = displayMenu();
        
        // Handle encrypting a message
        if (menuSelection == "1") {
            handleEncryption(keyStr, encryptedStr, decryptedStr);
        }
        
        // Handle decrypting a message
        if (menuSelection == "2") {
            handleDecryption(keyStr, encryptedStr, decryptedStr);
        }
    } while (menuSelection != "3");
    
    // Display thank you message
    displayEndMessage();
    
    return 0;
}

// Function handles encryption logic
void handleEncryption(string &keyStr, string &encryptedStr, string &decryptedStr) {
    decryptedStr = getInput("Unencrypted Message");
    keyStr = getInput("Key");
    keyStr = resizeKey(keyStr, decryptedStr.length());
    encryptedStr = encryptStr(decryptedStr, keyStr);
    cout << BUFFER << endl;
    cout << "Encrypted Message: " << encryptedStr << endl;
}

// Function handles decryption logic
void handleDecryption(string &keyStr, string &encryptedStr, string &decryptedStr) {
    encryptedStr = getInput("Encrypted Message");
    keyStr = getInput("Key");
    keyStr = resizeKey(keyStr, encryptedStr.length());
    decryptedStr = decryptStr(encryptedStr, keyStr);
    cout << BUFFER << endl;
    cout << "Decrypted Message: " << decryptedStr << endl;
}

// Function displays menu to user and collects menu selection
string displayMenu() {
    string input;
    bool validInput = false;
    
    do {
        // Display menu options
        cout << BUFFER << endl;
        cout << "            ** Menu Options **            " << endl;
        cout << "1) Encrypt Message" << endl;
        cout << "2) Decrypt Message" << endl;
        cout << "3) Exit program" << endl << endl;
        cout << "Select Option (1-3): ";
        getline(cin, input);
        
        // Validate input and display error if invalid
        if (input == "1" || input == "2" || input == "3") {
            validInput = true;
        } else {
            cout << BUFFER << endl;
            cout << "     ** ERROR: Invalid menu option **     " << endl;
        }
    } while (!validInput);
    
    cout << BUFFER << endl;
    
    return input;
}

// Function collects inputs for keyStr, decryptedStr, and encryptedStr
string getInput(string variableName) {
    // Declare variables for input and input validation
    string input;
    bool validInput = false;
    
    // Loop until user inputs a valid input
    do {
        cout << variableName << ": ";
        getline(cin, input);
        
        // Check if input is valid
        if (isValidInput(input)) {
            validInput = true;
        } else {
            cout << BUFFER << endl;
            cout << "        ** ERROR: Invalid input **        " << endl;
            cout << BUFFER << endl;
        }
    } while (!validInput);
    
    // Return valid input
    return input;
}

// Function validates inputs for keyStr, decryptedStr, and encryptedStr
bool isValidInput(const string &input) {
    // Return false for an empty input
    if (input.empty()) {
        return false;
    }
    
    // Loop over input and validate that each character is in CHAR_STR
    for (char c : input) {
        // Return false if the character is not in CHAR_STR
        // .find() will return the index if the character is found
        // .find() will return string::npos if the character is not found
        if (CHAR_STR.find(c) == string::npos) {
            return false;
        }
    }
    
    // Return true if all chars are in CHAR_STR
    return true;
}

// Function resizes key to match the length of the string is is translating
string resizeKey(const string &key, size_t strLength) {
    // Declare variables for the new key and the old key length
    string newKey;
    size_t keyLength = key.size();
    
    // Build the new key to be the same length as the string we are translating
    for (size_t i = 0; i < strLength; i++) {
        // If the key is smaller than the string loop over and duplicate to match the length
        newKey += key[i % keyLength];
    }
    
    // Return new key
    return newKey;
}

// Function accepts decryptedStr and keyStr and returns the encrypted string
string encryptStr(string decryptedStr, string keyStr) {
    string encryptedStr = "";
    
    for (int i = 0; i < decryptedStr.length(); i++) {
        // .find() searches for char in a string
        // returns index of char if found
        // returns string::npos if not found
        size_t decryptedStrIndex = CHAR_STR.find(decryptedStr[i]);
        size_t keyStrIndex = CHAR_STR.find(keyStr[i]);
        
        // Add keyStrIndex to decryptedStrIndex to find encryptedStrIndex
        // Perform modulo operation to avoid overflow
        size_t encryptedStrIndex = (decryptedStrIndex + keyStrIndex) % CHAR_STR.length();
        
        // Add encrypted char to encryptedStr
        encryptedStr += CHAR_STR[encryptedStrIndex];
    }
    
    return encryptedStr;
}


// Function accepts encryptedStr and keyStr and returns the decrypted string
string decryptStr(string encryptedStr, string keyStr) {
    string decryptedStr = "";
    
    for (int i = 0; i < encryptedStr.length(); i++) {
        // .find() searches for char in a string
        // returns index of char if found
        // returns string::npos if not found
        size_t encryptedStrIndex = CHAR_STR.find(encryptedStr[i]);
        size_t keyStrIndex = CHAR_STR.find(keyStr[i]);
        
        // Subtract keyStrIndex from encryptedStrIndex to find decryptedStrIndex
        // Perform modulo operation to avoid overflow
        size_t decryptedStrIndex = (encryptedStrIndex + CHAR_STR.length() - keyStrIndex) % CHAR_STR.length();
        
        // Add decrypted char to decryptedStr
        decryptedStr += CHAR_STR[decryptedStrIndex];
    }

    return decryptedStr;
}

// Function displays end message to the user
void displayEndMessage() {
    cout << "Thank you for using the application today!" << endl;
    cout << BUFFER << endl;
}
