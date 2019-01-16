#include "c_MemoryCell.h"

c_MemoryCell::c_MemoryCell()
{
    //ctor
    pCellData = "";
    pCellDataLC = "";
    pCellPurpose = 'u'; //undefined
    pWordType    = 'u';
    pIsRoot = false;
    pNextVerb = 0;
    pNextNoun = 0;
    pToken = 0;
    pIsSet = false;
    GenderClass = 'n';
    SecondaryType = 'u';
    AlternateType = 'u';
    advDescriptors.clear();
    verbDescriptors.clear();
    adjDescriptors.clear();
    PointerToNextPattern = 0;
}

c_MemoryCell::~c_MemoryCell()
{
    //dtor
}
