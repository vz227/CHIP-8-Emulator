#include <chip8.h>

Chip8::Chip8()
{
	//Set program counter to the address of the first instruction of the ROM, 0x200
	PC = ROM_START_ADDRESS;

	//Load character sprites at address 0x50
	LoadFont();

	//Initialize function pointer table
	table[0x0] = &Chip8::Table0;
	table[0x1] = &Chip8::OP_1nnn;
	table[0x2] = &Chip8::OP_2nnn;
	table[0x3] = &Chip8::OP_3xkk;
	table[0x4] = &Chip8::OP_4xkk;
	table[0x5] = &Chip8::OP_5xy0;
	table[0x6] = &Chip8::OP_6xkk;
	table[0x7] = &Chip8::OP_7xkk;
	table[0x8] = &Chip8::Table8;
	table[0x9] = &Chip8::OP_9xy0;
	table[0xA] = &Chip8::OP_Annn;
	table[0xB] = &Chip8::OP_Bnnn;
	table[0xC] = &Chip8::OP_Cxkk;
	table[0xD] = &Chip8::OP_Dxyn;
	table[0xE] = &Chip8::TableE;
	table[0xF] = &Chip8::TableF;

	//Assign *OP_NULL() to all addresses in table0[], table8[] & tableE[]
	for (int i{0}; i <= 0xE; ++i)
	{
		table0[i] = &Chip8::OP_NULL;
		table8[i] = &Chip8::OP_NULL;
		tableE[i] = &Chip8::OP_NULL;
	}

	//Assign *OP_NULL() to all addresses in tableF[]
	for (int j{0}; j <= 0x65; ++j)
	{
		tableF[j] = &Chip8::OP_NULL;
	}

	//Initialize subtable table0[]
	table0[0x0] = &Chip8::OP_00E0;
	table0[0xE] = &Chip8::OP_00EE;

	//Initialize subtable table8[]
	table8[0x0] = &Chip8::OP_8xy0;
	table8[0x1] = &Chip8::OP_8xy1;
	table8[0x2] = &Chip8::OP_8xy2;
	table8[0x3] = &Chip8::OP_8xy3;
	table8[0x4] = &Chip8::OP_8xy4;
	table8[0x5] = &Chip8::OP_8xy5;
	table8[0x6] = &Chip8::OP_8xy6;
	table8[0x7] = &Chip8::OP_8xy7;
	table8[0xE] = &Chip8::OP_8xyE;

	//Initialize subtable tableE
	tableE[0x1] = &Chip8::OP_ExA1;
	tableE[0xE] = &Chip8::OP_Ex9E;

	//Initialize subtable tableF
	tableF[0x07] = &Chip8::OP_Fx07;
	tableF[0x0A] = &Chip8::OP_Fx0A;
	tableF[0x15] = &Chip8::OP_Fx15;
	tableF[0x18] = &Chip8::OP_Fx18;
	tableF[0x1E] = &Chip8::OP_Fx1E;
	tableF[0x29] = &Chip8::OP_Fx29;
	tableF[0x33] = &Chip8::OP_Fx33;
	tableF[0x55] = &Chip8::OP_Fx55;
	tableF[0x65] = &Chip8::OP_Fx65;
}

Chip8::~Chip8() {}

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
		for (long i{0}; i < static_cast<long>(size); ++i)
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
	for (unsigned int i{0}; i < 16; ++i)
	{
		for (unsigned int j{0}; j < 5; ++j)
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
	(this->*table[(opcode & 0xF000) >> 12])();

	//Decrement delay timer
	if (delayTimer > 0) delayTimer--;

	//Decrement sound timer
	if (soundTimer > 0) soundTimer--;
}

void Chip8::Table0()
{
	(this->*table0[opcode & 0x000F])();
}

void Chip8::Table8()
{
	(this->*table8[opcode & 0x000F])();
}

void Chip8::TableE()
{
	(this->*tableE[opcode & 0x000F])();
}

void Chip8::TableF()
{
	(this->*tableF[opcode & 0x00FF])();
}
