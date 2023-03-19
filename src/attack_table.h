#ifndef ATTACK_TABLE_H
#define ATTACK_TABLE_H

/**
 *
 */
struct AttackTable;

/**
 *
 */
typedef struct AttackTable *AttackTable;

/**
 *
 */
AttackTable attack_table();

/**
 *
 */
void finalize_attack_table(AttackTable this);

#endif
