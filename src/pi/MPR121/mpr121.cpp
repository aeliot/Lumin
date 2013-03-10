/**
 * MPR121 Library
 *
 * created on: 12/09/18
 * Version: 1.0
 *
 * Copyright 2012 Waiman Zhao <Binpower@foxmail.com>
 * Based on previous work by:
 *    Weibo: <http://weibo.com/binpower>
 *    QQ: <93242033>
 *		TaoBao: <http://waiman.taobao.com/>
*/

/*
 Power Supply: 3.3volts
 Hardware Connection:
           SDA -> A4
           SCL -> A5
           IRQ -> D2
*/

#include "../arduPi/arduPi.h"
#include "mpr121.h"

int bitRead(int val, int offset){
    return ((val>>offset) && 1);
}


//------------------- centigrade  -------------------------
MPR121::MPR121()
{
    Wire.begin();
    //config();
}

MPR121 CapaTouch=MPR121();


//------------------- WRITE register  -------------------------
void MPR121::mpwrite(uint8_t reg,uint8_t data)
{
    Wire.beginTransmission((uint8_t)MPR121_ADDR);

    Wire.write(reg);
    Wire.write(data);

    Wire.endTransmission();
}


//------------------- Read register  -------------------------
void MPR121::mpread(uint8_t reg,uint8_t length,uint8_t *ReturnData)
{
    Wire.beginTransmission(MPR121_ADDR);

    Wire.write(reg);


    //Wire.endTransmission();
    Wire.requestFrom((uint8_t)MPR121_ADDR, length);
    uint8_t i=0;
    //while(Wire.available())    // slave may send less than requested
    for(int n = 0; n < length; n++)
    {

        ReturnData[i] = Wire.read(); // receive a byte as character

        i++;
    }
}


//------------------- read Touch  -------------------------
int MPR121::touch(void)
{
    Wire.requestFrom((uint8_t)MPR121_ADDR,(uint8_t)2);
    uint8_t a,b;
    if(Wire.available()>=2)    // slave may send less than requested
    {
        a = Wire.read(); // receive a byte as character
        b = Wire.read();

        return (a | (int)(b<<8));
    }else
    {
        return 0;
    }
}


//------------------- MPR121 Config  -------------------------
void MPR121::begin(void){
    // STOP
    mpwrite(ELE_CFG, 0x00);
    mpwrite(RES_CF, 0X63);
    delay(10);
    // Section A
    // This group controls filtering when data is > baseline.
    mpwrite(MHD_R, 0x01);
    mpwrite(NHD_R, 0x01);
    mpwrite(NCL_R, 0x00);
    mpwrite(FDL_R, 0x00);

    // Section B
    // This group controls filtering when data is < baseline.
    mpwrite(MHD_F, 0x01);
    mpwrite(NHD_F, 0x01);
    mpwrite(NCL_F, 0xFF);
    mpwrite(FDL_F, 0x02);

    // Section C
    // This group sets touch and release thresholds for each electrode
    mpwrite(ELE0_T, TOU_THRESH);
    mpwrite(ELE0_R, REL_THRESH);
    mpwrite(ELE1_T, TOU_THRESH);
    mpwrite(ELE1_R, REL_THRESH);
    mpwrite(ELE2_T, TOU_THRESH);
    mpwrite(ELE2_R, REL_THRESH);
    mpwrite(ELE3_T, TOU_THRESH);
    mpwrite(ELE3_R, REL_THRESH);
    mpwrite(ELE4_T, TOU_THRESH);
    mpwrite(ELE4_R, REL_THRESH);
    mpwrite(ELE5_T, TOU_THRESH);
    mpwrite(ELE5_R, REL_THRESH);
    mpwrite(ELE6_T, TOU_THRESH);
    mpwrite(ELE6_R, REL_THRESH);
    mpwrite(ELE7_T, TOU_THRESH);
    mpwrite(ELE7_R, REL_THRESH);
    mpwrite(ELE8_T, TOU_THRESH);
    mpwrite(ELE8_R, REL_THRESH);
    mpwrite(ELE9_T, TOU_THRESH);
    mpwrite(ELE9_R, REL_THRESH);
    mpwrite(ELE10_T, TOU_THRESH);
    mpwrite(ELE10_R, REL_THRESH);
    mpwrite(ELE11_T, TOU_THRESH);
    mpwrite(ELE11_R, REL_THRESH);

    // Section D
    // Set the Filter Configuration
    // Set ESI2
    mpwrite(AFE1_CFG, 0x10);
    //AFE配置1 （默认=0x10）
    //	一级采样FFI:00-6次
    //	充放电电流CDC:100000 - 32uA
    mpwrite(AFE2_CFG, 0x04);
    //AFE配置2	（默认=0x24）
    //	充电时间CDT:010 - 1us
    //	二级采样SFI:00 - 4次
    //	二级采样间隔ESI:100 - 16ms


    // Section E
    // Electrode Configuration
    // Enable 6 Electrodes and set to run mode
    // Set ELE_CFG to 0x00 to return to standby mode
    mpwrite(ELE_CFG, 0x8C);	// Enables all 12 Electrodes

    //AFE配置1
    //	CL
    //	ELEPROX
    //	ELE:
    // Section F
    // Enable Auto Config and auto Reconfig
    /*mpwrite(ATO_CFG0, 0x0B);
    mpwrite(ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   mpwrite(ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
    mpwrite(ATO_CFGT, 0xB5);*/	// Target = 0.9*USL = 0xB5 @3.3V
}




//------------------- centigrade  -------------------------
int8_t MPR121::wheelKey(void)
{
    switch(touch())
    {
    case 0x0001:
        return 1;  // Electrode 0
        break;
    case 0x0003:
        return 2;  // Electrode 0 and 1
        break;
    case 0x0002:
        return 3;  // Electrode 1
        break;
    case 0x0006:
        return 4;  // Electrode 1 and 2
        break;
    case 0x0004:
        return 5;  // Electrode 2
        break;
    case 0x000C:
        return 6;  // Electrode 2 and 3
        break;
    case 0x0008:
        return 7;  // Electrode 3
        break;
    case 0x0018:
        return 8;  // Electrode 3 and 4
        break;
    case 0x0010:
        return 9;  // Electrode 4
        break;
    case 0x0030:
        return 10;  // Electrode 4 and 5
        break;
    case 0x0020:
        return 11;  // Electrode 5
        break;
    case 0x0060:
        return 12;  // Electrode 5 and 6
        break;
    case 0x0040:
        return 13;  // Electrode 6
        break;
    case 0x00C0:
        return 14;  // Electrode 6 and 7
        break;
    case 0x0080:
        return 15;  // Electrode 7
        break;
    case 0x0081:
        return 16;  // Electrode 7 and 0
        break;
    case 0x0100:
        return 20;  // Electrode 8 :centre button
        break;
    default:
        return -1;  // Release
        break;
    }
}

//------------------- centigrade  -------------------------
int8_t MPR121::keyPad(void)
{
    int var = touch();
    //Serial.println(var,HEX);
    if ((var&0x0001) >0) return 1;
    if ((var&0x0002) >0) return 4;
    if ((var&0x0004) >0) return 7;
    if ((var&0x0008) >0) return 11;

    if ((var&0x0010) >0) return 2;
    if ((var&0x0020) >0) return 5;
    if ((var&0x0040) >0) return 8;
    if ((var&0x0080) >0) return 0;

    if ((var&0x0100) >0) return 3;
    if ((var&0x0200) >0) return 6;
    if ((var&0x0400) >0) return 9;
    if ((var&0x0800) >0) return 12;

    return -1; // Release or other state
}


/************ Functions for getting the coordinate of the touch pad *************/
/************ A stupid way to get the right coodinate 0-0" **********************/

int MPR121::getX(void)
{
    int key = touch();
    int i,a,b,c,d,e,x;

    a=bitRead(key,0);
    b=bitRead(key,1);
    c=bitRead(key,2);
    d=bitRead(key,3);
    e=bitRead(key,4);
    if(key>0)
    {
        if(a==1&&b!=1)             return 1;                // Electrode 0
        if(a!=1&&b==1&&c!=1)       return 3;                // Electrode 1
        if(b!=1&&c==1&&d!=1)       return 5;                // Electrode 2
        if(c!=1&&d==1&&e!=1)       return 7;                // Electrode 3
        if(d!=1&&e==1)             return 9;                // Electrode 4

        if(a==1&&b==1)             return 2;                // Electrode 0 and 1
        if(b==1&&c==1)             return 4;                // Electrode 1 and 2
        if(c==1&&d==1)             return 6;                // Electrode 2 and 3
        if(d==1&&e==1)             return 8;                // Electrode 3 and 4
    }
    return -1;  // Release or other state
}


int MPR121::getY(void)
{
    int key = touch();
    int i,a,b,c,d,e,f,g,y;

    if(key>0)
    {
        a=bitRead(key,5);
        b=bitRead(key,6);
        c=bitRead(key,7);
        d=bitRead(key,8);
        e=bitRead(key,9);
        f=bitRead(key,10);
        g=bitRead(key,11);

        if(a==1&&b!=1)           return 1;                    // Electrode 5
        if(a!=1&&b==1&&c!=1)     return 3;                    // Electrode 6
        if(b!=1&&c==1&&d!=1)     return 5;                    // Electrode 7
        if(c!=1&&d==1&&e!=1)     return 7;                    // Electrode 8
        if(d!=1&&e==1&&f!=1)     return 9;                    // Electrode 9
        if(e!=1&&f==1&&g!=1)     return 11;                   // Electrode 10
        if(f!=1&&g==1)           return 13;                   // Electrode 11

        if(a==1&&b==1)           return 2;                    // Electrode 5 and 6
        if(b==1&&c==1)           return 4;                    // Electrode 6 and 7
        if(c==1&&d==1)           return 6;                    // Electrode 7 and 8
        if(d==1&&e==1)           return 8;                    // Electrode 8 and 9
        if(e==1&&f==1)           return 10;                   // Electrode 9 and 10
        if(f==1&&g==1)           return 12;                   // Electrode 10 and 11
    }
    return -1; // Release or other state
}




