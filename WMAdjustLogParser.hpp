#ifndef NGINXPARSER_HPP
#define NGINXPARSER_HPP

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>

#define WM_TABLE_FULL       0xFF

#define STATE_OK    1
#define STATE_NOK   0

#define WM_STATE(WMIDX)    (1<<WMIDX)


using namespace std;

const int CALIB_ITER_NR = 40;
const int MAX_COUNTERS_NR = 10;

typedef struct __attribute__((packed, aligned(4))) {
    uint32_t TB_temp_ok:1;
    uint32_t TB_flow_ok:1;
    uint32_t WM_temp_ok:MAX_COUNTERS_NR;
    uint32_t WM_flow_ok:MAX_COUNTERS_NR;
    uint32_t reserved:((2+2*MAX_COUNTERS_NR)%4);
} state_t;

typedef struct calib_measurement{
	typedef struct {
		float WM_temp;
		float WM_flow;
	} counter_data_t;


	float TB_temp;
	float TB_flow;
	counter_data_t counter_data[MAX_COUNTERS_NR];
} calib_measurement_t;

typedef struct {
    uint8_t TB_temp_idx;
    uint8_t TB_flow_idx;
    uint8_t WM_temp_idx[MAX_COUNTERS_NR];
    uint8_t WM_flow_idx[MAX_COUNTERS_NR];
} points_idx_t;

class LogParser{

	int lines=0, valid_lines=0, counters=0, TB_flows=0, TB_temp=0, counters_flows=0, counters_temp=0;
	ifstream input;
	ofstream output;

	uint32_t check_WM_state = 0;
	points_idx_t points_idx = {0};
	uint32_t WM_IDs[MAX_COUNTERS_NR] = {0};
	state_t collection_state = {0};
	calib_measurement_t calibration_Point[CALIB_ITER_NR] = {0};

	long long int total_data = 0;

    private:
        bool try_TBTemp(string &line, float &value);
        bool try_TBFlow(string &line, float &value);
        bool try_WMTemp(string &line, float &value, uint32_t &WMID);
        bool try_WMFlow(string &line, float &value, uint32_t &WMID);

        uint8_t locateWMinTable(uint32_t WM_ID);
        bool try_print_export();
        void print_export();

	public:
		LogParser(string input, string output);
		void parse();
};
#endif
