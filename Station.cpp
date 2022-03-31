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
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& str){
		Utilities temp;
		size_t next_pos = 0;
		bool more = true;
		try{
			m_name = temp.extractToken(str, next_pos, more);
			if (m_widthField < temp.getFieldWidth()){
				m_widthField = temp.getFieldWidth();
			}
			m_serialNum = std::stoi(temp.extractToken(str, next_pos, more));
			m_stock = std::stoi(temp.extractToken(str, next_pos, more));
			m_desc = temp.extractToken(str, next_pos, more);
		}
		catch (std::string& err){
			std::cout << err;
		}
		id_generator++;
		m_stationId = id_generator;
	}
	const std::string& Station::getItemName() const{
		return m_name;
	}
	unsigned int Station::getNextSerialNumber(){
		return m_serialNum++;
	}

	size_t Station::getQuantity() const{
		return m_stock;
	}

	void Station::updateQuantity(){
		m_stock--;
		if (m_stock < 0){
			m_stock = 0;
		}
	}
	void Station::display(std::ostream& os, bool full) const{
		os << "[" << std::setw(3) << std::right << std::setfill('0') << m_stationId << "] ";
		os << "Item: " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name;
		os << " [" << std::setw(6) << std::right << std::setfill('0') << m_serialNum << "]";
		if (full == false){
			os << std::endl;
		}
		else{
			os << " Quantity: " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_stock;
			os << " Description: " << m_desc << std::endl;
		}
	}
}
