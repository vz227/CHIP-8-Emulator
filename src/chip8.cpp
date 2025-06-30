#include <chip8.h>

Chip8::Chip8() //:randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
	//Set program counter to the address of the first instruction of the ROM, 0x200
	PC = ROM_START_ADDRESS;

	//Load character sprites at address 0x50
	LoadFont();


	//Initialize RNG
	//randByte = std::uniform_int_distribution<Byte>(0, 255U);

	//Initialize function pointer table
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
		size_t size = static_cast<size_t>(file.tellg());

		//Make sure file will fit into memory
		if (static_cast<unsigned int>(size) > (MEMORY_SIZE - ROM_START_ADDRESS))
		{
			fprintf(stderr, "The size of the provided ROM exceeds the memory capacity. Exiting..\n");
			return;
		}

		//Allocate buffer to hold its contents
		char* buffer = new char[size];

		//Return to the beginning of the file
		file.seekg(0, std::ios::beg);

		//Read in the file & close it
		file.read(buffer, static_cast<std::streamsize>(size));
		file.close();

		//Write buffer into memory starting at 0x200
		for (long i = 0; i < static_cast<long>(size); i++)
		{
			memory[ROM_START_ADDRESS + i] = buffer[i];
		}

		//Free memory
		delete[] buffer;
	}

	else
	{
		std::fprintf(stderr, "Could not load specified ROM.\n");
		return;
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
	for (unsigned int i = 0; i < 16; i ++)
	{
		for (unsigned int j = 0; j < 5; j++)
		{
			memory[FONTSET_START_ADDRESS + (i * 5) + j] = fontSet[i].sprite[j];
		}
	}
}

void Chip8::CPUCycle()
{
	//Fetch current opcode (concatinate bytes at PC and PC+1 & store in opcode)
	opcode = (memory[PC] << 8) | memory[PC + 1];

	//Increment PC
	PC += 2;

	//Decode & execute

	//Decrement delay timer
	if (delayTimer > 0) delayTimer--;

	//Decrement sound timer
	if (soundTimer > 0) soundTimer--;
}