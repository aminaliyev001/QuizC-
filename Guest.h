#pragma once
class Guest {
private:
    string name;
    map<int, string> question_answer;
    string quiz_taken;
public:
    string getName() const {
        return name;
    }
    void setName(string _name) {
        name = _name;
    }
    string getQuizName() const {
        return quiz_taken;
    }
    void setQuizTaken(string _q_t) {
        quiz_taken = _q_t;
    }
    void endTheQuiz() {
        question_answer.clear();
        quiz_taken = "";
    }
    Guest(string _name) {
        setName(_name);
    }
    void answer_the_question(int q, string answer) {
        question_answer[q] = answer;
    }
    string getAnswerAtQ(int q_number){
            auto it = question_answer.find(q_number);
            if (it != question_answer.end()) {
                return it->second;
            } else {
                return "";
            }
    }
    int answered_question_count() const {
        return question_answer.size();
    }
};
