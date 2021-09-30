#include <iostream>
#include <string>


using std::string;
using std::cout;
using std::endl;
using std::ostream;


#include <vaxlib.h>
#include "Center.h"


int main() {
    

    Center center;

    center.add_checkin();
    center.add_checkin();
    center.add_checkin();
    center.add_checkin();    
    


    //Vaccine(string name, int age_range, int shots, int recall_span){
    center.add_injection_point(Vaccine{0, "x", std::pair<int,int>(60,100), 1, 0}, 500);
    center.add_injection_point(Vaccine{1, "y", std::pair<int,int>(20,40), 2, 15},300);
    center.add_injection_point(Vaccine{2, "z", std::pair<int,int>(18,35), 2, 21},400);

    
    //cout << center << endl;

                    // cod fiscale, nome, cognome, data di nascita, nomi vaccini a cui è allergico
    center.add_patient("a", "Mario", "Rossi", Date{1990,1,1}, {});
    center.add_patient("b", "Ada", "Verdi", Date{2000,7,2}, {"z"});
    center.add_patient("c", "Ugo", "Gialli", Date{1960,12,31}, {});
    center.add_patient("d", "Andrea", "Rododendri", Date{1960,5,1}, {"x"});
    center.add_patient("e", "Sara", "Cippirilli", Date{1960,7,11}, {});
    center.add_patient("f", "Ludovico", "Manzotti", Date{1960,2,21}, {"x"});
    center.add_patient("g", "Remo", "Nammi", Date{1960,4,15}, {});
    center.add_patient("h", "Elisa", "Stradi", Date{1960,11,31}, {"y","x"});
    center.add_patient("i", "Marco", "Zemmi", Date{1980,3,3}, {});
    center.add_patient("l", "Chiara", "Dapinti", Date{1930,12,7}, {"x"});
    center.add_patient("m", "Chiara", "Dapinti", Date{1930,12,7}, {});
    center.add_patient("n", "Pancrazio", "Ropenni", Date{1910,12,9}, {});

    
    Appointment app1 = center.book("a", Date{2021,7,1}, Time{9,30}, "x");
    Appointment app2 = center.book("b", Date{2021,7,1}, Time{9,30}, "y");
    Appointment app3 = center.book("c", Date{2021,7,1}, Time{9,30}, "z");
    Appointment app4 = center.book("d", Date{2021,7,1}, Time{9,35}, "x");
    Appointment app5 = center.book("e", Date{2021,7,1}, Time{9,35}, "y");    
    Appointment app6 = center.book("f", Date{2021,7,1}, Time{9,35}, "z");    
    Appointment app7 = center.book("g", Date{2021,7,1}, Time{9,40}, "x");
    Appointment app8 = center.book("h", Date{2021,7,1}, Time{9,40}, "y");
    Appointment app9 = center.book("i", Date{2021,7,1}, Time{9,40}, "z");
    Appointment app10 = center.book("l", Date{2021,7,1}, Time{9,45}, "x");
    Appointment app11 = center.book("m", Date{2021,7,1}, Time{9,45}, "y");
    Appointment app12 = center.book("n", Date{2021,7,1}, Time{9,45}, "z");

    
    center.open(Date{2021,7,1}, Time{9,30});
    
    center.enqueue(app1);
    center.enqueue(app2);
    center.enqueue(app3);
    center.enqueue(app4);
    center.enqueue(app5);
    center.enqueue(app6);
    center.enqueue(app7);
    center.enqueue(app8);
    center.enqueue(app9);
    center.enqueue(app10);
    center.enqueue(app11);
    center.enqueue(app12);
    /*
    cout << center << endl;

    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;
    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;
    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;
    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;
    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;


    Appointment app13 = center.book("a", Date{2021,7,22}, Time{9,0}, "x");
    Appointment app14 = center.book("b", Date{2021,7,22}, Time{9,0}, "y");
    Appointment app15 = center.book("c", Date{2021,7,22}, Time{9,0}, "z");
    Appointment app16 = center.book("d", Date{2021,7,22}, Time{9,10}, "x");
    Appointment app17 = center.book("e", Date{2021,7,22}, Time{9,10}, "y");
    Appointment app18 = center.book("f", Date{2021,7,22}, Time{9,10}, "z");


    center.close();
    center.open(Date{2021,7,22}, Time{9,0});    

    center.enqueue(app13);
    center.enqueue(app14);
    center.enqueue(app15);
    center.enqueue(app16);
    center.enqueue(app17);
    center.enqueue(app18);

    cout << center << endl;
    

    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;
    cout << "Exiting center: " << vec2str(center.dequeue()) << endl;
    cout << center << endl;    
    */
    return 0;
 
}


