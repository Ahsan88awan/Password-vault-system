#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// ================= PASSWORD ENTRY CLASS =================
class PasswordEntry {
private:
    string website;
    string username;
    string password;

public:
    // Constructor
    PasswordEntry(string w = "", string u = "", string p = "") {
        website = w;
        username = u;
        password = p;
    }

    // Getters
    string getWebsite() {
        return website;
    }

    string getUsername() {
        return username;
    }

    string getPassword() {
        return password;
    }

    // Setters
    void setUsername(string u) {
        username = u;
    }

    void setPassword(string p) {
        password = p;
    }

    // Display
    void display() {
        cout << "\nWebsite: " << website << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
    }

    // Convert into file format
    string toFileString() {
        return website + "," + username + "," + password;
    }
};

// ================= ABSTRACT CLASS =================
class UserManager {
public:
    virtual void addPassword() = 0;
    virtual void deletePassword() = 0;
    virtual void updatePassword() = 0;
    virtual void searchPassword() = 0;
    virtual void viewPasswords() = 0;
};

// ================= SECOND BASE CLASS =================
class Security {
protected:
    string loginPassword;

public:
    Security() {
    loginPassword = "Ahsan";
    }
bool login() {
    string pass;
    cout << "Enter Login Password: ";
    cin >> pass;
if (pass == loginPassword) {
    cout << "\nLogin Successful!\n";
    return true;
    }
    else {
    cout << "\nWrong Password!\n";
    return false;}
    }
void changeLoginPassword() {
    string oldPass, newPass;
    cout << "\nEnter Old Password: ";
    cin >> oldPass;
if (oldPass == loginPassword) {
    cout << "Enter New Password: ";
    cin >> newPass;

    loginPassword = newPass;
    cout << "\nLogin Password Changed Successfully!\n";
    }
    else {
        cout << "\nIncorrect Old Password.\n";}
    }
};

// ================= FILE HANDLER CLASS =================
class FileHandler {
public:

    // Save Data
static void saveToFile(vector<PasswordEntry>& entries) {
    ofstream file("vault.txt");
for (int i = 0; i < entries.size(); i++) {

    file << entries[i].toFileString() << endl;
    }

    file.close();
    }

    // Read File
static void readFile() {
    ifstream file("vault.txt");
    string line;

    cout << "\n===== FILE DATA =====\n";
while (getline(file, line)) {
    cout << line << endl;
    }
    file.close();
    }
};
// ================= DERIVED CLASS =================
// Multiple Inheritance Used Here
class PasswordVault : public UserManager, public Security {
private:
    vector<PasswordEntry> entries;
public:

    // Add Password
    void addPassword() {

string website, username, password;
    cout << "\nEnter Website Name: ";
    cin >> website;

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    PasswordEntry obj(website, username, password);

    entries.push_back(obj);

    FileHandler::saveToFile(entries);

    cout << "\nPassword Added Successfully!\n";
    }

    // Delete Password
void deletePassword() {

    string website;
    bool found = false;

    cout << "\nEnter Website to Delete: ";
    cin >> website;
for (int i = 0; i < entries.size(); i++) {
    if (entries[i].getWebsite() == website) {
        entries.erase(entries.begin() + i);
    FileHandler::saveToFile(entries);

    cout << "\nPassword Deleted Successfully!\n";

    found = true;
    break;
    }
}
if (!found) {
    cout << "\nWebsite Not Found.\n";
}
    }
// Update Password
    void updatePassword() {

    string website;
    bool found = false;

    cout << "\nEnter Website to Update: ";
    cin >> website;
for (int i = 0; i < entries.size(); i++) {
    if (entries[i].getWebsite() == website) {
        string newUser, newPass;

    cout << "Enter New Username: ";
    cin >> newUser;
                
	cout << "Enter New Password: ";
    cin >> newPass;

    entries[i].setUsername(newUser);
    entries[i].setPassword(newPass);

    FileHandler::saveToFile(entries);

    cout << "\nPassword Updated Successfully!\n";
    found = true;
    break;
}
    }
if (!found) {
    cout << "\nWebsite Not Found.\n";
    }
}
    // Search Password
void searchPassword() {

    string website;
    bool found = false;

    cout << "\nEnter Website to Search: ";
    cin >> website;

    for (int i = 0; i < entries.size(); i++) {

    if (entries[i].getWebsite() == website) {

    cout << "\nPassword Found:\n";

    entries[i].display();
    found = true;
    break;
    }
}
if (!found) {
    cout << "\nWebsite Not Found.\n";
}
    }

    // View Passwords
void viewPasswords() {
   if (entries.empty()) {
   cout << "\nNo Passwords Saved.\n";
    return;
    }

    cout << "\n===== SAVED PASSWORDS =====\n";

    for (int i = 0; i < entries.size(); i++) {

    cout << "\nEntry " << i + 1 << endl;

    entries[i].display();
        }
    }

    // Main Menu
void menu() {
    int choice;
do {
    cout << "\n====== PASSWORD VAULT SYSTEM ======\n";
    cout << "1. Add Password\n";
    cout << "2. Delete Password\n";
    cout << "3. Update Password\n";
    cout << "4. Search Password\n";
    cout << "5. View Passwords\n";
    cout << "6. Change Login Password\n";
    cout << "7. View File Data\n";
    cout << "8. Exit\n";
    cout << "\nEnter Choice: ";
    cin >> choice;

switch (choice) {

    case 1:
        addPassword();
        break;
    case 2:
        deletePassword();
        break;

    case 3:
        updatePassword();
        break;

    case 4:
        searchPassword();
        break;

    case 5:
        viewPasswords();
        break;

    case 6:
        changeLoginPassword();
        break;

    case 7:
        FileHandler::readFile();
        break;

    case 8:
        cout << "\nExiting Program...\n";
        break;
default:
    cout << "\nInvalid Choice.\n";
    }
} while (choice != 8);
  }
   };

// ================= MAIN FUNCTION =================
int main() {

    PasswordVault obj;

    // Login System
    if (obj.login()) {
    obj.menu();
    }
return 0;
}
