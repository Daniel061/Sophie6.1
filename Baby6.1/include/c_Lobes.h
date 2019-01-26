#ifndef C_LOBES_H
#define C_LOBES_H

#include <c_MemoryCell.h>
#include <unordered_map>

#include <iostream>
#include <string>

extern bool Verbose;

class c_Lobes : public c_MemoryCell
{
    public:
        c_Lobes();
        virtual ~c_Lobes();

    protected:

    private:
        unordered_map <int, c_MemoryCell> RightLobeMemoryMap;
        unordered_map <int, c_MemoryCell> LeftLobeMemoryMap;
        unordered_map <int, c_MemoryCell>::iterator mapIT;
        c_MemoryCell WorkingCell;

            /* Private Function to search the map to see if
               the address (token value of the data) exists.
               if it does, modifies the address of the bool at Result to TRUE and
               ALWAYS returns the iterator.
               = end() if not found.
            */
            unordered_map <int, c_MemoryCell>::iterator FindAddressInMap(int Address, bool &Result, char SideToCheck = 'r'){
            Result = false;
            if(SideToCheck == 'r'){
                mapIT = RightLobeMemoryMap.find(Address);
                if(mapIT != RightLobeMemoryMap.end())Result = true;
                }
            else{
                mapIT = LeftLobeMemoryMap.find(Address);
                if(mapIT != LeftLobeMemoryMap.end())Result = true;
            }
            return mapIT;
        }

    public:

        //Updates ContractionLongFormFirst if exists
        //returns True if added, else false if updated
        //send LongFormFirst data in strData and the address of the contraction word in Address
        bool SetMemoryCellContractionLongFormFirst(string strData,int Address, char SideToCheck = 'r'){
           bool Result = false;
           mapIT       = FindAddressInMap(Address, Result, SideToCheck);
               if (!Result){
                  WorkingCell.SetpCellContractionLongFormFirst(strData);
                  RightLobeMemoryMap.emplace(Address,WorkingCell);
                  Result = true;}
                  else{
                    mapIT->second.SetpCellContractionLongFormFirst(strData);}
               return Result;
        }


        //Updates ContractionLongFormSecond if exists
        //returns True if added, else false if updated
        //send LongFormSecond data in strData and the address of the contraction word in Address
        bool SetMemoryCellContractionLongFormSecond(string strData,int Address, char SideToCheck = 'r'){
           bool Result = false;
           mapIT       = FindAddressInMap(Address, Result, SideToCheck);
               if (!Result){
                  WorkingCell.SetpCellContractionLongFormSecond(strData);
                  RightLobeMemoryMap.emplace(Address,WorkingCell);
                  Result = true;}
                  else{
                    mapIT->second.SetpCellContractionLongFormSecond(strData);}
               return Result;
        }



        //Gets ContractionLongFormFirst if exists
        //returns the data if exits, else "" if not found
        //send the address of the contraction word in Address
        string GetMemoryCellContractionLongFormFirst(int Address, char SideToCheck = 'r'){
           bool Result    = false;
           string strData = "";
           mapIT       = FindAddressInMap(Address, Result, SideToCheck);
               if (Result){
                 strData =  mapIT->second.GetpCellContractionLongFormFirst();}
                return strData;

        }


        //Gets ContractionLongFormSecond if exists
        //returns the data if exits, else "" if not found
        //send the address of the contraction word in Address
        string GetMemoryCellContractionLongFormSecond(int Address, char SideToCheck = 'r'){
           bool Result    = false;
           string strData = "";
           mapIT       = FindAddressInMap(Address, Result, SideToCheck);
               if (Result){
                 strData =  mapIT->second.GetpCellContractionLongFormSecond();}
                return strData;

        }


        //Updates the RawStringData if exists, adds it if it doesn't exist
        //returns True if added, else false if updated
        bool SetMemoryCellRawStringData(string strData, int Address, char SideToCheck = 'r'){
            bool Result = false;
            mapIT       = FindAddressInMap(Address, Result, SideToCheck);
                if(!Result){
                    WorkingCell.SetpCellDataString(strData);
                    RightLobeMemoryMap.emplace(Address,WorkingCell);
                    Result = true;}
                else{
                    mapIT->second.SetpCellDataString(strData);}
                return Result;
            }

        //Gets the RawStringData if exists,
        //returns the string value, else bool address of Result modified to false if not found
        string GetMemoryCellRawStringData( bool &Result, string strData = "", int Address = -1, char SideToCheck = 'r'){
            Result           = false;
            string RawString = "";
                if(Address != -1){
                    mapIT        = FindAddressInMap(Address,Result,SideToCheck);}
                else{
                    mapIT        = FindAddressInMap(Tokenize(strData), Result, SideToCheck);}
                if(Result){
                    RawString = mapIT->second.GetpCellDataString(); // WorkingCell.GetpCellDataString();
                    Result = true;}

                return RawString;
            }

        //Updates the LowerCaseStringData if exists, adds it if it doesn't exist
        //returns True if added, else false if updated
        bool SetMemoryCellLCStringData(string strData, int Address, char SideToCheck = 'r'){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result,SideToCheck);
                if(!Result){
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(strData);
                    RightLobeMemoryMap.emplace(Address,WorkingCell);
                    Result = true;}
                else{
                    mapIT->second.SetpCellDataString(strData);}
                return Result;
            }

        //Returns NULL if doesn't exist, else returns CellWordType
        char GetMemoryCellWordType(int Address){
            char Result;
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult);
                if(!SearchResult){
                    Result = '\0';}
                else{
                   Result = mapIT->second.GetpWordType();}
            return Result;
        }


        //Returns NULL if doesn't exist, else returns CellWordDataLC
        string GetMemoryCellWordLC(string WordInUC, int Address = -1, char SideToCheck = 'r'){
            if(Address == -1) Address = Tokenize(WordInUC);
            string Result = "";
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult,SideToCheck);
                if(!SearchResult){
                    Result = "";}
                else{
                   Result = mapIT->second.GetpCellDataLC();}
            return Result;
        }

        //Returns TRUE if exist and the the WordType was set, else returns false
        bool SetMemoryCellWordType(int Address,char WordTypeToSet){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    mapIT->second.SetpWordType(WordTypeToSet);
                    Result = true;}
            return Result;
        }

        //Returns TRUE if exist and the the Purpose was set, else returns false
        bool SetMemoryCellPurpose(int Address,char CellPurpose){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    mapIT->second.SetpCellPurpose (CellPurpose);
                    Result = true;}
            return Result;
        }

        //Returns char cell purpose
        char GetMemoryCellPurpose(int Address){
            bool Result = false;
            char CellPurpose = '\0';
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    CellPurpose = mapIT->second.GetpCellPurpose();
                    Result      = true;}
            return CellPurpose;
        }

        //Returns -1 if cell doesn't exist else returns pointer to next pattern;
        int GetMemoryCellPointerToNextPattern(int Address,char SideToCheck = 'l'){
            int Result        = -1;
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult,SideToCheck);
                if(SearchResult){
                    Result = mapIT->second.GetpPointerToNextPattern();}
            return Result;
        }

        //Returns -1 if cell doesn't exist else sets the data and returns 0
        int SetMemoryCellPointerToNextPattern(int Address, int PointerToNextAddress, char SideToCheck = 'l'){
            int Result        = -1;
            bool SearchResult = false;
            mapIT = FindAddressInMap(Address,SearchResult,SideToCheck);
                if(SearchResult){
                    mapIT->second.SetpPointerToNextPattern(PointerToNextAddress);
                    Result = 0;}
            return Result;
        }

        //Returns NULL if cell doesn't exist, else returns char value of WordTense
        char GetMemoryCellWordTense(int Address){
            char Result       = '\0';
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult);
                if(SearchResult){
                    Result = mapIT->second.GetpWordTense();}
            return Result;
        }

        //Returns TRUE if exists and data is set, else returns false
        bool SetMemoryCellWordTense(int Address, char TenseToSet){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    mapIT->second. SetpWordTense(TenseToSet);
                    Result = true;}
            return Result;
        }

        //Returns TRUE if exists and data is set, else returns false
        bool SetMemoryCellGenderClass(int Address, char GenderToSet){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    mapIT->second.SetpGenderClass(GenderToSet);
                    Result = true;}
            return Result;
        }

        //Returns char GenderClass from memory cell
        char GetMemoryCellGenderClass(int Address){
            bool Result = false;
            char Gender = '\0';
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    Gender = mapIT->second.GetpGenderClass();
                    Result = true;}
            return Gender;
        }

        //Returns -1 if doesn't exist, else returns adjective count
        int GetMemoryCellAdjectiveCount(int Address){
            int Result        = -1;
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult);
                if(SearchResult){
                    Result = mapIT->second.GetNumberOfAdjectivesInMap();}
            return Result;
        }

        //Checks to see if there is a memorycell for the Address given.
        //returns true if so, if not returns false.
        bool GetMemoryCellIsSet(int Address,char SideToCheck = 'r'){
            bool Result = false;
            FindAddressInMap(Address,Result,SideToCheck);
            return Result;
        }


        //First checks to see if the cell at the address given exist.
        //if not, returns -1.
        //otherwise, returns the Adjective count and
        //by reference, the tokenized adjective value in the array Adjectives[]
        int GetMemoryCellAdjectives(int Address,int Adjectives[]){
            bool Result  = false;
            int  Count   = -1;
            mapIT        = FindAddressInMap(Address,Result);
                if(Result){
                   Count = mapIT->second.GetNumberOfAdjectivesInMap();
                   for(int x = 0; x<=(Count-1); x++){
                    Adjectives[x] = mapIT->second.GetAdjectiveFromMap(x);
                   }}
                 return Count;
        }


        //First checks to see if the cell at the address given exist.
        //if not, returns -1.
        //otherwise, returns the RelatedNoun count and
        //by reference, the tokenized RelatedNoun value in the array RelatedNouns[]
        int GetMemoryCellRelatedNouns(int Address,int RelatedNouns[]){
            bool Result  = false;
            int  Count   = -1;
            mapIT        = FindAddressInMap(Address,Result);
                if(Result){
                   Count = mapIT->second.GetNumberOfRelatedNounsInMap();
                   for(int x = 0; x<=(Count-1); x++){
                    RelatedNouns[x] = mapIT->second.GetNounFromMap(x);
                   }}
                 return Count;
        }




        //First checks to see if the cell at the address given exist.
        //if not, returns -1.
        //otherwise, returns the Verb count and
        //by reference, the tokenized Verb value in the array Verbs[]
        int GetMemoryCellVerbs(int Address,int Verbs[]){
            bool Result  = false;
            int  Count   = -1;
            mapIT        = FindAddressInMap(Address,Result);
                if(Result){
                   Count = mapIT->second.GetNumberOfVerbsInMap();
                   for(int x = 0; x<=(Count-1); x++){
                    Verbs[x] = mapIT->second.GetVerbFromMap(x);
                   }}
                 return Count;
        }


         //First checks to see if the cell at the address given exist.
         //if not, returns -1.
         //otherwise, returns the Adverb count and
         //by reference, the tokenized Adverb value in the array Adverbs[]
         int GetMemoryCellAdverbs(int Address,int Adverbs[]){
             bool Result  = false;
             int  Count   = -1;
             mapIT        = FindAddressInMap(Address,Result);
                  if(Result){
                     Count = mapIT->second.GetNumberOfAdverbsInMap();
                     for(int x = 0; x<=(Count-1); x++){
                      Adverbs[x] = mapIT->second.GetAdverbFromMap(x);
                     }}
                   return Count;
          }



          //First makes sure the address given exists,
          //then associates adjective to the address given.
          //NOTE:will not duplicate Adjectives.
          bool AssociateMemoryCellAdjective(int Address, string AdjectiveToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateAdjectiveInMap(AdjectiveToAssociate);}
               return Result;
          }


          //First makes sure the address given exists,
          //then associates Noun to the address given.
          //NOTE:will not duplicate Nouns.
          bool AssociateMemoryCellNoun(int Address, string NounToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateNounInMap(NounToAssociate);}
               return Result;
          }



          //First makes sure the address given exists,
          //then associates Adverb to verb in the address given.
          //NOTE:will not duplicate Adverbs.
          bool AssociateMemoryCellAdverbToVerb(int Address, string AdverbToAssociate, string VerbToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateAdverbToVerbInMap(AdverbToAssociate,VerbToAssociate);}
               return Result;

          }


          //First makes sure the address given exists,
          //then associates Verb to adjective in the address given.
          //NOTE:will not duplicate Adverbs.
          bool AssociateMemoryCellVerbToAdjective(int Address, string AdverbToAssociate, string VerbToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateAdverbToVerbInMap(AdverbToAssociate,VerbToAssociate);}
               return Result;
          }


          //First Checks to see if cell address given exists,
          //if so, checks to see if NounToCheck is related to this cell address.
          //Returns true if so, false if not or cell doesn't exist
          bool GetIsNounRelatedToThisMemoryCell(int Address, string NounToCheck){
               bool Result = false;
               mapIT       = FindAddressInMap(Address,Result);
                   if(Result){
                      Result = mapIT->second.IsNounRelatedToMe(NounToCheck);}
               return Result;
          }


          //returns the Memory cell count in RightLobe memory map
          int GetRightLobeCellCount(){
              return RightLobeMemoryMap.size();
          }

          //returns the Memory cell count in LeftLobe memory map
          int GetLeftLobeCellCount(){
              return LeftLobeMemoryMap.size();
          }



          //Checks to see if the NewWord exists first,
          //if so AND Update = true, Updates the data, returns Installed = false.
          //If NewWord doesn't exist,
          //Stores all the data and returns Installed = true.
          bool InstallNewWord(string NewWord, char WordType, char Purpose, bool Update=false,
                              char GenderClass = 'u', string LongFormFirst = "", string LongFormSecond = "",
                              char SingularValue = 'u', int SingularRoot = 0){     //currently right side only
                if(Verbose)cout << "[c_Lobes.h::InstallNewWord]\n";
                int tmpToken     = 0;
                tmpToken         = Tokenize(NewWord);
                bool Result      = false;
                bool Installed   = false;
                string NewWordLC = MakeStringLowerCase(NewWord);
                mapIT            = FindAddressInMap(tmpToken,Result);
                if (!Result){
                            WorkingCell.InitializeAll();
                            WorkingCell.SetpCellDataString(NewWord);                        //stores raw data
                            WorkingCell.SetpWordType(WordType);                             //stores word type
                            WorkingCell.SetpCellPurpose(Purpose);                           //store cell purpose i.e 'w' - word
                            WorkingCell.SetpCellDataLC(NewWordLC);                          //store the raw data in lower case
                            WorkingCell.SetpGenderClass(GenderClass);                       //store the gender class
                            WorkingCell.SetpCellContractionLongFormFirst(LongFormFirst);    //store the contraction word long form
                            WorkingCell.SetpCellContractionLongFormSecond(LongFormSecond);  //store the contraction word long form
                            WorkingCell.SetpCellIsSingular(SingularValue);                  //store p - plural s - singular u - undetermined
                            WorkingCell.SetpSingularLocation(SingularRoot);                 //address of root i.e. address of "color" for "colors"
                            RightLobeMemoryMap.emplace(tmpToken,WorkingCell);               //Add this new cell to map.
                            Installed = true;                                               //flag this operation as happened.
                            if(Verbose)
                             cout << "Storing new word-->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;
                            }
                        else
                            if(Update){
                                mapIT->second.SetpCellDataString(NewWord);
                                mapIT->second.SetpWordType(WordType);
                                mapIT->second.SetpCellPurpose(Purpose);
                                mapIT->second.SetpCellDataLC(NewWordLC);
                                mapIT->second.SetpGenderClass(GenderClass);
                                mapIT->second.SetpCellContractionLongFormFirst(LongFormFirst);
                                mapIT->second.SetpCellContractionLongFormSecond(LongFormSecond);
                                mapIT->second.SetpCellIsSingular(SingularValue);
                                mapIT->second.SetpSingularLocation(SingularRoot);
                                if(Verbose)
                                    cout << "Updating -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;
                            }
                            else
                                if(Verbose)
                                 cout << "Not Storing -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;


                         return Installed;
        }


          bool CheckLinkOfTwoNounsWithAdjectives(string FirstNoun,string SecondNoun, string& VerbUsage, string MatchedAdjective[], int& MatchedCount){


                   VerbUsage           = "";
                   for(int x = 0; x<15; x++) MatchedAdjective[x] = "";
                   bool Result; Result = false;
                   int FirstNounAdjectiveCount,SecondNounAdjectiveCount;
                   int TokenFirstNoun,TokenSecondNoun;
                   int AdjectiveMatches; AdjectiveMatches = 0;
                   int AdjectivesFirstNoun[20];
                   int AdjectivesSecondNoun[20];
                   int Verbs[20];
                   TokenFirstNoun           = Tokenize(FirstNoun);
                   TokenSecondNoun          = Tokenize(SecondNoun);
                   FirstNounAdjectiveCount  = GetMemoryCellAdjectives(TokenFirstNoun,AdjectivesFirstNoun);
                   SecondNounAdjectiveCount = GetMemoryCellAdjectives(TokenSecondNoun,AdjectivesSecondNoun);

                   if((FirstNounAdjectiveCount == 0) | (SecondNounAdjectiveCount == 0)){
                      //can't match, no adjectives to compare
                      //returns empty strings and false.
                      }
                   else{
                      for(int x = 0; x < FirstNounAdjectiveCount; x++){
                        for(int y = 0; y < SecondNounAdjectiveCount; y++){
                            if(AdjectivesFirstNoun[x] == AdjectivesSecondNoun[y]){
                                Result                                = true;
                                //intMatchedAdjective                   = AdjectivesFirstNoun[x];
                                MatchedAdjective[AdjectiveMatches]    = GetMemoryCellWordLC("",AdjectivesFirstNoun[x]);
                                //intVerbUsage                          = GetMemoryCellVerbs(intMatchedAdjective,Verbs);
                                VerbUsage                             = Verbs[0];
                                AdjectiveMatches++;}
                        } } }
                      MatchedCount = AdjectiveMatches;
                      return Result;
    }



          //stores Pre and Post Construction Patterns.
          //if doesn't exist, adds it
          //if does exist, updates it
          void SavePreAndPostPatternConstruction(string PreConstructionPattern,string PostConstructionPattern){

                int PreToken  = Tokenize(PreConstructionPattern,false);
                int PostToken = Tokenize(PostConstructionPattern,false);
                bool Result   = false;
                mapIT         = FindAddressInMap(PreToken,Result,'l');

                if(!Result){
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(PreConstructionPattern);
                    WorkingCell.SetpCellPurpose('1');    // pattern storage
                    WorkingCell.SetpToken(PreToken);
                    WorkingCell.SetpPointerToNextPattern(PostToken);
                    LeftLobeMemoryMap.emplace(PreToken,WorkingCell);
                    mapIT  = FindAddressInMap(PostToken,Result,'l');
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(PostConstructionPattern);
                    WorkingCell.SetpCellPurpose('1');    //pattern storage
                    WorkingCell.SetpToken(PostToken);
                    WorkingCell.SetpPointerToNextPattern(PostToken);
                    LeftLobeMemoryMap.emplace(PostToken,WorkingCell);
                }
                else{
                     mapIT->second.SetpCellDataString(PreConstructionPattern);
                     mapIT->second.SetpCellPurpose('1');    // pattern storage
                     mapIT->second.SetpToken(PreToken);
                     mapIT->second.SetpPointerToNextPattern(PostToken);

                     mapIT  = FindAddressInMap(PostToken,Result,'l');
                     if(Result){
                         mapIT->second.SetpCellDataString(PostConstructionPattern);
                         mapIT->second.SetpCellPurpose('1');    //pattern storage
                         mapIT->second.SetpToken(PostToken);
                         mapIT->second.SetpPointerToNextPattern(PostToken);}
                         else{
                            WorkingCell.InitializeAll();
                            WorkingCell.SetpCellDataString(PostConstructionPattern);
                            WorkingCell.SetpCellPurpose('1');    //pattern storage
                            WorkingCell.SetpToken(PostToken);
                            WorkingCell.SetpPointerToNextPattern(PostToken);
                            LeftLobeMemoryMap.emplace(PostToken,WorkingCell);
                         }


                }

    }

            //Returns miniDefinition from memorycell
            //Returns "" if memorycell doesn't exist
            //can send string data or tokenized string data for address
            //currently rightside cells only, don't see a need for leftside yet

          string GetMemoryCellMiniDefinition(string strData = "", int Address = 0){
                bool Result = false;
                if(Address ==0) Address = Tokenize(strData);

                mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    return mapIT->second.GetpCellMiniDefinition();
                }
                else
                            return "";
          }

            //Sets the memorycell minidefinition if the memorycell exists
            //can send string data or the tokenized version of the string data for the address
          void SetMemoryCellMiniDefinition(string Definition, string strData = "", int Address = 0){
               bool Result = false;
               if (Address ==0) Address = Tokenize(strData);

               mapIT       = FindAddressInMap(Address,Result);
               if(Result){
                   mapIT->second.SetpCellMiniDefinition(Definition);
               }

          }


            //Returns pCellIsSingular from memorycell
            //Returns '\0' null, if memorycell doesn't exist
            //can send string data or tokenized string data for address
            //currently right side cells only, don't see a need for left side yet

          char GetMemoryCellpCellIsSingular(string strData = "", int Address = 0){
                bool Result = false;
                if(Address ==0) Address = Tokenize(strData);

                mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    return mapIT->second.GetpCellIsSingular();
                }
                else
                return '\0';}

            //Sets pCellIsSingular in memorycell
            //if memorycell exist
            //can send string data or tokenized string data for address
            //currently right side cells only, don't see a need for left side yet

          void SetMemoryCellpCellIsSingular(char newData, string strData = "", int Address = 0){
                bool Result = false;
                if(Address ==0) Address = Tokenize(strData);

                mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    return mapIT->second.SetpCellIsSingular(newData);
                }}


            //Returns pSingularLocation from memorycell
            //Returns 0 , if memorycell doesn't exist
            //can send string data or tokenized string data for address
            //currently right side cells only, don't see a need for left side yet

          int GetMemoryCellpSingularLocation(string strData = "", int Address = 0){
                bool Result = false;
                if(Address ==0) Address = Tokenize(strData);

                mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    return mapIT->second.GetpSingularLocation();
                }
                else
                return 0;}

            //Sets pSingularLocation from memorycell
            //if memorycell exist
            //can send string data or tokenized string data for address
            //send int for new location
            //currently right side cells only, don't see a need for left side yet

          void SetMemoryCellpSingularLocation(int newLocation, string strData = "", int Address = 0){
                bool Result = false;
                if(Address ==0) Address = Tokenize(strData);

                mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    return mapIT->second.SetpSingularLocation(newLocation);
                }
                }

        int Tokenize (string str_Data,bool ForceLowerCase = true)
        {
            int z;
            int y;
            int PlaceValue;
            int tmpToken;

                z = str_Data.size();
                PlaceValue = 1;
                tmpToken = 0;
                if(ForceLowerCase){
                for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(tolower(str_Data[y-1])))*PlaceValue;
                    PlaceValue ++;}}
                  else {
                    for( y = z; y > 0; y--){
                    tmpToken = tmpToken + (int(str_Data[y-1]))*PlaceValue;
                    PlaceValue ++;}
                  }

            return tmpToken;

        }

        string MakeStringLowerCase(string strData){
            for(int x =0; x<= int(strData.size()); x++)
                strData[x] = tolower(strData[x]);
            return strData;
        }
};


#endif // C_LOBES_H
