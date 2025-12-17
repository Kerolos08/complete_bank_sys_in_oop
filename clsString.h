#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
    string _Value;

public:
    clsString()
    {
        // default constructor
        _Value = "";
    }

    clsString(string Input)
    {
        // Parameterized constructor
        _Value = Input;
    }

    void Set_Value(string Input)
    {
        _Value = Input;
    }

    string Get_Value()
    {
        return _Value;
    }

    static short Length(string S1)
    {
        return S1.length();
    }

    static void PrintFirstLetterFromEachWord(string S)
    {
        for (int i = 0; i < S.length(); i++)
        {
            if (i == 0)
            {
                cout << S.at(i) << endl;
            }
            else if (S.at(i) == ' ')
            {
                cout << S.at(i + 1) << endl;
            }
        }
    }

    static string UpperFirstLetter(string S)
    {
        bool isFirst = true;

        for (short i = 0; i < S.length(); i++)
        {
            if (S[i] != ' ' && isFirst)
            {
                S[i] = toupper(S[i]);
            }

            isFirst = (S[i] == ' ') ? true : false;
        }

        return S;
    }

    static string LowerFirsLetter(string S)
    {
        bool isFirst = true;

        for (short i = 0; i < S.length(); i++)
        {
            if (S[i] != ' ' && isFirst)
            {
                S[i] = tolower(S[i]);
            }
            isFirst = (S[i] == ' ') ? true : false;
        }

        return S;
    }

    static string LowerAllLetter(string S)
    {
        for (short i = 0; i < S.length(); i++)
        {
            if (S[i] != ' ')
            {
                S[i] = tolower(S[i]);
            }
        }
        return S;
    }

    static string UpperAllLetter(string S)
    {
        for (short i = 0; i < S.length(); i++)
        {
            if (S[i] != ' ')
            {
                S[i] = toupper(S[i]);
            }
        }
        return S;
    }

    static char InvertChar(char x)
    {
        return (isupper(x)) ? tolower(x) : toupper(x);
    }

    static string InvertAllletters(string S)
    {
        for (short i = 0; i < S.length(); i++)
        {
            S[i] = InvertChar(S[i]);
        }

        return S;
    }

    static short CountCapitalLetter(string S)
    {
        short count = 0;

        for (short i = 0; i < S.length(); i++)
        {
            if (isupper(S[i]))
            {
                count++;
            }
        }
        return count;
    }

    static short CountSmallLetter(string S)
    {
        short count = 0;

        for (short i = 0; i < S.length(); i++)
        {
            if (islower(S[i]))
            {
                count++;
            }
        }
        return count;
    }

    static short CountLetterMatchCase(string S, char x, bool Matchcase = true)
    {
        short count = 0;
        for (short i = 0; i < S.length(); i++)
        {
            if (Matchcase)
            {
                if (S[i] == x)
                {
                    count++;
                }
            }
            else
            {
                if (toupper(S[i]) == toupper(x))
                {
                    count++;
                }
            }
        }
        return count;
    }

    static bool IsVowel(char x)
    {
        const char vowel[5] = {'a', 'e', 'i', 'o', 'u'};
        for (short i = 0; i < 5; i++)
        {
            if (vowel[i] == tolower(x))
                return true;
        }
        return false;
    }

    static short CountAllVowel(string S)
    {
        short count = 0;
        for (short i = 0; i < S.length(); i++)
        {
            if (IsVowel(S[i]))
            {
                count++;
            }
        }
        return count;
    }

    static void PrintAllVowls(string S)
    {
        cout << "Vowels in string are: ";
        for (short i = 0; i < S.length(); i++)
        {
            if (IsVowel(S[i]))
            {
                cout << S[i] << "  ";
            }
        }
    }

    static void PrintEachWord(string S)
    {
        string Space = " ";
        short pos = 0;
        string word = "";

        while ((pos = S.find(Space)) != string::npos)
        {
            word = S.substr(0, pos);
            if (word != "")
            {
                cout << word << endl;
            }
            S.erase(0, pos + Space.length());
        }

        if (S != "")
        {
            cout << S << endl;
        }
    }

    static short CountEachWord(string S)
    {
        string delim = " ";
        short pos = 0;
        short count = 0;

        string word = "";

        while ((pos = S.find(delim)) != string::npos)
        {
            word = S.substr(0, pos);
            if (word != "")
            {
                count++;
            }

            S.erase(0, pos + delim.length());
        }

        if (S != "")
        {
            count++;
        }
        return count;
    }

    static vector<string> SplitString(string S, string delimter = " ")
    {
        short pos = 0;
        string word = "";
        vector<string> vSplit;
        while ((pos = S.find(delimter)) != string::npos)
        {
            word = S.substr(0, pos);
            if (word != "")
            {
                vSplit.push_back(word);
            }
            S.erase(0, pos + delimter.length());
        }

        // if (S != "")
        // {
        vSplit.push_back(S);
        // }
        return vSplit;
    }

    static string JoinString(vector<string> vString, string Sperator = " ")
    {
        string S1;

        for (string &S : vString)
        {
            S1 = S1 + S + Sperator;
        }
        return S1.substr(0, S1.length() - Sperator.length());
    }

    static string JoinString(string arr[100], short length, string Sperator = " ")
    {
        string S1 = "";

        for (short i = 0; i < length; i++)
        {
            S1 = S1 + arr[i] + Sperator;
        }
        return S1.substr(0, S1.length() - Sperator.length());
    }

    static string TrimLeft(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - 1);
            }
        }
        return "";
    }

    static string TrimRight(string S1)
    {
        for (short i = S1.length(); i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }

    static string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    static string ReverseString(string S1)
    {
        vector<string> vString;

        std::string S2 = "";
        vString = SplitString(S1);
        vector<string>::iterator iter;

        iter = vString.end();
        while (iter != vString.begin())
        {
            --iter;
            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1);

        return S2;
    }

    static string ReplaceWord(string S1, string Replacefrom, string Replaceto)
    {

        short pos = 0;
        pos = S1.find(Replacefrom);
        string S2 = S1;
        while (pos != string::npos)
        {

            S1.erase(pos, (S1.length() - pos));
            S1 += (S1.substr(pos, (S1.length() - pos)) = Replaceto);
            pos = S1.find(Replacefrom);
        }

        return S2;
    }

    static string RemovePunctInString(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (ispunct(S1[i]))
            {
                S1[i] = S1.empty();
            }
        }
        return S1;
    }

    short Length()
    {
        return _Value.length();
    }

    void PrintFirstLetterFromEachWord()
    {
        PrintFirstLetterFromEachWord(_Value);
    }

    void UpperFirstLetter()
    {
        _Value = UpperFirstLetter(_Value);
    }

    void LowerFirsLetter()
    {
        _Value = LowerFirsLetter(_Value);
    }

    void LowerAllLetter()
    {
        _Value = LowerAllLetter(_Value);
    }

    void UpperAllLetter()
    {
        _Value = UpperAllLetter(_Value);
    }

    void InvertAllletters()
    {
        _Value = InvertAllletters(_Value);
    }

    short CountCapitalLetter()
    {
        return CountCapitalLetter(_Value);
    }

    short CountSmallLetter()
    {
        return CountSmallLetter(_Value);
    }

    short CountLetterMatchCase(char x, bool Matchcase = true)
    {
        return CountLetterMatchCase(_Value, x, Matchcase);
    }

    short CountAllVowel()
    {
        return CountAllVowel(_Value);
    }

    void PrintAllVowls()
    {
        PrintAllVowls(_Value);
    }

    void PrintEachWord()
    {
        PrintEachWord(_Value);
    }

    short CountEachWord()
    {
        return CountEachWord(_Value);
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    void ReverseString()
    {
        _Value = ReverseString(_Value);
    }

    void ReplaceWord(string Replacefrom, string Replaceto)
    {
        _Value = ReplaceWord(_Value, Replacefrom, Replaceto);
    }

    void RemovePunctInString()
    {
        _Value = RemovePunctInString(_Value);
    }
};