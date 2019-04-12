/* 
 * File:   message.h
 * Author: laure
 *
 * Created on 12 avril 2019, 11:30
 */

#ifndef MESSAGE_H
#define	MESSAGE_H

#ifdef	__cplusplus
extern "C" {
#endif


void avertissement(int NumAvertissement);
void message_etat(int etat);
void question_configuration(int etape);

#ifdef	__cplusplus
}
#endif

#endif	/* MESSAGE_H */

