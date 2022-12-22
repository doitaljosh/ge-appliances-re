#include <iostream>
#include <vector>

struct ErdData {
	uint16_t tag;
	uint8_t length;
	std::vector<uint8_t> payload;
};

std::vector<ErdData> parseErd(std::vector<uint8_t> data) {
	std::vector<ErdData> erdData;
	int index = 0;
	while (index < data.size()) {
		ErdData erd;
		erd.tag = (data[index] << 8) + data[index + 1];
		erd.length = data[index + 2];
		erd.payload.resize(erd.length);
		std::copy(data.begin() + index + 3, data.begin() + index + 3 + erd.length, erd.payload.begin());
		erdData.push_back(erd);
		index += erd.length + 3;
	}
	return erdData;
}

std::vector<uint8_t> unescape(std::vector<uint8_t> data) {
	std::vector<uint8_t> unescapedData;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == 0xe0) {
			i++;
			switch (data[i]) {
				case 0xe1:
					unescapedData.push_back(0xe1);
					break;
				case 0xe2:
					unescapedData.push_back(0xe2);
					break;
				case 0xe3:
					unescapedData.push_back(0xe3);
					break;
				default:
					std::cerr << "Invalid escape sequence at index " << i << std::endl;
					return unescapedData;
			}
		} else {
			unescapedData.push_back(data[i]);
		}
	}
	return unescapedData;
}

std::vector<uint8_t> stripPacketOverhead(std::vector<uint8_t> Gea2Msg) {
	if (Gea2Msg.size() < 6) {
		std::cerr << "Error: GEA message must contain at least 6 bytes" << std::endl;
		return Gea2Msg;
	}

	if (Gea2Msg[0] != 0xe2) {
		std::cerr << "Error: Invalid GEA header" << std::endl;
		return Gea2Msg;
	}

	std::vector<uint8_t> Gea2MsgStripped(Gea2Msg.begin() + 6, Gea2Msg.end());
	if (Gea2MsgStripped.back() == 0xe3) {
		Gea2MsgStripped.resize(Gea2MsgStripped.size() - 3);
	} else if (Gea2MsgStripped.back() == 0xe1) {
		Gea2MsgStripped.resize(Gea2MsgStripped.size() - 4);
	}
	return Gea2MsgStripped;
}

std::vector<uint8_t> parseAndPrintMessage(std::vector<uint8_t> data) {
	unescape(data);
	std::cout << "Destination: " << std::hex << data[1] << std::endl;
	std::cout << "Total Length: " << std::dec << data[2] << std::endl;
	std::cout << "Source: " << std::hex << data[3] << std::endl;
	std::cout << "Message Type: ";
	switch(data[4]) {
		case 0xF0:
			std::cout << "ERD Read";
			break;
		case 0xF1:
			std::cout << "ERD Write";
			break;
		case 0xF2:
			std::cout << "ERD Subscribe";
			break;
		case 0xF3:
			std::cout << "ERD Subscribe List";
			break;
		case 0xF4:
			std::cout << "ERD Unsubscribe";
			break;
		case 0xF5:
			std::cout << "ERD Publish";
			break;
		case 0xB8:
			std::cout << "GEA3 ERD Write";
			break;
		default:
			std::cout << "Unknown: " << std::hex << data[4];
			break;
	}
	std::cout << std::endl;
	switch (data.back()) {
		case 0xE3:
			std::cout << "CRC16: " << std::hex << ((data[data.size()-3] << 8) + data[data.size()-2]) << std::endl;
			break;
		case 0xE1:
			std::cout << "CRC16: " << std::hex << ((data[data.size()-4] << 8) + data[data.size()-3]) << std::endl;
                        break;
		default:
			break;
	}
	std::cout << std::endl;
	data = stripPacketOverhead(data);
	std::vector<ErdData> erdData = parseErd(data);
	for (const ErdData& erd : erdData) {
		std::cout << "ERD: " << std::hex << erd.tag << std::endl;
		std::cout << "ERD Length: " << std::dec << (int)erd.length << std::endl;
		std::cout << "ERD Payload: ";
		for (const uint8_t& payload : erd.payload) {
			std::cout << std::hex << payload << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

int main() {
	std::vector<uint8_t> data = {0xE2,0x3F,0x70,0xC0,0xB8,0x04,0xF0,0x20,0x58,0x02,0x3D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x23,0x01,0x02,0xF0,0x26,0x01,0x1F,0xF2,0x13,0x01,0x00,0x7A,0x73,0xE3};
	parseAndPrintMessage(data);
}
