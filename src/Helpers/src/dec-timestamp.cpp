#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sstream>

#include "htime.h"
#include "DecoderInterface.h"
#include "dec-timestamp.h"
#include "logging.h"

#define LOG_TAG "TTR"

void DecTimeStamp::SetDebug(uint32_t value)
{
	DebugStatus = (value > 0) ? true : false;
}

void DecTimeStamp::SetTriggerTime()
{
	if(DebugStatus)
		TriggerTimeStamp = get_time_us();
}

void DecTimeStamp::SetStartAcqTime()
{
	if(DebugStatus)
		StartAcqTimeStamp = get_time_us();
}

void DecTimeStamp::SetImageTime()
{
	if(DebugStatus)
		GotImage.push_back(get_time_us());
}

void DecTimeStamp::SetImageParas(uint32_t exposure, uint32_t gain, uint32_t white_value)
{
	if(DebugStatus)
	{
		imageExposure.push_back(exposure);
		imageGain.push_back(gain);
		imageWhiteValue.push_back(white_value);
	}
}

void DecTimeStamp::SetIllumLevel(uint32_t level)
{
	if(DebugStatus)
		imageIllumLevel.push_back(level);
}

void DecTimeStamp::SetIQScore(uint32_t score)
{
	if(DebugStatus)
		imageIQScore.push_back(score);
}

void DecTimeStamp::SetFldStartTime(uint32_t n)
{
	if(DebugStatus)
	{
		FldStart.push_back(get_time_us());
		FldImageNr.push_back(n);
	}
}

void DecTimeStamp::SetFldStopTime()
{
	if(DebugStatus)
	{
		uint64_t t = get_time_us();
		FldStop.push_back(t);
	}
}

void DecTimeStamp::SetIdStartTime(uint32_t n)
{
	if(DebugStatus)
	{
		IdStart.push_back(get_time_us());
		IdImageNr.push_back(n);
	}
}

void DecTimeStamp::SetIdStopTime()
{
	if(DebugStatus)
		IdStop.push_back(get_time_us());
}

void DecTimeStamp::SetDecDoneTime()
{
	if(DebugStatus)
		DecDoneTime = get_time_us();
}

void DecTimeStamp::SetBeepStartTime()
{
	if(DebugStatus)
		BeepStartTime = get_time_us();
}

void DecTimeStamp::SetDecType(int T)
{
	if(DebugStatus)
		DecType = T;
}

void DecTimeStamp::SetDecData(unsigned char *pData, size_t len)
{
	if(DebugStatus)
		decData.append((const char*)pData, len);
}

void DecTimeStamp::CleanStatistics()
{
	DecType = -1;
	DecDoneTime = 0;
	TriggerTimeStamp = 0;
	StartAcqTimeStamp = 0;
	GotImage.clear();
	imageExposure.clear();
	imageGain.clear();
	imageWhiteValue.clear();
	imageIllumLevel.clear();
	imageIQScore.clear();
	FldStart.clear();
	FldStop.clear();
	IdStart.clear();
	IdStop.clear();
	FldImageNr.clear();
	IdImageNr.clear();
	decData.clear();
}

std::string illum2string(int level)
{
	if(level == 1)
		return "High";
	else if(level == 2)
		return "Mid";
	else if(level == 3)
		return "Low";
	else
		return "n/a";
}

void DecTimeStamp::StatisticsToString(std::string &stat)
{
	uint32_t i;
	uint32_t fld, id;
	uint32_t successNbr = 0;
	char buf[512];
	uint32_t len = 0;

/*
	example:

		0604.095 barcode-scanner: TTR: 	image#	stamp	 exp	gain	illum	FLDs	FLD(us)	 IDs	ID(us)	res	TTR	start(us)	proc(us)	data
		0642.943 barcode-scanner: TTR: 	1	44	18504	1	96	44	1740	48	323451	ID	367	214	374	www.nicelabel.com
		0642.943 barcode-scanner: TTR: 	2	64	18504	1	107	64	1783
		0642.943 barcode-scanner: TTR: 	3	83	18504	1	150	83	2264
		0642.943 barcode-scanner: TTR: 	4	103	18504	1	122	103	1639
		0642.943 barcode-scanner: TTR: 	5	121	13570	1	102	121	1883
		0642.943 barcode-scanner: TTR: 	6	160	13570	1	134	161	1737
		0642.943 barcode-scanner: TTR: 	7	218	14634	1	155	218	3287
		0642.943 barcode-scanner: TTR: 	8	276	14634	1	111	276	2146
		0642.943 barcode-scanner: TTR: 	9	333	10385	1	90	333	1552
		0642.943 barcode-scanner: TTR: 	10	353	10385	1	75	353	1117
		0642.943 barcode-scanner: TTR: 	11	411

	Image sequence:
		image#: image index
		stamp: image time stamp in ms
		exp: exposure time in us
		gain: gain value
		white: white value of image
		illum: illumination level
		IQ: IQ score
		FLD_s: FLD start time stamp in ms
		FLD(us): FLD interval in us
		ID_s: ID start time stamp in ms
		ID(ms): ID interval in ms
		res: FLD/ID success flag

	Successful decode:
		res: FLD/ID success flag
		dec_t: decode time from start to result callback. FLD in us, ID in ms.
		TTR: time to read in ms
		start: trigger to start capture duration in us
		proc: decode to beep time in us
		data: decode result
*/

	std::stringstream ss;
	ss	<< std::endl
		<< std::setw(5) << " img#"
		<< std::setw(7) << "stamp"
		<< std::setw(7) << "exp"
		<< std::setw(6) << "gain"
		<< std::setw(7) << "white"
		<< std::setw(7) << "illum"
		<< std::setw(7) << "IQ"
		<< std::setw(7) << "FLD_s"
		<< std::setw(8) << "FLD(us)"
		<< std::setw(7) << "ID_s"
		<< std::setw(8) << "ID(ms)"
		<< std::setw(5) << "res"
		<< std::endl;

	if (DecDoneTime) {
		if (DecType == DEC_TYPE_FLD)
			successNbr = FldImageNr.back();
		else
			successNbr = IdImageNr.back();
	}

	for (i = 0, fld=0, id=0; i < GotImage.size(); i++)
	{
		//image#, stamp
		ss	<< std::setw(5) << i+1
			<< std::setw(7) << (uint32_t)((GotImage.at(i)-StartAcqTimeStamp)/1000);

		//exp, gain, white, illum, IQ
		ss	<< std::setw(7) << (i<imageExposure.size() ? imageExposure.at(i) : 0)
			<< std::setw(6) << (i<imageGain.size() ? imageGain.at(i) : 0)
			<< std::setw(7) << (i<imageWhiteValue.size() ? imageWhiteValue.at(i) : 0)
			<< std::setw(7) << (i<imageIllumLevel.size() ? illum2string(imageIllumLevel.at(i)) : "n/a")
			<< std::setw(7) << (i<imageIQScore.size() ? imageIQScore.at(i) : 0);

		//FLDs, FLD(us)
		if(fld < FldStop.size() && i == FldImageNr.at(fld)) {
			ss	<< std::setw(7) << (uint32_t)((FldStart.at(fld) - StartAcqTimeStamp)/1000)
				<< std::setw(8) << (uint32_t)(FldStop.at(fld) - FldStart.at(fld));
			fld++;
		} else {
			ss	<< std::setw(7) << "n/a"
				<< std::setw(8) << "n/a";
		}

		//IDs, ID(us)
		if(id < IdStop.size() && i == IdImageNr.at(id))
		{
			ss	<< std::setw(7) << (uint32_t)((IdStart.at(id) - StartAcqTimeStamp)/1000)
				<< std::setw(8) << (uint32_t)((IdStop.at(id) - IdStart.at(id))/1000);
			id++;
		} else {
			ss	<< std::setw(7) << "n/a"
				<< std::setw(8) << "n/a";
		}

		if(DecDoneTime && successNbr == i)
		{
			//res
			if (DecType == DEC_TYPE_FLD) {
				ss	<< std::setw(5) << "FLD";
			} else {
				ss	<< std::setw(5) << "ID";
			}
		}
		ss << std::endl;
	}

	if(DecDoneTime)
	{
		ss	<< std::setw(5) << " res"
			<< std::setw(7) << "dec_t"
			<< std::setw(8) << "TTR(ms)"
			<< std::setw(10) << "start(us)"
			<< std::setw(10) << "proc(us)"
			<< std::setw(2) << ""
			<< std::setw(4) << "data"
			<< std::endl;

		//res, dec_t, TTR
		if (DecType == DEC_TYPE_FLD) {
			ss	<< std::setw(5) << "FLD"
				<< std::setw(7) << (uint32_t)(DecDoneTime - FldStart.at(FldStop.size()-1))
				<< std::setw(8) << (uint32_t)((DecDoneTime - StartAcqTimeStamp)/1000);
		} else {
			ss	<< std::setw(5) << "ID"
				<< std::setw(7) << (uint32_t)((DecDoneTime - IdStart.at(IdStop.size()-1))/1000)
				<< std::setw(8) << (uint32_t)((DecDoneTime - StartAcqTimeStamp)/1000);
		}

		//start(us), process(us), data
		ss	<< std::setw(10) << (uint32_t)(StartAcqTimeStamp-TriggerTimeStamp)
			<< std::setw(10) << (uint32_t)(BeepStartTime - DecDoneTime)
			<< std::setw(2) << ""
			<< std::setw(8) << decData;
	}
	ss << std::endl;

	stat = ss.str();

	// Must clean statistics to release memory
	dec_timestamp.CleanStatistics();
}

//return 0 when stat is populated -1 otherwise
int DecTimeStamp::DecDoneToString(std::string &stat)
{
	if (!DecDoneTime)
		return -1;

	uint32_t i;
	std::stringstream ss;

	/*
		Successful decode:
			image#: image index
			stamp: image time stamp in ms
			exp: exposure time in us
			gain: gain value
			white: white value of image
			illum: illumination level
			iq: IQ score
			res: FLD/ID success flag
			dec_st: decode start time stamp in ms
			dec_ms: decode time in ms
			ttr: time to read in ms
			data: decode result
	*/

	ss	<< std::endl
		<< std::setw(5) << " img#"
		<< std::setw(7) << "stamp"
		<< std::setw(7) << "exp"
		<< std::setw(6) << "gain"
		<< std::setw(7) << "white"
		<< std::setw(7) << "illum"
		<< std::setw(7) << "iq"
		<< std::setw(5) << "res"
		<< std::setw(7) << "dec_ms"
		<< std::setw(8) << "ttr"
		<< std::setw(2) << ""
		<< std::setw(8) << "data"
		<< std::endl;

	if (DecType == DEC_TYPE_FLD)
		i = FldImageNr.back();
	else
		i = IdImageNr.back();

	//image#, stamp
	ss	<< std::setw(5) << i+1
		<< std::setw(7) << (uint32_t)((GotImage.at(i)-StartAcqTimeStamp)/1000);

	//exp, gain, white, illum, IQ
	ss	<< std::setw(7) << (i<imageExposure.size() ? imageExposure.at(i) : 0)
		<< std::setw(6) << (i<imageGain.size() ? imageGain.at(i) : 0)
		<< std::setw(7) << (i<imageWhiteValue.size() ? imageWhiteValue.at(i) : 0)
		<< std::setw(7) << (i<imageIllumLevel.size() ? illum2string(imageIllumLevel.at(i)) : "n/a")
		<< std::setw(7) << (i<imageIQScore.size() ? imageIQScore.at(i) : 0);

	//res, dec_ms, TTR
	if (DecType == DEC_TYPE_FLD) {
		ss	<< std::setw(5) << "FLD"
			<< std::setw(7) << (uint32_t)(DecDoneTime - FldStart.at(FldStop.size()-1))
			<< std::setw(8) << (uint32_t)((DecDoneTime - StartAcqTimeStamp)/1000);
	} else {
		ss	<< std::setw(5) << "ID"
			<< std::setw(7) << (uint32_t)((DecDoneTime - IdStart.at(IdStop.size()-1))/1000)
			<< std::setw(8) << (uint32_t)((DecDoneTime - StartAcqTimeStamp)/1000);
	}

	//start(us), process(us), data
	ss	<< std::setw(2) << ""
		<< std::setw(8) << decData;

	ss << std::endl;
	stat = ss.str();

	// Must clean statistics to release memory
	dec_timestamp.CleanStatistics();

	return 0;
}

void DecTimeStamp::SyslogPrint(std::string &stat)
{
	int len = 0;
	char buf[512];
	const char *str = stat.data();
	int lineStart = 0;

	while(len < stat.size())
	{
		if(str[len] == '\n')
		{
			syslog(LOG_NOTICE, "%s\n", stat.substr(lineStart, len-lineStart+1).c_str());
			lineStart = len+1;
		}
		len++;
	}
}

DecTimeStamp dec_timestamp;

