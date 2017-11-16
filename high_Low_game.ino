//FND pin layout
enum
{
	DISP1 = 2,
	DISP2 = 3,
	DISP3 = 4,

	FND_A = 5,
	FND_B = 6,
	FND_C = 7,
	FND_D = 8,
	FND_E = 9,
	FND_F = 10,
	FND_G = 11,
};

// Font array index
enum
{
	FONT_0 = 0,
	FONT_1,
	FONT_2,
	FONT_3,
	FONT_4,
	FONT_5,
	FONT_6,
	FONT_7,
	FONT_8,
	FONT_9,

	FONT_H,
	FONT_L,
	FONT_I,
	FONT_O
};
//Font array
uint8_t fnd_font[14][7] = {	1, 1, 1, 1, 1, 1, 0
							,0, 1, 1, 0, 0, 0, 0
							,1, 1, 0, 1, 1, 0, 1
							,1, 1, 1, 1, 0, 0, 1
							,0, 1, 1, 0, 0, 1, 1
							,1, 0, 1, 1, 0, 1, 1
							,1, 0, 1, 1, 1, 1, 1
							,1, 1, 1, 0, 0, 1, 0
							,1, 1, 1, 1, 1, 1, 1
							,1, 1, 1, 1, 0, 1, 1
							,0, 1, 1, 0, 1, 1, 1
							,0, 0, 0, 1, 1, 1, 0
							,0, 0, 0, 0, 1, 1, 0
							,0, 0, 1, 1, 1, 0, 1};

//remote controller command index
enum
{
	REMOTE_CONFIRM = 0,
	REMOTE_0,
	REMOTE_1,
	REMOTE_2,
	REMOTE_3,
	REMOTE_4,
	REMOTE_5,
	REMOTE_6,
	REMOTE_7,
	REMOTE_8,
	REMOTE_9,
};
//remote controller command
uint32_t remote_val[11] = {	0xFFA857 //confirm
							, 0xFF6897 //0
							, 0xFF30CF //1
							, 0xFF18E7 //2
							, 0xFF7A85 //3
							, 0xFF10EF //4
							, 0xFF38C7 //5
							, 0xFF5AA5 //6
							, 0xFF42BD //7
							, 0xFF4AB5 //8
							, 0xFF52AD}; //9


void digit3_disp_num(int num, int val)
{
	//select
	switch(num)
	{
	case 1:
		digitalWrite(DISP1, HIGH);
		digitalWrite(DISP2, LOW);
		digitalWrite(DISP3, LOW);
		break;
	case 2:
		digitalWrite(DISP1, LOW);
		digitalWrite(DISP2, HIGH);
		digitalWrite(DISP3, LOW);
		break;
	case 3:
		digitalWrite(DISP1, LOW);
		digitalWrite(DISP2, LOW);
		digitalWrite(DISP3, HIGH);
		break;
	default :
		digitalWrite(DISP1, LOW);
		digitalWrite(DISP2, LOW);
		digitalWrite(DISP3, LOW);
		break;
	}

	//write value
	for(int i = 0; i < 7; i++)
	{
		digitalWrite(FND_A+i, !fnd_font[val][i]);
	}
	delay(10);
}

void display_high_low(bool val)
{
	switch(val)
	{
	case HIGH:
		digitalWrite(DISP1, HIGH);
		digitalWrite(DISP2, LOW);
		digitalWrite(DISP3, LOW);

		//write value
		for(int i = 0; i < 7; i++)
		{
			digitalWrite(FND_A+i, !fnd_font[FONT_H][i]);
		}
		delay(10);

		digitalWrite(DISP1, LOW);
		digitalWrite(DISP2, HIGH);
		digitalWrite(DISP3, LOW);

		//write value
		for(int i = 0; i < 7; i++)
		{
			digitalWrite(FND_A+i, !fnd_font[FONT_I][i]);
		}
		delay(10);
		break;
	case LOW:
		digitalWrite(DISP1, HIGH);
		digitalWrite(DISP2, LOW);
		digitalWrite(DISP3, LOW);

		//write value
		for(int i = 0; i < 7; i++)
		{
			digitalWrite(FND_A+i, !fnd_font[FONT_L][i]);
		}
		delay(10);

		digitalWrite(DISP1, LOW);
		digitalWrite(DISP2, HIGH);
		digitalWrite(DISP3, LOW);

		//write value
		for(int i = 0; i < 7; i++)
		{
			digitalWrite(FND_A+i, !fnd_font[FONT_O][i]);
		}
		delay(10);
		break;
	default:
		break;
	}
}

void setup()
{
	//FND SETUP
	for(int i = 0; i < 12; i++)
	{
		pinMode(i+2, OUTPUT);
	}
}

void loop()
{
	display_high_low(HIGH);
}
