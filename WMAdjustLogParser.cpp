#include "WMAdjustLogParser.hpp"

WMAdjustLogParser::WMAdjustLogParser(string input, string output){
	input_file = input;
	output_file = output;
}

void WMAdjustLogParser::parse(){
	
	ifstream input(input_file);
	string line;
	//char line[MAX_LINE];
	int length=0;
	
	while( std::getline(input, line) ){
		
		length = sizeof(line);
		
		
		//if(strncmp(line+left+1,"CONNECT",7)==0 );

				

	
	input.close();
}

	/*
void WMAdjustLogParser::statistics(){
	int current_max,w=35;
	string ip,id;
	
	ofstream output(output_file);
	output << setw(w) << left << "Number of unique IPs: " << users.size() << "\n\n";
	output << setw(w) << "Number of unique contents: " << contents.size() << "\n\n";
	output << setw(w) << "Total data sent: " << (double)total_data/1e9 << "GB\n\n";
	output << setw(w) << "Number of video requests: " << videos << "\n\n";
	output << setw(w) << "Number of audio requests: " << audios << "\n\n";
	output << setw(w) << "Number of cs hits requests: " << cs_hits << "\n\n";
	
	current_max = 0;
	for( auto &user: users )
		if( user.second > current_max ){
			current_max = user.second;
			ip = user.first;
		}
	
	output << setw(w) << "The IP that watched contents most: " << ip << " (" << current_max << " times)\n\n";
	
	current_max = 0;
	for( auto &content: contents )
		if( content.second > current_max ){
			current_max = content.second;
			id = content.first;
		}
	
	output << setw(w) << "The content that watched most: " << id << " (" << current_max << " times)\n\n";
	
	output << "Browsers:\n";
	for( auto &browser: user_agents )
		output << browser.first << ": %" << ((double)browser.second/valid_lines)*100.0 << "\n";
	
	output << "\nHTTP Statuses:\n";
	for( int i=0 ; i<5 ; i++ )
		output << i+1 << "xx: %" << ((double)http_statuses[i]/valid_lines)*100.0 << "\n";
	
	output << "\nBitrates:\n";
	for( auto &bitrate: bitrates )
		output << bitrate.first << ": %" << ((double)bitrate.second/valid_lines)*100.0 << "\n";
	
	output.close();
}
	*/
