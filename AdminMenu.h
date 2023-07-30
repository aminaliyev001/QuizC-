#pragma once
void update_quiz(int index);
void admin_menu();
void login();
void display_quiz(int index) {
    if(DB::signed_admin->checkQuizIndex(index)) {
        cout << endl;
        DB::signed_admin->getQuizes().at(index)->display();
    } else throw invalid_argument("Enter a valid index please ");
    cout << endl << endl << "Enter something to go back ";
    string sel;
    getline(cin,sel);
    admin_menu();
}
void show_quizes() {
    show_quiz:
    cout << endl;
    if(DB::signed_admin->getQuizes().size() > 0) {
        short count = 1;
        for(auto item:DB::signed_admin->getQuizes()) {
            cout << count << ". ";
            item->display_short();
            count+=1;
        }
        string sel;
        cout << "Enter which quiz to display or press enter to go back ";
        getline(cin,sel);
        if(sel.empty())
            admin_menu();
        else {
            try {
                display_quiz(stoi(sel)-1);
            } catch(exception &e) {
                system("cls");
                cout << e.what();
                goto show_quiz;
            }
        }
    }  else  {
        cout << "There are no quizes :(";
        cout << endl << "Enter smth to go back " << endl;
        string sel;
        getline(cin,sel);
        admin_menu();
    }
}
void add_quiz() {
    line_30:
    cout << endl;
    string quiz_name;
    cout << "Enter the quiz name: ";
    getline(cin,quiz_name);
    Quiz * newQuiz;
    try {
        DB::checkQuizName(quiz_name);
        newQuiz = new Quiz(quiz_name);
    } catch(exception &e) {
        system("cls");
        cout << e.what();
        goto line_30;
    }
    while(true){
        string question;
        string correct_answer;
        vector<string> variants;
        cout << endl << "Enter the question: ";
        getline(cin,question);
        cout << endl << "Enter the correct answer: ";
        getline(cin,correct_answer);
        
        short count = 1;
        cout << "And enter variants: (just press enter if you finished with adding)" << endl;
        line_53:
        while(true) {
            string wrong_v;
            cout << endl << count << ": ";
            getline(cin,wrong_v);
            if(wrong_v.empty()) {
                if(count == 1) {
                    cout << "You should at least add one variant" << endl;
                    goto line_53;
                }
                try {
                    newQuiz->addQuestion(question, variants, correct_answer);
                    break;
                }catch(exception &e) {
                    system("cls");
                    cout << e.what();
                    goto line_53;
                }
            }
            else variants.push_back(wrong_v);
            count+=1;
        }
        cout << endl << "Enter something to one more question or just press enter to finish adding the questions ";
        string sel;
        getline(cin,sel);
        if(sel.empty())
            break;
    }
    DB::signed_admin->addQuiz(newQuiz);
    admin_menu();
}
void saveToFile() {
    ofstream file(DB::admin_pin+".txt");
            if (file.is_open()) {
                for (auto item : DB::signed_admin->getQuizes()) {
                    file << item->getName() << '\n';
                    for(auto item2:item->getQuestions()) {
                        file << item2.first << '\n';
                        for(auto item3:item2.second->getVariants()) {
                            file << item3 << ",";
                        }
                        file << '\n';
                        file << item2.second->getAnswer() << '\n';
                    }
                    file << '\n';
                }
                file.close();
            }
};
void editQuiz() {
    edit_quiz:
    cout << endl;
    if(DB::signed_admin->getQuizes().size() > 0) {
        short count = 1;
        for(auto item:DB::signed_admin->getQuizes()) {
            cout << count << ". ";
            item->display_short();
            count+=1;
        }
        string sel;
        cout << "Enter which quiz to edit ";
        getline(cin,sel);
        if(DB::signed_admin->checkQuizIndex(stoi(sel)-1)) {
            update_quiz(stoi(sel)-1);
        } else {
            system("cls");
            goto edit_quiz;
        }
    }  else  {
        cout << "There are no quizes :(";
        cout << endl << "Enter smth to go back " << endl;
        string sel;
        getline(cin,sel);
        admin_menu();
    }
}
void update_quiz(int index) {
    update_quiz_label:
    Quiz * editQuiz = DB::signed_admin->getQuizes().at(index);
    string name;
    cout << "Name: (" << editQuiz->getName() << ") Enter press to not change this"  << endl;
    getline(cin,name);
    if(name.empty())
        name = editQuiz->getName();
    Quiz * newQ;
    try {
        DB::checkQuizName(name,editQuiz->getName());
        newQ = new Quiz(name);
    }catch(exception &e) {
        system("cls");
        cout << e.what();
        goto update_quiz_label;
    }
    short count = 1;
    for(auto item : editQuiz->getQuestions()){
        line_every_question:
        string question;
        string correct_answer;
        cout << "Question " << count << ". (" << item.first << ") Enter press to not change this ";
        cout << endl;
        getline(cin,question);
        
        
        short count2 = 1;
        vector<string> variants;
        for(auto item2 : item.second->getVariants()) {
            string variant_string;
            cout << "Variant " << count2 << ". (" << item2 << ") Enter press to not change this ";
            getline(cin,variant_string);
            if(variant_string.empty())
                variants.push_back(item2);
            else variants.push_back(variant_string);
            count2+=1;
        }
        cout << "Correct answer: (" << item.second->getAnswer() << ") Enter press to not change this "  << endl;
        getline(cin,correct_answer);
        if(correct_answer.empty())
            correct_answer = item.second->getAnswer();
        if(question.empty())
            question = item.first;
        try{
            newQ->addQuestion(question, variants,correct_answer);
        }catch(exception &e) {
            system("cls");
            cout << e.what();
            goto line_every_question;
        }
        count+=1;
    }
    DB::signed_admin->replaceQuiz(newQ,index);
    admin_menu();
}
void admin_menu() {
    line_14:
    cout << "1. Create a quiz" << endl;
    cout << "2. Edit a quiz" << endl;
    cout << "3. My quizes" << endl; // show takers
    cout << "4. Leaderboard(Top 10)" << endl;
    cout << "5. Save to file" << endl;
    cout << "6. Sign out" << endl;
    string selection;
    getline(cin,selection);
    if(selection == "1") {
        add_quiz();
    }
    else if(selection == "2") {
        editQuiz();
    }
    else if(selection == "3") {
        show_quizes();
    }
    else if(selection == "4") {
        DB::getLeaderTop10(DB::signed_admin);
        cout << endl << endl;
        string as;
        cout << "Enter something to go back ";
        getline(cin,as);
        admin_menu();
    }
    else if(selection == "5") {
        saveToFile();
        system("cls");
        goto line_14;
    }
    else if(selection == "6") {
        DB::admin_pin = "";
        DB::signed_admin = NULL;
        login();
    }
    else {
        system("cls");
        cout << "You can choose only between 1-5" << endl;
        goto line_14;
    }
}
