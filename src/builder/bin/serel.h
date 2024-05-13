#ifndef SRL__H_
#define SRL__H_

#include "../../bin/include.h"
#include "../class/head/project.h"
#include "../class/head/target_ex.h"
#include "../class/head/var.h"
#include "../class/head/err.h"
#include "../setup/assist.h"
#include "../StreamEI/StreamEI.h"

extern void serelization_full(std::ofstream &file);
extern void deserelization_full(std::ifstream &file, uint32_t exp);

extern void deserelization_template(std::ifstream &file);

#endif