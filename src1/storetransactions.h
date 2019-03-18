/*
 * storetransactions.h
 *
 *  Created on: Dec 27, 2018
 *      Author: pos
 */

#ifndef SRC1_STORETRANSACTIONS_H_
#define SRC1_STORETRANSACTIONS_H_

void merchant_transactionss(void *merchantTransactions);
void merchant_transactions(void);
typedef struct agentdetails{
	  char *agentid;
	  char *merchantid;
	  char *agentaccount;
	  char *merchantaccount;
	  char *userid;
}Agentdetails;
#endif /* SRC1_STORETRANSACTIONS_H_ */
