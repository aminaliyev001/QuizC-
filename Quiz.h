#pragma once
class Quiz {
private:
    string name;
    map<string, Answers*> questions;
public:
    string getName() const {
        return this->name;
    }
    map<string, Answers*> getQuestions() const {
        return this->questions;
    }
    void setName(string _name) {
        if(_name.length() > 0)
        this->name = _name;
        else throw invalid_argument("Quiz's name cannot be empty");
    }
    bool questionExists(string _question) {
        for(auto item: questions){
            if(item.first == _question)
                return true;
        }
        return false;
    }
    void addQuestion(string _ques, vector<string> wrong_variants, string correct_answer) {
        if(questionExists(_ques)) {
            throw invalid_argument("The same questions exists, please enter another question");
        }
        if(_ques.length() == 0) {
            throw invalid_argument("Question text cannot be empty");
        }
        if(_ques.size() == 0) {
            throw invalid_argument("Variants of the question cannot be empty");
        }
        if(correct_answer.length() == 0) {
            throw invalid_argument("Correct answer cannot be empty");
        }
        questions[_ques] = new Answers(wrong_variants,correct_answer);
    }
    void display_short() const {
        cout << getName()<<endl;
    }
    void display() const {
        display_short();
        cout << endl;
        short count = 1;
        for(auto item: questions) {
            cout << "Question " << count << ". " << item.first << endl;
            cout << "Variants: " << endl;
            item.second->display_wrong_variants();
            item.second->display_correct_answer();
            count+=1;
        }
    }
    Quiz() = delete;
    Quiz(string _name) {
        setName(_name);
    }
};
