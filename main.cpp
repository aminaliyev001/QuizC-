#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include<map>
#include <ctime>
#include<fstream>
#include <cstdlib>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include <cctype>
#include<cmath>
using namespace std;
#include "Answers.h"
#include "Quiz.h"
#include "Admin.h"
#include "Guest.h"
#include "Db.h"
#include "AdminMenu.h"
#include "GuestMenu.h"
#include "Login.h"

void start_quiz() {
    try {
        login();
    }catch(exception &e) {
        cout << e.what();
        start_quiz();
    }
}

int main() {
    srand(time(0));
    DB::readAdmins();
    DB::addAdmins();
    start_quiz();
    return 0;
}
