//==============================================
// Project       : MS3
//==============================================
// Name          : Smit Shah
// Student Number: 116605205
// Email         : syshah3@myseneca.ca
//
// Section       : ZAA         
//==============================================

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>
namespace sdds {
	class Station{
		size_t m_stationId{};
		std::string m_name{};
		std::string m_desc{};
		size_t m_serialNum{};
		size_t m_stock{};
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		unsigned int getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H