# Project Untuk Pengukuran Indeks Massa Tubuh *(Body Mass Index)*

![coba](/block_diagram.png)

Inti dari project ini adalah bagaimana membuat sebuah alat pengukur indeks massa tubuh dengan menggunakan arduino dan beberapa perangkat pendukung lainnya. Project ini didesain agar setiap hasil pengukuran indeks massa tubuh dapat ditampilkan secara visual melalui LCD dan *serial monitor*.

## Kebutuhan Perangkat Keras

Untuk membangun alat pengukur indeks massa tubuh ini yang diperlukan beberapa perangkat keras yaitu;

1. Arduino Uno R3
2. Modul Sensor Ultrasonic HC-SR04
3. Load Cell
4. Modul HX-711
5. LM35
6. LCD Character 4 x 16 dengan modul I2C

## Skematik

![alt](/schematic.png)

## Kebutuhan Perangkat Lunak

Dalam implementasi kode program, project ini menggunakan beberapa aplikasi dan pustaka yaitu;

1. [Arduino IDE](https://https://www.arduino.cc/en/main/software)
2. Pustaka
   1. [Ultrasonic](https://github.com/ErickSimoes/Ultrasonic)
   2. [Wire](https://https://www.arduino.cc/en/Reference/Wire)
   3. [LiquidCrystal_I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)
   4. [HX711](https://github.com/bogde/HX711)

## Pengembangan Lanjutan

Dalam pengembanagan lanjutan project ini dapat dikembangkan dengan menambah fitur suara untuk membaca hasil pengukuran dengan menambahkan modul MP3.