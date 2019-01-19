#include "c_MemoryCell.h"

c_MemoryCell::c_MemoryCell()
{
    //ctor
    pCellData             = "";
    pCellDataLC           = "";
    pCellMiniDefinition   = "";
    pGivenName            = "";
    pCellPurpose          = 'u'; //undefined
    pWordType             = 'u';
    pIsRoot               = false;
    pNextVerb             = 0;
    pNextNoun             = 0;
    pToken                = 0;
    pIsSet                = false;
    pGenderClass          = 'u';
    pSecondaryType        = 'u';
    pAlternateType        = 'u';
    pCellIsSingular       = 'u';
    pWordTense            = 'u';
    pSingularLocation     = 0;
    advDescriptors.clear();
    verbDescriptors.clear();
    adjDescriptors.clear();
    pPointerToNextPattern = 0;
}

c_MemoryCell::~c_MemoryCell()
{
    //dtor
}
