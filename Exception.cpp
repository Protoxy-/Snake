#include "Exception.hh"

errExcept::errExcept(std::string const &message, std::string const &component)
  : _message(message), _component(component)
{}

errExcept::~errExcept() throw()
{}

std::string const & errExcept::getComponent() const
{
  return (_component);
}

const char* 		errExcept::what() const throw()
{
  return (_message.c_str());
}

errGraphic::errGraphic(std::string const &message, std::string const &component)
  : _message(message), _component(component)
{}

errGraphic::~errGraphic() throw()
{}

std::string const & errGraphic::getComponent() const
{
  return (_component);
}

const char* 		errGraphic::what() const throw()
{
  return (_message.c_str());
}

errAbort::errAbort(std::string const &message, std::string const &component)
  : _message(message), _component(component)
{}

errAbort::~errAbort() throw()
{}

std::string const & errAbort::getComponent() const
{
  return (_component);
}

const char* 		errAbort::what() const throw()
{
  return (_message.c_str());
}
