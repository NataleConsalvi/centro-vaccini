
#include "vaxlib.h"
#include "Center.h"
#include "catch2/catch2.hpp"




TEST_CASE("Adding ", "[Center]") {
    
    Center center;
    
    
    center.add_checkin();
    center.add_checkin();
    center.add_checkin();

    center.add_injection_point(Vaccine{0, "x", std::pair<int,int>(60,100), 1, 0}, 500);
    center.add_injection_point(Vaccine{1, "y", std::pair<int,int>(20,40), 2, 15},300);
    center.add_injection_point(Vaccine{2, "z", std::pair<int,int>(18,35), 2, 21},400);

    center.add_patient("a", "Mario", "Rossi", Date{1990,1,1}, {});
    center.add_patient("b", "Ada", "Verdi", Date{2000,7,2}, {"z"});
    center.add_patient("c", "Ugo", "Gialli", Date{1960,12,31}, {});
    center.add_patient("d", "Andrea", "Rododendri", Date{1960,5,1}, {"x"});
    
    /*
    Appointment app1 = center.book("a", Date{2021,7,1}, Time{9,30}, "x");
    Appointment app2 = center.book("b", Date{2021,7,1}, Time{9,30}, "y");
    Appointment app3 = center.book("c", Date{2021,7,1}, Time{9,30}, "z");
    */
}


TEST_CASE("test 2", "[vaxlib]") {
                
    //REQUIRE(square_root(4.0) == Approx(2.0));
}


TEST_CASE("test 3", "[vaxlib]") {
    
    //REQUIRE( cxx_examples::say_hello("peppo") == std::string("hello peppo"));        
}





