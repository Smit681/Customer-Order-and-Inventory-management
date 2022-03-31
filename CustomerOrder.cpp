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
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const string& str){

		Utilities temp;
		bool state = true;
		size_t next = 0;
		m_name = temp.extractToken(str, next, state);
		m_product = temp.extractToken(str, next, state);
		m_cntItem = 0;
		size_t pos = next;
		while (state == true){
			temp.extractToken(str, next, state);
			m_cntItem++;
		}
		m_lstItem = new Item * [m_cntItem];
		state = true;
		for (size_t i = 0; i < m_cntItem; ++i){
			m_lstItem[i] = new Item(temp.extractToken(str, pos, state));
		}
		if (temp.getFieldWidth() > m_widthField){
			m_widthField = temp.getFieldWidth();
		}
	}

	bool CustomerOrder::isFilled() const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_isFilled == false){
				filled = false;
			}
		}
		return filled;
	}

	bool CustomerOrder::isItemFilled(const string& str) const{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == str) {
				filled = m_lstItem[i]->m_isFilled;
			}
		}
		return filled;
	}

	void CustomerOrder::fillItem(Station& station, ostream& os) {
		for (size_t i = 0; i < m_cntItem; ++i){
			if (m_lstItem[i]->m_itemName == station.getItemName()){
				if (station.getQuantity() > 0){
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					m_lstItem[i]->m_isFilled = true;
					os << right << "    Filled " << m_name << ", " << m_product << " [" 
						<< m_lstItem[i]->m_itemName << "]" << endl;
				}
				else{
					os << right << "    Unable to fill " << m_name << ", " << m_product << " ["
						<< m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	CustomerOrder::CustomerOrder() : m_name{}, m_product{}, m_cntItem{}, m_lstItem{} {}

	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept{
		*this = move(order);
	}

	CustomerOrder::~CustomerOrder(){
		if (m_lstItem)
			for (size_t i = 0; i < m_cntItem; ++i){
				delete m_lstItem[i];
			}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept{
		if (&order != this){
			if (m_lstItem)
				for (size_t i = 0; i < m_cntItem; ++i){
					delete m_lstItem[i];
				}
			delete[] m_lstItem;
			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;
			order.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&){
		throw string("A CustomerOrder object should not allow copy operations");
	}

	void CustomerOrder::display(ostream& os) const{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++){
			os << "[" << setfill('0') << right << setw(6) << m_lstItem[i]->m_serialNumber << "] " 
				<< setfill(' ') << setw(m_widthField) << left << m_lstItem[i]->m_itemName 
				<< setfill(' ') << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") 
				<< endl;
		}
	}
}
