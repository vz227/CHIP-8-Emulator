#include "chip8.h"

void Chip8::OP_00E0()
{
	//
	memset(video_buffer, 0, sizeof(video_buffer));
}

void Chip8::OP_00EE()
{
	
	PC = SP; // Set program counter to that of the top of the stack
	SP--;    // Decrement stack pointer
}

void Chip8::OP_1nnn()
{
	PC = opcode & 0x0FFF; //Set program counter to address nnn
}

void Chip8::OP_2nnn()
{	
	SP++;                 //Increment stack pointer	
	stack[SP] = PC;       //Put current stack pointer on top of the stack	
	PC = opcode & 0x0FFF; //Set PC to address nnn
}

void Chip8::OP_3xkk()
{
	// Compare value in register Vx with kk, and increment program counter by 2 if equal
	if (registers[opcode & 0x0F00] == (opcode && 0x00FF)) PC += 2;
}

void Chip8::OP_4xkk()
{
	// Compare value in register Vx with kk, and increment program counter by 2 if not equal
	if (registers[opcode & 0x0F00] != (opcode && 0x00FF)) PC += 2;
}

void Chip8::OP_5xy0()
{
	// Compare value in register Vx with that in register Vy, and increment program counter by 2 if equal
	if (registers[opcode & 0x0F00] == registers[opcode && 0x00F0]) PC += 2;
}

void Chip8::OP_6xkk()
{
	// Put value kk into register Vx
	registers[opcode & 0x0F00] = opcode & 0x00FF;
}

void Chip8::OP_7xkk()
{
	// Set Vx = Vx + kk
	registers[opcode & 0x0F00] += opcode & 0x00FF;
}

void Chip8::OP_8xy0()
{
	// Set Vx = Vy
	registers[opcode & 0x0F00] = registers[opcode & 0x00F0];
}

void Chip8::OP_8xy1()
{
	// Set Vx = Vx OR Vy
	registers[opcode & 0x0F00] |= registers[opcode & 0x00F0];
}

void Chip8::OP_8xy2()
{
	// Set Vx = Vx AND Vy
	registers[opcode & 0x0F00] &= registers[opcode & 0x00F0];
}

void Chip8::OP_8xy3()
{
	// Set Vx = Vx XOR Vy
	registers[opcode & 0x0F00] ^= registers[opcode & 0x00F0];
}

void Chip8::OP_8xy4()
{
	// Extract result
	Word result = (registers[opcode & 0x0F00] + registers[opcode & 0x00F0]);
	
	// Set carry register VF to 1 if result is greater than 8 bits, otherwise 0
	registers[0xF] = (result > 255) ? 1 : 0;

	// Store lowest 8 bits of result in Vx
	registers[opcode & 0x0F00] = (result & 0x00FF);	
}

void Chip8::OP_8xy5()
{
	// Set carry register VF to 1 if value in register Vx is greater than value in register Vy, otherwise 0
	registers[0xF] = (registers[opcode & 0x0F00] > registers[opcode & 0x00F0]) ? 1 : 0;

	// Subtract value in register Vy from value in register Vx and store result in register Vx
	registers[opcode & 0x0F00] -= registers[opcode & 0x00F0];
}

void Chip8::OP_8xy6()
{
	// Set carry register VF to 1 if least significant bit of value in register Vx is 1, otherwise 0
	registers[0xF] = ((registers[opcode & 0x0F00] & 0b00000001) == 0b00000001) ? 1 : 0;

	// Divide value in register Vx by 2 and store in Vx
	registers[opcode & 0x0F00] /= 2;
}

void Chip8::OP_8xy7()
{
	// Set carry register VF to 1 if value in register Vx is greater than value in register Vy, otherwise 0
	registers[0xF] = (registers[opcode & 0x0F00] < registers[opcode & 0x00F0]) ? 1 : 0;

	// Subtract value in register Vx from Vy and store result in register Vx
	registers[opcode & 0x0F00] = (registers[opcode & 0x00F0] - registers[opcode & 0x0F00]);
}

void Chip8::OP_8xyE()
{
	// Set carry register VF to 1 if least significant bit of value in register Vx is 1, otherwise 0
	registers[0xF] = ((registers[opcode & 0x0F00] & 0b00000001) == 0b00000001) ? 1 : 0;

	// Multiply value in register Vx by 2 and store in Vx
	registers[opcode & 0x0F00] *= 2;
}

void Chip8::OP_9xy0()
{
	// Skip next instruction if Vx != Vy
	if (registers[opcode & 0x0F00] != registers[opcode & 0x00F0]) PC += 2;
}

void Chip8::OP_Annn()
{
	// Set index to address nnn
	index = opcode & 0x0FFF;
}

void Chip8::OP_Bnnn()
{
	// Set PC to address nnn plus the value in register V0
	PC = (opcode & 0x0FFF) + registers[0];
}

void Chip8::OP_Cxkk()
{

}

void Chip8::OP_Dxyn()
{

}

void Chip8::OP_Ex9E()
{

}

void Chip8::OP_ExA1()
{

}

void Chip8::OP_Fx07()
{

}

void Chip8::OP_Fx0A()
{

}

void Chip8::OP_Fx15()
{

}

void Chip8::OP_Fx18()
{

}

void Chip8::OP_Fx1E()
{

}

void Chip8::OP_Fx29()
{

}

void Chip8::OP_Fx33()
{

}

void Chip8::OP_Fx55()
{

}

void Chip8::OP_Fx65()
{

}