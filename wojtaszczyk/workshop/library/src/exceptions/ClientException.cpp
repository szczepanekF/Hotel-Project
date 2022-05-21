#include "exceptions/ClientException.h"

ClientException::ClientException(const std::string &arg) : logic_error(arg) {}
