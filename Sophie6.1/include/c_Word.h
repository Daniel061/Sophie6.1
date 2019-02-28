#ifndef C_WORD_H
#define C_WORD_H

#include <string>
#include <unordered_set>
using namespace std;
class c_Word
{
    public:
        c_Word();
        virtual ~c_Word();

    protected:
          string  w_WordForm                = "";    // the word data in its original form
          string  w_WordFormLC              = "";    // the word data in all lowercase
          string  w_ContractionFormFirst    = "";    // deconstructed contraction what's = what
          string  w_ContractionFormSecond   = "";    // deconstructed contraction what's = is
          string  w_SingularForm            = "";    // i.e. cats = cat
          string  w_PluralRoot              = "";    // deconstructed plural to the root,cars = car
          string  w_SubWord                 = "";    // replacement word, usually from subject
          string  w_PossessiveRoot          = "";    // cat's  = cat
          bool    w_isContraction           = false; // contraction flag
          bool    w_isPlural                = false; // plural flag
          bool    w_SingularPossessive      = false; // i.e. cat's
          bool    w_PluralPossessive        = false; // i.e. cats'
          int     w_QuoteLocation           = -1;    // location of quote if contraction
          int     w_WordTokens              = -1;    // depreciated
          char    w_PossessiveRootType      = 'u';   // usually a 'n' noun but not always
          char    w_WordType                = 'u';   // defines word type  u = unknown
          char    w_GenderClass             = 'u';   // defines gender     u = undefined
          char    w_PluralWordFlag          = 'u';   // s = singular p=plural u = undefined
          char    w_SecondaryType           = 'u';   // some words have more than 1 usage
          char    w_AlternativeType         = 'u';   // some words have more than 1 usage
          char    w_WordTense               = 'u';   // c - present p - past

          unordered_set <string> w_MiniDefinition;   // if this word is a subject, gist of sentence is here too
          unordered_set <string>::iterator SetIT;    // iterator
          unordered_set <string> w_Adjectives;       // adjectives used towards this word
          unordered_set <string> w_Adverbs;          // adverbs used towards this word
          unordered_set <string> w_RelatedNouns;     // Nouns related to this word

    private:


    public:


        void     Setw_MiniDefinition(string newVal){w_MiniDefinition.emplace(newVal);}
        int      Getw_MiniDefinitionCount(){return w_MiniDefinition.size();}
        string   Getw_MiniDefinition(int intWhich){
                 SetIT = w_MiniDefinition.begin();
                 for(int x = 0; x<=intWhich; x++) ++SetIT;
                 if(SetIT == w_MiniDefinition.end())
                    return "";
                 else
                    return *SetIT;}

        string   Getw_SingularForm(){return w_SingularForm;}
        void     Setw_SingularForm(string newVal){w_SingularForm = newVal;}

        bool     Getw_PluralPossessive(){return w_PluralPossessive;}
        void     Setw_PluralPossessive(bool newVal){w_PluralPossessive = newVal;}

        bool     Getw_SingularPossessive(){return w_SingularPossessive;}
        void     Setw_SingularPossessive(bool newVal){w_SingularPossessive = newVal;}

        string   Getw_WordForm(){return w_WordForm;}
        void     Setw_WordForm(string newVal){w_WordForm = newVal;}

        string   Getw_WordFormLC(){return w_WordFormLC;}
        void     Setw_WordFormLC(string newVal){w_WordFormLC = newVal;}

        string   Getw_ContractionFormFirst(){return w_ContractionFormFirst;}
        void     Setw_ContractionFormFirst(string newVal){w_ContractionFormFirst = newVal;}

        string   Getw_ContractionFormSecond(){return w_ContractionFormSecond;}
        void     Setw_ContractionFormSecond(string newVal){w_ContractionFormSecond = newVal;}

        string   Getw_PluralRoot(){return w_PluralRoot;}
        void     Setw_PluralRoot(string newVal){w_PluralRoot = newVal;}

        string   Getw_SubWord(){return w_SubWord;}
        void     Setw_SubWord(string newVal){w_SubWord = newVal;}

        bool     Getw_isContraction(){return w_isContraction;}
        void     Setw_isContraction(bool newVal){w_isContraction = newVal;}

        bool     Getw_isPlural(){return w_isPlural;}
        void     Setw_isPlural(bool newVal){w_isPlural = newVal;}

        int      Getw_QuoteLocation(){return w_QuoteLocation;}
        void     Setw_QuoteLocation(int newVal){w_QuoteLocation = newVal;}

        int      Getw_WordTokens(){return w_WordTokens;}
        void     Setw_WordTokens(int newVal){w_WordTokens = newVal;}

        char     Getw_WordType(){return w_WordType;}
        void     Setw_WordType(char newVal){w_WordType = newVal;}

        char     Getw_GenderClass(){return w_GenderClass;}
        void     Setw_GenderClass(char newVal){w_GenderClass = newVal;}

        char     Getw_PluralWordFlag(){return w_PluralWordFlag;}
        void     Setw_PluralWordFlag(char newVal){w_PluralWordFlag = newVal;}

        char     Getw_SecondaryType(){return w_SecondaryType;}
        void     Setw_SecondaryType(char newVal){w_SecondaryType = newVal;}

        char     Getw_AlternateType(){return w_AlternativeType;}
        void     Setw_AlternateType(char newVal){w_AlternativeType = newVal;}

        char     Getw_WordTense(){return w_WordTense;}
        void     Setw_WordTense(char newVal){w_WordTense = newVal;}

        string   Getw_PossessiveRoot(){return w_PossessiveRoot;}
        void     Setw_PossessiveRoot(string newVal){w_PossessiveRoot = newVal;}

        char     Getw_PossessiveRootType(){return w_PossessiveRootType;}
        void     Setw_PossessiveRootType(char newVal){w_PossessiveRootType = newVal;}

        string   Getw_RelatedNoun(int Location){
                 SetIT == w_RelatedNouns.begin();
                 for(int x =0; x <= Location; x++) ++SetIT;
                 if(SetIT == w_RelatedNouns.end())
                    return "";
                 else
                    return *SetIT;}

        string   Getw_Adjective(int Location){
                 SetIT == w_Adjectives.begin();
                 for(int x =0; x <= Location; x++) ++SetIT;
                 if(SetIT == w_Adjectives.end())
                    return "";
                 else
                    return *SetIT;}

        string   Getw_Adverb(int Location){
                 SetIT == w_Adverbs.begin();
                 for(int x =0; x <= Location; x++) ++SetIT;
                 if(SetIT == w_Adverbs.end())
                    return "";
                 else
                    return *SetIT;}

         void    Setw_RelatedNoun(string newVal){w_RelatedNouns.emplace(newVal);}

         void    Setw_Adjective(string newVal){w_Adjectives.emplace(newVal);}

         void    Setw_Adverb(string newVal){w_Adverbs.emplace(newVal);}

         int     Getw_RelatedNounCount(){return w_RelatedNouns.size();}

         int     Getw_AdjectiveCount(){return w_Adjectives.size();}

         int     Getw_AdverbCount(){return w_Adverbs.size();}

        void c_WordInitializeAll(){

          w_WordForm                 = "";      // the word data in its original form           1
          w_WordFormLC               = "";      // the word data in all lowercase               2
          w_ContractionFormFirst     = "";      // deconstructed contraction what's = what      3
          w_ContractionFormSecond    = "";      // deconstructed contraction what's = is        4
          w_PluralRoot               = "";      // deconstructed plural , i.e. cars = car       5
          w_SubWord                  = "";      // replacement word,usually from subject        6
          w_PossessiveRoot           = "";      // cat's = cat                                  7
          w_isContraction            = false;   // contraction flag                             8
          w_isPlural                 = false;   // plural flag                                  9
          w_QuoteLocation            = -1;      // location of quote if contraction/possessive  10
          w_WordTokens               = -1;      // depreciated                                  11
          w_WordType                 = 'u';     // defines word type  u = unknown               12
          w_GenderClass              = 'u';     // defines gender     u = undefined             13
          w_PluralWordFlag           = 'u';     // s = singular  p=plural u = undefined         14
          w_SecondaryType            = 'u';     // some words have more than 1 usage            15
          w_AlternativeType          = 'u';     // some words have more than 1 usage            16
          w_WordTense                = 'u';     // c - present p - past                         17
          w_PossessiveRootType       = 'u';     // usually a 'n' noun but not always            18
          w_SingularForm             = "";      // i.e. cats = cat                              19

          w_MiniDefinition.clear();             // usually Gist of sentence if used as subject  20
          w_Adjectives.clear();                 // adjectives used towards this word            21
          w_Adverbs.clear();                    // adverbs used towards this word               22
          w_RelatedNouns.clear();               // nouns related to this word                   23
        }


};

#endif // C_WORD_H
