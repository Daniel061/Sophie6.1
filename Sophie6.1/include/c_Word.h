#ifndef C_WORD_H
#define C_WORD_H

#include <string>
using namespace std;
class c_Word
{
    public:
        c_Word();
        virtual ~c_Word();

    protected:
          string      w_WordForm                      = "";               // the word data in its original form
          string      w_WordFormLC                    = "";               // the word data in all lowercase
          string      w_ContractionFormFirst          = "";               // deconstructed contraction first half, i.e. contraction what's = what
          string      w_ContractionFormSecond         = "";               // deconstructed contraction first half, i.e. contraction what's = is
          string      w_PluralRoot                    = "";               // deconstructed plural to the root, i.e. cars = car
          string      w_SubWord                       = "";               // replacement word, usually a pronoun replacement from subject, i.e. he = (from subject) John
          bool        w_isContraction                 = false;            // contraction flag
          bool        w_isPlural                      = false;            // plural flag
          int         w_QuoteLocation                 = -1;               // location of quote if contraction
          int         w_WordTokens                    = -1;               // depreciated
          char        w_WordType                      = 'u';              // defines word type  u = unknown
          char        w_GenderClass                   = 'u';              // defines gender     u = undefined
          char        w_PluralWordFlag                = 'u';              // plural flag, s = singular  p=plural u = undefined
          char        w_SecondaryType                 = 'u';              // some words have more than 1 usage
          char        w_AlternativeType               = 'u';              // some words have more than 1 usage
          char        w_WordTense                     = 'u';              // c - present p - past


    private:


    public:

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



        void c_WordInitializeAll(){

          w_WordForm                      = "";               // the word data in its original form
          w_WordFormLC                    = "";               // the word data in all lowercase
          w_ContractionFormFirst          = "";               // deconstructed contraction first half, i.e. contraction what's = what
          w_ContractionFormSecond         = "";               // deconstructed contraction first half, i.e. contraction what's = is
          w_PluralRoot                    = "";               // deconstructed plural to the root, i.e. cars = car
          w_SubWord                       = "";               // replacement word, usually a pronoun replacement from subject, i.e. he = (from subject) John
          w_isContraction                 = false;            // contraction flag
          w_isPlural                      = false;            // plural flag
          w_QuoteLocation                 = -1;               // location of quote if contraction
          w_WordTokens                    = -1;               // depreciated
          w_WordType                      = 'u';              // defines word type  u = unknown
          w_GenderClass                   = 'u';              // defines gender     u = undefined
          w_PluralWordFlag                = 'u';              // plural flag, s = singular  p=plural u = undefined
          w_SecondaryType                 = 'u';              // some words have more than 1 usage
          w_AlternativeType               = 'u';              // some words have more than 1 usage
          w_WordTense                     = 'u';              // c - present p - past
        }


};

#endif // C_WORD_H
