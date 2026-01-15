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

    //Going to need this later:      Obadiah,  3 John,   2 John,   Philemon, Jude
    const std::vector<int> singleChapterBooks = { 31000000, 64000000, 63000000, 57000000, 65000000 };

    int BibleIndexes::IncreaseBibleReference(int reference, SelectionOption so)
    {
        //      base value minus the remainder of value div by option plus option
        return (reference - (reference % (int)so)) + (int)so;
    }

    int BibleIndexes::GetBibleIndexFromArray(String element)
    {
        for (int i = 0; i < BOOKS_BIBLE; i++)
        {
            if (std::regex_match(element, bibleRegexes[i]))
            {
                return i + 1;
            }
        }
        return 0;
    }

    String KuwagataDLL::BibleIndexes::GetFromBiblePlainArray(int index)
    {
        if (index <= BOOKS_BIBLE) {
            return biblePlainArray[index - 1];
        }
        return String();
    }

    bool BibleIndexes::IsOneChapterBook(int book)
    {
        return std::find(singleChapterBooks.begin(), singleChapterBooks.end(), book) != singleChapterBooks.end();
    }

}