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
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include "Utilities.h"
#include "Workstation.h"
#include "LineManager.h"
using namespace std;

namespace sdds
{
    //Took help from peer for this constructor.
    LineManager::LineManager(const string& str, const vector<Workstation*>& stations) {
        ifstream fin(str);
        string Size = "";
        size_t itrnum = 0;
        bool check = true;
        m_cntCustomerOrder = pending.size();

        while (getline(fin, Size)){
            string::size_type val = Size.find('|');
            for (size_t iname = 0; iname < stations.size(); ++iname){
                if (stations.at(iname)->getItemName() == Size.substr(0, val)){
                    if (val != string::npos){
                        for (size_t ilist = 0; ilist < stations.size(); ++ilist){
                            if (stations.at(ilist)->getItemName() == Size.substr(val + 1)){
                                stations.at(iname)->setNextStation(stations.at(ilist));
                                activeLine.push_back(move(stations.at(iname)));
                            }
                        }
                    }
                    else{
                        activeLine.push_back(move(stations.at(iname)));
                    }
                }
            }
            for (size_t iname = 0; iname < activeLine.size(); ++iname){
                for (size_t ilist = 0; ilist < activeLine.size(); ++ilist){
                    if (activeLine.at(ilist)->getNextStation() != nullptr){
                        if (activeLine.at(iname)->getItemName() == activeLine.at(ilist)->getNextStation()->getItemName()){
                            check = false;
                        }
                    }
                }
                if (check){
                    m_firstStation = activeLine.at(iname);
                }
                check = true;
            }
            itrnum++;
        }
    }

    bool LineManager::run(ostream& os) {
        static size_t counter = 1;
        bool check = false;
        os << "Line Manager Iteration: " << counter << endl;
        counter++;
        if (!pending.empty()){
            *activeLine.front() += move(pending.front());
            pending.erase(pending.begin());
        }
        for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workStation){
            workStation->fill(os);
        });
        for_each(activeLine.begin(), activeLine.end(), [&](Workstation* workStation){
            workStation->attemptToMoveOrder();
        });
        if (completed.size() + incomplete.size() == m_cntCustomerOrder){
            check = true;
        }
        return check;
    }

    void LineManager::linkStations() {
        vector<Workstation*> line;
        Workstation* first = m_firstStation;
        while (first){
            line.push_back(first);
            first = first->getNextStation();
        }
        activeLine = line;
    }

    void LineManager::display(ostream& os) const{
        for (size_t i = 0; i < activeLine.size(); ++i){
            activeLine.at(i)->display(os);
            os << endl;
        }
    }


}
