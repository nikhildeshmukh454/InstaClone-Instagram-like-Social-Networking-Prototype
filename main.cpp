#include<iostream>
#include<string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

unordered_map<string, vector<string>> UserData;
unordered_map<string, bool> mailIds;
unordered_map<string, bool> userIds;
unordered_map<string, unordered_map<string, stack<string>>> messagesData;




string generatePassword(int length = 8) {
    const string upperCaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lowerCaseLetters = "abcdefghijklmnopqrstuvwxyz";
    const string digits = "0123456789";
    const string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    
    if (length < 8) {
        length = 8; // Ensure the minimum length is 8
    }

    vector<char> password;

    // Ensure at least one character from each category is included
    password.push_back(upperCaseLetters[rand() % upperCaseLetters.size()]);
    password.push_back(lowerCaseLetters[rand() % lowerCaseLetters.size()]);
    password.push_back(digits[rand() % digits.size()]);
    password.push_back(specialChars[rand() % specialChars.size()]);

    // Fill the remaining length of the password with random characters from all categories
    const string allChars = upperCaseLetters + lowerCaseLetters + digits + specialChars;
    for (int i = 4; i < length; ++i) {
        password.push_back(allChars[rand() % allChars.size()]);
    }

    // Shuffle the password to avoid a predictable pattern
    random_shuffle(password.begin(), password.end());

    return string(password.begin(), password.end());
}



bool validPassword(string& password)
{
    if (password.length() < 8) {
        return false; // Password length should be at least 8 characters
    }

    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    for (char ch : password) {
        if (isupper(ch)) {
            hasUpperCase = true;
        } else if (islower(ch)) {
            hasLowerCase = true;
        } else if (isdigit(ch)) {
            hasDigit = true;
        } else if (ispunct(ch)) { // Check for special characters
            hasSpecialChar = true;
        }
    }

    // Check if all required conditions are met
    return hasUpperCase && hasLowerCase && hasDigit && hasSpecialChar;
}


class Post {
public:
    string imgUrl;
    string caption;

    Post(string imgUrl, string caption = "") {
        this->imgUrl = imgUrl;
        this->caption = caption;
    }
};



class MyFeed {
private:
    vector<Post> feed;

public:
    void addToFeed(const Post& post) {
        feed.push_back(post);
    }

    void viewMyFeed() {
        cout << "My Feed:" << endl;
        for (auto& post : feed) {
            cout << post.imgUrl << " - " << post.caption << endl;
        }
    }
};

class User {
protected:
    string mailId;
    string password;

public:
    string userId;
    string bio;
    vector<string> posts;
    vector<User*> following;
    vector<User*> followers;
    string  profilePicture ;

    void createAccount(string mailId) {
        while (mailIds[mailId]) {
            cout << "This Mail Id Already Exists. Enter a new one: " << endl;
            cin >> mailId;
        }
        mailIds[mailId] = true;

      
        cout << "Do you want an auto-generated password? (y/n): ";
        char choice;
        cin >> choice;

        if (tolower(choice) == 'y') {
            password = generatePassword();
            cout << "Generated Password: " << password << endl;
        } else {
            cout << "Enter Your Password: " << endl;
            cin >> password;
            while (!validPassword(password)) {
                cout << "Enter a Stronger Password: " << endl;
                cin >> password;
            }
        }

        
        cout << "Enter User ID: " << endl;
        string newUserId;
        cin >> newUserId;
        while (userIds[newUserId]) {
            cout << "This User ID Already Exists. Enter a new one: " << endl;
            cin >> newUserId;
        }

        userId = newUserId;
        password = newPassword;
        this->mailId = mailId;

        UserData[userId] = { mailId, password, "" };
    }

    void deleteAccount(string userId, string password) {
        string mail;
        cout << "Enter Your Mail Id: " << endl;
        cin >> mail;
        if (UserData[userId][0] == mail && UserData[userId][1] == password) {
            UserData.erase(userId);
        } else {
            cout << "Incorrect password or mail id" << endl;
        }
    }

    void follow(User* userToFollow) {
        following.push_back(userToFollow);
        userToFollow->followers.push_back(this);
    }

    void unfollow(User* userToUnfollow) {
        following.erase(remove(following.begin(), following.end(), userToUnfollow), following.end());
        userToUnfollow->followers.erase(remove(userToUnfollow->followers.begin(), userToUnfollow->followers.end(), this), userToUnfollow->followers.end());
    }

    void showMyFollowing() {
        cout << "Following: ";
        for (auto& user : following) {
            cout << user->userId << " ";
        }
        cout << endl;
    }

    void showMyFollowers() {
        cout << "Followers: ";
        for (auto& user : followers) {
            cout << user->userId << " ";
        }
        cout << endl;
    }

    void sendMessage(string message, User& receiver) {
        messagesData[userId][receiver.userId].push(message);
        messagesData[receiver.userId][userId].push(message);
    }

    void postPhoto(string imgUrl, string caption = "") {
        posts.push_back(imgUrl);

        // Add this post to all followers' feeds
        for (auto& follower : followers) {
            follower->addToFeed(Post(imgUrl, caption));
        }
    }

    void addToFeed(const Post& post) {
        // To be implemented in MyFeed class
    }

     void editProfile(string newBio, string newProfilePicture) {
        bio = newBio;
        profilePicture = newProfilePicture;
        cout << "Profile updated successfully." << endl;
    }



    void showPreviousChats(string friendUserId, int n = -1) {
    if (messagesData[userId].find(friendUserId) == messagesData[userId].end()) {
        cout << "No previous chats with this user." << endl;
        return;
    }

    stack<string>& chatStack = messagesData[userId][friendUserId];

    if (n == -1 || n > chatStack.size()) {
        n = chatStack.size();
    }

    vector<string> messages;
    for (int i = 0; i < n; ++i) {
        messages.push_back(chatStack.top());
        chatStack.pop();
    }

    // Print messages in reverse order to maintain original sequence
    for (auto it = messages.rbegin(); it != messages.rend(); ++it) {
        cout << *it << endl;
    }

    // Push messages back to the stack
    for (const auto& message : messages) {
        chatStack.push(message);
    }
}


};

class Friend : public User {
public:
    void viewFriendDetails(User& friendUser) {
        // Check if the current user is following friendUser
        auto it = find(friendUser.followers.begin(), friendUser.followers.end(), this);
        if (it != friendUser.followers.end()) {
            cout << "UserID: " << friendUser.userId << endl;
            cout << "Bio: " << friendUser.bio << endl;
            cout << "Posts: " << endl;
            for (const auto& post : friendUser.posts) {
                cout << post << endl;
            }
            cout << "Following: " << friendUser.following.size() << endl;
            cout << "Followers: " << friendUser.followers.size() << endl;
        } else {
            cout << "You are not following this user." << endl;
        }
    }
};
