#include "chip8.h"

void Chip8::OP_00E0()
{
	//Clear the video buffer
	memset(videoBuffer, 0, sizeof(videoBuffer));
}

void Chip8::OP_00EE()
{

	PC = stack[SP];		//Set program counter to that of the top of the stack
	SP--;				//Decrement stack pointer
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
	//Compare value in register Vx with kk, and increment program counter by 2 if equal
	if (registers[(opcode & 0x0F00) >> 8u] == (opcode & 0x00FF)) PC += 2;
}

void Chip8::OP_4xkk()
{
	//Compare value in register Vx with kk, and increment program counter by 2 if not equal
	if (registers[(opcode & 0x0F00) >> 8u] != (opcode & 0x00FF)) PC += 2;
}

void Chip8::OP_5xy0()
{
	//Compare value in register Vx with that in register Vy, and increment program counter by 2 if equal
	if (registers[(opcode & 0x0F00) >> 8u] == registers[(opcode & 0x00F0) >> 4u]) PC += 2;
}

void Chip8::OP_6xkk()
{
	//Put value kk into register Vx
	registers[(opcode & 0x0F00) >> 8u] = (opcode & 0x00FF);
}

void Chip8::OP_7xkk()
{
	//Set Vx = Vx + kk
	registers[(opcode & 0x0F00) >> 8u] += (opcode & 0x00FF);
}

void Chip8::OP_8xy0()
{
	//Set Vx = Vy
	registers[(opcode & 0x0F00) >> 8u] = registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy1()
{
	//Set Vx = Vx OR Vy
	registers[(opcode & 0x0F00) >> 8u] |= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy2()
{
	//Set Vx = Vx AND Vy
	registers[(opcode & 0x0F00) >> 8u] &= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy3()
{
	//Set Vx = Vx XOR Vy
	registers[(opcode & 0x0F00) >> 8u] ^= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy4()
{
	//Extract result
	Word result = (registers[(opcode & 0x0F00) >> 8u] + registers[(opcode & 0x00F0) >> 4u]);

	//Set carry register VF to 1 if result is greater than 8 bits, otherwise 0
	registers[0xF] = (result > 255) ? 1 : 0;

	//Store lowest 8 bits of result in Vx
	registers[(opcode & 0x0F00) >> 8u] = (result & 0x00FF);
}

void Chip8::OP_8xy5()
{
	//Set carry register VF to 1 if value in register Vx is greater than value in register Vy, otherwise 0
	registers[0xF] = (registers[(opcode & 0x0F00) >> 8u] > registers[(opcode & 0x00F0) >> 4u]) ? 1 : 0;

	//Subtract value in register Vy from value in register Vx and store result in register Vx
	registers[(opcode & 0x0F00) >> 8u] -= registers[(opcode & 0x00F0) >> 4u];
}

void Chip8::OP_8xy6()
{
	//Set carry register VF to 1 if least significant bit of value in register Vx is 1, otherwise 0
	registers[0xF] = ((registers[(opcode & 0x0F00) >> 8u] & 0b00000001) == 0b00000001) ? 1 : 0;

	//Divide value in register Vx by 2 and store in Vx
	registers[(opcode & 0x0F00) >> 8u] >>= 1;
}

void Chip8::OP_8xy7()
{
	//Set carry register VF to 1 if value in register Vx is greater than value in register Vy, otherwise 0
	registers[0xF] = (registers[(opcode & 0x0F00) >> 8u] < registers[(opcode & 0x00F0) >> 4u]) ? 1 : 0;

	// Subtract value in register Vx from Vy and store result in register Vx
	registers[(opcode & 0x0F00) >> 8u] = (registers[(opcode & 0x00F0) >> 4u] - registers[(opcode & 0x0F00) >> 8u]);
}

void Chip8::OP_8xyE()
{
	//Set carry register VF to 1 if least significant bit of value in register Vx is 1, otherwise 0
	registers[0xF] = ((registers[(opcode & 0x0F00) >> 8u] & 0b10000000) == 0b10000000) ? 1 : 0;

	//Multiply value in register Vx by 2 and store in Vx
	registers[(opcode & 0x0F00) >> 8u] <<= 1;
}

void Chip8::OP_9xy0()
{
	//Skip next instruction if Vx != Vy
	if (registers[(opcode & 0x0F00) >> 8u] != registers[(opcode & 0x00F0) >> 4u]) PC += 2;
}

void Chip8::OP_Annn()
{
	//Set index to address nnn
	index = opcode & 0x0FFF;
}

void Chip8::OP_Bnnn()
{
	//Set PC to address nnn plus the value in register V0
	PC = (opcode & 0x0FFF) + registers[0];
}

void Chip8::OP_Cxkk()
{
	//Generate random number from 0 to 255 & AND it with the value kk. Store result in register Vx
	//registers[(opcode & 0x0F00) >> 8u] = //randnum// & (opcode & 0x00FFu);
}

void Chip8::OP_Dxyn()
{
	//Save the amount of bytes to be read from memory, i.e. the height of the sprite
	int byte_count = opcode & 0x000F;

	//Save current coordinates making sure the coordinates wrap around if they're out of bounds
	Byte xPos = registers[(opcode & 0x0F00) >> 8u] % VIDEO_WIDTH;
	Byte yPos = registers[(opcode & 0x00F0) >> 4u] % VIDEO_HEIGHT;

	//Make sure register VF is cleared before drawing
	registers[0xF] = 0;

	//Iterate through byte count, i.e. each row of the sprite
	for (int byte = 0; byte < byte_count; byte++)
	{
		//Save current byte/row of the sprite
		Byte current_byte = memory[index + byte];

		//Iterate through bits of current row/byte
		for (int bit = 0; bit < 8; bit++)
		{
			//Save current pixel of current row
			Byte current_pixel = current_byte & (0x80u >> bit);

			//Save pointer to current screen pixel (as a DWord for convenience with SDL)
			DWord* screen_pixel = &videoBuffer[((yPos + byte) % VIDEO_HEIGHT) * VIDEO_WIDTH + ((xPos + bit) % VIDEO_WIDTH)];

			if (current_pixel)
			{
				//Set register VF to 1 or 0 depending on whether a pixel is made to be erased
				if (*screen_pixel == 0xFFFFFFFF) registers[0xF] = 1;

				//XOR the screen pixel with the sprite pixel
				*screen_pixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void Chip8::OP_Ex9E()
{
	//Save key from opcode
	Byte key = registers[(opcode & 0x0F00) >> 8u];

	//Check whether key is pressed, if so, increment PC by 2
	if (keypad & (1 << key)) PC += 2;
}

void Chip8::OP_ExA1()
{
	//Save key from opcode
	Byte key = registers[(opcode & 0x0F00) >> 8u];

	//Check whether key is pressed, if not, increment PC by 2
	if (!(keypad & (1 << key))) PC += 2;
}

void Chip8::OP_Fx07()
{
	//Place value of delayTimer in register Vx
	registers[(opcode & 0x0F00) >> 8u] = delayTimer;
}

void Chip8::OP_Fx0A()
{
	//Decrement PC by 2 & return to run the same instruction if no key is pressed
	if (!keypad)
	{
		PC -= 2;
		return;
	}

	//Save register number
	Byte Vx = (opcode & 0x0F00) >> 8u;

	//Iterate through all keys, store first pressed key in Vx, and break
	for (int i = 0; i < 16; i++)
	{
		if (keypad & (1 << i))
		{
			registers[Vx] = i;
			break;
		}
	}
}

void Chip8::OP_Fx15()
{
	//Set delay timer to the value stored in Vx
	delayTimer = registers[(opcode & 0x0F00) >> 8u];
}

void Chip8::OP_Fx18()
{
	//Set sound timer to the value stored in Vx
	soundTimer = registers[(opcode & 0x0F00) >> 8u];
}

void Chip8::OP_Fx1E()
{
	//Increment index by the value stored in Vx
	index += registers[(opcode & 0x0F00) >> 8u];
}

void Chip8::OP_Fx29()
{
	//Set index to the location in memory of the sprite for digit stored in Vx
	index = 0x050 + (5 * registers[(opcode & 0x0F00) >> 8u]);
}

void Chip8::OP_Fx33()
{
	//Save value stored in register Vx
	Byte Vx = registers[(opcode & 0x0F00) >> 8u];

	memory[index] = Vx / 100;				//Store hundreds digit at memory location of index
	memory[index + 1] = (Vx % 100) / 10;	//Store tens digit at memory location of index + 1
	memory[index + 2] = Vx % 10;			//Store ones digit at memory location index + 2
}

void Chip8::OP_Fx55()
{
	//Store registers V0 through Vx in memory starting at location I
	for (int i = 0; i <= ((opcode & 0x0F00) >> 8u); i++)
	{
		memory[index + i] = registers[i];
	}
}

void Chip8::OP_Fx65()
{
	//Read memory starting from location I into registers V0 through Vx
	for (int i = 0; i <= ((opcode & 0x0F00) >> 8u); i++)
	{
		registers[i] = memory[index + i];
	}
}

void Chip8::OP_NULL()
{
	return;
}