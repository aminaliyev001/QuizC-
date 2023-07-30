#pragma once
class Admin {
private:
    string pin;
    string username;
    string password;
    vector<Quiz*> quizes;
public:
    string getPin() const {
        return pin;
    }
    string getUsername() const {
        return username;
    }
    string getPassword() const {
        return password;
    }
    vector<Quiz*> getQuizes() const {
        return quizes;
    }
    void replaceQuiz(Quiz * newQ, int index){
        quizes[index] = newQ;
    }
    bool checkQuizIndex(int index) {
        try {
            quizes.at(index);
        } catch (const out_of_range& e) {
            return false;
        }
        return true;
    }
    void setPin(string data) {
        if(data.length() >= 5)
            pin = data;
        else throw invalid_argument("PIN length should be at least 5");
    }
    bool upperCase_Number(string str) {
        bool has_uppercase = false, has_number = false;
        for (char c : str) {
            if (isupper(c)) {
                has_uppercase = true;
            }
            if (isdigit(c)) {
                has_number = true;
            }
        }
        return (has_uppercase && has_number);
    }
    void setUsername(string data)  {
        if(data.length() > 0)
            this->username = data;
        else throw invalid_argument("Username cannot be empty");
    }
    void setPassword(string data) {
        if(data.length() > 0) {
            if(upperCase_Number(data)) {
                this->password = data;
            } else throw invalid_argument("Password should contain at least one upper case and one number");
        } else throw invalid_argument("Password cannot be empty");
    }
    void addQuiz(Quiz* _q) {
        quizes.push_back(_q);
    }
    Admin() = delete;
    Admin(string _pin,string _username, string _pass) {
        setPin(_pin);
        setUsername(_username);
        setPassword(_pass);
    }
    void displayQuizNames() {
        for(auto quiz : quizes) {
            cout << quiz->getName() << endl;
        }
    }
};
