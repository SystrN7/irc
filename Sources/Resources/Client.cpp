#include "Resources/Client.hpp"

Client::Client() : _nick("user"), _isOperator(false) {};

Client::Client(bool isop) : _nick("user"), _isOperator(isop) {};

Client::Client(string name) : _nick(name), _isOperator(false) {};

Client::Client(string name, bool isop) : _nick(name), _isOperator(isop) {};

bool	Client::getIsOperator(){return (this->_isOperator);};