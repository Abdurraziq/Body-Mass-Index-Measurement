#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

// Pengaturan HX711
#define calibration_factor -22500
// Pengaturan pin HX711
#define pinDout 7
#define pinClk 6

// Pengaturan pin HC-SR04
#define pinTriger 12
#define pinEcho 11

// Definisi Lainnya
#define PRIA 0
#define WANITA 1

#define belas 12
#define puluh 13
#define seratus 14
#define ratus 15
#define seribu 16
#define ribu 17
#define koma 18

#define Tinggi_Anda 19
#define cm 20
#define Berat_Anda 21
#define kg 22

#define Indek_Massa_Tubuh_Anda 23
#define Normal 24
#define Kurang 25
#define Berlebih 26
#define Obesitas 27

#define Anda_Harus 28
#define Mempertahankan 29
#define Mengurangi 30
#define Menambah 31
#define Berat_anda_pada_kisaran 32
#define sampai_dengan 33

volatile bool jenisKelamin;
unsigned char keadaanBerat;
unsigned char saran;

HX711 scale;

Ultrasonic ultrasonic(pinTriger, pinEcho);
LiquidCrystal_I2C lcd(0x27, 20, 4);

String bil[] = {
	"nol ",
	"satu ",
	"dua ",
	"tiga ",
	"empat ",
	"lima ",
	"enam ",
	"tujuh ",
	"delapan ",
	"sembilan ",
	"sepuluh ",
	"sebelas ",
	"belas ",
	"puluh ",
	"seratus ",
	"ratus ",
	"seribu ",
	"ribu ",
	"koma ",

	"Tinggi Anda ",
	"cm ",
	"Berat Anda ",
	"kg ",

	"Indek Massa Tubuh Anda: ",
	"Normal ",
	"Kurang ",
	"Berlebih ",
	"Obesitas ",

	"Anda Harus ",
	"Mempertahankan ",
	"Mengurangi ",
	"Menambah ",
	"Berat anda pada kisaran ",
	"sampai dengan "};

void setup()
{
	Serial.begin(9600);
	pinMode(2, INPUT_PULLUP);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(13, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(2), ubahJenisKelamin, LOW);

	digitalWrite(4, !jenisKelamin);
	digitalWrite(5, jenisKelamin);

	lcd.begin();
	lcd.clear();
	lcd.backlight();

	tampilanAwal();
	
	scale.begin(pinDout, pinClk);
	scale.set_scale(calibration_factor);
	scale.tare();

	tamplate();
}

void loop()
{
	int tinggi = 200 - ultrasonic.distanceRead();
	int berat = (int)scale.get_units();
	float suhu = ((500.00 / 1023.00) * analogRead(A0)) + 2.50;
	float bmi = ((float)berat / pow(((float)tinggi / 100), 2));

	char temp[3];
	dtostrf(bmi, 3, 1, temp);
	String statusBerat = Status(bmi);

	lcd.setCursor(3, 0);
	lcd.print("   ");
	lcd.setCursor(3, 0);
	lcd.print(tinggi);

	lcd.setCursor(16, 0);
	lcd.print("  ");
	lcd.setCursor(16, 0);
	lcd.print((int)suhu);

	lcd.setCursor(3, 1);
	lcd.print("   ");
	lcd.setCursor(3, 1);
	lcd.print(berat);

	lcd.setCursor(16, 1);
	lcd.print("    ");
	lcd.setCursor(16, 1);
	lcd.print(temp);

	lcd.setCursor(12, 3);
	lcd.print("        ");
	lcd.setCursor(12, 3);
	lcd.print(statusBerat);

	if (berat > 2)
	{
		BacaData(tinggi, berat);
	}
	delay(1500);
}

void tampilanAwal()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("--------------------");
	lcd.setCursor(0, 3);
	lcd.print("--------------------");

	char baris1[] = "ALAT PENGUKUR";
	char baris2[] = "INDEKS MASSA TUBUH";

	lcd.setCursor(3, 1);
	for (int i = 0; i < sizeof(baris1) - 1; i++)
	{
		lcd.print(baris1[i]);
		delay(20);
	}
	delay(200);

	lcd.setCursor(1, 2);
	for (int i = 0; i < sizeof(baris2) - 1; i++)
	{
		lcd.print(baris2[i]);
		delay(20);
	}
	delay(2000);
}

void tamplate()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("T:     cm");
	lcd.setCursor(11, 0);
	lcd.print("S  :   " + (String)(char)223 + "C");
	lcd.setCursor(0, 1);
	lcd.print("B:     kg");
	lcd.setCursor(11, 1);
	lcd.print("BMI:     ");
	lcd.setCursor(0, 2);
	lcd.print("-------------------");
	lcd.setCursor(0, 3);
	lcd.print("BERAT ANDA: ");
}

String Status(float bmi)
{
	if (jenisKelamin == PRIA)
	{
		if (bmi < 18)
		{
			keadaanBerat = Kurang;
			saran = Menambah;
			return "KURANG";
		}
		else if (bmi >= 18 && bmi < 25)
		{
			keadaanBerat = Normal;
			saran = Mempertahankan;
			return "NORMAL";
		}
		else if (bmi >= 25 && bmi < 27)
		{
			keadaanBerat = Berlebih;
			saran = Mengurangi;
			return "BERLEBIH";
		}
		else if (bmi >= 27)
		{
			keadaanBerat = Obesitas;
			saran = Mengurangi;
			return "OBESITAS";
		}
	}
	else
	{
		if (bmi < 17)
		{
			keadaanBerat = Kurang;
			saran = Menambah;
			return "KURANG";
		}
		else if (bmi >= 17 && bmi < 23)
		{
			keadaanBerat = Normal;
			saran = Mempertahankan;
			return "NORMAL";
		}
		else if (bmi >= 23 && bmi < 27)
		{
			keadaanBerat = Berlebih;
			saran = Mengurangi;
			return "BERLEBIH";
		}
		else if (bmi >= 27)
		{
			keadaanBerat = Obesitas;
			saran = Mengurangi;
			return "OBESITAS";
		}
	}
}

void ubahJenisKelamin()
{
	_delay_ms(350);
	jenisKelamin = !jenisKelamin;
	digitalWrite(4, !jenisKelamin);
	digitalWrite(5, jenisKelamin);
	digitalWrite(13, jenisKelamin);
}

void BacaData(int dataTinggi, int dataBerat)
{

	Serial.print(bil[Tinggi_Anda]);
	suaraBilangan(dataTinggi);
	Serial.println(bil[cm]);

	Serial.print(bil[Berat_Anda]);
	suaraBilangan(dataBerat);
	Serial.println(bil[kg]);

	Serial.print(bil[Indek_Massa_Tubuh_Anda]);
	Serial.println(bil[keadaanBerat]);

	Serial.print(bil[Anda_Harus]);
	Serial.print(bil[saran]);
	Serial.print(bil[Berat_anda_pada_kisaran]);

	if (jenisKelamin == PRIA)
	{
		suaraBilanganDesimal(18.0 * pow(((float)dataTinggi / 100.00), 2));
	}
	else
	{
		suaraBilanganDesimal(17.0 * pow(((float)dataTinggi / 100.00), 2));
	}

	Serial.print(bil[kg]);
	Serial.print(bil[sampai_dengan]);

	if (jenisKelamin == PRIA)
	{
		suaraBilanganDesimal(25.0 * pow(((float)dataTinggi / 100.00), 2));
	}
	else
	{
		suaraBilanganDesimal(23.0 * pow(((float)dataTinggi / 100.00), 2));
	}

	Serial.println(bil[kg]);
}

void suaraBilanganDesimal(float Bilangan)
{
	uint32_t xtemp = (Bilangan + 0.005) * 100;
	uint32_t keseluruhan = Bilangan;
	uint16_t desimal = xtemp - (keseluruhan * 100);
	uint8_t desimal1 = (desimal / 10);
	uint8_t desimal2 = desimal - (desimal1 * 10);

	suaraBilangan(keseluruhan);

	if (desimal != 0)
	{
		Serial.print(bil[koma]);
		suaraBilangan(desimal1);
		suaraBilangan(desimal2);
	}
}

void suaraBilangan(uint32_t Bilangan)
{
	if (Bilangan < 100)
	{
		suaraPuluhan(Bilangan);
	}
	else if (Bilangan < 1000)
	{
		suaraRatusan(Bilangan);
	}
	else
	{
		suaraRibuan(Bilangan);
	}
}

void suaraPuluhan(uint8_t Bilangan)
{
	if (Bilangan < 12)
	{
		Serial.print(bil[Bilangan]);
	}
	else if (Bilangan < 20)
	{
		Serial.print(bil[Bilangan - 10]);
		Serial.print(bil[belas]);
	}
	else
	{
		uint8_t puluhan = Bilangan / 10;
		Serial.print(bil[puluhan]);
		Serial.print(bil[puluh]);

		puluhan *= 10;
		if (Bilangan - puluhan != 0)
		{
			Serial.print(bil[(Bilangan - puluhan)]);
		}
	}
}

void suaraRatusan(uint16_t Bilangan)
{
	uint8_t ratusan = (uint8_t)(Bilangan / 100);
	if (ratusan == 1)
	{
		Serial.print(bil[seratus]);
	}
	else
	{
		Serial.print(bil[ratusan]);
		Serial.print(bil[ratus]);
	}
	if (Bilangan % 100)
	{
		suaraPuluhan(Bilangan - (ratusan * 100));
	}
}

void suaraRibuan(uint32_t Bilangan)
{
	uint16_t ribuan = (uint16_t)(Bilangan / 1000);
	if (ribuan == 1)
	{
		Serial.print(bil[seribu]);
	}
	else if (ribuan < 100)
	{
		suaraPuluhan(ribuan);
		Serial.print(bil[ribu]);
	}
	else
	{
		suaraRatusan(ribuan);
		Serial.print(bil[ribu]);
	}

	if (Bilangan % 1000)
	{
		suaraBilangan(Bilangan - (ribuan * 1000));
	}
}
