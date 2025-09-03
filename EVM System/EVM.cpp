#include <bits/stdc++.h>
using namespace std;

// ------------------- Structures -------------------
struct User {
    string username;
    string passwordHash; // store hashed password
    bool hasVoted;
};

struct Candidate {
    string name;
    int votes;
};

// ------------------- Global Storage -------------------
unordered_map<string, User> users;
vector<Candidate> candidates = {
    {"Candidate-1", 0},
    {"Candidate-2", 0},
    {"Candidate-3", 0}
};

// ------------------- Utility Functions -------------------

// Simple hashing for passwords (not cryptographically strong, but better than plain text)
string hashPassword(const string &password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Save users to file
void saveUsers() {
    ofstream fout("users.txt");
    for (auto &p : users) {
        fout << p.second.username << " " << p.second.passwordHash << " " << p.second.hasVoted << "\n";
    }
    fout.close();
}

// Load users from file
void loadUsers() {
    ifstream fin("users.txt");
    if (!fin.is_open()) return;
    string uname, pass;
    bool voted;
    while (fin >> uname >> pass >> voted) {
        users[uname] = {uname, pass, voted};
    }
    fin.close();
}

// Save votes to file
void saveVotes() {
    ofstream fout("votes.txt");
    for (auto &c : candidates) {
        fout << c.name << " " << c.votes << "\n";
    }
    fout.close();
}

// Load votes from file
void loadVotes() {
    ifstream fin("votes.txt");
    if (!fin.is_open()) return;
    string name;
    int v;
    int i = 0;
    while (fin >> name >> v && i < candidates.size()) {
        candidates[i].votes = v;
        i++;
    }
    fin.close();
}

// ------------------- Core Functions -------------------

void registerUser() {
    string username, password;
    cout << "Enter username (no spaces): ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) == users.end()) {
        users[username] = {username, hashPassword(password), false};
        saveUsers();
        cout << "User registered successfully!\n";
    } else {
        cout << "Username already exists. Try another.\n";
    }
}

bool authenticateUser(const string &username, const string &password) {
    return (users.find(username) != users.end() &&
            users[username].passwordHash == hashPassword(password));
}

void vote() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (authenticateUser(username, password)) {
        if (!users[username].hasVoted) {
            cout << "Candidates:\n";
            for (int i = 0; i < candidates.size(); i++) {
                cout << i + 1 << ". " << candidates[i].name << "\n";
            }
            int choice;
            cout << "Enter candidate number: ";
            cin >> choice;

            if (choice >= 1 && choice <= candidates.size()) {
                candidates[choice - 1].votes++;
                users[username].hasVoted = true;
                saveUsers();
                saveVotes();
                cout << "Vote cast successfully!\n";
            } else {
                cout << "Invalid choice.\n";
            }
        } else {
            cout << "You have already voted.\n";
        }
    } else {
        cout << "Authentication failed.\n";
    }
}

void displayResults() {
    cout << "\n---- Voting Results ----\n";
    for (auto &c : candidates) {
        cout << c.name << ": " << c.votes << " votes\n";
    }
}

// ------------------- Admin Functions -------------------

void adminMenu() {
    string password;
    cout << "Enter admin password: ";
    cin >> password;

    if (password != "admin123") { // default admin password
        cout << "Incorrect password.\n";
        return;
    }

    int choice;
    do {
        cout << "\n---- Admin Menu ----\n";
        cout << "1. View Results\n";
        cout << "2. Exit Admin Menu\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) displayResults();
    } while (choice != 2);
}

// ------------------- Main -------------------

int main() {
    loadUsers();
    loadVotes();

    int choice;
    do {
        cout << "\n========== Voting System ==========\n";
        cout << "1. Register\n";
        cout << "2. Vote\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            vote();
        } else if (choice == 3) {
            adminMenu();
        } else if (choice == 4) {
            cout << "Thank you for using the Voting System.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
