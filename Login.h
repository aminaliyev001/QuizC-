#pragma once
void login_guest() {
    cout << endl;
    string name;
    cout << "Enter your name to continue: ";
    getline(cin,name);
    if(name.length()>=3)
        DB::guest = new Guest(name);
    else throw invalid_argument("Name should have min 3 letters");
    if(DB::guest_read == false) {
        DB::readAllQuizes();
        DB::guest_read = true;
    }
    display_guest_menu();
}
void login_admin(){
    line_auth:
    cout << endl;
    string user;
    string pass;
    string pin_admin;
    cout << "Enter your username: ";
    getline(cin,user);
    cout << "Enter your password: ";
    getline(cin,pass);
    try {
        pin_admin = DB::loginAuth(user, pass);
    } catch(exception &e ) {
        cout << e.what();
        goto line_auth;
    }
    system("cls");
    DB::admin_pin = pin_admin;
    if(DB::admin_read == false) {
        DB::readQuizes();
        DB::admin_read = true;
    }
    admin_menu();
}

void login() {
    cout << endl;
    cout << "1. Login as a guest" << endl;
    cout << "2. Login as an admin" << endl;
    cout << "0. Exit" << endl;
    string selection;
    getline(cin,selection);
    
    system("cls");
    login_label:
    if(selection == "1") {
        line28:
        try {
            login_guest();
        }catch(exception &e) {
            cout << e.what();
            goto line28;
        }
    } else if(selection == "2") {
        login_admin();
    }
    else if(selection == "0") {
        return;
    }
    else {
        system("cls");
        throw invalid_argument("you can select only 1 or 2");
        
    }
}
