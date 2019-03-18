/*
 * storetransactions.c
 *
 *  Created on: Dec 27, 2018
 *      Author: pos
 */

#include "storetransactions.h"
#include "string.h"
#include "stdlib.h"
//#include "cJSON.h"
#include "stdio.h"
#include "restservice.h"
#include "lcd.h"
#include "keyboart.h"


Agentdetails agent;

int rolluptransactions(void);
int transfertostore(void);
int withdrawtobank(void);
const char storetransactionmenus[][100] = {"Roll up","Transfer to Store","Withdraw to Bank","Exit"};
void initializeAgent(void);
char *removefirstandlastchar(char *str,char *destt);
void merchant_transactionss(void *merchantTransactions){
	int resp;
	//cJSON *merchantTransactions = cJSON_CreateObject();
	cJSON *storeTxn = cJSON_CreateObject();
/*	cJSON_AddStringToObject(merchantTransactions,"transOperation","100");
	cJSON_AddStringToObject(merchantTransactions,"debitAccountNo","29785764");
	cJSON_AddStringToObject(merchantTransactions,"creditAccountNo","39785761");*/
	//cJSON_AddStringToObject(merchantTransactions,"amount","2200");
	cJSON_AddStringToObject(merchantTransactions,"transId","201812271950");
	cJSON_AddStringToObject(merchantTransactions,"terminalId","82:34:26:05");
	cJSON_AddStringToObject(merchantTransactions,"authMode","101");
	cJSON_AddStringToObject(merchantTransactions,"userId","sor225");
	cJSON_AddStringToObject(merchantTransactions,"date","20181227195044");
	cJSON_AddItemToObject(storeTxn,"storeTxn",merchantTransactions);

	printf("Check JSON format::%s\n",cJSON_Print(storeTxn));

	printf("-------------mock rest service call here -------------\n");
	resp = restservice("http://192.168.0.29:2000/api","/storetxn/storetxn","POST",storeTxn);
	if(resp){
		printf("will print receipt\n");
		printf("%s\n",respdata);
	}


}
void merchant_transactions(void){
	int selected = 0;
	while(selected>=0){
		selected = lcd_menu("Store Transactions", storetransactionmenus, sizeof(storetransactionmenus)/100, selected);
		switch(selected){
			case 0:
				printf("roll up txn\n");
				rolluptransactions();
				break;
			case 1:
				printf("transfer to store\n");
				transfertostore();
				break;
			case 2:
				printf("withdraw to bank\n");
				withdrawtobank();
				break;
			case 3:
				return;
			default:
				break;

		}
	}
}

int  rolluptransactions(void){
	int x,ret;
	char *dest = NULL;
	char getCharacters[40];
	char getCharacters1[0];
	char forminput[2][30] = {"Enter amount","confirm roll up account"};
	cJSON *merchantTransactions =cJSON_CreateObject();
	initializeAgent();
	cJSON_AddStringToObject(merchantTransactions,"transOperation","100");
	cJSON_AddStringToObject(merchantTransactions,"debitAccountNo",agent.agentaccount);
	cJSON_AddStringToObject(merchantTransactions,"creditAccountNo",agent.merchantaccount);
	for(x=0;x<2;x++){
		ret = kb_getStringtwo(ALPHA_IN ,ALPHA_IN ,  1, 16, getCharacters,getCharacters1,"abc" , forminput[x], "","Roll up transaction", 0);
		if(strlen(getCharacters)>0 && ret!=-1){
			if(x==0){
			//cJSON_AddStringToObject(merchantTransactions,"amount",getCharacters);
				cJSON_AddNumberToObject(merchantTransactions,"amount",atoi(getCharacters));
			}
			else if(x==1){
			cJSON_AddStringToObject(merchantTransactions,"creditAccountNo",getCharacters);
			}
		}
		else{
			//return NULL;
		}

	}
	printf("form data....\n %s\n",cJSON_Print(merchantTransactions));
	while(1){
		//message_display_function(0,"","", "submit transaction? Enter to submit or Cancel", (char *)NULL);
		message_display_function(1,"","Transaction Details","",(char *)NULL);
		int y=get_y_position();

		lcd_printf(ALG_LEFT, "%s", "Transfer to");
		lcd_printf_ex(ALG_RIGHT,y," %s",removefirstandlastchar(cJSON_Print(cJSON_GetObjectItem(merchantTransactions,"creditAccountNo")),dest));
		y=get_y_position();
		lcd_printf(ALG_LEFT, "%s", "Amount");
		lcd_printf_ex(ALG_RIGHT,y," %s",cJSON_Print(cJSON_GetObjectItem(merchantTransactions,"amount")));
		lcd_printf(ALG_LEFT, "");
		lcd_printf(ALG_LEFT, "__________________________________________");
		y=get_y_position();
		defined_x=150;
		lcd_set_font_color(COLOR_BLUE);
		lcd_printf(ALG_CENTER, "%s","Cancel to exit     :     Enter to confirm");
		lcd_flip();
		lcd_set_font_color(COLOR_BLACK);
		int key = kb_getkey();
		if(key == 0x0D){
			printf("This way out...\n");
			//return merchantTransactions;
			merchant_transactionss(merchantTransactions);
			return 0;
		}
		else if(key == 0x1B){
			printf("will cancel...\n");
			return -1;
		}
		else{
			//do nothing
		}
	}

	//return formData;
}

int transfertostore(void){
	int x,ret;
	char *dest=NULL;
	char getCharacters[40];
	char getCharacters1[0];
	char forminput[2][30] = {"Enter amount","confirm store  account"};
	cJSON *merchantTransactions =cJSON_CreateObject();
	initializeAgent();
	cJSON_AddStringToObject(merchantTransactions,"transOperation","100");
	cJSON_AddStringToObject(merchantTransactions,"debitAccountNo",agent.agentaccount);
	//cJSON_AddStringToObject(merchantTransactions,"creditAccountNo",agent.merchantaccount);
	for(x=0;x<2;x++){
		ret = kb_getStringtwo(NUM_IN ,NUM_IN ,  1, 16, getCharacters,getCharacters1,"" , forminput[x], "","Roll up transaction", 0);
		if(strlen(getCharacters)>0 && ret!=-1){
			if(x==0){
				cJSON_AddNumberToObject(merchantTransactions,"amount",atoi(getCharacters));
			}
			else if(x==1){
			cJSON_AddStringToObject(merchantTransactions,"creditAccountNo",getCharacters);
			}
		}
		else{
			//return NULL;
		}

	}
	printf("form data....\n %s\n",cJSON_Print(merchantTransactions));
	while(1){
		//message_display_function(0,"","", "submit transaction? Enter to submit or Cancel", (char *)NULL);
		message_display_function(1,"","Transaction Details","",(char *)NULL);
		int y=get_y_position();

		lcd_printf(ALG_LEFT, "%s", "Transfer to");
		lcd_printf_ex(ALG_RIGHT,y," %s",removefirstandlastchar(cJSON_Print(cJSON_GetObjectItem(merchantTransactions,"creditAccountNo")),dest));
		y=get_y_position();
		lcd_printf(ALG_LEFT, "%s", "Amount");
		lcd_printf_ex(ALG_RIGHT,y," %s",cJSON_Print(cJSON_GetObjectItem(merchantTransactions,"amount")));
		lcd_printf(ALG_LEFT, "");
		lcd_printf(ALG_LEFT, "__________________________________________");
		y=get_y_position();
		defined_x=150;
		lcd_set_font_color(COLOR_BLUE);
		lcd_printf(ALG_CENTER, "%s","Cancel to exit     :     Enter to confirm");
		lcd_flip();
		lcd_set_font_color(COLOR_BLACK);
		int key = kb_getkey();
		if(key == 0x0D){
			printf("This way out...\n");
			//return merchantTransactions;
			merchant_transactionss(merchantTransactions);
			return 0;
		}
		else if(key == 0x1B){
			printf("will cancel...\n");
			return -1;
		}
		else{
			//do nothing
		}
	}
}
int withdrawtobank(void){

	int x,ret;
	char *dest = NULL;
	char getCharacters[40];
	char getCharacters1[0];
	char forminput[2][30] = {"Enter amount","bank account"};
	cJSON *merchantTransactions =cJSON_CreateObject();
	initializeAgent();
	cJSON_AddStringToObject(merchantTransactions,"transOperation","100");
	cJSON_AddStringToObject(merchantTransactions,"debitAccountNo",agent.agentaccount);
	//cJSON_AddStringToObject(merchantTransactions,"creditAccountNo",agent.merchantaccount);
	for(x=0;x<2;x++){
		ret = kb_getStringtwo(ALPHA_IN ,ALPHA_IN ,  1, 16, getCharacters,getCharacters1,"" , forminput[x], "","Roll up transaction", 0);
		if(strlen(getCharacters)>0 && ret!=-1){
			if(x==0){
				cJSON_AddNumberToObject(merchantTransactions,"amount",atoi(getCharacters));
			}
			else if(x==1){
			cJSON_AddStringToObject(merchantTransactions,"creditAccountNo",getCharacters);
			}
		}
		else{
			//return NULL;
		}

	}
	printf("form data....\n %s\n",cJSON_Print(merchantTransactions));
	while(1){
		//message_display_function(0,"","", "submit transaction? Enter to submit or Cancel", (char *)NULL);
		message_display_function(1,"","Transaction Details","",(char *)NULL);
		int y=get_y_position();

		lcd_printf(ALG_LEFT, "%s", "Transfer to");
		lcd_printf_ex(ALG_RIGHT,y," %s",removefirstandlastchar(cJSON_Print(cJSON_GetObjectItem(merchantTransactions,"creditAccountNo")),dest));
		y=get_y_position();
		lcd_printf(ALG_LEFT, "%s", "Amount");
		lcd_printf_ex(ALG_RIGHT,y," %s",cJSON_Print(cJSON_GetObjectItem(merchantTransactions,"amount")));
		lcd_printf(ALG_LEFT, "");
		lcd_printf(ALG_LEFT, "__________________________________________");
		y=get_y_position();
		defined_x=150;
		lcd_set_font_color(COLOR_BLUE);
		lcd_printf(ALG_CENTER, "%s","Cancel to exit     :     Enter to confirm");
		lcd_flip();
		lcd_set_font_color(COLOR_BLACK);
		int key = kb_getkey();
		if(key == 0x0D){
			printf("This way out...\n");
			//return merchantTransactions;
			merchant_transactionss(merchantTransactions);
			return 0;
		}
		else if(key == 0x1B){
			printf("will cancel...\n");
			return -1;
		}
		else{
			//do nothing
		}
	}
}
char *removefirstandlastchar(char *str,char *destt){
	  int x,y=0;
	  char *dest;
	  dest = calloc((strlen(str)-2),sizeof(char));
	  memset(dest,0,sizeof(dest));
	  printf("%s\n",str);
	  for(x=1;x<(strlen(str)-1);x++){
	    dest[y] = str[x];
	    y++;
	  }
	  destt = dest;
	  return destt;
}
void initializeAgent(void){
	agent.agentid = "29785761";
	agent.merchantid = "3978761";
	agent.agentaccount = "8cg230pci";
	agent.merchantaccount = "8cg4240pci";
	agent.userid = "s0r254";
}
