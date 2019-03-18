/*
 * jsontest.c

 *
 *  Created on: Oct 23, 2018
 *      Author: pos
 */
#include "string.h"
#include "stdlib.h"
#include "main.h"
#include <jsontest.h>
#include "cJSON.h"
#include "stdio.h"
void jsonOperations(void){
	char *developerString;
	cJSON * pc, *keynote,*company,*evangelist;
	char *pcName, *keynotename,*companyname,*evangelistname;
	cJSON *developerJSON = cJSON_CreateObject();
	cJSON_AddStringToObject(developerJSON,"keynote","apache spark");
	cJSON_AddStringToObject(developerJSON,"pc","dell 5000");
	cJSON_AddStringToObject(developerJSON,"company","AfricaNewLogic");
	cJSON_AddStringToObject(developerJSON,"evangelist","JavaScript");

	//print the json object

	developerString = cJSON_Print(developerJSON);
	printf("JSON string::%s\n",developerString);
	pc = cJSON_GetObjectItem(developerJSON,"pc");
	keynote = cJSON_GetObjectItem(developerJSON,"keynote");
	company = cJSON_GetObjectItem(developerJSON,"company");
	evangelist = cJSON_GetObjectItem(developerJSON,"evangelist");

	pcName = cJSON_Print(pc);
	keynotename = cJSON_Print(keynote);
	companyname = cJSON_Print(company);
	evangelistname = cJSON_Print(evangelist);

	printf("developer pc::%s\n",pcName);
	printf("developer pc::%s\n",keynotename);
	printf("developer pc::%s\n",companyname);
	printf("developer pc::%s\n",evangelistname);

}


