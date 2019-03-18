/*
 * print_receipt.h
 *
 *  Created on: Dec 31, 2018
 *      Author: pos
 */

#ifndef SRC1_PRINT_RECEIPT_H_
#define SRC1_PRINT_RECEIPT_H_

int print_receipt(char * type_of_receipt , cJSON * transaction ,  cJSON * personal_data , int * printflag ,  int * print_complete) ;
#endif /* SRC1_PRINT_RECEIPT_H_ */
