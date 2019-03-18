/*
 * cardinfo.c

 *
 *  Created on: Dec 9, 2018
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
#include "cardinfo.h"

int personalizecardd(){
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

		//uint8_t fileno = 1;
		desfire_appinfo appInfo;
		(appInfo).AID[0]=0x11;
		(appInfo).AID[1]=0x00;
		(appInfo).AID[2]=0x00;
		appInfo.MasterKeySetting = 0;
		appInfo.NumberOfKey = 2;
		appInfo.CryptoMode =0;
		appInfo.IsSupFID = 0;
		appInfo.IsSupISOFID = 0;
		appInfo.LenOfDFName = 0;







		desfire_std_backup_file_info transactionfile;
		transactionfile.file_size = 100;
		transactionfile.com_sett = 0x00;
		transactionfile.change_access_right_keyno = 0;
		transactionfile.read_and_write_access_right_keyno = 0x00;
		transactionfile.write_access_right_keyno = 0;
		transactionfile.read_access_right_keyno = 0;
		uint8_t transactionfileno = 3;


		/*desfire_std_backup_file_info biodatafiletest;
		biodatafiletest.file_size = 50;
		biodatafiletest.com_sett = 0x00;
		biodatafiletest.change_access_right_keyno = 0;
		biodatafiletest.read_and_write_access_right_keyno = 0;
		biodatafiletest.write_access_right_keyno = 0;
		biodatafiletest.read_access_right_keyno = 0;
		uint8_t biodatafileno = 4;

		desfire_std_backup_file_info balancefile;
		balancefile.file_size = 100;
		balancefile.com_sett = 0x00;
		balancefile.change_access_right_keyno = 0;
		balancefile.read_and_write_access_right_keyno = 0;
		balancefile.write_access_right_keyno = 0;
		balancefile.read_access_right_keyno = 0;
		uint8_t balancefileno = 2;

		desfire_std_backup_file_info dummyfile;
		dummyfile.file_size = 100;
		dummyfile.com_sett = 0x00;
		dummyfile.change_access_right_keyno = 0;
		dummyfile.read_and_write_access_right_keyno = 0;
		dummyfile.write_access_right_keyno = 0;
		dummyfile.read_access_right_keyno = 0;
		uint8_t dummyfileno = 1;*/

		int createbiodatafileresult,createbalancefileresult,createtransactionfileresult,createdummyfileresult;
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
			printf("Initialization done...\n");
			/*************************************************************************/
			/***poll card here ****/
			pollresult =  desfire_poll(fd,0,uid,atslen,ats);
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
				createappstatus = desfire_create_application(fd,&appInfo);
				if(createappstatus == 0){
					printf("App created successfully\n\n");
					//set application key
					int auth = desfire_authenticate(fd,keyno,authkey);
					//select application
					ret = desfire_select_application(fd,appInfo.AID);
					if(ret==0){
						printf("personal details app selection passed\n\n");
						ret = desfire_authenticate(fd,keyno,authkey);
						if(ret !=0){
							printf("authentication failed..\n");
						}
						else{

							createtransactionfileresult =  desfire_create_std_datafile(fd,transactionfileno,&transactionfile);
							if(createtransactionfileresult==0){
								printf("passs\n");

							}
							else{
								printf("create txn file failed with err %d and status %d\n",createtransactionfileresult,errno);

							}
/*							createtransactionfileresult =  desfire_create_std_datafile(fd,biodatafileno,&biodatafiletest);
							if(createtransactionfileresult==0){
								printf("passs\n");
							}
							else{
								printf("create biodata file failed with err %d and status %d\n",createtransactionfileresult,errno);

							}
							createbiodatafileresult =  desfire_create_std_datafile(fd,balancefileno,&balancefile);
							if(createbiodatafileresult ==0){
								printf("success\n\n");
							}
							else{
								printf("create balance failed with err %d and status %d\n",createbiodatafileresult,errno);

							}
							createdummyfileresult= desfire_create_std_datafile(fd,dummyfileno,&dummyfile);
							if(createdummyfileresult == 0){
								printf("success\n\n");
							}
							else{
								printf("create dummy file  failed with err %d and status %d\n",createdummyfileresult,errno);
							}*/

						/*printf("balance file created with result %d and optionally error %d\n",createbalancefileresult,errno);
						printf("transaction file created with result %d and optionally error %d\n",createtransactionfileresult,errno);
						printf("bio data file created with result %d and optionally error %d\n",createbiodatafileresult,errno);*/

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
					ret = desfire_select_application(fd,appInfo.AID);
					if(ret == 0){
						ret = desfire_authenticate(fd,keyno,authkey);
						if(ret ==-1){
							printf("authentication failed\n");
						}
						else{
							printf("authentication passed\n\n");
							printf("-----\n");
						//create file and select or select file
						ret =  desfire_create_std_datafile(fd,fileno,&transactionfile);
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
