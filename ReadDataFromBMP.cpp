#include<iostream>
#include <stdio.h>

using namespace std;

int main()
{
    char* filename = "bmp.24\\Mem1-24.bmp";
    int i, whites = 0, blacks = 0;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    //for each row in the bmp file count whites (255) from zero position until reaching black. Then count blacks until reaching white again.
    for(int i = 0; i < height; i++)
    {
        whites = 0;
        blacks = 0;
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

            if((int)data[j]==255&&blacks>0)
            {
                cout << whites <<";"<< blacks << endl;
                break;
            }

            if((int)data[j]==255)
                whites++;
            else
                blacks++;
        }
    }

    fclose(f);
    return 0;
}

