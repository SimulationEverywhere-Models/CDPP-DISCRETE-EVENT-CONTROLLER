/*******************************************************************
*
*  DESCRIPTION: class Model1
*  AUTHOR:  Alex Campbell
*  EMAIL: alexc@sce.carleton.ca
*  DATE: October 20, 2004
*
*******************************************************************/

#ifndef __Model1_H
#define __Model1_H

#include <list>
#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;


class Model1 : public Atomic
{
public:
	Model1( const string &name = "Model1" );	 //Default constructor

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
	

};	// class Model1

// ** inline ** // 
inline
string Model1::className() const
{
	return "Model1" ;
}

#endif   //Model1
