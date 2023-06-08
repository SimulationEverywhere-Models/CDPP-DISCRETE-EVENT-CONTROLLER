/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Shanta Ramchandani
*
*  EMAIL: mailto: shantar@sympatico.ca
*
*  DATE: October 20, 2003
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "interpLast.h" //class InterpLast
#include "genControl.h" //class GenControl
#include "plant.h" //class Plant
#include "unitDelay.h" //class UnitDelay
#include "model1.h" //class Model1
#include "model2.h" //class Model2
#include "model3.h" //class Model3


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<InterpLast>() , "InterpLast" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<GenControl>() , "GenControl" ) ;	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Plant>() , "Plant" ) ;	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<UnitDelay>() , "UnitDelay" ) ;	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Model1>() , "Model1" ) ;	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Model2>() , "Model2" ) ;	
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Model3>() , "Model3" ) ;				
}
