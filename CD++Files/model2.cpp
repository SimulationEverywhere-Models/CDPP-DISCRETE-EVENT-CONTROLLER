#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "model2.h"


Model2::Model2( const string &name )
: Atomic( name )
, Uin( addInputPort( "Uin" ) )
, Ypin( addInputPort( "Ypin" ) )
, Ypdin( addInputPort( "Ypdin" ) )
, Ypddin( addInputPort( "Ypddin" ) )
, Ymout( addOutputPort( "Ymout" ) )
, Eout( addOutputPort( "Eout" ) )


{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
		MASSERT( dist ) ;
		for ( register int i = 0; i < dist->varCount(); i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
			dist->setVar( i, str2Value( parameter ) ) ;
		}
}

/*******************************************************************
* Function Name: initFunction
* Description: 
********************************************************************/
Model &Model2::initFunction()
{
	p1 = 0.1;
	p2 = 0.8;
	p3 = 2.5;					
	U = 0;
	Ym = 0;
	Yp = 0;	
	Ypd = 0;
	Ypdd = 0;
	E = 0; //This is the modelling error
	haveU = 0;
	haveYp = 0;		
	haveYpd = 0;
	haveYpdd = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: When input is received, wait for a random amount ....
********************************************************************/
Model &Model2::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == Uin) {
 		if (haveU == 0) {
			haveU = 1;
			U = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
 		}
	}
	if (msg.port() == Ypin) {
 		if (haveYp == 0) {
			haveYp = 1;
			Yp = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
 		}
	}
	if (msg.port() == Ypdin) {
 		if (haveYpd == 0) {
			haveYpd = 1;
			Ypd = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
 		}
	}	
	if (msg.port() == Ypddin) {
 		if (haveYpdd == 0) {
			haveYpdd = 1;
			Ypdd = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
 		}
	}	
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: no internal functions
********************************************************************/
Model &Model2::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: output the product and output a ready signal to identify
*		
********************************************************************/
Model &Model2::outputFunction( const InternalMessage &msg )
{

	if (haveU == 1) { 
		if (haveYp == 1) { 	
			if (haveYpd == 1) { 
				if (haveYpdd == 1) { 
					haveU = 0;
					haveYp = 0;
					haveYpd = 0;					
					haveYpdd = 0;				
					Ym = p1*Ypd+p2*Ypdd+p3*U;
					E = (Yp-Ym)*(Yp-Ym); //Error Squared (model identification error)
					sendOutput( msg.time(), Ymout, Ym ) ;
					sendOutput( msg.time(), Eout, E ) ;				
				}
			}
		}
	}
		return *this ;
}

