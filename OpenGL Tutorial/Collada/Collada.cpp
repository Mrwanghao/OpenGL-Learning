#include "Collada.h"
#include "../tinyxml2/tinyxml2.h"

using namespace tinyxml2;

void Collada::readCollada()
{
	XMLDocument doc;
	doc.LoadFile("Dragon.dae");

}
