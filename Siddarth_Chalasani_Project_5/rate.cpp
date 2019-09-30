#include <cstring>
#include <cctype>
#include <cassert>
#include <iostream>
using namespace std;

const int MAX_WORD_LENGTH = 20;

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns);

void remPattern(char word1[][MAX_WORD_LENGTH+1],
                char word2[][MAX_WORD_LENGTH+1],
                int separation[],
                int nPatterns,
                int position);

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns);

int findNextWord(const char document[], char temp[], int position);

int main() {
    char w1[8][MAX_WORD_LENGTH+1] = {"mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS"};
    char w2[8][MAX_WORD_LENGTH+1] = {"scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT"};
    int sep[8] = {1, 3, 0, 2, 1, 0, 12, 0};
    
    cout << makeProper(w1, w2, sep, 8) << endl;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; w1[i][j] != '\0'; j++)
            cout << w1[i][j];
        cout << endl;
        for (int k = 0; w2[i][k] != '\0'; k++)
            cout << w2[i][k];
        cout << endl;
        for (int l = 0; l < 8; l++)
            cout << sep[l];
        cout << endl;
    }
    const int TEST1_NRULES = 4;
    char test1w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test1w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test1dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
    
    const int TEST2_NRULES = 7;
    char test2w1[TEST2_NRULES][MAX_WORD_LENGTH + 1] =
    {
        "bob", "cow", "MatH", "biGBerg", "bIgbErg", "KyLE",  "FAILURE"
    };
    char test2w2[TEST2_NRULES][MAX_WORD_LENGTH + 1] =
    {
        "core", "moo", "calculus", "David", "dAviD","EdwaRd" , "SUCKS"
    };
    int test2dist[TEST2_NRULES] = {
        2,           3,          5,           1, 3, 4, -1
    };
    const int TEST3_NRULES = 8;
    char test3w1[TEST3_NRULES][MAX_WORD_LENGTH + 1] =
    {
        "door", "dean", "Math32A", "bergBird", "egged", "KyLE",  "UCLA", "importance"
    };
    char test3w2[TEST3_NRULES][MAX_WORD_LENGTH + 1] =
    {
        "opened", "burger", "calc", "David", "PAuL","EdwaRd" , "Hard", "sleep"
    };
    int test3dist[TEST3_NRULES] = {
        2,           3,          5,           1, 3, 4, 0, 3
    };
    const int TEST4_NRULES = 6;
    char test4w1[TEST4_NRULES][MAX_WORD_LENGTH + 1] =
    {
        "pokemon", "dean", "corbin", "david", "computer","twentycharacterwords"
    };
    char test4w2[TEST4_NRULES][MAX_WORD_LENGTH + 1] =
    {
        "pokemon", "burger", "curved", "computer", "daViD", "suck"
    };
    int test4dist[TEST4_NRULES] = {
        7,           3,          5,           3, 2, 5
    };
    
    assert(makeProper(test2w1, test2w2, test2dist, TEST2_NRULES) == 5  && strcmp(test2w2[4], "edward") ==0);
    
    assert(rate("Bob made a core mistake by letting moo cows do calculus with david bigberg", test2w1, test2w2, test2dist, 5)==2);
    assert(rate("K'yle Edward has allowed bob to let the nuclear core meltdown because his math didn't use caLculus", test2w1, test2w2, test2dist, 5)==2);
    assert(rate(" a cow will moo when david has done his bigb32@erg math using calculus  ", test2w1, test2w2, test2dist, 5)==3);
    assert(rate("my dog name'@d DaVID biGbERg likes to mow such as a certain cow named kyLe EDwArd! ", test2w1, test2w2, test2dist, 5)==2);
    assert(rate("HALLO @Bigberg, david!!! I heard failing your class sucks- KYLE EDwa!R#D", test2w1, test2w2, test2dist, 5)==2);
    
    assert(makeProper(test3w1, test3w2, test3dist, TEST3_NRULES) == 7 && strcmp(test3w2[4], "edward") == 0);
    
    assert(rate("at a burger bbq dean paul egged the crowd because bigbiRD told him to at the wedding of david", test3w1, test3w2, test3dist, 7)==2);
    assert(rate("The door opened when paul told kyle edward about the importance of sleep", test3w1, test3w2, test3dist, 7)==3);
    assert(rate("UcLA is so hard that David Bergbird got all of us a burger34&)'  with the      d5&8ean", test3w1, test3w2, test3dist, 7)==2);
    assert(rate("Bergbird david told us that david had a bergbird", test3w1, test3w2, test3dist, 7)==1);
    assert(rate("nothing of importance is here", test3w1, test3w2, test3dist, 7)==0);
    
    assert(makeProper(test4w1, test4w2, test4dist, TEST4_NRULES) == 5);
    assert(rate("The pokemon trainer caught 20 pokemon after corbin curved the exam", test4w1, test4w2, test4dist, 4)==2);
    assert(rate("twentycharacterwordses shouldn't suck so much", test4w1, test4w2, test4dist, 4)==0);
    assert(rate("the dean ate many burger's before having a 2nd meal", test4w1, test4w2, test4dist, 4)==0);
    assert(rate("I took a corbin test and after being   curved I got a c- thanks to david and his computer lessons", test4w1, test4w2, test4dist, 4)==2);
    assert(rate("*932041pokemon pokemon corbin pokemon curved pokemon corbin pokemon curved", test4w1, test4w2, test4dist, 4)==2);
    
    const int TEST5_NRULES = 3;
        char test5w1[TEST5_NRULES][MAX_WORD_LENGTH+1] = {
                "", "deranged", ""
            };
        char test5w2[TEST5_NRULES][MAX_WORD_LENGTH+1] = {
                "scientist", "", "plot",
            };
        int test5dist[TEST5_NRULES] = {
                12, 3, 5
            };
        
        assert(makeProper(test5w1, test5w2, test5dist, TEST5_NRULES) == 0);
    
    const int TEST6_NRULES = 4;
    char test6w1[TEST6_NRULES][21] = {
        "mad", "deranged", "nefarious", "have"
    };
        char test6w2[TEST6_NRULES][21] = {
                "scientist", "robot", "plot", "mad"
            };
        int test6dist[TEST6_NRULES] = {
                1, 3, 0, 12
            };
    
    assert(rate("", test6w1, test6w2, test6dist, TEST6_NRULES) == 0);
    
    cout << "All tests succeeded" << endl;
}

int makeProper(char word1[][MAX_WORD_LENGTH+1],
               char word2[][MAX_WORD_LENGTH+1],
               int separation[],
               int nPatterns)
{
    if (nPatterns < 0)
        return 0;
    
    int count = nPatterns; //counts number of valid patterns
    
    for (int i = 0; i < count; i++) {
        
        //removes patterns with empty words or negative separation
        if (word1[i][0] == '\0' || word2[i][0] == '\0' || separation[i] < 0) {
            remPattern(word1, word2, separation, nPatterns, i);
            count--;
            i--;
        }
        
        //removes pattern if word1 has a non-alphabetical character
        for (int j = 0; word1[i][j] != '\0'; j++)
            if (!isalpha(word1[i][j])) {
                remPattern(word1, word2, separation, nPatterns, i);
                count--;
                i--;
                break;
            }
        //removes pattern if word2 has a non-alphabetical character
        for (int k = 0; word2[i][k] != '\0'; k++)
            if (!isalpha(word2[i][k])) {
                remPattern(word1, word2, separation, nPatterns, i);
                count--;
                i--;
                break;
            }
    }
    
    //converts all words in valid patterns into lowercase
    for (int i = 0; i < count; i++) {
        for (int l = 0; word1[i][l] != '\0'; l++)
            word1[i][l] = tolower(word1[i][l]);
        for (int m = 0; word2[i][m] != '\0'; m++)
            word2[i][m] = tolower(word2[i][m]);
    }
    
    //deletes additional patterns with same combination of words
    for (int i = 0; i < count; i++) {
        for (int n = i + 1; n < count; n++)
            
            //if patterns have same combination of words, deletes whichever pattern has a lower separation, and latter pattern if the separations are equal
            if ((!strcmp(word1[i], word1[n]) && !strcmp(word2[i], word2[n])) || (!strcmp(word1[i], word2[n]) && !strcmp(word2[i], word1[n]))) {
                if (separation[i] < separation[n]) {
                    remPattern(word1, word2, separation, nPatterns, i);
                    count--;
                    n--;
                }
                else {
                    remPattern(word1, word2, separation, nPatterns, n);
                    count--;
                    n--;
                }
            }
    }
    
    return count;
}

//function to over-write a pattern from the array of patterns
void remPattern(char word1[][MAX_WORD_LENGTH+1],
                char word2[][MAX_WORD_LENGTH+1],
                int separation[],
                int nPatterns,
                int position)
{
    //copies every element of the arrays after position i into the element directly preceding it
    for (int i = position + 1; i < nPatterns; i++) {
        strcpy(word1[i-1], word1[i]);
        strcpy(word2[i-1], word2[i]);
        separation[i-1] = separation[i];
    }
}

int rate(const char document[],
         const char word1[][MAX_WORD_LENGTH+1],
         const char word2[][MAX_WORD_LENGTH+1],
         const int separation[],
         int nPatterns)
{
    if (nPatterns < 0)
        return 0;
    
    int count = 0; //keeps track of many patterns the document matches
    
    char document2[251]; //creates modifiable cstring duplicate of document
    int i = 0; //position tracker for document
    int j = 0; //position tracker for document2
    while (document[i] != '\0') {
        //copies alphabetical characters from document into document2, converting them into lowercase
        if(isalpha(document[i]) || document[i] == ' ') {
            document2[j] = tolower(document[i]);
            j++;
        }
        i++;
    }
    //adds null byte to document2, making it a null-terminated cstring
    document2[j] = document[i];
    
    for (int k = 0; k < nPatterns; k++) {
        int l = 0; //position tracker for document2
        bool hasPattern = false; //keeps track of whether the document has already tested positive for a pattern
        while ( document2[l] != '\0' && !hasPattern) {
            char temp1[251]; //cstring to store a word from document2
            l = findNextWord(document2, temp1, l); //stores first word in document2 starting at position l into temp1, and changes the value of l to the position after the word ends
            
            if (!strcmp(temp1, word1[k])) {
                char temp2[251];
                
                //checks if any of the separation+1 words following temp1 in document2 are equal to temp2
                for (int m = 0; m <= separation[k]; m++) {
                    l = findNextWord(document2, temp2, l); //sets temp2 equal to the first word in document2 starting from position l
                    if (!strcmp(temp2, word2[k])) {
                        count++;
                        hasPattern = true;
                        break;
                    }
                }
            }
            
            else if (!strcmp(temp1, word2[k])) {
                char temp2[251];
                
                //checks if any of the separation+1 words following temp1 in document2 are equal to temp2
                for (int m = 0; m <= separation[k]; m++) {
                    l = findNextWord(document2, temp2, l); //sets temp2 equal to the first word in document2 starting from position l
                    if (!strcmp(temp2, word1[k])) {
                        count++;
                        hasPattern = true;
                        break;
                    }
                }
            }
        }
    }
    
    return count;
}

//function to set temp equal to the first word starting from position pos in document
int findNextWord(const char document[], char temp[], int pos) {
    int i = pos; //position tracker for document
    
    //ignores all empty spaces between document[pos] and start of first word
    while (document[i] == ' ' && document[i] != '\0')
        i++;
    pos = i;
    
    //copies word from document into temp
    while (document[i] != '\0' && document [i] != ' ') {
        temp[i - pos] = document[i];
        i++;
    }
    //appends null byte to temp
    temp[i - pos] = '\0';
    return i; //returns position of character following last character of word
}
