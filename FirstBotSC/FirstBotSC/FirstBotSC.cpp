// This is the main DLL file.

#include "FirstBotSC.h"

using namespace BWAPI;

void FirstBot :: onStart() {
  Broodwar->sendText("Hello world!");
}

void FirstBot :: onFrame() {

}