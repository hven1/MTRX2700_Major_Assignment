#include <hidef.h>
#include "derivative.h"
#include "iic.h"  
#include "pll.h"
#include "sci1.h"
#include "l3g4200.h"

#define laser_wr  0xc4
#define laser_rd  0xc5

#define gyro_wr 0xD2
#define gyro_rd 0xD3

#define accel_wr 0xA6    //
#define accel_rd 0xA7    // 
#define ADXL345_TO_READ 6
 
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATAX0 0x32
#define ADXL345_DATA_FORMAT 0x31
 
#define ADXL345_OFSX 0x1E
#define ADXL345_OFSY 0x1F
#define ADXL345_OFSZ 0x20
 
#define ALPHA 0.5

#define magnet_wr  0x3C
#define magnet_rd  0x3D

#define HM5883_MODE_REG 0x02
#define HM5883_DATAX0 0x03

#define BUFF_SIZE	100
extern char buff[BUFF_SIZE];
extern int gxraw[BUFF_SIZE];
extern int gyraw[BUFF_SIZE],gzraw[BUFF_SIZE];	

extern int axraw[BUFF_SIZE];
extern int ayraw[BUFF_SIZE],azraw[BUFF_SIZE];	

extern int mxraw[BUFF_SIZE];
extern int myraw[BUFF_SIZE],mzraw[BUFF_SIZE];	
extern int k;


/************************LIDAR**********************/

/***************************************************/

/************************Gyroscope**********************/
 //  Gyro Initialisation
 
 void gyro_init (void) {
  
	 int  res1;

	 res1=iicstart(gyro_wr);
	 res1=iictransmit(L3G4200D_CTRL_REG1 );  // ; 100hz, 12.5Hz, Power up
	 res1=iictransmit(0x0f );
	 iicstop();  
 }
 

void l3g4200d_getrawdata(int *gxraw, int *gyraw, int *gzraw) {
 	uint8_t i = 0;
	uint8_t buff[6];
	int res1;
	
   res1=iicstart(gyro_wr);
   res1=iictransmit(L3G4200D_OUT_XYZ_CONT );
   res1= iicrestart(gyro_rd); 
 
 iicswrcv();
 
 for(i=0; i<4  ;i++) {
  buff[i]=iicreceive();
 }
 
buff[i]= iicreceivem1();
buff[i+1]= iicreceivelast();

	*gxraw = ((buff[1] << 8) | buff[0]);
	*gyraw = ((buff[3] << 8) | buff[2]);
	*gzraw = ((buff[5] << 8) | buff[4]);
}

/***************************************************/

/***********************Magnetometer**********************/
void magnet_init(void){
  
  int  res1; 
  res1=iicstart(magnet_wr);
  res1=iictransmit(HM5883_MODE_REG );
  res1=iictransmit(0x00 );
  iicstop(); 
}

void hm5883_getrawdata(int *mxraw, int *myraw, int *mzraw){
  
 uint8_t i = 0;
 uint8_t buff[6];
 int res1;
	
 res1=iicstart(magnet_wr);
 res1=iictransmit(HM5883_DATAX0 );
 res1= iicrestart(magnet_rd); 
 iicswrcv();
 
 for(i=0; i<4  ;i++) {
  buff[i]=iicreceive();
 }
 
 buff[i]= iicreceivem1();
 buff[i+1]= iicreceivelast();

	*mxraw = ((buff[0] << 8) | buff[1]);
	*myraw = ((buff[2] << 8) | buff[3]);
	*mzraw = ((buff[4] << 8) | buff[5]);
}
/***************************************************/

/************************Accelerometer**********************/
void accel_init (void){
  
 int  res1;
 
 res1=iicstart(accel_wr);
 res1=iictransmit(ADXL345_POWER_CTL );  //  
 res1=iictransmit(0x08 );
  
 res1=iictransmit(ADXL345_DATA_FORMAT );  // ; 
 res1=iictransmit(0x08 );
  
 iicstop();  
}

void adxl345_getrawdata(int *axraw, int *ayraw, int *azraw){
  
 uint8_t i = 0;
 uint8_t buff[6];
 int res1;
	
 res1=iicstart(accel_wr);
 res1=iictransmit(ADXL345_DATAX0 );
 res1= iicrestart(accel_rd); 
 iicswrcv();
 
 for(i=0; i<4  ;i++) {
  buff[i]=iicreceive();
 }
 
 buff[i]= iicreceivem1();
 buff[i+1]= iicreceivelast();

	*axraw = ((buff[1] << 8) | buff[0]);
	*ayraw = ((buff[3] << 8) | buff[2]);
	*azraw = ((buff[5] << 8) | buff[4]);
}  

/***************************************************/
