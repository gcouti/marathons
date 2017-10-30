#include <iostream>

#include <sstream>
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int eSize;
    int textSize;
    string in;

	while(true)
	{
	    std::getline(cin, in);

	    if(in == "0 0") break;

        std::istringstream is( in );

	    is >> eSize;
	    is >> textSize;

        string* e = new string[eSize];
        for(int i=0; i < eSize; i++){
            std::getline(cin, e[i]);
        }

        int total = 0;
        for(int i=0; i< textSize; i++){
            std::getline(cin, in);
            for(int si=0; si<in.length(); si++) {
                char c = in[si];

                for (int j=0;j <eSize;j++){
                    string emoticon = e[j];
                    if (c == emoticon[emoticon.length()-1]){
                        bool isEqual = true;
                        for(int ei=emoticon.length()-2; ei >=0; ei-- ){
                            if(emoticon[ei] != in[si-(emoticon.length() -1 - ei)]) {
                                isEqual = false;
                                break;
                            }
                        }

                        if (isEqual){
                            total ++;
                            for(int ei=0; ei <emoticon.length(); ei++ ){
                                in[si-ei] = '&';
                            }
                            break;
                        }
                    }
                }
            }
        }

        cout << total << endl;

	}

    return 0;
}