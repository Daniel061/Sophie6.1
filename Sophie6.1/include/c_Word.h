#ifndef C_WORD_H
#define C_WORD_H

#include <string>
#include <iostream>
#include <unordered_set>

/** SOPHIE 6.1
     author - Daniel W. Ankrom ©2019

     GNU General Public License v3.0
     Permissions of this strong copyleft license are conditioned
      on making available complete source code of licensed works
       and modifications, which include larger works using a licensed
       work, under the same license.
       Copyright and license notices must be preserved.
       Contributors provide an express grant of patent rights.

     see - https://github.com/Daniel061/Sophie6.1/blob/master/LICENSE
*/

using namespace std;
class c_Word
{
    public:
        c_Word();
        virtual ~c_Word();

    protected:
          string  w_WordForm                = "";    // 1)  the word data in its original form
          string  w_WordFormLC              = "";    // 2)  the word data in all lowercase
          string  w_ContractionFormFirst    = "";    // 3)  deconstructed contraction what's = what
          string  w_ContractionFormSecond   = "";    // 4)  deconstructed contraction what's = is
          string  w_SingularForm            = "";    // 5)  i.e. cats = cat
          string  w_PluralRoot              = "";    // 6)  deconstructed plural to the root,cars = car
          string  w_SubWord                 = "";    // 7)  replacement word, usually from subject
          string  w_PossessiveRoot          = "";    // 8)  cat's  = cat
          string  w_VowelPattern            = "";    // 9)  C - constant V - vowel
          string  w_PresentTenseForm        = "";    // 10) Threw = throw
          bool    w_isContraction           = false; // 11)  contraction flag
          bool    w_isPlural                = false; // 12) plural flag
          bool    w_SingularPossessive      = false; // 13) i.e. cat's
          bool    w_PluralPossessive        = false; // 14) i.e. cats'
          int     w_QuoteLocation           = -1;    // 15) location of quote if contraction
          int     w_WordTokens              = -1;    // 16) depreciated
          char    w_PossessiveRootType      = 'u';   // 17) usually a 'n' noun but not always
          char    w_WordType                = 'u';   // 18) defines word type  u = unknown
          char    w_GenderClass             = 'u';   // 19) defines gender     u = undefined
          char    w_PluralWordFlag          = 'u';   // 20) s = singular p=plural u = undefined
          char    w_SecondaryType           = 'u';   // 21) some words have more than 1 usage
          char    w_AlternativeType         = 'u';   // 22) some words have more than 1 usage
          char    w_WordTense               = 'u';   // 23) c - present p - past
          char    w_Polarity                = 'p';   // 24) positive/negative



          unordered_set <string> w_MiniDefinition;   // if this word is a subject, gist of sentence is here too
          unordered_set <string>::iterator SetIT;    // iterator
          unordered_set <string> w_Adjectives;       // adjectives used towards this word
          unordered_set <string> w_Adverbs;          // adverbs used towards this word
          unordered_set <string> w_Verbs;            // verbs used towards this word
          unordered_set <string> w_RelatedNouns;     // Nouns related to this word

    private:


    public:
        string   Getw_PresentTenseForm(){return w_PresentTenseForm;}
        void     Setw_PresentTenseForm(string newVal){w_PresentTenseForm = newVal;}

        string   Getw_VowelPattern(){return w_VowelPattern;}
        void     Setw_VowelPattern(string newVal){w_VowelPattern = newVal;}

        char     Getw_Polarity(){return w_Polarity;}
        void     Setw_Polarity(char newVal){w_Polarity = newVal;}

        void     Setw_MiniDefinition(string newVal){if(newVal != "") w_MiniDefinition.emplace(newVal);}
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
        void     Setw_WordType(char newVal){
                 w_WordType = newVal;}

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
                 SetIT = w_RelatedNouns.begin();
                 for(int x =0; x < Location; x++) ++SetIT;
                 if(SetIT == w_RelatedNouns.end())
                    return "";
                 else
                    return *SetIT;}

        string   Getw_Adjective(int Location){
                 SetIT = w_Adjectives.begin();
                 for(int x =0; x < Location; x++) ++SetIT;
                 if(SetIT == w_Adjectives.end())
                    return "";
                 else
                    return *SetIT;}

        string   Getw_Adverb(int Location){
                 SetIT = w_Adverbs.begin();
                 for(int x =0; x < Location; x++) ++SetIT;
                 if(SetIT == w_Adverbs.end())
                    return "";
                 else
                    return *SetIT;}

        string   Getw_Verb(int Location){
                 SetIT = w_Verbs.begin();
                 for(int x =0; x < Location; x++) ++SetIT;
                 if(SetIT == w_Verbs.end())
                    return "";
                 else
                    return *SetIT;}

         void    Setw_RelatedNoun(string newVal){if(newVal != "") w_RelatedNouns.emplace(newVal);}

         void    Setw_Adjective(string newVal){if(newVal != "") w_Adjectives.emplace(newVal);}

         void    Setw_Adverb(string newVal){if(newVal != "") w_Adverbs.emplace(newVal);}

         void    Setw_Verb(string newVal){if(newVal != "") w_Verbs.emplace(newVal);}

         int     Getw_RelatedNounCount(){return w_RelatedNouns.size();}

         int     Getw_AdjectiveCount(){return w_Adjectives.size();}

         int     Getw_AdverbCount(){return w_Adverbs.size();}

         int     Getw_VerbCount(){return w_Verbs.size();}

        void c_WordInitializeAll(){

          w_WordForm                 = "";      // the word data in its original form           1
          w_WordFormLC               = "";      // the word data in all lowercase               2
          w_ContractionFormFirst     = "";      // deconstructed contraction what's = what      3
          w_ContractionFormSecond    = "";      // deconstructed contraction what's = is        4
          w_PluralRoot               = "";      // deconstructed plural , i.e. cars = car       5
          w_SubWord                  = "";      // replacement word,usually from subject        6
          w_PossessiveRoot           = "";      // cat's = cat                                  7
          w_VowelPattern             = "";      // C - constant V - vowel                       8
          w_isContraction            = false;   // contraction flag                             9
          w_isPlural                 = false;   // plural flag                                  10
          w_QuoteLocation            = -1;      // location of quote if contraction/possessive  11
          w_WordTokens               = -1;      // depreciated                                  12
          w_WordType                 = 'u';     // defines word type  u = unknown               13
          w_GenderClass              = 'u';     // defines gender     u = undefined             14
          w_PluralWordFlag           = 'u';     // s = singular  p=plural u = undefined         15
          w_SecondaryType            = 'u';     // some words have more than 1 usage            16
          w_AlternativeType          = 'u';     // some words have more than 1 usage            17
          w_WordTense                = 'u';     // c - present p - past                         18
          w_PossessiveRootType       = 'u';     // usually a 'n' noun but not always            19
          w_Polarity                 = 'p';     // positive / negative                          20
          w_SingularForm             = "";      // i.e. cats = cat                              21
          w_PresentTenseForm         = "";      // threw = throw                                22

          w_MiniDefinition.clear();             // usually Gist of sentence if used as subject  23
          w_Adjectives.clear();                 // adjectives used towards this word            24
          w_Adverbs.clear();                    // adverbs used towards this word               25
          w_RelatedNouns.clear();               // nouns related to this word                   26
        }


};

#endif // C_WORD_H
