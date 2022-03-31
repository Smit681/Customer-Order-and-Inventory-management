//==============================================
// Project       : MS3
//==============================================
// Name          : Smit Shah
// Student Number: 116605205
// Email         : syshah3@myseneca.ca
//
// Section       : ZAA         
//==============================================

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
using namespace std;

namespace sdds
{
    extern deque<CustomerOrder> pending; 
    extern deque<CustomerOrder> completed; 
    extern deque<CustomerOrder> incomplete; 

    class Workstation : public Station 
    {
        deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{ nullptr };
    public:
        void fill(ostream& os);
        Workstation& operator+=(CustomerOrder&& );
        Workstation(const string& str);
        Workstation* getNextStation() const;
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        void display(ostream& os) const;
    };
}
#endif //!SDDS_WORKSTATION_H
