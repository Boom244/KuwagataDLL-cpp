#include "BibleIndexes.h"
namespace KuwagataDLL {

    

    const int BOOKS_BIBLE = 66;
    //These regexes are ripped *ahem* I mean, borrowed, from a previous version of Avendesora's PythonBible:
    //https://github.com/avendesora/pythonbible
    const Regex bibleRegexes[] = {
                Regex("Gen\\.*(?:esis)?"),
                Regex("Exo\\.*(?:d\\.*)?(?:us)?"),
                Regex("Lev\\.*(?:iticus)?"),
                Regex("Num\\.*(?:bers)?"),
                Regex("Deu\\.*(?:t\\.*)?(?:eronomy)?"),
                Regex("(Joshua|Josh\\.*|Jos\\.*|Jsh\\.*)"),
                Regex("(Judges|Judg\\.*|Jdgs\\.*|Jdg\\.*)"),
                Regex("(Ruth|Rut\\.*|Rth\\.*)"),
                Regex("1 (Samuel|Sam\\.*|Sa\\.*|Sm\\.*)"),
                Regex("2 (Samuel|Sam\\.*|Sa\\.*|Sm\\.*)"),
                Regex("1 (Kings|Kgs\\.*|Kin\\.*|Ki\\.*)"),
                Regex("2 (Kings|Kgs\\.*|Kin\\.*|Ki\\.*)"),
                Regex("1 (Chronicles|Chron\\.*|Chro\\.*|Chr\\.*|Ch\\.*)"),
                Regex("2 (Chronicles|Chron\\.*|Chro\\.*|Chr\\.*|Ch\\.*)"),
                Regex("Ezr\\.*(?:a)?"),
                Regex("Neh\\.*(?:emiah)?"),
                Regex("Est\\.*(?:h\\.*)?(?:er)?"),
                Regex("Job"),
                Regex("(Psalms|Psalm|Pslm\\.*|Psa\\.*|Psm\\.*|Pss\\.*|Ps\\.*)"),
                Regex("(Proverbs|Prov\\.*|Pro\\.*|Prv\\.*)"),
                Regex("(Ecclesiastes(?:\\s+or\\,\\s+the\\s+Preacher)?|Eccles\\.*|Eccle\\.*|Eccl\\.*|Ecc\\.*|Ec\\.*|Qoh\\.*)$"),
                Regex("(Song(?: of (Solomon|Songs|Sol\\.*))?)|Canticles|(Canticle(?: of Canticles)?)|SOS|Cant"),
                Regex("Is\\.*(?:aiah)?"),
                Regex("Jer\\.*(?:emiah)?"),
                Regex("Lam\\.*(?:entations)?"),
                Regex("(Ezekiel|Ezek\\.*|Eze\\.*|Ezk\\.*)"),
                Regex("Dan\\.*(?:iel)?"),
                Regex("Hos\\.*(?:ea)?"),
                Regex("Joe\\.*(?:l)?"),
                Regex("Amo\\.*(?:s)?"),
                Regex("Oba\\.*(?:d\\.*(?:iah)?)?"),
                Regex("Jonah|Jon\\.*|Jnh\\.*"),
                Regex("Mic\\.*(?:ah)?"),
                Regex("Nah\\.*(?:um)?"),
                Regex("Hab\\.*(?:akkuk)?"),
                Regex("Zep\\.*(?:h\\.*(?:aniah)?)?"),
                Regex("Hag\\.*(?:gai)?"),
                Regex("Zec\\.*(?:h\\.*(?:ariah)?)?"),
                Regex("Mal\\.*(?:achi)?"),
                Regex("Mat\\.*(?:t\\.*(?:hew)?)?"),
                Regex("Mark|Mar\\.*|Mrk\\.*"),
                Regex("Luk\\.*(?:e)?"),
                Regex("^((?!1|2|3).)*(John|Joh\\.*|Jhn\\.*|Jo\\.*|Jn\\.*)"),
                Regex("Act\\.*(?:s)?"),
                Regex("Rom\\.*(?:ans)?"),
                Regex("1 Co\\.*(?:r\\.*(?:inthians)?)?"),
                Regex("2 Co\\.*(?:r\\.*(?:inthians)?)?"),
                Regex("Gal\\.*(?:atians)?"),
                Regex("Eph\\.*(?:es\\.*(?:ians)?)?"),
                Regex("Ph(?:(p\\.*)|(?:il\\.*(?!e\\.*(?:m\\.*(?:on)?)?)(?:ippians)?))"),
                Regex("Col\\.*(?:ossians)?"),
                Regex("1 Th\\.*(?:(s|(es(?:s)?))\\.*(?:alonians)?)?"),
                Regex("2 Th\\.*(?:(s|(es(?:s)?))\\.*(?:alonians)?)?"),
                Regex("1 Ti\\.*(?:m\\.*(?:othy)?)?"),
                Regex("2 Ti\\.*(?:m\\.*(?:othy)?)?"),
                Regex("Tit\\.*(?:us)?"),
                Regex("(Philemon|Philem\\.*|Phile\\.*|Phlm\\.*|Phi\\.*|Phm\\.*)"),
                Regex("Heb\\.*(?:rews)?"),
                Regex("Ja(?:me)?s\\.*"),
                Regex("1 (Pe\\.*(?:t\\.*(?:er)?)?|Pt\\.*)"),
                Regex("2 (Pe\\.*(?:t\\.*(?:er)?)?|Pt\\.*)"),
                Regex("1 (John|Joh\\.*|Jhn\\.*|Jo\\.*|Jn\\.*)"),
                Regex("2 (John|Joh\\.*|Jhn\\.*|Jo\\.*|Jn\\.*)"),
                Regex("3 (John|Joh\\.*|Jhn\\.*|Jo\\.*|Jn\\.*)"),
                Regex("Jud\\.*(:?e)?"),
                Regex("Rev\\.*(?:elation)?")
    };

    const String biblePlainArray[] = {
                    "Genesis",
                    "Exodus",
                    "Leviticus",
                    "Numbers",
                    "Deuteronomy",
                    "Joshua",
                    "Judges",
                    "Ruth",
                    "1 Samuel",
                    "2 Samuel",
                    "1 Kings",
                    "2 Kings",
                    "1 Chronicles",
                    "2 Chronicles",
                    "Ezra",
                    "Nehemiah",
                    "Esther",
                    "Job",
                    "Psalm",
                    "Proverbs",
                    "Ecclesiastes",
                    "Song of Solomon",
                    "Isaiah",
                    "Jeremiah",
                    "Lamentations",
                    "Ezekiel",
                    "Daniel",
                    "Hosea",
                    "Joel",
                    "Amos",
                    "Obadiah",
                    "Jonah",
                    "Micah",
                    "Nahum",
                    "Habakkuk",
                    "Zephaniah",
                    "Haggai",
                    "Zechariah",
                    "Malachi",
                    "Matthew",
                    "Mark",
                    "Luke",
                    "John",
                    "Acts",
                    "Romans",
                    "1 Corinthians",
                    "2 Corinthians",
                    "Galatians",
                    "Ephesians",
                    "Philippians",
                    "Colossians",
                    "1 Thessalonians",
                    "2 Thessalonians",
                    "1 Timothy",
                    "2 Timothy",
                    "Titus",
                    "Philemon",
                    "Hebrews",
                    "James",
                    "1 Peter",
                    "2 Peter",
                    "1 John",
                    "2 John",
                    "3 John",
                    "Jude",
                    "Revelation"
    };

    //Going to need this later: Obadiah,3 John, 2 John,Philemon,Jude.
    const std::vector<int> singleChapterBooks = { 31000000, 64000000, 63000000, 57000000, 65000000 };

    /*
    Increases a bible reference by the numerical value of a Selection Option.
    @param reference the OSIS reference to increase.
    @param so the Selection Option to use.
    @return the reference, appropriately increased by the selection option factor.
    */
    int BibleIndexes::IncreaseBibleReference(int reference, SelectionOption so)
    {
        //      base value minus the remainder of value div by option plus option
        return (reference - (reference % (int)so)) + (int)so;
    }

    /*
    Gets the bible index from the array. Used to transform a book name into a base
    OSIS reference.
    @param element The element to transform.
    @return an integer (one-indexed, not zero) representing said element as a number of a 
    bible book. */
    int BibleIndexes::GetBibleIndexFromArray(String element)
    {
        for (int i = 0; i < BOOKS_BIBLE; i++)
        {
            if (std::regex_search(element, bibleRegexes[i]))
            {
                return i + 1;
            }
        }
        return 0;
    }

    /*
    Gets the string corresponding to a Bible Index - 1. 
    @param index The number corresponding to a book of the bible (not zero-indexed!)
    @returns Thr string corresponding to that book's name. If the index does not exist, an
    empty string is returned.*/
    String BibleIndexes::GetFromBiblePlainArray(int index)
    {
        if (index <= BOOKS_BIBLE) {
            return biblePlainArray[index - 1];
        }
        return String();
    }

    /*
    @returns A boolean reflecting whether or not a book denoted by a full OSIS reference (minus any chapters or verses)
    corresponds to a single-chaptered book of the bible.*/
    bool BibleIndexes::IsOneChapterBook(int book)
    {
        return std::find(singleChapterBooks.begin(), singleChapterBooks.end(), book) != singleChapterBooks.end();
    }

}