//==============================================
// Project       : MS3
//==============================================
// Name          : Smit Shah
// Student Number: 116605205
// Email         : syshah3@myseneca.ca
//
// Section       : ZAA         
//==============================================

#include <iostream>
#include "Workstation.h"
#include "Station.h"

using namespace std;
namespace sdds
{
    deque<CustomerOrder> pending{};
    deque<CustomerOrder> completed{};
    deque<CustomerOrder> incomplete{};

    Workstation::Workstation(const string& str) : Station(str){}

    bool Workstation::attemptToMoveOrder()
    {
        bool moved = false;
        if (m_orders.empty()) {
            return moved;
        }
        if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0){
            if (m_pNextStation != nullptr) {
                *m_pNextStation += move(m_orders.front());
            }
            else if (m_orders.front().isFilled()){
                completed.push_back(move(m_orders.front()));
            }
            else{
                incomplete.push_back(move(m_orders.front()));
            }
            m_orders.erase(m_orders.begin());
            return moved == true;
        }
        else{
            return moved;
        }
    }

    void Workstation::fill(ostream& os){
        if (!m_orders.empty()){
            m_orders.begin()->fillItem(*this, os);
        }
    }

    Workstation* Workstation::getNextStation() const{
        return m_pNextStation;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& order){
        m_orders.push_back(move(order));
        return *this;
    }


    void Workstation::setNextStation(Workstation* station){
        m_pNextStation = station;
    }

    void Workstation::display(ostream& os) const{
        os << getItemName() << " --> ";
        if (m_pNextStation){
            os << m_pNextStation->getItemName();
        }
        else{
            os << "End of Line";
        }
    }
}
