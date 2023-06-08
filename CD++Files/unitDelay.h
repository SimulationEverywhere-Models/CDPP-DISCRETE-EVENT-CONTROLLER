/*******************************************************************
*
*  DESCRIPTION: class UnitDelay
*  AUTHOR:  Alex Campbell
*  EMAIL: alexc@sce.carleton.ca
*  DATE: October 20, 2004
*
*******************************************************************/

#ifndef __UnitDelay_H
#define __UnitDelay_H

#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;


class UnitDelay : public Atomic
{
public:
	UnitDelay( const string &name = "UnitDelay" );	 //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &theIn;
	Port &theOut;
	
	int	haveSignal;
	double theSignal;

	
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
	

};	// class UnitDelay

// ** inline ** // 
inline
string UnitDelay::className() const
{
	return "UnitDelay" ;
}

#endif   //UnitDelay
