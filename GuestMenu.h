#pragma once
void display_guest_menu();
map<char,string> displayVariants(vector<string> wrong_v, string correct_v) {
        vector<string> variants = wrong_v;
        variants.push_back(correct_v);
        random_device rd;
        mt19937 g(rd());
        shuffle(variants.begin(), variants.end(), g);
        map <char, string>c_answer;
        char option = 'a';
        for (auto& variant : variants) {
            c_answer[option] = variant;
            cout << option << ") " << variant << "\t";
            option+=1;
        }
    return c_answer;
}
void display_button() {
    cout << "1. Previous" << endl;
    cout << "2. Next" << endl;
    cout << "3. Submit" << endl;
}
int answer_of_question(int question_n,string sel, map<char,string> variants) {
    if(sel == "1" || sel == "2" || sel == "3") {
        if(sel == "1") {
            return 1;
        } else if(sel == "2") {
            return 2;
        } else return 3;
        
    } else if(sel.length() == 1) {
        for(auto it = variants.begin(); it != variants.end(); it++) {
            if(it->first == char(sel[0]))
            {
                DB::guest->answer_the_question(question_n, it->second);
                return 4;
            }
        }
    }
    return 0;
}
void saveRecord(Guest * guest,Quiz * quiz_main, int correct_ans) {
        ofstream file("results.txt",ios::app);
        if (file.is_open()) {
            double result = static_cast<double>(correct_ans)/quiz_main->getQuestions().size();
            file << guest->getName() << " " << quiz_main->getName() << " " << round(result*100) << '\n';
            file.close();
        }
}
void endQuiz(Quiz * quiz_main) {
    short question_no = 1;
    short correct_ans = 0;
    for(auto question : quiz_main->getQuestions()) {
        if(question.second->getAnswer() == DB::guest->getAnswerAtQ(question_no)){
            correct_ans+=1;
        }
            question_no+=1;
    }
    
    system("cls");
    cout << "QUIZ ENDED" << endl;
    cout << "Total questions: " << quiz_main->getQuestions().size() << endl;
    cout << "Answered questions: " << DB::guest->answered_question_count() << endl;
    cout << "Correct answers: " << correct_ans << endl;
    saveRecord(DB::guest, quiz_main, correct_ans);
    
    
    cout << endl << endl;
    cout << "Enter something to go back " << endl;
    string sp;
    getline(cin,sp);
    display_guest_menu();
}
void startQuiz(Quiz * quiz_main) {
    cout << endl << "Starting the quiz ... " << quiz_main->getName() << endl;
    this_thread::sleep_for(chrono::seconds(1));
    int count_question = 1;
    auto questions = quiz_main->getQuestions();
    for(auto question = questions.begin(); question != questions.end(); ++question) {
        question_label:
        cout << "Question " << count_question << ". " << question->first << endl << endl;
        map<char,string> variants = displayVariants(question->second->getVariants(),question->second->getAnswer());
        cout << endl << endl;
        display_button();
        answer_label:
        string selection_question;
        getline(cin,selection_question);
        
        int return_answer = answer_of_question(count_question,selection_question,variants);
        
        if(return_answer == 0) {
            cout << "Enter a number between 1-3 or letter to answer the question ..." << endl;
            goto question_label;
        }
        else if(return_answer == 1) {
            if(question->first != quiz_main->getQuestions().begin()->first){
                count_question-=1;
                --question;
                goto question_label;
            } else {
                display_guest_menu();
                break;
            }
        }
        else if(return_answer == 2) {
            if(question->first != prev(quiz_main->getQuestions().end())->first){
                ++question;
                count_question+=1;
                goto question_label;
            } else {
                break;
            }
            goto question_label;
        }
        else if(return_answer == 3) {
            break;
        }
        else if(return_answer == 4)
        {
            count_question+=1;
            continue;
        }
            
    }
    
    endQuiz(quiz_main);
}

Quiz * quizExist(int index){
    short count = 1;
    for(auto admin : DB::admins) {
        for(auto item : admin->getQuizes()) {
            if(index == count)
                return item;
            count+=1;
        }
    }
    return NULL;
}
void selection_guest(string sel) {
    if(sel == "0") {
        delete DB::guest;
        DB::guest = NULL;
        system("cls");
        login();
    } else if(sel == "1") {
        selection_guest_1:
        system("cls");
        cout << endl;
        short count = 1;
        for(auto admin : DB::admins) {
            for(auto item : admin->getQuizes()) {
                cout << count << ". ";
                item->display_short();
                count+=1;
            }
        }
        count = 1;
        string quiz_selection;
        getline(cin,quiz_selection);
        Quiz * quiz_m;
        quiz_m = quizExist(stoi(quiz_selection));
        if(quiz_m == NULL)
            goto selection_guest_1;
        else startQuiz(quiz_m);
        
    } else if(sel == "2") {
        DB::getLeaderTop10();
        cout << endl << endl;
        string sa;
        cout << "Enter something to go back ";
        getline(cin,sa);
        display_guest_menu();
    } else {
        throw invalid_argument("Choose between 0-2 ");
    }
}

void display_guest_menu() {
    system("cls");
    guest_menu_label:
    cout << endl;
    cout << "1. Choose and start a quiz" << endl;
    cout << "2. LeaderBoard(Top 10)" << endl;
    cout << "0. Exit" << endl;
    string selection;
    getline(cin,selection);
    
    try {
        selection_guest(selection);
    } catch(exception &e) {
        system("cls");
        cout << e.what();
        goto guest_menu_label;
    }
}
