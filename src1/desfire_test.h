/*
 * desfire_test.h
 *
 *  Created on: Oct 18, 2018
 *      Author: pos
 */

#ifndef SRC_DESFIRE_TEST_H_
#define SRC_DESFIRE_TEST_H_
#include "sgfplib.h"
#include "keyboart.h"
//#include "seos.h"
#include "cJSON.h"
#include "iso14443.h"

enum apps{
	personal=0,
	biodata
};

char dataout[3000];
char *serial_number;
const struct mif_timeout *ptime;
//int createApplicationAndFileAndWriteData(char *filename,char *data);
int createApplicationAndFileAndWriteData(cJSON* data1,char *data);
char *readDataFromMifareCard(char *applicationName,char *filename);
//int peformCardOperations(cJSON * data1, char *data2);
int peformCardOperations();

int testnfc(void);
#endif /* SRC_DESFIRE_TEST_H_ */
