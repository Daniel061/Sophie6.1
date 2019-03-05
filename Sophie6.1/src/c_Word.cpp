#include "c_Word.h"

c_Word::c_Word()
{
    //ctor

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

c_Word::~c_Word()
{
    //dtor
}
