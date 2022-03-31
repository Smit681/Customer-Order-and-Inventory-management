//==============================================
// Project       : MS3
//==============================================
// Name          : Smit Shah
// Student Number: 116605205
// Email         : syshah3@myseneca.ca
//
// Section       : ZAA         
//==============================================

#include <string>
#include "Utilities.h"
using namespace std;

namespace sdds {
	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth){
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const{
		return m_widthField;
	}

	void Utilities::setDelimiter(char newDelimiter){
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter(){
		return m_delimiter;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		string ans = str.substr(next_pos);
		size_t posE = ans.find(m_delimiter);
		if (posE < str.length()){
			ans = ans.substr(0, posE);
			next_pos += posE + 1;
			if (ans == ""){
				more = false;
				throw "There is not any token between delimiters";
			}
			more = true;
		}
		else{
			more = false;
		}

		if (ans.length() > m_widthField)
			setFieldWidth(ans.length());

		return ans;
	}
}
