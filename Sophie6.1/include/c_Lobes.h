#ifndef C_LOBES_H
#define C_LOBES_H

#include <c_MemoryCell.h>
#include <unordered_map>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

extern bool   Verbose;
extern string Version;



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
        unordered_map <int, c_MemoryCell>::iterator fileIT;
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


        //returns number of days since beginning of 2019 for a day stamp
        int GetDaysSinceDate(){

            struct  tm StartDate;
            time_t  startTime,Finish;
            time (&Finish);
            time (&startTime);
            StartDate           = *localtime(&startTime);
            StartDate.tm_year   = 2019;
            StartDate.tm_mon    = 0;
            StartDate.tm_mday   = 1;
            StartDate.tm_hour   = 0;
            StartDate.tm_min    = 0;
            StartDate.tm_sec    = 0;
            return StartDate.tm_yday;

        }


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

        //Returns 'u' if doesn't exist, else returns CellWordType
        char GetMemoryCellWordType(int Address){
            char Result = 'u';
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult);
                if(!SearchResult){
                    Result = 'u';}
                else{
                   Result = mapIT->second.GetpCellWordType();}
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
                    mapIT->second.SetpCellWordType(WordTypeToSet);
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
            char CellPurpose = 'u';
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
                    Result = mapIT->second.GetpCellPointerToNextPattern();}
            return Result;
        }

        //Returns -1 if cell doesn't exist else sets the data and returns 0
        int SetMemoryCellPointerToNextPattern(int Address, int PointerToNextAddress, char SideToCheck = 'l'){
            int Result        = -1;
            bool SearchResult = false;
            mapIT = FindAddressInMap(Address,SearchResult,SideToCheck);
                if(SearchResult){
                    mapIT->second.SetpCellPointerToNextPattern(PointerToNextAddress);
                    Result = 0;}
            return Result;
        }

        //Returns NULL if cell doesn't exist, else returns char value of WordTense
        char GetMemoryCellWordTense(int Address){
            char Result       = 'u';
            bool SearchResult = false;
            mapIT             = FindAddressInMap(Address,SearchResult);
                if(SearchResult){
                    Result = mapIT->second.GetpCellWordTense();}
            return Result;
        }

        //Returns TRUE if exists and data is set, else returns false
        bool SetMemoryCellWordTense(int Address, char TenseToSet){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    mapIT->second. SetpCellWordTense(TenseToSet);
                    Result = true;}
            return Result;
        }

        //Returns TRUE if exists and data is set, else returns false
        bool SetMemoryCellGenderClass(int Address, char GenderToSet){
            bool Result = false;
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    mapIT->second.SetpCellGenderClass(GenderToSet);
                    Result = true;}
            return Result;
        }

        //Returns char GenderClass from memory cell
        char GetMemoryCellGenderClass(int Address){
            bool Result = false;
            char Gender = 'u';
            mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    Gender = mapIT->second.GetpCellGenderClass();
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

///====================================================================================
          //First Checks to see if cell address given exists,
          //if so, checks to see if AdjectiveToCheck is associated to this cell address.
          //Returns true if so, false if not or cell doesn't exist
          bool GetIsAdjectiveAssociatedToThisMemoryCell(int Address, string AdjectiveToCheck){
               bool Result = false;
               mapIT       = FindAddressInMap(Address,Result);
                   if(Result){
                      Result = mapIT->second.IsAdjectiveAssociatedToMe(AdjectiveToCheck);}
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
                            WorkingCell.SetpCellWordType(WordType);                         //stores word type
                            WorkingCell.SetpCellPurpose(Purpose);                           //store cell purpose i.e 'w' - word
                            WorkingCell.SetpCellDataLC(NewWordLC);                          //store the raw data in lower case
                            WorkingCell.SetpCellGenderClass(GenderClass);                   //store the gender class
                            WorkingCell.SetpCellContractionLongFormFirst(LongFormFirst);    //store the contraction word long form
                            WorkingCell.SetpCellContractionLongFormSecond(LongFormSecond);  //store the contraction word long form
                            WorkingCell.SetpCellIsSingular(SingularValue);                  //store p - plural s - singular u - undetermined
                            WorkingCell.SetpCellSingularLocation(SingularRoot);             //address of root i.e. address of "color" for "colors"
                            WorkingCell.SetpCellToken(Tokenize(NewWord));                   //store the token value of the word
                            RightLobeMemoryMap.emplace(tmpToken,WorkingCell);               //Add this new cell to map.
                            Installed = true;                                               //flag this operation as happened.
                            if(Verbose)
                             cout << "Storing new word-->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;
                            }
                        else
                            if(Update){
                                mapIT->second.SetpCellDataString(NewWord);
                                mapIT->second.SetpCellWordType(WordType);
                                mapIT->second.SetpCellPurpose(Purpose);
                                mapIT->second.SetpCellDataLC(NewWordLC);
                                mapIT->second.SetpCellGenderClass(GenderClass);
                                mapIT->second.SetpCellContractionLongFormFirst(LongFormFirst);
                                mapIT->second.SetpCellContractionLongFormSecond(LongFormSecond);
                                mapIT->second.SetpCellIsSingular(SingularValue);
                                mapIT->second.SetpCellSingularLocation(SingularRoot);
                                mapIT->second.SetpCellToken(Tokenize(NewWord));
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
          void SavePreAndPostPatternConstruction(string PreConstructionPattern,string PostConstructionPattern, int PostToken = 0){

                int PreToken  = Tokenize(PreConstructionPattern,false);
                if (PostToken == 0)
                    PostToken = Tokenize(PostConstructionPattern,false);
                bool Result   = false;
                mapIT         = FindAddressInMap(PreToken,Result,'l');

                if(!Result){
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(PreConstructionPattern);
                    WorkingCell.SetpCellPurpose('1');    // pattern storage
                    WorkingCell.SetpCellToken(PreToken);
                    WorkingCell.SetpCellPointerToNextPattern(PostToken);
                    LeftLobeMemoryMap.emplace(PreToken,WorkingCell);
                    mapIT  = FindAddressInMap(PostToken,Result,'l');
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(PostConstructionPattern);
                    WorkingCell.SetpCellPurpose('1');    //pattern storage
                    WorkingCell.SetpCellToken(PostToken);
                    WorkingCell.SetpCellPointerToNextPattern(PostToken);
                    LeftLobeMemoryMap.emplace(PostToken,WorkingCell);
                }
                else{
                     mapIT->second.SetpCellDataString(PreConstructionPattern);
                     mapIT->second.SetpCellPurpose('1');    // pattern storage
                     mapIT->second.SetpCellToken(PreToken);
                     mapIT->second.SetpCellPointerToNextPattern(PostToken);

                     mapIT  = FindAddressInMap(PostToken,Result,'l');
                     if(Result){
                         mapIT->second.SetpCellDataString(PostConstructionPattern);
                         mapIT->second.SetpCellPurpose('1');    //pattern storage
                         mapIT->second.SetpCellToken(PostToken);
                         mapIT->second.SetpCellPointerToNextPattern(PostToken);}
                         else{
                            WorkingCell.InitializeAll();
                            WorkingCell.SetpCellDataString(PostConstructionPattern);
                            WorkingCell.SetpCellPurpose('1');    //pattern storage
                            WorkingCell.SetpCellToken(PostToken);
                            WorkingCell.SetpCellPointerToNextPattern(PostToken);
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
                    return mapIT->second.GetpCellSingularLocation();
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
                    return mapIT->second.SetpCellSingularLocation(newLocation);
                }
                }



        string MakeStringLowerCase(string strData){
            for(int x =0; x<= int(strData.size()); x++)
                strData[x] = tolower(strData[x]);
            return strData;
        }

        int Tokenize (string str_Data,bool ForceUpperCase = true)
        {
            int z          = str_Data.size();
            int y;
            int PlaceValue = 1;
            int tmpToken   = 0;
            int tmpHolder  = 0;

                if(ForceUpperCase){
                for( y = z; y > 0; y--){
                    tmpHolder  = int(toupper(str_Data[y-1]))-64; //'A' to 'Z'
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}}
                  else {
                    for( y = z; y > 0; y--){
                    tmpHolder  = str_Data[y-1] - 64;
                    if(tmpHolder <= 0) tmpHolder = str_Data[y-1];
                    tmpToken   = tmpToken + (tmpHolder*PlaceValue);
                    PlaceValue = PlaceValue * 10;}
                  }

            return tmpToken;

        }

        void LobesStoreTheLearnedWords(){
            string Delim            = "\n";
            int    Count            = 0;
            ofstream LearnedDataFile ("LearnedData.dat", ios::out);
            if (LearnedDataFile.is_open()){
                    LearnedDataFile << "VERSION " << Version << ", file version" << Delim;
                for(fileIT = RightLobeMemoryMap.begin(); fileIT != RightLobeMemoryMap.end(); fileIT++ ){
                    LearnedDataFile << "Original string,"     << fileIT->second.GetpCellDataString() << Delim;
                    LearnedDataFile << "Lower Case string,"   << fileIT->second.GetpCellDataLC() << Delim;
                    LearnedDataFile << "Given name,"          << fileIT->second.GetpCellGivenName() << Delim;
                    LearnedDataFile << "Mini Def.,"           << fileIT->second.GetpCellMiniDefinition() << Delim;
                    LearnedDataFile << "Contraction 1st,"     << fileIT->second.GetpCellContractionLongFormFirst() << Delim;
                    LearnedDataFile << "Contraction 2nd,"     << fileIT->second.GetpCellContractionLongFormSecond() << Delim;
                    LearnedDataFile << "Cell purpose,"        << fileIT->second.GetpCellPurpose() << Delim;
                    LearnedDataFile << "Word Type,"           << fileIT->second.GetpCellWordType() << Delim;
                    LearnedDataFile << "Word tense,"          << fileIT->second.GetpCellWordTense() << Delim;
                    LearnedDataFile << "Secondary type,"      << fileIT->second.GetpCellSecondaryType() << Delim;
                    LearnedDataFile << "Alternate type,"      << fileIT->second.GetpCellAlternateType() << Delim;
                    LearnedDataFile << "Gender class,"        << fileIT->second.GetpCellGenderClass() << Delim;
                    LearnedDataFile << "Is root,"             << fileIT->second.GetpCellIsRoot() << Delim;
                    LearnedDataFile << "Is Set,"              << fileIT->second.GetpCellIsSet() << Delim;
                    LearnedDataFile << "Is Singular,"         << fileIT->second.GetpCellIsSingular() << Delim;
                    LearnedDataFile << "Singular location,"   << fileIT->second.GetpCellSingularLocation() << Delim;
                    LearnedDataFile << "Next Verb,"           << fileIT->second.GetpCellNextVerb() << Delim;
                    LearnedDataFile << "Next Noun,"           << fileIT->second.GetpCellNextNoun() << Delim;
                    LearnedDataFile << "Token,"               << fileIT->second.GetpCellToken() << Delim;
                    LearnedDataFile << "Next Pattern,"        << fileIT->second.GetpCellPointerToNextPattern() << Delim;

                Count = fileIT->second.GetNumberOfAdjectivesInMap();
                LearnedDataFile << "Number of Adjectives,"    << Count << Delim;
                for (int x = 0; x <= Count-1; x++){
                    LearnedDataFile << "Adjective,"           << GetMemoryCellWordLC("",fileIT->second.GetAdjectiveFromMap(x)) << Delim;
                }
                Count = fileIT->second.GetNumberOfVerbsInMap();
                LearnedDataFile << "Nunber of Verbs,"         << Count << Delim;
                for (int x = 0; x<=Count-1; x++){
                    LearnedDataFile << "Verb,"                << GetMemoryCellWordLC("",fileIT->second.GetVerbFromMap(x)) << Delim;
                }
                Count = fileIT->second.GetNumberOfAdverbsInMap();
                LearnedDataFile << "Number of Adverbs,"       << Count << Delim;
                for (int x = 0; x<=Count-1; x++){
                    LearnedDataFile << "Adverb,"              << GetMemoryCellWordLC("",fileIT->second.GetAdverbFromMap(x)) << Delim;
                }
                Count = fileIT->second.GetNumberOfRelatedNounsInMap();
                LearnedDataFile << "Related Nouns,"           << Count << Delim;
                for (int x = 0; x<=Count-1; x++){
                    LearnedDataFile << "Noun,"                << GetMemoryCellWordLC("", fileIT->second.GetNounFromMap(x)) << Delim;
                }
                 //++mapIT;
                }//end of loop of Words to store
            }//end if open
          LearnedDataFile.close();

          ofstream PatternFile ("PatternWorkLearned.dat", ios::out);
          if(PatternFile.is_open()){
                PatternFile << "VERSION " << Version << Delim;
                for(fileIT = LeftLobeMemoryMap.begin(); fileIT != LeftLobeMemoryMap.end(); fileIT++ ){
                    PatternFile << fileIT->second.GetpCellDataString() << Delim;
                    PatternFile << fileIT->second.GetpCellPointerToNextPattern() << Delim;
                }
          }
          PatternFile.close();

        }//end store memory cells


        void LobesReadTheLearnedWords(){
                //ensure datafile version is the same as our version, if not, delete the file
                string     strLineData     = "";
                int        Count           = 0;
                ifstream LearnedDataFile ("LearnedData.dat");
                string::size_type decType;
                cout << "..";
                if(LearnedDataFile.is_open()){
                        getline(LearnedDataFile,strLineData,',');
                        if(strLineData != "VERSION " + Version){
                            LearnedDataFile.close();
                            remove("LearnedData.dat");
                            strLineData = "";
                        }
                        else{ //skip to the data
                            getline(LearnedDataFile,strLineData);
                            getline(LearnedDataFile,strLineData,',');
                        }
                  while(strLineData != ""){
                        WorkingCell.InitializeAll();
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellDataString(strLineData);                        //set the original string data
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellDataLC(strLineData);                            //set the lower case string data
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellGivenName(strLineData);                         //set the given name string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellMiniDefinition(strLineData);                    //set the minidefinition string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellContractionLongFormFirst(strLineData);          //set the Contraction long form first string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellContractionLongFormSecond(strLineData);         //set the contraction long form second string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellPurpose(strLineData[0]);                        //set the char cell purpose
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellWordType(strLineData[0]);                       //set the char wordtype
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellWordTense(strLineData[0]);                      //set the char wordtense
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellSecondaryType(strLineData[0]);                  //set the char secondary type
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellAlternateType(strLineData[0]);                  //set the char alternate type
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellGenderClass(strLineData[0]);                    //set the char Gender class
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellIsRoot(stoi(strLineData,&decType));             //set the bool cell is root
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellIsSet(stoi(strLineData,&decType));              //set the bool pcellisSet
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellIsSingular(strLineData[0]);                     //set the char cell is singular
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellSingularLocation(stoi(strLineData,&decType));   //set the int singular location
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellNextVerb(stoi(strLineData,&decType));           //set the int next verb location
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellNextNoun(stoi(strLineData,&decType));           //set the int next noun location
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellToken(stoi(strLineData,&decType));              //set the int Token
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellPointerToNextPattern(stoi(strLineData,&decType)); //set the int pointer to next pattern
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);                                  //got number of adjectives
                        //count = adjective count
                        for(int x = 0; x< Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);                           //next store requires a string
                            WorkingCell.AssociateAdjectiveInMap(strLineData);
                        }//end for adjectives loop
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);
                        //Count = verb count
                        for(int x = 0; x< Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);
                            WorkingCell.AssociateVerbToAdjectiveInMap("",strLineData);
                        }//end for verbs loop
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);
                        //Count = adverb count
                        for(int x = 0; x < Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);
                            WorkingCell.AssociateAdverbToVerbInMap(strLineData,"");
                        }//end for adverbs loop
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);
                        //Count = Noun count
                        for(int x = 0; x < Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);
                        //if(WorkingCell.GetpCellDataLC() == "dog") cout << " Dog related noun =" << strLineData << endl;
                            WorkingCell.AssociateNounInMap(strLineData);
                        }//end for nouns loop
                    getline(LearnedDataFile,strLineData,',');
                    RightLobeMemoryMap.emplace(WorkingCell.GetpCellToken(),WorkingCell);

                    }//end while not empty loop

                }//end if open
              LearnedDataFile.close();
              cout << "..";

              ifstream PatternFile ("PatternWorkLearned.dat", ios::in);
              string SecondLineData = "";
              if(PatternFile.is_open()){
                    getline(LearnedDataFile,strLineData);
                    if(strLineData != "VERSION " + Version){
                        PatternFile.close();
                        remove("PatternWorkLearned.dat");
                    }
                    else{
                        getline(LearnedDataFile,strLineData);
                    }
                    while(strLineData != ""){
                        getline(LearnedDataFile,SecondLineData);
                        SavePreAndPostPatternConstruction(strLineData,"",stoi(SecondLineData,&decType));
                        getline(LearnedDataFile,strLineData);
                    }//end while loop
              }//end Pattern file
              PatternFile.close();
            cout << endl;
        }//end function
};


#endif // C_LOBES_H
