/*
------------------------------------------------------------
Copyright 2003-201x Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
File name :	main.c
Author and date :	Monnerat Serge 29 ao�t 2013

Description in the header (.h)

-----------------------------------------------------------------------------
History:
-----------------------------------------------------------------------------

$History: $

-----------------------------------------------------------------------------
*/
#include "MK64F12.h"
#include "mSpi.h"
#include "mDac.h"
#include "mAccelMagneto.h"
#include "mWifi.h"
#include "mTimer.h"
#include "mCpu.h"
#include "mSwitch.h"
#include "mLeds.h"
#include "mAd.h"
#include "mDelay.h"
#include "mRs232.h"
#include "stdio.h"
#include "stbp.h"
#include "gInput.h"
#include "gCompute.h"
#include "gOutput.h"

//-------------------------------------------------------------------------
// Variables globales utiles pour la mesure de vitesse, l'acquisition de l'image
// et l'acquisition du magn�tom�tre et acc�l�rom�tre
//-------------------------------------------------------------------------
// Tableau contenant l'image (et diverses infos) de la camera
// digitale, le tableau test est utilis� pour l'app Labview
static UInt8 sImageTab[200];
static UInt16 sImageTabTest[200];

// Mesure de l'acc�l�rom�tre et du magn�tom�tre
static SRAWDATAEnum sAccel;				// en g
static SRAWDATAEnum sMagneto;			// en micro teslas
//static UInt8 sAccelMagnetoStatus;	
float sYaw;		// en degr�s
float sRoll;	// en degr�s
float sPitch;	// en degr�s

// Mesure de vitesse et de sens
float sSpeedMotLeft;
float sSpeedMotRight;

//-------------------------------------------------------------------------
// Variables et constantes utiles au monitoring
//-------------------------------------------------------------------------
// Taille des buffer RX et TX
#define kBUFFERSIZE 	500
#define kTxBUFFERSIZE	1000

// STBP message ID
#define Frame1_MSGID	1	// Identifacateur du 1er message transmis
#define Frame2_MSGID	2 // Identifacateur du 2e message transmis

// Variables utiles pour la transmission de donn�es
// selon le protocole ST et par WIFI
static CStbp sMyComm;													// Structure de contr�le d'un buffer
static CStbp * sMyCommPtr = &sMyComm;					// Pointeur sur la structure de contr�le
static UInt8 sMyCommRxBuffer[kBUFFERSIZE];		// Buffer contenant les donn�es brutes re�ues
static UInt8 sMyCommTxBuffer[kBUFFERSIZE];		// Buffer contenant les donn�es � transmettre
static UInt16 sNumberOfTransferredBytes = 0;	// Nb de byte � transmettre
UInt8 sTxMsgBuffer[kTxBUFFERSIZE] = {0};			// Buffer contenant les donn�es � transmettre
UInt8* sTxMsgBufferPtr = sTxMsgBuffer;				// Pointeur sur le Buffer contenant les donn�es � transmettre

// Structure de donn�es en r�ception WIFI --> doit-�tre identique de chaque c�t� de la transmission
typedef struct 
{
	int type;
	int temp;
	int time;
	float tata[20];
	char titi;
}CmdMenuStruct;
static CmdMenuStruct sFrameRxWifi;
static UInt8 *sFrameRxWifiPtr=(UInt8*)&sFrameRxWifi;
static Int16 sDlyJava;

// Test envoi de donn�es � l'app JAVA
void SendDataJava(void);

// Test r�ception de donn�es de l'app JAVA
void ReadDataJava(void);

// Init pour la comm de l'app JAVA
void InitDataJava(void);

//-------------------------------------------------------------------------
// Programme principal
//-------------------------------------------------------------------------
int main(void)
{
	static Int16 sDly;
	UInt32 i=0;
	static UInt16 aStatus;
	bool aRet;
	Int8 aChar;
	float aDuty=0;
	Int8 aCharTab[50];
	static UInt16 sIntTime=25000;
	static bool OldSw1=false;
	static bool OldSw2=false;
	bool aVal;
	static bool sSocketOpen=true;
	
	//--------------------------------------------------------------------
	// Initialisation du protocole ST pour la comm wifi
	//--------------------------------------------------------------------
	InitDataJava();
		
	//--------------------------------------------------------------------
	// Setup des p�riph�riques et de la carte
	//--------------------------------------------------------------------
	// Config de la PLL --> CPU 100MHz, bus et p�riph 50MHz
	mCpu_Setup();
	
	// Config et start des interrupteurs et poussoirs
	mSwitch_Setup();
	mSwitch_Open();
	
	// Config et start des Leds
	mLeds_Setup();
	mLeds_Open();
	
	// Config et start de l'ADC
	mAd_Setup();
	mAd_Open();
		
	// Config et start du SPI
	mSpi_Setup();
	mSpi_Open();
	
	// Config et start des delay non bloquant par PIT
	mDelay_Setup();
	mDelay_Open();
	
	// Config des timer pour la mesure de vitesse et les sorties PWM pour les servos
	mTimer_Setup();
	mTimer_Open();
	
	// Setup FXOS8700CQ 
	mAccelMagneto_Setup();
	mAccelMagneto_Open();
	
	// Config et start du DAC0 utilis� pour piloter le driver LED �clairage
	mDac_Setup();
	mDac_Open();
	
	// Setup et start de la commandes des PWMs moteur et servo ainsi que la mesure de vitesse
	mTimer_Setup();
	mTimer_Open();
	
	// Enable des IRQ au niveau du CPU -> Primask
	__enable_irq();

	// UART 3 module configuration et start --> wifi autobaud
	mWifi_Setup();
	mWifi_Open();
	
	// UART 4 monitoring image
	mRs232_Setup();
	mRs232_Open();
	
	// SPI0 --> cam�ra SPI --> reset + idle command
	mSpi_MLX75306_Reset();
	
	//--------------------------------------------------------------------
	// Init et calibration de l'acc�l�rom�tre et du magn�tom�tre
	//--------------------------------------------------------------------
#if(kWithAccel)
	// Init du FXOS8700CQ
	aRet=mAccelMagneto_Init();
	// Calibration de l'offset de l'acc�l�rom�tre
	aRet=mAccelMagneto_Accel_Calibration();
	// Calibration de l'offset du magn�tom�tre
	aRet=mAccelMagneto_Mag_Calibration();
#endif
	
	//--------------------------------------------------------------------
	// Config wifi, Adhoc --> Pour le Laptop se mettre en static IP
	// --> Laptop IP: 192.168.1.172
	// --> Subnet mask: 255.255.255.0
	// --> Gateway: 192.168.1.1
	// --> WEP, 12345ABCDE
	//--------------------------------------------------------------------
	// S�lection de la bande:
	aRet=mWifi_SendCmd("at+rsi_band=0\r\n");
	// Init:
	aRet=mWifi_SendCmd("at+rsi_init\r\n");
	// Network Type: AdHoc, canal 6
	// !! Chaque �quipe prend un canal diff�rent, ici 6
	aRet=mWifi_SendCmd("at+rsi_network=IBSS_SEC,1,6\r\n");
	// Set PSK: 
	aRet=mWifi_SendCmd("at+rsi_psk=12345ABCDE\r\n");
	// Create IBSS network: 
	// Chaque �quipe avec un non diff�rent
	aRet=mWifi_SendCmd("at+rsi_join=FREESCALE_CUP_C6,0,2\r\n");
	// IP Address Configuration (DHCP Manual): 
	aRet=mWifi_SendCmd("at+rsi_ipconf=0,192.168.1.176,255.255.255.0,192.168.1.1\r\n");
	// Open a server TCP socket in the module sur le port 5001
	aRet=mWifi_SendCmd("at+rsi_ltcp=5001\r\n");
	// On vide le buffer
	while(mWifi_SciReadDataFromBuffer(&aChar)==false);
	
	// Pour les tests
	sDly=mDelay_GetDelay(kPit1,500/kPit1Period);
	
	// Pour le test Wifi JAVA
	sDlyJava=mDelay_GetDelay(kPit1,100/kPit1Period);
	
	//--------------------------------------------------------------------
	// Boucle infinie --> round robin
	//--------------------------------------------------------------------
	for(;;)
		{	   	
			// � impl�menter ....
			gInput_Execute();
			gCompute_Execute();
			gOutput_Execute();
			
			//--------------------------------------------------------------------
			// Selon la position de l'interrupteur 1 on passe de l'�tat test (si =1, voir ci-dessous) � l'�tat automatique
			//--------------------------------------------------------------------
			if(mSwitch_ReadSwitch(kSw1)==true)
				{
					//--------------------------------------------------------------------
					// Start exposition � la lumi�re et lecture de l'image
					//--------------------------------------------------------------------
					mSpi_MLX75306_StartIntegration(kCamera2,1);
					mSpi_MLX75306_ReadPicture(kCamera2,sImageTab);

#if(kWithAccel)
					//--------------------------------------------------------------------
					// Lecture de l'acc�l�rom�tre et du magn�tom�tre
					// Angle en degr�s et acc�l�ration en g
					//--------------------------------------------------------------------
					aRet=mAccelMagneto_ReadData(&sAccel,&sMagneto,&sYaw,&sRoll,&sPitch);
#endif
					//-----------------------------------------------------------------------------
					// Lecture de la vitesse de rotation des moteurs
					// Moteur A = moteur gauche --> valeur n�gative = en arri�re, valeur pos=en avant
					// Moteur B = moteur droite
					//-----------------------------------------------------------------------------
					mTimer_GetSpeed(&sSpeedMotLeft,&sSpeedMotRight);
					
					// Set DAC 0 buffer output value, entre 0 et 4095 --> driver de LEDS
					// Entre 0 et 100% --> 0 et 1.0
					mDac_SetDac0Output(1.0);
					
					aVal=mSwitch_ReadPushBut(kPushButSW1);
					if((aVal==true)&&(OldSw1==false))
						{
							// Reset du module wifi
							aRet=mWifi_SendCmd("at+rsi_reset\r\n");
							sSocketOpen=false;
						}
					OldSw1=aVal;
					
					aVal=mSwitch_ReadPushBut(kPushButSW2);
					if((aVal==true)&&(OldSw2==false))
						{
							// S�lection de la bande:
							aRet=mWifi_SendCmd("at+rsi_band=0\r\n");
							// Init:
							aRet=mWifi_SendCmd("at+rsi_init\r\n");
							// Network Type: AdHoc, canal 6
							// !! Chaque �quipe prend un canal diff�rent, ici 6
							aRet=mWifi_SendCmd("at+rsi_network=IBSS_SEC,1,6\r\n");
							// Set PSK: 
							aRet=mWifi_SendCmd("at+rsi_psk=12345ABCDE\r\n");
							// Create IBSS network: 
							// Chaque �quipe avec un non diff�rent
							aRet=mWifi_SendCmd("at+rsi_join=FREESCALE_CUP_C6,0,2\r\n");
							// IP Address Configuration (DHCP Manual): 
							aRet=mWifi_SendCmd("at+rsi_ipconf=0,192.168.1.176,255.255.255.0,192.168.1.1\r\n");
							// Open a server TCP socket in the module sur le port 5001
							aRet=mWifi_SendCmd("at+rsi_ltcp=5001\r\n");
							sSocketOpen=true;
						}
					OldSw2=aVal;
					
					
					if(sSocketOpen==true)
						{
							// ---------------------------------------------
							// Test envoi de donn�es � l'app JAVA
							// ---------------------------------------------
							SendDataJava();
							
							// ---------------------------------------------
							// Test r�ception de donn�es de l'app JAVA
							// ---------------------------------------------
							ReadDataJava();
						}
				}
			
			//--------------------------------------------------------------------
			// Mode test
			//--------------------------------------------------------------------
			else
				{
					// Lecture de l'acc�l�rom�tre et du magn�tom�tre
					// Angle en degr�s et acc�l�ration en g
#if(kWithAccel)
					aRet=mAccelMagneto_ReadData(&sAccel,&sMagneto,&sYaw,&sRoll,&sPitch);
#endif
					
					//-----------------------------------------------------------------------------
					// Lecture de la vitesse de rotation des moteurs
					// Moteur A = moteur gauche (tr/mn)--> valeur n�gative = en arri�re, valeur pos=en avant
					// Moteur B = moteur droite (tr/mn)
					//-----------------------------------------------------------------------------
					mTimer_GetSpeed(&sSpeedMotLeft,&sSpeedMotRight);
					
					// Selon la position des interrupteurs (interrupteur 2 et 3) on teste les poussoirs, le servo, les moteurs DC et la camera
					if(mDelay_IsDelayDone(kPit1,sDly)==true)
						{
							mDelay_ReStart(kPit1,sDly,300/kPit1Period);
							
							// Test des LEDS
							mLeds_Toggle(kMaskLed1+kMaskLed2+kMaskLed3+kMaskLed4);
							
							// Tests des servo
							// Les 2 boutons poussoirs permettent de bouger dans un sens et dans l'autre
							if(mSwitch_ReadPushBut(kPushButSW1)==true)
								{
									aDuty+=0.05;
									if(aDuty>1)
										{
											aDuty=1;
										}
									mTimer_SetServoDuty(0,aDuty);
								}
							else if(mSwitch_ReadPushBut(kPushButSW2)==true)
								{
									aDuty-=0.05;
									if(aDuty<-1)
										{
											aDuty=-1;
										}
									mTimer_SetServoDuty(0,aDuty);
								}
							else
								{
									aDuty=0;
									mTimer_SetServoDuty(0,0);
								}
						
						// Si le switch 2 est ON les potentiom�tres pilotes les moteurs
						// sinon le pot1 pilote le temps d'exposition de la cam�ra
						if(mSwitch_ReadSwitch(kSw2)==true)
							{
								// Test des moteurs
								// Pot1 moteur gauche
								// Pot1 moteur droit
								mTimer_SetMotorDuty(mAd_Read(kPot1) ,mAd_Read(kPot2));
							}
						else
							{
								sIntTime=mAd_ReadCamera(kPot1);
							}
														
						
						// Start exposition � la lumi�re
						mSpi_MLX75306_StartIntegration_old(kCamera2,sIntTime);
														
						// Test de la cam�ra
						mSpi_MLX75306_ReadPictureTest(kCamera2,sImageTabTest);
												 
						mRs232_Uart4WriteString("\r\n");
						mRs232_Uart4WriteString("L:");
						
						for(i=0;i<143;i++)
							{
								sprintf(aCharTab,"%X,",sImageTabTest[13+i]);
								mRs232_Uart4WriteString(aCharTab);
							}
									
						 for(i=0;i<143;i++)
							 {
								 sprintf(aCharTab,"%X",sImageTabTest[13+i]);
								 mRs232_Uart4WriteString(aCharTab);
								 if(i==143)
									 mRs232_Uart4WriteString("\r\n");
								 else
									 mRs232_Uart4WriteString(",");
							 }													
						}
					}
			}
	}



// -----------------------------------------------------------------------
// Structure de test pour monitoring JAVA
// -----------------------------------------------------------------------
typedef struct
{
	float SpeedLeft;
	float SpeedRight;
	Int16 ConsSpeedLeft;
	Int16 ConsSpeedRight;
	Int16 ConsServo;
	Int16 ConsLed;
	float sYaw;
	float sRoll;
	float sPitch;
	float AccelX;
	float AccelY;
	float AccelZ;
	float ResFloat1;
	float ResFloat2;
	float ResFloat3;
	float ResFloat4;
	Int16 ResInt161;
	Int16 ResInt162;
	Int16 ResInt163;
	Int16 ResInt164;
}SendFrame1Struct;

static SendFrame1Struct sFrameTxJava1;
static SendFrame1Struct sFrameRxJava1;
static UInt8 						*sFrameRxPtr=(UInt8*)&sFrameRxJava1;

typedef struct
{
	float SpeedLeft;
	float SpeedRight;
	Int16 ConsSpeedLeft;
	Int16 ConsSpeedRight;
	Int16 ConsServo;
	Int16 ConsLed;
	float sYaw;
	float sRoll;
	float sPitch;
	float AccelX;
	float AccelY;
	float AccelZ;
	float ResFloat1;
	float ResFloat2;
	float ResFloat3;
	float ResFloat4;
	Int16 ResInt161;
	Int16 ResInt162;
	Int16 ResInt163;
	Int16 ResInt164;
	UInt8 ImageTab[143];
}SendFrame2Struct;

static SendFrame2Struct sFrameTxJava2;

static float sSinusTab[25]=
{
	1,
	1.248689887,
	1.481753674,
	1.684547106,
	1.844327926,
	1.951056516,
	1.998026728,
	1.982287251,
	1.904827052,
	1.770513243,
	1.587785252,
	1.368124553,
	1.125333234,
	0.874666766,
	0.631875447,
	0.412214748,
	0.229486757,
	0.095172948,
	0.017712749,
	0.001973272,
	0.048943484,
	0.155672074,
	0.315452894,
	0.518246326,
	0.751310113
};

//-----------------------------------------------------------------------
// Codage et envoi par WIFI � l'app JAVA
//-----------------------------------------------------------------------
void stbpSendFrameJava1(SendFrame1Struct *aFrameJava1)
{
	UInt8 msgId = Frame1_MSGID;
	UInt16 i=0;
	bool aRet=false;
	// Create a Message
	Stbp_NewMsg(sMyCommPtr, ESTBP_CONF_NOSUBHEADER,ESTBP_APPID_FreescaleCup,msgId); 
	Stbp_PutString(sMyCommPtr, (CHAR*) aFrameJava1, sizeof(SendFrame1Struct));
	
	// Encode the Whole Message 
	sNumberOfTransferredBytes += Stbp_EncodeMessage(sMyCommPtr, (UINT8*)(sTxMsgBufferPtr + sNumberOfTransferredBytes));
	
	// Envoi d'une donn�e par le WIFI: d�but de la commande AT
	aRet=mWifi_SendCmd("at+rsi_snd=1,0,0,0,");
	
	i=0;
	while(sNumberOfTransferredBytes>0)
		{
			if((sTxMsgBufferPtr[i]==0xd)&&(sTxMsgBufferPtr[i+1]==0xa))
				{
					sNumberOfTransferredBytes--;
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(0xDB);
					mWifi_WriteChar(0xDC);
					i++;
					i++;
				}
			else if(sTxMsgBufferPtr[i]==0xDB)
				{
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(0xDB);
					mWifi_WriteChar(0xDD);
					i++;
				}
			else if((sTxMsgBufferPtr[i]==0xDB)&&(sTxMsgBufferPtr[i+1]==0xDC))
				{
					
					sNumberOfTransferredBytes--;
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(0xDB);
					mWifi_WriteChar(0xDD);
					mWifi_WriteChar(0xDC);
					i++;
					i++;
				}
			else
				{
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(sTxMsgBufferPtr[i]);
					i++;
				}
		}
	
	// N�cessaire pour terminer la commande AT
	mWifi_WriteChar(0xd);
	mWifi_WriteChar(0xa);
}

//-----------------------------------------------------------------------
// Codage et envoi par WIFI � l'app JAVA
//-----------------------------------------------------------------------
void stbpSendFrameJava2(SendFrame2Struct *aFrameJava2)
{
	UInt8 msgId = Frame2_MSGID;
	UInt16 i=0;
	bool aRet=false;
		
	// Create a Message
	Stbp_NewMsg(sMyCommPtr, ESTBP_CONF_NOSUBHEADER,ESTBP_APPID_FreescaleCup,msgId); 
//	Stbp_PutUint8(sMyCommPtr, gainMode);
//	Stbp_PutUint16(sMyCommPtr, rxGain);
//	Stbp_PutUint8(sMyCommPtr, ledsStatus);
	Stbp_PutString(sMyCommPtr, (CHAR*) aFrameJava2, sizeof(SendFrame2Struct));
	
	
	// Encode the Whole Message 
	sNumberOfTransferredBytes += Stbp_EncodeMessage(sMyCommPtr, (UINT8*)(sTxMsgBufferPtr + sNumberOfTransferredBytes));
	
	// Envoi d'une donn�e par le WIFI: d�but de la commande AT
	aRet=mWifi_SendCmd("at+rsi_snd=1,0,0,0,");
	
	i=0;
	while(sNumberOfTransferredBytes>0)
		{
			if((sTxMsgBufferPtr[i]==0xd)&&(sTxMsgBufferPtr[i+1]==0xa))
				{
					sNumberOfTransferredBytes--;
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(0xDB);
					mWifi_WriteChar(0xDC);
					i++;
					i++;
				}
			else if(sTxMsgBufferPtr[i]==0xDB)
				{
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(0xDB);
					mWifi_WriteChar(0xDD);
					i++;
				}
			else if((sTxMsgBufferPtr[i]==0xDB)&&(sTxMsgBufferPtr[i+1]==0xDC))
				{
					
					sNumberOfTransferredBytes--;
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(0xDB);
					mWifi_WriteChar(0xDD);
					mWifi_WriteChar(0xDC);
					i++;
					i++;
				}
			else
				{
					sNumberOfTransferredBytes--;
					mWifi_WriteChar(sTxMsgBufferPtr[i]);
					i++;
				}
		}
	
	// N�cessaire pour terminer la commande AT
	mWifi_WriteChar(0xd);
	mWifi_WriteChar(0xa);
}

//------------------------------------------------------------
// D�codage des trames RS232 de commande du PC Host
//------------------------------------------------------------
static UInt8 DecodeFrame(UInt8 *aBuffPtr,UInt8 aSize,UInt8 *aNewBuffPtr)
{
  bool aNext = false;
  UInt8 aNewSize=0;
  
  while(aSize>0)
    {
      if ((*aBuffPtr != 0x00) && (*aBuffPtr != 0x01))
        {
          if (aNext == false)
            {
              if (*aBuffPtr ==0x02)
                {
                  aNext = true;
                }
              else
                {
                  *aNewBuffPtr=*aBuffPtr;
                  *aNewBuffPtr-=3;
                  aNewBuffPtr++;
                  aNewSize++;
                }
            }
          else
            {
              *aNewBuffPtr=*aBuffPtr;
              aNewBuffPtr++;
              aNewSize++;
              aNext = false;
            }
        }
      
      aBuffPtr++;
      aSize--; 
    }
  
  return aNewSize; 
}

//-------------------------------------------------------------------------
// Test envoi de donn�es � l'app JAVA
//-------------------------------------------------------------------------
void SendDataJava(void)
{
	static bool sLedOn1=false;
	static UInt8 sSinIndex=0;
	UInt16 i;
		
	// ---------------------------------------------
	// Test envoi de donn�es � l'app JAVA
	// ---------------------------------------------
	if(mDelay_IsDelayDone(kPit1,sDlyJava))
		{
			if(sLedOn1==true)
				{
					sLedOn1=false;
				}
			else
				{
					sLedOn1=true;
				}
			
			// On envoi tous les 100ms
			mDelay_ReStart(kPit1,sDlyJava,100/kPit1Period);
			
			// ------------------------------------------------------------
			// Test d'envoi d'une trame WIFI avec le protocole ST
			// ------------------------------------------------------------
			// On simule des signaux � l'aide d'une sinus par-exemple
			sFrameTxJava1.SpeedLeft=sSinusTab[sSinIndex];
			sFrameTxJava1.SpeedRight=sSinusTab[sSinIndex]*1.3;
			sFrameTxJava1.ConsSpeedLeft+=50;
			sFrameTxJava1.ConsSpeedRight+=60;
			sFrameTxJava1.ConsServo+=1;
			sFrameTxJava1.ConsLed+=2000;
			sFrameTxJava1.sYaw=sSinusTab[sSinIndex]*1.5;
			sFrameTxJava1.sRoll=sSinusTab[sSinIndex]*1.7;
			sFrameTxJava1.sPitch=sSinusTab[sSinIndex]*2;
			sFrameTxJava1.AccelX=sSinusTab[sSinIndex]*2.2;
			sFrameTxJava1.AccelY=sSinusTab[sSinIndex]*2.4;
			sFrameTxJava1.AccelZ=sSinusTab[sSinIndex]*2.6;
			sFrameTxJava1.ResFloat1=sSinusTab[sSinIndex]*2.8;
			sFrameTxJava1.ResFloat2=sSinusTab[sSinIndex]*3;
			sFrameTxJava1.ResFloat3=sSinusTab[sSinIndex]*3.2;
			sFrameTxJava1.ResFloat4=sSinusTab[sSinIndex]*3.4;
			sFrameTxJava1.ResInt161+=12;
			sFrameTxJava1.ResInt162+=22;
			sFrameTxJava1.ResInt163=0;
			sFrameTxJava1.ResInt164=0xFFFF;
			
			sSinIndex++;
			if(sSinIndex>=25)
				{
					sSinIndex=0;
				}
			
			// Codage et transmission de la trame
			stbpSendFrameJava1(&sFrameTxJava1);
			
			// 2e frame avec l'image
			sFrameTxJava2.SpeedLeft=101.1;
			sFrameTxJava2.SpeedRight=102.2;
			sFrameTxJava2.ConsSpeedLeft=1050;
			sFrameTxJava2.ConsSpeedRight=1060;
			sFrameTxJava2.ConsServo=11000;
			sFrameTxJava2.ConsLed=12000;
			sFrameTxJava2.sYaw=103.3;
			sFrameTxJava2.sRoll=104.4;
			sFrameTxJava2.sPitch=105.5;
			sFrameTxJava2.AccelX=106.6;
			sFrameTxJava2.AccelY=107.7;
			sFrameTxJava2.AccelZ=108.8;
			sFrameTxJava2.ResFloat1=109.9;
			sFrameTxJava2.ResFloat2=111.1;
			sFrameTxJava2.ResFloat3=122.2;
			sFrameTxJava2.ResFloat4=133.3;
			sFrameTxJava2.ResInt161=10111;
			sFrameTxJava2.ResInt162=10222;
			sFrameTxJava2.ResInt163=10333;
			sFrameTxJava2.ResInt164=10444;
			for(i=0;i<143;i++)
				{
					sFrameTxJava2.ImageTab[i]=i;
				}
			
			// Codage et transmission de la trame
			stbpSendFrameJava2(&sFrameTxJava2);
		}
}

//-------------------------------------------------------------------------
// Test r�ception de donn�es de l'app JAVA
//-------------------------------------------------------------------------
UInt32 sCounterRxFrame=0;
void ReadDataJava(void)
{
	static ReadFramestruct *aReadFrame;		
	UInt16 i=0;
	
	// Check si des donn�es ont �t� re�ues et lecture d'une trame
	aReadFrame=mRS232_GetReadWifiFrame();
	if(aReadFrame!=0)
		{
			sCounterRxFrame++;
			// D�codage de la trame
			Stbp_DecodeMessage(sMyCommPtr, aReadFrame->Size, aReadFrame->Payload);
			sFrameRxWifiPtr=(UInt8*)&sFrameRxWifi;
			// Copie des donn�es re�ues et d�cod�es
			for(i=6;i<(sMyComm.uRxBufferHead-1);i++)
				{
					*sFrameRxWifiPtr++=sMyCommRxBuffer[i];
				}
		}
}

//-------------------------------------------------------------------------
// Init pour la comm de l'app JAVA
//-------------------------------------------------------------------------
void InitDataJava(void)
{
		Stbp_InitSw(sMyCommPtr, sMyCommRxBuffer,kBUFFERSIZE,sMyCommTxBuffer,kBUFFERSIZE);
}
