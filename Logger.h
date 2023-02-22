//James Dirr CSC-402-001
//singleton logger class

#ifndef HOSPITAL_ADIM_LOGGER_H
#define HOSPITAL_ADIM_LOGGER_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Logger{
private:
    Logger() {};
public:
    static Logger instance(){
        static Logger instance;
        return instance;
    }

    void log(string output, bool debug){
        //logs to log.txt or to log.txt and console in debug mode
        if (debug){
            cout<<output<<endl;
        }
        ofstream opFile ("Log.txt", ios::app);
        if ( !opFile) {
            cerr << "File could not be opened" << endl;
            exit(1);
        }
        opFile<< output << endl;
    }

};
#endif //HOSPITAL_ADIM_LOGGER_H
