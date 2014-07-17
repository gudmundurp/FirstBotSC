#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SCV/SCV.h"
#include "SCV/SCV_States.h"
#include "MockWorld.h"
#include <iostream>

TEST_CASE( "SCV starts in Idle state", "[SCV] [StartsInIdle]" ) {
    MockWorld world;
    SCV scv(0,&world);

    REQUIRE( scv.GetStateName() == "Idle" );

    scv.Update();

    REQUIRE( scv.GetStateName() == "Mining" );
}

TEST_CASE( "WHEN SCV executes Mining state it checks if it should Build Supply Depot", "[SCV] [MaybeBuildSD]" ) {
    MockWorld world;
    SCV scv(0,&world);

    REQUIRE( scv.GetStateName() == "Idle" );

    scv.Update();

    //Dont need to check if gathering minerals

    scv.Update();

    REQUIRE( scv.DidTryToBuildSupplyDepot() );

    std::cout << "\n\nI did try to build supply Depot: \n\t" << (scv.DidTryToBuildSupplyDepot() ? "True" : "False") << "\n";
}

SCENARIO( "SCV enters Build_Supply_Depot when 100 minerals and low supply", "[SCV] [EnterBuildSupplyDepotState]" ) {

    GIVEN( "100 minerals and 8/10 supply and an SCV in mining state" ) {
        MockWorld world;
        world.setMinerals(100);
        world.setSupplies(10);
        world.setUsedSupplies(8);

        SCV scv(0,&world);
        scv.GetSM()->ChangeState(Mining::Instance());

        THEN( "SCV should change to Build_SD when updating state and it should spend 100 minerals when started building") {
            scv.Update();

            #define B_SD "GoingToBuildSupplyDepot"

            INFO("SCV should have entered the " << B_SD << " state now");

            REQUIRE( scv.GetStateName() == B_SD );

            INFO("SCV should now have extracted 100 minerals from the bank");
            REQUIRE(0 == world.getMinerals());

            INFO("SCV should start building now ...");
            scv.Update();

            INFO("SCV should now be in BuildingSupplyDepot state");
            REQUIRE( scv.GetStateName() == "BuildingSupplyDepot" );
        }
    }

}
