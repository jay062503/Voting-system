#include <bits/stdc++.h>
using namespace std;

// Structures to store user and candidate data
struct User
{
    string username;
    string password;
    bool hasVoted;
};

struct Candidate
{
    string name;
    int votes;
};

// to store users and candidates
unordered_map<string, User> users;
vector<Candidate> candidates;

void registerUser();
void vote();
void displayResults();
bool authenticateUser(const string &username, const string &password);

int main()
{

    candidates.push_back({"candidate-1", 0});
    candidates.push_back({"candidate-2", 0});
    candidates.push_back({"candidate-3", 0});
    int choice;

    do {
        cout << "--------------------------------------------*************--------------------------------------------" << endl;
        cout << "1. Register" << endl;
        cout << "2. Vote" << endl;
        cout << "3. Display Results" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";

        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            vote();
        } else if (choice == 3) {
            displayResults();
        } else if (choice == 4) {
            cout << "Thank you !!" << endl;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

void registerUser()
{
    string username, password;
    cout << "Enter username without spaces: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) == users.end())
    {
        users[username] = {username, password, false};
        cout << "User registered successfully!\n";
    }
    else
    {
        cout << "Username already exists. Try a different username." << endl;
    }
}

bool authenticateUser(const string &username, const string &password)
{
    if (users.find(username) != users.end() && users[username].password == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void vote()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (authenticateUser(username, password))
    {
        if (!users[username].hasVoted)
        {
            cout << "Candidates:" <<endl;
            for (int i = 0; i < candidates.size(); ++i)
            {
                cout << i + 1 << ". " << candidates[i].name << endl;
            }
            int choice;
            cout << "Enter the number of the candidate you want to vote for: ";
            cin >> choice;

            if (choice > 0 && choice <= candidates.size())
            {
                candidates[choice - 1].votes++;
                users[username].hasVoted = true;
                cout << "Vote cast successfully!" << endl;
            }
            else
            {
                cout << "Invalid choice. Vote not cast." << endl;
            }
        }
        else
        {
            cout << "You have already voted." << endl;
        }
    }
    else
    {
        cout << "Authentication failed. Check your username and password." << endl;
    }
}

void displayResults()
{
    cout << "Voting Results:" << endl;
    for (const auto &candidate : candidates)
    {
        cout << candidate.name << ": " << candidate.votes << " votes" << endl;
    }
}
