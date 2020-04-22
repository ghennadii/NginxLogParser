#ifndef WMAdjustLogParser_HPP
#define WMAdjustLogParser_HPP

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>

using namespace std;

const int MAX_LINE = 500;

typedef struct calib_measurement_t{
	struct counter_data_t {
		int WM_ID;
		float WM_temp;
		float WM_flow;
	} ;

	float TB_temp;
	float TB_flow;
	counter_data_t counter_data[10];
};

class WMAdjustLogParser{
	
	int lines=0, valid_lines=0, counters=0, TB_flows=0, TB_temp=0, counters_flows=0, counters_temp=0;
	string input_file, output_file;

	calib_measurement_t calibration_Point[40];
	long long int total_data = 0;
	
	public:
		WMAdjustLogParser(string input, string output);
		void parse();
		//void statistics();
};
#endif
