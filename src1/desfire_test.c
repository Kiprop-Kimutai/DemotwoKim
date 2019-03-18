/*
 * desfire_test.c

 *
 *  Created on: Oct 16, 2018
 *      Author: pos
 */

#include "posapi.h"
#include "seos.h"
#include "desfire.h"
#include "iso14443.h"
#include "miful.h"
#include "mifone.h"
#include "main.h"
#include "desfire_test.h"
#include "cJSON.h"
#include "jsonread.h"

int openCardReader(void);
void initializeCardSectors(void);

char *readDataFromMifareCard(char *applicationName,char *filename);

int testnfc(){
	int fd=-1,pollresult = -1;
	char uidbuff[2],uidd[14];
	char uid[7];
	int k,ret;
	uint8_t x = 40;
	uint8_t *atslen = &x;
	char ats[40];
	int authstatus =-1;
	char app0[3] = {0x00,0x00,0x00};
    char authkey[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t keyno = 0;
	int createappstatus;

		uint8_t fileno = 1;

		desfire_appinfo info;
		(info).AID[0]=0x10;
		(info).AID[1]=0x00;
		(info).AID[2]=0x00;
		info.MasterKeySetting = 0;
		info.NumberOfKey = 10;
		info.CryptoMode =0;
		info.IsSupFID = 0;
		info.IsSupISOFID = 0;
		info.LenOfDFName = 0;

		desfire_std_backup_file_info fileinfo;
		fileinfo.file_size = 100;
		fileinfo.com_sett = 0x00;
		//fileinfo.FlgISOFileID = 0x00;
		fileinfo.change_access_right_keyno = 0;
		fileinfo.read_and_write_access_right_keyno = 0;
		fileinfo.write_access_right_keyno = 0;
		fileinfo.read_access_right_keyno = 0;

		char *datain;
		char dataout[100];
		uint32_t outlen;

	uint8_t kk = 2;
	uint8_t *kkk = &kk;
	char aids[84];

	fd = mif_open("/dev/nfc");
	printf("fd status %d\n",fd);
	if(fd<0){
		printf("Failed to open nfc reader module error %d\n",errno);
	}
	else{
		pollresult =  desfire_poll(fd,0,uid,atslen,ats);
		while(1){
			 //mif_set_timeout(const struct mif_timeout *ptime)
			printf("Initialization done...\n");
			/*************************************************************************/
			/***poll card here ****/
			//pollresult =  desfire_poll(fd,0,uid,atslen,ats);
			printf("poll result %d\n",pollresult);
			if(pollresult == 0){
				printf("card atslen %d\n",*atslen);
				for(k=0;k<7;k++){
					printf("%02X",ats[k]);
					memset(uidbuff,0,sizeof(uidbuff));
					sprintf(uidbuff,"%02x",ats[k]);
					strcat(uidd,uidbuff);
					strcpy(uidbuff,"");
				}
				printf("\n\n");
				printf("uid %s\n",uidd);
				//do something here
			}
			else{
				printf("poll result failed...\n");
			}
			/*******************************************************************/
			//select MF
			ret = desfire_select_application(fd,app0);
			printf("select MF result %d\n",ret);
			/**authenticate card ********/
			authstatus = desfire_authenticate(fd,keyno,authkey);
			printf("auth status %d\n",authstatus);
			if(authstatus == 0){
				//authentication successful. create application if it does not exist
				createappstatus = desfire_create_application(fd,&info);
				if(createappstatus == 0){
					printf("App created successfully\n\n");
					//select application
					ret = desfire_select_application(fd,info.AID);
					if(ret==0){
						printf("personal details app selection passed\n\n");
						ret = desfire_authenticate(fd,keyno,authkey);
						if(ret !=0){
							printf("authentication failed..\n");
						}
						else{
						//create kyc standard data file, if it does not exist
							printf("Auth status %d with probable error %d\n",ret,errno);
						ret =  desfire_create_std_datafile(fd,fileno,&fileinfo);
						if(ret == 0){
							printf("kyc data file created successfully\n\n");

						}
						else{
							printf("kyc file creation failed with status %d corresponding to error %d\n",ret,errno);
							// go ahead and write records
						}
					}
					}
					else{
						printf("personal details file selection failed with result %d corresponding to errno %d\n",ret,errno);
					}
				}
				else{
					printf("App creation failed with error %d corresponding to errno %d\n",createappstatus,errno);
					//get all application ids and select the application you want//optional
					ret =  desfire_get_application_ids(fd,&kkk,&aids);
					if(ret==0){
						printf("we will print out app ids \n");
						for(k=0;k<sizeof(aids);k++){
							printf("%02X",aids[k]);
							if(k%3==0){
								printf("\n");
							}
						}
						printf("\n");
					}
					else{
						printf("fix card ids\n\n");
					}
					//now select application
					ret = desfire_select_application(fd,info.AID);
					if(ret == 0){
						ret = desfire_authenticate(fd,keyno,authkey);
						if(ret ==-1){
							printf("authentication failed\n");
						}
						else{
							printf("authentication passed\n\n");
							printf("-----\n");
						//create file and select or select file
						ret =  desfire_create_std_datafile(fd,fileno,&fileinfo);
						//ret =  desfire_create_linear_recordfile(fd,1,&recordfile);
						if(ret == 0){
							printf("kyc record file created successfully\n");
							//write some data to file
							datain = "JonahHexx";
							ret =  desfire_write_data(fd,fileno,0x00,0,strlen(datain),datain);
							if(ret == 0){
								printf("Data written successfuly\n");
								//now read back data
								  ret =  desfire_read_data(fd,fileno,0x00,0,100,&outlen,dataout);
												  if(ret==0){
													  //print out read data
													  printf("Data in file %s\n",dataout);
												  }
												  else{
													  printf("Read data failed with error %d corresponding to status %d\n",ret,errno);
												  }
							}
							else{
								//go ahead and read available data
							  ret =  desfire_read_data(fd,fileno,0x00,0,100,&outlen,dataout);
							  if(ret==0){
								  //print out read data
								  printf("Data in file %s\n",dataout);
							  }
							  else{
								  printf("Read data failed with error %d corresponding to status %d\n",ret,errno);
							  }
							}
						}
						else{
							printf("kyc record file creation failed with status %d corresponding to error %d\n",ret,errno);
							//go ahead and write card
							datain = "JonahHexx";
							ret =  desfire_write_data(fd,fileno,0x00,0,strlen(datain),datain);
							if(ret == 0){
								printf("Data written successfuly\n");
								//now read back data
								  ret =  desfire_read_data(fd,fileno,0x00,0,100,&outlen,dataout);
												  if(ret==0){
													  //print out read data
													  printf("Data in file %s\n",dataout);
												  }
												  else{
													  printf("Read data failed with error %d corresponding to status %d\n",ret,errno);
												  }
							}
							else{
								//go ahead and read available data
								  ret =  desfire_read_data(fd,fileno,0x00,0,100,&outlen,dataout);
												  if(ret==0){
													  //print out read data
													  printf("Data in file %s\n",dataout);
												  }
												  else{
													  printf("Read data failed with error %d corresponding to status %d\n",ret,errno);
												  }
							}
						}
					}
				}

				}

			}
			break;
		}
	}
	printf("closing reader module  with result %d\n",mif_close(fd));
	//printf("closing reader module  with result \n");


	return 0;
}
int peformCardOperations(){

	int fd = -1;
	int ret;
	int recv_len;
	int i;
	uint8_t mode;
	//uint8_t uid[20];
	char uid[50];
	char ats[50];
	uint8_t atslen[50];
	char app0[3] = {0x00,0x00,0x00};
	char authkey[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t keyno = 0;
	desfire_appinfo info;
	//uint8_t pointer[3]={0x00,0x00,0x01};
	(info).AID[0]=0x10;
	(info).AID[1]=0x00;
	(info).AID[2]=0x00;
	info.MasterKeySetting = 0;
	info.NumberOfKey = 1;
	info.CryptoMode =0;
	info.IsSupFID = 1;
	info.IsSupISOFID = 0;
	info.ISOFID[0] = 0x12;
	info.ISOFID[1] = 0x00;
	info.LenOfDFName = 0;

	desfire_std_backup_file_info fileinfo;
	fileinfo.file_size =500;
	fileinfo.com_sett = 0x00;
	fileinfo.FlgISOFileID = 0x01;
	fileinfo.ISOFileID[0] = 0x00;
	fileinfo.ISOFileID[1] = 0x01;
	fileinfo.change_access_right_keyno = 0x00;
	fileinfo.read_and_write_access_right_keyno = 0x00;
	fileinfo.write_access_right_keyno = 0x00;
	uint8_t fileno = 1;
	//info.DFName 0;
	//open card reader
	/* Open device */
	printf("Mifare One Card Test\r\n");
	fd = mif_open("/dev/nfc");
	if (fd < 0) {
		printf("Open nfc failed! errno:%d\r\n", errno);
		//goto exit_entry;
		return 0;

	}

	printf("Open desfire success.Please approach card ....\n");
	while(1){
/*		lcdCls();
		lcdDisplay(0,0,DISP_CFONT,"open device success\n");
		lcdDisplay(0,2,DISP_CFONT,"please show the card\n");
		lcdFlip();*/
		message_display_function(1,"","Message","Device open successful.Please tap your card",(char *)NULL);
		/**poll card and get card uuid**/
		printf(".....\n");
		ret = desfire_poll(fd,0,uid,atslen, ats);
		printf("Returned value::%d\n",ret);
		printf("Error number value  on polling %d\n",errno);
		//printf("Received data::%s\n",ats);
		printf("Received data length::%d\n",sizeof(ats));
		printf("Returned content::%s\n",ats);
		 // char  uid[16];
		  ret =  desfire_get_card_uid(fd,uid);
		  printf("card iccid:%s\n",uid);
		/**select master file******/
		ret = desfire_select_application(fd,app0);
		printf("Returned value on master file select::%d\n",ret);
		printf("Error number value on selecting app 0 %d\n",errno);
		  ret =  desfire_get_card_uid(fd,uid);
		  printf("card iccid:%s\n",uid);
		/*now, authenticate card */
		printf("About to authenticate\n");
		 ret = desfire_authenticate(fd,keyno,authkey);
		 printf("Returned value on authentication::%d\n",ret);
		 printf("Error number value on authenticating %d\n",errno);
		 printf("Init...\n");
		 /**create application ******/
		 printf("create application....\n");
		 ret = desfire_create_application(fd, &info);
		 printf("App creation returned value  %d\n", ret);
		 printf("Error number value on creating app %d\n",errno);
		 /**select application then create file*****/
		 ret =  desfire_select_application(fd,info.AID);
		 ret = desfire_authenticate(fd,keyno,authkey);
		 printf("Error number value on selecting app  %d\n",errno);
		 printf("App selection result:%d\n",ret);
		 ret =  desfire_create_std_datafile(fd,fileno,&fileinfo);
		  printf("File creation result:::%d\n",ret);
		  printf("Error number value on creating file 1 %d\n",errno);
		  char * martin="Martin chirchir";
		  //uint8_t fileno;
		  ret=desfire_write_data(fd,fileno,0x00, 0, strlen(martin), martin);
		  printf("Write result::%d\n",ret);
		  printf("Error number value on writing into file1  %d\n",errno);
		  uint32_t outlen;
		  char dataout[1000];
		  ret =  desfire_read_data(fd,fileno,0x00,0,strlen(martin),&outlen,dataout);
		  printf("Result from reading data out from card file 1  ::%d\n  ",ret);
		  printf("Error number value on reading data fromm file1  %d\n",errno);
		  printf("Data read from the card  %s\n",dataout);
		  fileno=2;
		  fileinfo.FlgISOFileID = 0x02;
		  fileinfo.ISOFileID[0] = 0x01;
		  fileinfo.ISOFileID[1] = 0x02;
		  fileinfo.file_size=1000;
		  ret =  desfire_create_std_datafile(fd,fileno,&fileinfo);
		  printf("File 2 creation result:::%d\n",ret);
		  printf("Error number value on creating file2 %d\n",errno);
		  martin="Jonah kimutai";

		  ret=desfire_write_data(fd,fileno,0x00, 0, strlen(martin), martin);
		  printf("Result in writing data into file 2::%d\n",ret);
		  printf("Error number value on writing data into file2  %d\n",errno);
		  ret =  desfire_read_data(fd,fileno,0x00,0,strlen(martin),&outlen,dataout);
		  printf("Result from reading data out from card file 2  ::%d\n  ",ret);
		  printf("Error number value on reading data from file2  %d\n",errno);
		  printf("Data read from the card  %s\n",dataout);
		   /* fileinfo.FlgISOFileID = 0x02;
		  	fileinfo.ISOFileID[0] = 0x03;
		  	fileinfo.ISOFileID[1] = 0x04;
		  	fileno=2;*/
		  /*ret =  desfire_create_std_datafile(fd,fileno,&fileinfo);
		  		  printf("Second file creation result:::%d\n",ret);
		  		  char * martin1="Jonah kiprop was here";
		  		  //uint8_t fileno;
		  		  ret=desfire_write_data(fd,fileno,0x00, 0, strlen(martin), martin);
		  		  printf("Write result2::%d\n",ret);
		  		 // uint32_t outlen;
		  		 // char dataout[50];
		  		  ret =  desfire_read_data(fd,fileno,0x00,0,strlen(martin),&outlen,dataout);
		  		  printf("Read value1::%d\n",ret);
		  		  printf("Read data1::%s\n",dataout);
*/
		  /**read card iccid***/

		//goto close_exit;
		//kbGetKeyMs(1000);
		//lcdFlip();
		mif_close(fd);
		return 0;

	}

}

int openCardReader(void){
	int fd = -1;
	/** open device card reader**/
	fd = mif_open("/dev/nfc");
	if(fd<0){
		printf("Open nfc failed! errno:%d\r\n", errno);
		return 0;
	}
	return 0;
}

void initializeCardSectors(void){
	//peformCardOperations();
}
//int createApplicationAndFileAndWriteData(char *data1, char *data2){
int createApplicationAndFileAndWriteData(cJSON * data1, char *data2){
	/****personal details variables*******/
	cJSON *firstname,*lastname,*dateofbirth,*Gender;
	char *fname,*lname,*yob,*gender;
	//char *personaldetails;
	char *personaldetails = malloc(20*sizeof(char));
	//char personaldetails[200];
	char *developerstring;
	char *sql;
	sql = malloc(2000);
	/******************************************/
	int fd = -1;
	int ret;
	char uid[50];
	char ats[50];
	char buff1[10];
	char buff2[50];
	uint8_t atslen[50];
	char MF[3] = {0x00,0x00,0x00};
	char mfauthkey[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	uint8_t keyno = 0;
	//uint8_t fileno=-1;
	char dataout[1000];
	char dataout1[50];
	uint32_t outlen;
	desfire_appinfo info;
	//uint8_t pointer[3]={0x00,0x00,0x01};
	(info).AID[0]=0x10;
	(info).AID[1]=0x00;
	(info).AID[2]=0x00;

	info.MasterKeySetting = 0;
	info.NumberOfKey = 10;
	info.CryptoMode =0;
	info.IsSupFID = 1;
	info.IsSupISOFID = 0;
	//info.ISOFID[0] = 0x13;
	//info.ISOFID[1] = 0x00;
	info.LenOfDFName = 0;

	desfire_std_backup_file_info fileinfo;
/*	fileinfo.file_size = 0x10;
	fileinfo.com_sett = 0x00;
	fileinfo.FlgISOFileID = 0x01;
	//fileinfo.ISOFileID[0] = 0x00;
	//fileinfo.ISOFileID[1] = 0x01;
	fileinfo.change_access_right_keyno = 0x00;
	fileinfo.read_and_write_access_right_keyno = 0x00;
	fileinfo.write_access_right_keyno = 0x00;*/

	fileinfo.file_size = 100;
	fileinfo.com_sett = 0x00;
	//fileinfo.FlgISOFileID = 0x00;
	//fileinfo.ISOFileID[0] = 0x00;
	//fileinfo.ISOFileID[1] = 0x01;
	fileinfo.change_access_right_keyno = 0;
	fileinfo.read_and_write_access_right_keyno = 0;
	fileinfo.write_access_right_keyno = 0;
	fileinfo.read_access_right_keyno = 0;
	uint8_t fileno = 1;


	/**************print values to be written to card here *******************/
	printf("card personalization init....\n");
	developerstring = cJSON_Print(data1);
	printf("Personal info::%s\n",developerstring);
	//printf("Biodata:::%s\n",data2);
	firstname = cJSON_GetObjectItem(data1,"firstname");
	lastname = cJSON_GetObjectItem(data1,"lastname");
	dateofbirth = cJSON_GetObjectItem(data1,"dateofbirth");
	Gender = cJSON_GetObjectItem(data1,"Gender");

	fname = cJSON_Print(firstname);
	lname = cJSON_Print(lastname);
	yob = cJSON_Print(dateofbirth);
	gender = cJSON_Print(Gender);

	printf("developer pc::%s\n",fname);
	printf("developer pc::%s\n",lname);
	printf("developer pc::%s\n",yob);
	printf("developer pc::%s\n",gender);
	sprintf(personaldetails,"%s#%s#%s#%s",fname,lname,gender,yob);
	printf("*************\n\n");
	printf("personal details=========|%s\n",personaldetails);

	printf("card personalization finished.....\n");
	/*************************************************************************/
	//fd = mif_open("/dev/nfc");
	printf("Mifare One Card Test\r\n");
	fd = mif_open("/dev/nfc");
	if(fd<0){
		printf("open nfc failed! errno:%d\r\n",errno);
		return 0;
	}
	printf("fd value:%d\n",fd);
	printf("Open desfire success.Please approach card ....\n");



		/*		lcdCls();
				lcdDisplay(0,0,DISP_CFONT,"open device success\n");
				lcdDisplay(0,2,DISP_CFONT,"please show the card\n");
				lcdFlip();*/
				/**poll card and get card uuid**/
				printf(".....\n");
				while(1){
				ret = desfire_poll(fd,0,uid,atslen, ats);
				if (ret == 0){
					break;
				}
				}
				printf("Returned value::%d\n",ret);
				//printf("Received data::%s\n",ats);
				printf("Received data length::%d\n",sizeof(ats));
				printf("Returned content::%s\n",ats);
				 // char  uid[16];
				  ret =  desfire_get_card_uid(fd,uid);
				  int w = 0;
				  while(w<7){
						printf( "%02X",uid[w]);
						sprintf(buff1,"%02X",uid[w]);
						printf("buff1::%s\n",buff1);
						strcat(buff2,buff1);
						strcpy(buff1,"");
						w++;
				 }
				  printf("Buff2 content:::%s\n",buff2);
				sprintf(sql,"insert into cardHolderTable values '%s','%s';",buff1,"jonahkimtaimartinchirchir");
				 read_database(sql,"transaction");
				free(sql);

				  //printf("card iccid:%s\n",uid);
				/**select master file******/
				ret = desfire_select_application(fd,MF);
				printf("Returned value on master file select::%d\n",ret);
				  ret =  desfire_get_card_uid(fd,uid);
				  printf("card iccid:%s\n",uid);
				/*now, authenticate card */
				printf("About to authenticate\n");
				 ret = desfire_authenticate(fd,keyno,mfauthkey);
				 printf("Returned value on authentication::%d\n",ret);
				 printf("Init...\n");
				 /**create application ******/
				 printf("create application....\n");
				 ret = desfire_create_application(fd, &info);
				 printf("App creation returned value  %d\n", ret);
				 /**select application then create file*****/
				 ret =  desfire_select_application(fd,info.AID);
				 printf("App selection result:%d\n",ret);
				 ret = desfire_authenticate(fd,keyno,mfauthkey);
				 printf("App authentication result:%d\n",ret);
				 ret =  desfire_create_std_datafile(fd,fileno,&fileinfo);
				 if(ret == 0){
					 printf("File creation successful %d\n\n",ret);
					  char * martin="Martin chirchir";
					  //uint8_t fileno;
					  ret=desfire_write_data(fd,fileno,0x00, 0, strlen(data2), data2);
					  printf("Write result::%d\n",ret);
					  ret =  desfire_read_data(fd,fileno,0x00,0,strlen(data2),&outlen,dataout);
					  if(ret>=0){
					  printf("Read value::%d\n",ret);
					  printf("Read data::%s\n",dataout);
					  }
				 }
				 else{
					 printf("file creation failed with status %d corresponding errno %d\n",ret,errno);
				 }
				//kbGetKeyMs(1000);
				//lcdFlip();
				mif_close(fd);
				return 0;



	//return 0;
}

char * readDataFromMifareCard(char *applicationName,char *filename){
	int fd = -1;
	char MF[3] = {0x00,0x00,0x00};
	char mfauthkey[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int ret;
	uint8_t keyno = 0;
	uint8_t fileno = -1;
	desfire_appinfo info;
	//char dataout[3000];
	char filedata[1800];
	uint32_t outlen;
	//uint8_t pointer[3]={0x00,0x00,0x01};
	(info).AID[0]=0x10;
	(info).AID[1]=0x00;
	(info).AID[2]=0x00;

	info.MasterKeySetting = 0;
	info.NumberOfKey = 1;
	info.CryptoMode =0;
	info.IsSupFID = 1;
	info.IsSupISOFID = 0;
	info.ISOFID[0] = 0x12;
	info.ISOFID[1] = 0x00;
	info.LenOfDFName = 0;

	if(strcmp(applicationName,"personal") == 0){
		fileno = 1;
	}
	else{
		fileno = 2;
	}
	fd = mif_open("/dev/nfc");
	if(fd<0){
		printf("open nfc failed! errno:%d\r\n",errno);
		return -1;
	}
	printf("Open desfire success.Please approach card ....\n");
	while(1){
		//lcdCls();
		//lcdDisplay(0,0,DISP_CFONT,"open device success\n");
		//lcdDisplay(0,2,DISP_CFONT,"please show the card\n");
		//lcdFlip();
		ret = desfire_select_application(fd,MF);
		printf("Returned value on master file select::%d\n",ret);
		/*now, authenticate card */
		printf("About to authenticate\n");
		 ret = desfire_authenticate(fd,keyno,mfauthkey);
		 printf("Returned value on authentication::%d\n",ret);
		 /*select application then create file****/
		 ret =  desfire_select_application(fd,info.AID);
		 ret = desfire_authenticate(fd,keyno,mfauthkey);
		 printf("App selection result:%d\n",ret);
		 ret =  desfire_read_data(fd,fileno,0x00,0,1800,&outlen,filedata);
		 strcpy(dataout,filedata);
		 strcpy(filedata,"");
		 ret =  desfire_read_data(fd,fileno,0x00,0,1800,&outlen,filedata);
		 strcat(dataout,filedata);
		 printf("Read value::%d\n",ret);
		 printf("Read data::%s\n",dataout);
		 return dataout;
	}
}


