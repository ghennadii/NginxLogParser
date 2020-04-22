# WMAdjustLogParser

source: https://github.com/burakbugrul/NginxLogParser 

This tiny code was write to parse a specific multiline log in order to facilitate data analyses.
It will collect a block of CALIB_ITER_NR records for each counter and TestBench.
Sure it needs improvements such as additional filters, verifications and cleaning. It's far from ideal but it does its work.

## Compile

```
$ make
```
or
```
$ g++ main.cpp WMAdjustLogParser.cpp -std=c++14 -O2 -o parser
```

# Run
```
$ ./parser <input-file> <output-file>
```
```
$ ./parser <input-file>
```
or
```
$ ./parser
Please enter path of the log file: <input file>
Please enter path of the output file: <output file>
```

# The sample of log file

```
07-04-2020 16:38:14:677 	Get TestBench Temperature: 13.500°C
07-04-2020 16:38:14:864 	Get TestBench Flowrate: 44.100l/h
07-04-2020 16:38:16:051 	Get TestBench Temperature: 13.500°C
07-04-2020 16:38:16:239 	Get TestBench Flowrate: 44.010l/h
07-04-2020 16:38:17:426 	Get TestBench Temperature: 13.500°C
07-04-2020 16:38:17:614 	Get TestBench Flowrate: 44.010l/h
07-04-2020 16:38:18:801 	Get TestBench Temperature: 13.500°C
07-04-2020 16:38:18:988 	Get TestBench Flowrate: 44.100l/h
07-04-2020 16:38:20:176 	Get TestBench Temperature: 13.500°C
07-04-2020 16:38:20:363 	Get TestBench Flowrate: 44.100l/h
07-04-2020 16:38:24:128 	Get Saved Counter Flowrate: 52.978l/h, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Temperature: 0.000°C, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Flowrate: 53.287l/h, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Temperature: 0.000°C, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Flowrate: 53.316l/h, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Temperature: 0.000°C, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Flowrate: 53.181l/h, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Temperature: 0.000°C, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Flowrate: 53.013l/h, Counter ID: 5245
07-04-2020 16:38:24:128 	Get Saved Counter Temperature: 0.000°C, Counter ID: 5245
07-04-2020 16:38:24:425 	Get Saved Counter Flowrate: 54.245l/h, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Temperature: 0.000°C, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Flowrate: 53.007l/h, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Temperature: 0.000°C, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Flowrate: 53.314l/h, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Temperature: 0.000°C, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Flowrate: 54.093l/h, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Temperature: 0.000°C, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Flowrate: 53.287l/h, Counter ID: 3225
07-04-2020 16:38:24:425 	Get Saved Counter Temperature: 0.000°C, Counter ID: 3225
The End!
```
will convert to CSV:
```
1	13.5	44.1	0	52.978	5245	0	54.245	3225
2	13.5	44.01	0	53.287	5245	0	53.007	3225
3	13.5	44.01	0	53.316	5245	0	53.314	3225
4	13.5	44.1	0	53.181	5245	0	54.093	3225
5	13.5	44.1	0	53.013	5245	0	53.287	3225
Read 31 lines!								
```
