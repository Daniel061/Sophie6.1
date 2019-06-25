#include "c_MemoryCell.h"

c_MemoryCell::c_MemoryCell()
{
    //ctor
    pCellData             = "";
    pCellDataLC           = "";
    pGivenName            = "";
    pCellPurpose          = 'u'; //undefined
    pWordType             = 'u';
    pIsRoot               = false;
    pNextVerb             = 0;
    pNextNoun             = 0;
    pToken                = 0;
    pDaysOld              = 0;
    pIsLocked             = false;
    pGenderClass          = 'u';
    pSecondaryType        = 'u';
    pAlternateType        = 'u';
    pCellIsSingular       = 'u';
    pWordTense            = 'u';
    pSingularLocation     = 0;
    pResolvedPattern      = "";
    pCellMiniDefinition.clear();
}

c_MemoryCell::~c_MemoryCell()
{
    //dtor
}
