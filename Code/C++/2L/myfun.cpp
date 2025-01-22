#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

/*  Interprets an integer value in a byte string pointed to by str.
    Function discards any whitespace characters until first non-whitespace
    character is found. Then it takes as many characters as possible to
    form a valid integer number representation and converts them to integer value.
    The valid integer value consists of the following parts:
        (optional) plus or minus sign
        numeric digits
 
    Parameters
        str	 -	 pointer to the null-terminated char string to be interpreted 
    
    Return value: Integer value corresponding to the contents of str on success. 
        If the converted value falls out of range of corresponding return type, 
        the return value is undefined. 
        If no conversion can be performed, 0 is returned.
 
*/

int myatoi(const char * ptr){
    string str;
    str = ptr;
    int size = 0;
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    string newstr="";
    for(int i=0;i<str.length();i++){

        if ((str[i] != '+') || (str[i] != '+')) { //if character not to be removed
            // string(1,x) converts character 'x' to string "x"
            newstr += string(1, str[i]); //apend to new str
            //if (str[i + 1] )
        }

        if (isalpha(str[i]) != 0) {
            if (i > 0) {
                str = str.substr(0, i);
                break;
            } else {    
                return 0;
            }
        }
    }

    if (str.size() > 0) {
        //cout << "Input: " << newstr << endl;
        return stoi(newstr);
    } else {
        return 0;
    }
}

// DO NOT ADD MAIN() FUNCTION IN THIS FILE
