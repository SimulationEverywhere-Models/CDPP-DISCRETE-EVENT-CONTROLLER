#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "plant.h"


Plant::Plant( const string &name )
: Atomic( name )
, Uin( addInputPort( "Uin" ) )
, Ypdin( addInputPort( "Ypdin" ) )
, Ypddin( addInputPort( "Ypddin" ) )
, Trigger( addInputPort( "Trigger" ) )
, plantState( addInputPort( "plantState" ) )
, Ypout( addOutputPort( "Ypout" ) )

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
Model &Plant::initFunction()
{

	p11 = 0.6;
	p12 = 0.2;
	p13 = 2.0;	
	
	p21 = 0.1;
	p22 = 0.8;
	p23 = 2.5;	
	
	p31 = 0.2;
	p32 = 0.5;
	p33 = 1.0;	
			
	U = 0;
	Ypd = 0;
	Ypdd = 0;
	Yp = 0;
	scrap = 0;
	createOutput = 0;
	pState = 1;	
	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: When input is received, wait for a random amount ....
********************************************************************/
Model &Plant::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == Uin) {
			U = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
	}
	if (msg.port() == Ypdin) {
			Ypd = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
	}
	if (msg.port() == Ypddin) {
			Ypdd = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
	}	
	if (msg.port() == Trigger) {
 		if (createOutput == 0) {
			createOutput = 1; 
			scrap = (double)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
 		}
	}
	if (msg.port() == plantState) {
			pState = (int)msg.value();
	     	holdIn( active, Time( static_cast< float >(.1) ) ) ; 
	}			
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: no internal functions
********************************************************************/
Model &Plant::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: output the product and output a ready signal to identify
*		
********************************************************************/
Model &Plant::outputFunction( const InternalMessage &msg )
{
	if (createOutput == 1) { 
		createOutput = 0;
		if (pState == 1) { 
			Yp = p11*Ypd+p12*Ypdd+p13*U;
		}
		if (pState == 2) { 
			Yp = p21*Ypd+p22*Ypdd+p23*U;
		}
		if (pState == 3) { 
			Yp = p31*Ypd+p32*Ypdd+p33*U;
		}		
		sendOutput( msg.time(), Ypout, Yp ) ;
	}
	return *this ;
}

