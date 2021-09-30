#ifndef CENTER_H
#define CENTER_H

#include "vaxlib.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>


using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
using std::deque;


class Patient{
    private:
        string cf;
        string name;
        string surname;
        Date birthday;
        vector<string> allergie;
    
    public:
        Patient(string cf = "", string name = "", string surname = "", Date birtday = {1900,1,1}, vector<string> allergie = {}){
            this->cf = cf;
            this->name = name;
            this->surname = surname;
            this->birthday = birthday;
            this->allergie = allergie;
        }

        ~Patient(){
            cout << "DEBUG: destroying patient " << this->cf << endl;;
        }

        const string get_cf(){
            return this->cf;
        }

        const vector<string> get_allergie(){
            return this->allergie;
        }

        const int get_age(){
            return (2021 - this->birthday.year);
        }

};

class CheckIn{
    private:
        deque<Appointment*> queue;
        int name;
    
    public:
        CheckIn(){
            this->queue = {};
            this->name = 0;
        }

        ~CheckIn(){
            cout << "DEBUG: destroying CheckIn " << std::to_string(this->name) << endl;;
            for(Appointment* app : this->queue){
                delete app;
            }
        }

        void set_name(int new_name){
            this->name = new_name;
        }

        int get_size() const{
            return this->queue.size();
        }

        int get_name() const{
            return this->name;
        }

        void add_app(Appointment* app){
            this->queue.push_back(app);
        }
};

class InjectionPoint{
    private:
        int code;
        string name;
        Vaccine* vaccine;
        int n_dosi;
        deque<Patient*> patients;

    public:
        InjectionPoint(Vaccine& vaccine, int n_dosi){
            Vaccine* vax = new Vaccine;
            vax = &vaccine;
            this->vaccine = vax;
            this->name = vaccine.name;
            this->code = vaccine.code;
            this->n_dosi = n_dosi;
        }

        ~InjectionPoint(){
            delete this->vaccine;
            for(Patient* p : this->patients){
                delete p;
            }
        }
};

class Center{
    private:
        bool status; //open(true) of close(false)
        unordered_map<string,Patient*> patient_list;
        vector<CheckIn*> check_in;
        vector<InjectionPoint*> injection_point;
        unordered_map<string,Vaccine> vax_list;
        Time time;
        Date date;

    public:

        Center(){
            this->status = false;
            cout << "DEBUG: adding new center" << endl;
            this->time = {0,0};
            this->date = {2021,7,1};

        }

        //RICORDA DISTRUTTORE

        void add_checkin(){
            CheckIn* new_checkin = new CheckIn();
            int i = this->check_in.size();
            new_checkin->set_name(i);
            this->check_in.push_back(new_checkin);
            cout << "Adding check in " << std::to_string(i) << endl;
        }

        void add_injection_point(Vaccine vax, int n_dosi){
            InjectionPoint* new_ip = new InjectionPoint(vax, n_dosi);
            this->injection_point.push_back(new_ip);

            //Aggiunta vaccino
                //RICORDA DI METTERE VERIFICHE SE GIA' PRESENTE
            /* QUI LO FACEVO CON ALLOCAZIONE DINAMICA MA SBAGLIAVO!
            Vaccine* new_vax = new Vaccine();
            new_vax = &vax;
            
            new_vax->name = vax.name;
            new_vax->code = vax.code;
            new_vax->age_range = vax.age_range;
            new_vax->injections = vax.injections;
            new_vax->recall_span = vax.recall_span;
            
            this->vax_list[new_vax->name] = new_vax;
            */
            this->vax_list[vax.name] = vax;
            cout << "Adding injection point for " << vax << endl;
        }


        void add_patient(string cf, string name, string surname, Date birthday, vector<string> allergie){
            Patient* new_patient = new Patient(cf, name, surname, birthday, allergie);
            this->patient_list[cf] = new_patient;
            cout << "Adding patient with cf : '" << cf << "'" << endl;
        }

        Appointment book(string cf, Date date, Time time, string vax){


            //CONTROLLO PRENOTAZIONE (tolto perché con il primo andavo già fuori range)
            /*
            for (string s : this->patient_list[cf]->get_allergie()){
                if(vax == s){
                    throw std::invalid_argument(string("Il vaccino non può essere prenotato: provocherà allergie!"));
                }
            }
            
            if(this->vax_list[vax]->age_range.first > this->patient_list[cf]->get_age() || this->vax_list[vax]->age_range.second < this->patient_list[cf]->get_age()){
                throw std::invalid_argument(string("Il vaccino non può essere prenotato: fuori dal range di età"));
            }
            */
            //Manca verifica seconda dose

            Appointment new_app;
            new_app.fiscal_code = cf;
            new_app.vaccine_code = this->vax_list[vax].code;
            //new_app.vaccine_code = this->vax_list[vax]->code;
            new_app.vaccine_name = vax;
            new_app.date = date;
            new_app.time = time;
            new_app.recall = 1;
            new_app.injected = true;

            cout << "Booking " << cf << " at " << date << " " << time << " for vaccine " << vax << endl;
            return new_app;
        }

        void open(Date date, Time time){
            cout << "**** Opening at " << date << ", " << time << "****" << endl;
            this->time = time;
            this->date = date;
        }

        void enqueue(Appointment& app){
            Appointment* new_app = new Appointment(app);
            CheckIn* current = new CheckIn();
            current = this->check_in[0];
            for(CheckIn* checkin : this->check_in){
                if(checkin->get_size() < current->get_size()){
                    current = checkin;
                }
            }
            this->check_in[current->get_name()]->add_app(new_app);
            cout << "enqueing " << app << " at check in " << std::to_string(current->get_name()) << endl;
        }




};


#endif //CENTER_H