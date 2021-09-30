#ifndef VAXLIB_H
#define VAXLIB_H

#include <sstream>
#include <string>
#include <vector>

using std::stringstream;

using std::string;
using std::ostream;
using std::vector;

template<typename T>
string vec2str(const vector<T> vec){
    stringstream ss;
    int i=0;
    for (const T& el : vec){
        if (i>0){
            ss << ", ";
        }
        ss << el;
        i++;
    }
    return ss.str();
}

template<typename T, typename U>
string pair2str(const std::pair<T, U> p){
    stringstream ss;
    ss << "pair(" << p.first << "," << p.second << ")";
    return ss.str();
}

struct Vaccine {
    int code;     // es 0
    string name;  // es x
    std::pair<int, int> age_range;
    int injections;  // iniezioni richieste
    int recall_span;  // giorni al prossimo vaccino

    friend ostream& operator<<(ostream& os, const Vaccine& vax);
};

inline ostream& operator<<(ostream& os, const Vaccine& vax){
    os << "Vaccine(";
    os << vax.code << "," << vax.name << "," << pair2str(vax.age_range) << "," << vax.injections << "," << vax.recall_span << ")";
    return os;
};


struct Date {    
    int year;    
    int month;  // 1-12 inclusi
    int day;    // 1-31 inclusi
    
    // Overrides default ostream << behaviour      
    friend ostream& operator<<(ostream& os, const Date& date);      
};


inline ostream& operator<<(ostream& os, const Date& date){
    os << "Date(";
    os << date.year << "," << date.month << "," << date.day << ")";
    return os;
};

struct Time {
    int hour;   // 0->11 incluse
    int minute; // 0 -> 59 inclusi

    friend ostream& operator<<(ostream& os, const Time& time);      
};


inline ostream& operator<<(ostream& os, const Time& time){
    os << "Time(";
    os << time.hour << "," << time.minute << ")";
    return os;
};


struct Appointment {
        
    string fiscal_code;
    int vaccine_code;    
    string vaccine_name;
    Date date;
    Time time;        
    int recall; // numero richiamo - NOTA: parte da 1
    bool injected;  // l'appuntamento si è concluso con l'iniezione
    
    friend ostream& operator<<(ostream& os, const Appointment& appointment);
};

inline ostream& operator<<(ostream& os, const Appointment& app){
    os << "Appointment(";
    os << app.fiscal_code 
        << "," << app.vaccine_code
        << "," << app.vaccine_name
        << "," << app.date 
        << "," << app.time
        << "," << app.recall 
        << "," << app.injected << ")";
    return os;
}


#endif // VAXLIB_H