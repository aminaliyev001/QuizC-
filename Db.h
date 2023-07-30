#pragma once
namespace DB {
static bool admin_read = false;
static bool guest_read = false;
string generatePin() {
    return to_string(rand() % 1000000 + 1);
}
static Guest * guest;
static string admin_pin = "";
vector<Admin*> admins;
vector<Quiz *> quizes;
static Admin* signed_admin;
class Result {
private:
    string user_name;
    string quiz_name;
    int score;

public:

    Result(const string& user_name, const string& quiz_name, int score)
        : user_name(user_name), quiz_name(quiz_name), score(score) {}

    string getUserName() const {
        return user_name;
    }

    void setUserName( string user_name) {
        this->user_name = user_name;
    }

    string getQuizName() const {
        return quiz_name;
    }

    void setQuizName(string quiz_name) {
        this->quiz_name = quiz_name;
    }

    int getScore() const {
        return score;
    }

    void setScore(int score) {
        this->score = score;
    }

    bool operator<(const Result& other) const {
        return score < other.score;
    }
};

void saveAdminsToFile() {
    ofstream file("admins.txt");
    if (file.is_open()) {
        for (auto item : admins) {
            file << item->getPin() << " " << item->getUsername() << " " << item->getPassword() << "\n";
        }
        file.close();
    }
}
void addAdmins() {
    if(admins.empty()) {
        admins.push_back(new Admin(generatePin(),"Amin","Amin2007."));
        admins.push_back(new Admin(generatePin(),"Cavid","Cavid2023"));
        saveAdminsToFile();
    }
}
void readAdmins() {
    ifstream file("admins.txt");
    if(file.is_open()) {
            string pin;
            string name;
            string password;
            while (getline(file, pin, ' ') && getline(file, name, ' ') &&
                   getline(file, password,'\n')) {
                
                admins.push_back(new Admin(pin,name,password));
            }
            file.close();
    }
}
bool checkQuizName(string name) {
    for(auto admin:admins) {
        for(auto quiz:admin->getQuizes()){
            if(quiz->getName() == name)
                throw invalid_argument("Bu adda Quiz artig movcuddr");
        }
    }
    return true;
}
bool checkQuizName(string name, string name_exist) {
    for(auto admin:admins) {
        for(auto quiz:admin->getQuizes()){
            if(quiz->getName() == name && name != name_exist)
                throw invalid_argument("Bu adda Quiz artig movcuddr");
        }
    }
    return true;
}
bool resultCompare(Result& r1, Result& r2) {
    return r1.getScore() > r2.getScore();
}
void getLeaderTop10() {
    ifstream file("results.txt");
    if(file.is_open()) {
        string name;
        string quiz_name;
        string result;
        vector<Result> results;
        while (getline(file, name, ' ') && getline(file, quiz_name, ' ') &&
               getline(file, result,'\n')) {
            results.push_back(Result(name,quiz_name,stoi(result)));
        }
        sort(results.begin(), results.end(), resultCompare);
        short count = 1;
        for(auto result:results){
            if(count == 11)
                break;
            cout << count << ". User: " << result.getUserName() << " | Quiz: " << result.getQuizName() << " | Score: " << result.getScore() << "%" << endl;
            count+=1;
        }
        
        file.close();
    }
};
void getLeaderTop10(Admin * admin) {
    ifstream file("results.txt");
    if(file.is_open()) {
        string name;
        string quiz_name;
        string result;
        vector<Result> results;
        while (getline(file, name, ' ') && getline(file, quiz_name, ' ') &&
               getline(file, result,'\n')) {
            for(auto quiz : admin->getQuizes()) {
                if(quiz->getName() == quiz_name)
                    results.push_back(Result(name,quiz_name,stoi(result)));
            }
            
        }
        sort(results.begin(), results.end(), resultCompare);
        short count = 1;
        for(auto result:results){
            if(count == 11)
                break;
            cout << count << ". User: " << result.getUserName() << " | Quiz: " << result.getQuizName() << " | Score: " << result.getScore() << "%" << endl;
            count+=1;
        }
        
        file.close();
    }
}
void readQuizes() {
    ifstream file(admin_pin + ".txt");
    string line;
    if (file.is_open()) {
        string quiz_name;
        while (getline(file, quiz_name)) {
            if (quiz_name.empty()) continue;

            Quiz * newQ = new Quiz(quiz_name);
            string question;
            string variants;
            string correct_answer;
            while (getline(file, question)) {
                if (question.empty()) break;

                getline(file, variants);
                getline(file, correct_answer);

                vector<string> wrong_variants;
                stringstream s(variants);
                string item;
                while (getline(s, item, ',')) {
                    wrong_variants.push_back(item);
                }
                newQ->addQuestion(question, wrong_variants, correct_answer);
            }
            signed_admin->addQuiz(newQ);
        }
        file.close();
    }
}


void readQuizByAdmin(Admin *& admin) {
    ifstream file(admin->getPin()+".txt");
    string line;
    if (file.is_open()) {
        string quiz_name;
        while (getline(file, quiz_name)) {
            if (quiz_name.empty()) continue;

            Quiz * newQ = new Quiz(quiz_name);
            string question;
            string variants;
            string correct_answer;
            while (getline(file, question)) {
                if (question.empty()) break;

                getline(file, variants);
                getline(file, correct_answer);

                vector<string> wrong_variants;
                stringstream s(variants);
                string item;
                while (getline(s, item, ',')) {
                    wrong_variants.push_back(item);
                }
                newQ->addQuestion(question, wrong_variants, correct_answer);
            }
            admin->addQuiz(newQ);
        }
        file.close();
    }
    
}
void readAllQuizes() {
    for(auto & admin : admins) {
        readQuizByAdmin(admin);
    }
}
string loginAuth(string username, string pass) {
    for(auto &item :  admins) {
        if(item->getUsername() == username && item->getPassword() == pass) {
                signed_admin = item;
                return item->getPin();
        }
    }
    throw invalid_argument("Password/Username is not correct");
}
};

