// Austin Cavanagh
// CIS-7 Online
// 11/06/24
// Course Project

#include <iostream>
#include <string>
using namespace std;

const string CHAR_STR = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&* ";

string displayMenu();
string getInput(string variableName);
bool isValidInput(const string &input);

string resizeKey(const string &key, size_t textLength);

char encryptChar(char decryptedTextChar, char keyTextChar);
char decryptChar(char encryptedTextChar, char keyTextChar);

int main() {
    // Declare variables to hold the key, plain text, and encrypted text
    string key;
    string encryptedText;
    string decryptedText;

    string menuSelection;
    
    // Loop through program until used selections option 3 to exit
    do {
        // Clear variables at the start of each iteration to avoid errors
        key.clear();
        encryptedText.clear();
        decryptedText.clear();
        
        // Display menu to the user
        menuSelection = displayMenu();
        
        // Handle encrypting a message
        if (menuSelection == "1") {
            decryptedText = getInput("Unencrypted Message");
            key = getInput("Key");
            key = resizeKey(key, decryptedText.length());
            
            for (size_t i = 0; i < decryptedText.length(); i++)
                encryptedText += encryptChar(decryptedText[i], key[i]);

            cout << "Encrypted Message: " << encryptedText << endl;
        }
        
        // Handle decrypting a message
        if (menuSelection == "2") {
            encryptedText = getInput("Encrypted Message");
            key = getInput("Key");
            key = resizeKey(key, encryptedText.length());
            
            for (size_t i = 0; i < encryptedText.length(); i++)
                decryptedText += decryptChar(encryptedText[i], key[i]);

            cout << "Decrypted Message: " << decryptedText << endl;
        }
    } while (menuSelection != "3");
    
    return 0;
}



// Function resizes key to match the length of the text is is translating
string resizeKey(const string &key, size_t textLength) {
    // Declare variables for the new key and the old key length
    string newKey;
    size_t keyLength = key.size();
    
    // Build the new key to be the same length as the text we are translating
    for (size_t i = 0; i < textLength; i++)
        newKey += key[i % keyLength];
    
    // Return new key
    return newKey;
}




// Function displays menu to user and collects menu selection
string displayMenu() {
    string input;
    bool validInput = false;
    
    cout << "Menu options" << endl;
    cout << "1) Encrypt Message" << endl;
    cout << "2) Decrypt Message" << endl;
    cout << "3) Exit program" << endl;
    
    do {
        cout << "Select Option (1-3): ";
        getline(cin, input);
        
        if (input == "1" || input == "2" || input == "3")
            validInput = true;
        else
            cout << "Error" << endl;
    } while (!validInput);
    
    return input;
}

// Function collects inputs for keyText, decryptedText, and encryptedText
string getInput(string variableName) {
    // Declare variables for input and input validation
    string input;
    bool validInput = false;
    
    // Loop until user inputs a valid input
    do {
        cout << variableName << ": ";
        getline(cin, input);
        
        if (isValidInput(input))
            validInput = true;
        else
            cout << "Error" << endl;
    } while (!validInput);
    
    // Return input0
    return input;
}

// Function validates inputs for keyText, decryptedText, and encryptedText
bool isValidInput(const string &input) {
    // Return false for an empty input
    if (input.empty())
        return false;
    
    // Loop over input and validate each character is also in CHAR_STR
    for (char c : input) {
        // Return false if the char is not in CHAR_STR
        if (CHAR_STR.find(c) == string::npos)
            return false;
    }
    
    // Return true if all chars are in CHAR_STR
    return true;
}

// Function accepts the decryptedText char and keyText char and returns the encrypted char
string encryptChar(string decryptedText, string keyText) {
    string encryptedText = "";
    
    for (int i = 0; i < decryptedText.length(); i++) {
        // .find() searches for char in a string
        // returns index of char if found
        // returns string::npos if not found
        size_t decryptedTextIndex = CHAR_STR.find(decryptedText[i]);
        size_t keyTextIndex = CHAR_STR.find(keyText[i]);
        
        // Add keyTextIndex to decryptedTextIndex to find encryptedTextIndex
        // Perform modulo operation to avoid overflow
        size_t encryptedTextIndex = (decryptedTextIndex + keyTextIndex) % CHAR_STR.length();
        
        //
        encryptedText += CHAR_STR[encryptedTextIndex];
    }
    
    return encryptedText;
    
    
    // .find() searches for char in a string
    // returns index of char if found
    // returns string::npos if not found
    size_t decryptedTextIndex = CHAR_STR.find(decryptedTextChar);
    size_t keyTextIndex = CHAR_STR.find(keyTextChar);
    
    // Add keyTextIndex to decryptedTextIndex to find encryptedTextIndex
    // Perform modulo operation to avoid overflow
    size_t encryptedTextIndex = (decryptedTextIndex + keyTextIndex) % CHAR_STR.length();
    
    // Return new encrypted char
    return CHAR_STR[encryptedTextIndex];
}

// Function accepts the encryptedText char and keyText char and returns the decrypted char
char decryptChar(char encryptedTextChar, char keyTextChar) {
    // .find() searches for char in a string
    // returns index of char if found
    // returns string::npos if not found
    size_t encryptedTextIndex = CHAR_STR.find(encryptedTextChar);
    size_t keyTextIndex = CHAR_STR.find(keyTextChar);
    
    // Subtract keyTextIndex from encryptedTextIndex to find decryptedTextIndex
    // Perform modulo operation to avoid overflow
    size_t decryptedTextIndex = (encryptedTextIndex + CHAR_STR.length() - keyTextIndex) % CHAR_STR.length();
    
    // Return new decrypted char
    return CHAR_STR[decryptedTextIndex];
}
