//James Dirr CSC-402-001
//Patient object

#ifndef HOSPITAL_ADIM_PATIENT_H
#define HOSPITAL_ADIM_PATIENT_H
#include <utility>

#include "iostream"
#include "vector"
#include "Logger.h"
using namespace std;

class Patient{
    //patient info
private:
    string Fname;
    string Mname;
    string Lname;
    string suffix;
    vector<string> ailments;
    string doctor;
    bool treated;
    int priority;
    static int idCount;
    int id;
public:
    //constructor
    Patient(string  Fname, string  Mname, string  Lname, string  suffix, vector<string> aliments, string  doctor, bool treated, int priority)
            : Fname(std::move(Fname)), Mname(std::move(Mname)), Lname(std::move(Lname)), suffix(std::move(suffix)), ailments(std::move(aliments)),doctor(std::move(doctor)), treated(treated),priority(priority), id(++idCount){}
    //copy
    Patient(const Patient &rhs){
        Fname = rhs.Fname;
        Mname = rhs.Mname;
        Lname = rhs.Lname;
        suffix = rhs.suffix;
        ailments = rhs.ailments;
        doctor = rhs.doctor;
        treated = rhs.treated;
        priority =rhs.priority;
        id = rhs.id;
    }
    //operator overload
    const Patient & operator=(const Patient & rhs){
        if (this != &rhs){
            Fname = rhs.Fname;
            Mname = rhs.Mname;
            Lname = rhs.Lname;
            suffix = rhs.suffix;
            ailments = rhs.ailments;
            doctor = rhs.doctor;
            treated = rhs.treated;
            priority = rhs.priority;
            id = rhs.id;
        }
        return *this;
    }

    string getFname(){
        return Fname;
    }
    void setFname(string name){
        Fname = std::move(name);
    }
    string getMname(){
        return Mname;
    }
    void setMname(string name){
        Mname = name;
    }
    string getLname(){
        return Lname;
    }
    void setLname(string name){
        Lname = name;
    }
    string getSufifx(){
        return suffix;
    }
    void setSuffix(string s){
        suffix = s;
    }
    vector<string> getAilments(){
        return ailments;
    }
    void setAilments(vector<string> a){
        ailments = a;
    }
    string getDoctor() {
        return doctor;
    }
    void setDoctor(string d){
        doctor = d;
    }
    bool getTreated(){
        return treated;
    }
    void setTreated(bool t){
        treated = t;
    }
    int getPriority() const {
        return priority;
    }
    void setPriority(int n){
        priority = n;
    }
    int getId(){
        return id;
    }
    //returns all aliments
    static string listAilments(const vector<string>& a){
        //Logger::instance().log("listing ailments ", true);
        string temp;
        for(const auto& s : a){
            //Logger::instance().log(s, true);
            temp =  temp + "ailment: " + s + "\n";
            //Logger::instance().log(temp, true);
        }
        return temp;
    }
    //returns a report for the patient
    string patientReport(){
        string report = ("----------REPORT----------\nID: " + to_string(id)
                                +"\nFirstName: " + Fname
                                +"\nMiddleName: " + Mname
                                +"\nLastName: " + Lname
                                +"\nSuffix: " + suffix
                                +"\n" + listAilments(ailments)
                                + "Doctor: " + doctor
                                +"\nTreated: " + to_string(treated)
                                + "\nPriority: " + to_string(priority));
        return report;
    }
    //returns a patients info
    string patientInfo(){
        string info = ("ID: " + to_string(id) +", Name: " + Fname + " " + Mname + " "+ Lname + " " + suffix + " ");
        return info;
    }

};
int Patient::idCount;
#endif //HOSPITAL_ADIM_PATIENT_H
