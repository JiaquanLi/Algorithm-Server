#include <vector>
#include <string>

class DecTimeStamp
{
public:
	void SetTriggerTime();
	void SetStartAcqTime();
	void SetImageTime();
	void SetImageParas(uint32_t exposure, uint32_t gain, uint32_t white_value);
	void SetIllumLevel(uint32_t level);
	void SetIQScore(uint32_t score);
	void SetFldStartTime(uint32_t n);
	void SetFldStopTime();
	void SetIdStartTime(uint32_t n);
	void SetIdStopTime();
	void SetDecDoneTime();
	void SetBeepStartTime();
	void SetDecType(int);
	void SetDecData(unsigned char *pData, size_t len);
	void CleanStatistics();
	void StatisticsToString(std::string &stat);
	int DecDoneToString(std::string &stat);
	void SyslogPrint(std::string &stat);
	void SetDebug(uint32_t value);

private:
	bool DebugStatus;
	uint64_t TriggerTimeStamp;
	uint64_t StartAcqTimeStamp;
	std::vector<uint64_t> GotImage;
	std::vector<uint32_t> imageExposure;
	std::vector<uint32_t> imageGain;
	std::vector<uint32_t> imageWhiteValue;
	std::vector<uint32_t> imageIllumLevel;
	std::vector<uint32_t> imageIQScore;
	std::vector<uint64_t> FldStart;
	std::vector<uint64_t> FldStop;
	std::vector<uint64_t> IdStart;
	std::vector<uint64_t> IdStop;
	std::vector<uint32_t> FldImageNr;
	std::vector<uint32_t> IdImageNr;
	std::string decData;
	uint64_t DecDoneTime;
	uint64_t BeepStartTime;
	int DecType;
};

extern DecTimeStamp dec_timestamp;
