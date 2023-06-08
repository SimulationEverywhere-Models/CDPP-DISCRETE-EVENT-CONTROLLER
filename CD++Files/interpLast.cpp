#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "interpLast.h"


InterpLast::InterpLast( const string &name )
: Atomic( name )
, evXin( addInputPort( "evXin" ) )
, xTin( addInputPort( "xTin" ) )
, xdout( addOutputPort( "xdout" ) )
, xddout( addOutputPort( "xddout" ) )

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
Model &InterpLast::initFunction()
{
	evX = 0;
	oldEvX = 0;
	xT = 0;
	oldxT = 0;
	slopeX = 0;		
	xtd = 0;
	xtdd = 0;	
	waitingforData = 0;
	haveNewEvent = 0;
	haveNewEventT = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: When input is received, wait for a random amount ....
********************************************************************/
Model &InterpLast::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == evXin) {
 		if (haveNewEvent == 0) {
			haveNewEvent = 1;
			oldEvX = evX;
			evX = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 
 		}
	}
	if (msg.port() == xTin) {
 		if (haveNewEvent == 1) {		
 			haveNewEventT = 1;
			oldxT = xT;
			xT = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.001) ) ) ; 				
 		}
	}	
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: no internal functions
********************************************************************/
Model &InterpLast::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: output the product and output a ready signal to identify
*		
********************************************************************/
Model &InterpLast::outputFunction( const InternalMessage &msg )
{

	if (haveNewEvent == 1) { //have the new event
		if (haveNewEventT == 1) { //have the new event time		
		haveNewEvent = 0;
		haveNewEventT = 0;
		slopeX = (evX-oldEvX)/(xT-oldxT);
		xtd = evX - slopeX;
		xtdd = evX - 2*slopeX;		
		sendOutput( msg.time(), xdout, xtd ) ;
		sendOutput( msg.time(), xddout, xtdd ) ;		
		}
	}
		return *this ;
}

