#ifndef DMRC_DES_STRINGBUILDERFACTORY_H
#define DMRC_DES_STRINGBUILDERFACTORY_H

#include "AimStringBuilder.h"
#include "ApplicationIdentifierStringBuilder.h"
#include "SerialStringBuilder.h"
#include "UsbOemStringBuilder.h"

namespace DigimarcEmbeddedSystems {

class StringBuilderFactory
{
public:
	StringBuilderFactory(int payloadVersion, int payloadSubtype);

	ApplicationIdentifierStringBuilder* GetBuilder(PosInterfaceType protocol) const;

private:
	int payloadVersion;
	int payloadSubtype;

	mutable ApplicationIdentifierStringBuilder builderNone;
	mutable SerialStringBuilder builderSerial;
	mutable AimStringBuilder builderIsoIecAim;
	mutable UsbOemStringBuilder builderUsbOem;
};
}

#endif
