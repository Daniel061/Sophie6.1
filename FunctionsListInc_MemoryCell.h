    public:
        int    GetPointerToNextPattern(){return PointerToNextPattern;}
        char   GetWordTense() {return WordTense;}		
        int    GetAdjectiveCount(){return AdjectiveCount;}
        char   GetSecondaryType(){return SecondaryType;}
        char   GetAlternateType(){return AlternateType;}
        string GetpCellDataString(){return pCellData;}
        string GetpCellDataLC(){return pCellDataLC;}
        char   GetpCellPurpose(){return pCellPurpose;}
        char   GetpWordType(){return pWordType;}
        bool   GetpIsRoot(){return pIsRoot;}
        int    GetpNextVerb(){return pNextVerb;}
        int    GetpNextNoun(){return pNextNoun;}
        int    GetpToken(){return pToken;}
        bool   GetpIsSet() {return pIsSet;}		
        char   GetGenderClass(){return GenderClass;}
        string GetGivenName(){return GivenName;}
		int    GetAdjective(int Location)		
		int    GetNumberOfAdjectivesInMap()
		int    GetNumberOfVerbsInMap()
		int    GetNumberOfAdverbsInMap()
		int    GetNumberOfRelatedNounsInMap()
		int    GetAdjectiveFromMap(int Location)
		int    GetVerbFromMap(int Location)
		int    GetAdverbFromMap(int Location)
		int    GetNounFromMap(int Location)
		
		
        void   SetPointerToNextPattern(int NextPattern){PointerToNextPattern = NextPattern;}
        void   SetWordTense(char newTense){WordTense = newTense;}
        void   SetSecondaryType(char Type){SecondaryType = Type;}
        void   SetAlternateType(char Type){AlternateType = Type;}
        void   SetpCellDataLC(string newData){pCellDataLC=newData;}
        void   SetpCellPurpose (char NewData){pCellPurpose = NewData;}
        void   SetpWordType(char NewData){pWordType = NewData;}
        void   SetpIsRoot(bool NewVal){pIsRoot = NewVal;}
        void   SetpNextVerb(int NewVal){pNextVerb = NewVal;}
        void   SetpToken(int NewVal){pToken=NewVal;}
        void   SetGenderClass(char NewClass){GenderClass = NewClass;}
        void   SetGivenName(string NewName){GivenName = NewName;}
        void   SetpCellDataString(string NewData){pCellData = NewData; pIsSet = true;}
		
		void   AccociateAdjective(int NewAdjective)
		void   AccociateAdjectiveWithVerb(int NewVerb,int AdjectiveToAssociate, int AdverbToAssociate = -1)
		void   AssociateAdjectiveInMap(string AdjectiveToAssociate)
		void   AssociateNounInMap(string NounToAssociate)
		void   AssociateVerbToAdjectiveInMap(string AdjectiveToAssociate, string VerbToAssociate)
		void   AssociateAdverbToVerbInMap(string AdverbToAssociate,string VerbToAssociate)

		bool   IsNounRelatedToMe(string NounToCheck)

		int    Tokenize (string str_Data, bool ForceLowerCase=true)
		
		
		
		
		