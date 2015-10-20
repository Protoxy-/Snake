#ifndef EXCEPTION_HH_
#define EXCEPTION_HH_

#include <string>

class errExcept : public std::exception
{
protected:
	std::string	_message;
	std::string	_component;

public:
	errExcept(std::string const &message, std::string const &component = "Unknown");
	~errExcept() throw();

    virtual std::string const 	&getComponent() const;
    const char* 								what() const throw();
};

class errGraphic : public std::exception
{
protected:
	std::string	_message;
	std::string	_component;

public:
	errGraphic(std::string const &message, std::string const &component = "Unknown");
	~errGraphic() throw();

    virtual std::string const 	&getComponent() const;
    const char* 								what() const throw();
};

class errAbort : public std::exception
{
protected:
	std::string	_message;
	std::string	_component;

public:
	errAbort(std::string const &message, std::string const &component = "Unknown");
	~errAbort() throw();

    virtual std::string const 	&getComponent() const;
    const char* 								what() const throw();
};


#endif
