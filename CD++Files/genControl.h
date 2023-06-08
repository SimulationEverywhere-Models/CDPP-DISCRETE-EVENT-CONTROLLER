/*******************************************************************
*
*  DESCRIPTION: class GenControl
*  AUTHOR:  Alex Campbell
*  EMAIL: alexc@sce.carleton.ca
*  DATE: October 20, 2004
*
*******************************************************************/

#ifndef __GenControl_H
#define __GenControl_H

#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;


class GenControl : public Atomic
{
public:
	GenControl( const string &name = "GenControl" );	 //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &Yrin;
	Port &Ypin;
	Port &Ypdin;	
	Port &Uout;		
	Port &Em1in;		
	Port &Em2in;		
	Port &Em3in;		
	Port &modelSelect;			
		
	double q11;
	double q12;
	double q13;	
	double q21;
	double q22;
	double q23;	
	double q31;
	double q32;
	double q33;				
	double Yr;
	double Yp;
	double Ypd;
	double U;
	double em1;
	double em2;
	double em3;		
	int haveYr;
	int haveYp;
	int haveYpd; 
	int bestModel; 	
	
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
	

};	// class GenControl

// ** inline ** // 
inline
string GenControl::className() const
{
	return "GenControl" ;
}

#endif   //GenControl
