#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "unitDelay.h"


UnitDelay::UnitDelay( const string &name )
: Atomic( name )
, theIn( addInputPort( "theIn" ) )
, theOut( addOutputPort( "theOut" ) )

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
Model &UnitDelay::initFunction()
{
	haveSignal = 0;
	theSignal = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: When input is received, wait for a random amount ....
********************************************************************/
Model &UnitDelay::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == theIn) {
 		if (haveSignal == 0) {
	 		haveSignal = 1;
			theSignal = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.5) ) ) ; 
 		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: no internal functions
********************************************************************/
Model &UnitDelay::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: output the product and output a ready signal to identify
*		
********************************************************************/
Model &UnitDelay::outputFunction( const InternalMessage &msg )
{

	if (haveSignal == 1) { //have the new event
		haveSignal = 0;
		sendOutput( msg.time(), theOut, theSignal ) ;		

	}
		return *this ;
}

