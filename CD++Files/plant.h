/*******************************************************************
*
*  DESCRIPTION: class Plant
*  AUTHOR:  Alex Campbell
*  EMAIL: alexc@sce.carleton.ca
*  DATE: October 20, 2004
*
*******************************************************************/

#ifndef __Plant_H
#define __Plant_H

#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;


class Plant : public Atomic
{
public:
	Plant( const string &name = "Plant" );	 //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &Uin;
	Port &Ypdin;
	Port &Ypddin;	
	Port &Ypout;	
	Port &Trigger;	
	Port &plantState;			

	double p11;
	double p12;
	double p13;	
	double p21;
	double p22;
	double p23;	
	double p31;
	double p32;
	double p33;	
	double U;
	double Ypd;
	double Ypdd;
	double Yp;
	double scrap;	
	int	createOutput;
	int pState;	


	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
	

};	// class Plant

// ** inline ** // 
inline
string Plant::className() const
{
	return "Plant" ;
}

#endif   //Plant
