#include <iostream>

#include "WMAdjustLogParser.hpp"

using namespace std;

int main(int argc, char **argv){

	//ios::sync_with_stdio(false); // For speed boost

	cout    << "Log parser application for logs provided by WM_Adjust.exe\n"
            << "\t(The application for calibration & testing of Water Meters).\n"
            << "Author: ghennadii.gubceac@addgrup.com\n\n";

	cout    << "(!)Please clean the log file first!\n"
            << "1. Ensure there are only compleated calibration points measurements\n"
            << "\ti.e. all interrupted calibrations must be removed!\n"
            << "2. Please keep at least one more line after the last record obtained from counters.\n"
            << "\ti.e. at the file end.\n";


    string input_file, output_file;

	if ( argc == 3 ){
        input_file = argv[1];
        output_file = argv[2];
	} else
        if (argc == 2)
    {
	    input_file = argv[1];
        output_file = input_file + ".csv";
	} else {
		cerr << "Please enter path of the log file: ";
		getline(cin, input_file);

        output_file = input_file + ".csv";
        cout << "Input file: " << input_file << endl;
		cout << "Output file: " << output_file << endl;
	}

    WMAdjustLogParser parser(input_file.c_str(), output_file.c_str());
    parser.parse();

    system("pause");
    std::getchar();

	return 0;
}
