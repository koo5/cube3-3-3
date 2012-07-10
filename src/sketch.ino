char cube[3][3][3];

void anim()
{
    cube[random(3)][random(3)][random(3)] = random(2);
}




const int OD = MISO;
const int ST = PD3;

void setup()
{
    pinMode(OD, OUTPUT);
    pinMode(ST, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(PC1, OUTPUT);
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

char row = 0;

void loop()
{
    row++;
    if (row == 3)
    {
	anim();
	row = 0;
    }
    
    char x,y;
    for (x=0;x<3;x++)
        for (y=0;y<3;y++)
        {
	    digitalWrite(MOSI, cube[row][x][y]);
	    so();
	}
    digitalWrite(OD, 1);
    st();
    digitalWrite(OD, 0);

}
