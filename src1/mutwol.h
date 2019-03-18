/*
 * mutwol.h
 *
 *  Created on: Dec 9, 2018
 *      Author: pos
 */

#ifndef SRC1_MUTWOL_H_
#define SRC1_MUTWOL_H_

int personalizecard(char *personaldetails,unsigned char *fp);
int cardoperations(int operation,char *data,char ** response , BYTE ** fingerprint,char *transactiondata,char* personaldetails);
char * UID;

#endif /* SRC1_MUTWOL_H_ */
