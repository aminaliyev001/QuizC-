#pragma once
class Answers {
private:
    vector<string> wrong_variants;
    string answer;
public:
    string getAnswer() const {
        return this->answer;
    }
    vector<string> getVariants() const {
        return this->wrong_variants;
    }
    void setAnswer(string _answer) {
        if(_answer.length()>0)
            this->answer = _answer;
            else throw invalid_argument("Correct answer cannot be empty");
    }
    void setVariants(vector<string> _var) {
        if(_var.size()>0)
            this->wrong_variants = _var;
        else throw invalid_argument("Wrong variant lists cannot be empty");
    }
    void addVariant(string _var) {
        if(_var.length()>0){
            wrong_variants.push_back(_var);
        } else throw invalid_argument("Variant cannot be empty");
    }
    void display_wrong_variants() const {
        for(auto item: wrong_variants) {
            cout << "- " << item << endl;
        }
    }
    void display_correct_answer() const {
        cout << endl << "Correct answer: " << getAnswer();
    }
    Answers() = delete;
    Answers(vector<string> _variants, string _answer) {
        setVariants(_variants);
        setAnswer(_answer);
    }
};
