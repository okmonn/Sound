#include "WaveWriter.h"

WaveWriter::WaveWriter()
{
}

WaveWriter::WaveWriter(const std::string& fileName, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel)
{
	Open(fileName, sample, bit, channel);
}

std::uint8_t WaveWriter::Open(const std::string& fileName, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel)
{
	file.open(fileName, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!file) {
		return 0;
	}

	fmt.sample  = sample;
	fmt.bit     = bit;
	fmt.channel = channel;
	fmt.block   = (fmt.bit / 8) * fmt.channel;
	fmt.byte    = fmt.sample * fmt.block;

	return 1;
}

template<typename T>
std::uint32_t WaveWriter::Write(const T* buf, const std::uint32_t& num)
{
	if (file) {
		std::uint32_t size = (fmt.bit / 8) * num;
		file.write((char*)buf, size);
		data.size += size;

		return size;
	}

	return 0;
}
template std::uint32_t WaveWriter::Write(const std::uint8_t*, const std::uint32_t&);
template std::uint32_t WaveWriter::Write(const std::int16_t*, const std::uint32_t&);

void WaveWriter::Close(void)
{
	if (file) {
		/*ƒtƒ@ƒCƒ‹æ“ª‚ÉˆÚ“®*/
		file.seekp(0, std::ios_base::beg);

		riff.size = (sizeof(RIFF) + sizeof(FMT) + sizeof(DATA) + data.size) - (sizeof(riff.id) + sizeof(riff.size));
		
		file.write((char*)&riff, sizeof(riff));
		file.write((char*)&fmt, sizeof(fmt));
		file.write((char*)&data, sizeof(data));

		file.close();
	}
}
