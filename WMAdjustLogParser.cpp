#include "WMAdjustLogParser.hpp"

//#define WMTempExcluded
//#define SEP_CH                  "\t"
#define SEP_CH                  ","

LogParser::LogParser(string input_file, string output_file){
	input.open(input_file);
	output.open(output_file);

    if (!output.is_open()){
	    cerr << "Can't open the output file: " << output_file << endl;
	    return;
	}

	if (!input.is_open()){
	    output << "Can't open the input file! ";
	    return;
	}

	// Print the header
	output  << "Nr." << SEP_CH
            << "TB_temp(C)" << SEP_CH
            << "TB_flow(L/h)" << SEP_CH;
    for (uint8_t WM_idx = 0; WM_idx < MAX_COUNTERS_NR; WM_idx++){
        output  << "WM_temp(C)" << SEP_CH
                << "WM_flow(L/h)" << SEP_CH
                << "Error(%)" << SEP_CH
                << "WM_ID" << SEP_CH;
    }
    output  << "\n";

	for (uint8_t WM_idx = 0; WM_idx < MAX_COUNTERS_NR; WM_idx++){
        check_WM_state |= WM_STATE(WM_idx);
    }
}

using namespace std;

void LogParser::parse(){

    string line;

	while( std::getline(input, line) ){
        lines++;
        float value = 0;
        uint32_t WMID = 0;

        if (try_TBTemp(line, value)){
            calibration_Point[points_idx.TB_temp_idx].TB_temp = value;
            points_idx.TB_temp_idx++;
            if (points_idx.TB_temp_idx == CALIB_ITER_NR){
                collection_state.TB_temp_ok = 1;
                points_idx.TB_temp_idx = 0;
            }

            continue;
        }

        if (try_TBFlow(line, value)){
            calibration_Point[points_idx.TB_flow_idx].TB_flow = value;
            points_idx.TB_flow_idx++;
            if (points_idx.TB_flow_idx == CALIB_ITER_NR){
                collection_state.TB_flow_ok = 1;
                points_idx.TB_flow_idx = 0;
            }

            continue;
        }
        if (try_WMTemp(line, value, WMID)){
#ifndef WMTempExcluded
            uint8_t WM_idx = locateWMinTable(WMID);

            if (WM_TABLE_FULL != WM_idx){
                calibration_Point[points_idx.WM_temp_idx[WM_idx]].counter_data[WM_idx].WM_temp = value;
                points_idx.WM_temp_idx[WM_idx]++;
                if (points_idx.WM_temp_idx[WM_idx] == CALIB_ITER_NR){
                    collection_state.WM_temp_ok |= WM_STATE(WM_idx);
                    points_idx.WM_temp_idx[WM_idx] = 0;
                }
            }
#endif // WMTempExcluded
            continue;
        }

        if (try_WMFlow(line, value, WMID)){
            uint8_t WM_idx = locateWMinTable(WMID);

            if (WM_TABLE_FULL != WM_idx){
                calibration_Point[points_idx.WM_flow_idx[WM_idx]].counter_data[WM_idx].WM_flow = value;
                points_idx.WM_flow_idx[WM_idx]++;
                if (points_idx.WM_flow_idx[WM_idx] == CALIB_ITER_NR){
                    collection_state.WM_flow_ok |= WM_STATE(WM_idx);
                    points_idx.WM_flow_idx[WM_idx] = 0;
                }
            }
            continue;
        }

        if (true == try_print_export()){
            print_export();
        }
    }

    if (true == try_print_export()){
        print_export();
    }

    output << "Read " << lines <<" lines!\n";
    cout << "Read " << lines <<" lines!\t" << "Valide: " << valid_lines << endl;
	input.close();
}

bool LogParser::try_TBTemp(string &line, float &value){
    bool line_corresponds = false;
    string string2find = "Get TestBench Temperature:";
    size_t pos = 0;

    pos = line.find(string2find, 0);

    if (string::npos != pos){
        // Matching string Found!
        line_corresponds = true;
        value = atof((char*)&line[pos + string2find.length()]);
    }

    return line_corresponds;
};

bool LogParser::try_TBFlow(string &line, float &value){
    bool line_corresponds = false;
    string string2find = "Get TestBench Flowrate:";
    size_t pos = 0;

    pos = line.find(string2find, 0);

    if (string::npos != pos){
        // Matching string Found!
        line_corresponds = true;
        value = atof((char*)&line[pos + string2find.length()]);
    }

    return line_corresponds;
};

bool LogParser::try_WMTemp(string &line, float &value, uint32_t &WMID){
    bool line_corresponds = false;
    string string2find = "Get Saved Counter Temperature:";
    string string2findCounter = "Counter ID:";
    size_t pos1 = 0, pos2 = 0;

    pos1 = line.find(string2find, 0);
    pos2 = line.find(string2findCounter, 0);

    if (string::npos != pos1 && string::npos != pos2){
        // Matching string Found!
        line_corresponds = true;
        value = atof((char*)&line[pos1 + string2find.length()]);
        WMID = atoi((char*)&line[pos2 + string2findCounter.length()]);
    }

    return line_corresponds;
};

bool LogParser::try_WMFlow(string &line, float &value, uint32_t &WMID){
    bool line_corresponds = false;
    string string2find = "Get Saved Counter Flowrate:";
    string string2findCounter = "Counter ID:";
    size_t pos1 = 0, pos2 = 0;

    pos1 = line.find(string2find, 0);
    pos2 = line.find(string2findCounter, 0);

    if (string::npos != pos1 && string::npos != pos2){
        // Matching string Found!
        line_corresponds = true;
        value = atof((char*)&line[pos1 + string2find.length()]);
        WMID = atoi((char*)&line[pos2 + string2findCounter.length()]);
    }

    return line_corresponds;
};

uint8_t LogParser::locateWMinTable(const uint32_t WM_ID){
    uint8_t WM_idx;
    for (WM_idx = 0; WM_idx < MAX_COUNTERS_NR; WM_idx++){
        if (WM_ID == WM_IDs[WM_idx]){
            return WM_idx;
        } else
            if (0 == WM_IDs[WM_idx]){
                WM_IDs[WM_idx] = WM_ID;
                return WM_idx;
        }
    }
    return WM_TABLE_FULL;
}

bool LogParser::try_print_export(){
    bool export_log = false;

    if (1 == collection_state.TB_flow_ok
        && 1 == collection_state.TB_temp_ok)
    {

        for (uint8_t WM_idx = 0; WM_idx < MAX_COUNTERS_NR; WM_idx++){
            if (WM_STATE(WM_idx) | collection_state.WM_flow_ok
#ifndef WMTempExcluded
                && WM_STATE(WM_idx) | collection_state.WM_temp_ok
#endif // WMTempExcluded
                && 0 != WM_IDs[WM_idx]){
                   export_log = true;
                   break;
            }
        }

        collection_state.TB_flow_ok = 0;
        collection_state.TB_temp_ok = 0;
        collection_state.WM_flow_ok = 0;
        collection_state.WM_temp_ok = 0;
    }
    return export_log;
}

void LogParser::print_export(){
    for (uint8_t idx = 0; idx < CALIB_ITER_NR; idx++){
        valid_lines ++;
        output  << valid_lines << SEP_CH
                << calibration_Point[idx].TB_temp << SEP_CH
                << calibration_Point[idx].TB_flow << SEP_CH;
        for (uint8_t WM_idx = 0; WM_idx < MAX_COUNTERS_NR; WM_idx++){
            output  << calibration_Point[idx].counter_data[WM_idx].WM_temp << SEP_CH
                    << calibration_Point[idx].counter_data[WM_idx].WM_flow << SEP_CH
                    << SEP_CH
                    << WM_IDs[WM_idx] << SEP_CH;
        }
        output  << "\n";
    }
}
