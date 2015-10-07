#include <iostream>
#include <fstream>
#include <iomanip>
#include "crc16.hpp"
using namespace std;


int main(int argc, char **argv)
{
    ifstream fin;
    uint32_t file_size;
    uint8_t *file_data;
    crc16 crc_obj(0xFFFF);

    if(argc != 2)
    {
        cout << "Usage: crc16 <filename>\n";
    }
    else
    {
        fin.open(argv[1], ios::in | ios::binary | ios::ate);
        if(fin.fail())
        {
            cout << "Failed to open \"" << argv[1] << "\"\n";
            return 0;
        }
        file_size = fin.tellg();
        cout << "Opened " << file_size << " byte file '" << argv[1] << "'\n";

        try
        {
            file_data = new uint8_t[file_size];
        }
        catch(exception &except)
        {
            cout << "Exception \"" << except.what() << "\"\n";
            fin.close();
            return 0;
        }

        fin.seekg(ios::beg);
        fin.read((char *)file_data, file_size);
        fin.close();

        cout << "Processing checksum...\n";
        crc_obj.process_bytes(file_data, file_size);
        cout << "0xFFFF CRC-CCITT (XModem): 0x"
             << uppercase << setw(4) << hex << crc_obj.checksum() << '\n';

        delete file_data;
    }

    return 0;
}
