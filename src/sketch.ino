const int OD = MISO;
const int ST = PD3;
const int RED = PC2;



char cube[3][3][4];

void anim()
{
/*
    static char anim;
    anim ++;
    if (anim < 25) return;
    anim = 0;
    
    {
    char x = random(3);
    char y = random(3);
    
    cube[x][y][3] = !cube[x][y][3];
    }
    

    {
    //char x = random(3);
    //char y = random(3);

    char x,y;
    for (x=0;x<3;x++)
        for (y=0;y<3;y++)
        {
	    cube[x][y][0] = cube[x][y][1];
	    cube[x][y][1] = cube[x][y][2];
	    cube[x][y][2] = cube[x][y][3];
	}
    }
*/    



    
    
    
}


void setup()
{
    OSCCAL = 0xff;

    Serial.begin(9600);
    
    DDRC = 0b10;
    PORTC = 0b10;
        
    pinMode(PD7, OUTPUT);
    digitalWrite(PD5, 1);
    digitalWrite(PB1, 1);
    
    pinMode(OD, OUTPUT);
    pinMode(ST, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(RED, OUTPUT);
}

void so()
{
    digitalWrite(SCK, 0);
    digitalWrite(SCK, 1);
}

void st()
{
    digitalWrite(ST, 0);
    digitalWrite(ST, 1);
}

void d(char dd)
{
    digitalWrite(MOSI, dd); so();
}


char decoder(char i)
{
    char dir;
    static char j=i;
    if (j == i)
	dir = 0;
    if(
	((j == 0)&&(i == 1))
	||
	((j == 1)&&(i == 3))
	||
	((j == 3)&&(i == 0))
	    )
		dir = 1;
    else if(
	((j == 0)&&(i == 3))
	||
	((j == 3)&&(i == 1))
	||
	((j == 1)&&(i == 0))
	    )
		dir =-1;
	j=i;
	return dir;
}
    

char row = 0;

void loop()
{
    row++;
    if (row == 3)
    {
	anim();
//	anim2();
	row = 0;
    }
    
    cube[0][0][0] = PIND & 0b100000;
    cube[0][1][0] = PINB & 0b10;
//    Serial.println(((PIND & 0b100000)>>5) | (PINB & 0b10));
    char dec = decoder(((PIND & 0b100000)>>5) | (PINB & 0b10));
    cube[1][1][0] = 0;
    cube[1][1][1] = 0;
    cube[1][1][2] = 0;
    cube[1][1][1+dec] = 1;
    
    d(row == 0);
    d(row == 1);
    d(row == 2);

    d(0);
    d(0);
    d(0);

    char x,y;
    for (x=0;x<3;x++)
        for (y=0;y<3;y++)
	    d(cube[x][y][row]);

    digitalWrite(OD, 1);
    digitalWrite(OD, 1);
    digitalWrite(OD, 1);
    st();
    digitalWrite(OD, 1);
    digitalWrite(OD, 1);
    digitalWrite(OD, 0);

}
