/*******************************************************************
*
*  DESCRIPTION: class InterpLast
*  AUTHOR:  Alex Campbell
*  EMAIL: alexc@sce.carleton.ca
*  DATE: October 20, 2004
*
*******************************************************************/

#ifndef __InterpLast_H
#define __InterpLast_H

#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;


class InterpLast : public Atomic
{
public:
	InterpLast( const string &name = "InterpLast" );	 //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &evXin;
	Port &xTin;
	Port &xdout;	
	Port &xddout;		

	double	evX;
	double oldEvX;
	double xT;	
	double oldxT;
	double slopeX;
	double xtd;		
	double xtdd;			
	int waitingforData;
	int haveNewEvent;
	int haveNewEventT;
	
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
	

};	// class InterpLast

// ** inline ** // 
inline
string InterpLast::className() const
{
	return "InterpLast" ;
}

#endif   //InterpLast
