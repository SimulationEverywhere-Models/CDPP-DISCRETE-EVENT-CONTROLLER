/*******************************************************************
*
*  DESCRIPTION: class Model1
*  AUTHOR:  Alex Campbell
*  EMAIL: alexc@sce.carleton.ca
*  DATE: October 20, 2004
*
*******************************************************************/

#ifndef __Model2_H
#define __Model2_H

#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;


class Model2 : public Atomic
{
public:
	Model2( const string &name = "Model2" );	 //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &Uin;
	Port &Ypin;	
	Port &Ypdin;
	Port &Ypddin;	
	Port &Ymout;		
	Port &Eout;
	
	double p1;
	double p2;
	double p3;		
	double	U;
	double	Ym;
	double	Yp;	
	double	Ypd;
	double	Ypdd;
	double	E;
	int	haveU;
	int	haveYp;	
	int	haveYpd;
	int	haveYpdd;					
	
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}
	

};	// class Model2

// ** inline ** // 
inline
string Model2::className() const
{
	return "Model2" ;
}

#endif   //Model2
