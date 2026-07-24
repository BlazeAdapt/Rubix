#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_camera.h"
#include <ESP32Servo.h>
#include <Arduino.h>
#include <math.h>
#define TUA 45.0  //top servo up angle
#define TMA 90.0 //top servo middle angle
#define TDA 120.0 //top servo down angle
#define BRA 136.0 // bottom servo rotated angle
#define BUA 46.0 //bottom servo unrotated angle
//servo delay times and pins
#define timeD 500
#define timeU 600
#define PINTOP 13
#define PINBOT 15
//camera settings
#define WARMUP_FRAMES  10
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define FLASH_LED_PIN 4
#define FRAME_W 320
#define FRAME_H 240
#define NUM_COLORS 6
const char* ssid = "your wifi name";
const char* password = "your wifi password";
String url="https://rubix-n3cb.onrender.com/solve?state=";
HTTPClient http;
String ans;
Servo top;
Servo bottom;
char solution[100]={0};
char orientationof[256];
int k=0;
bool bottomrotated=true;
bool solvestarted=false;

struct Color {
  const char* name;
  char        code;  
 
  int   hLo, hHi;   
  int   sLo; 
  int   vLo;      
};

static const Color COLORS[] = {
  // name      code  hLo  hHi  sLo  vLo
   { "Yellow",  'Y',   50,  102, 0, 20  },
  { "Red",     'R',  300,  12,  80,  5  },
  { "Orange",  'O',   5,  50, 0 ,  20  },
  { "Green",   'G',   95, 165,   100,  10  },
  { "Blue",    'B',  165, 265,   100,  10  },
  { "White",   'W',    0, 360,    0, 100  },
};

struct HSV { float h; float s; float v; }; 

HSV rgbToHsv(uint8_t r, uint8_t g, uint8_t b) {
  float rf = r / 255.0f, gf = g / 255.0f, bf = b / 255.0f;
  float mx = max(rf, max(gf, bf));
  float mn = min(rf, min(gf, bf));
  float d  = mx - mn;

  float h = 0, s = (mx == 0) ? 0 : d / mx, v = mx;

  if (d > 0) {
    if      (mx == rf) h = fmod((gf - bf) / d, 6.0f);
    else if (mx == gf) h = (bf - rf) / d + 2.0f;
    else               h = (rf - gf) / d + 4.0f;
    h *= 60.0f;
    if (h < 0) h += 360.0f;
  }
  return { h, s * 255.0f, v * 255.0f };
}


const Color& classify(uint8_t r, uint8_t g, uint8_t b) {
  HSV hsv = rgbToHsv(r, g, b);

  if (hsv.s < 35) {
    // find White entry
    for (int i = 0; i < NUM_COLORS; i++)
      if (COLORS[i].code == 'W') return COLORS[i];
  }

  if((hsv.s<100 && hsv.h>=0 && hsv.h<16)||(hsv.h<COLORS[0].hHi && hsv.h>COLORS[0].hLo)||(hsv.h<COLORS[2].hHi && hsv.h>COLORS[2].hLo && hsv.s<100))
  {
    // find yellow entry
    for (int i = 0; i < NUM_COLORS; i++)
      if (COLORS[i].code == 'Y') return COLORS[i];
  }


  for (int i = 0; i < NUM_COLORS; i++) {
    const Color& c = COLORS[i];
    if (c.code == 'W') continue; 

    bool hOk;
    if (c.hLo <= c.hHi) {
      hOk = (hsv.h >= c.hLo && hsv.h <= c.hHi);
    } else {
      // wraps through 0 (e.g. Red: 350–10)
      hOk = (hsv.h >= c.hLo || hsv.h <= c.hHi);
    }

    if (hOk && hsv.s >= c.sLo && hsv.v >= c.vLo)
      return c;
  }

  static const Color UNKNOWN = { "Unknown", 'W', 0, 0, 0, 0 };
  return UNKNOWN;
}
char getopposite(char x){
  switch(x){
    case 'B':return 'G';
    case 'G':return 'B';
    case 'R':return 'O';
    case 'O':return 'R';
    case 'Y':return 'W';
    case 'W':return 'Y';
  }
}

void getPixelRGB(const uint8_t* buf, int w, int x, int y,
                 uint8_t& r, uint8_t& g, uint8_t& b) {
  int idx = (y * w + x) * 2;
  uint16_t pixel = ((uint16_t)buf[idx] << 8) | buf[idx + 1];
  r = (pixel >> 11) & 0x1F;  r = (r << 3) | (r >> 2);   
  g = (pixel >>  5) & 0x3F;  g = (g << 2) | (g >> 4);   
  b = (pixel >>  0) & 0x1F;  b = (b << 3) | (b >> 2);   
}

//camera initialise
bool initCamera() {
  camera_config_t cfg;
  cfg.ledc_channel = LEDC_CHANNEL_0;
  cfg.ledc_timer   = LEDC_TIMER_0;
  cfg.pin_d0       = Y2_GPIO_NUM;
  cfg.pin_d1       = Y3_GPIO_NUM;
  cfg.pin_d2       = Y4_GPIO_NUM;
  cfg.pin_d3       = Y5_GPIO_NUM;
  cfg.pin_d4       = Y6_GPIO_NUM;
  cfg.pin_d5       = Y7_GPIO_NUM;
  cfg.pin_d6       = Y8_GPIO_NUM;
  cfg.pin_d7       = Y9_GPIO_NUM;
  cfg.pin_xclk     = XCLK_GPIO_NUM;
  cfg.pin_pclk     = PCLK_GPIO_NUM;
  cfg.pin_vsync    = VSYNC_GPIO_NUM;
  cfg.pin_href     = HREF_GPIO_NUM;
  cfg.pin_sscb_sda = SIOD_GPIO_NUM;
  cfg.pin_sscb_scl = SIOC_GPIO_NUM;
  cfg.pin_pwdn     = PWDN_GPIO_NUM;
  cfg.pin_reset    = RESET_GPIO_NUM;
  cfg.xclk_freq_hz = 20000000;

 
  cfg.pixel_format = PIXFORMAT_RGB565;
  cfg.frame_size   = FRAMESIZE_QVGA;   
  cfg.jpeg_quality = 12;            
  cfg.fb_count     = 1;

  esp_err_t err = esp_camera_init(&cfg);
  sensor_t* s = esp_camera_sensor_get();
  if (s) {
    s->set_saturation(s,  1);    // boost color separation
    s->set_contrast(s,    0);
    s->set_brightness(s,  0);
    s->set_whitebal(s,    1);    // auto white balance on
    s->set_awb_gain(s,    1);
    s->set_wb_mode(s,     0);    // 0 = auto
    s->set_exposure_ctrl(s, 1);  // auto exposure on
    s->set_aec2(s,        1);
    s->set_gain_ctrl(s,   1);    // auto gain on
    s->set_agc_gain(s,    0);
    s->set_gainceiling(s, (gainceiling_t)2);
    s->set_bpc(s,  1);
    s->set_wpc(s,  1);
    s->set_raw_gma(s, 1);
    s->set_lenc(s,    1);
    s->set_hmirror(s, 0);
    s->set_vflip(s,   0);
    s->set_dcw(s,     1);
    s->set_colorbar(s,0);
  }
  return true;
}
  char      codes[9];



void doScan() {
 analogWrite(FLASH_LED_PIN, 15); 
  delay(100);
  for (int i = 0; i < WARMUP_FRAMES; i++) {
    camera_fb_t* fb = esp_camera_fb_get();
    if (fb) esp_camera_fb_return(fb);
    delay(30);
  }

  // Capture working frame
  camera_fb_t* fb = esp_camera_fb_get();

  int pointcount=0;
  int m=0;
  // Storage for 9 cells
  for(int i=0;i<9;i++){
  int cx,cy;
      int idx=i;
        if(i>4) m=0;
    switch(i){
  case 6: cx=30;cy=20;break; 
  case 7: cx=160;cy=40;break;
  case 8: cx=238;cy=25;break;
  case 3: cx=38;cy=90;break;
  case 4: cx=130;cy=100;break;
  case 5: cx=223;cy=110;break;
  case 0: cx=55;cy=147;break;
  case 1: cx=130;cy=155;break;
  case 2: cx=200;cy=160;break;
    }
              cx+=(m*20);
              cy-=(m*m*15);
              int cnt=0;
              long rSum = 0, gSum = 0, bSum = 0;
      for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++) {
          int px = cx + dx, py = cy + dy;
          if (px < 0 || py < 0 || px >= (int)fb->width || py >= (int)fb->height)
            continue;
          uint8_t r, g, b;
          getPixelRGB(fb->buf, fb->width, px, py, r, g, b);
          rSum += r; gSum += g; bSum += b;
          cnt++;
        }
      }
      uint8_t r = rSum / cnt;
      uint8_t g = gSum / cnt;
      uint8_t b = bSum / cnt;

      const Color& c = classify(r, g, b);

      if(i==4 && pointcount<2 && (c.code=='R'||c.code=='O')){i--;if(pointcount==0) m=1;else m=-1;pointcount++;} 

      codes[idx] = c.code;

      }

  esp_camera_fb_return(fb);

 analogWrite(FLASH_LED_PIN, 0); 
  delay(100);
}



void colorscan(){
  char ourcube[55];
  doScan();
  char scan1[10];
  for(int i=0;i<9;i++) scan1[i]=codes[i];
  scan1[9]='\0';


  bottom.write(BUA);delay(timeD);
  flip();
  doScan();

  char scan2[10];
  for(int i=0;i<9;i++) scan2[i]=codes[i];
  scan2[9]='\0';


  bottom.write(BRA);delay(timeD);flip();bottom.write(BUA);delay(timeD);
  doScan();
  char scan3[10];
  for(int i=0;i<9;i++) scan3[i]=codes[i];
  scan3[9]='\0';


  orientationof[scan1[4]]='U';
  orientationof[getopposite(scan1[4])]='D';
  orientationof[scan2[4]]='R';
  orientationof[getopposite(scan2[4])]='L';
  orientationof[scan3[4]]='F';
  orientationof[getopposite(scan3[4])]='B';
  for(int i=0;i<9;i++){
    ourcube[i]=orientationof[scan1[i]];
    ourcube[i+9]=orientationof[scan2[i]];
    ourcube[i+18]=orientationof[scan3[i]];
  }

  flip();
  doScan();
    for(int i=0;i<9;i++) ourcube[27+i]=orientationof[codes[i]];
    flip();
    doScan();
    for(int i=0;i<9;i++) ourcube[53-i]=orientationof[codes[i]];
    bottom.write(BRA);delay(timeD);flip();bottom.write(BUA);delay(timeD);
  doScan();
    for(int i=0;i<9;i++) ourcube[44-i]=orientationof[codes[i]];
    flip(); bottom.write(BRA);delay(timeD);
    ourcube[54]='\0';


    url=url+ourcube;

    findsol();
}

void setup() {
  Serial.begin(115200);
  http.setTimeout(3000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);

  }

    http.begin("https://rubix-n3cb.onrender.com/");
  int httpcode= http.GET();
  Serial.println(httpcode);
  delay(1000);

  if (!initCamera()) {
    while (true) delay(1000);
  }

  top.setPeriodHertz(50);
  bottom.setPeriodHertz(50);
  top.attach(PINTOP,500,2500);
  bottom.attach(PINBOT,500,2500);
  top.write(TMA);
  bottom.write(BRA);
  delay(1000);
  colorscan();
}


void fixsolDown(){
  int i=k;

  while(solution[i]!='\0'){
    if(solution[i]=='R') solution[i]='B';
    else if(solution[i]=='r') solution[i]='b';
    else if(solution[i]=='F') solution[i]='R';
    else if(solution[i]=='f') solution[i]='r';
    else if(solution[i]=='L') solution[i]='F';
    else if(solution[i]=='l') solution[i]='f';
    else if(solution[i]=='B') solution[i]='L';
    else if(solution[i]=='b') solution[i]='l';
    i++;
  }

  return;
}
void fixsolAntiDown(){
  int i=k;
  while(solution[i]!='\0'){
    if(solution[i]=='R') solution[i]='F';
    else if(solution[i]=='r') solution[i]='f';
    else if(solution[i]=='F') solution[i]='L';
    else if(solution[i]=='f') solution[i]='l';
    else if(solution[i]=='L') solution[i]='B';
    else if(solution[i]=='l') solution[i]='b';
    else if(solution[i]=='B') solution[i]='R';
    else if(solution[i]=='b') solution[i]='r';
    i++;
  }
  return;
}
void fixsolFlip(){
  int i=k;
  while(solution[i]!='\0'){
    if(solution[i]=='F') solution[i]='U';
    else if(solution[i]=='f') solution[i]='u';
    else if(solution[i]=='U') solution[i]='B';
    else if(solution[i]=='u') solution[i]='b';
    else if(solution[i]=='B') solution[i]='D';
    else if(solution[i]=='b') solution[i]='d';
    else if(solution[i]=='D') solution[i]='F';
    else if(solution[i]=='d') solution[i]='f';
    i++;
  }
  return;
}

void Down(){
  if(bottomrotated){
    bottom.write(BUA);
    delay(timeD);
    fixsolAntiDown();
  }
  top.write(TDA);delay(timeU);
  bottom.write(BRA+5);
  delay(timeD-100);
  bottom.write(BRA);
  delay(100);
  top.write(TMA);delay(timeU);
  bottomrotated=true;
}

void AntiDown(){
  if(!bottomrotated){
    bottom.write(BRA);
    delay(timeD);
    fixsolDown();
  }
  top.write(TDA);delay(timeU);
  bottom.write(BUA-5);
  delay(timeD-100);
  bottom.write(BUA);
  delay(100);
  top.write(TMA);delay(timeU);
  bottomrotated=false;
}



void flip(){
  top.write(TUA);
  delay(timeU);
  top.write(TMA);
  delay(timeU);
  if(solvestarted) fixsolFlip();
}
void fixflip(char x){
  if(x=='B' || x=='b') flip();
  else if(x=='F' || x=='f'){flip(); flip(); flip();}
  else if(x=='U' || x=='u'){flip(); flip();}
  else if(x=='R'|| x=='r'){
    if(bottomrotated){bottom.write(BUA);delay(timeD);bottomrotated=false;fixsolAntiDown();flip();flip();flip();}
    else {bottom.write(BRA);delay(timeD);bottomrotated=true;fixsolDown();flip();}
  }
  else if(x=='L'|| x=='l'){
    if(bottomrotated){bottom.write(BUA);delay(timeD);bottomrotated=false;fixsolAntiDown();flip();}
    else {bottom.write(BRA);delay(timeD);bottomrotated=true;fixsolDown();flip();flip();flip();}
  }
  return;
}

void fixans(){
  int a=0;int b=0;char templast;
  while(ans[a]!='\0'){
    if(ans[a]==' '){ a++;continue; }
    else if(ans[a]=='\'') { solution[b-1]=templast+32; a++ ; continue;}
    else if(ans[a]=='2'){ solution[b]=templast; b++; a++; continue;}
    else {solution[b]=ans[a]; templast=ans[a]; a++;b++;}
  }
  solution[b]='\0';
}

void solvecube(){
 while(solution[k]!='\0'){

  if(solution[k]=='D'){ Down();k++;}
  else if(solution[k]=='d'){ AntiDown();k++;}
  else (fixflip(solution[k])) ;
  }
}

void findsol() {
  HTTPClient htp;
  htp.begin(url);
  int httpcode=htp.GET();
  ans= htp.getString();
  htp.end();
  fixans();
  solvestarted=true;
  solvecube();
  }



void loop() {
}
