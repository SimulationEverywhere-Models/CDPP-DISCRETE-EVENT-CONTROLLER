#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "genControl.h"


GenControl::GenControl( const string &name )
: Atomic( name )
, Yrin( addInputPort( "Yrin" ) )
, Ypin( addInputPort( "Ypin" ) )
, Ypdin( addInputPort( "Ypdin" ) )
, Em1in( addInputPort( "Em1in" ) )
, Em2in( addInputPort( "Em2in" ) )
, Em3in( addInputPort( "Em3in" ) )
, Uout( addOutputPort( "Uout" ) )
, modelSelect( addOutputPort( "modelSelect" ) )
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
Model &GenControl::initFunction()
{
	q11 = 0.6;
	q12 = 0.2;
	q13 = 2.0;	
	
	q21 = 0.1;
	q22 = 0.8;
	q23 = 2.5;	
	
	q31 = 0.2;
	q32 = 0.5;
	q33 = 1.0;	
	Yr = 0;
	Yp = 0;
	Ypd = 0;
	U = 0;
	em1 = 0;
	em2 = 0;
	em3 = 0;		
	haveYr = 0;
	haveYp = 0;
	haveYpd = 0;	
	bestModel = 1;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: When input is received, wait for a random amount ....
********************************************************************/
Model &GenControl::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == Yrin) {
 		if (haveYr == 0) {
			haveYr = 1;
			Yr = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
 		}
	}
	if (msg.port() == Ypin) {
 		if (haveYp == 0) {
			haveYp = 1;
			Yp = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
 		}
	}
	if (msg.port() == Ypdin) {
 		if (haveYpd == 0) {
			haveYpd = 1;
			Ypd = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
 		}
	}	
	if (msg.port() == Em1in) {
		em1 = (double)msg.value();
     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
	}		
	if (msg.port() == Em2in) {
		em2 = (double)msg.value();
     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
	}		
	if (msg.port() == Em3in) {
		em3 = (double)msg.value();
     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
	}				
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: no internal functions
********************************************************************/
Model &GenControl::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: output the product and output a ready signal to identify
*		
********************************************************************/
Model &GenControl::outputFunction( const InternalMessage &msg )
{

	if (haveYr == 1) { 
		if (haveYp == 1) { 
			if (haveYpd == 1) { 
				haveYr = 0;
				haveYp = 0;
				haveYpd = 0;	
				U = (Yr-q21*Yp-q22*Ypd)/q23;
				// em1 = -2; //This is used to turn of switching for a demo!
				bestModel = 2;
				if (em1 < em2) { 							
					if (em1 < em3) { 
						bestModel = 1;							
						U = (Yr-q11*Yp-q12*Ypd)/q13;
					}
					if (em3 < em1) {
						bestModel = 3; 							
						U = (Yr-q31*Yp-q32*Ypd)/q33;
					}					
				}
				sendOutput( msg.time(), Uout, U ) ;
				sendOutput( msg.time(), modelSelect, bestModel ) ;				
			}
		}
	}
		return *this ;
}

