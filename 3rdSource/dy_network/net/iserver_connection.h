#ifndef ISERVERCONNECTION_H
#define ISERVERCONNECTION_H

/**********************************************************************************************//**
 * @class	IServerConnection
 *
 * @brief	Network connection for server side.
 *
 * @date	2012/10/9
 **************************************************************************************************/
class IServerConnection
{
protected:
	virtual ~IServerConnection(){};
public:
	virtual void CloseServer() = 0;

};


#endif
