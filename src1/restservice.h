/*
 * restservice.h
 *
 *  Created on: Dec 27, 2018
 *      Author: pos
 */

#ifndef SRC1_RESTSERVICE_H_
#define SRC1_RESTSERVICE_H_
#include "cJSON.h"
char *respdata;
int restservice(char *host, char *endpoint,char *method,cJSON *postdata);
#endif /* SRC1_RESTSERVICE_H_ */
