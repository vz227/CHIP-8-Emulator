#include <chip8.h>
#include <fstream>

Chip8::Chip8()
{
	//Set program counter to the address of the first instruction of the ROM, 0x200
	PC = ROM_START_ADDRESS;

	//Load characters at address 0x50
	LoadFont();


}

Chip8::~Chip8()
{

}

void Chip8::LoadROM(char* const filePath)
{
	//Initialize fstream object to read file from filePath
	std::ifstream file(filePath, std::ios::binary);

	if (file.is_open())
	{
		//Move pointer to the end of the file to determine size & save that size
		file.seekg(0, std::ios::end);
		std::streampos size = file.tellg();

		//Allocate buffer to hold its contents
		char* buffer = new char[size];

		//Return to the beginning of the file
		file.seekg(0, std::ios::beg);

		//Read in the file & close it
		file.read(buffer, size);
		file.close();

		//Write buffer into memory starting at 0x200
		for (long i = 0; i < static_cast<long>(size); i++)
		{
			memory[ROM_START_ADDRESS + i] = buffer[i];
		}

		//Free memory
		delete[] buffer;
	}
}

void Chip8::LoadFont()
{
	//Initialize fontSet
	Character fontSet[16]
	{
		{0xF0, 0x90, 0x90, 0x90, 0xF0}, // 0
		{0x20, 0x60, 0x20, 0x20, 0x70}, // 1
		{0xF0, 0x10, 0xF0, 0x80, 0xF0}, // 2
		{0xF0, 0x10, 0xF0, 0x10, 0xF0}, // 3
		{0x90, 0x90, 0xF0, 0x10, 0x10}, // 4
		{0xF0, 0x80, 0xF0, 0x10, 0xF0}, // 5
		{0xF0, 0x80, 0xF0, 0x90, 0xF0}, // 6
		{0xF0, 0x10, 0x20, 0x40, 0x40}, // 7
		{0xF0, 0x90, 0xF0, 0x90, 0xF0}, // 8
		{0xF0, 0x90, 0xF0, 0x10, 0xF0}, // 9
		{0xF0, 0x90, 0xF0, 0x90, 0x90}, // A
		{0xE0, 0x90, 0xE0, 0x90, 0xE0}, // B
		{0xF0, 0x80, 0x80, 0x80, 0xF0}, // C
		{0xE0, 0x90, 0x90, 0x90, 0xE0}, // D
		{0xF0, 0x80, 0xF0, 0x80, 0xF0}, // E
		{0xF0, 0x80, 0xF0, 0x80, 0x80}  // F
	};

	//Store fontSet starting at address 0x50 in memory as per the technical reference
	for (unsigned int i = 0; i < 16; i + 5)
	{
		for (unsigned int j = 0; i < 5; j++)
		{
			memory[FONTSET_START_ADDRESS + (i * 5) + j] = fontSet[i].sprite[j];
		}
	}
}