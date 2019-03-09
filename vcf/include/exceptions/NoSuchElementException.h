/* Generated by Together */

#ifndef NOSUCHELEMENTEXCEPTION_H
#define NOSUCHELEMENTEXCEPTION_H




namespace VCF {

class FRAMEWORK_API NoSuchElementException : public BasicException {
public:
	NoSuchElementException( const String & message ):
	  BasicException( message ){};

	NoSuchElementException():
		BasicException( NO_SUCH_ELEMENT_FOUND ){};

	NoSuchElementException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~NoSuchElementException(){};
};

};

#endif //NOSUCHELEMENTEXCEPTION_H