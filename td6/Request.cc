#include "Request.h"

Request::Request(/* args */)
{
}

Request::~Request()
{
}

void Request::waitReturn()
{
    returnSema.take();
}