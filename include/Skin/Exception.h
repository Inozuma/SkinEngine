/* 
 * File:   Exception.h
 * Author: Inozuma
 *
 * Created on January 10, 2012, 4:00 PM
 */

#include <exception>
#include <string>

namespace Skin
{
	class Exception : public std::exception
	{
	private:
		std::string mMessage;

	public:
		explicit Exception(const std::string& msg) : mMessage(msg)
		{}
		virtual ~Exception() throw()
		{}

		const char* what() const throw()
		{
			return mMessage.c_str();
		}
	};
}