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
	if (registers[(opcode & 0x0F00) >> 8u] == (opcode & 0x00FF)) PC += 2;
}

void Chip8::OP_4xkk()
{
	// Compare value in register Vx with kk, and increment program counter by 2 if not equal
	if (registers[(opcode & 0x0F00) >> 8u] != (opcode & 0x00FF)) PC += 2;
}

void Chip8::OP_5xy0()
{
	// Compare value in register Vx with that in register Vy, and increment program counter by 2 if equal
	if (registers[(opcode & 0x0F00) >> 8u] == registers[(opcode & 0x00F0) >> 4u]) PC += 2;
}

void Chip8::OP_6xkk()
{
	// Put value kk into register Vx
	registers[(opcode & 0x0F00) >> 8u] = opcode & 0x00FF;
}

void Chip8::OP_7xkk()
{
	// Set Vx = Vx + kk
	registers[(opcode & 0x0F00) >> 8u] += opcode & 0x00FF;
}

void Chip8::OP_8xy0()
{
	// Set Vx = Vy
	registers[(opcode & 0x0F00) >> 8u] = registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy1()
{
	// Set Vx = Vx OR Vy
	registers[(opcode & 0x0F00) >> 8u] |= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy2()
{
	// Set Vx = Vx AND Vy
	registers[(opcode & 0x0F00) >> 8u] &= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy3()
{
	// Set Vx = Vx XOR Vy
	registers[(opcode & 0x0F00) >> 8u] ^= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy4()
{
	// Extract result
	Word result = (registers[(opcode & 0x0F00) >> 8u] + registers[(opcode & 0x00F0) >> 4u]);
	
	// Set carry register VF to 1 if result is greater than 8 bits, otherwise 0
	registers[0xF] = (result > 255) ? 1 : 0;

	// Store lowest 8 bits of result in Vx
	registers[(opcode & 0x0F00) >> 8u] = (result & 0x00FF);	
}

void Chip8::OP_8xy5()
{
	// Set carry register VF to 1 if value in register Vx is greater than value in register Vy, otherwise 0
	registers[0xF] = (registers[(opcode & 0x0F00) >> 8u] > registers[(opcode & 0x00F0) >> 4u]) ? 1 : 0;

	// Subtract value in register Vy from value in register Vx and store result in register Vx
	registers[(opcode & 0x0F00) >> 8u] -= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy6()
{
	// Set carry register VF to 1 if least significant bit of value in register Vx is 1, otherwise 0
	registers[0xF] = ((registers[opcode & 0x0F00] & 0b00000001) == 0b00000001) ? 1 : 0;

	// Divide value in register Vx by 2 and store in Vx
	registers[(opcode & 0x0F00) >> 8u] /= 2;
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
	//Generate random number from 0 to 255 & AND it with the value kk. Store result in register Vx
	registers[(opcode & 0x0F00) >> 8u] = randByte(randGen) & (opcode & 0x00FFu);
}

void Chip8::OP_Dxyn()
{
	// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.

	// The interpreter reads n bytes from memory, starting at the address stored in I.
	// These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen.
	// If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display,
	// it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display,
	// for more information on the Chip-8 screen and sprites.


	//Save the amount of bytes to be read from memory
	int n = registers[opcode & 0x000F];

	//Save current coordinates making sure the coordinates wrap around if they're out of bounds
	Byte xPos = (registers[opcode & 0x0F00] >> 8) % VIDEO_WIDTH;
	Byte yPos = (registers[opcode & 0x00F0] >> 4) % VIDEO_HEIGHT;

	for (int i = 0; i < n; i++)
	{

	}
}

void Chip8::OP_Ex9E()
{
	//Check whether button with value of Vx is pressed, and if so, increment the PC by 2
	if ((keypad[registers[(opcode & 0x0F00) >> 8]] & 0b10000000) == 128) PC += 2;
}

void Chip8::OP_ExA1()
{
	//Check whether button with value of Vx is pressed, and if not, increment the PC by 2
	if ((keypad[registers[(opcode & 0x0F00) >> 8]] & 0b10000000) == 0) PC += 2;
}

void Chip8::OP_Fx07()
{
	//Place value of delayTimer in register Vx
	registers[opcode & 0x0F00 >> 8] = delayTimer;
}

void Chip8::OP_Fx0A()
{
	//Wait for a key press, store the value of the key in Vx.
	//All execution stops until a key is pressed, then the value of that key is stored in Vx.



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