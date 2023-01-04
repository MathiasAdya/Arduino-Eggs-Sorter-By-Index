//https://github.com/MathiasAdya
#include "KickSort.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte ldr = A2;  // LDR pin A2
byte led = 8;  // LED pin 8

//INPUT VARIABLES
const uint16_t samples=6;
signed arr[samples];
signed index[samples];

//ALGORITMA BINARY SEAR6CH
signed binarySearch(int l, int r, int cnt) {
  int mid=(l+r)/2;  
  if (l<=r) {
    if (arr[mid]>index[cnt]) binarySearch(l,mid-1,cnt);
    else if(arr[mid]<index[cnt]) binarySearch(mid+1,r,cnt);
    else return mid;
  }
  else return mid; 
}

void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  digitalWrite(led, HIGH);
  lcd.setCursor(1,0);
  lcd.print("Masukkan Telur");
  lcd.setCursor(2,1);
  lcd.print("(Kelompok 2)");
  delay (7500);
  lcd.clear();
  signed cahaya;
  int i=1;
  lcd.setCursor(0,0);
  while (i<=5) {
      cahaya = analogRead(ldr);//MEMBACA SENSOR LDR
      cahaya-=i;
      Serial.print("Cahaya ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(cahaya);
      Serial.println();
      lcd.print("Telur ");
      lcd.print(i);
      lcd.print(": ");
      lcd.setCursor(0,1);
      if (cahaya>=50) {
        lcd.print("Segar");
        // continue;
      }
      else {
        lcd.print("Tidak Segar");
        // continue;
      }
      arr[i]=cahaya;
      index[i]=arr[i];
      //if (i==1) cahaya=250;//2
      //if (i==4) cahaya=10;//5
      //if (i==3) cahaya=200;//4
      //if (i==2) cahaya=60;//3
      //tunggu 10 detik buat masukkin egg baru;
      for (int i=10; i>=0; i--) {
        lcd.setCursor(13,1);
        lcd.print(i);
        lcd.print("s");
        lcd.print(" ");
        delay(1000);
      }
      lcd.clear();
      lcd.blink();
      i++;
  }
  KickSort<uint16_t>::quickSort(arr, samples);//SORT ARRAY BARU
  Serial.print("Sorted Array: ");
  for (int i=1; i<=5; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
  signed ans[samples];
  for (int i=1; i<=5; i++) { //MEMASUKAN SORTED EGG BERDASARKAN INDEX //DARI BINARY SEARCH
    int mid=binarySearch(1, 5, i);
    ans[mid]=i;
    // if (ans[i]==0) ans[i]=5;
  }
  lcd.print("Kesegaran Telur: ");
  lcd.setCursor(0,1);
  Serial.print("Sorted by Index: ");
  for (int i=5; i>=1; i--) { //OUTPUT KE LCD SESUAI KESEGARAN TELUR
    lcd.print(ans[i]);
    Serial.print(ans[i]);
    if (i==1) continue;
    Serial.print(">");
    lcd.print(">");
  }
  Serial.println();
  Serial.println("New Input");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.clear();
}
