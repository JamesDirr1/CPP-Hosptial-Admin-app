//James Dirr CSC-402-001
//Hospital admin app that takes and in user commands and does various functions based on the command.

#include <sstream>
#include <unistd.h>
#include <algorithm>
#include "iostream"
#include "string"
#include "vector"
#include "queue"
#include "random"
#include "Logger.h"
#include "Patient.h"
#include "compare.h"

using namespace std;

static vector<Patient*> patientsList;
static vector<Patient*> treatedList;
static vector<string> doctorList;
static priority_queue<Patient*, vector<Patient*>, compare> triageList;
static bool debug;

void addPatient();
void MultiPatient();
void nextPatient();
void TreatPatient();
void TreatALl();
void PatientReport();
void PatientByDoctor();
void triage();
void TreatedReport();
int randInt(int a, int b);
bool check_number(string str);
void TrimWord(std::string& word);


int main() {
    //start of session
    Logger::instance().log("\n---------------NEW SESSION---------------", debug);
    debug = false;
    bool endProg = false;
    string command;
    vector<string> commandList;
    commandList.emplace_back("0 - 'Exit': Exits the program");
    commandList.emplace_back("1 - 'Help': List all commands");
    commandList.emplace_back("2 - 'Debug': Toggles debug mode");
    commandList.emplace_back("3 - 'AddPatient': Adds takes the user through the process of adding a single patient");
    commandList.emplace_back("4 - 'AddMultiPatients': Adds patients from a file");
    commandList.emplace_back("5 - 'NextPatient': Provides report for the next patient to be treated");
    commandList.emplace_back("6 - 'TreatPatient': Treats the next patient");
    commandList.emplace_back("7 - 'TreatAll': Treats all patients");
    commandList.emplace_back("8 - 'PatientReport': prints out a Patients report");
    commandList.emplace_back("9 - 'PatientByDoctor': prints out all patients by their doctor");
    commandList.emplace_back("10 - 'Triage': prints a report of all patients in triage");
    commandList.emplace_back("11 - 'TreatedReport': prints a report of all patients in triage");

    while(!endProg) {
        cout << "Enter a command or 'Exit' to end session: " << endl;
        cin >> command;
        if(command == "Exit" || command == "0"){
            Logger::instance().log("command 0 - 'Exit' Called \n---------------END SESSION---------------", debug);
            cout<<"ENDING SESSION"<<endl;
            endProg = true;
        }else if(command == "Help" || command == "1"){
            Logger::instance().log("command 1 - 'Help' Called", debug);
            cout<<"List of current commands: "<<endl;
            for(const auto& s: commandList){
                cout<< s << endl;
            }
        }else if(command == "Debug" || command == "2"){
            Logger::instance().log("command 2 - 'Debug' Called", debug);
            if(debug){
                Logger::instance().log("Debug mode Turned off", debug);
                debug = false;
            }else{
                debug = true;
                Logger::instance().log("Debug mode Turned on", debug);
            }
        }else if (command == "AddPatient" || command == "3") {
            Logger::instance().log("command 3 - 'AddPatient' called ", debug);
            addPatient();
        }else if (command == "AddMultiPatients" || command == "4") {
            Logger::instance().log("command 4 - 'AddMultiPatients' called ", debug);
            MultiPatient();
        }else if (command == "NextPatient" || command == "5") {
            Logger::instance().log("command 5 - 'NextPatient' called ", debug);
            nextPatient();
        }else if (command == "TreatPatient" || command == "6") {
            Logger::instance().log("command 6 - 'TreatPatient' called ", debug);
            TreatPatient();
        }else if (command == "TreatAll" || command == "7") {
            Logger::instance().log("command 7 - 'TreatAll' called ", debug);
            TreatALl();
        }else if (command == "PatientReport" || command == "8") {
            Logger::instance().log("command 8 - 'PatientReport' called ", debug);
            PatientReport();
        }else if (command == "PatientByDoctor" || command == "9") {
            Logger::instance().log("command 9 - 'PatientByDoctor' called ", debug);
            PatientByDoctor();
        }else if(command == "Triage" || command == "10"){
            Logger::instance().log("command 10 - 'Triage' Called", debug);
            triage();
        }else if(command == "TreatedReport" || command == "11"){
            Logger::instance().log("command 11 - 'TreatedReport' Called", debug);
            TreatedReport();
        }else{
            Logger::instance().log("Invalid command: " + command + " called", debug);
            cout<<command<< " is not a valid command"<<endl;
            cout<<"List of current commands: "<<endl;
            for(const auto& s: commandList){
                cout<< s << endl;
            }
        }
    }
}



void addPatient(){
    //patients info
    string Fname, Mname, Lname, suffix, ailment, doctor, treat, str;
    vector<string> ailments;
    vector<string> temp;
    bool treated, found = false;
    int priority;
    //process of getting info from user
    cout<<"Enter Patient's first name: "<< endl;
    cin>> Fname;
    cout<<"Enter Patient's middle name: "<< endl;
    cin >> Mname;
    cout<<"Enter Patient's last name: "<< endl;
    cin >> Lname;
    cout<<"Enter Patient's suffix: "<< endl;
    cin >> suffix;
    cout<<"Enter Patient's Aliments seperated by a ',': "<< endl;
    getline(cin>>ws, str);
    //cout<<str<<endl;
    stringstream ss(str);
    while(ss.good()){
        string substr;
        getline(ss, substr, ',');
        TrimWord(substr);
        //cout<<substr<<endl;
        ailments.push_back(substr);
    }
    cout<<"Enter Patient's doctor: "<<endl;
    cin >> doctor;
    cout<<"Has the patient been treated? 'Yes' or 'No':"<< endl;
    cin >> treat;
    if(treat == "Yes" || treat == "yes" || treat == "1"){
        treated = true;
    }else{
        treated = false;
    }
    cout<<"Enter Patient's priority, the lower the number the higher the priority: "<<endl;
    cin >> priority;
    //creates new patient
    auto *pat = new Patient(Fname, Mname, Lname, suffix, ailments, doctor, treated, priority);
    //adds patient to all patient list
    patientsList.push_back(pat);
    for(auto & i : doctorList){
        if(i == doctor){
            found = true;
        }
    }
    if(!found){
        Logger::instance().log("New doctor: " + doctor + " added to doctor list", debug);
        doctorList.push_back(doctor);
    }
    if(treated){
        Logger::instance().log(("Patient " + pat->patientInfo() + "added to treated"), debug);
        treatedList.push_back(pat);
    }else{
        Logger::instance().log(("Patient " + pat->patientInfo() + "added to triage"), debug);
        triageList.push(pat);
    }
}



void MultiPatient(){
    //patients info
    string Fname, Mname, Lname, suffix, ailment, doctor, treat, file, line;
    vector<string> ailments;
    vector<string> temp;
    bool treated;
    int priority, count = 0;
    cout<<"Enter name of file to add patients from: "<<endl;
    cin>>file;
    ifstream ClientFile( file, ios::in );
    //checks if files exists
    if(!ClientFile){
        Logger::instance().log("File " + file + " could not be opened", true);
    }else{
        //opens and reads from file
        Logger::instance().log("File " + file + " opened", debug);
        while (getline(ClientFile, line)){
            string category, value;
            stringstream ss(line);
            string substr;
            getline(ss, substr, ':');
            ss >> value;
            category = substr;
            if(category == "firstName"){
                Fname = value;
            }
            if(category == "middleName"){
                Mname = value;
            }
            if(category == "lastName"){
                Lname = value;
            }
            if(category == "suffix"){
                suffix = value;
            }
            if(category == "ailment"){
                ailments.push_back(value);
            }
            if(category == "doctor"){
                doctor = value;
            }
            if(category == "treated"){
                treated = (value == "1 ");
            }
            if(category == "priority"){
                bool found = false;
                priority = stoi(value);
                count ++;
                auto *pat = new Patient(Fname, Mname, Lname, suffix, ailments, doctor, treated, priority);
                patientsList.push_back(pat);
                if(treated){
                    Logger::instance().log(("Patient " + pat->patientInfo() + "added to treated"), debug);
                    treatedList.push_back(pat);
                }else{
                    Logger::instance().log(("Patient: " + pat->patientInfo() + "added to triage"), debug);
                    triageList.push(pat);
                }
                for(auto & i : doctorList){
                    if(i == doctor){
                        found = true;
                    }
                }
                if(!found){
                    Logger::instance().log("New doctor: " + doctor + " added to doctor list", debug);
                    doctorList.push_back(doctor);
                }
            }
        }
        Logger::instance().log((to_string(count) + " patients added from " + file), true);
        ClientFile.close();
        Logger::instance().log(file + "closed", debug);
    }
}

void nextPatient(){
    //checks if there is a patient in triage
    if(triageList.empty()) {
        Logger::instance().log("No one left to treat", true);
    }else{
        //outputs patient with the highest priority
        Patient *q = triageList.top();
        cout<<"Next patient is "<< q->patientInfo()<<endl;
        Logger::instance().log((("Next patient is " +  q->patientInfo())), debug);
    }
}

void TreatPatient(){
    //checks if there is a patient in triage
    if(triageList.empty()) {
        Logger::instance().log("No one left to treat", true);
    }else{
        //treats the highest priority patient and removes them from triage
        cout<<"Treating Patient"<<endl;
        sleep(randInt(1, 3));
        Patient *q = triageList.top();
        triageList.pop();
        cout<<"Patient "<< q->patientInfo() << "treated"<<endl;
        Logger::instance().log((("Patient " +  q->patientInfo() + "treated")), debug);
        Logger::instance().log(("Patient " + q->patientInfo() + "added to treated"), debug);
        treatedList.push_back(q);
    }
}

void TreatALl(){
    //checks if there is a patient in triage
    if(triageList.empty()) {
        Logger::instance().log("No one left to treat", true);
    }else {
        //treats and removes all patients from triage
        cout<<"Treating Patients"<<endl;
        int count = triageList.size();
        while (!triageList.empty()) {
            sleep(randInt(1, 3));
            Patient *q = triageList.top();
            triageList.pop();
            Logger::instance().log(("Patient " + q->patientInfo() + "treated"), debug);
            Logger::instance().log(("Patient " + q->patientInfo() + "added to treated"), debug);
            treatedList.push_back(q);
        }
        cout<< "All patients treated"<<endl;
        Logger::instance().log(to_string(count) + " patients treated", debug);
    }
}

void PatientReport(){
    string Fname;
    string Mname;
    string Lname;
    string suffix;
    string input;
    bool found = false;
    cout<<"Enter patients ID number or full name: "<<endl;
    getline(cin>>ws, input);
    //checks if input is an ID number or a name
    if(check_number(input)){
        for(auto & i : patientsList){
            //searches by ID number
            if(i->getId() == stoi(input)){
                cout<<i->patientReport()<<endl;
                found = true;
                Logger::instance().log((i->patientInfo() + "report printed"), debug);
                break;
            }
        }
        if(!found){
            Logger::instance().log("Patient of ID number: " + input + " does not exist", true);
        }
    }else{
        stringstream ss(input);
        string substr, substr2, substr3, substr4;
        getline(ss, substr, ' ');
        Fname = substr;
        getline(ss, substr2, ' ');
        Mname = substr2;
        getline(ss, substr3, ' ');
        Lname = substr3;
        getline(ss, substr4, ' ');
        suffix = substr4;
        for(auto & i : patientsList){
            //searches by name
            if(Fname == i->getFname() && Mname == i->getMname() && Lname == i->getLname() && suffix == i->getSufifx()){
                cout<<i->patientReport()<<endl;
                found = true;
                Logger::instance().log((i->patientInfo() + "report printed"), debug);
                break;
            }
        }
        if(!found){
            Logger::instance().log("Patient of name: " +  input + " does not exist", true);
        }
    }
}

void PatientByDoctor(){
    //sorts doctor list in order
    sort(doctorList.begin(), doctorList.end());
    for(auto & i : doctorList){
        //prints all patients by doctor
        cout<< i <<"'s patients: "<<endl;
        Logger::instance().log("Doctor: " + i, debug);
        for(auto & j : patientsList){
            if(j->getDoctor() == i){
                Logger::instance().log(j->patientInfo(), debug);
                cout<<j->patientInfo()<<endl;
            }
        }
    }
}


void triage(){
    vector<Patient*> temp;
    //checks if triage is empty
    if(triageList.empty()){
        Logger::instance().log("Triage is empty", true);
    }else{
        int count = triageList.size();
        cout<<"Number of patients in triage is "<<count<<endl;
        while(!triageList.empty()){
            //reports patients in order and removes them and puts them in a temp vector
            Patient *q = triageList.top();
            temp.push_back(q);
            triageList.pop();
            cout<<q->patientReport()<<endl;
            Logger::instance().log((q->patientInfo() + "report printed"), debug);
        }//puts patients back into triage
        for(auto & i : temp){
            triageList.push(i);
        }
        Logger::instance().log("Triage list Printed", true);
    }
}

void TreatedReport(){
    int count = treatedList.size();
    cout<<"Number of  treated patients is "<<count<<endl;
    for(auto & i : treatedList){
        //prints report for all treated pateints
        cout<<i->patientReport()<<endl;
        Logger::instance().log((i->patientInfo() + "report printed"), debug);
    }
}

int randInt(int a, int b){
    //Random int generator
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(a,b);
    return distribution(generator);
}

bool check_number(string str) {
    //checks if a string is an int
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false) {
            return false;
        }
    return true;
}

void TrimWord(std::string& word)
//removes extra spaces before or after a string
{
    if (word.empty()) return;
    // Trim spaces from left side
    while (word.find(' ') == 0)
    {
        word.erase(0, 1);
    }
    // Trim spaces from right side
    size_t len = word.size();
    while (word.rfind(' ') == --len)
    {
        word.erase(len, len + 1);
    }
}