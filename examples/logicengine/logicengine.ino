#include "ReelTwo.h"
#include "dome/Logics.h"
#include "i2c/I2CReceiver.h"

// Front Logic Device (Jawa ID#1)
LogicEngineDeathStarFLD<> FLD(1, LogicEngineFLDDefault);
// Rear Logic Device (Jawa ID#2)
LogicEngineDeathStarRLDInverted<> RLD(2, LogicEngineRLDDefault);

// LogicEngineControllerDefault reads the trimpots on the back of the board. It is optional.
LogicEngineControllerDefault controller(FLD, RLD);

// Setup a i2c command receiver on address 0x10
I2CReceiver i2cReceiver(0x10);

void setup()
{
    REELTWO_READY();

    SetupEvent::ready();

    // Scroll text for 15 seconds before switching to normal mode
    FLD.selectScrollTextLeft("R2\n    D2", LogicEngineRenderer::kBlue, 1, 15);
    RLD.selectScrollTextLeft("... RSeries LogicEngine ....", LogicEngineRenderer::kYellow, 0, 15);
}

void loop()
{
	AnimatedEvent::process();
}
