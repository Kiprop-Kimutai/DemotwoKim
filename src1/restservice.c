/*
 * restservice.c
 *
 *  Created on: Dec 27, 2018
 *      Author: pos
 */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "restservice.h"
#include "curl/curl.h"
#include "cJSON.h"
#include "keyboart.h"
#include "lcd.h"

void *responsedata;
char * function_pt(char *ptr, size_t size, size_t nmemb, void *stream);
int restservice(char *host, char *endpoint,char *method,cJSON *postdata){
	printf("<--------//---->\n");
	CURL *curl;
	CURLcode res;
	char url[100];
	memset(url,0,100);
	strcat(url,host);
	strcat(url,endpoint);
	printf("Hello world\n");
	printf(host);
	printf(endpoint);
	printf("url =>%s\n",url);
	char *requestdata = cJSON_Print(postdata);
	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers,"key:8cg4230pc1");
	//strcpy(url,"http://192.168.0.22:8080/getMenus");
	responsedata = "";
	cJSON_Minify(requestdata);
	printf("%s\n",requestdata);
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl,CURLOPT_URL,url);
		if(strcmp(method,"POST")==0){
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,requestdata);
		}
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,function_pt);
		res = curl_easy_perform(curl);
		printf("\n\n");
		printf("Res:%d\n",res);
	    printf("response data \n %s\n",responsedata);
		curl_easy_cleanup(curl);
		switch(res){
		case CURLE_OK:
		    respdata = responsedata;
		    printf("--------\n");
		    printf("%s\n",respdata);
			//print receipt;
			return 1;
		case CURLE_WRITE_ERROR:
		    respdata = responsedata;
		    printf("--------\n");
		    printf("%s\n",respdata);
			//print receipt
			return 1;
		case CURLE_UNSUPPORTED_PROTOCOL:
			message_display_function(0,"","Http Error", "unsupported protocol", (char *)NULL);
			kb_getkey();
			return 0;
		case CURLE_FAILED_INIT:
			message_display_function(0,"","Curl Init failed", "please retry again", (char *)NULL);
			kb_getkey();
			return 0;
		case CURLE_URL_MALFORMAT:
			message_display_function(0,"","malformed url", "invalid url format", (char *)NULL);
			kb_getkey();
			return 0;
		case CURLE_COULDNT_CONNECT:
			message_display_function(0,"","could not connect", "check connection and retry", (char *)NULL);
			kb_getkey();
			return 0;
		default:
			message_display_function(0,"","general error", "", (char *)NULL);
			kb_getkey();
			return 0;
		}

	}
	else{
		message_display_function(1,"","", "curl initialization failed", (char *)NULL);
		return -1;

	}
}

char* function_pt(char *ptr, size_t size, size_t nmemb, void *stream){
    printf("size \n %d\n", size);
    printf("response body\n %s\n",ptr);
    responsedata = ptr;
    //printf("response data \n %s\n",responsedata);
    return ptr;
}


