//James Dirr CSC-402-001
//compare structure for patients

#ifndef HOSPITAL_ADIM_COMPARE_H
#define HOSPITAL_ADIM_COMPARE_H
#include "Patient.h"
struct compare{
    //compares patients based on their priority
    bool operator()(const Patient* lhs, const Patient* rhs)const{
        return lhs->getPriority() > rhs->getPriority();
    }
};
#endif //HOSPITAL_ADIM_COMPARE_H
